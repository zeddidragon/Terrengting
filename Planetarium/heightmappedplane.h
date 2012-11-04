#ifndef ZEDDY_HEIGHTMAPPED_PLANE_H_
#define ZEDDY_HEIGHTMAPPED_PLANE_H_

#include "model.h"
#include "texture.h"

class HeightMappedPlane : public Model{
public:
	HeightMappedPlane(float quadWidth, float quadHeight, float maxHeight, unsigned int width, unsigned int height, Texture* heightmap);

private:
	void GenerateVertices(Vertex* vertices, float quadWidth, float quadHeight, float maxHeight, unsigned int width, unsigned int height, Texture* heightmap);
	void GenerateUvCoordinates(Vertex* vertices, float textureWidth, float textureHeight, unsigned int width, unsigned int height);
	void GenerateIndices(GLuint* indices, unsigned int width, unsigned int height);
	void GenerateIndexRow(GLuint* indices, unsigned int width, unsigned int row, unsigned int& index);
};

#endif