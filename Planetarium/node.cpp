#include "node.h"

void Node::Update(float secondsPassed){
	for (unsigned int i = 0; i < _children.size(); ++i){
		_children.at(i)->Update(secondsPassed);
	}
}

void Node::Render(Shader* shader, const vector<Light*>* lights, const mat4& viewMatrix, const mat4& modelMatrix){
	for (unsigned int i = 0; i < _children.size(); ++i){
		_children.at(i)->Render(shader, lights, viewMatrix, modelMatrix);
	}
}