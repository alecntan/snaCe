#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <time.h>


#include "model.h"
#include "view.h"

#define SNAKE_SPEED		10


//// SNAKE ////
Snake *create_snake(int initPosX, int initPosY){

	// Initialise new snake
	Snake *snake = malloc(sizeof(Snake));
	snake->length = 1;
	snake->dirVector[0] = 0;
	snake->dirVector[1] = -1;
	snake->vectorLength = 2;
	snake->next_x = 0; // initial value
	snake->next_y = 0; // Initial Value

	// Add head to new snake
	snake->head = malloc(sizeof(SnakeCell));
	snake->head->rect =  malloc(sizeof(SDL_Rect));
	snake->head->rect->x = initPosX;
	snake->head->rect->y = initPosY;
	snake->head->rect->w = SNAKE_WIDTH;
	snake->head->rect->h = SNAKE_HEIGHT;

	snake->head->next = NULL;
	snake->tail = snake->head;

	// Initial length of snake is 3
	grow_snake(snake);
	grow_snake(snake);
	grow_snake(snake);
	grow_snake(snake);
	grow_snake(snake);
	grow_snake(snake);

	return snake;
}


void destroy_snake(Snake *snake){

	SnakeCell *curr_cell = snake->head;
	SnakeCell *temp = NULL;
	while( curr_cell != NULL) {
		temp = curr_cell;
		curr_cell = curr_cell->next;
		free(temp->rect);
		free(temp);
	}

	free(snake);
}


void move_snake(Snake *snake){

	int prevX = snake->head->rect->x;
	int prevY = snake->head->rect->y;

	snake->next_x = snake->tail->rect->x;
	snake->next_y = snake->tail->rect->y;


	int tempX, tempY;
	int deltaX = snake->dirVector[0] * SNAKE_SPEED;
	int deltaY = snake->dirVector[1] * SNAKE_SPEED;

	SnakeCell *currCell = snake->head;
	while( currCell != NULL) {
		if (currCell == snake->head) {
			currCell->rect->x = currCell->rect->x + deltaX;
			currCell->rect->y = currCell->rect->y + deltaY;
		} else {
			tempX = currCell->rect->x;
			tempY = currCell->rect->y;

			currCell->rect->x = prevX;
			currCell->rect->y = prevY;

			prevX = tempX;
			prevY = tempY;
		}

		currCell = currCell->next;
	}

}


void change_dir(Snake *snake, int x_dir, int y_dir) {

	if( x_dir == (-1) * snake->dirVector[0] && y_dir == (-1) * snake->dirVector[1]) {
		return;
	}

	snake->dirVector[0] = x_dir;
	snake->dirVector[1] = y_dir;

}


void grow_snake(Snake *snake){

	SnakeCell *newTail = malloc(sizeof(SnakeCell));
	newTail->rect = malloc(sizeof(SDL_Rect));
	newTail->rect->x = snake->next_x;
	newTail->rect->y = snake->next_y;
	newTail->rect->w = SNAKE_WIDTH;
	newTail->rect->h = SNAKE_HEIGHT;
	newTail->next = NULL;

	snake->tail->next = newTail;
	snake->tail = newTail;
	++snake->length;
}


int hit_itself(Snake *snake) {


	int curr_x = snake->head->rect->x;
	int curr_y = snake->head->rect->y;

	SnakeCell *curr_cell = snake->head;
	while( curr_cell != NULL) {
		if( curr_cell != snake->head && (curr_cell->rect->x == curr_x && curr_cell->rect->y == curr_y)){
			return 1;
		}

		curr_cell = curr_cell->next;
	}

	return 0;
}

int pos_y(Snake *snake) {
	return snake->head->rect->y;
}

int pos_x(Snake *snake) {
	return snake->head->rect->x;
}

int is_hit_wall(Snake *snake) {

	int curr_y = pos_y(snake);
	int curr_x = pos_x(snake);

	if( curr_y < 0 || curr_y > WINDOW_HEIGHT) {
		return 1;
	} else if ( curr_x < 0 || curr_x > WINDOW_WIDTH ) {
		return 1;
	}

	return 0;
}


//// FOOD ////
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
