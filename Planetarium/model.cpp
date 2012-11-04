#include "model.h"
#include "window.h" 



Model::~Model(void){
	glDeleteBuffers(1, &_vboId);
	glDeleteBuffers(1, &_iboId);
	glDeleteVertexArrays(1, &_vaoId);
	Window::ExitOnGLError("destroy the buffer objects");
}



void Model::Draw(void){
	glBindVertexArray(_vaoId);
	Window::ExitOnGLError("bind the VAO for drawing purposes");

	glDrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_INT, (GLvoid*)0);
	Window::ExitOnGLError("draw the model");

	glBindVertexArray(0);
}



void Model::GenerateVao(const Vertex* vertices, const GLuint* indices, unsigned int vertexCount, unsigned int indexCount){
	_indexCount = indexCount;

	glGenVertexArrays(1, &_vaoId);	//Opprett en vertex tabell i OpenGL, legg referansen til den i BufferIds[0]
	Window::ExitOnGLError("generate the VAO");

	glBindVertexArray(_vaoId);	//Sett denne vertex tabell som nåværende
	Window::ExitOnGLError("bind the VAO");

	glGenBuffers(1, &_vboId);	//Generer buffer for VBO
	Window::ExitOnGLError("generate the buffer objects");

	glBindBuffer(GL_ARRAY_BUFFER, _vboId);	//Binder vertex buffer til grafikkort for videre bruk
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertexCount, vertices, GL_STATIC_DRAW);	//Pjåter data i VERTICES inn i gjeldende buffer
	Window::ExitOnGLError("buffer the vertices");

	unsigned int size = 0;
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)size);
	size += sizeof(vertices[0].Position);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)size);
	size += sizeof(vertices[0].Normal);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)size);
	size += sizeof(vertices[0].Tangent);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)size);
	size += sizeof(vertices[0].Bitangent);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)size);
	size += sizeof(vertices[0].UvCoordinate);
	Window::ExitOnGLError("set the VAO attributes");

	glEnableVertexAttribArray(0);	//Vertex shader vPosition
	glEnableVertexAttribArray(1);	//Vertex shader vNormal
	glEnableVertexAttribArray(2);	//Vertex shader vUv
	glEnableVertexAttribArray(3);	//Vertex shader vTangent
	glEnableVertexAttribArray(4);	//Vertex shader vBitangent
	Window::ExitOnGLError("enable vertex attributes");

	glGenBuffers(1, &_iboId);	//Generer buffer for IBO

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iboId);	//Bind indeksbuffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLint)*indexCount, indices, GL_STATIC_DRAW);	//Pjåt inn indeksdata
	Window::ExitOnGLError("bind the IBO to the VAO");

	glBindVertexArray(0);	//Kutt binding
}


// Note that this function will only work if indices represent a model drawn by GL_TRIANGLES

void Model::GenerateNormals(Vertex* vertices, const GLuint* indices, unsigned int vertexCount, unsigned int indexCount){
	vec3* normals = new vec3[vertexCount];
	unsigned int* divisors = new unsigned int[vertexCount];

	unsigned int i;

	// Nullset the arrays
	for (i = 0; i < vertexCount; ++i){
		normals[i] = vec3(0.0, 0.0, 0.0);
		divisors[i] = 0;
	}

	GLuint i1, i2, i3;

	for (unsigned int i = 0; i < indexCount; i += 3){
		i1 = indices[i];
		i2 = indices[i + 1];
		i3 = indices[i + 2];

		normals[i1] += GenerateNormal(vertices[i1], vertices[i2], vertices[i3]);
		normals[i2] += GenerateNormal(vertices[i2], vertices[i1], vertices[i3]);
		normals[i3] += GenerateNormal(vertices[i3], vertices[i1], vertices[i2]);

		divisors[i1]++;
		divisors[i2]++;
		divisors[i3]++;
	}

	// Average the normals
	for (i = 0; i < vertexCount; ++i){
		if (divisors[i] > 1)
			normals[i] /= divisors[i];
		vertices[i].Normal = glm::normalize(normals[i]);
	}

	delete[](normals);
	delete[](divisors);
}

//We don't normalize it here because we want larger polygons to have a heavier weight in on the final result
vec3 Model::GenerateNormal(Vertex& v1, Vertex& v2, Vertex& v3){
	vec3 q1 = vec3(v2.Position - v1.Position);
	vec3 q2 = vec3(v3.Position - v1.Position);
	return glm::cross(q1, q2);
}

// We will be going through each index, three at a time.
// Then we will compare the vertices referenced by those indexes with eachother,
// and calculate the tangents each point have based on the UV-coordinates between them.
// 
// The result will be added to an array with the vertex' index.
// At the end, the total tangent will be divided by the amount of times each vertex
// has appeared in a triangle, averaging it out.
void Model::GenerateTangents(Vertex* vertices, const GLuint* indices, unsigned int vertexCount, unsigned int indexCount){
	vec3* tangents = new vec3[vertexCount];
	unsigned int* divisors = new unsigned int[vertexCount];
	unsigned int i;

	// Nullset the arrays
	for (i = 0; i < vertexCount; ++i){
		tangents[i] = vec3(0.0, 0.0, 0.0);
		divisors[i] = 0;
	}

	GLuint i1, i2, i3;

	for (unsigned int i = 0; i < indexCount; i += 3){
		i1 = indices[i];
		i2 = indices[i + 1];
		i3 = indices[i + 2];

		tangents[i1] += GenerateTangent(vertices[i1], vertices[i2], vertices[i3]);
		tangents[i2] += GenerateTangent(vertices[i2], vertices[i1], vertices[i3]);
		tangents[i3] += GenerateTangent(vertices[i3], vertices[i1], vertices[i2]);

		divisors[i1]++;
		divisors[i2]++;
		divisors[i3]++;
	}

	// Average the tangents
	for (i = 0; i < vertexCount; ++i){
		if (divisors[i] > 1)
			tangents[i] /= divisors[i];
		vertices[i].Tangent = glm::normalize(tangents[i]);
	}

	delete[] tangents;
	delete[] divisors;
}

// http://www.terathon.com/code/tangent.html
vec3 Model::GenerateTangent(Vertex& v1, Vertex& v2, Vertex& v3){
	vec3 q1 = vec3(v2.Position - v1.Position);
	vec3 q2 = vec3(v3.Position - v1.Position);

	vec2 uv1 = v2.UvCoordinate - v1.UvCoordinate;
	vec2 uv2 = v3.UvCoordinate - v1.UvCoordinate;

	mat2 uvMatrix = mat2(uv2.t, -uv2.s, -uv1.t, uv1.s);
	//mat3x2 qMatrix = mat3x2(vec2(q1.x, q2.x), vec2(q1.y, q2.y), vec2(q1.z, q2.z));
	mat2x3 qMatrix = mat2x3(vec3(q1.x, q1.y, q1.z), vec3(q2.x, q2.y, q2.z));

	float inversion = (1.0f / (uv1.s * uv2.t - uv2.s * uv1.t));

	//mat3x2 tangents = inversion * uvMatrix * qMatrix;
	mat2x3 tangents = qMatrix * uvMatrix;
	//return vec3(tangents[0][0], tangents[1][0], tangents[2][0]);
	return tangents[0];
}

void Model::GenerateBitangents(Vertex* vertices, unsigned int vertexCount){
	for (unsigned int i = 0; i < vertexCount; ++i){
		vertices[i].Bitangent = glm::normalize(glm::cross(vertices[i].Normal, vertices[i].Tangent));
	}
}