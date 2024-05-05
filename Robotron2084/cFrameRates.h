#pragma once
#include "pch.h"
#include "DetailsFromFile.h"
#include "cModelManipulator.h"

// This struct is created to check if animation is being played by a character and imitate a structure for an animation framerate
struct sAnimationFrames
{
	bool isActivated = false;
	int FrameRateValue = 0;
	std::string previousModelName = "";
	std::string newGivenModelName = "";
	std::vector < std::string > animationSet;
	std::string meshType = "";
	unsigned int modelId = 0;
	float xPos = 0.0f;
	float yPos = 0.0f;
};

// This class is created to increment/update framerate
class cFrameRates
{

public:
	void UpdateFrameRates(std::vector < sAnimationFrames* >& animationFrames);
};

