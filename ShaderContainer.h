/*============================================================
*	@file	 : ShaderContainer.h
*	@brief	 : シェーダーコンテナ
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/14
*	@updated : 2026/07/14
*============================================================*/
#pragma once

#include "ShaderLoader.h"

namespace ShaderSet {
	inline void initialize() {
			ShaderLoader::getInstance().Register("Unlit", 
				"Resources\\Shaders\\unlitTextureVS.cso", "Resources\\Shaders\\unlitTexturePS.cso");
	}
}