#include "pch.h"
#include "cJsonReader.h"

rapidjson::Document cJsonReader::ReadFile(std::string fileName)
{
	using namespace rapidjson;

	Document docReadObj;
	char readBuffer[65536];
	FILE* filePointer = 0; // Initializing filePointer to read from opened file
	errno_t errorChecker;

	docReadObj.SetObject(); // docReadObj initialized to parse JSON data

	errorChecker = fopen_s(&filePointer, fileName.c_str(), "rb");

	if (errorChecker != 0)
	{
		std::cout << "Error while reading the file - " << fileName << std::endl;
		return NULL;
	}

	FileReadStream inputStream(filePointer, readBuffer, sizeof(readBuffer));

	// Parses JSON data from inputStream onto docReadObj 
	docReadObj.ParseStream(inputStream);

	fclose(filePointer);

	return docReadObj;
}

bool cJsonReader::ReadScene(const std::string& filePath, std::vector <sModelDetailsFromFile>& differentModelDetails, std::vector<sLightDetailsFromFile>& differentLightDetails, sCameraDetailsFromFile& camDetails)
{
	using namespace rapidjson;

	Document docObj;

	docObj.SetObject();
	docObj = ReadFile(filePath);

	if (docObj.HasParseError())
	{
		std::cerr << "Failed to parse JSON." << std::endl;
		return false;
	}

	const Value& modelArray = docObj["ModelProperties"];
	const Value& lightingArray = docObj["LightProperties"];
	const Value& cameraInfo = docObj["CameraProperties"];

	for (SizeType modelIndex = 0; modelIndex < modelArray.Size(); modelIndex++)
	{
		const Value& modelDetails = modelArray[modelIndex];

		sModelDetailsFromFile newModelDetails;

		newModelDetails.modelName = modelDetails["ModelName"].GetString();
		newModelDetails.modelFilePath = modelDetails["FilePath"].GetString();
		newModelDetails.modelScaleValue = modelDetails["Scale"].GetFloat();
		newModelDetails.meshLightsOn = modelDetails["bMeshLightsOn"].GetBool();
		newModelDetails.manualColors = modelDetails["bUseManualColors"].GetBool();
		newModelDetails.modelColorRGB.r = modelDetails["Color"][0].GetFloat();
		newModelDetails.modelColorRGB.g = modelDetails["Color"][1].GetFloat();
		newModelDetails.modelColorRGB.b = modelDetails["Color"][2].GetFloat();
		newModelDetails.meshType = modelDetails["MeshType"].GetString();

		differentModelDetails.push_back(newModelDetails);
	}

	if (lightingArray.IsArray())
	{
		for (SizeType lightingIndex = 0; lightingIndex < lightingArray.Size(); lightingIndex++)
		{
			const Value& lightDetails = lightingArray[lightingIndex];

			sLightDetailsFromFile newLightDetails;

			newLightDetails.lightId = lightDetails["LightId"].GetInt();
			newLightDetails.lightOn = lightDetails["bLightOn"].GetBool();
			newLightDetails.lightType = lightDetails["LightType"].GetFloat();
			newLightDetails.linearAttenuation = lightDetails["LinearAttenuation"].GetFloat();
			newLightDetails.quadraticAttenuation = lightDetails["QuadraticAttenuation"].GetFloat();
			newLightDetails.innerAngle = lightDetails["InnerAngle"].GetFloat();
			newLightDetails.outerAngle = lightDetails["OuterAngle"].GetFloat();
			newLightDetails.lightPosition.x = lightDetails["LightPosition"][0].GetFloat();
			newLightDetails.lightPosition.y = lightDetails["LightPosition"][1].GetFloat();
			newLightDetails.lightPosition.z = lightDetails["LightPosition"][2].GetFloat();
			newLightDetails.lightColorRGB.r = lightDetails["LightColor"][0].GetFloat();
			newLightDetails.lightColorRGB.g = lightDetails["LightColor"][1].GetFloat();
			newLightDetails.lightColorRGB.b = lightDetails["LightColor"][2].GetFloat();
			newLightDetails.lightDirection.x = lightDetails["LightDirection"][0].GetFloat();
			newLightDetails.lightDirection.y = lightDetails["LightDirection"][1].GetFloat();
			newLightDetails.lightDirection.z = lightDetails["LightDirection"][2].GetFloat();

			differentLightDetails.push_back(newLightDetails);
		}
	}

	else
	{
		sLightDetailsFromFile newLightDetails;

		newLightDetails.lightId = lightingArray["LightId"].GetInt();
		newLightDetails.lightOn = lightingArray["bLightOn"].GetBool();
		newLightDetails.lightType = lightingArray["LightType"].GetFloat();
		newLightDetails.linearAttenuation = lightingArray["LinearAttenuation"].GetFloat();
		newLightDetails.quadraticAttenuation = lightingArray["QuadraticAttenuation"].GetFloat();
		newLightDetails.innerAngle = lightingArray["InnerAngle"].GetFloat();
		newLightDetails.outerAngle = lightingArray["OuterAngle"].GetFloat();
		newLightDetails.lightPosition.x = lightingArray["LightPosition"][0].GetFloat();
		newLightDetails.lightPosition.y = lightingArray["LightPosition"][1].GetFloat();
		newLightDetails.lightPosition.z = lightingArray["LightPosition"][2].GetFloat();
		newLightDetails.lightColorRGB.r = lightingArray["LightColor"][0].GetFloat();
		newLightDetails.lightColorRGB.g = lightingArray["LightColor"][1].GetFloat();
		newLightDetails.lightColorRGB.b = lightingArray["LightColor"][2].GetFloat();
		newLightDetails.lightDirection.x = lightingArray["LightDirection"][0].GetFloat();
		newLightDetails.lightDirection.y = lightingArray["LightDirection"][1].GetFloat();
		newLightDetails.lightDirection.z = lightingArray["LightDirection"][2].GetFloat();

		differentLightDetails.push_back(newLightDetails);
	}

	camDetails.initialCameraPosition.x = cameraInfo["CameraPosition"][0].GetFloat();
	camDetails.initialCameraPosition.y = cameraInfo["CameraPosition"][1].GetFloat();
	camDetails.initialCameraPosition.z = cameraInfo["CameraPosition"][2].GetFloat();

	return true;
}

