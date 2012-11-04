#ifndef ZEDDY_MODEL_H
#define ZEDDY_MODEL_H

#include <gl\glew.h>
#include <glm\glm.hpp>

#include "vertex.h"

using namespace glm;

class Model {
protected:
	GLuint _vaoId, _vboId, _iboId, _indexCount;
	void GenerateVao(const Vertex* vertices, const GLuint* indices, unsigned int vertexCount, unsigned int indexCount);

	void GenerateNormals(Vertex* vertices, const GLuint* indices, unsigned int vertexCount, unsigned int indexCount);
	vec3 GenerateNormal(Vertex& v1, Vertex& v2, Vertex& v3);
	void GenerateTangents(Vertex* vertices, const GLuint* indices, unsigned int vertexCount, unsigned int indexCount);
	void GenerateBitangents(Vertex* vertices, unsigned int vertexCount);
	vec3 GenerateTangent(Vertex& v1, Vertex& v2, Vertex& v3);
public:
	~Model(void);
	virtual void Draw(void);
};

#endif