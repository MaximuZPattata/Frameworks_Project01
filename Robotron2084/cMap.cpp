#include "pch.h"
#include "cMap.h"
#include "cBullet.h"

cMap::cMap()
{
    std::cout << "Map created !" << std::endl;
}

cMap::~cMap()
{

}

float getVeryRandomFloat(float num1, float num2)
{
    float randomNum = ((float)rand()) / (float)RAND_MAX;
    float difference = num2 - num1;
    float product = randomNum * difference;

    return num1 + product;
}

void cMap::Initialize(std::vector <sModelDetailsFromFile>& modelDetailsList, cModelManipulator* modelManipulator, std::vector <sAnimationFrames*>& animationFrameRate,
                        std::vector <sPositionTracker*>& modelCurrentPositionsList)
{
    mModelManipulator = modelManipulator;

    //------------Load Map Model------------------------------------
    
    SetWalls(modelDetailsList);

    //-----------Initialize Player----------------------------------

    CreatePlayer(modelDetailsList, modelManipulator, animationFrameRate, modelCurrentPositionsList);
}

void cMap::CreatePlayer(std::vector <sModelDetailsFromFile>& modelDetailsList, cModelManipulator* modelManipulator, std::vector <sAnimationFrames*>& animationFrameRate,
                        std::vector <sPositionTracker*>& modelCurrentPositionsList)
{
    mThePlayer = new cPlayer();
    mThePlayer->Initialize(modelManipulator, animationFrameRate, modelCurrentPositionsList);
}

void cMap::SetWalls(std::vector <sModelDetailsFromFile>& modelDetailsList)
{
    for (int index = 0; index < modelDetailsList.size(); index++)
    {
        if (modelDetailsList[index].meshType == "Walls")
        {
            std::string modelName;
            float numberOfColumns = 60.0f;
            float offset = modelDetailsList[index].modelScaleValue;
            float xPos = 0.0f;
            float yPos = 0.0f;

            for (float wallXPos = 0.0f; wallXPos < numberOfColumns; wallXPos++)
            {
                for (float wallYPos = 0.0f; wallYPos < numberOfColumns; wallYPos++)
                {
                    if (wallXPos == 0 || wallXPos == numberOfColumns - 1 || wallYPos == 0 || wallYPos == numberOfColumns - 1)
                    {
                        modelName = modelDetailsList[index].modelName + std::to_string((int)wallXPos) + std::to_string((int)wallYPos);
                        xPos = (offset * wallXPos) - (offset * (numberOfColumns - 1) / 2); //This brings the Xaxis of the map centre to 0.0f [i.e (x,y) = (0,0)]
                        yPos = (offset * wallYPos) - (offset * (numberOfColumns - 1) / 2); //This brings the Yaxis of the map centre to 0.0f [i.e (x,y) = (0,0)]

                        mModelManipulator->LoadModelsWithoutNameCheck(modelDetailsList[index].meshType, modelName, xPos, yPos);
                    }
                }
            }
        }
    }
}

