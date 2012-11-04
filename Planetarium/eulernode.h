#ifndef ZEDDY_EULER_NODE_H_
#define ZEDDY_EULER_NODE_H_

#include "modelnode.h"

class EulerNode : public ModelNode {
public:
	vec3 Position;
	vec3 Speed;

	EulerNode(Model* model, Material* material, TextureSet* textures);

	virtual	void Update(float secondsPassed) override;
	virtual void Render(Shader* shader, const vector<Light*>* lights, const mat4& viewMatrix, const mat4& parentMatrix) override;

	virtual vec3 GetPosition(void) override;
	virtual void SetPosition(vec3 position) override;
	virtual void MoveX(float amount) override;
	virtual void MoveY(float amount) override;
	virtual void MoveZ(float amount) override;
};

#endif