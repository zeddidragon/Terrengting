#ifndef ZEDDY_CAMERA_H_
#define ZEDDY_CAMERA_H_

#include <glm\glm.hpp>

using namespace glm;

class Camera{
public:
	Camera(int width, int height);
	void Resize(int width, int height);

	void Move(vec4 translation);
	void MoveTo(vec4 position);
	void Look(float pitch, float yaw, float roll);
	void LookTo(float pitch, float yaw, float roll);
	void LookAt(vec4 target);

	mat4 GetViewMatrix(void);
	mat4 GetProjectionMatrix(void);
protected:
	vec4 _position;
	float _pitch, _yaw, _roll;
	mat4 _projectionMatrix;
};

#endif