#include "cameranode.h"

CameraNode::CameraNode(OrientationNode* node, Camera* camera) : EncapsulationNode(node){
	_camera = camera;
}

void CameraNode::Update(float secondsPassed){
	EncapsulationNode::Update(secondsPassed);

	OrientationNode* oNode = (OrientationNode*) _node;

	_camera->MoveTo(vec4(-oNode->GetPosition(), 1.0f));
	_camera->LookTo(oNode->Pitch, oNode->Yaw, oNode->Roll);
}