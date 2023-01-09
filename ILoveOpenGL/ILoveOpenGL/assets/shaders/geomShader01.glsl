#version 420
// Geometry shader
layout(triangles) 			in;
layout(triangle_strip)		out;
layout(max_vertices = 3)	out;

// Coming in from the vertex shader
in vec4 gColour;		// colour;			
in vec4 gNormal;
in vec4 gVertWorldLocation;	// using only matModel
in vec4 gUVx2;
in vec4 gTangent;
in vec4 gBinormal;

// Going out to the fragment shader
out vec4 fColour;		// colour;			
out vec4 fNormal;
out vec4 fVertWorldLocation;	// using only matModel
out vec4 fUVx2;
out vec4 fTangent;
out vec4 fBinormal;

void main()
{

	// TODO: VERY exciting code to come!!
	
	
}