/*============================================================
*	@file	 : ShaderManager.h
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

// シェーダー構造体
struct SHADER
{
	std::string KeyName;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> Layout;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> VertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> PixelShader;
};

class ShaderManager final
{
/*--------------------------------------------------
	Singleton用
----------------------------------------------------*/
public:
	static ShaderManager& getInstance() {
		static ShaderManager instance;
		return instance;
	}

private:
	ShaderManager() = default;
	ShaderManager(const ShaderManager&) = delete;

	ShaderManager& operator=(const ShaderManager&) = delete;
	ShaderManager(ShaderManager&&) = delete;

	ShaderManager& operator=(ShaderManager&&) = delete;
	~ShaderManager() {};

/*--------------------------------------------------
	メンバ変数・メンバ関数
----------------------------------------------------*/
private:
	// シェーダーコンテナ
	static std::unordered_map <std::string, std::unique_ptr<SHADER>	> mShaders;

public:
	void Initialize();

	// ロード済みシェーダーの取得
	SHADER* Get(const std::string& keyName);

private:
	// ロード
	SHADER* Load(const std::string& keyName,
		const std::string& pathVS, const std::string& pathPS);
};