#include <iostream>
#include "GameOfLife.h"

constexpr int WIDTH = 640;
constexpr int HEIGHT = 480;

int main(int argn, char **argv)
{
	GameOfLife gameOfLife(WIDTH, HEIGHT);
	std::cout << "Hello World\n";

	system("pause");

	return 0;
}