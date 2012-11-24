#ifndef ZEDDY_HEIGHTMAP_H_
#define ZEDDY_HEIGHTMAP_H_

#include "texture.h"

class HeightMap{
public:
	HeightMap(unsigned int width, unsigned int height, Texture* texture);
	unsigned int Width(void), Height(void);
	float* Map;
protected:
	unsigned int _width, _height;
};

#endif