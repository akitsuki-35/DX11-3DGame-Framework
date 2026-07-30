/*============================================================
*	@file	 : ShaderManager.cpp
*	@brief	 : シェーダー管理
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/14
*	@updated : 2026/07/14
*============================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include "ShaderManager.h"
#include "Shader.h"
#include "DeviceManager.h"
#include <cassert>
#include <shlwapi.h>
#include <io.h>

using namespace Microsoft::WRL;

Shader* ShaderManager::Get(const std::string& keyName)
{
	if (mShaders.contains(keyName))
		return mShaders[keyName].get();

	return nullptr;
}

Shader* ShaderManager::Register(const std::string& keyName, const char* vsPath, const char* psPath)
{
	// 登録済みならreturn
	if (mShaders.contains(keyName)) {
		return mShaders[keyName].get();
	}

	// キャッシュ取得用にパスを正規化
	std::string vsKey = normalizePath(vsPath);
	std::string psKey = normalizePath(psPath);

	auto shader = std::make_unique<Shader>();
	
	// 頂点シェーダー作成
	if (mVSCache.contains(vsKey)) {
		shader->_mVertexShader = mVSCache[vsKey];
		shader->_mLayout = mLayoutCache[vsKey];
	}
	else {
		auto vsBuffer = road(vsPath);

		D3D11::DeviceManager::getInstance().
			GetDevice()->CreateVertexShader(vsBuffer.data(), vsBuffer.size(), nullptr, &shader->_mVertexShader);

		// 頂点レイアウト作成
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 4 * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 4 * 6, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 4 * 10, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		UINT numElements = ARRAYSIZE(layout);

		D3D11::DeviceManager::getInstance().
			GetDevice()->CreateInputLayout(layout, numElements,
				vsBuffer.data(), vsBuffer.size(), &shader->_mLayout);

		// キャッシュ登録
		mVSCache[vsKey] = shader->_mVertexShader;
		mLayoutCache[vsKey] = shader->_mLayout;

		// キャッシュからコンテナに登録
		shader->_mVertexShader = mVSCache[vsKey];
		shader->_mLayout = mLayoutCache[vsKey];
	}

	// ピクセルシェーダー作成
	if (mPSCache.contains(psKey)) {
		shader->_mPixelShader = mShaders[psKey]->_mPixelShader;
	}
	else {
		auto psBuffer = road(psPath);

		D3D11::DeviceManager::getInstance().
			GetDevice()->CreatePixelShader(psBuffer.data(), psBuffer.size(), nullptr, &shader->_mPixelShader);
	
		// キャッシュ登録
		mPSCache[psKey] = shader->_mPixelShader;

		// キャッシュからコンテナに登録
		shader->_mPixelShader = mPSCache[psKey];
	}

	// コンテナに登録
	mShaders[keyName] = std::move(shader);

	return mShaders[keyName].get();
}

std::vector<char> ShaderManager::road(const char* filePath)
{
	FILE* file;

	file = fopen(filePath, "rb");
	assert(file);

	fseek(file, 0, SEEK_END);
	long fSize = ftell(file);
	fseek(file, 0, SEEK_SET);

	std::vector<char> buffer(fSize);
	fread(buffer.data(), 1, fSize, file);
	fclose(file);

	return buffer;
}

std::string ShaderManager::normalizePath(const char* filePath)
{
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