void cMap::UpdateMap(std::vector <sAnimationFrames*> animationFrameRate, std::vector <sPositionTracker*> modelCurrentPositionsList)
{
    float boundaryValue = 140.0f;
 
    for (int frameIndex = 0; frameIndex < animationFrameRate.size(); frameIndex++)
    {
        if (animationFrameRate[frameIndex]->FrameRateValue == 1 || animationFrameRate[frameIndex]->FrameRateValue == 7 ||
            animationFrameRate[frameIndex]->FrameRateValue == 14 || animationFrameRate[frameIndex]->FrameRateValue == 21)
        {
            glm::vec2 model2DPos = mModelManipulator->Get2DModelPosition(animationFrameRate[frameIndex]->newGivenModelName);
            std::string newGivenName = animationFrameRate[frameIndex]->newGivenModelName;

            model2DPos.x += animationFrameRate[frameIndex]->xPos;
            model2DPos.y += animationFrameRate[frameIndex]->yPos;

            if (model2DPos.x > boundaryValue || model2DPos.x < -boundaryValue || model2DPos.y > boundaryValue - 10.0f || model2DPos.y < -boundaryValue - 5.0f)
            {
                model2DPos.x -= animationFrameRate[frameIndex]->xPos;
                model2DPos.y -= animationFrameRate[frameIndex]->yPos;
            }

            mModelManipulator->DeleteModel(animationFrameRate[frameIndex]->newGivenModelName);

            if (animationFrameRate[frameIndex]->FrameRateValue == 1)
                animationFrameRate[frameIndex]->previousModelName = animationFrameRate[frameIndex]->animationSet[0];

            else if (animationFrameRate[frameIndex]->FrameRateValue == 7)
                animationFrameRate[frameIndex]->previousModelName = animationFrameRate[frameIndex]->animationSet[1];

            else if (animationFrameRate[frameIndex]->FrameRateValue == 14)
                animationFrameRate[frameIndex]->previousModelName = animationFrameRate[frameIndex]->animationSet[2];

            else if (animationFrameRate[frameIndex]->FrameRateValue == 21)
            {
                animationFrameRate[frameIndex]->previousModelName = animationFrameRate[frameIndex]->animationSet[0];

                animationFrameRate[frameIndex]->isActivated = false;
                animationFrameRate[frameIndex]->FrameRateValue = 0;
            }

            mModelManipulator->LoadModelWithNewName(animationFrameRate[frameIndex]->meshType, animationFrameRate[frameIndex]->previousModelName, 
                                                    newGivenName, model2DPos.x, model2DPos.y);

            UpdatePositions(modelCurrentPositionsList, animationFrameRate[frameIndex]->modelId, animationFrameRate[frameIndex]->meshType, model2DPos.x, model2DPos.y);
        }
    }

    CheckAndUpdateProjectiles(boundaryValue, modelCurrentPositionsList);
    CheckAndUpdateEnemyPositions(modelCurrentPositionsList);
}

void cMap::UpdatePositions(std::vector <sPositionTracker*> modelCurrentPositionsList, float modelId, std::string meshType, float currentXPos, float currentYPos)
{
    for (int modelPosIndex = 0; modelPosIndex < modelCurrentPositionsList.size(); modelPosIndex++)
    {
        if (modelCurrentPositionsList[modelPosIndex]->modelId == modelId && modelCurrentPositionsList[modelPosIndex]->meshType == meshType)
        {
            modelCurrentPositionsList[modelPosIndex]->modelXPos = currentXPos;
            modelCurrentPositionsList[modelPosIndex]->modelYPos = currentYPos;
        }
    }
}

void cMap::CheckAndUpdateProjectiles(float boundaryValue, std::vector <sPositionTracker*> modelCurrentPositionsList)
{
    std::vector<cBullet*> bulletsCount = mThePlayer->mPlayerWeapon->mBulletList;


    for (int projectileIndex = 0; projectileIndex < bulletsCount.size(); projectileIndex++)
    {
        bulletsCount[projectileIndex]->position += bulletsCount[projectileIndex]->direction * bulletsCount[projectileIndex]->velocity;

        //------------------------Bullets get destroyed when reaching the walls--------------------------------------------------------

        if (bulletsCount[projectileIndex]->position.x > boundaryValue || bulletsCount[projectileIndex]->position.x < -boundaryValue ||
            bulletsCount[projectileIndex]->position.y > boundaryValue - 5.0f || bulletsCount[projectileIndex]->position.y < -boundaryValue - 5.0f)
        {
            mModelManipulator->DeleteModel(bulletsCount[projectileIndex]->modelName);
            mThePlayer->mPlayerWeapon->DestroyBullet(bulletsCount[projectileIndex]->bulletId);
        }
        else
        {
            mModelManipulator->MoveModels(bulletsCount[projectileIndex]->modelName ,bulletsCount[projectileIndex]->position.x, 
                                            bulletsCount[projectileIndex]->position.y, 0.0f);
        }

        //------------Bullets get destroyed when reaching the enemies(Also destroying the enemies)------------------------------------

        for (int modelPosIndex = 0; modelPosIndex < modelCurrentPositionsList.size(); modelPosIndex++)
        {
            if (modelCurrentPositionsList[modelPosIndex]->meshType == "Grunt")
            {
                std::string enemyModelName = modelCurrentPositionsList[modelPosIndex]->modelName;
                float enemyRadius = modelCurrentPositionsList[modelPosIndex]->modelRadius;
                float enemyXPos = modelCurrentPositionsList[modelPosIndex]->modelXPos;
                float enemyYPos = modelCurrentPositionsList[modelPosIndex]->modelYPos;

                if ((bulletsCount[projectileIndex]->position.x > enemyXPos - enemyRadius && bulletsCount[projectileIndex]->position.x < enemyXPos + enemyRadius) &&
                    (bulletsCount[projectileIndex]->position.y > enemyYPos - enemyRadius && bulletsCount[projectileIndex]->position.y < enemyYPos + enemyRadius + 5.0f))
                {
                    mModelManipulator->DeleteModel(bulletsCount[projectileIndex]->modelName);
                    mThePlayer->mPlayerWeapon->DestroyBullet(bulletsCount[projectileIndex]->bulletId);
                    mModelManipulator->DeleteModel(enemyModelName);
                    for (int enemyIndex = 0; enemyIndex < mEnemyList.size(); enemyIndex++)
                    {
                        if (mEnemyList[enemyIndex]->GetUniqueModelName() == enemyModelName)
                        {
                            delete mEnemyList[enemyIndex];
                            mEnemyList.erase(std::remove(mEnemyList.begin(), mEnemyList.end(), mEnemyList[enemyIndex]), mEnemyList.end());
                        }
                    }
                }
            }
        }
    }
}

