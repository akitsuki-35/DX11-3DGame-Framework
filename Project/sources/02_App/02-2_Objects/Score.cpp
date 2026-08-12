/*============================================================
*	@file	 : Score.cpp
*	@brief	 : スコア表示
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/30
*	@updated : 2026/08/12
*============================================================*/
#include "Score.h"
#include "UIRenderer.h"
#include "TextRenderer.h"

void Score::Initialize()
{
	mLayer = 3;

	TextRenderer* renderer = AddComponent<TextRenderer>(this);

	renderer->GetCanvas().CreateCanvas(UIStyle::Pivot::LeftTop);

	mTransform.SetPosition({ 0.0f, 0.0f, 0.0f });
	mTransform.SetScale({ 1000.0f, 100.0f, 0.0f });

	renderer->SetFont("MPLUS_Regular")->SetText("あのイーハトーヴォのすきとおった風、夏でも底に冷たさをもつ青いそら、うつくしい森で飾られたモリーオ市、郊外のぎらぎらひかる草の波")->LoadShader("UI");

	mValue = 0;
}

void Score::Finalize()
{
	GameObject::Finalize();
}

void Score::Update()
{
	GameObject::Update();
}

void Score::Draw() const
{
	// UV座標書き換え				
	//for (int i = 0; i < DIGIT; i++)
	//{
	//	int num = number % 10;
	//	number /= 10;

	//	D3D11_MAPPED_SUBRESOURCE msr;
	//	Renderer::GetDeviceContext()->Map(_mVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	//	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	//	float x = -102.0f * i;

	//	float tx = 1.0f / 5.0f * (num % 5);
	//	float ty = 1.0f / 2.0f * (num / 10);
	//	float tw = 1.0f / 5.0f;
	//	float th = 1.0f / 2.0f;

	//	vertex[0].Position = XMFLOAT3(x, 0.0f, 0.0f);
	//	vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	//	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	//	vertex[0].TexCoord = XMFLOAT2(tx, ty);

	//	vertex[1].Position = XMFLOAT3(x + 102.0f, 0.0f, 0.0f);
	//	vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	//	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	//	vertex[1].TexCoord = XMFLOAT2(tx + tw, ty);

	//	vertex[2].Position = XMFLOAT3(x, 102.0f, 0.0f);
	//	vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	//	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	//	vertex[2].TexCoord = XMFLOAT2(tx, ty + th);

	//	vertex[3].Position = XMFLOAT3(x + 102.0f, 102.0f, 0.0f);
	//	vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	//	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	//	vertex[3].TexCoord = XMFLOAT2(tx + tw, ty + th);

	//	Renderer::GetDeviceContext()->Unmap(_mVertexBuffer, 0);

	//	// 描画	
	//	Renderer::GetDeviceContext()->Draw(4, 0);
	//}

	GameObject::Draw();
}