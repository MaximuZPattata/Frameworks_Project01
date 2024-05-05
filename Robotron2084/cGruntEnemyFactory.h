#pragma once
#include "pch.h"
#include "iEnemyFactory.h"
#include "cGruntEnemy.h"

class cGruntEnemyFactory : public iEnemyFactory
{

public:
    iEnemy* CreateEnemy();
};

