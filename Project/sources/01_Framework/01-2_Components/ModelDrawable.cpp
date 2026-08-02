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

    for (auto& mesh : _mModel->mMeshs)
    {
        mesh.Bind();

        OutputDebugStringA(
            ("MaterialCount : " +
                std::to_string(_mModel->mMaterials.size()) +
                "\n").c_str()
        );

        for (auto& subset : mesh.subsets)
        {
            Element::MATERIAL material{};
            material.Diffuse = _mModel->mMaterials[subset.MaterialIndex].material.Diffuse;
            material.TextureEnable = _mModel->mMaterials[subset.MaterialIndex].material.TextureEnable;
            
            D3D11::BufferManager::getInstance().SetMaterial(material);

            if (material.TextureEnable) {
                _mModel->mMaterials[subset.MaterialIndex].texture.Bind();
            }

            mesh.Draw(subset);
        }
    }
}