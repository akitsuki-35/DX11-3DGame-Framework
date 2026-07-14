/*============================================================
*	@file	 : BufferManager.cpp
*	@brief	 : 定数バッファ管理
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/14
*	@updated : 2026/07/14
*============================================================*/
#include "BufferManager.h"
#include "DeviceManager.h"
#include "Config.h"

using namespace DirectX;

void D3D11::BufferManager::Initialize()
{
	// 定数バッファ初期化
	_mWorld = GenerateBuffer(sizeof(DirectX::XMMATRIX));
	_mView = GenerateBuffer(sizeof(DirectX::XMMATRIX));
	_mProjection = GenerateBuffer(sizeof(DirectX::XMMATRIX));
	_mMaterial = GenerateBuffer(sizeof(Element::MATERIAL));
	_mLight = GenerateBuffer(sizeof(Element::LIGHT));

	// ライト初期化
	Element::LIGHT light{};
	light.Enable = true;
	light.Direction = XMFLOAT4(0.0f, -1.0f, 0.0f, 0.0f);
	light.Ambient = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
	light.Diffuse = XMFLOAT4(1.5f, 1.5f, 1.5f, 1.0f);
	D3D11::BufferManager::getInstance().SetLight(light);

	// マテリアル初期化
	Element::MATERIAL material{};
	material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	material.Ambient = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	D3D11::BufferManager::getInstance().SetMaterial(material);
}

winrt::com_ptr<ID3D11Buffer> D3D11::BufferManager::GenerateBuffer(UINT size)
{
	// 定数バッファ生成
	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = size;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = sizeof(float);

	ComPtr<ID3D11Buffer> buffer;
	D3D11::DeviceManager::getInstance().
		GetDevice()->CreateBuffer(&bufferDesc, nullptr, buffer.put());

	return buffer;
}

void D3D11::BufferManager::Set2DMatrix()
{
	// 2D用マトリクス設定
	SetWorldMatrix(XMMatrixIdentity());
	SetViewMatrix(XMMatrixIdentity());

	XMMATRIX projection;
	projection = XMMatrixOrthographicOffCenterLH(0.0f, Screen::WIDTH, Screen::HEIGHT, 0.0f, 0.0f, 1.0f);
	SetProjectionMatrix(projection);
}

void D3D11::BufferManager::SetWorldMatrix(DirectX::XMMATRIX worldMatrix)
{
	// ワールド行列設定
	XMFLOAT4X4 worldf;
	XMStoreFloat4x4(&worldf, XMMatrixTranspose(worldMatrix));
	DeviceManager::getInstance().
		GetContext()->UpdateSubresource(_mWorld.get(), 0, nullptr, &worldf, 0, 0);

	ID3D11Buffer* buf = _mWorld.get();
	DeviceManager::getInstance().
		GetContext()->VSSetConstantBuffers(0, 1, &buf);
}

void D3D11::BufferManager::SetViewMatrix(DirectX::XMMATRIX viewMatrix)
{
	// ビュー行列設定
	XMFLOAT4X4 viewf;
	XMStoreFloat4x4(&viewf, XMMatrixTranspose(viewMatrix));
	DeviceManager::getInstance().
		GetContext()->UpdateSubresource(_mView.get(), 0, nullptr, &viewf, 0, 0);

	ID3D11Buffer* buf = _mView.get();
	DeviceManager::getInstance().
		GetContext()->VSSetConstantBuffers(1, 1, &buf);
}

void D3D11::BufferManager::SetProjectionMatrix(DirectX::XMMATRIX projectionMatrix)
{
	// プロジェクション行列設定
	XMFLOAT4X4 projectionf;
	XMStoreFloat4x4(&projectionf, XMMatrixTranspose(projectionMatrix));
	DeviceManager::getInstance().
		GetContext()->UpdateSubresource(_mProjection.get(), 0, nullptr, &projectionf, 0, 0);

	ID3D11Buffer* buf = _mProjection.get();
	DeviceManager::getInstance().
		GetContext()->VSSetConstantBuffers(2, 1, &buf);
}

void D3D11::BufferManager::SetMaterial(Element::MATERIAL material)
{
	// マテリアル設定
	DeviceManager::getInstance().
		GetContext()->UpdateSubresource(_mMaterial.get(), 0, nullptr, &material, 0, 0);

	ID3D11Buffer* buf = _mMaterial.get();
	DeviceManager::getInstance().
		GetContext()->VSSetConstantBuffers(3, 1, &buf);
	DeviceManager::getInstance().
		GetContext()->PSSetConstantBuffers(3, 1, &buf);
}

void D3D11::BufferManager::SetLight(Element::LIGHT light)
{
	// ライト設定
	DeviceManager::getInstance().
		GetContext()->UpdateSubresource(_mLight.get(), 0, nullptr, &light, 0, 0);

	ID3D11Buffer* buf = _mLight.get();
	DeviceManager::getInstance().
		GetContext()->VSSetConstantBuffers(4, 1, &buf);
	DeviceManager::getInstance().
		GetContext()->PSSetConstantBuffers(4, 1, &buf);
}