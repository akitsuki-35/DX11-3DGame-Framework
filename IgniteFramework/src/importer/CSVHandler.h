/*============================================================
*	@file	 : CSVHandler.h
*	@brief	 : CSVファイル入出力
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/21
*	@updated : 2026/09/16
*============================================================*/
#pragma once

#include <string>
#include <vector>

/*============================================================
*	@class	: CSVHandler
*	@brief	: CSVファイル入出力
*============================================================*/
class CSVHandler final
{
private:
	CSVHandler() = delete;

public:
	// データ行
	using Row = std::vector<std::string>;
	
	// 行内のデータ
	using Data = std::vector<Row>;

	// ロード
	static bool Load(const char* filePath, Data& data);

	// 出力
	static bool Export(const char* filePath, const Data& data);

	// データからの数値取得
	static std::string GetString(const Row& row, size_t index, const std::string& defaultValue = "");
	static int GetInt(const Row& row, size_t index, int defaultValue = 0);
	static float GetFloat(const Row& row, size_t index, float defaultValue = 0.0f);
	static double GetDouble(const Row& row, size_t index, double defaultValue = 0.0);

private:
	// 空白のトリム
	static std::string trim(const std::string& str);
};