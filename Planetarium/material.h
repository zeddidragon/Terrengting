#ifndef ZEDDY_MATERIAL_H_
#define ZEDDY_MATERIAL_H_

#include <glm\glm.hpp>

using namespace glm;

class Material{
public:
	Material(vec4 ambient, vec4 diffuse, vec4 specular, vec4 emitted, float shininess);

	glm::vec4 Ambient, Diffuse, Specular, Emitted;
	float Shininess;
};

#endif