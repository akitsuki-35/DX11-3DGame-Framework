#include "Utility.h"

std::vector<char> Utility::File::load(const char* filePath)
{
	// ファイルロード

	std::ifstream file(filePath, std::ios::binary);

	assert(file.is_open());

	// ファイルサイズ取得
	file.seekg(0, std::ios::end);
	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);

	std::vector<char> buffer(static_cast<size_t>(size));

	file.read(buffer.data(), size);

	return buffer;
}

std::string Utility::File::normalizePath(const char* filePath)
{
	// ファイルパス正規化

	char fullPath[MAX_PATH];

	// 絶対パス変換
	if (!GetFullPathNameA(filePath, MAX_PATH, fullPath, nullptr)) {
		return std::string(filePath);
	}

	char canonical[MAX_PATH];

	// 正規化
	if (PathCanonicalizeA(canonical, fullPath)) {
		return std::string(canonical);
	}

	// 正規化失敗時は絶対パスを返す
	return std::string(fullPath);
}

std::wstring Utility::String::toWideString(const std::string& string)
{
	// std::string→std::wstringに変換

	if (string.empty())
	{
		return{};
	}

	// 終端文字を含む文字列を取得
	const int size = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS,
		string.c_str(), -1, nullptr, 0);

	assert(size > 0);

	std::wstring wide(size - 1, L'\0');

	MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS,
		string.c_str(), -1, wide.data(), size);

	return wide;
}
