#pragma once
#include "pch.h"
#include "cFrameRates.h"
#include "DetailsFromFile.h"
#include "cModelManipulator.h"
#include "sPositionTracker.h"
#include "eDirection.h"

// Abstract Product
class iEnemy 
{

public:
    virtual ~iEnemy() {};

    virtual void Initialize(cModelManipulator* modelManipulator, std::vector <sAnimationFrames*>& animationFrameRate, 
                            std::vector <sPositionTracker*>& modelCurrentPositionsList, float randomXPos, float randomYPos) = 0;
    virtual void EnemyDirectionChange(eDirection enemyDir) = 0;

    virtual std::string GetUniqueModelName() = 0;
};
