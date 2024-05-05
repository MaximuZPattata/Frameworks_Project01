#pragma once
#include "pch.h"
#include "cPlayer.h"
#include "cFrameRates.h"
#include "DetailsFromFile.h"
#include "cModelManipulator.h"
#include "sPositionTracker.h"
#include "cGruntEnemyFactory.h"
#include "iEnemyFactory.h"
#include "iEnemy.h"

class cMap
{
public:

	cMap();
	~cMap();

	void Initialize(std::vector <sModelDetailsFromFile>& modelDetailsList, cModelManipulator* modelManipulator, std::vector <sAnimationFrames*>& animationFrameRateList, 
					std::vector <sPositionTracker*>& modelCurrentPositionsList);
	void UpdateMap(std::vector<sAnimationFrames*> animationFrameRate, 
					std::vector<sPositionTracker*> modelCurrentPositionsList);
	void SpawnGruntEnemies(float currentTime, float randomNum, std::vector<sAnimationFrames*> animationFrameRate, std::vector<sPositionTracker*>& modelCurrentPositionsList);

	cPlayer* mThePlayer = NULL;

private:

	cModelManipulator* mModelManipulator = NULL;
	iEnemyFactory* mEnemyFactory;
	cGruntEnemyFactory mGruntFactory;

	std::vector <iEnemy*> mEnemyList;

	float lastCheckedTime = 0.0f;

	void CreatePlayer(std::vector <sModelDetailsFromFile>& modelDetailsList, cModelManipulator* modelManipulator, std::vector <sAnimationFrames*>& animationFrameRate,
						std::vector <sPositionTracker*>& modelCurrentPositionsList);
	void SetWalls(std::vector<sModelDetailsFromFile>& modelDetailsList);
	void UpdatePositions(std::vector<sPositionTracker*> modelCurrentPositionsList, float modelId, std::string meshType, float currentXPos, float currentYPos);
	void CheckAndUpdateProjectiles(float boundaryValue, std::vector <sPositionTracker*> modelCurrentPositionsList);
	void CheckAndUpdateEnemyPositions(std::vector <sPositionTracker*>& modelCurrentPositionsList);
};

