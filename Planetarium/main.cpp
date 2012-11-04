#include <vector>

#include "main.h"

bool MouseIsWarping = false;
Window GlobalWindow;
vector<KeyboardControls*> keyboardControls;
vector<MouseControls*> mouseControls;



int main(int argc, char* argv[]){
	GlobalWindow.Initialize(argc, argv);
	AssignFunctions();
	Scene* scene = CreateScene();
	GlobalWindow.MainScene = scene;

	glutMainLoop();

	exit(EXIT_SUCCESS);
}



void AssignFunctions(){
	glutReshapeFunc(ResizeFunction);
	glutDisplayFunc(RenderFunction);
	glutIdleFunc(IdleFunction);
	glutTimerFunc(0, TimerFunction, 0);
	glutKeyboardFunc(KeyboardFunction);
	glutSpecialFunc(SpecialKeyFunction);
	glutKeyboardUpFunc(KeyboardReleasedFunction);
	glutSpecialUpFunc(SpecialKeyReleasedFunction);
	glutMotionFunc(MouseMovementFunction);
	glutPassiveMotionFunc(MouseMovementFunction);
	glutMouseFunc(MouseClickedFunction);
	glutCloseFunc(Cleanup);
}



Scene* CreateScene(void){
	Scene* scene = new Scene();

	//Initiate materials
	Material* sunMaterial = new Material(
		vec4(0.0f, 0.0f, 0.0f, 0.0f),
		vec4(0.0f, 0.0f, 0.0f, 0.0f),
		vec4(0.0f, 0.0f, 0.0f, 0.0f),
		vec4(1.0f, 1.0f, 0.6f, 1.0f),
		1
	);
	scene->AddMaterial(sunMaterial);

	Material* earthMaterial = new Material(
		vec4(0.04f, 0.04f, 0.2f, 1.0f),
		vec4(0.1f, 0.5f, 0.3f, 1.0f),
		vec4(0.5f, 0.5f, 0.5f, 1.0f),
		vec4(0.0f, 0.0f, 0.0f, 1.0f),
		5
	);
	scene->AddMaterial(earthMaterial);

	Material* moonMaterial = new Material(
		vec4(0.1f, 0.1f, 0.1f, 1.0f),
		vec4(0.5f, 0.5f, 0.5f, 1.0f),
		vec4(0.0f, 0.0f, 0.0f, 1.0f),
		vec4(0.0f, 0.0f, 0.0f, 1.0f),
		1
	);
	scene->AddMaterial(moonMaterial);

	Material* brickMaterial = new Material(
		vec4(-0.3f, -0.3f, -0.3f, 1.0f),
		vec4(1.5f, 1.5f, 1.5f, 1.0f),
		vec4(1.6f, 1.6f, 1.6f, 1.0f),
		vec4(0.0f, 0.0f, 0.0f, 1.0f),
		20
	);
	scene->AddMaterial(earthMaterial);

	Material* metalMaterial = new Material(
		vec4(0.2f, 0.2f, 0.2f, 1.0f),
		vec4(0.2f, 0.2f, 0.2f, 1.0f),
		vec4(1.0f, 1.0f, 1.0f, 1.0f),
		vec4(0.0f, 0.0f, 0.0f, 1.0f),
		10
	);
	scene->AddMaterial(metalMaterial);

	// Initiate Textures
	Texture* mudBrickTexture = new Texture("Textures/AlternatingMudbrick-ColorMap.png");
	scene->AddTexture(mudBrickTexture);
	Texture* mudBrickNormals = new Texture("Textures/AlternatingMudbrick-NormalMap.png");
	scene->AddTexture(mudBrickNormals);

	Texture* crackedBrickTexture = new Texture("Textures/CrackedAlternatingBricks-ColorMap.png");
	scene->AddTexture(crackedBrickTexture);
	Texture* crackedBrickNormals = new Texture("Textures/CrackedAlternatingBricks-NormalMap.png");
	scene->AddTexture(crackedBrickNormals);

	Texture* sandTexture = new Texture("Textures/Sand_1_Diffuse.png");
	scene->AddTexture(sandTexture);
	Texture* sandNormals = new Texture("Textures/Sand_1_Normal.png");
	scene->AddTexture(sandNormals);

	Texture* heightMap = new Texture("Textures/terrain-heightmap.png");
	//Texture* heightMap = new Texture("Textures/heightmap.png");
	//Texture* heightMap = new Texture("Textures/z.png");
	scene->AddTexture(heightMap);

	// Initiate Models
	/*
	Model* cube = new Cube();
	scene->AddModel(cube);
	*/
	Model* sphere = new Sphere(24);
	scene->AddModel(sphere);
	
	Model* plane = new Plane(2.0f, 2.0f, 64, 64);
	scene->AddModel(plane);

	Model* heightMapPlane = new HeightMappedPlane(2.0f, 2.0f, 5.0f, 64, 64, heightMap);

	// Initiate TextureSets
	TextureSet* brickBlend = new TextureSet();
	brickBlend->Add(mudBrickTexture, 2.0f);
	brickBlend->Add(crackedBrickTexture, 2.0f);

	TextureSet* blankTextureSet = new TextureSet();

	TextureSet* brickBlendNormals = new TextureSet();
	brickBlendNormals->Add(mudBrickNormals, 2.0f);
	brickBlendNormals->Add(crackedBrickNormals, 2.0f);

	TextureSet* smallBricks = new TextureSet();
	smallBricks->Add(crackedBrickTexture, 0.25f);
	TextureSet* smallBrickNormals = new TextureSet();
	smallBrickNormals->Add(crackedBrickNormals, 0.25f);

	// Initiate Nodes
	//EulerNode* ground = new EulerNode(plane, brickMaterial, brickBlend);
	EulerNode* ground = new EulerNode(heightMapPlane, brickMaterial, brickBlend);
	ground->Position = vec3(0.0f, -10.0f, 0.0f);
	ground->SetNormalMaps(brickBlendNormals);
	
	TextureSwitcher* textureSwitcher = new TextureSwitcher(ground);
	textureSwitcher->AddTextures(mudBrickTexture, mudBrickNormals);
	textureSwitcher->AddTextures(crackedBrickTexture, crackedBrickNormals);
	textureSwitcher->AddTextures(sandTexture, sandNormals);
	scene->AddNode(textureSwitcher);
	
	EulerNode* orb = new EulerNode(sphere, metalMaterial, blankTextureSet);
	//EulerNode* orb = new EulerNode(sphere, metalMaterial, smallBricks);
	orb->Position = vec3(0.0f, 5.0f, 0.0f);
	orb->SetNormalMaps(blankTextureSet);
	//orb->SetNormalMaps(smallBrickNormals);
	orb->Size = 5;
	ground->AddChild(orb);
	
	// Initiate Lights
	PointLight* pointLight = new PointLight();
	SpotLight* spotLight = new SpotLight();
	spotLight->Ambient = vec4(0.3f, 0.3f, 0.3f, 1.0);
	spotLight->Diffuse = vec4(0.5f, 0.5f, 0.3f, 0.0);
	spotLight->Specular = vec4(1.0f, 1.0f, 1.0f, 1.0);
	spotLight->Angle = 55.0f;
	spotLight->Direction = vec3(0.0f, -1.0f, 0.0f);

	scene->AddLight(pointLight);
	scene->AddLight(spotLight);

	EulerNode* spotLightModelNode = new EulerNode(sphere, sunMaterial, blankTextureSet);
	spotLightModelNode->Position = vec3(50.0f, 100.0f, 50.0f);
	spotLightModelNode->SetNormalMaps(blankTextureSet);
	spotLightModelNode->Position = vec3(spotLight->Position);
	scene->AddNode(spotLightModelNode);

	MouseNode* spotLightMover = new MouseNode(spotLightModelNode, GLUT_LEFT_BUTTON, true);
	LightNode* spotLightNode = new LightNode(spotLight, spotLightMover);
	spotLightMover->SetPosition(vec3(5.0f, 5.0f, 5.0f));
	scene->AddNode(spotLightNode);

	EulerNode* pointLightModelNode = new EulerNode(sphere, sunMaterial, blankTextureSet);
	pointLightModelNode->Position = vec3(50.0f, 50.0f, 50.0f);
	pointLightModelNode->SetNormalMaps(blankTextureSet);
	pointLightModelNode->Position = vec3(pointLight->Position);
	scene->AddNode(pointLightModelNode);

	MouseNode* pointLightMover = new MouseNode(pointLightModelNode, GLUT_RIGHT_BUTTON, false);
	LightNode* pointLightNode = new LightNode(pointLight, pointLightMover);
	pointLightMover->SetPosition(vec3(0.0f, 5.0f, 0.0f));
	scene->AddNode(pointLightNode);

	Node* globalControls = new GlobalControls();
	scene->AddNode(globalControls);

	return scene;
}



