#pragma once
#include "pch.h"
#include "cFrameRates.h"
#include "eDirection.h"
#include "cBullet.h"
#include "cModelManipulator.h"

class cWeapon
{
public:
	cWeapon();
	~cWeapon();

	std::vector<cBullet*> mBulletList;

	void ShootWeapon(cModelManipulator* modelManipulator, float initialPlayerXPos, float initialPlayerYPos, float playerRadius, eDirection attackDir);
	void DestroyBullet(float bulletId);

private:
	cBullet* mBullet = NULL;
};

