/*============================================================
*	@file	 : BufferManager.h
*	@brief	 : 定数バッファ管理
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/14
*	@updated : 2026/07/14
*============================================================*/
#pragma once

#include "DeviceManager.h"
#include "GraphicsTypes.h"

#include <winrt/base.h>

namespace D3D11 {
	/*============================================================
	*	@class	: BufferManager
	*	@brief	: 定数バッファ管理
	*============================================================*/
	class BufferManager final
	{
		template <typename T>
		using ComPtr = winrt::com_ptr<T>;

		/*--------------------------------------------------
			Singleton用
		----------------------------------------------------*/
	public:
		static BufferManager& getInstance() {
			static BufferManager instance;
			return instance;
		}

	private:
		BufferManager() = default;
		BufferManager(const BufferManager&) = delete;

		BufferManager& operator=(const BufferManager&) = delete;
		BufferManager(BufferManager&&) = delete;

		BufferManager& operator=(BufferManager&&) = delete;
		~BufferManager() {};

		/*--------------------------------------------------
			メンバ変数・メンバ関数
		----------------------------------------------------*/
	private:
		// 定数バッファ
		winrt::com_ptr<ID3D11Buffer> _mWorld;
		winrt::com_ptr<ID3D11Buffer> _mView;
		winrt::com_ptr<ID3D11Buffer> _mProjection;
		winrt::com_ptr<ID3D11Buffer> _mMaterial;
		winrt::com_ptr<ID3D11Buffer> _mLight;

	public:
		void Initialize();

	private:
		// 定数バッファ生成
		winrt::com_ptr<ID3D11Buffer> generateBuffer(UINT size);

	public:
		// セッター
		void Set2DMatrix();
		void SetWorldMatrix(DirectX::XMMATRIX worldMatrix);
		void SetViewMatrix(DirectX::XMMATRIX viewMatrix);
		void SetProjectionMatrix(DirectX::XMMATRIX projectionMatrix);
		void SetMaterial(Element::MATERIAL material);
		void SetLight(Element::LIGHT light);

		// ゲッター
		winrt::com_ptr<ID3D11Buffer> GetWorldBuffer() const { return _mWorld; }
		winrt::com_ptr<ID3D11Buffer> GetViewBuffer() const { return _mView; }
		winrt::com_ptr<ID3D11Buffer> GetProjectionBuffer() const { return _mProjection; }
		winrt::com_ptr<ID3D11Buffer> GetMaterialBuffer() const { return _mMaterial; }
		winrt::com_ptr<ID3D11Buffer> GetLightBuffer() const { return _mLight; }
	};
}