#include "encapsulationnode.h"

EncapsulationNode::EncapsulationNode(Node* node){
	_node = node;
}
void EncapsulationNode::Update(float secondsPassed){
	_node->Update(secondsPassed);
}
void EncapsulationNode::Render(Shader* shader, const vector<Light*>* lights, const mat4& projectionMatrix, const mat4& viewMatrix){
	_node->Render(shader, lights, projectionMatrix, viewMatrix);
}
vec3 EncapsulationNode::GetPosition(void){
	return _node->GetPosition();
}
void EncapsulationNode::SetPosition(vec3 position){
	_node->SetPosition(position);
}
void EncapsulationNode::MoveX(float amount){
	_node->MoveX(amount);
}
void EncapsulationNode::MoveY(float amount){
	_node->MoveY(amount);
}
void EncapsulationNode::MoveZ(float amount){
	_node->MoveZ(amount);
}