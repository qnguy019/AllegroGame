// game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "allegro5\allegro5.h"
#include "allegro5\allegro_font.h"
#include "allegro5\allegro_ttf.h"
#include "allegro5\allegro_primitives.h"
#include "allegro5\allegro_image.h"
#include "allegro5\allegro_native_dialog.h"
#include "Player.h"
#include "Enemy.h"
#include <iostream>
#include <sstream>
#include <vector>
#include "Level.h"
using namespace std;

enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };
const int width = 1330;
const int height = 630;
const int NUM_BULLETS = 5;
const int NUM_COMETS = 10;

bool keys[5] = { false, false, false ,false, false };

int main(int argc, char** argv)
{
	al_init();
	ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
	bool done = false; //for keyboard input
	bool redraw = true;
	bool isGameOver = false;
	const int FPS = 60;

	ALLEGRO_DISPLAY *display = nullptr;
	ALLEGRO_EVENT_QUEUE *event_queue = nullptr;
	ALLEGRO_TIMER *timer = nullptr;


	al_set_app_name("Penquynh Games");
	display = al_create_display(width, height);
	if (display == nullptr)
	{
		cerr << "Display not working" << endl;
		al_rest(5.0);
		return EXIT_FAILURE;
	}

	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_keyboard();
	al_init_image_addon();

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);
	srand(time(NULL));
	ALLEGRO_BITMAP *bgSheet = al_load_bitmap("Images/map.png");
	ALLEGRO_FONT* scorefont = al_load_font("Fonts/Aspex.ttf", 24, 0);

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));


	//Load Player
	Player* Girl = new Player("Lucy", "PLAYER1", 100, height / 2, 5, 25, 25, 6, 7, 64, 64, 50, 20, "Images/Girl/");
	Player* Boy = new Player("Daichi", "PLAYER2", 20, height / 2, 5, 25, 25, 6, 7, 64, 64, 50, 20, "Images/Boy/");
	Girl->LoadBullets("FIRE", "Images/firebullet.png");
	Boy->LoadBullets("ICE", "Images/icebullet.png");
	Player* arr[2] = { Girl, Boy };

	Player* Main = arr[0];
	Player* Second = arr[1];

	Level* level1 = new Level(1, "Images/Monster/blue", "Images/Monster/red", 5, 5);
	srand(time(0));
	al_start_timer(timer);
	while (!done) //While the player doesn't press ESC
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		Main->setMoving(false);
		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true;
			Main->CheckCycle();
			Second->CheckCycle();
			Second->followMain(Main);
			level1->followMain(Main);

			if (keys[UP]) Main->RunUp();
			if (keys[DOWN]) Main->RunDown();
			if (keys[LEFT]) Main->RunLeft();
			if (keys[RIGHT]) Main->RunRight();
			if (!isGameOver) //update the stuff
			{
				Main->UpdateBullets();
				Second->UpdateBullets();
				Main->UpdatePlayer();
				Second->UpdatePlayer();
				Second->followMain(Main);

				level1->StartEnemy();
				level1->UpdateEnemy();
				Main->CheckCollideBullets(level1);
				Second->CheckCollideBullets(level1);
				level1->CollideEnemyPlayer(Main);

				if (Main->getHealth() <= 0) isGameOver = true;
				
			}
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) done = true;
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_R:
				isGameOver = false;
				Main->setHealth(50);
				Second->setHealth(50);
				Main->setScore(0);
				Second->setScore(0);
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = true;
				Main->FireBullets();
				break;
			case ALLEGRO_KEY_S:
				Main->changeCoord(Second);
				Player* temp = Main;
				Main = Second;
				Second = temp;
				temp = 0;
				break;


			}

		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;
			}
		}
		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;
			al_draw_bitmap(bgSheet, 0, 0, 0);
			int tot_score = Main->getScore() + Second->getScore();
			al_draw_textf(scorefont, al_map_rgb(0, 0, 0), width / 5, 30, ALLEGRO_ALIGN_RIGHT,
				"Score: %i", tot_score);
			al_draw_textf(scorefont, al_map_rgb(0, 0, 0), width / 4, 30, ALLEGRO_ALIGN_LEFT,
				"Lucy Health: %i", arr[0]->getHealth());
			al_draw_textf(scorefont, al_map_rgb(0, 0, 0), width / 2, 30, ALLEGRO_ALIGN_LEFT,
				"Daichi Health: %i", arr[1]->getHealth());
			if (!isGameOver)
			{
				//al_draw_bitmap(bgSheet, 0, 0, 0);
				Main->DrawBullets();
				Second->DrawBullets();
				Second->DrawPlayer();
				Main->DrawPlayer();
				level1->DrawEnemy();
			}
			else
			{
				al_draw_text(scorefont, al_map_rgb(0, 0, 0), width / 2, height / 2, ALLEGRO_ALIGN_CENTRE,
					"GAME OVER");
				al_draw_text(scorefont, al_map_rgb(0, 0, 0), width / 2, height / 2 + 100, ALLEGRO_ALIGN_CENTRE,
					"Press R to Restart");
			}

			al_flip_display();
			al_clear_to_color(white);
		}

	}
	al_destroy_display(display);
	//al_destroy_font(scorefont);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_bitmap(bgSheet);
	for (int i = 0; i < 2; i++)
	{
		delete arr[i];
		arr[i] = 0;
	}
	Main = 0;
		return 0;
}
