#include "pch.h"
#include "cGruntEnemy.h"

cGruntEnemy::cGruntEnemy()
{
    std::cout << "Grunt created !" << std::endl;

    mGruntAnimationFrameRate = new sAnimationFrames();
    mGruntPosition = new sPositionTracker();
}

cGruntEnemy::~cGruntEnemy()
{
    delete mGruntAnimationFrameRate;
    delete mGruntPosition;
}

void cGruntEnemy::Initialize(cModelManipulator* modelManipulator, std::vector <sAnimationFrames*>& animationFrameRate,
    std::vector <sPositionTracker*>& modelCurrentPositionsList, float randomXPos, float randomYPos)
{
    std::string modelName = "Grunt_1";
    std::string meshType = "Grunt";
    float xPos = randomXPos;
    float yPos = randomYPos;

    //------------Initialize position and framerate--------------------

    mGruntAnimationFrameRate->meshType = meshType;
    mGruntAnimationFrameRate->previousModelName = modelName;
    mGruntAnimationFrameRate->newGivenModelName = modelName + "_" + std::to_string(xPos) + std::to_string(yPos);
    mGruntAnimationFrameRate->animationSet.push_back("Grunt_1");
    mGruntAnimationFrameRate->animationSet.push_back("Grunt_2");
    mGruntAnimationFrameRate->animationSet.push_back("Grunt_3");

    uniqueModelName = mGruntAnimationFrameRate->newGivenModelName;

    mGruntPosition->meshType = meshType;
    mGruntPosition->modelName = uniqueModelName;
    mGruntPosition->modelRadius = 5.0f;
    mGruntPosition->modelXPos = xPos;
    mGruntPosition->modelYPos = yPos;

    //--------------------Add to the list-------------------------------

    modelCurrentPositionsList.push_back(mGruntPosition);
    animationFrameRate.push_back(mGruntAnimationFrameRate);

    //-------------------Load Player model------------------------------

    modelManipulator->LoadModelWithNewName(meshType, modelName, mGruntAnimationFrameRate->newGivenModelName, xPos, yPos);
}

void cGruntEnemy::EnemyDirectionChange(eDirection enemyDir)
{
    float movementDistance = 1.5f;


    switch (enemyDir)
    {
    case UP:

        mGruntAnimationFrameRate->xPos = 0.0f;
        mGruntAnimationFrameRate->yPos = movementDistance;
        mGruntAnimationFrameRate->isActivated = true;
        break;

    case DOWN:

        mGruntAnimationFrameRate->xPos = 0.0f;
        mGruntAnimationFrameRate->yPos = -movementDistance;
        mGruntAnimationFrameRate->isActivated = true;
        break;

    case LEFT:

        mGruntAnimationFrameRate->xPos = -movementDistance;
        mGruntAnimationFrameRate->yPos = 0.0f;
        mGruntAnimationFrameRate->isActivated = true;
        break;

    case RIGHT:

        mGruntAnimationFrameRate->xPos = movementDistance;
        mGruntAnimationFrameRate->yPos = 0.0f;
        mGruntAnimationFrameRate->isActivated = true;
        break;

    case UP_LEFT:

        mGruntAnimationFrameRate->xPos = -movementDistance;
        mGruntAnimationFrameRate->yPos = movementDistance;
        mGruntAnimationFrameRate->isActivated = true;
        break;

    case UP_RIGHT:

        mGruntAnimationFrameRate->xPos = movementDistance;
        mGruntAnimationFrameRate->yPos = movementDistance;
        mGruntAnimationFrameRate->isActivated = true;
        break;

    case DOWN_LEFT:

        mGruntAnimationFrameRate->xPos = -movementDistance;
        mGruntAnimationFrameRate->yPos = -movementDistance;
        mGruntAnimationFrameRate->isActivated = true;
        break;

    case DOWN_RIGHT:

        mGruntAnimationFrameRate->xPos = movementDistance;
        mGruntAnimationFrameRate->yPos = -movementDistance;
        mGruntAnimationFrameRate->isActivated = true;
        break;
    }
}

std::string cGruntEnemy::GetUniqueModelName()
{
    return uniqueModelName;
}