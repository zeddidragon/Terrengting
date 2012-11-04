#include <gl\glew.h>
#include <glm\gtc\type_ptr.hpp>

#include "material.h"
#include "window.h"

Material::Material(vec4 ambient, vec4 diffuse, vec4 specular, vec4 emitted, float shininess){
	Ambient = ambient;
	Diffuse = diffuse;
	Specular = specular;
	Emitted = emitted;
	Shininess = shininess;
}