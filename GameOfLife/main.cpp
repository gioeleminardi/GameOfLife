#include <iostream>
#include "GameOfLife.h"

constexpr int WIDTH = 800;
constexpr int HEIGHT = 800;
constexpr int CELL_SIZE = 80;

int main(int argn, char **argv)
{
	GameOfLife gameOfLife(WIDTH, HEIGHT, CELL_SIZE);

	gameOfLife.Loop();

	return 0;
}