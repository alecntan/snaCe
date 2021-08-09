#include <SDL2/SDL.h>
#include <time.h>
#include <stdlib.h>
#include "food.h"
#include <stdio.h>

Food *create_food(void) {

	Food *new_food = malloc(sizeof(Food));
	new_food->x = 320;
	new_food->y = 150;
	new_food->w = FOOD_WIDTH;
	new_food->h = FOOD_HEIGHT;

	return new_food;
}

void destroy_food(Food *food) {
	free(food);
}
