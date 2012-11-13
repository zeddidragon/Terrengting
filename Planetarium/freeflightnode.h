#ifndef ZEDDY_FREEFLIGHTNODE_H_
#define ZEDDY_FREEFLIGHTNODE_H_

#include "main.h"
#include "keyboardcontrols.h"
#include "mousecontrols.h"

#include "orientationnode.h"

class FreeFlightNode : public OrientationNode {
public:
	FreeFlightNode(void);
	virtual ~FreeFlightNode(void);

	virtual void Update(float secondsPassed) override;
	virtual vec3 GetPosition(void) override;
	virtual void SetPosition(vec3 position) override;
	virtual void MoveX(float amount) override;
	virtual void MoveY(float amount) override;
	virtual void MoveZ(float amount) override;
private:
	inline bool IsKeyHeld(int);

	KeyboardControls _keyboard;
	MouseControls _mouse;
	int _keys[6];
	vec3 _position;
};

#endif