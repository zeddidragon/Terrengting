#include <stdlib.h>
#include <time.h>
#include <glm\glm.hpp>

#include "matrixmath.h"
#include "grass.h"


const float PI = 3.14159265359f;


Grass::Grass(Model* model, Material* material, TextureSet* textures, float quadWidth, float quadHeight, float maxHeight, HeightMap* heightMap, unsigned int count)
	: ModelNode(model, material, textures){
	_model = model;
	_count = count;
	_positions = new vec4[_count];
	_yaws = new float[_count];

	vec4 scale = vec4(quadWidth * heightMap->Width(), maxHeight, quadHeight * heightMap->Height(), 1.0f);
	
	srand(time(NULL));

	for (unsigned int i = 0; i < _count; ++i){
		Randomize(i);
		AdjustHeight(i, heightMap);
		_positions[i] *= scale;
	}
}



void Grass::Randomize(unsigned int index){
	float x = (float)rand() / (float)RAND_MAX - 0.5f;
	float y = (float)rand() / (float)RAND_MAX - 0.5f;
	_positions[index] = vec4(x, 0.0f, y, 1.0f);

	_yaws[index] = ((float)rand()/(float)RAND_MAX - 0.5f) * 2.0f * 3.14f;
}



//Linear filtering of the height between the vertices closest to the point
void Grass::AdjustHeight(unsigned int index, HeightMap* heightMap){
	//Position can range from -0.5 to 0.5, convert to range 0 to 1
	vec2 position = vec2(_positions[index].x, _positions[index].z) + 0.5f;

	unsigned int width = heightMap->Width();

	position.x *= width;
	position.y *= heightMap->Height();

	unsigned int west =		glm::floor(position.x);
	unsigned int east =		glm::ceil(position.x);
	unsigned int north =	glm::floor(position.y);
	unsigned int south =	glm::ceil(position.y);

	vec2 offset = position - vec2(west, north);

	float nw = heightMap->Map[west + north * width];
	float ne = heightMap->Map[east + north * width];
	float sw = heightMap->Map[west + south * width];
	float se = heightMap->Map[east + south * width];

	_positions[index].y = (nw + ne + sw + se) / 4.0f;
}



void Grass::Render(Shader* shader,const vector<Light*>* lights,const mat4& viewMatrix,const mat4& parentMatrix){

	Node::Render(shader, lights, viewMatrix, parentMatrix);

	GLint modelViewLocation = shader->GetUniformLocation("ModelView");
	GLint normalMatrixLocation = shader->GetUniformLocation("NormalMatrix");

	mat4 modelMatrix;
	mat4 modelView;
	mat3 normalMatrix;

	for (unsigned int i = 0; i < lights->size(); ++i){
		lights->at(i)->Bind(shader, _material, i, viewMatrix);
	}

	GLint emittedLocation = shader->GetUniformLocation("MaterialEmitted");
	glUniform4fv(emittedLocation, 1, glm::value_ptr(_material->Emitted));

	_textures->Bind(shader);
	if (_normalMaps){
		_normalMaps->BindNormalMap(shader, _textures->Size());
	} else {
		GLint countLocation = shader->GetUniformLocation("NormalMapCount");
		glUniform1i(countLocation, 0);
	}

	//glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	for (unsigned int i = 0; i < _count; ++i){
		modelMatrix = parentMatrix;
		modelMatrix = glm::translate(modelMatrix, vec3(_positions[i])); // Apply Position
		modelMatrix = modelMatrix * MatrixMath::YawMatrix(_yaws[i]); // Apply Orientation.

		modelView = viewMatrix * modelMatrix;
		normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelView)));

		glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, value_ptr(modelView));	//Bind model matrix.
		glUniformMatrix3fv(normalMatrixLocation, 1, GL_FALSE, value_ptr(normalMatrix));	//Bind normal matrix.

		_model->Draw();
	}

	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	_textures->Unbind();
	if (_normalMaps){
		_normalMaps->UnbindNormalMap(_textures->Size());
	}
}