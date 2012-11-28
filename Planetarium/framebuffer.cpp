#include "framebuffer.h"

FrameBuffer::FrameBuffer(unsigned int width, unsigned int height){
	_width = width;
	_height = height;

	glGenFramebuffers(1, &_id);
	glBindFramebuffer(GL_FRAMEBUFFER, _id);

	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


	glGenRenderbuffers(1, &_depthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, _depthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, _width, _height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthBuffer);
}

void FrameBuffer::Bind(void){
	glBindFramebuffer(GL_FRAMEBUFFER, _id);
	//glViewport(0, 0, _width, _height);
}

void FrameBuffer::Unbind(void){
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//glViewport(0, 0, _width, _height);
}

int FrameBuffer::Width(void){
	return _width;
}

int FrameBuffer::Height(void){
	return _height;
}