#include "scene.h"

void Scene::Update(float secondsPassed){
	for (unsigned int i = 0; i < _nodes.size(); ++i){
		_nodes.at(i)->Update(secondsPassed);
	}
}

void Scene::Render(Shader* shader, const mat4& viewMatrix){
	GLint lightCountLocation = shader->GetUniformLocation("LightCount");
	glUniform1i(lightCountLocation, _lights.size());
	for (unsigned int i = 0; i < _nodes.size(); ++i){
		_nodes.at(i)->Render(shader, &_lights, viewMatrix, mat4(1.0f));
	}
}

int Scene::AddLight(Light* light){ //Return index in vector of material
	_lights.push_back(light);
	return _lights.size() - 1;
}

Light* Scene::GetLight(int index){
	return _lights.at(index);
}

int Scene::AddMaterial(Material* material){ //Return index in vector of material
	_materials.push_back(material);
	return _materials.size() - 1;
}

Material* Scene::GetMaterial(int index){
	return _materials.at(index);
}

int Scene::AddTexture(Texture* texture){ //Return index in vector of texture
	_textures.push_back(texture);
	return _textures.size() - 1;
}

Texture* Scene::GetTexture(int index){
	return _textures.at(index);
}

int Scene::AddModel(Model* model){
	_models.push_back(model);
	return _models.size() - 1;
}

Model* Scene::GetModel(int index){
	return _models.at(index);
}

int Scene::AddNode(Node* node){
	_nodes.push_back(node);
	return _nodes.size() - 1;
}

Node* Scene::GetNode(int index){
	return _nodes.at(index);
}