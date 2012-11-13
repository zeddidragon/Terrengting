#include "modelnode.h"
#include "window.h"
#include "matrixmath.h"

ModelNode::ModelNode(Model* model, Material* material, TextureSet* textures){
	_model = model;
	_material = material;
	_textures = textures;
	_normalMaps = 0;

	_children = std::vector<Node*>();
	Size = 1;

	PitchSpeed = YawSpeed = RollSpeed = 0.0f;
}



void ModelNode::SetTextures(TextureSet* textures){
	_textures = textures;
}
void ModelNode::SetNormalMaps(TextureSet* normalMaps){
	_normalMaps = normalMaps;
}
TextureSet* ModelNode::GetTextures(void){
	return _textures;
}
TextureSet* ModelNode::GetNormalMaps(void){
	return _normalMaps;
}



ModelNode::~ModelNode(){
	for (unsigned int i = 0; i < _children.size(); ++i){
		delete _children.at(i);
	}
}



void ModelNode::Update(const float secondsPassed){
	Pitch += PitchSpeed;
	Yaw += YawSpeed;
	Roll += RollSpeed;

	ConstrainAngle(Pitch);
	ConstrainAngle(Yaw);
	ConstrainAngle(Roll);

	Node::Update(secondsPassed);
}


void ModelNode::Render(Shader* shader, const vector<Light*>* lights, const mat4& viewMatrix, const mat4& parentMatrix){
	Node::Render(shader, lights, viewMatrix, parentMatrix);

	mat4 modelMatrix = parentMatrix;

	modelMatrix = glm::scale(modelMatrix, vec3(Size, Size, Size));	//Apply scale.
	modelMatrix = modelMatrix * MatrixMath::OrientationMatrix(Pitch, Yaw, Roll); // Apply Orientation.

	mat4 modelView = viewMatrix * modelMatrix;
	mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelView)));

	GLint modelViewLocation = shader->GetUniformLocation("ModelView");
	GLint normalMatrixLocation = shader->GetUniformLocation("NormalMatrix");
	glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, value_ptr(modelView));	//Bind model matrix.
	glUniformMatrix3fv(normalMatrixLocation, 1, GL_FALSE, value_ptr(normalMatrix));	//Bind normal matrix.

	for (unsigned int i = 0; i < lights->size(); ++i){
		lights->at(i)->Bind(shader, _material, i, viewMatrix);
	}
	
	_textures->Bind(shader);
	if (_normalMaps != 0)
		_normalMaps->BindNormalMap(shader, _textures->Size());

	_model->Draw();
	_textures->Unbind();
	_normalMaps->UnbindNormalMap(_textures->Size());
}



void ModelNode::AddChild(Node* child){
	_children.push_back(child);
}