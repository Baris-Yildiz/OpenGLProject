#shader vertex
#version 330 core

layout(location = 0) in vec4 position; //get data in layout in location 0. this is position data
layout(location = 1) in vec2 texCoord;
layout(location = 2) in float texIndex;

uniform mat4 u_MVP; //projection matrix.
out vec2 v_TexCoord;
out float v_TexIndex;

void main() {
	v_TexCoord = texCoord;
	v_TexIndex = texIndex;
	gl_Position = u_MVP * position; // order is important
};

#shader fragment
#version 330 core

layout (location = 0) out vec4 color; 
in vec2 v_TexCoord;
in float v_TexIndex;

uniform sampler2D u_Textures[2];

void main() {
	int index = int(v_TexIndex);
	color = texture(u_Textures[index], v_TexCoord);
};