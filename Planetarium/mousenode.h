#ifndef ZEDDY_MOUSE_NODE_H_
#define ZEDDY_MOUSE_NODE_H_

#include "encapsulationnode.h"
#include "mousecontrols.h"

class MouseNode : public EncapsulationNode {
public:
	MouseNode(Node* node, int mouseButton, bool yIsVertical);
	~MouseNode(void);

	virtual void Update(float secondsPassed) override;
private:
	MouseControls* _controls;
	int _mouseButton;
	bool _yIsVertical;
};

#endif