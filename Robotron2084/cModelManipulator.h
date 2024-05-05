#pragma once
#include "pch.h"
#include "DetailsFromFile.h"
#include <cControlGameEngine.h>

class cModelManipulator
{
public:
	void Initialize(cControlGameEngine* gameEngine, std::vector <sModelDetailsFromFile>& modelDetailsList);

	void LoadModels(std::string meshType, std::string modelName, float initial_x, float initial_y); // Used for character movement

	void LoadModelsWithoutNameCheck(std::string meshType, std::string modelName, float initial_x, float initial_y); // Used for setting walls

	void LoadModelWithNewName(std::string meshType, std::string modelName, std::string newModelName, float initial_x, float initial_y); // Used for projectiles

	void MoveModels(std::string modelName, float translate_x, float translate_y, float translate_z);

	void ScaleModel(std::string modelModel, float scale_value);

	void MeshLightsOn(std::string modelModel);

	void MeshColorChange(std::string modelName, float r, float g, float b);

	void ConfirmManualColoring(std::string modelName, bool useColor);

	void DeleteModel(std::string modelName);

	glm::vec2 Get2DModelPosition(std::string modelName);

private:
	cControlGameEngine* mEngine;

	std::vector <sModelDetailsFromFile> mModelInfoList;

};

