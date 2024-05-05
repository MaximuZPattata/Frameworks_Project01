#pragma once
#include "pch.h"
#include "cFrameRates.h"
#include "DetailsFromFile.h"
#include "cModelManipulator.h"
#include "sPositionTracker.h"
#include "eDirection.h"
#include "cWeapon.h"

class cPlayer
{
public:
	cPlayer();
	~cPlayer();

	void Initialize(cModelManipulator* modelManipulator, std::vector <sAnimationFrames*>& animationFrameRate, std::vector <sPositionTracker*>& modelCurrentPositionsList);
	void PlayerDirectionChange(eDirection playerDir);
	void Attack(eDirection playerDir);
	cWeapon* mPlayerWeapon;

private:
	sAnimationFrames* mPlayerAnimationFrameRate;
	sPositionTracker* mPlayerPosition;
	cModelManipulator* mPlayerModelManipulator = NULL;
};

