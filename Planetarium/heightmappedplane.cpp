#include "heightmappedplane.h"

HeightMappedPlane::HeightMappedPlane(float quadWidth, float quadHeight, float maxHeight, HeightMap* heightMap){
	unsigned int width = heightMap->Width() - 1, height = heightMap->Height() - 1;
	unsigned int quadCount = width * height;
	unsigned int vertexCount = (width + 1) * (height + 1);
	// We're not doing trianglestrips this time, so six indicies per quad (2 triangles * 3 points).
	unsigned int indexCount = quadCount * 6;

	Vertex* vertices = new Vertex[vertexCount];
	GLuint* indices = new GLuint[indexCount];

	//heightMap->PrintData();

	GenerateVertices(vertices, quadWidth, quadHeight, maxHeight, heightMap);
	GenerateIndices(indices, width, height);
	GenerateUvCoordinates(vertices, 1.0f / quadWidth, 1.0f / quadHeight, width + 1, height + 1);
	Model::GenerateNormals(vertices, indices, vertexCount, indexCount);
	Model::GenerateTangents(vertices, indices, vertexCount, indexCount);
	Model::GenerateBitangents(vertices, vertexCount);
	Model::GenerateVao(vertices, indices, vertexCount, indexCount);

	delete indices;
}



void HeightMappedPlane::GenerateVertices(Vertex* vertices, float quadWidth, float quadHeight, float maxHeight, HeightMap* heightMap){
	unsigned int i, j, columnOffset;
	float x, y, z;
	float u, v;
	unsigned int width = heightMap->Width(), height = heightMap->Height();

	columnOffset = 0;

	z = height * -quadHeight / 2.0f;
	v = 0.0f;
	for (j = 0; j < height; ++j){
		x = width * -quadWidth / 2.0f;
		u = 0.0f;
		for (i = 0; i < width; ++i){
			y = maxHeight * heightMap->Map[i + j * width];
			vertices[columnOffset + i].Position = vec4(x, y, z, 1.0f);
			vertices[columnOffset + i].Normal = vec3(0.0f, 1.0f, 0.0f);
			x += quadWidth;
		}
		z += quadHeight;
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

	for (unsigned int quad = 0; quad < width; ++quad){
		indices[index++] = totalOffset + quad;
		indices[index++] = totalOffset + quad + rowOffset;
		indices[index++] = totalOffset + quad + 1;

		indices[index++] = totalOffset + quad + 1;
		indices[index++] = totalOffset + quad + rowOffset;
		indices[index++] = totalOffset + quad + rowOffset + 1;
		
	}
}