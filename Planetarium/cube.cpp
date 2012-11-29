#include "cube.h"
#include "vertex.h"

Cube::Cube(){
	Vertex* vertices = new Vertex[24];	// 6 faces with 4 unique vertices
	GLuint* indices = new GLuint[36];	// 6 faces with 2 triangles with 3 indexes
	
	GenerateVertices(vertices);
	GenerateIndices(indices);
	GenerateVao(vertices, indices, 24, 36);

	delete vertices;
	delete indices;
}

Cube::Cube(bool generateVao){
	if (generateVao)
		Cube();
}

void Cube::GenerateVertices(Vertex* vertices){
	unsigned int index = 0;

	vec3 x = vec3(1.0f, 0.0f, 0.0f);
	vec3 y = vec3(0.0f, 1.0f, 0.0f);
	vec3 z = vec3(0.0f, 0.0f, 1.0f);
	vec2 u = vec2(1.0f / 4, 0.0f);
	vec2 v = vec2(0.0f, 1.0f / 2);

	GenerateQuadVertices(vertices, index,  z, -y, -x, 1.0f * u + 1.0f * v, 2.0f * u + 2.0f * v);	// Front
	GenerateQuadVertices(vertices, index, -x, -y, -z, 0.0f * u + 1.0f * v, 1.0f * u + 2.0f * v);	// Left
	GenerateQuadVertices(vertices, index,  x, -y,  z, 2.0f * u + 1.0f * v, 3.0f * u + 2.0f * v);	// Right
	GenerateQuadVertices(vertices, index, -z, -y,  x, 3.0f * u + 1.0f * v, 4.0f * u + 2.0f * v);	// Back
	GenerateQuadVertices(vertices, index,  y,  z, -x, 1.0f * u + 0.0f * v, 2.0f * u + 1.0f * v);	// Top
	GenerateQuadVertices(vertices, index, -y, -z, -x, 0.0f * u + 0.0f * v, 1.0f * u + 1.0f * v);	// Bottom

}

void Cube::GenerateIndices(GLuint* indices){
	unsigned int index = 0;

	for (unsigned int  i = 0; i < 24; i += 4){
		GenerateQuadIndices(indices, i, index);
	}
}

void Cube::GenerateQuadVertices(Vertex* vertices, unsigned int& index, vec3 normal, vec3 tangent, vec3 bitangent, vec2 uvUpperLeft, vec2 uvLowerRight){
	// To understand this function, realize that in a cube, the normal should be pointing
	// in the direction the quad is facing, the tangent should be pointing "up" on the face
	// and the bitangent should be pointing "right".
	// Knowing this, one can procedurally create a cube using arbitrary vectors as long as
	// they all align 90 degrees with eachother.

	vec3 upperLeft	= normal - tangent + bitangent;
	vec3 upperRight	= normal - tangent - bitangent;
	vec3 lowerLeft	= normal + tangent + bitangent;
	vec3 lowerRight	= normal + tangent - bitangent;

	const Vertex VERTICES[] = {
		{
			vec4(upperLeft * 0.5f, 1.0f),
			normal, tangent, bitangent,
			uvUpperLeft, 0.0f
		} , {
			vec4(upperRight * 0.5f, 1.0f),
			normal, tangent, bitangent,
			vec2(uvLowerRight.x, uvUpperLeft.y),
			0.0f
		}, {
			vec4(lowerLeft * 0.5f, 1.0f),
			normal, tangent, bitangent,
			vec2(uvUpperLeft.x, uvLowerRight.y),
			0.0f
		}, {
			vec4(lowerRight * 0.5f, 1.0f),
			normal, tangent, bitangent,
			uvLowerRight, 0.0f
		}
	};

	vertices[index++] = VERTICES[0];
	vertices[index++] = VERTICES[1];
	vertices[index++] = VERTICES[2];
	vertices[index++] = VERTICES[3];
};

void Cube::GenerateQuadIndices(GLuint* indices, unsigned int vertexIndex, unsigned int& indexIndex){
	indices[indexIndex++] = vertexIndex + 2;
	indices[indexIndex++] = vertexIndex + 1;
	indices[indexIndex++] = vertexIndex;

	indices[indexIndex++] = vertexIndex + 3;
	indices[indexIndex++] = vertexIndex + 1;
	indices[indexIndex++] = vertexIndex + 2 ;
}