/*============================================================
*	@file	 : direct3d.cpp
*	@brief	 : DirectX初期化
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/12
*	@updated : 2026/06/02
*============================================================*/
#include "direct3d.h"
#include "debug_ostream.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

/*------------------------------------------------------------
	グローバル変数定義
------------------------------------------------------------*/
//各種インターフェース
static ID3D11Device* g_pDevice = nullptr;
static ID3D11DeviceContext* g_pDeviceContext = nullptr;
static IDXGISwapChain* g_pSwapChain = nullptr;

static ID3D11BlendState* g_BlendStateMultiply = nullptr;
static ID3D11BlendState* g_BlendStateAdd = nullptr;

static ID3D11DepthStencilState* g_DepthStencilStateDepthDisable = nullptr;

//バックバッファ関連
static ID3D11RenderTargetView* g_pRenderTargetView = nullptr;
static ID3D11Texture2D* g_pDepthStencilBuffer = nullptr;
static ID3D11DepthStencilView* g_pDepthStencilView = nullptr;
static D3D11_TEXTURE2D_DESC g_BackBufferDesc{};
static D3D11_VIEWPORT g_Viewport{};

/*------------------------------------------------------------
	ローカル関数 プロトタイプ宣言
------------------------------------------------------------*/
bool ConfigureBackBuffer();
void ReleaseBackBuffer();

bool Direct3DInitialize(HWND hWnd)
{
	//デバイス、スワップチェーン、コンテキスト生成
	DXGI_SWAP_CHAIN_DESC swapChainDesc{};
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.BufferCount = 2;

	//ウィンドウサイズに合わせて自動的に設定される
		//swap_chain_desc.BufferDesc.Width = 0;
		//swap_chain_desc.BufferDesc.Height = 0;

	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
	//swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_SEQUENTIAL;
	swapChainDesc.OutputWindow = hWnd;

	UINT deviceFlags = 0;

#if defined(DEBUG) || defined (_DEBUG)
	deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL levels[] = {
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0
	};

	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		deviceFlags,
		levels,
		ARRAYSIZE(levels),
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&g_pSwapChain,
		&g_pDevice,
		&featureLevel,
		&g_pDeviceContext
	);

	if (FAILED(hr))
	{
		MessageBox(hWnd, "Direct3Dの初期化に失敗しました", "エラー", MB_OK);
		return false;
	}

	if (!ConfigureBackBuffer())
	{
		MessageBox(hWnd, "バックバッファの設定に失敗しました", "エラー", MB_OK);
		return false;
	}

	//深度ステンシルステート設定
	D3D11_DEPTH_STENCIL_DESC dsd = {};
	dsd.DepthFunc = D3D11_COMPARISON_LESS;
	dsd.StencilEnable = FALSE;
	dsd.DepthEnable = FALSE; //無効化
	dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;

	g_pDevice->CreateDepthStencilState(&dsd, &g_DepthStencilStateDepthDisable);

	g_pDeviceContext->OMSetDepthStencilState(g_DepthStencilStateDepthDisable, NULL);

	return true;
}

void Direct3DFinalize()
{
	ReleaseBackBuffer();

	SAFE_RELEASE(g_pSwapChain);
	SAFE_RELEASE(g_pDeviceContext);
	SAFE_RELEASE(g_pDevice);
}

