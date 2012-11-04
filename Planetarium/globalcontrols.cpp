#include "globalcontrols.h"
#include "main.h"

GlobalControls::GlobalControls(void){
	_quitKey = _input.AddKey(new Key(27, false));
	RegisterKeyboardControls(&_input);
}

void GlobalControls::Update(float){
	if (_input.IsKeyHeld(_quitKey)){
		exit(0);
	}
}