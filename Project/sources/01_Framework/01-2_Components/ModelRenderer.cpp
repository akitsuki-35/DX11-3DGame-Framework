/*============================================================
*	@file	 : ModelRenderer.cpp
*	@brief	 : モデル描画コンポーネント
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/01
*	@updated : 2026/08/04
*============================================================*/
#include "ModelRenderer.h"
#include "BufferManager.h"
#include "Texture.h"

void ModelRenderer::Draw() const
{
	if (!_mModel) return;

    Bind();

    // ワールド行列セット
	D3D11::BufferManager::getInstance().SetWorldMatrix(getWorldMatrix());

    // ボーン行列セット
    if (_mModel->GetSkeleton().GetBoneCount() > 0) {
        D3D11::BufferManager::getInstance().SetBoneMatrices(_mModel->GetSkeleton());
    }

    for (auto& mesh : _mModel->mMeshes)
    {
        mesh.Bind();

        // マテリアル設定
        for (auto& subset : mesh.subsets)
        {
            Element::MATERIAL material{};
            material.Diffuse = _mModel->mMaterials[subset.MaterialIndex].Material.Diffuse;

            if (mTextures.Diffuse || _mModel->mMaterials[subset.MaterialIndex].Material.TextureEnable) {
                // 埋め込みテクスチャまたは外部テクスチャが存在
                material.TextureEnable = true;
            }
            else {
                // 埋め込みテクスチャまたは外部テクスチャが存在しない
                material.TextureEnable = false;
            }
            
            // マテリアルのセット
            D3D11::BufferManager::getInstance().SetMaterial(material);

            if (mTextures.Diffuse)
            {
                // 外部テクスチャを使用して描画
                mTextures.Diffuse->Bind();
            }
            else if (material.TextureEnable) {
                // 埋め込みテクスチャを使用して描画
                _mModel->mMaterials[subset.MaterialIndex]._Texture->Bind();
            }
            else {
                Texture* dummy = TextureManager::getInstance().Load("assets\\textures\\Common\\white.png");
                dummy->Bind();
            }

            mesh.Draw(subset);
        }
    }
}