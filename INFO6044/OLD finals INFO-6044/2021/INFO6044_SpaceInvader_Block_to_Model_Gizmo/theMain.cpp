#include <iostream>
#include <fstream>
#include <vector>


class cVertex
{
public:
	cVertex()
	{
		this->x = this->y = this->z = 0.0f;
		this->nx = this->ny = this->nz = 0.0f;
		this->r = this->g = this->b = this->a = 1.0f;
		this->u = this->v = 0.0f;
	}
	cVertex(float x_, float y_, float z_, float nx_, float ny_, float nz_, float r_, float g_, float b_, float a_, float u_, float v_)
	{
		this->x = x_;		this->y = y_;		this->z = z_;
		this->r = r_;		this->g = g_;		this->b = b_;		this->a = a_;
		this->nx = nx_;		this->ny = ny_;		this->nz = nz_;
		this->u = u_;		this->v = v_;
	}
	cVertex(double x_, double y_, double z_, double nx_, double ny_, double nz_, 
			unsigned char r_, unsigned char g_, unsigned char b_, unsigned char a_, 
			double u_, double v_)
	{
		this->x = (float)x_;		this->y = (float)y_;		this->z = (float)z_;
		this->r = (float)r_/255.0f;		
		this->g = (float)g_/255.0f;		
		this->b = (float)b_/255.0f;		
		this->a = (float)a_/255.0f;
		this->nx = (float)nx_;		this->ny = (float)ny_;		this->nz = (float)nz_;
		this->u = (float)u_;		this->v = (float)v_;
	}
	float x, y, z;
	float nx,ny,nz;
	float r,g,b,a;
	float u,v;
};

class cTriangle
{
public:
	cTriangle()
	{
		this->index[0] = this->index[1] = this->index[2] = 0;
	}
	cTriangle(unsigned int index0, unsigned int index1, unsigned int index2)
	{
		this->index[0] = index0;
		this->index[1] = index1;
		this->index[2] = index2;
	}
	unsigned int index[3];
};

class cCube
{
public:
	cCube() {};
	std::vector<cVertex> vecVertices;
	std::vector<cTriangle> vecTris;
};

const float CUBE_WIDTH = 10.0f;


void centreOnX(std::vector<cVertex>& vecVertices)
{
	if ( vecVertices.empty() )
	{
		return;
	}

	float minX = vecVertices[0].x;
	float maxX = vecVertices[0].x;

	for ( unsigned int vertIndex = 0; vertIndex != vecVertices.size(); vertIndex++ )
	{
		if ( vecVertices[vertIndex].x < minX ) { minX = vecVertices[vertIndex].x; }
		if ( vecVertices[vertIndex].x > maxX ) { maxX = vecVertices[vertIndex].x; }
	}

	float midX = (maxX - minX - CUBE_WIDTH)/2.0f;

	for ( unsigned int vertIndex = 0; vertIndex != vecVertices.size(); vertIndex++ )
	{
		vecVertices[vertIndex].x -= midX;
	}

	return;
}

void alightBaseToXZPlane(std::vector<cVertex>& vecVertices)
{
	if ( vecVertices.empty() )
	{
		return;
	}

	float minY = vecVertices[0].y;

	for ( unsigned int vertIndex = 0; vertIndex != vecVertices.size(); vertIndex++ )
	{
		if ( vecVertices[vertIndex].y < minY ) { minY = vecVertices[vertIndex].y; }
	}

	for ( unsigned int vertIndex = 0; vertIndex != vecVertices.size(); vertIndex++ )
	{
		vecVertices[vertIndex].y -= minY;
	}

	return;
}

void addCubeToVector(std::vector<cVertex>& vecVertices, std::vector<cTriangle>& vecTris, cCube &cube, float xOffset, float yOffset, float zOffset)
{

	for ( unsigned int triIndex = 0; triIndex != cube.vecTris.size(); triIndex++ )
	{
		unsigned int vertBaseIndex = (unsigned int)vecVertices.size();

		// Get triangle vertices
		cVertex vert0 = cube.vecVertices[ (cube.vecTris[triIndex].index[0]) ];
		cVertex vert1 = cube.vecVertices[ (cube.vecTris[triIndex].index[1]) ];
		cVertex vert2 = cube.vecVertices[ (cube.vecTris[triIndex].index[2]) ];

		vert0.x += xOffset;
		vert0.y += yOffset;
		vert0.z += zOffset;

		vert1.x += xOffset;
		vert1.y += yOffset;
		vert1.z += zOffset;

		vert2.x += xOffset;
		vert2.y += yOffset;
		vert2.z += zOffset;

		cTriangle curTri;
		curTri.index[0] = vertBaseIndex;
		curTri.index[1] = vertBaseIndex + 1;
		curTri.index[2] = vertBaseIndex + 2;

		vecVertices.push_back(vert0);
		vecVertices.push_back(vert1);
		vecVertices.push_back(vert2);

		vecTris.push_back(curTri);

	}

	return;
}

