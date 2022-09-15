#include <iostream> 
#include <string>
//#include <fstream>
//#include <sstream>
#include <vector>

#include "myExcitingFunctions.h"

#include "../MichaelCrappyOpenGL/MichaelsCrappyOpenGL.h"

#include <Windows.h>


//float AddSomeNumbers(float myArray[], int arraysize)
float AddSomeNumbers(int arraysize, float* pMyArray)
{
	// 
//	int myGiantArray[2'000'000]			// Stack
	//int* pMyArray = new int[2'000'000];		// Heap

//	int* pX = new int();

	int theArraySize = sizeof(pMyArray);

	float sum = 0.0f;
	for (int index = 0; index != arraysize; index++)
	{
		sum += pMyArray[index];
	}
	return sum;
}

class cPerson
{
	int x;// = 0;
	float y;// = 0.0f;	// C++11 
};
//
//std::string name = "Michael";
//std::string name[] = { "M", "i", "c",....

int main( int argc, char* argv[] )
//int main( int argc, char** argv )
{
//	glDoThat();


//	FARPROC GetProcAddress(
//		[in] HMODULE hModule,
//		[in] LPCSTR  lpProcName
//	);
	FARPROC pMsgBoxFunction = GetProcAddress(NULL, "MessageBoxW");
	FARPROC p_glCompileShader = GetProcAddress(NULL, "glCompileShader");

	MessageBox(NULL, L"HEY!", L"what's up?", MB_OK);
	pMsgBoxFunction(NULL, L"HEY!", L"what's up?");

	p_glCompileShader(3);

//	std::string name = "Michael";
	char name[] = "Michael";
//	char* name;
	//std::string name[] = { "M", "i", "c",....
	std::cout << name[3] << std::endl;


	for (int index = 0; index != argc; index++)
	{
		std::cout << index << ":" << argv[index] << std::endl;
	}

//	unsigned int index = 99;
//	std::string names[10];
//	std::string hey = "hey";
//	int garbage[1000] = { 0 };
//	names[index] = "michael";

	// ON THE STACK
	int myGiantArray[2'000] = { 0 };
//	int myGiantArray[2'000'000] = { 0 };

	int x;		
	x = 9;
	int x1 = 9;

	// Same as 	int x = 9;
	int* pX = new int();	// Same as "int x;"
	*pX = 9;				// int x = 9;

	delete pX;
	
	// 0 nullptr
	// int myGiantArray[2'000'000]			// Stack
	int* pMyArray = new int[2'000'000];		// Heap

	myGiantArray[828] = 3;
	pMyArray[828] = 3;

	delete [] pMyArray;		// Note the syntax


	const int ARRAYSIZE = 10;
	float myArray[ARRAYSIZE];			// 4 bytes
	for ( int index = 0; index != ARRAYSIZE; index++)
	{
		myArray[index] = ((float)rand())/100.0f;
	}

	int theArraySize = sizeof(myArray);

	myArray[0] = 4.5f; 	myArray[1] = 3.42f; myArray[2] = 2.0f;
	float total = AddSomeNumbers(ARRAYSIZE, myArray);

	float y = 4.5f;
	float x2 = 3.42f;
	float a = 2.0f;
	std::cout << AddSomeNumbers(x2, y, a);


	//std::cout << AddSomeNumbers<double>(x, y, a);
	//std::cout << AddSomeNumbers<float>(x, y, a);
	//cNinjaTurtle t1, t2, t3;
	//std::cout << AddSomeNumbers<cNinjaTurtle>(t1, t2, t3);
	//std::cout << t1;



//	std::cout << "Hello GDP'er!" << std::endl;
//
//	int x = 0;
//	std::cin >> x;		// "Michael"
//	std::string MyName;
//	std::cin >> MyName;
//
//	myFile >> myString;
//	ssHey << "a";

	return 0;
}





//float AddSomeNumbers(float a, float b)
//{
//	float sum = a + b;
//	return sum;
//}

//
//std::vector<int, somethng> MyStrangeContainer
//
//for (auto x = 1; x != 3.0f; x += 1.0)
//{
//}
//double x;		// 64 bit (80 bit) 10^308
//float y;		// 32 bit 10^38  10^-37
//int z;			// 32 bit or 64 bit?
//				// +2 billion 2^32 = 4billion
//				// 16 billion billion
//z = x + y;
//
//int z = MAX_INT + 1;	2 ^ 32 = +2 billion
//- 2 billion
//unsigned int z = MAX_INT + 1;	0 to + 4 billion
//2, 000, 000, 000
//16, 000, 000, 000, 000, 000, 000
//
//unsigned long long x;
//
//1 2 3 4
//
//1  111111   111111
//1111 1111 1111 1111 1111 1111 1111 1111
//1 1111111111111111111111111 111111
//
//Pos.xyz =
//Pos.x += 40, 000, 000, 000.0001
//31, 234, 567, 812, 345, 678
//
//moon
//400, 000 km
//400, 000, 000 m
//40, 000, 000, 000 cm
//
//3.1234567812345678 x 10 ^ 0
//32.26725 x 10 ^ 0
//3.236725 x 10 ^ 38
//
//32 bit -> 2 ^ 32
//
//6782.2
//6.7342347329487342978822 x 10 ^ 3
//
//
//1 000 0010	(-2)-- > negative
//0 000 0011  (3)
//
//- 2 + 3 = -5
//
//int index = -2;
//unsigned int index;
//
//myArray[index];
//
//z = x + y;
//
//1 000 0101 - 5
