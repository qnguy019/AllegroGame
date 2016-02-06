#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"


int Enemy::getHealth()
{
	return health;
}

void Enemy::setHealth(int h)
{
	health = h;
}

int Enemy::getDamage()
{
	return damage;
}

float Enemy::getX()
{
	return posx;
}

float Enemy::getY()
{
	return posy;
}

void Enemy::setX(float x)
{
	posx = x;
}

void Enemy::setY(float y)
{
	posy = y;
}

float Enemy::getboundX()
{
	return boundx;
}

float Enemy::getboundY()
{
	return boundy;
}

string Enemy::getID()
{
	return ID;
}

bool Enemy::getLive()
{
	return live;
}

void Enemy::setLive(bool a)
{
	live = a;
}

void Enemy::setDirection(int d)
{
	direction = d;
}

void Enemy::followMain(Player * main)
{
	float new_x = main->getX() - posx;
	float new_y = main->getY() - posy;
	float hyp = sqrt(new_x * new_x + new_y * new_y);
	new_x /= hyp;
	new_y /= hyp;
	float distance;

	distance = sqrt(pow(posx - main->getX(), 2) + pow(posy - main->getY(), 2));
	posx += new_x * speed / 2;
	posy += new_y * speed / 2;

	if (main->getX() > posx) direction = 3;
	if (main->getX() < posx) direction = 2;
	if (main->getY() > posy) direction = 0;
	if (main->getY() > posy) direction = 1;
}

Enemy::Enemy(string n, string id, float x, float y, int s, int bx, int by,
	int mF, int fDelay, int fW, int fH, int h, int d, string pic)
	: name(n), ID(id), posx(x), posy(y), speed(s), boundx(bx), boundy(by), maxFrame(mF),
	frameDelay(fDelay), frameWidth(fW), frameHeight(fH), health(h), damage(d)
{
	curFrame = 0;
	frameCount = 0;
	direction = 0;
	moving = false;
	live = false;
	string temp1 = pic + "back.png";
	string temp2 = pic + "front.png";
	string temp3 = pic + "left.png";
	string temp4 = pic + "right.png";
	monster[0] = al_load_bitmap(temp1.c_str());
	monster[1] = al_load_bitmap(temp2.c_str());
	monster[2] = al_load_bitmap(temp3.c_str());
	monster[3] = al_load_bitmap(temp4.c_str());
}

Enemy::~Enemy()
{
	for (int i = 0; i < 4; i++)
	{
		al_destroy_bitmap(monster[i]);
	}
}

//returns true if there was a collision so start fight sequence
void Enemy::CollideEnemy(Player * main) 
{
	if (posx - boundx < main->getX() + main->getboundX() &&
		posx + boundx > main->getX() - main->getboundX() &&
		posy - boundy < main->getY() + main->getboundY() &&
		posy + boundy > main->getY() - main->getboundY())
	{
		cout << "AHH A COLLISION! " << endl;
		live = false;
		main->setHealth(main->getHealth() - damage);
	}
}

void Enemy::UpdateEnemy()
{
	if (++frameCount >= frameDelay)
	{
		if (++curFrame >= maxFrame) curFrame = 0;
		frameCount = 0;
	}
	
	if (posx > 1330) live = false;
	if (posx < 0) live = false;
	if (posy > 630) live = false;
	if (posy < 0) live = false;
}

void Enemy::DrawEnemy()
{
	al_draw_bitmap_region(monster[direction], curFrame * frameWidth, 0, frameWidth, frameHeight, posx, posy, 0);
}