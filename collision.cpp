/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	コリジョン[collision.cpp]
*
* 　Author  : Asuka Kuroda
* 　Date	: 2026/04/19
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#include "collision.h"
#include "debug_collisiondraw.h"
#include "texture.h"
#include "sprite.h"
#include <cmath>
using namespace DirectX;

bool Collision::Circle::IsOverlap(const Circle* target) const
{
    XMFLOAT2 distance{ target->center.x - center.x, target->center.y - center.y };
    float centerDistance = std::sqrt((distance.x * distance.x) + (distance.y * distance.y));

    if (centerDistance <= radius + target->radius) {
        return true;
    }

    return false;
}

bool Collision::Circle::IsOverlap(const Box* /*target*/) const
{
    // 未実装
    return false;
}

void Collision::Circle::Draw() const
{
#if defined(DEBUG) || defined(_DEBUG)
    CircleCollisionDraw(center, radius, { 0.0f, 1.0f, 0.0f, 1.0f });
#endif
}

bool Collision::Box::IsOverlap(const Circle* /*target*/) const
{
    // 未実装
    return false;
}

bool Collision::Box::IsOverlap(const Box* target) const
{
    return min.x < target->max.x
        && max.x > target->min.x
        && min.y < target->max.y
        && max.y > target->min.y;
}

void Collision::Box::Draw() const
{
#if defined(DEBUG) || defined(_DEBUG)
    BoxCollisionDraw(center, collisionSize, { 0.0f, 1.0f, 0.0f, 1.0f });
#endif
}