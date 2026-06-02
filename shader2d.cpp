/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	2D用シェーダー[shader.cpp]
*
* 　Author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　Date	: 2026/04/01
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#include "shader2d.h"
#include "direct3d.h"
#include "debug_ostream.h"
#include <fstream>
#include <DirectXMath.h>
using namespace DirectX;

static ID3D11VertexShader* g_pVertexShader{ nullptr };
static ID3D11InputLayout* g_pInputLayout{ nullptr };

static ID3D11Buffer* g_pVSConstantBufferproj{ nullptr };
static ID3D11Buffer* g_pVSConstantBufferworld{ nullptr };

static ID3D11PixelShader* g_pPixelShader{ nullptr }
;
static ID3D11SamplerState* g_pSamplerStateLinear{ nullptr };
static ID3D11SamplerState* g_pSamplerStatePoint{ nullptr };

static ID3D11Buffer* g_pPSConstantBuffer{ nullptr };

bool Shader2DInitialize()
{
	HRESULT hr; // 戻り値格納用

	// 事前コンパイル済み頂点シェーダーの読み込み
	std::ifstream ifsVs("Resources/Shaders/VertexShader2d.cso", std::ios::binary);

	if (!ifsVs) {
		MessageBox(nullptr, "頂点シェーダーの読み込みに失敗しました\n\nVertexShader2d.cso", "エラー", MB_OK);
		return false;
	}

	// ファイルサイズを取得
	ifsVs.seekg(0, std::ios::end); // ファイルポインタを末尾に移動
	std::streamsize fileSize = ifsVs.tellg(); // ファイルポインタの位置を取得（つまりファイルサイズ）
	ifsVs.seekg(0, std::ios::beg); // ファイルポインタを先頭に戻す

	// バイナリデータを格納するためのバッファを確保
	unsigned char* vsBinaryPointer = new unsigned char[fileSize];
	
	ifsVs.read((char*)vsBinaryPointer, fileSize); // バイナリデータを読み込む
	ifsVs.close(); // ファイルを閉じる

	// 頂点シェーダーの作成
	hr = Direct3DGetDevice()->CreateVertexShader(vsBinaryPointer, fileSize, nullptr, &g_pVertexShader);

	if (FAILED(hr)) {
		dOst::dout << "Shader2d_Initialize() : 頂点シェーダーの作成に失敗しました" << std::endl;
		delete[] vsBinaryPointer; // メモリリークしないようにバイナリデータのバッファを解放
		return false;
	}

	// 頂点レイアウトの定義
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	UINT num_elements = ARRAYSIZE(layout); // 配列の要素数を取得

	// 頂点レイアウトの作成
	hr = Direct3DGetDevice()->CreateInputLayout(layout, num_elements, vsBinaryPointer, fileSize, &g_pInputLayout);

	delete[] vsBinaryPointer; // バイナリデータのバッファを解放

	if (FAILED(hr)) {
		dOst::dout << "Shader2d_Initialize() : 頂点レイアウトの作成に失敗しました" << std::endl;
		return false;
	}


	// 頂点シェーダー用定数バッファの作成
	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = sizeof(XMFLOAT4X4); // バッファのサイズ
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; // バインドフラグ
	Direct3DGetDevice()->CreateBuffer(&bufferDesc, nullptr, &g_pVSConstantBufferproj);

	bufferDesc.ByteWidth = sizeof(XMFLOAT4X4); // バッファのサイズ
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; // バインドフラグ
	Direct3DGetDevice()->CreateBuffer(&bufferDesc, nullptr, &g_pVSConstantBufferworld);


	// 事前コンパイル済みピクセルシェーダーの読み込み
	std::ifstream ifsPs("Resources/Shaders/PixelShader2d.cso", std::ios::binary);
	if (!ifsPs) {
		MessageBox(nullptr, "ピクセルシェーダーの読み込みに失敗しました\n\nPixelShader2d.cso", "エラー", MB_OK);
		return false;
	}

	ifsPs.seekg(0, std::ios::end);
	fileSize = ifsPs.tellg();
	ifsPs.seekg(0, std::ios::beg);

	unsigned char* psBinaryPointer = new unsigned char[fileSize];
	ifsPs.read((char*)psBinaryPointer, fileSize);
	ifsPs.close();

	// ピクセルシェーダーの作成
	hr = Direct3DGetDevice()->CreatePixelShader(psBinaryPointer, fileSize, nullptr, &g_pPixelShader);

	delete[] psBinaryPointer; // バイナリデータのバッファを解放

	if (FAILED(hr)) {
		dOst::dout << "Shader2d_Initialize() : ピクセルシェーダーの作成に失敗しました" << std::endl;
		return false;
	}

	//// ピクセルシェーダー用定数バッファの作成
	bufferDesc.ByteWidth = sizeof(XMFLOAT4); // バッファのサイズ
	//buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; // バインドフラグ

	Direct3DGetDevice()->CreateBuffer(&bufferDesc, nullptr, &g_pPSConstantBuffer);

	// 通常スプライト用サンプラーステート設定
	D3D11_SAMPLER_DESC samplerDesc{};
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.MipLODBias = 0;
	samplerDesc.MaxAnisotropy = 16;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	Direct3DGetDevice()->CreateSamplerState(&samplerDesc, &g_pSamplerStateLinear);

	// UVスプライト用サンプラーステート設定
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.MipLODBias = 0;
	samplerDesc.MaxAnisotropy = 16;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	Direct3DGetDevice()->CreateSamplerState(&samplerDesc, &g_pSamplerStatePoint);

	return true;
}

