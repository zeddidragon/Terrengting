#include "pointlight.h"

PointLight::PointLight() : Light(){
	Position = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

void PointLight::Bind(Shader* shader, Material* material, unsigned int index, const mat4& viewMatrix){
	Light::Bind(shader, material, index, viewMatrix);

	GLint positionLocation = shader->GetUniformLocation("LightPositions") + index;
	GLint typeLocation = shader->GetUniformLocation("LightTypes") + index;

	glUniform4fv(positionLocation, 1, value_ptr(viewMatrix * Position));
	glUniform1i(typeLocation, ZD_LightType_Point);
}