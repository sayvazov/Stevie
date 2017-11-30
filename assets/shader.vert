#version 150

uniform mat4	ciModelView;
uniform mat4	ciProjectionMatrix;
uniform mat3	ciNormalMatrix;
uniform vec3	ciLightDir;

in vec4			ciPosition;
in vec3			ciNormal;
in vec2			ciTexCoord0;

out vec3		NormalViewSpace;
out vec2		texCoord;
out vec3		lightViewSpace;


void main()
{	
	vec4 newPos = ciPosition;

	texCoord = ciTexCoord0;

	lightViewSpace = normalize(ciNormalMatrix*ciLightDir);
	
	// calculate view space normal (required for lighting & normal mapping)
	NormalViewSpace = normalize(ciNormalMatrix * ciNormal);

	// vertex shader must always pass projection space position
	gl_Position = ciProjectionMatrix * ciModelView  * newPos;
}
