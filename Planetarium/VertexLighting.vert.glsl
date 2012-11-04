#version 400

uniform mat4 ModelView;
uniform mat4 ProjectionMatrix;
uniform mat3 NormalMatrix;

uniform vec4 AmbientProductAndEmitted, DiffuseProduct, SpecularProduct;
uniform float Shininess;
uniform vec4 LightPosition; //Pre-calculated for viewspace

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec3 vNormal;

out vec4 fColor;

void main(void){

	vec3 positionVector = (ModelView * vPosition).xyz;
	vec3 normalVector = normalize(NormalMatrix * vNormal);
	vec3 lightVector = LightPosition.xyz;
	if (LightPosition.w != 0.0)
		lightVector = normalize(LightPosition.xyz - positionVector);

	vec3 reflectVector = normalize(reflect(lightVector, normalVector));


	float diffuseDot = dot(normalVector, lightVector);
	float diffuseRatio = max(diffuseDot, 0.0);
	float specularRatio = pow(max(dot(reflectVector, normalize(positionVector)), 0.0), Shininess);

	vec4 ambient = AmbientProductAndEmitted;
	vec4 diffuse = diffuseRatio * DiffuseProduct;
	vec4 specular = specularRatio * SpecularProduct;
	if (diffuseDot < 0.0){
		specular = vec4(0.0, 0.0, 0.0, 1.0);
	}
	
	fColor = ambient + diffuse + specular;
	
	gl_Position = ProjectionMatrix * ModelView * vPosition;
}