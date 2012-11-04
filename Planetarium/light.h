#ifndef ZEDDY_LIGHT_H_
#define ZEDDY_LIGHT_H_

#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "material.h"
#include "shader.h"
#include "constants.h"

using namespace glm;

class Light {
public:
	Light();
	virtual void Bind(Shader* shader, Material* material, unsigned int index, const mat4& viewMatrix);
	
	vec4 Ambient, Diffuse, Specular;
};

#endif