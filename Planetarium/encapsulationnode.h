#ifndef ZEDDY_ENCAPSULATION_NODE_H_
#define ZEDDY_ENCAPSULATION_NODE_H_

#include "node.h"

class EncapsulationNode : public Node {
public:
	virtual void Update(float secondsPassed) override;
	virtual void Render(Shader*,const vector<Light*>*,const mat4&,const mat4&) override;
	virtual vec3 GetPosition(void) override;
	virtual void SetPosition(vec3 position) override;
	virtual void MoveX(float amount) override;
	virtual void MoveY(float amount) override;
	virtual void MoveZ(float amount) override;
protected:
	EncapsulationNode(Node* node);
	Node* _node;
};

#endif