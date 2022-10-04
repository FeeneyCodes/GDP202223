// Vertex shader
#version 420

in vec3 vCol;
in vec3 vPos;

out vec3 colour;			// varying

//uniform mat4 MVP;
uniform mat4 mModel;
uniform mat4 mView;
uniform mat4 mProjection;

void main()
{
	vec3 vertPosition = vPos;
	
//	vertPosition.xyz *= 0.1f;
//	vertPosition.x += 10.0f;
	
	// Output is in screen space 
	// x & y are in (normalized) screen space, z is the depth from the camera
	mat4 mMVP = mProjection * mView * mModel;
	
	gl_Position = mMVP * vec4(vertPosition, 1.0f);
	colour = vCol;
}
