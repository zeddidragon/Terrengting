#ifndef ZEDDY_TEXTURE_SWITCHER_H_
#define ZEDDY_TEXTURE_SWITCHER_H_

#include <vector>

#include "texture.h"
#include "modelnode.h"
#include "encapsulationnode.h"
#include "keyboardcontrols.h"

class TextureSwitcher : public EncapsulationNode {
public:
	TextureSwitcher(ModelNode* node);

	void Update(float secondsPassed) override;
	void AddTextures(Texture* texture, Texture* normal);

private:
	KeyboardControls _controls;
	int _switch1, _switch2;
	vector<Texture*> _textures;
	int _index1, _index2;
};

#endif