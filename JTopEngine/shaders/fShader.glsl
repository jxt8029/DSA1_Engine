#version 430

out vec4 FragColor;

//in vec3 blend;
layout (location = 5) uniform vec3 camLoc;
layout (location = 6) uniform vec3 lightLoc;
in vec3 fragLoc; //varying
in vec3 fragNorm; //varying

uniform sampler2D myTexture;
in vec2 fragUV;

void main()
{
	vec3 L = normalize(lightLoc - fragLoc);
	vec3 V = normalize(camLoc - fragLoc);
	vec3 H = normalize(L + V);
	vec3 N = normalize(fragNorm);
	float diffuse = max(dot(L, N), 0);
	float spec = max(dot(H, N), 0);
	float brightness = .1 + .5 * diffuse + .5 * pow(spec, 16);
	vec3 color = brightness * vec3(1, 1, 1);
	//FragColor = vec4(color, 1.f);
	FragColor = texture(myTexture, fragUV);
}