#include "skybox.h"

Skybox::Skybox(void){
	Vertex* vertices = new Vertex[24];	// 6 faces with 4 unique vertices
	GLuint* indices = new GLuint[36];	// 6 faces with 2 triangles with 3 indexes
	
	Cube::GenerateVertices(vertices);
	GenerateIndices(indices);
	GenerateVao(vertices, indices, 24, 36);

	delete vertices;
	delete indices;
}

void Skybox::GenerateIndices(GLuint* indices){
	unsigned int index = 0;

	for (unsigned int  i = 0; i < 24; i += 4){
		GenerateQuadIndices(indices, i, index);
	}
}

void Skybox::GenerateQuadIndices(GLuint* indices, unsigned int vertexIndex, unsigned int& indexIndex){
	indices[indexIndex++] = vertexIndex;
	indices[indexIndex++] = vertexIndex + 1;
	indices[indexIndex++] = vertexIndex + 2;

	indices[indexIndex++] = vertexIndex + 2;
	indices[indexIndex++] = vertexIndex + 1;
	indices[indexIndex++] = vertexIndex + 3 ;
}