#ifndef ZEDDY_GRASS_H_
#define ZEDDY_GRASS_H_

#include "modelnode.h"
#include "model.h"
#include "textureset.h"
#include "heightmap.h"
#include "shader.h"

class Grass : public ModelNode {
public:
	Grass(Model* model, Material* material, TextureSet* textures, float quadWidth, float quadHeight, float maxHeight, HeightMap* heightMap, unsigned int count);
	//virtual void Update(float secondsPassed) override;
	virtual void Render(Shader*,const vector<Light*>*,const mat4&,const mat4&) override;

private:
	void Randomize(unsigned int index);
	void AdjustHeight(unsigned int index, HeightMap* heightMap);

	unsigned int _count;
	vec4* _positions;
	float* _yaws;
};

#endif