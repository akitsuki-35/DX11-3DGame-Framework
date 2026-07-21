/*============================================================
*	@file	 : transform.cpp
*	@brief	 : トランスフォーム
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/05/19
*	@updated : 2026/06/02
*============================================================*/
#include "Transform.h"

using namespace DirectX;

DirectX::XMMATRIX Transform::createScaleMatrix() const
{
    // スケール行列作成
    XMMATRIX scale =
        XMMatrixScaling(
            mScale.x,
            mScale.y,
            mScale.z);

    return scale;
}

DirectX::XMMATRIX Transform::createRotationMatrix() const
{
    // 回転行列作成
    XMMATRIX rotation =
        XMMatrixRotationRollPitchYaw(
            mRotation.x,
            mRotation.y,
            mRotation.z);

    return rotation;
}

DirectX::XMMATRIX Transform::createTranslationMatrix() const
{
    // 移動行列作成
    XMMATRIX translation =
        XMMatrixTranslation(
            mPosition.x,
            mPosition.y,
            mPosition.z);

    return translation;
}

void Transform::rebuildWorldMatrix() const
{
    XMMATRIX scale = createScaleMatrix();
    XMMATRIX rotation = createRotationMatrix();
    XMMATRIX translation = createTranslationMatrix();

    mWorldMatrix = scale * rotation * translation;

    mDirty = false;
}