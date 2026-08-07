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
    auto itr = mBoneMap.find(name);

    if (itr == mBoneMap.end())
        return -1;

    return itr->second;
}
