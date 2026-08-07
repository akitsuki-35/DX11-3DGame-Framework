/*============================================================
*	@file	 : Quaternion.h
*	@brief	 : クォータニオンクラス
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/07
*	@updated : 2026/08/07
*============================================================*/
#pragma once

#include <DirectXMath.h>

/*============================================================
*	@class	: Quaternion
*	@brief	: クォータニオン
*============================================================*/
class Quaternion
{
public:
    float x{};
    float y{};
    float z{};
    float w{ 1.0f };

    // XMMATRIXへ変換
    DirectX::XMMATRIX ToMatrix() const {
        DirectX::XMVECTOR q = DirectX::XMVectorSet(x, y, z, w);
        return DirectX::XMMatrixRotationQuaternion(q);
    }

    // 回転を補間
    static Quaternion Slerp(const Quaternion& a, const Quaternion& b, float t) {
        // 球面補間
        DirectX::XMVECTOR qa = DirectX::XMVectorSet(a.x, a.y, a.z, a.w);
        DirectX::XMVECTOR qb = DirectX::XMVectorSet(b.x, b.y, b.z, b.w);
        DirectX::XMVECTOR result = DirectX::XMQuaternionSlerp(qa, qb, t);

        DirectX::XMFLOAT4 value{};
        DirectX::XMStoreFloat4(&value, result);

        return Quaternion(value.x, value.y, value.z, value.w);
    }
};