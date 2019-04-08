#include "GameOfLife.h"

GameOfLife::GameOfLife(int WIDTH, int HEIGHT): _width(WIDTH), _height(HEIGHT)
{
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

	// Init Event queue
	queue = al_create_event_queue();
	check_init(queue, "queue");

	// Init Timer
	timer = al_create_timer(TIMER_PERIOD);
	check_init(timer, "timer");

	// Create Display
	display = al_create_display(_width, _height);
	check_init(display, "display");

	// Create font
	font = al_create_builtin_font();
	check_init(font, "font");

	// Register keyboard, display, timer events
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));
}

void GameOfLife::check_init(bool condition, const std::string &msg)
{
	if (condition) return;

	printf("Error on %s init\n", msg);
	exit(-1);
}

void GameOfLife::clean_resources()
{

	al_destroy_font(font);
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);

}

GameOfLife::~GameOfLife()
{
}