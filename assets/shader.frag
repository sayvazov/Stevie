#version 150

uniform sampler2D	diffuseMap;
uniform sampler2D	normalMap;

in vec3				NormalViewSpace;
in vec2				texCoord;
in vec3				lightViewSpace;

out vec4	oColor;


void main()
{
	//vec4 normalAngleVec = texture(normalMap, texCoord);
	//float normalAngle = normalAngleVec.x;
//	vec3 normal = vec3(sin(normalAngle), cos(normalAngle), 1 - sin(normalAngle) - cos(normalAngle));
	//float dotProd = max(0.0, dot(normal, lightViewSpace));
	float dotProd = 1.0;
	oColor = vec4(dotProd, dotProd, dotProd, 1.0)*texture(diffuseMap, texCoord);
}

