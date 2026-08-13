/*============================================================
*	@file	 : BillboardRenderer.cpp
*	@brief	 : ビルボード描画コンポーネント
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/13
*	@updated : 2026/08/13
*============================================================*/
#include "BillboardRenderer.h"
#include "Game.h"
#include "Camera.h"

DirectX::XMMATRIX BillboardRenderer::GetWorldMatrix() const
{
	Camera* camera = Game::GetGameObject<Camera>();
	return _mOwner->GetTransform().GetBillboardMatrix(camera->GetViewMatrix());
}
