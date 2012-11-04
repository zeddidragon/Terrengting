#ifndef ZEDDY_PLAYER_H
#define ZEDDY_PLAYER_H

#include "mousecontrols.h"
#include "keyboardcontrols.h"
#include "camera.h"
#include "node.h"

class Player : public Node {
public:
	Player(Camera* camera);
	~Player(void);

	virtual void Update(float secondsPassed) override;
	virtual vec3 GetPosition(void) override;
	virtual void SetPosition(vec3 position) override;
	virtual void MoveX(float amount) override;
	virtual void MoveY(float amount) override;
	virtual void MoveZ(float amount) override;

protected:
	Camera* _camera;
	KeyboardControls* _keyboard;
	MouseControls* _mouse;
};

#endif