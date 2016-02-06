#pragma once
#include <string>
#include "allegro5\allegro5.h"
#include "allegro5\allegro_image.h"
#include <iostream>


using namespace std;
class Player;
class Enemy
{
public:
	string name;
	string ID;
	float posx;
	float posy;
	int speed;
	int boundx;
	int boundy;
	bool live;

	const int maxFrame;
	int curFrame;
	int frameCount;
	int frameDelay;
	int frameWidth;
	int frameHeight;
	int direction;
	bool moving;

	int health;
	int damage;

	int getHealth();
	void setHealth(int h);
	int getDamage();

	float getX();
	float getY();
	void setX(float x);
	void setY(float y);
	float getboundX();
	float getboundY();
	string getID();
	bool getLive();
	void setLive(bool a);
	void setDirection(int d);

	void followMain(Player* main);
	ALLEGRO_BITMAP *monster[4];

	Enemy(string n, string id, float x, float y, int s, int bx, int by, int mF,
		int fDelay, int fW, int fH, int health, int damage, string pic);
	~Enemy();

	void CollideEnemy(Player* main);
	void UpdateEnemy();
	void DrawEnemy();
};

