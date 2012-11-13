#ifndef ZEDDY_SKYBOX_H_
#define ZEDDY_SKYBOX_H_

#include "cube.h"

class Skybox : public Cube {
public:
	Skybox(void);
protected:
	void GenerateIndices(GLuint* indices);
	void GenerateQuadIndices(GLuint* indices, unsigned int vertexIndex, unsigned int& indexIndex);
};

#endif