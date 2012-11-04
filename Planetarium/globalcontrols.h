#ifndef ZEDDY_GLOBAL_CONTROLS_H_
#define ZEDDY_GLOBAL_CONTROLS_H_

#include "node.h"
#include "keyboardcontrols.h"

class GlobalControls : public Node {
public:
	GlobalControls(void);
	virtual void Update(float) override;
private:
	KeyboardControls _input;
	int _quitKey;
};

#endif