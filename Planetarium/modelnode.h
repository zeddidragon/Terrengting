#ifndef ZEDDY_MODEL_NODE_H_
#define ZEDDY_MODEL_NODE_H_

#include <vector>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "orientationnode.h"
#include "model.h"
#include "material.h"
#include "textureset.h"

class ModelNode : public OrientationNode {
public:
	ModelNode(Model* model, Material* material, TextureSet* textures);
	virtual ~ModelNode();
	
	virtual void Update(float secondsPassed) override;
	virtual void Render(Shader* shader, const vector<Light*>* lights, const mat4& viewMatrix, const mat4& parentMatrix) override;

	void SetTextures(TextureSet* textures);
	void SetNormalMaps(TextureSet* map);
	TextureSet* GetTextures(void);
	TextureSet* GetNormalMaps(void);

	void AddChild(Node* child);

	float Size;

	float PitchSpeed, YawSpeed, RollSpeed;

protected:
	Model* _model;
	Material* _material;
	TextureSet* _textures;
	TextureSet* _normalMaps;
};

#endif