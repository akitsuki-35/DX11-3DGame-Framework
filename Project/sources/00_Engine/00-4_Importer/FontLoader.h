/*============================================================
*	@file	 : FontLoader.h
*	@brief	 : フォントファイル読み込み
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/04
*	@updated : 2026/08/11
*============================================================*/
#pragma once

#include <dwrite.h>
#include <string>
#include <vector>

// フォントデータ
struct Font {
	IDWriteFontFace* Face{ nullptr };
	DWRITE_FONT_METRICS Metrics{};
	float Size = 32.0f;
};

/*============================================================
*	@class	: FontLoader
*	@brief	: フォントファイル読み込み
*============================================================*/
class FontLoader final
{
/*--------------------------------------------------
	Singleton用
----------------------------------------------------*/
public:
	static FontLoader& getInstance() {
		static FontLoader instance;
		return instance;
	}

private:
	FontLoader() = default;
	FontLoader(const FontLoader&) = delete;

	FontLoader& operator=(const FontLoader&) = delete;
	FontLoader(FontLoader&&) = delete;

	FontLoader& operator=(FontLoader&&) = delete;
	~FontLoader() {};

/*--------------------------------------------------
	メンバ変数・メンバ関数
----------------------------------------------------*/
public:
	bool Load(IDWriteFactory* factory, const std::string& path, Font& font);

private:

	/*============================================================
	*	@class	: IDWriteStream
	*	@brief	: フォントファイルのバイト列送信
	*============================================================*/
	class IDWriteStream : public IDWriteFontFileStream
	{
	private:
		ULONG mRefCount{ 0 }; // COM参照カウンタ
		std::vector<BYTE> mData{}; // フォントファイルの全バイト列

	public:
		IDWriteStream(const void* fontData, size_t size)
			: mData((BYTE*)fontData, (BYTE*)fontData + size) {}

		// DirectWriteによるデータ要求
		HRESULT STDMETHODCALLTYPE ReadFileFragment(const void** fragmentStart, UINT64 fileOffset,
			UINT64 fragmentSize, void** fragmentContext) override {
			// 要求された範囲がファイルサイズを超えていないかチェック
			if (fileOffset + fragmentSize > mData.size()) {
				return E_FAIL;
			}

			// データ先頭コメント
			*fragmentStart = &mData[(size_t)fileOffset];
			
			*fragmentContext = nullptr;
			
			return S_OK;
		}

		void STDMETHODCALLTYPE ReleaseFileFragment(void* fragmentContext) override {}

		// フォントファイルのサイズ襲来
		HRESULT STDMETHODCALLTYPE GetFileSize(UINT64* fileSize) override {
			*fileSize = mData.size();
			return S_OK;
		}

		// 更新日時を取得
		HRESULT STDMETHODCALLTYPE GetLastWriteTime(UINT64* lastWriteTime) override {
			*lastWriteTime = 0;
			return S_OK;
		}

		// COM参照カウンタ
		ULONG STDMETHODCALLTYPE AddRef() override { return ++mRefCount; }
		ULONG STDMETHODCALLTYPE Release() override {
			ULONG newCount = --mRefCount;
			if (newCount == 0) delete this;
			return newCount;
		}

		HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject) override {
			if (riid == __uuidof(IDWriteFontFileStream))
			{
				*ppvObject = this;
				AddRef();
				return S_OK;
			}
			*ppvObject = nullptr;
			return E_NOINTERFACE;
		}
	};

	/*============================================================
	*	@class	: IDWriteLoader
	*	@brief	: DirectWrite用ストリーム生成
	*============================================================*/
	class IDWriteLoader : public IDWriteFontFileLoader
	{
	private:
		ULONG mRefCount{ 0 };
		IDWriteStream* _mStream{ nullptr };

	public:
		IDWriteLoader(IDWriteStream* stream)
			: _mStream(stream) {}

		// DirectWriteによるストリーム要求
		HRESULT STDMETHODCALLTYPE CreateStreamFromKey(void const* referenceKey,
			UINT32 referenceKeySize, IDWriteFontFileStream** stream) override {
			// DirectWriteにストリームを送る
			*stream = _mStream;
			_mStream->AddRef();
			return S_OK;
		}

		// COM参照カウンタ
		ULONG STDMETHODCALLTYPE AddRef() override { return ++mRefCount; }
		ULONG STDMETHODCALLTYPE Release() override {
			ULONG newCount = --mRefCount;
			if (newCount == 0) delete this;
			return newCount;
		}

		HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject) override {
			if (riid == __uuidof(IDWriteFontFileLoader))
			{
				*ppvObject = this;
				AddRef();
				return S_OK;
			}
			*ppvObject = nullptr;
			return E_NOINTERFACE;
		}
	};
};