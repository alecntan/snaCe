#include <SDL2/SDL.h>
#include <time.h>
#include <stdlib.h>
#include "snake.h"
#include "food.h"
#include "view.h"
#include <stdio.h>

Food *create_food(void) {

	Food *new_food = malloc(sizeof(Food));
	new_food->x = 320;
	new_food->y = 150;
	new_food->w = FOOD_WIDTH;
	new_food->h = FOOD_HEIGHT;

	return new_food;
}

void change_food_pos(Food *food, Snake *snake) {

	srand(time(NULL));
  int new_y = rand() % WINDOW_HEIGHT;
	while( new_y == 0 || new_y == WINDOW_HEIGHT || new_y == pos_y(snake)){
		new_y = rand() % (WINDOW_HEIGHT - 150);
	}

	int new_x = rand() % WINDOW_WIDTH;
	while( new_x == 0 || new_y == WINDOW_WIDTH || new_y == pos_x(snake)) {
		new_x = rand() % (WINDOW_WIDTH - 150);
	}

	food->x = new_x;
	food->y = new_y;
}

void destroy_food(Food *food) {
	free(food);
}
