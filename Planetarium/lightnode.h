#ifndef ZEDDY_LIGHT_NODE_H_
#define ZEDDY_LIGHT_NODE_H_

#include "pointlight.h"
#include "encapsulationnode.h"

class LightNode : public EncapsulationNode{
public:
	LightNode(PointLight* light, Node* node);

	virtual void Update(float secondsPassed) override;
private:
	PointLight* _light;
	vec4 _previousPosition;
};

#endif