void Cleanup(){
}



void IdleFunction(void){
	glutPostRedisplay();
}



void TimerFunction(int value){
	GlobalWindow.UpdateTitle(value);
	glutTimerFunc(250, TimerFunction, 1); //Fps oppdatert 4x i sekundet, antar jeg
}



void ResizeFunction(int width, int height){
	GlobalWindow.Resize(width, height);
	UpdateMice();
}



void RenderFunction(void){
	GlobalWindow.Render();
}



void KeyboardFunction(unsigned char key, int x, int y){
	for (auto i = keyboardControls.begin(); i < keyboardControls.end(); ++i){
		(*i)->CharPressed(key);
	}
}



void KeyboardReleasedFunction(unsigned char key, int x, int y){
	for (auto i = keyboardControls.begin(); i < keyboardControls.end(); ++i){
		(*i)->CharReleased(key);
	}
}

void SpecialKeyFunction(int key, int x, int y){
	for (auto i = keyboardControls.begin(); i < keyboardControls.end(); ++i){
		(*i)->SpecialPressed(key);
	}
}



void SpecialKeyReleasedFunction(int key, int x, int y){
	for (auto i = keyboardControls.begin(); i < keyboardControls.end(); ++i){
		(*i)->SpecialReleased(key);
	}
}



void MouseClickedFunction(int button, int state, int x, int y){
	for (auto i = mouseControls.begin(); i < mouseControls.end(); ++i){
		if (state == GLUT_UP){
			(*i)->Lift(button);
		} else {
			(*i)->Click(button);
		}
	}
}



