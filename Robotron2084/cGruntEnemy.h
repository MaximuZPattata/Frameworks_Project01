#pragma once
#include "pch.h"
#include "cFrameRates.h"
#include "DetailsFromFile.h"
#include "cModelManipulator.h"
#include "sPositionTracker.h"
#include "eDirection.h"
#include "iEnemy.h"

class cGruntEnemy : public iEnemy
{
public:
    cGruntEnemy();
    ~cGruntEnemy();

    void Initialize(cModelManipulator* modelManipulator, std::vector <sAnimationFrames*>& animationFrameRate,
                    std::vector <sPositionTracker*>& modelCurrentPositionsList, float randomXPos, float randomYPos);
    void EnemyDirectionChange(eDirection enemyDir);

    std::string GetUniqueModelName();

private:
    sAnimationFrames* mGruntAnimationFrameRate;
    sPositionTracker* mGruntPosition;

    std::string uniqueModelName;
};

