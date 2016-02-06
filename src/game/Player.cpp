#include "stdafx.h"
#include "Player.h"
#include <iostream>
#include <cmath>
#include "Projectile.h"
#include "Level.h"

Player::Player(string n, string id, float x, float y, int s, int bx, int by, 
	int mF, int fDelay, int fW, int fH, int h, int d, string pic)
	: name(n), ID(id), posx(x), posy(y), speed(s), boundx(bx), boundy(by), maxFrame(mF),
	frameDelay(fDelay), frameWidth(fW), frameHeight(fH), health(h), damage(d)
{
	curFrame = 0;
	frameCount = 0;
	direction = 0;
	score = 0;
	string temp1 = pic + "front.png";
	string temp2 = pic + "back.png";
	string temp3 = pic + "right.png";
	string temp4 = pic + "left.png";
	string temp5 = pic + "idle.png";
	player[0] = al_load_bitmap(temp1.c_str());
	player[1] = al_load_bitmap(temp2.c_str());
	player[2] = al_load_bitmap(temp3.c_str());
	player[3] = al_load_bitmap(temp4.c_str());
	player[4] = al_load_bitmap(temp5.c_str());
	moving = false;
}

Player::~Player()
{
	for (int i = 0; i < 5; i++)
	{
		al_destroy_bitmap(player[i]);
	}
}

void Player::UpdatePlayer()
{
	if (++frameCount >= frameDelay)
	{
		if (++curFrame >= maxFrame) curFrame = 0;
		frameCount = 0;
	}
	if (posx > 1330) posx = 1330;
	if (posx < 0) posx = 0;
	if (posy > 630) posy = 630;
	if (posy < 0) posy = 0;
}

void Player::RunUp()
{
	direction = 1;
	posy -= speed;
	moving = true;

}

void Player::RunDown()
{
	direction = 0;
	posy += speed;
	moving = true;
}

void Player::RunRight()
{
	direction = 3;
	posx += speed;
	moving = true;
}

void Player::RunLeft()
{
	direction = 2;
	posx -= speed;
	moving = true;
}

void Player::DrawPlayer()
{
	if (moving) al_draw_bitmap_region(player[direction], curFrame * frameWidth, 0, frameWidth, frameHeight, posx, posy, 0);
	else al_draw_bitmap_region(player[4], direction * frameWidth, 0, frameWidth, frameHeight, posx, posy, 0);
}

bool Player::getMoving()
{
	return moving;
}

void Player::setMoving(bool m)
{
	moving = m;
}

float Player::getX()
{
	return posx;
}

float Player::getY()
{
	return posy;
}

void Player::setX(float x)
{
	posx = x;
}

void Player::setY(float y)
{
	posy = y;
}

float Player::getboundX()
{
	return boundx;
}

float Player::getboundY()
{
	return boundy;
}

int Player::getfW()
{
	return frameWidth;
}

int Player::getfH()
{
	return frameHeight;
}

int Player::getHealth()
{
	return health;
}

void Player::setHealth(int h)
{
	health = h;
}

int Player::getScore()
{
	return score;
}

void Player::setScore(int s)
{
	score = s;
}

int Player::getDirection()
{
	return direction;
}

void Player::changeCoord(Player * second)
{
	int x_second = second->getX();
	int y_second = second->getY();
	second->setX(posx);
	second->setY(posy);
	posx = x_second;
	posy = y_second;

}

void Player::followMain(Player * main)
{
	//MATH IS IMPORTANT
	float new_x = main->getX() - posx;
	float new_y = main->getY() - posy;
	float hyp = sqrt(new_x * new_x + new_y * new_y);
	new_x /= hyp;
	new_y /= hyp;
	float distance;

	distance = sqrt(pow(posx - main->getX(), 2) + pow(posy - main->getY(), 2));
	while (distance > 50)
	{
		posx += new_x * speed / 2;
		posy += new_y * speed / 2;
		distance = sqrt(pow(posx - main->getX(), 2) + pow(posy - main->getY(), 2));

	}
	direction = main->getDirection();
	moving = main->getMoving();
}

void Player::CheckCycle()
{
	if (++frameCount >= frameDelay)
	{
		if (++curFrame >= maxFrame) curFrame = 0;
		frameCount = 0;
	}
}

void Player::LoadBullets(string ID, string imageloc)
{
	for (int i = 0; i < 5; i++)
	{
		Projectile* temp = new Projectile(ID, 0, 0, 20, 20, 8, imageloc);
		bullets.push_back(temp);
	}

}

void Player::FireBullets()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets.at(i)->Fire(this)) break;
	}
}

void Player::DrawBullets()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets.at(i)->Draw();
	}
}

void Player::UpdateBullets()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets.at(i)->Update();
	}
}

void Player::CheckCollideBullets(Level* l)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		for (int j = 0; j < l->getEnemyNum(); j++)
		{
			if (l->returnIce(j)->getLive() &&
				bullets.at(i)->CollideProjectile(l->returnIce(j))) score++;
			if (l->returnFire(j)->getLive() &&
				bullets.at(i)->CollideProjectile(l->returnFire(j))) score++;
		}
	}
}


