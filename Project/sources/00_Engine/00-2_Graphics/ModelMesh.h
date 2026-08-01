/*============================================================
*	@file	 : ModelMesh.h
*	@brief	 : モデル用メッシュ
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/01
*	@updated : 2026/08/01
*============================================================*/
#pragma once

#include <vector>
#include <wrl/client.h>
#include <d3d11.h>

/*============================================================
*	@class	: ModelMesh
*	@brief	: モデル用メッシュ
*============================================================*/
class ModelMesh
{
	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

private:

	// サブセット
	struct SUBSET
	{
		uint32_t startIndex{};
		uint32_t indexNum{};
		uint32_t materialIndex{};
	};

	// 頂点バッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> _mVertexBuffer{};

	// インデックスバッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> _mIndexBuffer{};

	std::vector<SUBSET> subsets{};

public:
	ModelMesh() = default;
	~ModelMesh() = default;

	void Bind() const;
	void Draw(const SUBSET& subset) const;
};