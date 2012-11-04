#include <gl\glew.h>

#include "light.h"

Light::Light(){
	Ambient = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	Diffuse = Ambient;
	Specular = Ambient;
}

void Light::Bind(Shader* shader, Material* material, unsigned int index, const mat4& viewMatrix){
	GLint ambientLocation = shader->GetUniformLocation("LightMaterialAmbients") + index;
	GLint diffuseLocation = shader->GetUniformLocation("LightMaterialDiffuses") + index;
	GLint specularLocation = shader->GetUniformLocation("LightMaterialSpeculars") + index;
	GLint shininessLocation = shader->GetUniformLocation("MaterialShininess");

	glUniform4fv(ambientLocation, 1, glm::value_ptr(Ambient * material->Ambient + material->Emitted));
	glUniform4fv(diffuseLocation, 1, glm::value_ptr(Diffuse * material->Diffuse));
	glUniform4fv(specularLocation, 1, glm::value_ptr(Specular * material->Specular));
	glUniform1f(shininessLocation, material->Shininess);
}