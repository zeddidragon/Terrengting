#ifndef ZEDDY_TEXTURE_H_
#define ZEDDY_TEXTURE_H_

#include <vector>

#include <gl\glew.h>
#include <glm\glm.hpp>

class Texture{
public:
	Texture(char* filepath);
	~Texture(void);

	void Bind(void);
	static void Unbind(void);
	float DataAt(glm::vec2 uv);
	void PrintData(void);
private:
	GLuint _glId;
	std::vector<unsigned char> _data;
	unsigned int _width, _height;
};

#endif