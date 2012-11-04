#ifndef ZEDDY_TEXTURESET_H_
#define ZEDDY_TEXTURESET_H_

#include <vector>
#include <gl\glew.h>

#include "texture.h"
#include "shader.h"

class TextureSet{
public:
	int Add(Texture* texture, float scale);
	bool Remove(unsigned int index);
	bool Replace(unsigned int index, Texture* texture);
	int IndexOf(Texture* texture);
	int IndexOf(Texture* texture, unsigned int fromIndex);
	Texture* GetTexture(unsigned int index);
	float GetScale(unsigned int index);

	void Bind(Shader* shader);
	void BindNormalMap(Shader* shader, unsigned int offset);
	void Unbind(void);
	void UnbindNormalMap(unsigned int offset);
	unsigned int Size(void);
private:
	std::vector<Texture*> _textures;
	std::vector<float> _scales;
};

#endif