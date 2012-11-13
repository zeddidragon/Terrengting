#ifndef ZEDDY_CUBE_H_
#define ZEDDY_CUBE_H_

#include "model.h"
#include "vertex.h"

class Cube : public Model {
public:
	Cube(void);
protected:
	Cube(bool generateVao); //Null constructor for inherited use! Kind of an ugly hack.

	void GenerateVertices(Vertex* vertices);
	void GenerateIndices(GLuint* indices);
	void GenerateQuadVertices(Vertex* vertices, unsigned int& index, vec3 normal, vec3 tangent, vec3 bitangent, vec2 uvUpperLeft, vec2 uvLowerRight);
	void GenerateQuadIndices(GLuint* indices, unsigned int vertexIndex, unsigned int& indexIndex);
};

#endif