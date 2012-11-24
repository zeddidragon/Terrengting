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

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

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

vec4 Texture::PixelAt(vec2 uv){
	float x, y;
	x = uv.x * _width;
	y = uv.y * _height;

	int xMin = (int)glm::floor(x);
	int xMax = (int)glm::ceil(x);

	int yMin = (int)glm::floor(y);
	int yMax = (int)glm::ceil(y);

	float xOffset = x - xMin;
	float yOffset = y - yMin;

	unsigned int iTopLeft = (xMin + yMin * _width) * 4;
	unsigned int iTopRight = (xMax + yMin * _width) * 4;
	unsigned int iBottomLeft = (xMin + yMax * _width) * 4;
	unsigned int iBottomRight = (xMax + yMax * _width) * 4;

	vec4 vTopLeft = vec4(_data[iTopLeft], _data[iTopLeft + 1], _data[iTopLeft + 2], _data[iTopLeft + 3]);
	vec4 vTopRight = vec4(_data[iTopRight], _data[iTopRight + 1], _data[iTopRight + 2], _data[iTopRight + 3]);
	vec4 vBottomLeft = vec4(_data[iBottomLeft], _data[iBottomLeft + 1], _data[iBottomLeft + 2], _data[iBottomLeft + 3]);
	vec4 vBottomRight = vec4(_data[iBottomRight], _data[iBottomRight + 1], _data[iBottomRight + 2], _data[iBottomRight + 3]);

	vec4 ret = vec4(0.0f);

	ret += vTopLeft * (xOffset + yOffset);
	ret += vTopRight * ((1.0f - xOffset) + yOffset);
	ret += vBottomLeft * (xOffset + (1.0f - yOffset));
	ret += vBottomRight * (1.0f - (xOffset + yOffset));

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