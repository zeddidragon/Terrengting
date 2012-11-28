#ifndef ZEDDY_MAIN_H_
#define ZEDDY_MAIN_H_

#include "main.h"

#include "window.h"
#include "scene.h"

#include "cube.h"
#include "skybox.h"
#include "plane.h"	
#include "sphere.h"
#include "heightmappedplane.h"
#include "billboard.h"

#include "sphericalnode.h"
#include "eulernode.h"
#include "lightnode.h"
#include "mousenode.h"
#include "textureswitcher.h"
#include "cameranode.h"
#include "freeflightnode.h"
#include "grass.h"
#include "glarenode.h"

#include "spotlight.h"
#include "directionallight.h"

#include "textureset.h"
#include "globalcontrols.h"

#include "keyboardcontrols.h"
#include "mousecontrols.h"

void RegisterKeyboardControls(KeyboardControls* controls);
void UnregisterKeyboardControls(KeyboardControls* controls);
void RegisterMouseControls(MouseControls* controls);
void UnregisterMouseControls(MouseControls* controls);
void UpdateMice(void);

void AssignFunctions();
Scene* CreateScene(void);

void ResizeFunction(int width, int height);
void RenderFunction(void);
void TimerFunction(int value);
void IdleFunction(void);
void KeyboardFunction(unsigned char key, int, int);
void SpecialKeyFunction(int key, int, int);
void KeyboardReleasedFunction(unsigned char key, int, int);
void SpecialKeyReleasedFunction(int ket, int, int);
void MouseClickedFunction(int button, int state, int, int);
void MouseMovementFunction(int x, int y);
void Cleanup(void);

#endif