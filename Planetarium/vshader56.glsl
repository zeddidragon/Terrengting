#version 150 

in   vec4 vPosition;
in   vec3 vNormal;

// output values that will be interpretated per-fragment
out  vec3 fN;
out  vec3 fE;
out  vec3 fL;

uniform mat4 ModelView;
uniform vec4 LightPosition;
uniform mat4 ProjectionMatrix;
uniform mat3 NormalMatrix;

void main()
{
    fN = vNormal * NormalMatrix;
	fE = (vPosition * ModelView).xyz;
    fL = LightPosition.xyz;
    
    if( LightPosition.w != 0.0 ) {
	fL = LightPosition.xyz - vPosition.xyz;
    }

    gl_Position = ProjectionMatrix*ModelView*vPosition;
}
