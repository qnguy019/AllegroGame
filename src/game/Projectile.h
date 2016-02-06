#pragma once
#include "allegro5\allegro5.h"
#include "allegro5\allegro_image.h"
#include <string>
#include "Player.h"
#include "Enemy.h"
using namespace std;
class Projectile
{
public:
	string ID;
	int posx;
	int posy;
	int boundx;
	int boundy;
	bool live;
	int direction;
	int speed;
	int damage;

	ALLEGRO_BITMAP * image;
	Projectile(string id, int x, int y, int bx, int by, int s, string im);
	~Projectile();

	void Draw();
	bool Fire(Player* Main);
	void Update();
	bool CollideProjectile(Enemy * e);


};

