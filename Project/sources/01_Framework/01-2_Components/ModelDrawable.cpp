/*============================================================
*	@file	 : ModelDrawable.cpp
*	@brief	 : モデル描画コンポーネント
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/01
*	@updated : 2026/08/01
*============================================================*/
#include "ModelDrawable.h"
#include "BufferManager.h"

void ModelDrawable::Draw() const
{
	if (!_mModel) return;

	D3D11::BufferManager::getInstance().SetWorldMatrix(GetWorldMatrix());

    for (auto& mesh : _mModel->mMeshes)
    {
        mesh.Bind();

        for (auto& subset : mesh.subsets)
        {
            Element::MATERIAL material{};
            material.Diffuse = _mModel->mMaterials[subset.MaterialIndex].Material.Diffuse;
            material.TextureEnable = _mModel->mMaterials[subset.MaterialIndex].Material.TextureEnable;
            
            D3D11::BufferManager::getInstance().SetMaterial(material);

            if (mTextures.Diffuse)
            {
                mTextures.Diffuse->Bind();
            }
            else if (material.TextureEnable) {
                _mModel->mMaterials[subset.MaterialIndex]._Texture->Bind();
            }

            mesh.Draw(subset);
        }
    }
}