#ifndef ZEDDY_NODE_H_
#define ZEDDY_NODE_H_

#include <vector>

#include <glm\glm.hpp>

#include "shader.h"
#include "light.h"

using namespace std;
using namespace glm;

class Node {
public:
	virtual void Update(float secondsPassed);
	virtual void Render(Shader*,const vector<Light*>*,const mat4&,const mat4&); //Null implementation
	virtual vec3 GetPosition(void){return vec3(0.0f, 0.0f, 0.0f);}
	virtual void SetPosition(vec3 position){};
	virtual void MoveX(float amount){}
	virtual void MoveY(float amount){}
	virtual void MoveZ(float amount){}
protected:
	std::vector<Node*> _children;
};

#endif