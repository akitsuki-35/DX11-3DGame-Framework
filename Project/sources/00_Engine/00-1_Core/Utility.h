/*============================================================
*	@file	 : Utility.h
*	@brief	 : 汎用ユーティリティ
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/30
*	@updated : 2026/07/30
*============================================================*/
#pragma once

#include <string>
#include <vector>
#include <cassert>
#include <shlwapi.h>
#include <iostream>
#include <fstream>
#pragma comment(lib, "Shlwapi.lib")

/*============================================================
*	@namespace	: Utility
*	@brief		: 汎用ユーティリティ関数群
*============================================================*/
namespace Utility
{
/*--------------------------------------------------
	ファイル関連
----------------------------------------------------*/
	namespace File {
		// ファイルロード
		std::vector<char> load(const char* filePath);

		// ファイルパス正規化
		std::string normalizePath(const char* filePath);
	}

/*--------------------------------------------------
	文字列関連
----------------------------------------------------*/
	namespace String 
	{
		// std::string→std::wstringに変換
		std::wstring toWideString(const std::string& string);
	}
}