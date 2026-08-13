/*============================================================
*	@file	 : Animator.cpp
*	@brief	 : アニメーターコンポーネント
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/07
*	@updated : 2026/08/07
*============================================================*/
#include "Animator.h"
#include "Skeleton.h"
#include "BoneTransform.h"
#include "AnimationManager.h"
#include "ModelRenderer.h"
#include "GameObject.h"
#include <cmath>
using namespace DirectX;

void Animator::Set(const std::string& keyName)
{
    mAnimation = AnimationManager::getInstance().Get(keyName);
    assert(setSkeleton());
    mCurrentTime = 0.0;
}

void Animator::Update(double dt)
{
    if (!mAnimation || !mSkeleton) {
        return;
    }

    // Tickへ変換
    mCurrentTime += dt * mAnimation->GetTicksPerSecond();

    // アニメーションループ
    if (mCurrentTime >= mAnimation->GetDuration()) {
        mCurrentTime = std::fmod(mCurrentTime, mAnimation->GetDuration());
    }

    // チャンネル更新
    for (auto& channel : mAnimation->GetChannels()) {
        calculateBoneTransform(channel, mCurrentTime);
    }

    mSkeleton->Update();
}

bool Animator::setSkeleton()
{
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

void Animator::calculateBoneTransform(const Animation::Channel& channel, double time)
{
    BoneTransform transform{};

    // 座標更新
    transform.Position = calculatePosition(channel.Positions, time);

    // 回転更新
    transform.Rotation = calculateRotation(channel.Rotations, time);

    // スケール更新
    transform.Scale = calculateScale(channel.Scales, time);

    auto& bone = mSkeleton->GetBone(channel.BoneIndex);

    XMMATRIX animLocal = transform.ToMatrix();
    XMMATRIX finalLocal = animLocal;

    XMStoreFloat4x4(&bone.Local, finalLocal);
}

Vector3 Animator::calculatePosition(const std::vector<Animation::KeyPosition>& keys, double time)
{
    if (keys.empty()) {
        return { 0.0f, 0.0f, 0.0f };
    }

    if (keys.size() == 1) {
        return keys[0].Position;
    }

    int index = 0;

    for (int i = 0; i < static_cast<int>(keys.size()) - 1; i++) {
        if (time < keys[i + 1].Time) {
            index = i;
            break;
        }
    }

    const auto& current = keys[index];
    const auto& next = keys[index + 1];

    float factor = static_cast<float>((time - current.Time) / (next.Time - current.Time));

    return Vector3::Lerp(current.Position, next.Position, factor);
}

Quaternion Animator::calculateRotation(const std::vector<Animation::KeyRotation>& keys, double time)
{
    if (keys.empty()) {
        return { 0.0f, 0.0f, 0.0f, 1.0f };
    }

    if (keys.size() == 1) {
        return keys[0].Rotation;
    }

    int index = 0;

    for (int i = 0; i < static_cast<int>(keys.size()) - 1; i++) {
        if (time < keys[i + 1].Time) {
            index = i;
            break;
        }
    }

    const auto& current = keys[index];
    const auto& next = keys[index + 1];

    float factor = static_cast<float>((time - current.Time) / (next.Time - current.Time));

    return Quaternion::Slerp(current.Rotation, next.Rotation, factor);
}

Vector3 Animator::calculateScale(const std::vector<Animation::KeyScale>& keys, double time)
{
    if (keys.empty()) {
        return { 1.0f, 1.0f, 1.0f };
    }

    if (keys.size() == 1) {
        return keys[0].Scale;
    }

    int index = 0;

    for (int i = 0; i < static_cast<int>(keys.size()) - 1; i++) {
        if (time < keys[i + 1].Time) {
            index = i;
            break;
        }
    }

    const auto& current = keys[index];
    const auto& next = keys[index + 1];

    float factor = static_cast<float>((time - current.Time) / (next.Time - current.Time));

    return Vector3::Lerp(current.Scale, next.Scale, factor);
}
