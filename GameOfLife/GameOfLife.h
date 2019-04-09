#ifndef _GAMEOFLIFE_H
#define _GAMEOFLIFE_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <string>

#define GAME_NAME "Game Of Life"
#define VERSION "0.0.1a"

constexpr float FPS = 30.0;
constexpr float TIMER_PERIOD = 1 / FPS;

class GameOfLife
{
public:
	GameOfLife(int width, int height, int cell_size);
	virtual ~GameOfLife();

	void Loop();

protected:

	void DrawRect(float x1, float y1, float x2, float y2, ALLEGRO_COLOR color);

private:
	void check_init(bool condition, const std::string &msg);
	void init_allegro();
	void clean_resources();
	void set_window_title();
	void init_grid();
	void draw_grid(int *grid);
	void apply_rules();
	int check_neighbours(int *grid, int row, int col);
	void swap_grid();

	void debug_grid(int *grid);

private:
	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_TIMER* timer;
	ALLEGRO_FONT* font;
	
	int _width;
	int _height;
	int _cell_size;

	int _rows;
	int _cols;

	int *_grid;
	int *_next_grid;
};

#endif // _GAMEOFLIFE_H