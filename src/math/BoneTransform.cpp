/*============================================================
*	@file	 : BoneTransform.cpp
*	@brief	 : ボーン用トランスフォーム
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/13
*	@updated : 2026/09/16
*============================================================*/
#include "BoneTransform.h"

DirectX::XMMATRIX BoneTransform::ToMatrix() const
{
    // XMMATRIXに変換
    DirectX::XMMATRIX scale = DirectX::XMMatrixScaling(Scale.x, Scale.y, Scale.z);
    DirectX::XMMATRIX rotation = Rotation.ToMatrix();
    DirectX::XMMATRIX translation = DirectX::XMMatrixTranslation(Position.x, Position.y, Position.z);

    return scale * rotation * translation;
}
