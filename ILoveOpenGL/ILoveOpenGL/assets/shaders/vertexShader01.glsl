// Vertex shader
#version 420
uniform mat4 MVP;

in vec3 vCol;
in vec3 vPos;

out vec3 colour;			// varying

void main()
{
	vec3 vertPosition = vPos;
	
	gl_Position = MVP * vec4(vertPosition, 1.0f);
	colour = vCol;
}
