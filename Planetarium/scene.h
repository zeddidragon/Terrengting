#ifndef ZEDDY_SCENE_H_
#define ZEDDY_SCENE_H_

#include <vector>

#include "modelnode.h"
#include "pointlight.h"

class Scene{
public:
	void Update(float secondsPassed);
	void Render(Shader* shaders, const mat4& viewMatrix);

	int AddLight(Light* light);
	Light* GetLight(int index);
	int AddMaterial(Material* material); //Return index in vector of material
	Material* GetMaterial(int index);
	int AddModel(Model* model);
	Model* GetModel(int index);
	int AddTexture(Texture* texture);
	Texture* GetTexture(int index);
	int AddNode(Node* node);
	Node* GetNode(int index);

private:
	std::vector<Material*> _materials;
	std::vector<Model*> _models;
	std::vector<Texture*> _textures;
	std::vector<Node*> _nodes;
	std::vector<Light*> _lights;
};

#endif