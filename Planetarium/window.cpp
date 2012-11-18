#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "window.h"
#include "scene.h"
#include "sphericalnode.h"
#include "eulernode.h"
#include "cube.h"
#include "constants.h"



Window::~Window(void){
	delete _shader;
}



void Window::Initialize(int argc, char* argv[]){
	InitializeWindow(argc, argv);
	InitializeGlStuff();
	InitializeShader();
	InitializeCamera();
}



void Window::InitializeCamera(void){
	Viewer = new Camera(Width, Height);

	Viewer->Resize(Width, Height);
	Viewer->MoveTo(vec4(-5.0f, -15.0f, -20.0f, 1));
	//Viewer->MoveTo(vec4(-5.0f, -65.0f, -20.0f, 1));
	Viewer->LookAt(vec4(0.0f, 0.0f, 5.0f, 0.0f));
}



void Window::InitializeShader(void){
	_shader = new Shader("TexturedPhong.frag.glsl", "TexturedPhong.vert.glsl");
	_shader->Link();
	Window::ExitOnGLError("link shader");
}



void Window::InitializeGlStuff(void){
	glewExperimental = GL_TRUE;
	GLenum glewInitResult = glewInit();

	if (glewInitResult != GLEW_OK){
		fprintf(stderr, "ERROR: %s\n", glewGetErrorString(glewInitResult));
		system("pause");
		exit(EXIT_FAILURE);
	}

	fprintf(stdout, "INFO: OpenGL Version: %s\n", glGetString(GL_VERSION));

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	ExitOnGLError("set OpenGL depth testing options");

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	ExitOnGLError("set OpenGL culling options");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	ExitOnGLError("set OpenGL blending options");
}



void Window::InitializeWindow(int argc, char* argv[]){
	glutInit(&argc, argv);

	glutInitContextVersion(4, 0);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutSetOption(
		GLUT_ACTION_ON_WINDOW_CLOSE,
		GLUT_ACTION_GLUTMAINLOOP_RETURNS
	);

	glutInitWindowSize(Width, Height);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	_windowHandle = glutCreateWindow(WINDOW_TITLE);

	if (_windowHandle < 1){
		fprintf(stderr, "ERROR: Could not create a new rendering window.\n");
		exit(EXIT_FAILURE);
	}
}



void Window::Resize(int width, int height){
	Width = width;
	Height = height;

	glViewport(0, 0, Width, Height);
	ExitOnGLError("reassign the viewport");

	_shader->Use();
	ExitOnGLError("test the shader");

	Viewer->Resize(width, height);
	ExitOnGLError("assign the projection matrix");

	_shader->Unuse();
}



void Window::Render(void){
	++_frameCount;

	if (MainScene != 0)
		MainScene->Update(1.0f/60);
	//Viewer->Update();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	ExitOnGLError("clear the screen");

	_shader->Use();
	ExitOnGLError("use the shader");

	GLint projectionLocation = _shader->GetUniformLocation("ProjectionMatrix");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, value_ptr(Viewer->GetProjectionMatrix()));

	mat4 viewMatrix = Viewer->GetViewMatrix();

	if (MainScene)
		MainScene->Render(_shader, viewMatrix);

	_shader->Unuse();

	glutSwapBuffers();
	glutPostRedisplay();
}



void Window::UpdateTitle(int value){
	if (value != 0){
		char* tempString = (char*) malloc(512 + strlen(WINDOW_TITLE));

		sprintf(
			tempString,
			"%s: %d FPS @ %d x %d",
			WINDOW_TITLE,
			_frameCount * 4,
			Width, Height
		);

		glutSetWindowTitle(tempString);
		free(tempString);
	}

	_frameCount = 0;
}



void Window::ExitOnGLError(const char* codeblock){
	/*
	const GLenum errorValue = glGetError();

	if (errorValue != GL_NO_ERROR){
		fprintf(
			stderr,
			"ERROR: Could not %s: %s\n",
			codeblock,
			gluErrorString(errorValue)
		);

		system("pause");
		exit(EXIT_FAILURE);
	}
	*/
}