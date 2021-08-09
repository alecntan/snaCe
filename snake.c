#include <SDL2/SDL.h>
#include "snake.h"
#include <stdio.h>
#include <stdlib.h>


#define SNAKE_SPEED		10

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

void print_snake(Snake *snake) {

	printf("Length: %d\n", snake->length);
	SnakeCell *currCell = snake->head;
	int currCount = 1;
	while( currCell != NULL) {
		printf("Cell %d: X: %d Y: %d\n", currCount, currCell->rect->x, currCell->rect->y);
		++currCount;
		currCell = currCell->next;
	}
}
