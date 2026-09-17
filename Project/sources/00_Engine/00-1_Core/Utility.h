/*============================================================
*	@file	 : Utility.h
*	@brief	 : 汎用ユーティリティ
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/30
*	@updated : 2026/09/16
*============================================================*/
#pragma once

#include <string>
#include <vector>
#include <filesystem>

/*------------------------------------------------------------
	前方宣言
------------------------------------------------------------*/
enum easing_functions : int;

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

		// ディレクトリのパス取得
		std::filesystem::path getDirectoryPath(const char* filePath);

		// ファイル拡張子取得
		std::string getFileExtension(const std::string& filePath);
	}

/*--------------------------------------------------
	文字列関連
----------------------------------------------------*/
	namespace String 
	{
		// std::string→std::wstringに変換
		std::wstring toWideString(const std::string& string);
	}

/*--------------------------------------------------
	イージング関連
----------------------------------------------------*/
	namespace Easing
	{
		// ratio算出
		double CalculateRatio(double current, double duration);

		// ease算出
		float CalculateEase(double current, double duration, easing_functions easeType);
	}
}