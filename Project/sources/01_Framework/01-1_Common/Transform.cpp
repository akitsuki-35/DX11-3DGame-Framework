/*============================================================
*	@file	 : Transform.cpp
*	@brief	 : トランスフォーム
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/05/19
*	@updated : 2026/08/04
*============================================================*/
#include "Transform.h"

using namespace DirectX;

DirectX::XMMATRIX Transform::createScaleMatrix() const
{
    // スケール行列作成
    XMMATRIX scale =XMMatrixScaling(mScale.x, mScale.y, mScale.z);

    return scale;
}

DirectX::XMMATRIX Transform::createRotationMatrix() const
{
    // 回転行列作成
    XMMATRIX rotation = XMMatrixRotationRollPitchYaw(mRotation.x, mRotation.y, mRotation.z);

    return rotation;
}

DirectX::XMMATRIX Transform::createTranslationMatrix() const
{
    // 移動行列作成
    XMMATRIX translation = XMMatrixTranslation(mPosition.x, mPosition.y, mPosition.z);

    return translation;
}

DirectX::XMMATRIX Transform::createBillboardRotation(const DirectX::XMMATRIX& view) const
{
    // ビルボード用回転行列作成
    XMMATRIX billboardView = XMMatrixInverse(nullptr, view);
    billboardView.r[3].m128_f32[0] = 0.0f;
    billboardView.r[3].m128_f32[1] = 0.0f;
    billboardView.r[3].m128_f32[2] = 0.0f;

    return billboardView;
}

void Transform::rebuildWorldMatrix(const DirectX::XMMATRIX& rotation) const
{
    // ワールド行列を更新
    XMMATRIX scale = createScaleMatrix();
    XMMATRIX translation = createTranslationMatrix();

    mWorldMatrix = scale * rotation * translation;

    mDirty = false;
}