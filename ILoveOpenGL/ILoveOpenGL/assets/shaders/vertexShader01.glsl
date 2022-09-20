#version 110
// Vertex shader
uniform mat4 MVP;

attribute vec3 vCol;
attribute vec3 vPos;

varying vec3 colour;

void main()
{
	vec3 vertPosition = vPos;
	vertPosition.x += 100.0;
	
	gl_Position = MVP * vec4(vertPosition, 1.0);
	colour = vCol;
	colour.g = 0.0;
	colour.b = 0.0;
}
