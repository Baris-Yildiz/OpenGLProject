#shader vertex
#version 330 core

layout(location = 0) in vec4 position; //get data in layout in location 0. this is position data

uniform mat4 u_MVP; //projection matrix.

void main() {
	gl_Position = u_MVP * position; // order is important
};

#shader fragment
#version 330 core

layout (location = 0) out vec4 color; 

uniform vec4 u_Color;	//uniforms can be changed from cpp code.

void main() {
	color = u_Color;
};