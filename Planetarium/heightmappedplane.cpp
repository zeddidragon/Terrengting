#include "heightmappedplane.h"

HeightMappedPlane::HeightMappedPlane(float quadWidth, float quadHeight, float maxHeight, unsigned int width, unsigned int height, Texture* heightMap){
	unsigned int quadCount = width * height;
	unsigned int vertexCount = (width + 1) * (height + 1);
	// We're not doing trianglestrips this time, so six indicies per quad (2 triangles * 3 points).
	unsigned int indexCount = quadCount * 6;

	Vertex* vertices = new Vertex[vertexCount];
	GLuint* indices = new GLuint[indexCount];

	//heightMap->PrintData();

	GenerateVertices(vertices, quadWidth, quadHeight, maxHeight, width + 1, height + 1, heightMap);
	GenerateIndices(indices, width, height);
	GenerateUvCoordinates(vertices, 1.0f / quadWidth, 1.0f / quadHeight, width + 1, height + 1);
	Model::GenerateNormals(vertices, indices, vertexCount, indexCount);
	Model::GenerateTangents(vertices, indices, vertexCount, indexCount);
	Model::GenerateBitangents(vertices, vertexCount);
	Model::GenerateVao(vertices, indices, vertexCount, indexCount);
}



void HeightMappedPlane::GenerateVertices(Vertex* vertices, float quadWidth, float quadHeight, float maxHeight, unsigned int width, unsigned int height, Texture* heightMap){
	unsigned int i, j, columnOffset;
	float x, y, z;
	float u, v, uStep, vStep;

	columnOffset = 0;

	uStep = 1.0f / (width);
	vStep = 1.0f / (height);

	z = height * -quadHeight / 2.0f;
	v = 0.0f;
	for (j = 0; j < height; ++j){
		x = width * -quadWidth / 2.0f;
		u = 0.0f;
		for (i = 0; i < width; ++i){
			y = maxHeight * heightMap->DataAt(vec2(u, v));
			u += uStep;
			vertices[columnOffset + i].Position = vec4(x, y, z, 1.0f);
			vertices[columnOffset + i].Normal = vec3(0.0f, 1.0f, 0.0f);
			x += quadWidth;
		}
		z += quadHeight;
		v += vStep;
		columnOffset += width;
	}
}



void HeightMappedPlane::GenerateUvCoordinates(Vertex* vertices, float textureWidth, float textureHeight, unsigned int width, unsigned int height){
	unsigned int i, j, columnOffset;
	columnOffset = 0;
	for (j = 0; j < height; ++j){
		for (i = 0; i < width; ++i){
			vertices[columnOffset + i].UvCoordinate = vec2(i * textureWidth, j * textureHeight);
		}
		columnOffset += width;
	}
}



void HeightMappedPlane::GenerateIndices(GLuint* indices, unsigned int width, unsigned int height){
	unsigned int index, row;
	index = 0;
	for (row = 0; row < height; ++row){
		GenerateIndexRow(indices, width, row, index);
	}
}



void HeightMappedPlane::GenerateIndexRow(GLuint* indices, unsigned int width, unsigned int row, unsigned int& index){
	unsigned int rowOffset = (width + 1);
	unsigned int totalOffset = rowOffset * row;

	for (int quad = 0; quad < width; ++quad){
		indices[index++] = totalOffset + quad;
		indices[index++] = totalOffset + quad + rowOffset;
		indices[index++] = totalOffset + quad + 1;

		indices[index++] = totalOffset + quad + 1;
		indices[index++] = totalOffset + quad + rowOffset;
		indices[index++] = totalOffset + quad + rowOffset + 1;
		
	}
}