#include "mousenode.h"
#include "main.h"


MouseNode::MouseNode(Node* node, int mouseButton, bool yIsVertical) : EncapsulationNode(node){
	_controls = new MouseControls();
	_mouseButton = _controls->AddButton(new MouseButton(mouseButton));
	RegisterMouseControls(_controls);
	_yIsVertical = yIsVertical;
}



MouseNode::~MouseNode(void){
	delete _controls;
}



void MouseNode::Update(float secondsPassed){
	const float SENSITIVITY = 0.1f;

	if (_controls->IsButtonHeld(_mouseButton)){
		_node->MoveX(SENSITIVITY * _controls->getXMotion());
		if (_yIsVertical){
			_node->MoveY(-SENSITIVITY * _controls->getYMotion());
		} else {
			_node->MoveZ(SENSITIVITY * _controls->getYMotion());
		}
	}

	_controls->Clear();
	EncapsulationNode::Update(secondsPassed);
}