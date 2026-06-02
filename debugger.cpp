/*============================================================
*	@file	 : debugger.cpp
*	@brief	 : ImGuiデバッガー
*
* 　@Author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@Date	 : 2026/05/21
*	@Updated : 2026/06/02
*============================================================*/
#if defined(DEBUG) || defined(_DEBUG)
#include "debugger.h"
#include "direct3d.h"

// ImGui
#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>

// デバッグ対象のインクルード
#include "cursor.h"

/*============================================================
	使い方

	ヘッダ側にデバッグウィンドウ関数の宣言を記述し、cpp側で定義
	Initialize, Finalize, Drawの内部とUpdateのImGui::NewFrame();より上の行の変更厳禁

	デバッグ関数は以下の書式で記述する
	必ずBeginとEndで挟むこと（飛びます）

	const void Debugger::[関数名]()
	{
		ImGui::Begin("Cursor");

		// 処理内容

		ImGui::End();
	}
============================================================*/
const void Debugger::Initialize(HWND hwnd) const
{
	// バージョンチェック
	IMGUI_CHECKVERSION();

	// コンテキスト作成
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	// win32用の初期化
	ImGui_ImplWin32_Initialize(hwnd);

	// DirectX11用の初期化
	ImGui_ImplDX11_Initialize(Direct3DGetDevice(), Direct3DGetDeviceContext());
}

const void Debugger::Finalize() const
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

const void Debugger::Update() const
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// ===== デバッグウィンドウの追加処理 =====

	GetInstance().CursorDebug();
	GetInstance().CursorColorDebug();
}

const void Debugger::Draw() const
{
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

const void Debugger::CursorDebug()
{
	ImGui::Begin("Cursor");
	ImGui::Text("posX: %f", Cursor::GetInstance().GetPosition().x);
	ImGui::Text("posY: %f", Cursor::GetInstance().GetPosition().y);
	ImGui::Text("LeftPresed: %s", Cursor::GetInstance().IsLeftButtonPressed() ? "true" : "false");
	ImGui::Text("RightPresed: %s", Cursor::GetInstance().IsRightButtonPressed() ? "true" : "false");
	ImGui::End();
}

const void Debugger::CursorColorDebug()
{
	ImGui::Begin("CursorColor");
	ImGui::Text(
		"Color : %.2f %.2f %.2f %.2f",
		Cursor::GetInstance().GetColor().x,
		Cursor::GetInstance().GetColor().y,
		Cursor::GetInstance().GetColor().z,
		Cursor::GetInstance().GetColor().w
	);
	ImGui::End();
}

#endif // defined(DEBUG) || defined(_DEBUG)