void cMap::SpawnGruntEnemies(float currentTime, float randomNum, std::vector <sAnimationFrames*> animationFrameRate, 
                                std::vector <sPositionTracker*>& modelCurrentPositionsList)
{
    if ((currentTime - lastCheckedTime) > randomNum)
    {
        mEnemyFactory = &mGruntFactory;

        iEnemy* enemy = mEnemyFactory->CreateEnemy();

        float randomXPos = getVeryRandomFloat(-130.0, 130.0);
        float randomYPos = getVeryRandomFloat(-130.0, 130.0);

        enemy->Initialize(mModelManipulator, animationFrameRate, modelCurrentPositionsList, randomXPos, randomYPos);

        lastCheckedTime = currentTime;

        mEnemyList.push_back(enemy);
    }
}

void cMap::CheckAndUpdateEnemyPositions(std::vector <sPositionTracker*>& modelCurrentPositionsList)
{
    float playerXPos = 0.0f;
    float playerYPos = 0.0f;
    iEnemy* currentEnemy = NULL;

    for (int modelPosIndex = 0; modelPosIndex < modelCurrentPositionsList.size(); modelPosIndex++)
    {
        if (modelCurrentPositionsList[modelPosIndex]->meshType == "Player")
        {
            playerXPos = modelCurrentPositionsList[modelPosIndex]->modelXPos;
            playerYPos = modelCurrentPositionsList[modelPosIndex]->modelYPos;
        }
    }

    for (int modelPosIndex = 0; modelPosIndex < modelCurrentPositionsList.size(); modelPosIndex++)
    {
        if (modelCurrentPositionsList[modelPosIndex]->meshType == "Grunt")
        {
            for (int enemyIndex = 0; enemyIndex < mEnemyList.size(); enemyIndex++)
            {
                if (modelCurrentPositionsList[modelPosIndex]->modelName == mEnemyList[enemyIndex]->GetUniqueModelName())
                    currentEnemy = mEnemyList[enemyIndex];
            }
            
            float enemyXPos = modelCurrentPositionsList[modelPosIndex]->modelXPos;
            float enemyYPos = modelCurrentPositionsList[modelPosIndex]->modelYPos;
            
            if (playerXPos >= enemyXPos)
            {
                if (playerYPos >= enemyYPos)
                {
                    currentEnemy->EnemyDirectionChange(RIGHT);
                }
                else
                {
                    currentEnemy->EnemyDirectionChange(DOWN);
                }
            }
            else
            {
                if (playerYPos <= enemyYPos)
                {
                    currentEnemy->EnemyDirectionChange(LEFT);
                }
                else
                {
                    currentEnemy->EnemyDirectionChange(UP);
                }
            }
        }
    }
}
