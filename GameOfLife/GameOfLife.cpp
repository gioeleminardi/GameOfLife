#include "GameOfLife.h"
#include <random>;

GameOfLife::GameOfLife(int width, int height, int cell_size): _width(width), _height(height), _cell_size(cell_size)
{
	_rows = std::round(width / cell_size);
	_cols = std::round(height / cell_size);

	_grid = new int[_rows * _cols];
	check_init(_grid, "grid");

	_next_grid = new int[_rows * _cols];
	check_init(_next_grid, "next_grid");

	init_grid();
	debug_grid(_grid);

	init_allegro();
}

void GameOfLife::Loop()
{
	ALLEGRO_EVENT event;

	bool redraw = false;
	bool done = false;

	al_start_timer(timer);

	while (true)
	{
		al_wait_for_event(queue, &event);

		switch (event.type)
		{
		case ALLEGRO_EVENT_TIMER:
			redraw = true;
			break;
		case ALLEGRO_EVENT_KEY_DOWN:
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			done = true;
			break;
		default:
			break;
		}

		if (done)
			break;

		if (redraw && al_is_event_queue_empty(queue))
		{

			al_flip_display();
		}
	}

	clean_resources();
}

void GameOfLife::init_allegro()
{
	// Init Allegro system
	check_init(al_init(), "allegro");

	// Init Keyboard system
	check_init(al_install_keyboard(), "keyboard");

	// Init font addon
	check_init(al_init_font_addon(), "font addon");

	// Init primitives addon
	check_init(al_init_primitives_addon(), "primitives addon");

	// Init Event queue
	queue = al_create_event_queue();
	check_init(queue, "queue");

	// Init Timer
	timer = al_create_timer(TIMER_PERIOD);
	check_init(timer, "timer");

	// Create Display
	display = al_create_display(_width, _height);
	check_init(display, "display");

	set_window_title();

	// Create font
	font = al_create_builtin_font();
	check_init(font, "font");

	// Register keyboard, display, timer events
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));
}

void GameOfLife::DrawRect(float x1, float y1, float x2, float y2, ALLEGRO_COLOR color)
{
	al_draw_filled_rectangle(x1, y1, x2, y2, color);
}

void GameOfLife::check_init(bool condition, const std::string &msg)
{
	if (condition) return;

	printf("Error on %s init\n", msg.c_str());
	exit(-1);
}

void GameOfLife::clean_resources()
{
	al_destroy_font(font);
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);
	al_shutdown_primitives_addon();
}

void GameOfLife::set_window_title()
{
	al_set_window_title(display, GAME_NAME);
}

void GameOfLife::init_grid()
{
	std::random_device r;
	std::default_random_engine e1(r());
	std::uniform_int_distribution<int> uniform_dist(0, 1);


	int grid_offset = 0;
	for (int row = 0; row < _rows; ++row)
	{
		for (int col = 0; col < _cols; ++col)
		{
			grid_offset = row * _cols + col;
			_grid[grid_offset] = uniform_dist(e1);
		}
	}

}

void GameOfLife::debug_grid(int * grid)
{
	int grid_offset = 0;
	for (int row = 0; row < _rows; ++row)
	{
		for (int col = 0; col < _cols; ++col)
		{
			grid_offset = row * _cols + col;
			printf("%d", grid[grid_offset]);
			if (col + 1 < _cols)
				printf("\t");
		}
		printf("\n");
	}
}

GameOfLife::~GameOfLife()
{
}