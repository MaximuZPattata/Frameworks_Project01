#include "pch.h"
#include "cPlayer.h"

cPlayer::cPlayer()
{
	std::cout << "Player created !" << std::endl;

	mPlayerAnimationFrameRate = new sAnimationFrames();
    mPlayerPosition = new sPositionTracker();
    mPlayerWeapon = new cWeapon();
}

cPlayer::~cPlayer()
{
	delete mPlayerAnimationFrameRate;
    delete mPlayerPosition;
    delete mPlayerWeapon;
}

void cPlayer::Initialize(cModelManipulator* modelManipulator, std::vector <sAnimationFrames*>& animationFrameRate, std::vector <sPositionTracker*>& modelCurrentPositionsList)
{
	mPlayerModelManipulator = modelManipulator;

    std::string modelName = "Player_UP_01";
    std::string meshType = "Player";
    float xPos = 0.0f;
    float yPos = 0.0f;

    //------------Initialize position and framerate--------------------

    mPlayerAnimationFrameRate->meshType = meshType;
    mPlayerAnimationFrameRate->previousModelName = modelName;
    mPlayerAnimationFrameRate->newGivenModelName = modelName;

    mPlayerPosition->meshType = meshType;
    mPlayerPosition->modelName = modelName;
    mPlayerPosition->modelRadius = 10.0f;
    mPlayerPosition->modelXPos = xPos;
    mPlayerPosition->modelYPos = yPos;

    //--------------------Add to the list-------------------------------

    modelCurrentPositionsList.push_back(mPlayerPosition);
    animationFrameRate.push_back(mPlayerAnimationFrameRate);

    //-------------------Load Player model------------------------------

    mPlayerModelManipulator->LoadModels(meshType, modelName, xPos, yPos);
}

void cPlayer::PlayerDirectionChange(eDirection playerDir)
{
    float movementDistance = 3.0f; 

    switch (playerDir)
    {
    case UP:

        mPlayerAnimationFrameRate->animationSet.clear();
        mPlayerAnimationFrameRate->animationSet.push_back("Player_UP_01");
        mPlayerAnimationFrameRate->animationSet.push_back("Player_UP_02");
        mPlayerAnimationFrameRate->animationSet.push_back("Player_UP_03");
        mPlayerAnimationFrameRate->xPos = 0.0f;
        mPlayerAnimationFrameRate->yPos = movementDistance;
        mPlayerAnimationFrameRate->isActivated = true;
        break;

    case DOWN:

        mPlayerAnimationFrameRate->animationSet.clear();
        mPlayerAnimationFrameRate->animationSet.push_back("Player_DOWN_04");
        mPlayerAnimationFrameRate->animationSet.push_back("Player_DOWN_05");
        mPlayerAnimationFrameRate->animationSet.push_back("Player_DOWN_06");
        mPlayerAnimationFrameRate->xPos = 0.0f;
        mPlayerAnimationFrameRate->yPos = -movementDistance;
        mPlayerAnimationFrameRate->isActivated = true;
        break;

    case LEFT:

        mPlayerAnimationFrameRate->animationSet.clear();
        mPlayerAnimationFrameRate->animationSet.push_back("Player_LEFT_07");
        mPlayerAnimationFrameRate->animationSet.push_back("Player_LEFT_08");
        mPlayerAnimationFrameRate->animationSet.push_back("Player_LEFT_09");
        mPlayerAnimationFrameRate->xPos = -movementDistance;
        mPlayerAnimationFrameRate->yPos = 0.0f;
        mPlayerAnimationFrameRate->isActivated = true;
        break;

    case RIGHT:

        mPlayerAnimationFrameRate->animationSet.clear();
        mPlayerAnimationFrameRate->animationSet.push_back("Player_RIGHT_10");
        mPlayerAnimationFrameRate->animationSet.push_back("Player_RIGHT_11");
        mPlayerAnimationFrameRate->animationSet.push_back("Player_RIGHT_12");
        mPlayerAnimationFrameRate->xPos = movementDistance;
        mPlayerAnimationFrameRate->yPos = 0.0f;
        mPlayerAnimationFrameRate->isActivated = true;
        break;

    case UP_LEFT:

        mPlayerAnimationFrameRate->animationSet.clear();
        mPlayerAnimationFrameRate->animationSet.push_back("Player_LEFT_07");
        mPlayerAnimationFrameRate->animationSet.push_back("Player_LEFT_08");
        mPlayerAnimationFrameRate->animationSet.push_back("Player_LEFT_09");
        mPlayerAnimationFrameRate->xPos = -movementDistance;
        mPlayerAnimationFrameRate->yPos = movementDistance;
        mPlayerAnimationFrameRate->isActivated = true;
        break;
    
    case UP_RIGHT:

        mPlayerAnimationFrameRate->animationSet.clear();
        mPlayerAnimationFrameRate->animationSet.push_back("Player_RIGHT_10");
        mPlayerAnimationFrameRate->animationSet.push_back("Player_RIGHT_11");
        mPlayerAnimationFrameRate->animationSet.push_back("Player_RIGHT_12");
        mPlayerAnimationFrameRate->xPos = movementDistance;
        mPlayerAnimationFrameRate->yPos = movementDistance;
        mPlayerAnimationFrameRate->isActivated = true;
        break;
    
    case DOWN_LEFT:

        mPlayerAnimationFrameRate->animationSet.clear();
        mPlayerAnimationFrameRate->animationSet.push_back("Player_LEFT_07");
        mPlayerAnimationFrameRate->animationSet.push_back("Player_LEFT_08");
        mPlayerAnimationFrameRate->animationSet.push_back("Player_LEFT_09");
        mPlayerAnimationFrameRate->xPos = -movementDistance;
        mPlayerAnimationFrameRate->yPos = -movementDistance;
        mPlayerAnimationFrameRate->isActivated = true;
        break;
    
    case DOWN_RIGHT:

        mPlayerAnimationFrameRate->animationSet.clear();
        mPlayerAnimationFrameRate->animationSet.push_back("Player_RIGHT_10");
        mPlayerAnimationFrameRate->animationSet.push_back("Player_RIGHT_11");
        mPlayerAnimationFrameRate->animationSet.push_back("Player_RIGHT_12");
        mPlayerAnimationFrameRate->xPos = movementDistance;
        mPlayerAnimationFrameRate->yPos = -movementDistance;
        mPlayerAnimationFrameRate->isActivated = true;
        break;
    }
}

void cPlayer::Attack(eDirection playerDir)
{
    mPlayerWeapon->ShootWeapon( mPlayerModelManipulator, mPlayerPosition->modelXPos, mPlayerPosition->modelYPos, mPlayerPosition->modelRadius,playerDir);
}

