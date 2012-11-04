#include "spotlight.h"

SpotLight::SpotLight() : PointLight(){
	Direction = glm::vec3(0.0f, 0.0f, 1.0f);
	Angle = 45.0f;
}

void SpotLight::Bind(Shader* shader, Material* material, unsigned int index, const mat4& viewMatrix){
	PointLight::Bind(shader, material, index, viewMatrix);

	GLint directionLocation = shader->GetUniformLocation("LightDirections") + index;
	GLint apertureLocation = shader->GetUniformLocation("LightApertures") + index;
	GLint typeLocation = shader->GetUniformLocation("LightTypes") + index;

	glUniform3fv(directionLocation, 1, value_ptr(Direction));
	glUniform1f(apertureLocation, Angle);
	glUniform1i(typeLocation, ZD_LightType_Spot);
}