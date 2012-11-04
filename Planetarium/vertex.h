#ifndef ZEDDY_VERTEX_H_
#define ZEDDY_VERTEX_H_

#include <glm\glm.hpp>

struct Vertex{
	glm::vec4 Position;
	glm::vec3 Normal;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
	glm::vec2 UvCoordinate;
};

#endif
