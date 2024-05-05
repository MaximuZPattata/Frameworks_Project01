#pragma once
#include "pch.h"
#include "OpenGLCommon.h"
#include "DetailsFromFile.h"

#include<rapidjson/filereadstream.h>
#include<rapidjson/stringbuffer.h>
#include<rapidjson/document.h>

// This class is created to read from a Json file
class cJsonReader
{
public:

	bool ReadScene(const std::string& filePath, std::vector <sModelDetailsFromFile>& differentModelDetails, 
		std::vector<sLightDetailsFromFile>& differentLightDetails, sCameraDetailsFromFile& camDetails);

private:

	rapidjson::Document ReadFile(std::string fileName);
};

