/*============================================================
*	@file	 : Skeleton.cpp
*	@brief	 : ボーン構造体＆スケルトン
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/07
*	@updated : 2026/08/07
*============================================================*/
#include "Skeleton.h"

int Skeleton::FindBone(const std::string& name) const
{
    // ボーン探索
    auto it = mBoneMap.find(name);

    if (it == mBoneMap.end()) {
        return -1;
    }

    return it->second;
}

void Skeleton::Update()
{
    for (size_t i = 0; i < mBones.size(); i++)
    {
        Bone& bone = mBones[i];

        if (bone.ParentIndex == -1) {
            updateGlobal(static_cast<int>(i));
        }
    }

    updateSkinningMatrices();
}

void Skeleton::updateGlobal(int index)
{
    Bone& bone = mBones[index];

    DirectX::XMMATRIX local = DirectX::XMLoadFloat4x4(&bone.Local);

    if (bone.ParentIndex == -1) {
        DirectX::XMStoreFloat4x4(&bone.Global, local);
    }
    else {
        DirectX::XMMATRIX parent = DirectX::XMLoadFloat4x4(&mBones[bone.ParentIndex].Global);

        DirectX::XMMATRIX global = parent * local;

        DirectX::XMStoreFloat4x4(&bone.Global, global);
    }

    // 子ボーンを更新
    for (size_t i = 0; i < mBones.size(); i++)
    {
        if (mBones[i].ParentIndex == index) {
            updateGlobal(static_cast<int>(i));
        }
    }
}

void Skeleton::updateSkinningMatrices()
{
    mSkinningMatrices.resize(mBones.size());

    DirectX::XMMATRIX globalInverse = XMLoadFloat4x4(&mGlobalInverse);

    for (size_t i = 0; i < mBones.size(); ++i) {
        const Bone& bone = mBones[i];

        // グローバル行列取得
        DirectX::XMMATRIX global = DirectX::XMLoadFloat4x4(&bone.Global);

        DirectX::XMFLOAT4X4 debugGlobal{};
        DirectX::XMStoreFloat4x4(&debugGlobal, global);

        // オフセット行列取得
        DirectX::XMMATRIX offset = DirectX::XMLoadFloat4x4(&bone.Offset);

        // スキニング行列作成
        DirectX::XMMATRIX skinning = globalInverse * global * offset;

        DirectX::XMStoreFloat4x4(&mSkinningMatrices[i], skinning);
    }
}