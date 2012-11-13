#include "directionallight.h"

DirectionalLight::DirectionalLight() : Light(){
	Direction = glm::vec3(0.0f, 0.0f, 1.0f);
}

void DirectionalLight::Bind(Shader* shader, Material* material, unsigned int index, const mat4& viewMatrix){
	Light::Bind(shader, material, index, viewMatrix);

	GLint directionLocation = shader->GetUniformLocation("LightDirections") + index;
	GLint typeLocation = shader->GetUniformLocation("LightTypes") + index;

	glUniform3fv(directionLocation, 1, value_ptr(Direction));
	glUniform1i(typeLocation, ZD_LightType_Directional);
}