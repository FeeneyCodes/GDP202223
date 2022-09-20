//Fragment shader
#version 110

varying vec3 colour;

void main()
{
	vec3 finalColour = colour;
	finalColour.r = 1.0;
	
	gl_FragColor = vec4(finalColour, 1.0);
}
