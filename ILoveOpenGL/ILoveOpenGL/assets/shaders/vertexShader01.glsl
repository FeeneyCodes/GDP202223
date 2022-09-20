// Vertex shader
#version 420
uniform mat4 MVP;

attribute vec3 vCol;
attribute vec3 vPos;

out vec3 colour;			// varying

void main()
{
	vec3 vertPosition = vPos;
	vertPosition.x += 100.0f;
	
	gl_Position = MVP * vec4(vertPosition, 1.0f);
	colour = vCol;
}
