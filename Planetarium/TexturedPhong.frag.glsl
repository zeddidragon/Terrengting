#version 400 
  
const int MAX_LIGHTS = 2; 
const int MAX_TEXTURES = 2; 
const int MAX_NORMAL_MAPS = 2; 
 
  
uniform int LightTypes[MAX_LIGHTS];	//Point is 0, Directional is 1, Spotlight is 2 
uniform vec3 LightDirections[MAX_LIGHTS]; 
uniform float LightApertures[MAX_LIGHTS];	//In degrees 
uniform vec4 LightMaterialAmbients[MAX_LIGHTS]; 
uniform vec4 LightMaterialDiffuses[MAX_LIGHTS]; 
uniform vec4 LightMaterialSpeculars[MAX_LIGHTS]; 
uniform float MaterialShininess; 
uniform vec4 MaterialEmitted; 
uniform int LightCount; 
   
uniform mat4 ModelView;   
uniform mat3 NormalMatrix; 
   
uniform sampler2D TextureSamplers[MAX_TEXTURES]; 
uniform float TextureScales[MAX_TEXTURES]; 
uniform int TextureCount = 1; 
   
uniform sampler2D NormalSamplers[MAX_NORMAL_MAPS]; 
uniform float NormalMapScales[MAX_NORMAL_MAPS]; 
uniform int NormalMapCount = 0; 
 
  
in vec3 fNormal; 
in vec3 fTangent; 
in vec3 fBitangent; 
 
in vec3 fPosition; 
in vec3 fLights[MAX_LIGHTS]; 
in vec2 fUv; 
 
   
out vec4 fColour;   
 
 
 
vec3 normalBlend(void){ 
	mat3 tangentSpace = mat3( 
		normalize(fTangent), 
		normalize(fBitangent), 
		normalize(fNormal) 
	); 
 
	if (NormalMapCount == 0)   
		//return normalize(tangentSpace * vec3(0, 0, 1)); 
		return normalize(NormalMatrix * fNormal); 
   
	vec4 ret = vec4(0.0, 0.0, 0.0, 0.0);   
	for (int i = 0; i < NormalMapCount; ++i){   
		ret += texture(NormalSamplers[i], fUv * NormalMapScales[i]);   
	}   
	ret = normalize(ret / NormalMapCount);
	return normalize(NormalMatrix * tangentSpace * (ret.xyz - 0.5)); 
}   
 
 
 
vec4 calculateLight(vec3 normalVector, int index){   
	vec3 positionVector = normalize(fPosition);   
	vec3 lightVector = normalize(fLights[index]);   
	vec3 reflectVector = normalize(reflect(lightVector, normalVector));   
   
	float diffuseDot = dot(normalVector, lightVector);   
	float diffuseRatio = max(diffuseDot, 0);   
   
	vec4 ambient = LightMaterialAmbients[index]; 
	vec4 diffuse = diffuseRatio * LightMaterialDiffuses[index];   
    vec4 specular; 
   
    if (LightTypes[index] == 2){
        float spotLightDot = dot(normalize(NormalMatrix * LightDirections[index]), -lightVector); 
        if (acos(spotLightDot) > radians(LightApertures[index])) 
            return ambient; 
    }
 
	if (diffuseDot < 0.0){   
		specular = vec4(0.0, 0.0, 0.0, 1.0);   
	} else {   
		float specularRatio = pow(max(dot(reflectVector, positionVector), 0.0), MaterialShininess);  
		specular = specularRatio * LightMaterialSpeculars[index];   
	} 
	
	return ambient + diffuse + specular;   
}   
 
 
 
vec4 lightBlend(void){   
	vec3 normalVector = normalBlend(); 
    vec4 ret = vec4(0.0, 0.0, 0.0, 0.0); 
    for (int i = 0; i < LightCount; ++i){ 
        ret += calculateLight(normalVector, i); 
    } 
	ret.a = 1.0;
    return ret; 
}   
 
 
 
vec4 textureBlend(void){   
	if (TextureCount == 0)   
		return vec4(1.0, 1.0, 1.0, 1.0);   
   
	vec4 ret = vec4(0.0, 0.0, 0.0, 0.0);
	float totalAlpha = 0.0f;
	vec4 value;
	float alpha;
	for (int i = 0; i < TextureCount; ++i){
		value = texture(TextureSamplers[i], fUv * TextureScales[i]);
		alpha = value.a;
		value *= alpha;
		value.a = alpha;
		ret += value;
		totalAlpha += alpha;
	}
	ret /= totalAlpha;
	return ret;
}   
 
 
  
void main(void){
	vec4 texel = textureBlend();
	float alpha = texel.a;
	if (alpha < 1.0)
		discard;
	fColour = (lightBlend() + MaterialEmitted) * textureBlend();
	fColour.a = alpha;
}