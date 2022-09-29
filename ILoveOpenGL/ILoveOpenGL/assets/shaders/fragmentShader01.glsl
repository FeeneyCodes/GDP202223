//Fragment shader
#version 420

in vec3 colour;			// varying

// This replaces gl_FragColor
out vec4 pixelOutputColour;

uniform vec4 RGBA_Colour;
uniform bool bUseRGBA_Colour;

void main()
{
	vec3 finalColour = colour;
//	finalColour.r = 1.0f;

	if ( bUseRGBA_Colour )
	{
		finalColour = RGBA_Colour.rgb;
	}
	
	//gl_FragColor = vec4(finalColour, 1.0f);
	pixelOutputColour = vec4(finalColour, 1.0f);
}
