#ifndef ZEDDY_ORIENTATION_NODE_H_
#define ZEDDY_ORIENTATION_NODE_H_

#include "node.h"

class OrientationNode : public Node{
public:
	OrientationNode(void);

	float Pitch, Yaw, Roll;
protected:
	void ConstrainAngle(float& angle);
};

#endif