void Direct3DClear()
{
	float clearColor[4] = { 0.0f,0.0f,0.3f,1.0f };

	g_pDeviceContext->ClearRenderTargetView(g_pRenderTargetView, clearColor);
	g_pDeviceContext->ClearDepthStencilView(g_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	//レンダーターゲットビューとデプスステンシルビューの設定
	g_pDeviceContext->OMSetRenderTargets(1, &g_pRenderTargetView, g_pDepthStencilView);
}

void Direct3DPresent()
{
	//スワップチェーンの表示
	g_pSwapChain->Present(1, 0);
}

unsigned int Direct3DGetBackBufferWidth()
{
	return g_BackBufferDesc.Width;
}

unsigned int Direct3DGetBackBufferHeight()
{
	return g_BackBufferDesc.Height;
}

ID3D11Device* Direct3DGetDevice()
{
	return g_pDevice;
}

ID3D11DeviceContext* Direct3DGetDeviceContext()
{
	return g_pDeviceContext;
}

IDXGISwapChain* Direct3DGetSwapChain()
{
	return g_pSwapChain;
}

void Direct3DSetAlphaBlend(AlphaBlendMode blend)
{
	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	ID3D11BlendState* arg{};

	switch (blend)
	{
	case BLEND_MULTIPLY:
		arg = g_BlendStateMultiply; 
		break;
	
	case BLEND_ADD:
		arg = g_BlendStateAdd;
		break;
	}

	g_pDeviceContext->OMSetBlendState(arg, blendFactor, 0xffffffff);
}

bool ConfigureBackBuffer()
{
	HRESULT hr;

	ID3D11Texture2D* backBufferPointer = nullptr;

	// バックバッファの取得
	hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBufferPointer);

	if (FAILED(hr)) {
		dOst::dout << "バックバッファの取得に失敗しました" << std::endl;
		return false;
	}

	// バックバッファのレンダーターゲットビューの生成
	hr = g_pDevice->CreateRenderTargetView(backBufferPointer, nullptr, &g_pRenderTargetView);

	if (FAILED(hr)) {
		backBufferPointer->Release();
		dOst::dout << "バックバッファのレンダーターゲットビューの生成に失敗しました" << std::endl;
		return false;
	}

	// バックバッファの状態（情報）を取得
	backBufferPointer->GetDesc(&g_BackBufferDesc);

	backBufferPointer->Release(); // バックバッファのポインタは不要なので解放

	// デプスステンシルバッファの生成
	D3D11_TEXTURE2D_DESC depthStencilDesc{};
	depthStencilDesc.Width = g_BackBufferDesc.Width;
	depthStencilDesc.Height = g_BackBufferDesc.Height;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;
	hr = g_pDevice->CreateTexture2D(&depthStencilDesc, nullptr, &g_pDepthStencilBuffer);

	if (FAILED(hr)) {
		dOst::dout << "デプスステンシルバッファの生成に失敗しました" << std::endl;
		return false;
	}

	// デプスステンシルビューの生成
	D3D11_DEPTH_STENCIL_VIEW_DESC depth_stencil_view_desc{};
	depth_stencil_view_desc.Format = depthStencilDesc.Format;
	depth_stencil_view_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depth_stencil_view_desc.Texture2D.MipSlice = 0;
	depth_stencil_view_desc.Flags = 0;
	hr = g_pDevice->CreateDepthStencilView(g_pDepthStencilBuffer, &depth_stencil_view_desc, &g_pDepthStencilView);

	if (FAILED(hr)) {
		dOst::dout << "デプスステンシルビューの生成に失敗しました" << std::endl;
		return false;
	}

	//ビューポートの設定
	g_Viewport.TopLeftX = 0.0f;
	g_Viewport.TopLeftY = 0.0f;
	g_Viewport.Width = (FLOAT)g_BackBufferDesc.Width;
	g_Viewport.Height = (FLOAT)g_BackBufferDesc.Height;
	g_Viewport.MinDepth = 0.0f;
	g_Viewport.MaxDepth = 1.0f;

	g_pDeviceContext->RSSetViewports(1, &g_Viewport);

	// ブレンドステート設定
	D3D11_BLEND_DESC bd = {};
	bd.AlphaToCoverageEnable = FALSE;
	bd.IndependentBlendEnable = FALSE;
	bd.RenderTarget[0].BlendEnable = TRUE;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	g_pDevice->CreateBlendState(&bd, &g_BlendStateMultiply);

	// 加算合成
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	g_pDevice->CreateBlendState(&bd, &g_BlendStateAdd);

	Direct3DSetAlphaBlend(BLEND_MULTIPLY);

	return true;
}

void ReleaseBackBuffer()
{
	SAFE_RELEASE(g_pDepthStencilView);
	SAFE_RELEASE(g_pDepthStencilBuffer);
	SAFE_RELEASE(g_pRenderTargetView);
	SAFE_RELEASE(g_DepthStencilStateDepthDisable);
	SAFE_RELEASE(g_BlendStateAdd);
	SAFE_RELEASE(g_BlendStateMultiply);
}
