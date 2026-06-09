/*============================================================
*	@file	 : cursor.h
*	@brief	 : マウスカーソル
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/05/20
*	@updated : 2026/06/02
*============================================================*/
#ifndef CURSOR_H
#define CURSOR_H

#include "subject.h"

#include <list>
#include <memory>
#include <DirectXMath.h>

// 一旦諸々をカーソルに持たせる
enum Mode
{
	NONE,
	MOVE,
	SCALING,
	ROTATE,
	COLOR
};

/*------------------------------------------------------------
	マウスボタンの状態
------------------------------------------------------------*/
struct MouseButtonState
{
	bool leftButton{};
	bool rightButton{};
};

/*------------------------------------------------------------
	カーソルの状態
------------------------------------------------------------*/
struct CursorState
{
	Mode mode;
	DirectX::XMFLOAT4 color;
	MouseButtonState current;
	MouseButtonState last;
};

/*------------------------------------------------------------
	前方宣言
------------------------------------------------------------*/
class Texture;

/*============================================================
*	@class	: Cursor
*	@brief	: マウスカーソルオブジェクト
*			  シングルトンで作成
*============================================================*/
class Cursor : public Subject
{
private:
	static constexpr float SIZE{ 34.0f };
	static DirectX::XMFLOAT2 position;
	static std::list<std::unique_ptr<Texture>> textures; // ツール別にテクスチャを管理
	static CursorState cursorState;

	Cursor() {}
	Cursor(const Cursor&);
	Cursor& operator=(const Cursor&);
	~Cursor() {};

public:
	static Cursor& GetInstance() {
		static Cursor instance;
		return instance;
	}

	const void Update(double elapsedTime);

	// まだテクスチャの定義がないので通常のマウス表示
	// あとで使うので消さないで！！！！！
	// const void Draw();

/*------------------------------------------------------------
	ゲッター
------------------------------------------------------------*/
	const DirectX::XMFLOAT2& GetPosition() { return position; }
	const DirectX::XMFLOAT4& GetColor() { return cursorState.color; }

/*------------------------------------------------------------
	セッター
------------------------------------------------------------*/
	void SetColor(const DirectX::XMFLOAT4& color);

/*------------------------------------------------------------
	左ボタン状態取得
------------------------------------------------------------*/
	bool IsLeftButtonPressed();
	bool IsLeftButtonTrigger();
	bool IsLeftButtonUp();

/*------------------------------------------------------------
	右ボタン状態取得
------------------------------------------------------------*/
	bool IsRightButtonPressed();
	bool IsRightButtonTrigger();
	bool IsRightButtonUp();
};

#endif // CURSOR_H