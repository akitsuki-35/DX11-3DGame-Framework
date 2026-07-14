/*============================================================
*	@file	 : DeviceManager.h
*	@brief	 : DirectX11デバイス管理
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/13
*	@updated : 2026/07/14
*============================================================*/
#pragma once

#include <d3d11.h>
#include <winrt/base.h>

namespace D3D11 {
/*============================================================
*	@class	: DeviceManager
*	@brief	: DirectX11デバイス管理
*============================================================*/
	class DeviceManager final
	{
		template <typename T>
		using ComPtr = winrt::com_ptr<T>;

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
	private:
		// 実行フューチャーレベル
		D3D_FEATURE_LEVEL mFutureLevel{};

		// DX11デバイス
		winrt::com_ptr<ID3D11Device> _mDevice{};
		winrt::com_ptr<ID3D11DeviceContext> _mContext{};
		winrt::com_ptr<IDXGISwapChain> _mSwapChain{};

		// レンダーターゲット
		winrt::com_ptr<ID3D11RenderTargetView> _mRenderTargetView{};
		
		// 深度バッファ
		winrt::com_ptr<ID3D11DepthStencilView> _mDepthStencilView{};

		// 深度ステート
		winrt::com_ptr<ID3D11DepthStencilState>  _mDepthEnable{};
		winrt::com_ptr<ID3D11DepthStencilState>  _mDepthDisable{};

		// ブレンドステート
		winrt::com_ptr<ID3D11BlendState>  _mBlendAlpha{};
		winrt::com_ptr<ID3D11BlendState>  _mBlendAdd{};
		winrt::com_ptr<ID3D11BlendState>  _mBlendATC{};

		// ラスタライザステート
		winrt::com_ptr<ID3D11RasterizerState> _mRasterSolid{};
		winrt::com_ptr<ID3D11RasterizerState> _mRasterWireframe{};

		// サンプラーステート
		winrt::com_ptr<ID3D11SamplerState> _mSamplerAnisotropic{};
		winrt::com_ptr<ID3D11SamplerState> _mSamplerLinear{};
		winrt::com_ptr<ID3D11SamplerState> _mSamplerPoint{};

	public:
		bool Initialize(HWND hWnd, int width, int height);

	private:
		// デバイス・ステート生成
		bool GenerateDeviceAndSwapChain();
		bool GenerateDepthStencilView();
		bool GenerateDepthStencilState();
		bool GenerateBlendState();
		bool GenerateRasterizerState();
		bool GenerateSamplerState();
		void RenderStateRegister();

	public:
		// ゲッター
		winrt::com_ptr<ID3D11Device> GetDevice() const { return _mDevice; }
		winrt::com_ptr<ID3D11DeviceContext> GetContext() const { return _mContext; }
	};
}