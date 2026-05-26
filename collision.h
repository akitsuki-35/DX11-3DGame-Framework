/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	コリジョン[collision.h]
*
* 　Author  : Asuka Kuroda
* 　Date	: 2026/04/29
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#ifndef COLLISION_H
#define COLLISION_H

#include <DirectXMath.h>

/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	衝突防止のためnamespace使用
	using namespaceしないこと

	※サークルコリジョン試作段階のため、ボックスコリジョンを使用すること
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
/*----------------------------------------------------------------------------------------------------------
	前方宣言
----------------------------------------------------------------------------------------------------------*/
namespace Collision {
	class Circle;
	class Box;
}

/*----------------------------------------------------------------------------------------------------------
	コリジョン基底クラス
----------------------------------------------------------------------------------------------------------*/
class CollisionBase
{
protected:
	DirectX::XMFLOAT2 center{}; // コリジョン中心座標
	DirectX::XMFLOAT2 collisionSize{}; // コリジョンサイズ

public:
	CollisionBase(const DirectX::XMFLOAT2& position, const DirectX::XMFLOAT2& collisionSize,
		const DirectX::XMFLOAT2& objectSize = { 0.0f, 0.0f })
		: collisionSize(collisionSize) {
		SetCenter(position, objectSize);
	}
	virtual ~CollisionBase() = default;

protected:
	void SetCenter(const DirectX::XMFLOAT2& offset, const DirectX::XMFLOAT2& objectSize = { 0.0f, 0.0f }) {
		if (objectSize.x && objectSize.y) {
			center = { offset.x + objectSize.x / 2, offset.y + objectSize.y / 2 };
		}
		else {
			center = { offset.x + collisionSize.x / 2, offset.y + collisionSize.y / 2 };
		}
	}

	virtual bool IsOverlap(const Collision::Circle*) const { return false; }
	virtual bool IsOverlap(const Collision::Box*) const { return false; }

	virtual void Move(const DirectX::XMFLOAT2& currentPos, const DirectX::XMFLOAT2& objectSize = { 0.0f, 0.0f }) {
		SetCenter(currentPos, objectSize);
	}
	virtual const DirectX::XMFLOAT2& GetCenter() const { return center; }

	virtual void Draw() const {}
};

/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	コリジョン
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
/*----------------------------------------------------------------------------------------------------------
	サークルコリジョン
----------------------------------------------------------------------------------------------------------*/
class Collision::Circle : public CollisionBase
{
private:
	float radius{};

public:
	Circle(const DirectX::XMFLOAT2& position, const DirectX::XMFLOAT2& collisionSize,
		const DirectX::XMFLOAT2& objectSize)
		: CollisionBase(position, collisionSize, objectSize){
		if (collisionSize.x / 2 <= collisionSize.y / 2) {
			radius = collisionSize.x / 2;
		}
		else {
			radius = collisionSize.y / 2;
		}
	}

	bool IsOverlap(const Circle* target) const override;
	bool IsOverlap(const Box* target) const override;

	virtual void Move(const DirectX::XMFLOAT2& currentPos, const DirectX::XMFLOAT2& objectSize = { 0.0f, 0.0f }) override {
		SetCenter(currentPos, objectSize);
	}

	void Draw() const override;
};

/*----------------------------------------------------------------------------------------------------------
	ボックスコリジョン
----------------------------------------------------------------------------------------------------------*/
class Collision::Box : public CollisionBase
{
private:
	DirectX::XMFLOAT2 min{};
	DirectX::XMFLOAT2 max{};

public:
	Box(const DirectX::XMFLOAT2& position, const DirectX::XMFLOAT2& collisionSize,
		const DirectX::XMFLOAT2& objectSize)
		: CollisionBase(position, collisionSize, objectSize) {
		min = { center.x - (collisionSize.x / 2), center.y - (collisionSize.y / 2) };
		max = { center.x + (collisionSize.x / 2), center.y + (collisionSize.y / 2) };
	}

	bool IsOverlap(const Circle* target) const override;
	bool IsOverlap(const Box* target) const override;

	void Move(const DirectX::XMFLOAT2& currentPos, const DirectX::XMFLOAT2& objectSize = { 0.0f, 0.0f }) override {
		SetCenter(currentPos, objectSize);
		min = { center.x - (collisionSize.x / 2), center.y - (collisionSize.y / 2) };
		max = { center.x + (collisionSize.x / 2), center.y + (collisionSize.y / 2) };
	}

	void Draw() const override;
};

#endif // COLLISION_H