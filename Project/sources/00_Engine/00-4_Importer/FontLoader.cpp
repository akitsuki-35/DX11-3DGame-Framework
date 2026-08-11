/*============================================================
*	@file	 : FontLoader.h
*	@brief	 : フォントファイル読み込み
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/04
*	@updated : 2026/08/11
*============================================================*/
#include "FontLoader.h"
#include "Utility.h"
#include <Windows.h>

using namespace Microsoft::WRL;

//const void FontRenderer::Initialize(HWND hWnd)
//{
//	// DirectWrite初期化
//	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory);
//
//	// バックバッファ取得
//	Direct3DGetSwapChain()->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
//
//	// 解像度設定
//	float dpiX, dpiY;
//	dpiX = dpiY = static_cast<float>(GetDpiForWindow(hWnd));
//
//	// レンダーターゲット作成
//	D2D1_RENDER_TARGET_PROPERTIES rt =
//		D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT, 
//			D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED), dpiX, dpiY);
//
//	// サーフェス用レンダーターゲット
//	pFactory->CreateDxgiSurfaceRenderTarget(pBackBuffer, &rt, &pRenderTarget);
//
//	// アンチエイリアスモード設定
//	pRenderTarget->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE);
//
//	// ファクトリー作成
//	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), 
//		reinterpret_cast<IUnknown**>(&pDwriteFactory));
//}
//
//const void FontRenderer::Finalize()
//{
//	SAFE_RELEASE(pBackBuffer);
//	SAFE_RELEASE(pBackBuffer);
//	SAFE_RELEASE(pBackBuffer);
//	SAFE_RELEASE(pBackBuffer);
//	SAFE_RELEASE(pBackBuffer);
//}

IDWriteFactory* FontLoader::Initialize()
{
	// ファクトリ生成
	ComPtr<IDWriteFactory> factory;
	HRESULT hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown**>(factory.GetAddressOf()));
	if (FAILED(hr)) {
		return nullptr;
	}

	return factory.Get();
}

bool FontLoader::Load(IDWriteFactory* factory, Font& font, const char* fontPath)
{
	if (!factory || !fontPath) {
		return false;
	}

	// パスをstd::wstringに変換
	const std::wstring wide = Utility::String::toWideString(fontPath);

	// フォントファイル取得
	ComPtr<IDWriteFontFile> fontFile{};
	HRESULT hr = factory->CreateFontFileReference(wide.c_str(), nullptr, fontFile.GetAddressOf());
	if (FAILED(hr)) {
		return false;
	}

	// フォントフェース作成
	IDWriteFontFile* fontFileArray[] = { fontFile.Get() };
	hr = factory->CreateFontFace(DWRITE_FONT_FACE_TYPE_TRUETYPE, 1, fontFileArray,
		0, DWRITE_FONT_SIMULATIONS_NONE, font.Face.ReleaseAndGetAddressOf());
	if (FAILED(hr)) {
		return false;
	}

	// メトリクス取得
	font.Face->GetMetrics(&font.Metrics);

	//DWORD size = GetFileSize(file, nullptr);
	//std::vector<BYTE> buffer(size);

	//DWORD readBytes{};
	//
	//if (!ReadFile(file, buffer.data(), size, &readBytes, nullptr)) {
	//	return false;
	//}

	//CloseHandle(file);

	//// ストリームとローダーを生成
	//auto* stream = new IDWriteStream(buffer.data(), buffer.size());
	//auto* loader = new IDWriteLoader(stream);

	//// DirectWriteにローダーを登録
	//factory->RegisterFontFileLoader(loader);

	//// フォントファイル生成
	//IDWriteFontFile* fontFile = nullptr;
	//
	//HRESULT hr = factory->CreateCustomFontFileReference(nullptr, 0, loader, &fontFile);
	//if (FAILED(hr)) { 
	//	return false;
	//}

	////  FontFace(フォント実体)生成
	//IDWriteFontFace* fontFace = nullptr;
	//hr = factory->CreateFontFace(DWRITE_FONT_FACE_TYPE_TRUETYPE, 1, &fontFile, 0,
	//	DWRITE_FONT_SIMULATIONS_NONE, &fontFace);
	//
	//if (FAILED(hr)) {
	//	return false;
	//}

	//// メトリクス取得
	//DWRITE_FONT_METRICS metrics{};
	//fontFace->GetMetrics(&metrics);

	//// フォント登録
	//font.Face = fontFace;
	//font.Metrics = metrics;

	//return true;
}