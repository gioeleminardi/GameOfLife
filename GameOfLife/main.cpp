#include <iostream>
#include "GameOfLife.h"

constexpr int WIDTH = 1400;
constexpr int HEIGHT = 1000;
constexpr int CELL_SIZE = 5;

int main(int argn, char **argv)
{
	GameOfLife gameOfLife(WIDTH, HEIGHT, CELL_SIZE);

	gameOfLife.Loop();

	return 0;
}