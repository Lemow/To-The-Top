#version 450

layout(location = 0) in vec2 fTexCoords;
layout(location = 1) in float fTexID;

layout(location = 0) out vec4 fColor;

uniform sampler2D u_textures[32];

void main()
{
	fColor = texture(u_textures[int(fTexID)], fTexCoords);
}
