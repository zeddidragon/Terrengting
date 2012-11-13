#include <iostream>

#include <glm\gtc\type_ptr.hpp>

#include "shader.h"
#include "window.h"

Shader::Shader(const char* filename, GLenum shaderType){
	_id = 0;	//OpenGL's indeks for shaderprogrammet som blir opprettet
	FILE* file;
	long fileSize = -1;
	char* glslSource;	//Shaderprogrammet, før kompilering

	if (
		(file = fopen(filename, "rb")) != NULL &&
		fseek(file, 0, SEEK_END) == 0 &&
		(fileSize = ftell(file)) != -1
	){
		rewind(file);

		if ((glslSource = (char*)malloc(fileSize + 1)) != NULL){	//Kopier filinnhold?
			if (fileSize == (long)fread(glslSource, sizeof(char), fileSize, file)){
				glslSource[fileSize] = '\0';

				if ( ( _id = glCreateShader(shaderType) ) != 0){	//Opprett shader i OpenGL, lagre indeks
					const char *glslSource_temp = glslSource;
					glShaderSource(_id, 1, &glslSource_temp, NULL);	//Last strengen med shaderprogrammet inn i openGL
					glCompileShader(_id);	//Kompiler det
					Window::ExitOnGLError("compile a shader");
				} else {
					cout << "ERROR: Could not create a shader." << endl;
				}
			} else {
				cout << "ERROR: Could not read file " << filename << endl;
			}
			free(glslSource);
		} else {
			cout << "ERROR: Could not allocate " << fileSize << " bytes." << endl;
		}
		fclose(file);
	} else {
		cout << "ERROR: Could not open file " << filename << endl;
	}
}

Shader::Shader(const char* fragmentShaderFile, const char* vertexShaderFile){
	_id = glCreateProgram();	//Opprett shaderprogram i OpenGL, lagre indeks for fremtidig bruk
	Window::ExitOnGLError("create the shader program");

	Shader fragmentShader = Shader(fragmentShaderFile, GL_FRAGMENT_SHADER);	
	Window::ExitOnGLError("create the fragment shader");
	Shader vertexShader = Shader(vertexShaderFile, GL_VERTEX_SHADER);
	Window::ExitOnGLError("create the vertex shader");

	fragmentShader.Attach(_id);	//Fest fragment shader til hovedprogrammet
	Window::ExitOnGLError("attach the fragment shader");
	vertexShader.Attach(_id);	//Fest vertex shader til hovedprogrammet
	Window::ExitOnGLError("attach the vertex shader");
}

Shader::~Shader(void){
	glDeleteProgram(_id);
	// GL is bitching about an invalid operation after I call glDeleteProgram.
	// Everything's fine, though, so I just call glGetError() to clear the error buffer.
}

void Shader::Attach(GLuint shaderId){
	glAttachShader(shaderId, _id);
}

void Shader::Use(void){
	glUseProgram(_id);
}

void Shader::Unuse(void){
	glUseProgram(0);
}

void Shader::Link(void){
	glLinkProgram(_id); //Link hovedprogrammet til grafikkortet
}

GLuint Shader::GetUniformLocation(const char* uniformVariable){
	return glGetUniformLocation(_id, uniformVariable);
}

float* Shader::GetUniform(const char* uniformVariable){
	GLint uniformLocation = GetUniformLocation(uniformVariable);
	float fRet[4] = {0.0, 0.0, 0.0, 0.0};

	glGetUniformfv(_id, uniformLocation, fRet);
	return fRet;

	int iRet[4] = {0, 0, 0, 0};
	glGetUniformiv(_id, uniformLocation, iRet);
	return (float*)iRet;
}