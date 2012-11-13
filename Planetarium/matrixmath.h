#ifndef ZEDDY_MATRIX_MATH_H_
#define ZEDDY_MATRIX_MATH_H_

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

class MatrixMath{
public:
	static glm::mat4 PitchMatrix(float pitch);
	static glm::mat4 YawMatrix(float yaw);
	static glm::mat4 RollMatrix(float roll);
	static glm::mat4 OrientationMatrix(float pitch, float yaw, float roll);
};

#endif