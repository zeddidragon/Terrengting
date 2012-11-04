#include "keyboardcontrols.h"

Key::Key(int mapping, bool special){
	Mapping = mapping;
	Special = special;
	Held = false;
	Pressed = false;
	Released = false;
}



KeyboardControls::KeyboardControls(void){
}



KeyboardControls::KeyboardControls(std::vector<Key*> keys){
	_keys = keys;
}



int KeyboardControls::AddKey(Key* key){
	_keys.push_back(key);
	return _keys.size() - 1;
}



bool KeyboardControls::GetKey(int mapping, bool special, Key** key){
	for (int i = 0; i < _keys.size(); ++i){
		if (_keys.at(i)->Special == special && _keys.at(i)->Mapping == mapping){
			*key = _keys.at(i);
			return true;
		}
	}
	return false;
}



bool KeyboardControls::GetKey(int id, Key** key){
	if (id < _keys.size()){
		*key = _keys.at(id);
		return true;
	} else {
		return false;
	}
}



void KeyboardControls::KeyPressed(int keyCode, bool special){
	Key* key = 0;
	if (GetKey(keyCode, special, &key) && !key->Held){
		key->Pressed = true;
		key->Held = true;
	}
}



void KeyboardControls::KeyReleased(int keyCode, bool special){
	Key* key = 0;
	if (GetKey(keyCode, special, &key)){
		key->Released = true;
		key->Held = false;
	}
}



void KeyboardControls::Clear(void){
	for (int i = 0; i < _keys.size(); ++i){
		_keys.at(i)->Pressed = false;
		_keys.at(i)->Released = false;
	}
}



void KeyboardControls::CharPressed(unsigned char keyChar){
	KeyPressed(keyChar, false);
}
void KeyboardControls::CharReleased(unsigned char keyChar){
	KeyReleased(keyChar, false);
}
void KeyboardControls::SpecialPressed(int keyCode){
	KeyPressed(keyCode, true);
}
void KeyboardControls::SpecialReleased(int keyCode){
	KeyReleased(keyCode, true);
}



bool KeyboardControls::IsKeyHeld(int id){
	return _keys.at(id)->Held;
}
bool KeyboardControls::WasKeyPressed(int id){
	return _keys.at(id)->Pressed;
}
bool KeyboardControls::WasKeyReleased(int id){
	return _keys.at(id)->Released;
}