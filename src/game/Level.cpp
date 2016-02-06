#include "stdafx.h"
#include "Level.h"

Level::Level(int l, string iimage, string fimage, int speed, int sz)
	: size(sz)
{
	for (int i = 0; i < size; i++)
	{
		Enemy* ice_temp = new Enemy("Ice Skull", "ICE", 0, 0, speed, 20, 20, 6, 7, 64, 64, 20, 10, iimage);
		Enemy* fire_temp = new Enemy("Fire Skull", "FIRE", 0, 0, speed, 20, 20, 6, 7, 64, 64, 20, 10, fimage);
		ice.push_back(ice_temp);
		fire.push_back(fire_temp);
	}
}

Level::~Level()
{
	for (int i = 0; i < size; i++)
	{
		delete ice.at(i);
		delete fire.at(i);
		ice.at(i) = 0;
		fire.at(i) = 0;
	}
}

void Level::StartEnemy()
{
	//srand(time(NULL));
	bool doneice = false;
	bool donefire = false;
	for (int i = 0; i < size; i++)
	{
		if (!ice.at(i)->getLive())
		{
			if (rand() % 500 == 0)
			{
				ice.at(i)->setLive(true);
				doneice = true;
				//0 = bot, 1 = top, 2 = left, 3 = right
				int spawn = rand() % 4;
				switch (spawn)
				{
				case 0:
					ice.at(i)->setX(30 + rand() % (1330 - 80));
					ice.at(i)->setY(630);
					break;
				case 1:
					ice.at(i)->setX(30 + rand() % (1330 - 80));
					ice.at(i)->setY(0);
					break;
				case 2:
					ice.at(i)->setX(0);
					ice.at(i)->setY(30 + rand() % (630 - 80));
					break;
				case 3:
					ice.at(i)->setX(1330);
					ice.at(i)->setY(30 + rand() % (630 - 80));
					break;
				}
			}
		}
		if (doneice) break;
	}

	for (int i = 0; i < size; i++)
	{
		if (!fire.at(i)->getLive())
		{
			if (rand() % 500 == 0)
			{
				fire.at(i)->setLive(true);
				donefire = true;
				//0 = bot, 1 = top, 2 = left, 3 = right
				int spawn = rand() % 4;
				fire.at(i)->setDirection(spawn);
				switch (spawn)
				{
				case 0:
					fire.at(i)->setX(30 + rand() % (1330 - 60));
					fire.at(i)->setY(630);
					break;
				case 1:
					fire.at(i)->setX(30 + rand() % (1330 - 60));
					fire.at(i)->setY(0);
					break;
				case 2:
					fire.at(i)->setX(0);
					fire.at(i)->setY(30 + rand() % (630 - 60));
					break;
				case 3:
					fire.at(i)->setX(1330);
					fire.at(i)->setY(30 + rand() % (630 - 60));
					break;
				}
			}
		}
		if (donefire) break;
	}
}

void Level::DrawEnemy()
{
	for (int i = 0; i < size; i++)
	{
		if (ice.at(i)->getLive()) ice.at(i)->DrawEnemy();
		if (fire.at(i)->getLive()) fire.at(i)->DrawEnemy();
	}
}

void Level::followMain(Player* Main)
{
	for (int i = 0; i < size; i++)
	{
		if (ice.at(i)->getLive()) ice.at(i)->followMain(Main);
		if (fire.at(i)->getLive()) fire.at(i)->followMain(Main);
	}
}

void Level::CollideEnemyPlayer(Player * Main)
{
	for (int i = 0; i < size; i++)
	{
		if (ice.at(i)->getLive()) ice.at(i)->CollideEnemy(Main);
		if (fire.at(i)->getLive()) fire.at(i)->CollideEnemy(Main);
	}
}

void Level::UpdateEnemy()
{
	for (int i = 0; i < size; i++)
	{
		if (ice.at(i)->getLive()) ice.at(i)->UpdateEnemy();
		if (fire.at(i)->getLive()) fire.at(i)->UpdateEnemy();
	}
}

Enemy * Level::returnIce(int pos)
{
	return ice.at(pos);
}

Enemy * Level::returnFire(int pos)
{
	return fire.at(pos);
}

int Level::getEnemyNum()
{
	return size;
}