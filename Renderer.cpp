/*============================================================
*	@file	 : Renderer.cpp
*	@brief	 : 描画
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/21
*	@updated : 2026/06/02
*============================================================*/
#include "Main.h"
#include "Renderer.h"
#include "DeviceManager.h"
#include "BufferManager.h"
#include "ShaderContainer.h"
#include "ShaderLoader.h"
#include "SystemWindow.h"
#include <io.h>

void Renderer::Initialize()
{
	HRESULT hr = S_OK;
	
	auto& device = D3D11::DeviceManager::getInstance();

	// デバイス初期化
	device.Initialize();
	if (FAILED(hr)) { return; }

	// ビューポート設定
	// デフォルトではウィンドウ幅全体を使用
	SetViewport();

	// 定数バッファ初期化
	D3D11::BufferManager::getInstance().Initialize();

	// シェーダー読み込み
	Shader::initialize();
}

void Renderer::Begin()
{
	// ※ループ先頭で呼出
	auto& device = D3D11::DeviceManager::getInstance();

	// 画面クリア
	float clearColor[4] = { 0.2f, 0.5f, 0.1f, 1.0f };
	device.GetContext()->ClearRenderTargetView( device.GetRenderTargetView().get(), clearColor);
	device.GetContext()->ClearDepthStencilView( device.GetDepthStencilView().get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Renderer::SetViewport(float width, float height)
{
	// ビューポート設定
	D3D11_VIEWPORT viewport{};
	viewport.Width = (FLOAT)width;
	viewport.Height = (FLOAT)height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	D3D11::DeviceManager::getInstance().GetContext()->RSSetViewports(1, &viewport);
}

void Renderer::End()
{
	// ※ループ末尾で呼出
	D3D11::DeviceManager::getInstance().GetSwapChain()->Present(1, 0);
}

void Renderer::CreateVertexShader( ID3D11VertexShader** VertexShader, ID3D11InputLayout** VertexLayout, const char* FileName )
{
	FILE* file;
	long int fsize;

	file = fopen(FileName, "rb");
	assert(file);

	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);

	D3D11::DeviceManager::getInstance().
		GetDevice()->CreateVertexShader(buffer, fsize, NULL, VertexShader);

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 4 * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 4 * 6, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 4 * 10, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout);

	D3D11::DeviceManager::getInstance().
		GetDevice()->CreateInputLayout(layout,
		numElements,
		buffer,
		fsize,
		VertexLayout);

	delete[] buffer;
}

void Renderer::CreatePixelShader( ID3D11PixelShader** PixelShader, const char* FileName )
{
	FILE* file;
	long int fsize;

	file = fopen(FileName, "rb");
	assert(file);

	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);

	D3D11::DeviceManager::getInstance().
		GetDevice()->CreatePixelShader(buffer, fsize, NULL, PixelShader);

	delete[] buffer;
}