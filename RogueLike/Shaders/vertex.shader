#version 450

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec2 vTexCoords;
layout(location = 2) in float vTexID;

layout(location = 0) out vec2 fTexCoords;
layout(location = 1) out float fTexID;

uniform sampler2D u_textures[32];

uniform mat4 ortho;
uniform vec3 u_camera;

void main()
{
	vec3 Pos = vec3(vPos.xy - u_camera.xy, vPos.z) / u_camera.z;
	gl_Position = ortho * vec4(Pos,1.0);
	fTexCoords = vTexCoords;
	fTexID = vTexID;
}
