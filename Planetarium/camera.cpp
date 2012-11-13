#include "camera.h"
#include "matrixmath.h"

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

mat4 Camera::GetViewMatrix(void){
	mat4 orientationMatrix = MatrixMath::OrientationMatrix(_pitch, _yaw, _roll);
	mat4 translationMatrix = mat4(1.0f);
	translationMatrix[3] = _position;

	return orientationMatrix * translationMatrix;
}