#include "mousecontrols.h"


MouseButton::MouseButton(int number){
	Pressed = Released = Held = false;
	Number = number;
}



MouseControls::MouseControls(){
	_xMotion = 0;
	_yMotion = 0;
}



void MouseControls::SetOrigin(int xOrigin, int yOrigin){
	_xOrigin = xOrigin;
	_yOrigin = yOrigin;
}



void MouseControls::Motion(int x, int y){
	_xMotion += x - _xOrigin;
	_yMotion += y - _yOrigin;
}



void MouseControls::Clear(void){
	_xMotion = 0;
	_yMotion = 0;
	for (auto i = _buttons.begin(); i < _buttons.end(); ++i){
		(*i)->Pressed = false;
		(*i)->Released = false;
	}
}



int MouseControls::getXMotion(void){
	return _xMotion;
}



int MouseControls::getYMotion(void){
	return _yMotion;
}



void MouseControls::Click(int number){
	MouseButton* button = 0;
	if (GetButton(number, &button) && !button->Held){
		button->Held = true;
		button->Pressed = true;
	}
}



void MouseControls::Lift(int number){
	MouseButton* button = 0;
	if (GetButton(number, &button) && button->Held){
		button->Held = false;
		button->Released = false;
	}
}



int MouseControls::AddButton(MouseButton* button){
	_buttons.push_back(button);
	return _buttons.size() - 1;
}



bool MouseControls::GetButton(int number, MouseButton** button){
	for (auto i = _buttons.begin(); i < _buttons.end(); ++i){
		if ((*i)->Number == number){
			*button = *i;
			return true;
		}
	}
	return false;
}



bool MouseControls::IsButtonHeld(int id){
	return _buttons.at(id)->Held;
}
bool MouseControls::WasButtonPressed(int id){
	return _buttons.at(id)->Pressed;
}
bool MouseControls::WasButtonReleased(int id){
	return _buttons.at(id)->Released;
}