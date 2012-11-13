#include "matrixmath.h"

// http://planning.cs.uiuc.edu/node102.html
// Note that the page is refering to pitch as rotation about the y-axis,
// yaw as rotation about the z-axis and roll as rotation about the x-axis.
//
// These aren't necessarily wrong definitions, but they do not fit with my
// coordinate system where z = forward, y = up and x = right.

glm::mat4 MatrixMath::PitchMatrix(float pitch){
	glm::mat4 ret = glm::mat4(1.0f);

	ret[1][1] = cos(pitch);
	ret[2][1] = -sin(pitch);
	ret[1][2] = sin(pitch);
	ret[2][2] = cos(pitch);

	return ret;
}



glm::mat4 MatrixMath::YawMatrix(float yaw){
	glm::mat4 ret = glm::mat4(1.0f);

	ret[0][0] = cos(yaw);
	ret[2][0] = sin(yaw);
	ret[0][2] = -sin(yaw);
	ret[2][2] = cos(yaw);

	return ret;
}



glm::mat4 MatrixMath::RollMatrix(float roll){
	glm::mat4 ret = glm::mat4(1.0f);

	ret[0][0] = cos(roll);
	ret[1][0] = -sin(roll);
	ret[0][1] = sin(roll);
	ret[1][1] = cos(roll);

	return ret;
}

glm::mat4 MatrixMath::OrientationMatrix(float pitch, float yaw, float roll){
	glm::mat4 rollMatrix = RollMatrix(roll);
	glm::mat4 yawMatrix = YawMatrix(yaw);
	glm::mat4 pitchMatrix = PitchMatrix(pitch);

	return rollMatrix * pitchMatrix * yawMatrix;
}