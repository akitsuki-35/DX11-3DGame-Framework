/*============================================================
*	@file	 : Tree.h
*	@brief	 : 木のビルボード
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/02
*	@updated : 2026/07/26
*============================================================*/
#include "Main.h"
#include "Tree.h"
#include "Renderer.h"
#include "DeviceManager.h"
#include "BufferManager.h"
#include "Audio.h"
#include "BillboardDrawable.h"

#include "GraphicsTypes.h"
#include "MeshTypes.h"
#include "DirectX11Config.h"

using namespace MeshType;

void Tree::Initialize()
{
	mLayer = 2;

	//mMesh.CreatePlane(Plane::Pivot::CenterBottom, Plane::Axis::XY);
	//mTransform.SetPosition({ -5.0f,0.0f, 0.0f });
	//mTransform.SetScale({ 8.0f, 10.0f, 0.0f });

	//// テクスチャ読込
	//TexMetadata metaData;
	//ScratchImage image;
	//LoadFromWICFile(L"Resources\\Textures\\Background\\tree.png", WIC_FLAGS_NONE, &metaData, image);
	//CreateShaderResourceView(D3D11::DeviceManager::getInstance().GetDevice().Get(),
	//	image.GetImages(), image.GetImageCount(), metaData, &_mTexture); 
	//assert(_mTexture);

	//// シェーダー読込
	//mShader = ShaderLoader::getInstance().Get("Unlit");

	BillboardDrawable* drawable = AddComponent<BillboardDrawable>(this);

	drawable->GetMesh().CreatePlane(Plane::Pivot::CenterBottom, Plane::Axis::XY);

	mTransform.SetPosition({ -5.0f,0.0f, 0.0f });
	mTransform.SetScale({ 8.0f, 10.0f, 0.0f });

	drawable->GetTexture().Load(L"assets\\textures\\Background\\tree.png");

	drawable->LoadShader("Unlit");
}

void Tree::Finalize()
{

}

void Tree::Update()
{
}

void Tree::Draw() const
{
	GameObject::Draw();
}