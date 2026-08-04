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

void ModelRenderer::Draw() const
{
	if (!_mModel) return;

	D3D11::BufferManager::getInstance().SetWorldMatrix(GetWorldMatrix());

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
            else if (_mModel->mMaterials[subset.MaterialIndex].Material.TextureEnable) {
                // 埋め込みテクスチャまたは外部テクスチャが存在しない
                material.TextureEnable = false;
            }
            
            // マテリアルのセット
            D3D11::BufferManager::getInstance().SetMaterial(material);

            if (mTextures.Diffuse)
            {
                // 埋め込みテクスチャまたは外部テクスチャを使用して描画
                mTextures.Diffuse->Bind();
            }
            else if (material.TextureEnable) {
                // ランバートカラーのみで描画
                _mModel->mMaterials[subset.MaterialIndex]._Texture->Bind();
            }

            mesh.Draw(subset);
        }
    }
}