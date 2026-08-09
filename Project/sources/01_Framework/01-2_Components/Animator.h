/*============================================================
*	@file	 : Animator.h
*	@brief	 : アニメーターコンポーネント
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/07
*	@updated : 2026/08/07
*============================================================*/
#pragma once

#include "Component.h"
#include "GameObject.h"
#include "AnimationManager.h"
#include "ModelRenderer.h"
#include <cassert>

/*============================================================
*	@class	: Animator
*	@brief	: アニメーターコンポーネント
*============================================================*/
class Animator final : public Component
{
private:
    class Skeleton* mSkeleton{};
    class Animation* mAnimation{};
    double mCurrentTime{};

public:
    Animator(GameObject* owner)
        : Component(owner) {}

    void Set(const std::string& keyName) {
        mAnimation = AnimationManager::getInstance().Get(keyName);
        assert(setSkeleton());
        mCurrentTime = 0.0;
    }
    void Update(double dt);

    // ゲッター
    double GetTime() const { return mCurrentTime; }

private:
    bool setSkeleton() {
        Model* model{};

        // オブジェクトのModelRendererコンポーネント取得
        ModelRenderer* renderer = _mOwner->GetComponent<ModelRenderer>();

        if (!renderer) {
            return false;
        }

        // ModelRendererのモデル取得
        model = renderer->GetModel();

        if (!model) {
            return false;
        }

        // モデルからスケルトンを取得
        mSkeleton = &model->GetSkeleton();

        return true;
    }

    // ボーンアニメーション計算
    void calculateBoneTransform(const Animation::Channel& channel, double time);
    Vector3 calculatePosition(const std::vector<Animation::KeyPosition>& keys, double time);
    Quaternion calculateRotation(const std::vector<Animation::KeyRotation>& keys, double time);
    Vector3 calculateScale(const std::vector<Animation::KeyScale>& keys, double time);
};