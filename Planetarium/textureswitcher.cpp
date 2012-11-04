#include "textureswitcher.h"
#include "main.h"

TextureSwitcher::TextureSwitcher(ModelNode* node) : EncapsulationNode(node){
	_switch1 = _controls.AddKey(new Key('1', false));
	_switch2 = _controls.AddKey(new Key('2', false));
	_index1 = _index2 = 0;
	RegisterKeyboardControls(&_controls);
}



void TextureSwitcher::AddTextures(Texture* texture, Texture* normalMap){
	_textures.push_back(texture);
	_textures.push_back(normalMap);
}



void TextureSwitcher::Update(float secondsPassed){
	ModelNode* mNode = (ModelNode*) _node;

	if (_controls.WasKeyPressed(_switch1)){
		_index1 = (_index1 + 2) % _textures.size();
		mNode->GetTextures()->Replace(0, _textures[_index1]);
		mNode->GetNormalMaps()->Replace(0, _textures[_index1 + 1]);
	}
	if (_controls.WasKeyPressed(_switch2)){
		_index2 = (_index2 + 2) % _textures.size();
		mNode->GetTextures()->Replace(1, _textures[_index2]);
		mNode->GetNormalMaps()->Replace(1, _textures[_index2 + 1]);
	}

	_controls.Clear();
	EncapsulationNode::Update(secondsPassed);
}
