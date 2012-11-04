#ifndef ZEDDY_POINT_LIGHT_H_
#define ZEDDY_POINT_LIGHT_H_

#include <glm\glm.hpp>
#include "light.h"

class PointLight : public Light {
public:
	PointLight();
	virtual void Bind(Shader* shader, Material* material, unsigned int index, const mat4& viewMatrix) override;

	vec4 Position;
};

#endif