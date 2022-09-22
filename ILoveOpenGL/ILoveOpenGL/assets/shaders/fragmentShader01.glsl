//Fragment shader
#version 420

in vec3 colour;			// varying

// This replaces gl_FragColor
out vec4 pixelOutputColour;

void main()
{
	vec3 finalColour = colour;
	finalColour.r = 1.0f;
	
	//gl_FragColor = vec4(finalColour, 1.0f);
	pixelOutputColour = vec4(finalColour, 1.0f);
}
