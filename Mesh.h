/*============================================================
*	@file	 : Mesh.h
*	@brief	 : ポリゴンメッシュ
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/24
*	@updated : 2026/07/24
*============================================================*/
#pragma once

#include <vector>
#include <wrl/client.h>
#include <d3d11.h>

/*============================================================
*	@class	: Mesh
*	@brief	: ポリゴンメッシュ
*============================================================*/
class Mesh
{
	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
	// 頂点バッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> _mVertexBuffer{};

	// インデックスバッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> _mIndexBuffer{};

	UINT mVertexStride{};
	UINT mVertexNum{};
	UINT mIndexNum{};
	bool mIsIndex{ false };

public:
	Mesh() = default;
	~Mesh() = default;

	bool CreatePlane();

	void Draw() const;
	void Bind() const;
};