#pragma once
#include "pch.h"
#include <OpenGLCommon.h>

class cBullet
{
public:
	cBullet();
	~cBullet();

	glm::vec2 position;
	glm::vec2 direction;

	std::string modelName;
	
	float  bulletId;
	float velocity;
	
	bool isShot;
};