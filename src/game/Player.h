#pragma once
#include <string>
#include "allegro5\allegro5.h"
#include "allegro5\allegro_image.h"
#include <vector>
using namespace std;
class Projectile;
class Enemy;
class Level;
class Player
{
public:
	vector<Projectile*> bullets;
	string name;
	string ID;
	float posx;
	float posy;
	int speed;
	int boundx;
	int boundy;
	int score = 0;
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


	ALLEGRO_BITMAP *player[5];
	Player(string n, string id, float x, float y, int s, int bx, int by, int mF,
		int fDelay, int fW, int fH, int health, int damage, string pic);
	~Player();
	void UpdatePlayer();
	void RunUp();
	void RunDown();
	void RunRight();
	void RunLeft();
	void DrawPlayer();
	bool getMoving();
	void setMoving(bool m);

	float getX();
	float getY();
	void setX(float x);
	void setY(float y);
	float getboundX();
	float getboundY();
	int getfW();
	int getfH();


	int getHealth();
	void setHealth(int h);
	int getScore();
	void setScore(int s);

	int getDirection();
	void changeCoord(Player* second);
	void followMain(Player* main);
	void CheckCycle();


	void LoadBullets(string ID, string imageloc);
	void FireBullets();
	void DrawBullets();
	void UpdateBullets();
	void CheckCollideBullets(Level* l);

private:



};

