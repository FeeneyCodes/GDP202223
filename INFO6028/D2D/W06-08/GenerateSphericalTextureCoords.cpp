// Generates texture coordinates based on a shperical projection from the 
// origin (0,0,0) location of the model. 
// NOTE: Will overwrite any existing texture coordinates 
// Inspired by: http://www.mvps.org/directx/articles/spheremap.htm
// 
//	basedOnNormals = true --> uses normals for calculation, so good for reflections
//	basedOnNormals = false --> uses model coordinates, so more 'shrink wrapped'
//  fast -> approximate or not (not uses sin() )
//  scale -> normally 1.0, but can be the limits of the texture coord
//
// The 'bias' is what coordinates are used for the generation. 
// For example, if POSITIVE_X is for u and POSITIVE_Y is for v, then:
//	u coords: based on -x to +x
//  v coords: based on -y to +y
//

enum enumTEXCOORDBIAS
{
	POSITIVE_X, 
	POSITIVE_Y, 
	POSITIVE_Z
};

// This structure holds the vertex information 
// as listed in the bunny file
struct cPlyVertex
{
	cPlyVertex(): nx(0.0f), ny(0.0f), nz(0.0f), 
				 tex0u(0.0f), tex0v(0.0f), tex1u(0.0f), tex1v(0.0f),
				 red(0), green(0), blue(0) {}
	glm::vec3 xyz; 
	//float x, y, z;
	float nx, ny, nz;
	float tex0u, tex0v;
	float tex1u, tex1v;
	// *********************
	float red, green, blue;
};

void GenerateSphericalTextureCoords( 
	enumTEXCOORDBIAS uBias, enumTEXCOORDBIAS vBias, 
	std::vector<cPlyVertex> &vecVertices;,
	bool basedOnNormals, float scale, bool fast )
{
	// determine the 'remaining' coordinate...
	bool xUsed = false;
	bool yUsed = false;
	bool zUsed = false;
	if ( uBias == POSITIVE_X || vBias == POSITIVE_X )	xUsed = true;
	if ( uBias == POSITIVE_Y || vBias == POSITIVE_Y )	yUsed = true;
	if ( uBias == POSITIVE_Z || vBias == POSITIVE_Z )	yUsed = true;
	
	std::vector<PlyVertex>::iterator itVert;
	for ( itVert = this->vecVertices.begin(); itVert != this->vecVertices.end(); itVert++ )
	{
		glm::vec3 xyz;
		if ( basedOnNormals )
		{
			if ( uBias == POSITIVE_X )		xyz.x = itVert->nx;
			else if ( uBias == POSITIVE_Y )	xyz.x = itVert->ny;
			else if ( uBias == POSITIVE_Z )	xyz.x = itVert->nz;

			if ( vBias == POSITIVE_X )		xyz.y = itVert->nx;
			else if ( vBias == POSITIVE_Y )	xyz.y = itVert->ny;
			else if ( vBias == POSITIVE_Z )	xyz.y = itVert->nz;

			// Fill in the remaining coordinate...
			if ( !xUsed )	xyz.z = itVert->nx;
			if ( !yUsed )	xyz.z = itVert->ny;
			if ( !zUsed )	xyz.z = itVert->nz;
		}
		else
		{
			if ( uBias == POSITIVE_X )		xyz.x = itVert->xyz.x;
			else if ( uBias == POSITIVE_Y )	xyz.x = itVert->xyz.y;
			else if ( uBias == POSITIVE_Z )	xyz.x = itVert->xyz.z;

			if ( vBias == POSITIVE_X )		xyz.y = itVert->xyz.x;
			else if ( vBias == POSITIVE_Y )	xyz.y = itVert->xyz.y;
			else if ( vBias == POSITIVE_Z )	xyz.y = itVert->xyz.z;

			// Fill in the remaining coordinate...
			if ( !xUsed )	xyz.z = itVert->xyz.x;
			if ( !yUsed )	xyz.z = itVert->xyz.y;
			if ( !zUsed )	xyz.z = itVert->xyz.z;
		}

		xyz = glm::normalize(xyz);

		if ( fast )
		{
			itVert->tex0u = ( ( xyz.x / 2.0f) + 0.5f ) * scale;
			itVert->tex0v = ( ( xyz.y / 2.0f) + 0.5f ) * scale;
		}
		else
		{
			itVert->tex0u = ( ( asin(xyz.x) / PI ) + 0.5f ) * scale;
			itVert->tex0v = ( ( asin(xyz.y) / PI ) + 0.5f ) * scale;
		}
		itVert->tex1u = itVert->tex0u;
		itVert->tex1v = itVert->tex0v;
	}
	return;
}
