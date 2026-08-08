/*============================================================
*	@file	 : BoneTransform.h
*	@brief	 : ボーン用トランスフォーム
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/07
*	@updated : 2026/08/07
*============================================================*/
#pragma once

#include "Vector3.h"
#include "Quaternion.h"

/*============================================================
*	@class	: BoneTransform
*	@brief	: ボーン用トランスフォーム
*============================================================*/
class BoneTransform
{
public:
    Vector3 Position{};
    Quaternion Rotation{};
    Vector3 Scale{ 1.0f,1.0f,1.0f };

    DirectX::XMMATRIX ToMatrix() const {
        DirectX::XMMATRIX scale = DirectX::XMMatrixScaling(Scale.x, Scale.y, Scale.z);
        DirectX::XMMATRIX rotation = Rotation.ToMatrix();
        DirectX::XMMATRIX translation = DirectX::XMMatrixTranslation(Position.x,Position.y,Position.z);

        return scale * rotation * translation;
    }
};