#include "pch.h"
#include "cWeapon.h"


cWeapon::cWeapon()
{

}

cWeapon::~cWeapon()
{

}

float getRandomFloat(float num1, float num2)
{
	float randomNum = ((float)rand()) / (float)RAND_MAX;
	float difference = num2 - num1;
	float product = randomNum * difference;

	return num1 + product;
}

void cWeapon::ShootWeapon(cModelManipulator* modelManipulator, float initialPlayerXPos, float initialPlayerYPos, float playerRadius, eDirection attackDir)
{
	mBullet = new cBullet();

	std::string modelName;
	glm::vec2 projectilePos = glm::vec2(initialPlayerXPos, initialPlayerYPos + 5.0f);
	glm::vec2 projectileDir = glm::vec2(0.0f, 0.0f);
	
	//-------------Calculate values------------------------------

	switch (attackDir)
	{
	case UP:
		modelName = "Bullet_UP";
		projectilePos.y += playerRadius;
		projectileDir.y += 1.0f;

		break;

	case DOWN:
		modelName = "Bullet_DOWN";
		projectilePos.y -= playerRadius;
		projectileDir.y -= 1.0f;

		break;

	case LEFT:
		modelName = "Bullet_LEFT";
		projectilePos.x -= playerRadius;
		projectileDir.x -= 1.0f;

		break;

	case RIGHT:
		modelName = "Bullet_RIGHT";
		projectilePos.x += playerRadius;
		projectileDir.x += 1.0f;

		break;

	case UP_LEFT:
		modelName = "Bullet_UP_LEFT";
		projectilePos.x -= playerRadius;
		projectilePos.y += playerRadius;
		projectileDir.x -= 1.0f; 
		projectileDir.y += 1.0f;
		
		break;

	case UP_RIGHT:
		modelName = "Bullet_UP_RIGHT";
		projectilePos.x += playerRadius;
		projectilePos.y += playerRadius;
		projectileDir.x += 1.0f;
		projectileDir.y += 1.0f;

		break;

	case DOWN_LEFT:
		modelName = "Bullet_DOWN_LEFT";
		projectilePos.x -= playerRadius;
		projectilePos.y -= playerRadius;
		projectileDir.x -= 1.0f;
		projectileDir.y -= 1.0f;
		
		break;

	case DOWN_RIGHT:
		modelName = "Bullet_DOWN_RIGHT";
		projectilePos.x += playerRadius;
		projectilePos.y -= playerRadius;
		projectileDir.x += 1.0f;
		projectileDir.y -= 1.0f;

		break;
	}
	
	//-------Initialize Bullet object details-------------------

	float id = 0.0f;

	while (id == 0.0f)
	{
		id = getRandomFloat(0.1, 100.0);

		for (int index = 0; index < mBulletList.size(); index++)
		{
			if (mBulletList[index]->bulletId == id) //Checking if bullet id is unique from other bullet ids
				id == 0.0f;
		}
	}

	mBullet->bulletId = id;
	mBullet->position = projectilePos;
	mBullet->direction = projectileDir;
	mBullet->velocity = 1.0f;

	mBulletList.push_back(mBullet);

	//-----------Load Bullet model in map----------------------

	std::string meshType = "Bullet";
	std::string newModelName = modelName + std::to_string(mBullet->bulletId);
	
	mBullet->modelName = newModelName;

	modelManipulator->LoadModelWithNewName(meshType, modelName, newModelName, projectilePos.x, projectilePos.y);
}

void cWeapon::DestroyBullet(float bulletId)
{
	for (int index = 0; index < mBulletList.size(); index++)
	{
		if (mBulletList[index]->bulletId == bulletId)
		{
			delete mBulletList[index];

			mBulletList.erase(std::remove(mBulletList.begin(), mBulletList.end(), mBulletList[index]), mBulletList.end());
		}	
	}
}
