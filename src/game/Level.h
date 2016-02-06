#pragma once
#include "Enemy.h"
#include <vector>

class Level
{
private:
	vector<Enemy*> ice;
	vector<Enemy*> fire;
	int level;
	int size;
public:
	Level(int l, string iimage, string fimage, int speed, int sz);
	~Level();

	void StartEnemy();
	void DrawEnemy();
	void followMain(Player* Main);
	void CollideEnemyPlayer(Player* Main);
	void UpdateEnemy();
	Enemy* returnIce(int pos);
	Enemy* returnFire(int pos);
	int getEnemyNum();
};

