/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	カメラ[camera.h]
*
* 　Author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　Date	: 2026/04/26
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#ifndef CAMERA_H
#define CAMERA_H

#include "gameobject.h"

class Camera : public GameObject
{
protected:
	Vector3 target{}; // 注視点
	XMMATRIX viewMatrix;

public:
	virtual ~Camera() = default;
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() const override;

	XMMATRIX GetViewMatrix() const { return viewMatrix; }

	virtual Vector3 GetForward() const override {
		Vector3 forward = target - position;
		forward.Normalize();

		return forward;
	}

	virtual Vector3 GetRight() const override {
		Vector3 forward = target - position;
		Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
		Vector3 right = Vector3::cross(up, forward);
		right.Normalize();

		return right;
	}
};

class TopCamera : public Camera
{
public:
	void Initialize() override;
	void Update() override;
};

#endif // CAMERA_H