void Shader2DFinalize()
{
	SAFE_RELEASE(g_pPSConstantBuffer);
	SAFE_RELEASE(g_pSamplerStatePoint);
	SAFE_RELEASE(g_pSamplerStateLinear);
	SAFE_RELEASE(g_pPixelShader);
	SAFE_RELEASE(g_pVSConstantBufferworld);
	SAFE_RELEASE(g_pVSConstantBufferproj);
	SAFE_RELEASE(g_pInputLayout);
	SAFE_RELEASE(g_pVertexShader);
}

void Shader2DSetProjectionMatrix(const DirectX::XMMATRIX& matrix)
{
	// 定数バッファ格納用行列の構造体を定義
	XMFLOAT4X4 transpose;

	// 行列を転置して定数バッファ格納用行列に変換
	XMStoreFloat4x4(&transpose, XMMatrixTranspose(matrix));

	// 定数バッファに行列をセット
	Direct3DGetDeviceContext()->UpdateSubresource(g_pVSConstantBufferproj, 0, nullptr, &transpose, 0, 0);
}

void Shader2DSetWorldMatrix(const DirectX::XMMATRIX& matrix)
{
	// 定数バッファ格納用行列の構造体を定義
	XMFLOAT4X4 transpose;

	// 行列を転置して定数バッファ格納用行列に変換
	XMStoreFloat4x4(&transpose, XMMatrixTranspose(matrix));

	// 定数バッファに行列をセット
	Direct3DGetDeviceContext()->UpdateSubresource(g_pVSConstantBufferworld, 0, nullptr, &transpose, 0, 0);
}

void Shader2DSetColor(const DirectX::XMFLOAT4& color)
{
	// 定数バッファに色をセット
	Direct3DGetDeviceContext()->UpdateSubresource(g_pPSConstantBuffer, 0, nullptr, &color, 0, 0);
}

void Shader2DBeginLinear()
{
	// 頂点シェーダーとピクセルシェーダーを描画パイプラインに設定
	Direct3DGetDeviceContext()->VSSetShader(g_pVertexShader, nullptr, 0);
	Direct3DGetDeviceContext()->PSSetShader(g_pPixelShader, nullptr, 0);

	// 頂点レイアウトを描画パイプラインに設定
	Direct3DGetDeviceContext()->IASetInputLayout(g_pInputLayout);

	// 定数バッファを描画パイプラインに設定
	Direct3DGetDeviceContext()->VSSetConstantBuffers(0, 1, &g_pVSConstantBufferproj);
	Direct3DGetDeviceContext()->VSSetConstantBuffers(1, 1, &g_pVSConstantBufferworld);
	Direct3DGetDeviceContext()->PSSetConstantBuffers(0, 1, &g_pPSConstantBuffer);

	// サンプラーステートを描画パイプラインに設定
	Direct3DGetDeviceContext()->PSSetSamplers(0, 1, &g_pSamplerStateLinear);
}

void Shader2DBeginPoint()
{
	// 頂点シェーダーとピクセルシェーダーを描画パイプラインに設定
	Direct3DGetDeviceContext()->VSSetShader(g_pVertexShader, nullptr, 0);
	Direct3DGetDeviceContext()->PSSetShader(g_pPixelShader, nullptr, 0);

	// 頂点レイアウトを描画パイプラインに設定
	Direct3DGetDeviceContext()->IASetInputLayout(g_pInputLayout);

	// 定数バッファを描画パイプラインに設定
	Direct3DGetDeviceContext()->VSSetConstantBuffers(0, 1, &g_pVSConstantBufferproj);
	Direct3DGetDeviceContext()->VSSetConstantBuffers(1, 1, &g_pVSConstantBufferworld);
	Direct3DGetDeviceContext()->PSSetConstantBuffers(0, 1, &g_pPSConstantBuffer);

	// サンプラーステートを描画パイプラインに設定
	Direct3DGetDeviceContext()->PSSetSamplers(0, 1, &g_pSamplerStatePoint);
}
