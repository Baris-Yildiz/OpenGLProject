#shader vertex
#version 330 core

layout(location = 0) in vec4 position; //get data in layout in location 0. this is position data
layout(location = 1) in vec4 color;

uniform mat4 u_MVP; //projection matrix.
out vec4 v_Color;

void main() {
	v_Color = color;
	gl_Position = u_MVP * position; // order is important
};

#shader fragment
#version 330 core

layout (location = 0) out vec4 color; 

in vec4 v_Color;

void main() {
	color = v_Color;
};