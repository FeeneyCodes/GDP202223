#version 420
// Geometry shader
layout(triangles) 			in;
layout(triangle_strip)		out;
layout(max_vertices = 6)	out;

// Coming in from the vertex shader
in vec4 gColour[];		// colour;			
in vec4 gNormal[];
in vec4 gVertWorldLocation[];	// using only matModel
in vec4 gUVx2[];
in vec4 gTangent[];
in vec4 gBinormal[];

// Going out to the fragment shader
out vec4 fColour;		// colour;			
out vec4 fNormal;
out vec4 fVertWorldLocation;	// using only matModel
out vec4 fUVx2;
out vec4 fTangent;
out vec4 fBinormal;

void main()
{
	// Pass through original triangle:
	gl_Position = gl_in[0].gl_Position;
	fColour = gColour[0];		// colour;			
	fNormal = gNormal[0];
	fVertWorldLocation = gVertWorldLocation[0];	// using only matModel
	fUVx2 = gUVx2[0];
	fTangent = gTangent[0];
	fBinormal = gBinormal[0];
	EmitVertex();
	
	gl_Position = gl_in[1].gl_Position;
	fColour = gColour[1];		// colour;			
	fNormal = gNormal[1];
	fVertWorldLocation = gVertWorldLocation[1];	// using only matModel
	fUVx2 = gUVx2[1];
	fTangent = gTangent[1];
	fBinormal = gBinormal[1];
	EmitVertex();
	
	gl_Position = gl_in[2].gl_Position;
	fColour = gColour[2];		// colour;			
	fNormal = gNormal[2];
	fVertWorldLocation = gVertWorldLocation[2];	// using only matModel
	fUVx2 = gUVx2[2];
	fTangent = gTangent[2];
	fBinormal = gBinormal[2];
	EmitVertex();
	
	EndPrimitive();
	
	// Now draw another triangle to show the normal
	
	// Find the centre of the triangle
	vec3 normalStartVertex = ( gVertWorldLocation[0].xyz +
							   gVertWorldLocation[1].xyz + 
							   gVertWorldLocation[2].xyz ) / 3.0f;
	// Find the other end of this "line"
	vec3 normalAverage = ( gNormal[0].xyz +
						   gNormal[1].xyz + 
						   gNormal[2].xyz ) / 3.0f;
							
	const float NORMAL_LENGTH = 50.0f;
	vec3 normalEndVertex = normalStartVertex + (normalAverage * NORMAL_LENGTH);
	
	gl_Position.xyz = normalStartVertex.xyz;
	fColour.rgba = vec4(1.0f, 1.0f, 1.0f, 0.0f);		// colour;			
	fNormal = gNormal[2];
	fVertWorldLocation.xyz = normalStartVertex.xyz;	// using only matModel
	fUVx2 = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	fTangent = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	fBinormal = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	EmitVertex();
	
	gl_Position.xyz = normalStartVertex.xyz;
	fColour.rgba = vec4(1.0f, 1.0f, 1.0f, 0.0f);		// colour;			
	fNormal = gNormal[2];
	fVertWorldLocation.xyz = normalStartVertex.xyz;	// using only matModel
	fUVx2 = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	fTangent = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	fBinormal = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	EmitVertex();
	
	gl_Position.xyz = normalEndVertex.xyz;
	fColour.rgba = vec4(1.0f, 1.0f, 1.0f, 0.0f);		// colour;			
	fNormal = gNormal[2];
	fVertWorldLocation.xyz = normalEndVertex.xyz;	// using only matModel
	fUVx2 = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	fTangent = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	fBinormal = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	EmitVertex();
	
	EndPrimitive();
	
	
}