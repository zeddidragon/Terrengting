#include "glarenode.h"

GlareNode::GlareNode(vec3 sunDirection, Model* model, Material* material, TextureSet* textures) : EulerNode(model, material, textures){
	_sunDirection = sunDirection;
}

void GlareNode::Render(Shader* shader, const vector<Light*>* lights, const mat4& viewMatrix, const mat4& parentMatrix){
	vec3 temp = normalize(vec3(viewMatrix * vec4(_sunDirection, 0.0f)));
	float alpha = glm::dot(temp, vec3(0.0f, 0.0f, 1.0f));

	glUniform1f(shader->GetUniformLocation("Alpha"), clamp(alpha, 0.0f, 1.0f) * 0.7f);
	EulerNode::Render(shader, lights, viewMatrix, mat4(1.0f));
	glUniform1f(shader->GetUniformLocation("Alpha"), 1.0f);
}