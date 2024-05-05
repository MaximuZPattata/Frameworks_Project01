#include "pch.h"
#include "cGruntEnemyFactory.h"

iEnemy* cGruntEnemyFactory::CreateEnemy()
{
	return new cGruntEnemy();
}