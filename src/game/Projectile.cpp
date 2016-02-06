#include "stdafx.h"
#include "Projectile.h"


Projectile::Projectile(string id, int x, int y, int bx, int by, int s, string im)
	: ID(id), posx(x), posy(y), boundx(bx), boundy(by), speed(s), live(false), direction(0), damage(20)
{
	image = al_load_bitmap(im.c_str());
}

Projectile::~Projectile()
{
	al_destroy_bitmap(image);
}

void Projectile::Draw()
{
	if (live) al_draw_bitmap(image, posx, posy, 0);
}

bool Projectile::Fire(Player* Main)
{
	if (!live)
	{
		posx = Main->getX();
		posy = Main->getY();
		live = true;
		direction = Main->getDirection();
		return true;
	}
	return false;
}

void Projectile::Update()
{
	if (direction == 0) //going down
	{
		posy += speed;
		if (posy > 630) live = false;
	}
	if (direction == 1) //going up
	{
		posy -= speed;
		if (posy < 0) live = false;
	}
	if (direction == 2) //going left
	{
		posx -= speed;
		if (posx < 0) live = false;
	}
	if (direction == 3) //going right
	{
		posx += speed;
		if (posx > 1330) live = false;
	}
}

bool Projectile::CollideProjectile(Enemy* e)
{
	if (live)
	{
		if (posx - boundx < e->getX() + e->getboundX() &&
			posx + boundx > e->getX() - e->getboundX() &&
			posy - boundy < e->getY() + e->getboundY() &&
			posy + boundy > e->getY() - e->getboundY())
		{
			live = false;
			if (ID != e->getID())
			{
				e->setHealth(e->getHealth() - damage);
				if (e->getHealth() <= 0)
				{
					e->setLive(false);
					e->setHealth(20);
					return true;
				}
			}
			else
			{
				cout << "Before: " << e->getHealth() << endl;
				e->setHealth(e->getHealth() + damage);
				cout << "After: " << e->getHealth() << endl;
			}
		}

	}
	return false;
}

