#include <glm\gtc\matrix_transform.hpp>

#include "camera.h"

Camera::Camera(int width, int height){
	_position = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	_pitch = _yaw = _roll = 0.0f;
	Resize(width, height);
}

void Camera::Resize(int width, int height){
	_projectionMatrix = glm::perspective(75.0f, (float)(width)/height, 0.1f, 1024.0f);
}

mat4 Camera::GetProjectionMatrix(void){
	return _projectionMatrix;
}

void Camera::Move(vec4 translation){
	_position += translation;
	_position.w = 1.0f;
}

void Camera::MoveTo(vec4 position){
	_position = position;
}

void Camera::Look(float pitch, float yaw, float roll){
	_pitch += pitch;
	_pitch = clamp(_pitch, -90.0f, 90.0f);

	_yaw += yaw;
	if (_yaw < 0.0f){
		_yaw += 360.0f;
	} else if (_yaw > 360.0f){
		_yaw -= 360.0f;
	}

	_roll += roll;
	_roll = clamp(_roll, -90.0f, 90.0f);
}

void Camera::LookTo(float pitch, float yaw, float roll){
	_pitch = pitch;
	_yaw = yaw;
	_roll = roll;
}

void Camera::LookAt(vec4 target){
	vec4 direction = target - _position;
	_pitch = glm::atan(direction.y, glm::sqrt(direction.x * direction.x + direction.z * direction.z));
	_yaw = -glm::atan(direction.x, direction.z);
}

// http://planning.cs.uiuc.edu/node102.html
// Note that the page is refering to pitch as rotation about the y-axis,
// yaw as rotation about the z-axis and roll as rotation about the x-axis.
//
// These aren't necessarily wrong definitions, but they do not fit with my
// coordinate system where z = forward, y = up and x = sideways.
mat4 Camera::GetViewMatrix(void){
	mat4 rollMatrix = mat4(1.0f);
	rollMatrix[0][0] = cos(_roll);
	rollMatrix[1][0] = -sin(_roll);
	rollMatrix[0][1] = sin(_roll);
	rollMatrix[1][1] = cos(_roll);

	mat4 yawMatrix = mat4(1.0f);
	yawMatrix[0][0] = cos(_yaw);
	yawMatrix[2][0] = sin(_yaw);
	yawMatrix[0][2] = -sin(_yaw);
	yawMatrix[2][2] = cos(_yaw);

	mat4 pitchMatrix = mat4(1.0f);
	pitchMatrix[1][1] = cos(_pitch);
	pitchMatrix[2][1] = -sin(_pitch);
	pitchMatrix[1][2] = sin(_pitch);
	pitchMatrix[2][2] = cos(_pitch);

	mat4 translationMatrix = mat4(1.0f);
	translationMatrix[3] = _position;

	return rollMatrix * pitchMatrix * yawMatrix * translationMatrix;
}