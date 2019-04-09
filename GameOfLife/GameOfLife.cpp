#include "GameOfLife.h"
#include <random>

GameOfLife::GameOfLife(int width, int height, int cell_size): _width(width), _height(height), _cell_size(cell_size)
{
	_cols = std::round(width / cell_size);
	_rows = std::round(height / cell_size);

	_grid = new int[_rows * _cols];
	check_init(_grid, "grid");

	_next_grid = new int[_rows * _cols];
	check_init(_next_grid, "next_grid");

	init_grid();

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
			apply_rules();
			
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
			al_clear_to_color(al_map_rgb(0, 0, 0));

			draw_grid(_next_grid);
			swap_grid();

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

void GameOfLife::draw_grid(int *grid)
{
	int grid_offset = 0;
	int x1, y1, x2, y2;
	for (int row = 0; row < _rows; ++row)
	{
		for (int col = 0; col < _cols; ++col)
		{
			grid_offset = row * _cols + col;
			
			if (grid[grid_offset] == 1)
			{
				x1 = col * _cell_size;
				y1 = row * _cell_size;

				x2 = x1 + _cell_size - 1;
				y2 = y1 + _cell_size - 1;

				DrawRect(x1, y1, x2, y2, al_map_rgb(255, 255, 255));
			}
		}
	}
}

void GameOfLife::apply_rules()
{
	int grid_offset = 0;
	int sum;
	for (int row = 0; row < _rows; ++row)
	{
		for (int col = 0; col < _cols; ++col)
		{
			grid_offset = row * _cols + col;
			sum = check_neighbours(_grid, row, col);

			if (sum < 2 || sum > 3)
				_next_grid[grid_offset] = 0;
			else if (sum == 3)
				_next_grid[grid_offset] = 1;
			else
				_next_grid[grid_offset] = _grid[grid_offset];
		}
	}
}

int GameOfLife::check_neighbours(int * grid, int row, int col)
{
	int sum = 0;
	int new_row = 0, new_col = 0;
	int grid_offset = 0, cell_offset = row * _cols + col;

	for (int i = -1; i < 2; ++i)
	{
		for (int j = -1; j < 2; ++j)
		{
			new_col = col + j;
			new_row = row + i;

			new_col = (new_col + _cols) % _cols;
			new_row = (new_row + _rows) % _rows;

			grid_offset = new_row * _cols + new_col;
			
			if(grid_offset != cell_offset)
				sum += grid[grid_offset];

		}
	}

	return sum;
}

void GameOfLife::swap_grid()
{
	int *temp = _grid;
	_grid = _next_grid;
	_next_grid = temp;

	std::memset(_next_grid, 0, _cols * _rows * sizeof(int));
}

GameOfLife::~GameOfLife()
{

}