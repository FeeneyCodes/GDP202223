//Fragment shader
#version 420

in vec3 colour;			// varying

void main()
{
	vec3 finalColour = colour;
	finalColour.r = 1.0f;
	
	gl_FragColor = vec4(finalColour, 1.0f);
}