void printPlyFile(std::vector<cVertex>& vecVertices, std::vector<cTriangle>& vecTris);

int main(int argc, char* argv[])
{
	if ( argc != 2 )
	{
		std::cout << "Usage: exe block_filename" << std::endl;
		std::cout << std::endl;
		std::cout << "(You can also drop the block file onto the exe)" << std::endl;
		std::cout << std::endl;
		return -1;
	}

	// Make cube
	cCube theCube;
	theCube.vecVertices.push_back(cVertex(-5, 0, 5, 0, -1, 0, 255, 255, 255, 255, 0.666667, 0.000000));
	theCube.vecVertices.push_back(cVertex(-5, 0, -5, 0, -1, 0, 255, 255, 255, 255, 0.666667, 0.333333));
	theCube.vecVertices.push_back(cVertex(5, 0, -5, 0, -1, 0, 255, 255, 255, 255, 0.333333, 0.333333));
	theCube.vecVertices.push_back(cVertex(5, 0, 5, -0, -1, -0, 255, 255, 255, 255, 0.333333, 0.000000));
	theCube.vecVertices.push_back(cVertex(5, 10, -5, -0, 1, 0, 255, 255, 255, 255, 0.333333, 0.333333));
	theCube.vecVertices.push_back(cVertex(-5, 10, -5, -0, 1, 0, 255, 255, 255, 255, 0.333333, 0.666667));
	theCube.vecVertices.push_back(cVertex(-5, 10, 5, -0, 1, 0, 255, 255, 255, 255, 0.000000, 0.666667));
	theCube.vecVertices.push_back(cVertex(5, 10, 5, 0, 1, 0, 255, 255, 255, 255, 0.000000, 0.333333));
	theCube.vecVertices.push_back(cVertex(5, 0, -5, 0, 0, -1, 255, 255, 255, 255, 1.000000, 0.000000));
	theCube.vecVertices.push_back(cVertex(-5, 0, -5, 0, 0, -1, 255, 255, 255, 255, 1.000000, 0.333333));
	theCube.vecVertices.push_back(cVertex(-5, 10, -5, 0, 0, -1, 255, 255, 255, 255, 0.666667, 0.333333));
	theCube.vecVertices.push_back(cVertex(5, 10, -5, -0, -0, -1, 255, 255, 255, 255, 0.666667, 0.000000));
	theCube.vecVertices.push_back(cVertex(5, 0, 5, 1, 0, -0, 255, 255, 255, 255, 0.000000, 0.000000));
	theCube.vecVertices.push_back(cVertex(5, 0, -5, 1, 0, -0, 255, 255, 255, 255, 0.333333, 0.000000));
	theCube.vecVertices.push_back(cVertex(5, 10, -5, 1, 0, -0, 255, 255, 255, 255, 0.333333, 0.333333));
	theCube.vecVertices.push_back(cVertex(5, 10, 5, 1, 0, 0, 255, 255, 255, 255, 0.000000, 0.333333));
	theCube.vecVertices.push_back(cVertex(-5, 0, 5, 0, 0, 1, 255, 255, 255, 255, 0.333333, 0.666667));
	theCube.vecVertices.push_back(cVertex(5, 0, 5, 0, 0, 1, 255, 255, 255, 255, 0.333333, 1.000000));
	theCube.vecVertices.push_back(cVertex(5, 10, 5, 0, 0, 1, 255, 255, 255, 255, 0.000000, 1.000000));
	theCube.vecVertices.push_back(cVertex(-5, 10, 5, -0, 0, 1, 255, 255, 255, 255, 0.000000, 0.666667));
	theCube.vecVertices.push_back(cVertex(-5, 0, -5, -1, -0, -0, 255, 255, 255, 255, 0.666667, 0.666667));
	theCube.vecVertices.push_back(cVertex(-5, 0, 5, -1, -0, -0, 255, 255, 255, 255, 0.333333, 0.666667));
	theCube.vecVertices.push_back(cVertex(-5, 10, 5, -1, -0, -0, 255, 255, 255, 255, 0.333333, 0.333333));
	theCube.vecVertices.push_back(cVertex(-5, 10, -5, -1, -0, 0, 255, 255, 255, 255, 0.666667, 0.333333));

	theCube.vecTris.push_back(cTriangle(0, 1, 2));
	theCube.vecTris.push_back(cTriangle(0, 2, 3));
	theCube.vecTris.push_back(cTriangle(4, 5, 6));
	theCube.vecTris.push_back(cTriangle(4, 6, 7));
	theCube.vecTris.push_back(cTriangle(8, 9, 10));
	theCube.vecTris.push_back(cTriangle(8, 10, 11));
	theCube.vecTris.push_back(cTriangle(12, 13, 14));
	theCube.vecTris.push_back(cTriangle(12, 14, 15));
	theCube.vecTris.push_back(cTriangle(16, 17, 18));
	theCube.vecTris.push_back(cTriangle(16, 18, 19));
	theCube.vecTris.push_back(cTriangle(20, 21, 22));
	theCube.vecTris.push_back(cTriangle(20, 22, 23));


	std::ifstream blockFile(argv[1]);
	//std::ifstream blockFile("Space_Invader_Block_Files/SpaceInvader_I1_block_pose_1.txt");

	std::vector<std::string> vecBlockChars;

	while ( !blockFile.eof() )
	{
		const unsigned int BUFFER_SIZE = 1024;
		char lineBuffer[BUFFER_SIZE];
		memset(lineBuffer, 0, BUFFER_SIZE);

		blockFile.getline(lineBuffer, BUFFER_SIZE);

		std::string tempString(lineBuffer);

		vecBlockChars.push_back(tempString);
	};

	std::vector<cVertex> vecVertices;
	std::vector<cTriangle> vecTriangles;

	// Convert the block file into ply blocks
	for ( unsigned int row = 0; row != vecBlockChars.size(); row++ )
	{
		for ( unsigned int col = 0; col != vecBlockChars[row].size(); col++ )
		{
			float row_offset = (float)(vecBlockChars.size() - row) * CUBE_WIDTH;
			float col_offset = (float)col * CUBE_WIDTH;

			if ( vecBlockChars[row][col] == 'X' )
			{
				addCubeToVector(vecVertices, vecTriangles, theCube, col_offset, row_offset, 0.0f );
			}
			//addCubeToVector(vecVertices, vecTriangles, theCube, 0.0f, 0.0f, 0.0f );

		}//for ( unsigned int col
	}//for ( unsigned int row

	centreOnX(vecVertices);
	alightBaseToXZPlane(vecVertices);

	printPlyFile(vecVertices, vecTriangles);

	return 0;
}

