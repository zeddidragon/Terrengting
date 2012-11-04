#include "textureset.h"
#include "window.h"

int TextureSet::Add(Texture* texture, float scale){
	_textures.push_back(texture);
	_scales.push_back(1.0f / scale);
	return _textures.size() - 1;
}

bool TextureSet::Remove(unsigned int index){
	if (_textures.size() > index){
		_textures.erase(_textures.begin() + index);
		_scales.erase(_scales.begin() + index);
		return true;
	} else {
		return false;
	}
}

bool TextureSet::Replace(unsigned int index, Texture* texture){
	if (index < _textures.size()){
		_textures[index] = texture;
		return true;
	} else {
		return false;
	}
}

unsigned int TextureSet::Size(void){
	return _textures.size();
}

int TextureSet::IndexOf(Texture* texture){
	return IndexOf(texture, 0);
}

int TextureSet::IndexOf(Texture* texture, unsigned int fromIndex){
	for (auto i = _textures.begin() + fromIndex; i < _textures.end(); ++i){
		if (*i == texture){
			return i - _textures.begin();
		}
	}
	return -1;
}

Texture* TextureSet::GetTexture(unsigned int index){
	return _textures[index];
}

float TextureSet::GetScale(unsigned int index){
	return _scales[index];
}

void TextureSet::Bind(Shader* shader){
	GLint samplersLocation = shader->GetUniformLocation("TextureSamplers");
	GLint scalesLocation = shader->GetUniformLocation("TextureScales");
	GLint countLocation = shader->GetUniformLocation("TextureCount");

	glUniform1i(countLocation, _textures.size());

	for (unsigned int i = 0; i < _textures.size(); ++i){
		glActiveTexture(GL_TEXTURE0 + i);
		_textures[i]->Bind();
		glUniform1i(samplersLocation + i, i);
		glUniform1f(scalesLocation + i, _scales[i]);
	}

	glActiveTexture(GL_TEXTURE0);
}

void TextureSet::BindNormalMap(Shader* shader, unsigned int offset){
	GLint samplersLocation = shader->GetUniformLocation("NormalSamplers");
	GLint scalesLocation = shader->GetUniformLocation("NormalMapScales");
	GLint countLocation = shader->GetUniformLocation("NormalMapCount");

	glUniform1i(countLocation, _textures.size());

	for (unsigned int i = 0; i < _textures.size(); ++i){
		glActiveTexture(GL_TEXTURE0 + offset + i);
		_textures[i]->Bind();
		glUniform1i(samplersLocation + i, offset + i);
		glUniform1f(scalesLocation + i, _scales[i]);
	}

	glActiveTexture(GL_TEXTURE0);
}

void TextureSet::Unbind(void){
	for (unsigned int i = 0; i < _textures.size(); ++i){
		glActiveTexture(GL_TEXTURE0 + i);
		_textures[i]->Unbind();
	}
}

void TextureSet::UnbindNormalMap(unsigned int offset){
	for (unsigned int i = 0; i < _textures.size(); ++i){
		glActiveTexture(GL_TEXTURE0 + i + offset);
		_textures[i]->Unbind();
	}
}