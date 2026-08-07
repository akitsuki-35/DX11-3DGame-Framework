/*============================================================
*	@file	 : AnimationManager.h
*	@brief	 : アニメーションクリップ管理
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/07
*	@updated : 2026/08/07
*============================================================*/
#pragma once

#include "Animation.h"
#include <string>
#include <memory>
#include <unordered_map>

/*============================================================
*	@class	: AnimationManager
*	@brief	: アニメーションクリップ管理
*============================================================*/
class AnimationManager final
{
/*--------------------------------------------------
	Singleton用
----------------------------------------------------*/
public:
	static AnimationManager& getInstance() {
		static AnimationManager  instance;
		return instance;
	}

private:
	AnimationManager() = default;
	AnimationManager(const AnimationManager&) = delete;

	AnimationManager& operator=(const AnimationManager&) = delete;
	AnimationManager(AnimationManager&&) = delete;

	AnimationManager& operator=(AnimationManager&&) = delete;
	~AnimationManager() {};

/*--------------------------------------------------
	メンバ変数・メンバ関数
----------------------------------------------------*/
private:
	// アニメーションコンテナ
	std::unordered_map <std::string, std::unique_ptr<Animation>> mAnimations{};

public:
	// ロード済みアニメーションを取得
	Animation* Get(const std::string& keyName) {
		auto it = mAnimations.find(keyName);

		if (it != mAnimations.end()) {
			return it->second.get();
		}

		return nullptr;
	}

	// 登録
	Animation* Register(const std::string& keyName, std::unique_ptr<Animation> animation) {
		// 登録済みならreturn
		if (mAnimations.contains(keyName)) {
			return mAnimations[keyName].get();
		}

		mAnimations.emplace(keyName, std::move(animation));

		return mAnimations[keyName].get();
	}

	// クリア
	void Clear() {
		mAnimations.clear();
	}
};