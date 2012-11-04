#ifndef ZEDDY_KEYBOARD_CONTROLS_H_
#define ZEDDY_KEYBOARD_CONTROLS_H_

#include <vector>

struct Key{
public:
	bool Pressed, Released, Held;
	int Mapping;
	bool Special;

	Key(const int mapping, const bool special);
};

class KeyboardControls{
public:
	KeyboardControls(void);
	KeyboardControls(std::vector<Key*> keys);

	int AddKey(Key* key);
	bool GetKey(const int mapping, const bool special, Key** key);
	bool GetKey(const int id, Key** key);

	void KeyPressed(int code, bool special);
	void KeyReleased(int code, bool special);
	void CharPressed(const unsigned char key);
	void CharReleased(const unsigned char key);
	void SpecialPressed(const int key);
	void SpecialReleased(const int key);
	
	void Clear();

	bool IsKeyHeld(const int id);
	bool WasKeyPressed(const int id);
	bool WasKeyReleased(const int id);

private:
	std::vector<Key*> _keys;
};

#endif