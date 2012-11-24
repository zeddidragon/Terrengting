	#version 400  
  
const int MAX_LIGHTS = 8;
 
  
uniform vec4 LightPositions[MAX_LIGHTS]; //Pre-calculated for viewspace  
uniform vec3 LightDirections[MAX_LIGHTS]; 
uniform int LightTypes[MAX_LIGHTS];	//Point is 0, Directional is 1, Spotlight is 2 
uniform int LightCount;  
 
uniform mat4 ModelView;  
uniform mat4 ProjectionMatrix;  
uniform mat3 NormalMatrix;  
 
 
layout(location = 0) in vec4 vPosition;  
layout(location = 1) in vec3 vNormal; 
layout(location = 2) in vec2 vUv;  
layout(location = 3) in vec3 vTangent; 
layout(location = 4) in vec3 vBitangent; 
  
 
out vec3 fNormal; 
out vec3 fTangent; 
out vec3 fBitangent; 
 
out vec3 fPosition;  
out vec3 fLights[MAX_LIGHTS];  
out vec2 fUv;  
 
 
 
void calculateLightVectors(void){  
    // Temporary array because compiler error when writing directly to fLights[i] 
    // .. 
    // .. 
    // I would like to express thanks to gDEBugger for showing me that, 
    // because I'd never have guessed that on my own. 
     
    vec3 ret[MAX_LIGHTS]; 
 
	for (int i = 0; i < LightCount; ++i){  
		if (LightTypes[i] == 1)  
			ret[i] = NormalMatrix * -LightDirections[i];
		else  
			ret[i] = LightPositions[i].xyz - fPosition;  
	} 
     
    fLights = ret; 
}  
 
 
  
void main(void){  
	fPosition = (ModelView * vPosition).xyz;  
	fNormal = normalize(vNormal);  
	fTangent = normalize(vec3(-fNormal.y, fNormal.x, 0)); 
	fBitangent = cross(fNormal, fTangent); 
 
	calculateLightVectors();  
  
	fUv = vUv;  
	  
	gl_Position = ProjectionMatrix * ModelView * vPosition;  
}	