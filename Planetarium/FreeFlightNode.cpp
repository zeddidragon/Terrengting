#include "freeflightnode.h"
#include "matrixmath.h"

enum KEYS {
	THROTTLE, REVERSE, LEFT, RIGHT, ASCEND, DESCEND
};

const float MOVEMENT_SPEED = 10.0f;
const float MOUSE_SENSITIVITY = 0.01f;

FreeFlightNode::FreeFlightNode(void){
	_keys[THROTTLE] = _keyboard.AddKey(new Key('w', false));
	_keys[REVERSE]	= _keyboard.AddKey(new Key('s', false));
	_keys[LEFT]		= _keyboard.AddKey(new Key('a', false));
	_keys[RIGHT]	= _keyboard.AddKey(new Key('d', false));
	_keys[ASCEND]	= _keyboard.AddKey(new Key(' ', false));
	_keys[DESCEND]	= _keyboard.AddKey(new Key('c', false));

	RegisterKeyboardControls(&_keyboard);
	RegisterMouseControls(&_mouse);

	_position = vec3(0.0f);
}

FreeFlightNode::~FreeFlightNode(void){
	UnregisterKeyboardControls(&_keyboard);
	UnregisterMouseControls(&_mouse);
	OrientationNode::~OrientationNode();
}

void FreeFlightNode::Update(float secondsPassed){
	vec3 movement = vec3(0.0f);

	if (IsKeyHeld(THROTTLE)){
		movement.z = 1;
	} else if (IsKeyHeld(REVERSE)){
		movement.z = -1;
	}

	if (IsKeyHeld(RIGHT)){
		movement.x = -1;
	} else if (IsKeyHeld(LEFT)){
		movement.x = 1;
	}

	if (IsKeyHeld(ASCEND)){
		movement.y = -1;
	} else if (IsKeyHeld(DESCEND)){
		movement.y = 1;
	}

	if (movement != vec3(0.0f)){
		movement = glm::normalize(movement) * MOVEMENT_SPEED;
	}

	Yaw += _mouse.getXMotion() * MOUSE_SENSITIVITY;
	Pitch += _mouse.getYMotion() * MOUSE_SENSITIVITY;
	Pitch = glm::clamp(Pitch, -1.5f, 1.5f);
	_mouse.Clear();

	mat3 orientationMatrix = mat3(MatrixMath::OrientationMatrix(Pitch, Yaw, Roll));
	movement = movement * orientationMatrix;
	_position += movement * secondsPassed;
}

inline bool FreeFlightNode::IsKeyHeld(int key){
	return _keyboard.IsKeyHeld(_keys[key]);
}



vec3 FreeFlightNode::GetPosition(void){
	return _position;
}
void FreeFlightNode::SetPosition(vec3 position){
	_position = position;
}
void FreeFlightNode::MoveX(float amount){
	_position.x += amount;
}
void FreeFlightNode::MoveY(float amount){
	_position.y += amount;
}
void FreeFlightNode::MoveZ(float amount){
	_position.z += amount;
}