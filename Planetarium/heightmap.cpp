#include "heightmap.h"

HeightMap::HeightMap(unsigned int width, unsigned int height, Texture* texture){
	_width = width;
	_height = height;
	Map = new float[_width * _height];

	unsigned int i, j;
	glm::vec4 value;

	for (j = 0; j < _height; ++j){
		for (i = 0; i < _width; ++i){
			value = texture->PixelAt(glm::vec2((float)i / _width, (float)j / _height));
			Map[i + j * _width] = value.x;
		}
	}
}


unsigned int HeightMap::Width(void){
	return _width;
}
unsigned int HeightMap::Height(void){
	return _height;
}