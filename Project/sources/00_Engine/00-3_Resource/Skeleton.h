/*============================================================
*	@file	 : Skeleton.h
*	@brief	 : ボーン構造体＆スケルトン
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/07
*	@updated : 2026/08/07
*============================================================*/
#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <DirectXMath.h>

/*============================================================
*	@class	: Skeleton
*	@brief	: ボーン構造体＆スケルトン
*============================================================*/
class Skeleton final
{
public:
    // ボーン構造体
    struct Bone
    {
        std::string Name{}; // ボーン名
        int ParentIndex{ -1 }; // 親ボーン
        DirectX::XMFLOAT4X4 Offset{}; // オフセット行列
        DirectX::XMFLOAT4X4 Local{}; // ローカル変換
        DirectX::XMFLOAT4X4 Global{}; // グローバル変換
    };

private:
    std::unordered_map<std::string, int> mBoneMap{};
    std::vector<Bone> mBones{};

    std::vector<DirectX::XMFLOAT4X4>mSkinningMatrices{};
    DirectX::XMFLOAT4X4 mGlobalInverse{};

public:
    int AddBone(const Bone& bone){
        int index = static_cast<int>(mBones.size());
        mBones.push_back(bone);
        mBoneMap.emplace(bone.Name, index);
        
        return index;
    }

    int FindBone(const std::string& name) const;

    void Update();

    // ゲッター
    Bone& GetBone(size_t index) { return mBones[index]; }
    size_t GetBoneCount() const { return mBones.size(); }
    const std::vector<DirectX::XMFLOAT4X4>& GetSkinningMatrices() const { return mSkinningMatrices; }
    DirectX::XMFLOAT4X4& GetGlobalInverse() { return mGlobalInverse; }

private:
    void updateGlobal(int index);
    void updateSkinningMatrices();
};