/*============================================================
*	@file	 : Renderer.h
*	@brief	 : 描画コンポーネント基底クラス
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/27
*	@updated : 2026/08/15
*============================================================*/
#pragma once

#include "Component.h"
#include <string>
#include <DirectXMath.h>

/*------------------------------------------------------------
	前方宣言
------------------------------------------------------------*/
class Vector3;
class Shader;

/*------------------------------------------------------------
	ソート用構造体
------------------------------------------------------------*/
// 描画レイヤー
enum class Layer : uint8_t
{
	World,
	Alpha,
	UI,

	Count
};

// 描画ソート用情報
struct SORTKEY
{
	Layer layer{};
	float Zdepth{};

	bool operator<(const SORTKEY& key) const
	{
		if (layer != key.layer)
			return layer < key.layer;

		if (std::abs(Zdepth - key.Zdepth) < 0.0001f) {
			return false;
		}

		return Zdepth > key.Zdepth;
	}
};

/*============================================================
*	@class	: Renderer
*	@brief	: 描画コンポーネント基底クラス
*============================================================*/
class Renderer : public Component
{
protected:
	// シェーダー
	Shader* _mShader{ nullptr };

	// ソート用情報
	SORTKEY mSortKey{};

	void Bind() const;

public:
	Renderer(GameObject* owner)
		: Component(owner){}

	void Finalize() override {
		_mShader = nullptr;
	}

	// 描画
	virtual void Draw() const = 0;

	// シェーダー読み込み
	Renderer* LoadShader(const std::string& keyName);

	// ゲッター
	Shader* GetShader() const { return _mShader; }
	SORTKEY& GetSortKey() { return mSortKey; }

	// セッター
	void CalcCameraZ(Vector3 cameraPosition, Vector3 cameraForward);
	void SetZdepth(float z) { mSortKey.Zdepth = z; }

private:
	// ワールド行列取得
	virtual DirectX::XMMATRIX getWorldMatrix() const = 0;
};