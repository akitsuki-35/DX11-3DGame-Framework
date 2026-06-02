/*============================================================
*	@file	 : Component.h
*	@brief	 : コンポーネント基底クラス
*
* 　@Author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@Date	 : 2026/05/19
*	@Updated : 2026/06/02
*============================================================*/
#ifndef COMPONENT_H
#define COMPONENT_H

/*============================================================
*	@class	: Component
*	@brief	: コンポーネント基底クラス
*============================================================*/
class Component
{
protected:

	class GameObject* m_GameObject = nullptr;

public:
	Component() {}
	Component(GameObject* Object) { m_GameObject = Object; }
	virtual ~Component() {}

	virtual void Initialize() {};
	virtual void Finalize() {};
	virtual void Update() {};
	virtual void Draw() {};
};

#endif // COMPONENT_H