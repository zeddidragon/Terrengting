#include <iostream>

#include "lodepng.h"
#include "texture.h"
#include "window.h"

Texture::Texture(char* filepath){
	unsigned error = lodepng::decode(_data, _width, _height, filepath);

	if (error)
		std::cout << "png decoder error " << error << ": " <<
			lodepng_error_text(error) <<
		std::endl;
	 
	glGenTextures(1, &_glId);
	glBindTexture(GL_TEXTURE_2D, _glId);

	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _data.data());
	glGenerateMipmap(GL_TEXTURE_2D);

	Unbind();
}

Texture::~Texture(void){
}

void Texture::Bind(void){	
	glBindTexture(GL_TEXTURE_2D, _glId);
}

void Texture::Unbind(void){
	glBindTexture(GL_TEXTURE_2D, 0);
	Window::ExitOnGLError("Unbind the texture");
}

float Texture::DataAt(vec2 uv){
	float x, y;
	x = uv.x * _width;
	y = uv.y * _height;

	int xMin = (int)glm::floor(x);
	int xMax = (int)glm::ceil(x);

	int yMin = (int)glm::floor(y);
	int yMax = (int)glm::ceil(y);

	float xOffset = x - xMin;
	float yOffset = y - yMin;

	float topLeft = _data[(xMin + yMin * _width) * 4];
	float topRight = _data[(xMax + yMin * _width) * 4];
	float bottomLeft = _data[(xMin + yMax * _width) * 4];
	float bottomRight = _data[(xMax + yMax * _width) * 4];

	float ret = 0.0f;

	ret += topLeft * (xOffset + yOffset);
	ret += topRight * ((1.0f - xOffset) + yOffset);
	ret += bottomLeft * (xOffset + (1.0f - yOffset));
	ret += bottomRight * (1.0f - (xOffset + yOffset));

	return ret / 256.0f;
}

void Texture::PrintData(void){
	int index = 0;
	for (unsigned int j = 0; j < _height; ++j){
		for (unsigned int i = 0; i < _width; ++i){
			cout << (int) _data[index++] << ",";
		}
		cout << endl;
	}
}