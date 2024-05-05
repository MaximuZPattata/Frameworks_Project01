#include "pch.h"
#include "cModelManipulator.h"

void cModelManipulator::Initialize(cControlGameEngine* gameEngine, std::vector <sModelDetailsFromFile>& modelDetailsList)
{
	mEngine = gameEngine;
	mModelInfoList = modelDetailsList;
}

void cModelManipulator::LoadModels(std::string meshType, std::string modelName, float initial_x, float initial_y)
{
	for (int index = 0; index < mModelInfoList.size(); index++)
	{
		if (mModelInfoList[index].meshType == meshType && mModelInfoList[index].modelName == modelName)
		{
			mEngine->LoadModelsInto3DSpace(mModelInfoList[index].modelFilePath, modelName, initial_x, initial_y, 0.0f);
			mEngine->ScaleModel(modelName, mModelInfoList[index].modelScaleValue);
			mEngine->TurnMeshLightsOn(modelName);

			if (mModelInfoList[index].manualColors)
			{
				mEngine->UseManualColors(modelName, mModelInfoList[index].manualColors);

				mEngine->ChangeColor(modelName, mModelInfoList[index].modelColorRGB.r,
					mModelInfoList[index].modelColorRGB.g, mModelInfoList[index].modelColorRGB.b);
			}
		}
	}
}

void cModelManipulator::LoadModelsWithoutNameCheck(std::string meshType, std::string modelName, float initial_x, float initial_y)
{
	for (int index = 0; index < mModelInfoList.size(); index++)
	{
		if (mModelInfoList[index].meshType == meshType)
		{
			mEngine->LoadModelsInto3DSpace(mModelInfoList[index].modelFilePath, modelName, initial_x, initial_y, 0.0f);
			mEngine->ScaleModel(modelName, mModelInfoList[index].modelScaleValue);
			mEngine->TurnMeshLightsOn(modelName);

			if (mModelInfoList[index].manualColors)
			{
				mEngine->UseManualColors(modelName, mModelInfoList[index].manualColors);

				mEngine->ChangeColor(modelName, mModelInfoList[index].modelColorRGB.r,
					mModelInfoList[index].modelColorRGB.g, mModelInfoList[index].modelColorRGB.b);
			}
		}
	}
}

void cModelManipulator::LoadModelWithNewName(std::string meshType, std::string modelName, std::string newModelName, float initial_x, float initial_y)
{
	for (int index = 0; index < mModelInfoList.size(); index++)
	{
		if (mModelInfoList[index].meshType == meshType && mModelInfoList[index].modelName == modelName)
		{
			mEngine->LoadModelsInto3DSpace(mModelInfoList[index].modelFilePath, newModelName, initial_x, initial_y, 0.0f);
			mEngine->ScaleModel(newModelName, mModelInfoList[index].modelScaleValue);
			mEngine->TurnMeshLightsOn(newModelName);

			if (mModelInfoList[index].manualColors)
			{
				mEngine->UseManualColors(newModelName, mModelInfoList[index].manualColors);

				mEngine->ChangeColor(newModelName, mModelInfoList[index].modelColorRGB.r,
					mModelInfoList[index].modelColorRGB.g, mModelInfoList[index].modelColorRGB.b);
			}
		}
	}
}

void cModelManipulator::MoveModels(std::string modelName, float translate_x, float translate_y, float translate_z)
{
	mEngine->MoveModel(modelName, translate_x, translate_y, translate_z);
}


void cModelManipulator::ScaleModel(std::string modelModel, float scale_value)
{
	mEngine->ScaleModel(modelModel, scale_value);
}

void cModelManipulator::MeshLightsOn(std::string modelName)
{
	mEngine->TurnMeshLightsOn(modelName);
}

void cModelManipulator::MeshColorChange(std::string modelName, float r, float g, float b)
{
	mEngine->ChangeColor(modelName, r, g, b);
}

void cModelManipulator::ConfirmManualColoring(std::string modelName, bool useColor)
{
	mEngine->UseManualColors(modelName, useColor);
}

void cModelManipulator::DeleteModel(std::string modelName)
{
	mEngine->DeleteMesh(modelName);
}

glm::vec2 cModelManipulator::Get2DModelPosition(std::string modelName)
{
	glm::vec2 model2DPos;
	glm::vec3 model3DPos;

	model3DPos = mEngine->GetModelPosition(modelName);
	model2DPos.x = model3DPos.x;
	model2DPos.y = model3DPos.y;

	return model2DPos;
}