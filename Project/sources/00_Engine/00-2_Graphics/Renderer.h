/*============================================================
*	@file	 : Renderer.h
*	@brief	 : 描画クラス
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/21
*	@updated : 2026/07/24
*============================================================*/
#pragma once

#include "Config.h"

/*============================================================
*	@class	: Renderer
*	@brief	: 描画クラス
*============================================================*/
class Renderer final
{
/*--------------------------------------------------
	Singleton用
----------------------------------------------------*/
public:
	static Renderer& getInstance() {
		static Renderer instance;
		return instance;
	}

private:
	Renderer() = default;
	Renderer(const Renderer&) = delete;

	Renderer& operator=(const Renderer&) = delete;
	Renderer(Renderer&&) = delete;

	Renderer& operator=(Renderer&&) = delete;
	~Renderer() {};

/*--------------------------------------------------
	メンバ変数・メンバ関数
----------------------------------------------------*/
public:
	void Initialize();
	void Finalize();
	void Begin();
	void End();
	void SetViewport(float width = Screen::WIDTH, float height = Screen::HEIGHT);

	void CreateVertexShader(ID3D11VertexShader** VertexShader, ID3D11InputLayout** VertexLayout, const char* FileName);
	void CreatePixelShader(ID3D11PixelShader** PixelShader, const char* FileName);
};