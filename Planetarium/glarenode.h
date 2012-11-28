#ifndef ZEDDY_GLARE_NODE_H_
#define ZEDDY_GLARE_NODE_H_

#include "eulernode.h"

class GlareNode : public EulerNode {
public:
	GlareNode(vec3 sunDirection, Model* model, Material* material, TextureSet* textures);
	virtual void Render(Shader* shader, const vector<Light*>* lights, const mat4& viewMatrix, const mat4& parentMatrix) override;
private:
	vec3 _sunDirection;
};

#endif