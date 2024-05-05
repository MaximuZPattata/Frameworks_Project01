#pragma once
#include "pch.h"
#include "iEnemy.h"

class iEnemyFactory 
{

public:
    virtual ~iEnemyFactory() {};
    virtual iEnemy* CreateEnemy() = 0;
};