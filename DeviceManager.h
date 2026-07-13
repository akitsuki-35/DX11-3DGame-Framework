/*============================================================
*	@file	 : DeviceManager.h
*	@brief	 : DirectX11デバイス管理
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/13
*	@updated : 2026/07/13
*============================================================*/
#pragma once

#include <d3d11.h>
#include <wrl/client.h>

namespace D3D11 {
/*============================================================
*	@class	: DeviceManager
*	@brief	: DirectX11デバイス管理
*============================================================*/
	class DeviceManager final
	{
	
	/*--------------------------------------------------
		Singleton用
	----------------------------------------------------*/
	public:
		static DeviceManager& getInstance() {
			static DeviceManager instance;
			return instance;
		}

	private:
		DeviceManager() = default;
		DeviceManager(const DeviceManager&) = delete;

		DeviceManager& operator=(const DeviceManager&) = delete;
		DeviceManager(DeviceManager&&) = delete;

		DeviceManager& operator=(DeviceManager&&) = delete;
		~DeviceManager() {};

	/*--------------------------------------------------
		メンバ変数・メンバ関数
	----------------------------------------------------*/
		// 実行フューチャーレベル
		D3D_FEATURE_LEVEL mFutureLevel{};

		// DX11デバイス
		Microsoft::WRL::ComPtr<ID3D11Device> _mDevice{};
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> _mContext{};
		Microsoft::WRL::ComPtr<IDXGISwapChain> _mSwapChain{};

		// レンダーターゲット
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> _mRenderTargetView{};
		
		// 深度バッファ
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> _mDepthStencilView{};

		// 深度ステート
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState>  _mDepthEnable{};
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState>  _mDepthDisable{};

		// ブレンドステート
		Microsoft::WRL::ComPtr<ID3D11BlendState>  _mBlendAlpha{};
		Microsoft::WRL::ComPtr<ID3D11BlendState>  _mBlendAdd{};
		Microsoft::WRL::ComPtr<ID3D11BlendState>  _mBlendATC{};

		// ラスタライザステート
		Microsoft::WRL::ComPtr<ID3D11RasterizerState> _mRasterSolid{};
		Microsoft::WRL::ComPtr<ID3D11RasterizerState> _mRasterWireframe{};

		// サンプラーステート
		Microsoft::WRL::ComPtr<ID3D11SamplerState> _mSamplerAnisotropic{};
		Microsoft::WRL::ComPtr<ID3D11SamplerState> _mSamplerLinear{};
		Microsoft::WRL::ComPtr<ID3D11SamplerState> _mSamplerPoint{};

	public:
		bool Initialize(HWND hWnd, int width, int height);

	private:
		bool GenerateDeviceAndSwapChain();
		bool GenerateDepthStencilView();
		bool GenerateDepthStencilState();
		bool GenerateBlendState();
		bool GenerateRasterizerState();
		bool GenerateSamplerState();

		void RenderStateRegister();
	};
}