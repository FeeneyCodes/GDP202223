#include <iostream> 
#include <string>
//#include <fstream>
//#include <sstream>

#include "myExcitingFunctions.h"


int main( int argc, char* argv[] )
{
//	unsigned int index = 99;
//	std::string names[10];
//	std::string hey = "hey";
//	int garbage[1000] = { 0 };
//	names[index] = "michael";

	float myArray[3];
	myArray[0] = 4.5f;
	myArray[1] = 3.42f;
	myArray[2] = 2.0f;
//	float total = AddSomeNumbers( ? ? ? );

	float y = 4.5f;
	float x = 3.42f;
	float a = 2.0f;
	std::cout << AddSomeNumbers(x, y, a);

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
