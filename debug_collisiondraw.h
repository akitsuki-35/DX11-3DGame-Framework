/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	コリジョン可視化[debug_collisiondraw.h]
*
* 　Author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　Date	: 2026/04/20
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#ifndef DEBUG_COLLISIONDRAW_H
#define DEBUG_COLLISIONDRAW_H

#include <DirectXMath.h>

void CollisionDrawInitialize();
void CollisionDrawFinalize();

void CircleCollisionDraw(const DirectX::XMFLOAT2& center, const float& radius,
	const DirectX::XMFLOAT4& color = { 1.0f,1.0f,1.0f,1.0f });

void BoxCollisionDraw(const DirectX::XMFLOAT2& center, const DirectX::XMFLOAT2& size,
	const DirectX::XMFLOAT4& color = { 1.0f,1.0f,1.0f,1.0f });

#endif // DEBUG_COLLISIONDRAW_H