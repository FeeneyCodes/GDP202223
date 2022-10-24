#pragma once

#include <string>

// Here's a type that holds all the animal data
struct sAnimalData
{
	void Initialize(void)
	{
		this->health = 100.0f;
		this->weight = 0.0f;
		this->height = 0.0f;
	};
	std::string name;
	std::string soundIMake;
	float health;		// 0 to 100
	float weight;
	float height;
	unsigned int numberOfLegs;
};
