#ifndef ZEDDY_MOUSE_CONTROLS_H_
#define ZEDDY_MOUSE_CONTROLS_H_

#include <vector>

struct MouseButton {
public:
	bool Pressed, Released, Held;
	int Number;

	MouseButton(int number);
};



class MouseControls{
public:
	MouseControls();

	void Motion(int x, int y);
	void Click(int button);
	void Lift(int button);
	
	int AddButton(MouseButton* button);
	bool GetButton(int number, MouseButton** button);

	bool WasButtonPressed(int number);
	bool WasButtonReleased(int number);
	bool IsButtonHeld(int number);

	void SetOrigin(int xOrigin, int yOrigin);
	int getXMotion();
	int getYMotion();

	void Clear(void);

private:
	int _xMotion, _yMotion;
	int _xOrigin, _yOrigin;
	std::vector<MouseButton*> _buttons;
};

#endif