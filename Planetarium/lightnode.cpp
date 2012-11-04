#include "lightnode.h"

LightNode::LightNode(PointLight* light, Node* node) : EncapsulationNode(node){
	_light = light;
	Update(0.0f);
}



void LightNode::Update(float secondsPassed){
	EncapsulationNode::Update(secondsPassed);
	_light->Position = vec4(_node->GetPosition(), 1.0f);
}