#ifndef _GAMEOFLIFE_H
#define _GAMEOFLIFE_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>

constexpr float FPS = 30.0;
constexpr float TIMER_PERIOD = 1 / FPS;

class GameOfLife
{
public:
	GameOfLife(int WIDTH, int HEIGHT);
	virtual ~GameOfLife();

	void Loop();

private:
	void check_init(bool condition, const std::string &msg);
	void init_allegro();
	void clean_resources();

private:
	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_TIMER* timer;
	ALLEGRO_FONT* font;
	
	int _width;
	int _height;
};

#endif // _GAMEOFLIFE_H