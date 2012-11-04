#ifndef ZEDDY_PLANE_H_
#define ZEDDY_PLANE_H_

#include "model.h"

class Plane : public Model{ 
public:
	Plane(float quadWidth, float quadHeight, unsigned int width, unsigned int height);
	virtual void Draw(void);

protected:
	void GenerateVertices(Vertex* vertices, float quadWidth, float quadHeight, unsigned int width, unsigned int height);
	void GenerateNormals(Vertex* vertices, unsigned int width, unsigned int height);
	void GenerateUvCoordinates(Vertex* vertices, float textureWidth, float textureHeight, unsigned int width, unsigned int height);
	void GenerateIndices(GLuint* indices, unsigned int width, unsigned int height);
	void StripRight(GLuint* indices, unsigned int width, unsigned int row, unsigned int& index);
	void StripLeft(GLuint* indices, unsigned int width, unsigned int row, unsigned int& index);
};

#endif