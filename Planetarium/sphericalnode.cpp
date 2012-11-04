#include "sphericalnode.h"

SphericalNode::SphericalNode(Model* model, Material* material, TextureSet* textures) : ModelNode(model, material, textures){
	OrbitAxis = vec3(0.0f, 1.0f, 0.0f);
	OrbitRadius = 0;
	OrbitSpeed = 0;
	OrbitPosition = 0;
}



void SphericalNode::Update(const float secondsPassed) {
	OrbitPosition += OrbitSpeed * secondsPassed;

	ConstrainAngle(OrbitPosition);

	ModelNode::Update(secondsPassed);
}



void SphericalNode::Render(Shader* shader, const vector<Light*>* lights, const mat4& viewMatrix, const mat4& parentMatrix){
	mat4 modelMatrix = parentMatrix;
	modelMatrix = glm::rotate(modelMatrix, OrbitPosition, OrbitAxis);	//Apply orbit
	modelMatrix = glm::translate(modelMatrix, vec3(0, 0, OrbitRadius));
	modelMatrix = glm::rotate(modelMatrix, -OrbitPosition, OrbitAxis);	//Disapply orbit

	ModelNode::Render(shader, lights, viewMatrix, modelMatrix);
}



vec3 SphericalNode::GetPosition(void){
	vec4 ret = vec4(0.0f, 0.0f, OrbitRadius, 1.0f);
	mat4 orbitMatrix = mat4(1.0f);
	orbitMatrix = glm::rotate(orbitMatrix, OrbitPosition, OrbitAxis);
	ret = orbitMatrix * ret;

	return vec3(ret);
}



void SphericalNode::MoveX(float amount){OrbitAxis.x += amount;}
void SphericalNode::MoveY(float amount){OrbitAxis.y += amount;}
void SphericalNode::MoveZ(float amount){OrbitAxis.z += amount;}