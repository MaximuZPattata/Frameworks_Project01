#pragma once
#include "OpenGLCommon.h"
#include "pch.h"

// This struct is created to imitate the model variables in the json file
struct sModelDetailsFromFile
{
	float modelScaleValue;
	bool meshLightsOn;
	bool manualColors;

	std::string modelName;
	std::string modelFilePath;
	std::string meshType;

	glm::vec3 modelColorRGB;
};

// This struct is created to imitate the light variables in the json file
struct sLightDetailsFromFile
{
	int lightId;
	float linearAttenuation;
	float quadraticAttenuation;
	float lightType;
	float innerAngle;
	float outerAngle;
	bool lightOn;

	glm::vec3 lightPosition;
	glm::vec3 lightDirection;
	glm::vec3 lightColorRGB;
};

// This struct is created to imitate the camera variables in the json file
struct sCameraDetailsFromFile
{
	glm::vec3 initialCameraPosition;
};