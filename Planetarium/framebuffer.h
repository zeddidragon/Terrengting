#ifndef ZEDDY_FRAMEBUFFER_H_
#define ZEDDY_FRAMEBUFFER_H_

#include <gl\glew.h>

class FrameBuffer{
public:
	FrameBuffer(unsigned int width, unsigned int height);
	void Bind(void);
	void Unbind(void);
	int Width(void), Height(void);
private:
	unsigned int _width, _height;

	GLuint _id;
	GLuint _texture;
	GLuint _depthBuffer;
};

#endif