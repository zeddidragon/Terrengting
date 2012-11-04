#include "plane.h"
#include "window.h"

Plane::Plane(float quadWidth, float quadHeight, unsigned int width, unsigned int height){
	//There's one more row of vertices than quads, same for columns
	unsigned int quadCount = width*height;
	unsigned int vertexCount = (width+1)*(height+1);

	// This is explained further down, but the formula for the amount of indices in the plane is
	// (quads per row * 2 + 1) * rows + 1
	// The last +1 is for the stitch leading into the plane altogether,
	// while the +1 for each row is for the stitch finalizing each strip (as well as starting the next one.)
	
	unsigned int indexCount = (2 * width + 1) * height + 1;

	Vertex* vertices = new Vertex[vertexCount];
	GLuint* indices = new GLuint[indexCount];

	GenerateVertices(vertices, quadWidth, quadHeight, width + 1, height + 1);
	GenerateUvCoordinates(vertices, 1.0f / quadWidth, 1.0f / quadHeight, width + 1, height + 1);
	GenerateIndices(indices, width, height);
	GenerateNormals(vertices, width + 1, height + 1);

	GenerateVao(vertices, indices, vertexCount, indexCount);

	delete[] vertices;
	delete[] indices;
}

void Plane::Draw(void){
	glBindVertexArray(_vaoId);
	Window::ExitOnGLError("bind the VAO for drawing purposes");

	glDrawElements(GL_TRIANGLE_STRIP, _indexCount, GL_UNSIGNED_INT, (GLvoid*)0);
	Window::ExitOnGLError("draw the plane");

	glBindVertexArray(0);
}

/*
Base triangle strip, going right

	01	02	03	04...
	| / | / | / | /
	11	12	13	14...

	01 to 11 to 02 to 12 to 03 to 13 to 04 to 14...

Base triangle stripe, going left
	01	02	03	04...
	| \ | \ | \ |
	11	12	13	14...

	...04 to 14 to 03 to 13 to 02 to 12 to 01 to 11
*/

void Plane::GenerateVertices(Vertex* vertices, float quadWidth, float quadHeight, unsigned int width, unsigned int height){
	unsigned int i, j, columnOffset;
	float x, y;

	y = height * -quadHeight / 2.0f;
	columnOffset = 0;
	for (j = 0; j < height; ++j){
		x = width * -quadWidth / 2.0f;
		for (i = 0; i < width; ++i){
			vertices[columnOffset + i].Position = vec4(x, 0.0f, y, 1.0f);
			x += quadWidth;
		}
		y += quadHeight;
		columnOffset += width;
	}
}



void Plane::GenerateNormals(Vertex* vertices, unsigned int width, unsigned int height){
	unsigned int i, j, columnOffset;
	columnOffset = 0;
	for (j = 0; j < height; ++j){
		for (i = 0; i < width; ++i){
			vertices[columnOffset + i].Normal = vec3(0.0f, 1.0f, 0.0f);
			vertices[columnOffset + i].Tangent = vec3(1.0f, 0.0f, 0.0f);
			vertices[columnOffset + i].Bitangent = vec3(0.0f, 0.0f, -1.0f);
		}
		columnOffset += width;
	}
}



void Plane::GenerateUvCoordinates(Vertex* vertices, float textureWidth, float textureHeight, unsigned int width, unsigned int height){
	unsigned int i, j, columnOffset;
	columnOffset = 0;
	for (j = 0; j < height; ++j){
		for (i = 0; i < width; ++i){
			vertices[columnOffset + i].UvCoordinate = vec2(i * textureWidth, j * textureHeight);
		}
		columnOffset += width;
	}
}

/*
Corner for going right to going left
	01		02		03
	|	/	|	/	|
	11		12		13
	|	\	|	\	|
	21		22		23

	01 to 11 to 02 to 12 to...
	(actual corner starts here)
	...03 to 13 to 23 to 23 to 12 to 22...	<- Note that this creates a zero-area triangle (03 to 13 to 23). I'm unsure about how bad that is.
	(actual corner ended)
	...to 11 to 21

Corner for going from left to right
	01		02		03
	|	\	|	\	|
	11		12		13
	|	/	|	/	|
	21		22		23

	...13 to 03 to 02 to 12 to 01 to 11 to 21 to 12 to 22 to 13 to 23...

	In order for this to work, the trianglestrip must "start" at the second point,
	not the first one, as to follow up from the previous strip.
	This means that before any strips are generated, point 0 must be manually set.
*/

void Plane::GenerateIndices(GLuint* indices, unsigned int width, unsigned int height){
	unsigned int i, j;

	//Generate initial index
	i = 0;
	indices[i++] = 0;

	//And the rest
	for (j = 0; j < height; ++j){
		if (j % 2 == 0){
			StripRight(indices, width, j, i);	
		} else {
			StripLeft(indices, width, j, i);
		}
	}
}

void Plane::StripRight(GLuint* indices, unsigned int width, unsigned int row, unsigned int& index){
	unsigned int rowOffset = (width + 1);
	unsigned int totalOffset = rowOffset * row;
	unsigned int quad;

	//Generate strip
	for (quad = 0; quad < width; ++quad){
		indices[index++] = totalOffset + quad + rowOffset;	//Start bottom left
		indices[index++] = totalOffset + quad + 1;	//Go top right
	}

	//Generate stitch
	indices[index++] = totalOffset + quad + rowOffset;	//Bottom right

	//As you can see, a strip consists of (quads) * 2 + 1 indices
}

void Plane::StripLeft(GLuint* indices, unsigned int width, unsigned int row, unsigned int& index){
	unsigned int rowOffset = (width + 1);
	unsigned int totalOffset = rowOffset * row;
	unsigned int quad;

	//Generate strip
	for (quad = width; quad > 0; --quad){
		indices[index++] = totalOffset + quad + rowOffset;	//Start bottom right
		indices[index++] = totalOffset + quad - 1;	//Go top left
	}

	//Generate stitch
	indices[index++] = totalOffset + rowOffset;	//Bottom left

	//As you can see, a strip consists of (quads) * 2 + 1 indices
}