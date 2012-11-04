#include "eulernode.h"



EulerNode::EulerNode(Model* model, Material* material, TextureSet* textures) : ModelNode(model, material, textures){
	Position = vec3(0.0f, 0.0f, 0.0f);
	Speed = vec3(0.0f, 0.0f, 0.0f);
}



void EulerNode::Update(const float secondsPassed) {
	Position += Speed * secondsPassed;

	ModelNode::Update(secondsPassed);
}



void EulerNode::Render(Shader* shader, const vector<Light*>* lights, const mat4& viewMatrix, const mat4& parentMatrix){
	mat4 modelMatrix = mat4(1.0f);
	modelMatrix = glm::translate(parentMatrix, Position);	//Apply movement

	ModelNode::Render(shader, lights, viewMatrix, modelMatrix);
}



vec3 EulerNode::GetPosition(void){return Position;}
void EulerNode::SetPosition(vec3 position){Position = position;}
void EulerNode::MoveX(float amount){Position.x += amount;}
void EulerNode::MoveY(float amount){Position.y += amount;}
void EulerNode::MoveZ(float amount){Position.z += amount;}