#pragma once

#include <string>

//float AddSomeNumbers(float, float, float);

//template <class HelloKitty>
//HelloKitty AddSomeNumbers(HelloKitty a1, HelloKitty a2, HelloKitty a3)
//{
//// if type(HelloKitty == double)
////	then this is code you should use
//// it type(HelloKitty == cNinjaTurtle)
////	assert(false)
//	
//	HelloKitty sum = a1 + a2 + a3;
//	return sum;
//}

void PassNumbers(int x);
void PassNumbers(int &x);		// C++ int& x
void PassNumbers(int* x);		// C


float AddSomeNumbers(float a1, float a2, float a3);

//int AddSomeNumbers(int a1, int a2, int a3)
//{
//	int sum = a1 + a2 + a3;
//	return sum;
//}
//
//std::string AddSomeNumbers(std::string a1, std::string a2, std::string a3)
//{
//	std::string sum = a1 + a2 + a3;
//	return sum;
//}

float AndAddTheseFunctions(float a, float b, float c);

// Michael's pretend OpenGL functions
void glDoThis(int numVertices);
void glDoThat();