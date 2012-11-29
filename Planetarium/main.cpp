#include <vector>

#include "main.h"

bool MouseIsWarping = false;
Window GlobalWindow;
vector<KeyboardControls*> keyboardControls;
vector<MouseControls*> mouseControls;



int main(int argc, char* argv[]){
	GlobalWindow.Initialize(argc, argv);
	AssignFunctions();
	GlobalWindow.MainScene = CreateScene();

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
	auto scene = new Scene();

	//Initiate materials
	auto skyboxMaterial = new Material(
		vec4(0.0f, 0.0f, 0.0f, 0.0f),
		vec4(0.0f, 0.0f, 0.0f, 0.0f),
		vec4(0.0f, 0.0f, 0.0f, 0.0f),
		vec4(1.0f, 1.0f, 1.0f, 0.0f),
		1
	);
	scene->AddMaterial(skyboxMaterial);

	auto grassMaterial = new Material(
		vec4(1.0f, 1.0f, 1.0f, 1.0f),
		vec4(1.0f, 1.0f, 1.0f, 1.0f),
		vec4(0.3f, 0.3f, 0.3f, 1.0f),
		vec4(0.0f, 0.0f, 0.0f, 0.0f),
		2
	);
	scene->AddMaterial(grassMaterial);

	auto waterMaterial = new Material(
		vec4(1.0f, 1.0f, 1.2f, 1.0f),
		vec4(1.0f, 1.0f, 1.2f, 1.0f),
		vec4(0.3f, 0.3f, 0.5f, 1.0f),
		vec4(0.0f, 0.0f, 0.0f, 0.0f),
		20
	);
	scene->AddMaterial(waterMaterial);

	// Initiate Textures
	auto groundTexture = new Texture("Textures/tileset-grass.png");
	scene->AddTexture(groundTexture);
	auto groundNormals = new Texture("Textures/tileset-grass-normals.png");
	scene->AddTexture(groundNormals);

	auto waterTexture = new Texture("Textures/tileset-water.png");
	scene->AddTexture(waterTexture);

	auto billboardTexture = new Texture("Textures/billboards.png");
	scene->AddTexture(billboardTexture);
	auto billboardNormalMap = new Texture("Textures/billboards-normals.png");
	scene->AddTexture(billboardNormalMap);

	auto skyboxTexture = new Texture("Textures/tileset-skybox.png");
	scene->AddTexture(skyboxTexture);

	auto heightMapTexture = new Texture("Textures/terrain-heightmap.png");
	auto heightMap = new HeightMap(64, 64, heightMapTexture);
	delete heightMapTexture;

	// Initiate TextureSets

	auto billboardSet = new TextureSet();
	billboardSet->Add(billboardTexture, 1.0f);
	auto billboardNormals = new TextureSet();
	billboardNormals->Add(billboardNormalMap, 1.0f);

	// Cincada principle:
	// By making each layer repeat in ratios of prime numbers,
	// the next time they line up perfectly will be far apart.
	// The set will only exactly repeat each 7*13*31*47 unit.
	// The technique is so efficient it's hardly even noticable
	// that each layer is the same texture.
	auto grassSet = new TextureSet();
	grassSet->Add(groundTexture, 47 * 0.05f);
	grassSet->Add(groundTexture, 31 * 0.05f);
	grassSet->Add(groundTexture, 13 * 0.05f);
	grassSet->Add(groundTexture,  7 * 0.05f);

	auto grassNormalSet = new TextureSet();
	grassNormalSet->Add(groundNormals,  47 * 0.05f);
	grassNormalSet->Add(groundNormals,  31 * 0.05f);
	grassNormalSet->Add(groundNormals,  13 * 0.05f);
	grassNormalSet->Add(groundNormals,   7 * 0.05f);

	auto waterSet = new TextureSet();
	waterSet->Add(waterTexture, 1.0f);

	auto blankTextureSet = new TextureSet();

	auto skyboxSet = new TextureSet();
	skyboxSet->Add(skyboxTexture, 1.0f);


	// Initiate Models
	auto cube = new Cube();
	scene->AddModel(cube);

	auto skybox = new Skybox();
	scene->AddModel(skybox); 

	auto sphere = new Sphere(24);
	scene->AddModel(sphere);
	
	auto plane = new Plane(2.0f, 2.0f, 64, 64);
	scene->AddModel(plane);

	auto grass = new BillBoard(vec2(1.0f), vec2(0.5f, 1.0f), vec2(0.0f), vec2(1.0f) / 8.0f);
	scene->AddModel(grass);

	auto heightMapPlane = new HeightMappedPlane(2.0f, 2.0f, 4.0f, heightMap);


	// Initiate Lights
	auto sunLight = new DirectionalLight();
	sunLight->Direction = glm::normalize(vec3(1.0f, -1.0f, 1.0f));
	sunLight->Diffuse = vec4(0.4f, 0.4f, 0.4f, 1.0f);
	sunLight->Ambient = vec4(0.3f, 0.35f, 0.4f, 1.0f);
	scene->AddLight(sunLight);


	// Initiate Nodes
	auto ground = new EulerNode(heightMapPlane, grassMaterial, grassSet);
	//ground->Position = vec3(0.0f, -10.0f, 0.0f);
	ground->SetNormalMaps(grassNormalSet);
	scene->AddNode(ground);

	auto globalControls = new GlobalControls();
	scene->AddNode(globalControls);

	auto skyboxNode = new EulerNode(skybox, skyboxMaterial, skyboxSet);
	skyboxNode->SetNormalMaps(blankTextureSet);
	scene->SetSkybox(skyboxNode);

	auto flightNode = new FreeFlightNode();
	auto cameraNode = new CameraNode(flightNode, GlobalWindow.Viewer);
	cameraNode->SetPosition(vec3(0.0f, 10.0f, 0.0f));
	scene->AddNode(cameraNode);

	auto grassCover = new Grass(grass, grassMaterial, billboardSet, 2.0f, 2.0f, 4.0f, heightMap, 512);
	grassCover->SetNormalMaps(billboardNormals);
	scene->AddNode(grassCover);
	
	Shader* waterShader = new Shader("TexturedPhong.frag.glsl", "waves.vert.glsl");
	waterShader->Link();
	
	auto waterNode = new EulerNode(plane, waterMaterial, waterSet);
	waterNode->SetPosition(vec3(0.0f, 3.0f, 0.0f));
	//scene->SetWater(waterNode, waterShader);
	scene->AddNode(waterNode);

	auto glareNode = new GlareNode(vec3(1.0f, -1.0f, 1.0f), skybox, skyboxMaterial, blankTextureSet);
	scene->SetGlare(glareNode);

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