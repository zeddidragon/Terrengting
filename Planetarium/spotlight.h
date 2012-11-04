#ifndef ZEDDY_SPOT_LIGHT_H_
#define ZEDDY_SPOT_LIGHT_H_

#include <glm\glm.hpp>
#include "pointlight.h"

class SpotLight : public PointLight {
public:
	SpotLight();
	virtual void Bind(Shader* shader, Material* material, unsigned int index, const mat4& viewMatrix) override;

	vec3 Direction;
	float Angle;	//In degrees
};

#endif