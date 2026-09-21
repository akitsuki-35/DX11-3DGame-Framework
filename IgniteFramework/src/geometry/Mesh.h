/*============================================================
*	@file	 : Mesh.h
*	@brief	 : ポリゴンメッシュ
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/24
*	@updated : 2026/09/16
*============================================================*/
#pragma once

#include "MeshTypes.h"
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

public:
	Mesh() = default;
	~Mesh() = default;

	// 板ポリゴン作成
	bool CreatePlane(MeshType::Plane::Pivot pivot, MeshType::Plane::Axis axis);

	void Bind() const;
	void Draw() const;
};