void printPlyFile(std::vector<cVertex> &vecVertices, std::vector<cTriangle> &vecTris)
{
	std::ofstream outFile("block_model.ply");

	outFile << "ply" << std::endl;
	outFile << "format ascii 1.0" << std::endl;
	outFile << "comment VCGLIB generated" << std::endl;
	outFile << "element vertex " << vecVertices.size() << std::endl;
	outFile << "property float x" << std::endl;
	outFile << "property float y" << std::endl;
	outFile << "property float z" << std::endl;
	outFile << "property float nx" << std::endl;
	outFile << "property float ny" << std::endl;
	outFile << "property float nz" << std::endl;
	outFile << "property uchar red" << std::endl;
	outFile << "property uchar green" << std::endl;
	outFile << "property uchar blue" << std::endl;
	outFile << "property uchar alpha" << std::endl;
	outFile << "property float texture_u" << std::endl;
	outFile << "property float texture_v" << std::endl;
	outFile << "element face " << vecTris.size() << std::endl;
	outFile << "property list uchar int vertex_indices" << std::endl;
	outFile << "end_header" << std::endl;
	
	for ( unsigned int index = 0; index != vecVertices.size(); index++ )
	{
		outFile 
			<< vecVertices[index].x << " "
			<< vecVertices[index].y << " "
			<< vecVertices[index].z << " "
			<< vecVertices[index].nx << " "
			<< vecVertices[index].ny << " "
			<< vecVertices[index].nz << " "
			<< (unsigned int)( vecVertices[index].r * 255.0f ) << " "
			<< (unsigned int)( vecVertices[index].g * 255.0f ) << " "
			<< (unsigned int)( vecVertices[index].b * 255.0f ) << " "
			<< (unsigned int)( vecVertices[index].a * 255.0f ) << " "
			<< vecVertices[index].u << " "
			<< vecVertices[index].v << std::endl;
	}//for ( unsigned int index = 0;

	for ( unsigned int index = 0; index != vecTris.size(); index++ )
	{
		outFile 
			<< "3 "
			<< vecTris[index].index[0] << " "
			<< vecTris[index].index[1] << " "
			<< vecTris[index].index[2] << std::endl;
	}//for ( unsigned int index = 0


	outFile.close();

	return;
}
