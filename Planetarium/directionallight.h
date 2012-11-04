#ifndef ZEDDY_DIRECTIONAL_LIGHT_H_
#define ZEDDY_DIRECTIONAL_LIGHT_H_

#include <glm\glm.hpp>
#include "light.h"

class DirectionalLight : public Light {
public:
	DirectionalLight();
	virtual void Bind(Shader* shader, Material* material, unsigned int index, const mat4& viewMatrix) override;

	vec3 Direction;
};

#endif