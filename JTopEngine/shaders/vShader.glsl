#version 430

layout (location = 1) uniform mat4 worldView;
layout (location = 2) in vec3 loc;
layout (location = 3) in vec2 uv;
layout (location = 4) in vec3 norm;
layout (location = 7) uniform mat4 modelWorldTransform;

//out vec3 blend;
out vec3 fragLoc; //varying
out vec3 fragNorm; //varying

in vec2 modelUV;
out vec2 fragUV;

void main()
{
	//blend = vec3(loc.x + .7, loc.y + .9, loc.x + loc.y + .8);

	fragLoc = vec3(worldView * vec4(loc, 1.f));
	fragNorm = norm;

	fragUV = modelUV;

	gl_Position = worldView * modelWorldTransform * vec4(loc, 1);
}