#ifndef ZEDDY_SHADER_H_
#define ZEDDY_SHADER_H_

#include <gl\glew.h>
#include <glm\glm.hpp>

class Shader{
public:
	Shader(const char* fragmentShader, const char* vertexShader);
	Shader(const char* filepath, GLenum shaderType);
	~Shader(void);

	void Use(void);
	static void Unuse(void);
	void Link(void);
	GLint GetUniformLocation(const char* uniformVariable);

	float* Shader::GetUniform(const char* uniformVariable);
protected:
	void Attach(GLuint shaderId);

	GLuint _id;
};

#endif