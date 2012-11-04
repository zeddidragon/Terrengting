#ifndef ZEDDY_BOILERPLATE_H
#define ZEDDY_BOILERPLATE_H

#include <gl\glew.h>
#include <gl\freeglut.h>
#include <glm\glm.hpp>

#include "keyboardcontrols.h"
#include "mousecontrols.h"
#include "camera.h"
#include "scene.h"
#include "shader.h"

#define WINDOW_TITLE "TextureLightThingy v0.4"

using namespace std;
using namespace glm;

class Window{
public:
	~Window(void);

	Camera* Viewer;
	Scene* MainScene;

	int Width, Height;

	void Initialize(int, char*[]);
	void InitializeWindow(int, char*[]);
	void InitializeGlStuff(void);
	void InitializeShader(void);
	void GetUniformLocations(void);
	void InitializeCamera(void);

	void UpdateTitle(int);
	void Resize(int, int);
	void Render(void);

	static void ExitOnGLError(const char *);

private:
	int _windowHandle;
	int _frameCount;
	Shader* _shader;
};

#endif