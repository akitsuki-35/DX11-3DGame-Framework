/*============================================================
*	@file	 : Player.cpp
*	@brief	 : プレイヤー
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/05/19
*	@updated : 2026/07/26
*============================================================*/
#include "main.h"
#include "input.h"
#include "renderer.h"
#include "modelRenderer.h"
#include "ModelDrawable.h"
#include "game.h"
#include "audio.h"
#include "player.h"
#include "camera.h"
#include "bullet.h"

#include "tree.h"
#include "box.h"

#include "DeviceManager.h"
#include "BufferManager.h"

void Player::Initialize()
{
	mLayer = 1;

	mTransform = Transform(
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 1.0f, 1.0f, 1.0f }
	);

	mVelocity = { 0.0f, 0.0f, 0.0f };
	mAccel = { 50.0f, 0.0f, 50.0f };

	// コンポーネント読込
	//AddComponent<ModelRenderer>(this);
	//AddComponent<ModelRenderer>(this)->Load("assets\\models\\player.obj");
	//AddComponent<ModelDrawable>(this)->LoadModel("assets\\models\\player.obj");

	// シェーダー読込
	mShader = ShaderManager::getInstance().Get("Unlit");

	mSE = AddComponent<Audio>(this);
	mSE->Load("assets\\audio\\wan.wav");
}

void Player::Finalize()
{
	GameObject::Finalize();
}

void Player::Update()
{
	float dt = 1.0f / 60.0f; // 経過時間
	float j = 15.0f; // ジャンプ力
	float g = 30.0f; // 重力加速度
	float r = 5.0f; // 抵抗力

	Vector3 position = mTransform.GetPosition();
	Vector3 rotation = mTransform.GetRotation();
	Vector3 scale = mTransform.GetScale();

	Vector3 oldPosition = mTransform.GetPosition(); // プレイヤー移動前座標

	Camera* camera = Game::GetGameObject<Camera>();
	Vector3 forward = camera->GetForward();
	Vector3 right = camera->GetRight();

	forward.y = 0.0f;
	forward.Normalize();

	right.y = 0.0f;
	right.Normalize();

	// キー入力移動処理
	if (Input::GetKeyPress('D')) {
		mVelocity += right * 50.0f * dt;
	}
	if (Input::GetKeyPress('A')) {
		mVelocity -= right * 50.0f * dt;
	}
	if (Input::GetKeyPress('W')) {
		mVelocity += forward * 50.0f * dt;
	}
	if (Input::GetKeyPress('S')) {
		mVelocity -= forward * 50.0f * dt;
	}

	float yaw = atan2f(mVelocity.x, mVelocity.z);
	yaw += XM_PI;
	rotation.y = yaw;

	// ジャンプ
	if (mGround) {
		if (Input::GetKeyTrigger('K')) {
			mVelocity.y += j; // 撃力

			// スケールアニメーション
			//mTransform.SetScale({ 0.75f, 2.0f, 0.75f });
			scale.y = 2.0f;
			scale.x = 0.75f;
			scale.z = 0.75f;

			mSE->Play();
		}
	}

	// スケールを元に戻す
	scale.x += (1.0f - scale.x) * 0.1f;
	scale.y += (1.0f - scale.y) * 0.1f;
	scale.z += (1.0f - scale.z) * 0.1f;

	// 重力加速度
	mVelocity.y += -g * dt;

	// 摩擦抵抗
	mVelocity.x += -mVelocity.x * r * dt;
	mVelocity.z += -mVelocity.z * r * dt;

	// 移動処理
	position += mVelocity * dt;

	bool oldGround = mGround;
	mGround = false;

	// 地面との衝突判定
	if (position.y < 0.0f) {
		position.y = 0.0f;
		mVelocity.y = 0.0f;
		mGround = true;
	}

	//// 木との衝突判定
	//auto trees = Game::GetGameObjects<Tree>();
	//for (auto tree : trees) {
	//	Vector3 treePosition = tree->GetPosition();
	//	Vector3 playerPosition = mPosition;

	//	treePosition.y = 0.0f;
	//	playerPosition.y = 0.0f;
	//	Vector3 dir = playerPosition - treePosition; // 方向ベクトル算出
	//	float length = dir.Length(); // 距離計算

	//	if (length < 1.5f) {
	//		dir /= length; // 正規化
	//		dir *= 1.5f - length;

	//		mPosition += dir;
	//	}
	//}

	//// 箱との衝突判定
	//auto boxes = Game::GetGameObjects<Box>();
	//for (auto box : boxes) {
	//	Vector3 boxPosition = box->GetPosition();
	//	Vector3 boxScale = box->GetScale();

	//	if (boxPosition.x - boxScale.x < mPosition.x &&
	//		mPosition.x < boxPosition.x + boxScale.x &&
	//		boxPosition.z - boxScale.z < mPosition.z &&
	//		mPosition.z < boxPosition.z + boxScale.z) 
	//	{
	//		if (boxPosition.y + boxScale.y < mPosition.y &&
	//			mPosition.y < boxPosition.y + boxScale.y * 2.0f &&
	//			mVelocity.y < 0.0f)
	//		{
	//			mPosition.y = boxPosition.y + boxScale.y * 2.0f;
	//			mVelocity.y = 0.0f;
	//			mGround = true;
	//		}
	//		else if (boxPosition.y - boxScale.y < mPosition.y &&
	//			mPosition.y < boxPosition.y + boxScale.y)
	//		{
	//			mPosition.x = oldPosition.x + mScale.x;
	//			mPosition.z = oldPosition.z + mScale.z;

	//			mVelocity.x = 0.0f;
	//			mVelocity.z = 0.0f;
	//		}
	//	}
	//}

	//if (!oldGround && mGround) {
	//	// スケールアニメーション
	//	mScale.y = 0.5f;
	//	mScale.x = 1.5f;
	//	mScale.z = 1.5f;
	//}

	// スケールを元に戻す
	//mScale.x += (1.0f - mScale.x) * 0.1f;
	//mScale.y += (1.0f - mScale.y) * 0.1f;
	//mScale.z += (1.0f - mScale.z) * 0.1f;

	//// 弾の発射
	//if (Input::GetKeyTrigger('J')) {

	//	Bullet* bullet = Game::AddGameObject<Bullet>();
	//	bullet->SetPosition({ mPosition.x, mPosition.y, mPosition.z });
	//	bullet->SetVelocity(GetForward() * 50.0f);
	//}
	
	// 移動アニメーション
	if (mGround) {
		mMoveAnimation += mVelocity.Length() * dt;
		scale.y += sinf(mMoveAnimation * 3.0f) * 0.03f;
	}

	mTransform.SetPosition(position);
	mTransform.SetRotation(rotation);
	mTransform.SetScale(scale);

	GameObject::Update();
}

void Player::Draw() const
{
	// 入力レイアウト設定
	D3D11::DeviceManager::getInstance().GetContext()->IASetInputLayout(mShader->GetLayout());

	// シェーダー設定
	D3D11::DeviceManager::getInstance().GetContext()->VSSetShader(mShader->GetVertexShader(), NULL, 0);
	D3D11::DeviceManager::getInstance().GetContext()->PSSetShader(mShader->GetPixelShader(), NULL, 0);

	// マトリクス設定
	D3D11::BufferManager::getInstance().SetWorldMatrix(mTransform.GetWorldMatrix());

	GameObject::Draw(); // 継承元のDrawを呼び出す
}