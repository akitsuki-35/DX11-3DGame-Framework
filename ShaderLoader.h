/*============================================================
*	@file	 : ShaderLoader.h
*	@brief	 : シェーダー管理
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/14
*	@updated : 2026/07/14
*============================================================*/
#pragma once

#include <d3d11.h>
#include <string>
#include <memory>
#include <unordered_map>
#include <wrl/client.h>

/*============================================================
*	@class	: Shader
*	@brief	: シェーダーのセット記録
*============================================================*/
class Shader
{
public:
	std::string KeyName;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> VertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> PixelShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> Layout;
};

/*============================================================
*	@class	: ShaderLoader
*	@brief	: シェーダーのロード・管理
*============================================================*/
class ShaderLoader final
{
/*--------------------------------------------------
	Singleton用
----------------------------------------------------*/
public:
	static ShaderLoader& getInstance() {
		static ShaderLoader  instance;
		return instance;
	}

private:
	ShaderLoader () = default;
	ShaderLoader (const ShaderLoader&) = delete;

	ShaderLoader & operator=(const ShaderLoader&) = delete;
	ShaderLoader (ShaderLoader&&) = delete;

	ShaderLoader& operator=(ShaderLoader&&) = delete;
	~ShaderLoader() {};

/*--------------------------------------------------
	メンバ変数・メンバ関数
----------------------------------------------------*/
private:
	// シェーダーコンテナ
	std::unordered_map <std::string, std::unique_ptr<Shader>> mShaders;

	// キャッシュ
	std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11VertexShader>> mVSCache;
	std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11PixelShader>> mPSCache;
	std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11InputLayout>>  mLayoutCache;

public:
	// 登録
	Shader* Register(const std::string& keyName,
		const char* vsPath, const char* psPath);

	// 登録済みシェーダーの取得
	Shader* Get(const std::string& keyName);

private:
	std::vector<char> road(const char* filePath);
	std::string normalizePath(const char* filePath);
};