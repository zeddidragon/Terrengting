#include "orientationnode.h"

OrientationNode::OrientationNode(void){
	Pitch = Yaw = Roll = 0.0f;
}

void OrientationNode::ConstrainAngle(float& angle){
	if (angle < 0){
		angle += 360;
	} else if (angle > 360){
		angle -= 360;
	}
}