void MouseMovementFunction(int x, int y){ 
	if (!MouseIsWarping){
		for (auto i = mouseControls.begin(); i < mouseControls.end(); ++i){
			(*i)->Motion(x, y);
		}
		if (x != GlobalWindow.Width / 2 || y != GlobalWindow.Height / 2){
			MouseIsWarping = true;
			glutWarpPointer(GlobalWindow.Width / 2, GlobalWindow.Height / 2);
			MouseIsWarping = false;
		}
	}
}



void RegisterKeyboardControls(KeyboardControls* controls){
	keyboardControls.push_back(controls);
}



void UnregisterKeyboardControls(KeyboardControls* controls){
	for (auto i = keyboardControls.begin(); i < keyboardControls.end(); ++i){
		if (*i == controls){
			keyboardControls.erase(i);
			return;
		}
	}
}



void RegisterMouseControls(MouseControls* controls){
	mouseControls.push_back(controls);
	UpdateMice();
}



void UnregisterMouseControls(MouseControls* controls){
	for (auto i = mouseControls.begin(); i < mouseControls.end(); ++i){
		if (*i == controls){
			mouseControls.erase(i);
			return;
		}
	}
}



void UpdateMice(void){
	for (auto i = mouseControls.begin(); i < mouseControls.end(); ++i){
		(*i)->SetOrigin(GlobalWindow.Width / 2, GlobalWindow.Height / 2);
	}
}