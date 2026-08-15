/*============================================================
*	@file	 : Scene.cpp
*	@brief	 : シーン基底クラス
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/15
*	@updated : 2026/08/15
*============================================================*/
#include "Scene.h"
#include "DeviceManager.h"
#include "D3D11Config.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Camera.h"
#include <algorithm>

void Scene::Finalize()
{
	for (const auto& obj : _mGameObjects) {
		obj->Finalize();
	}

	_mGameObjects.clear();
}

void Scene::Update()
{
	for (const auto& obj : _mGameObjects) {
		obj->Update();
	}

	// ゲームオブジェクト削除
	_mGameObjects.remove_if([](const auto& object) {
		return object->Destroy();
		});	
}

void Scene::Draw() const
{
	D3D11::DeviceManager::getInstance().SetSamplerState(D3D11::RenderState::Sampler::Anisotropic);

	// カメラ取得
	Camera* camera = GetGameObject<Camera>();
	
	// 描画用キュー
	std::vector<GameObject*> renderQueue{};

	// 描画コンポーネントを持つオブジェクトをキューに登録
	for (const auto& obj : _mGameObjects) {
		if (auto* renderer = obj->GetComponent<Renderer>()) {
			renderQueue.push_back(obj.get());
		}
	}

	if (camera) {
		Vector3 forward = camera->GetForward();
		Vector3 position = camera->GetTransform().GetPosition();

		// カメラからの距離計算
		// 3Dオブジェクトのみ計算
		for (const auto& obj : renderQueue) {
			auto* renderer = obj->GetComponent<Renderer>();
			if (renderer->GetSortKey().layer != Layer::UI) {
				renderer->CalcCameraZ(position, forward);
			}
		}

		// Zソート
		std::sort(renderQueue.begin(), renderQueue.end(), [](GameObject* a, GameObject* b) {
			return a->GetComponent<Renderer>()->GetSortKey() < b->GetComponent<Renderer>()->GetSortKey();
			});

		// カメラ行列をセット
		camera->SetMatrix();
	}
	else {
		// レイヤー番号のみで描画
		std::sort(renderQueue.begin(), renderQueue.end(), [](GameObject* a, GameObject* b) {
			return a->GetComponent<Renderer>()->GetSortKey().layer < b->GetComponent<Renderer>()->GetSortKey().layer;
			});
	}

	// オブジェクト描画
	for (int layer = 0; layer < static_cast<int>(Layer::Count); layer++)
	{
		for (const auto& obj : renderQueue) {
			auto renderer = obj->GetComponent<Renderer>();

			if (renderer) {
				if (static_cast<int>(renderer->GetSortKey().layer) == layer) {
					obj->Draw();
				}
			}
		}
	}
}