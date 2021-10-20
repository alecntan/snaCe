#include <SDL2/SDL.h>
#include <time.h>
#include <stdlib.h>
#include "food.h"
#include "snake.h"
#include "view.h"
#include "controller.h"


View *init_view(void) {

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		SDL_Log("Unable to initialise SDL: %s\n", SDL_GetError());
		return NULL;
	}

	View *view = malloc(sizeof(View));

 	view->window = SDL_CreateWindow(
		"Snake",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);

	if(view->window == NULL) {
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL;
	}

	view->renderer = SDL_CreateRenderer(view->window, -1, SDL_RENDERER_ACCELERATED );
	return view;
}

void draw_snake(View *view, Snake *snake) {

	SDL_SetRenderDrawColor(view->renderer, 255, 255, 255, 255);

	SnakeCell *curr_cell = snake->head;
	while(curr_cell != NULL) {
		SDL_RenderFillRect(view->renderer, curr_cell->rect);
		if(SDL_RenderDrawRect(view->renderer, curr_cell->rect) != 0){
			printf("Could not draw rectangle: %s\n", SDL_GetError());
		}
		curr_cell = curr_cell->next;
	}
}

void draw_food(View *view, Food *food){

	SDL_SetRenderDrawColor(view->renderer, 100, 100, 255, 100);
	SDL_RenderFillRect(view->renderer, food);
	if(SDL_RenderDrawRect(view->renderer, food) != 0) {
		printf("Could not draw food: %s\n", SDL_GetError());
	}

	SDL_SetRenderDrawColor(view->renderer, 255, 255, 255, 255);
}

void update_view(View *view, Snake *snake, Food *food) {

	SDL_SetRenderDrawColor(view->renderer, 0, 0, 0, 0);
	SDL_RenderClear(view->renderer);
	SDL_SetRenderDrawColor(view->renderer, 255, 255, 255, 255);


	if( (food->y >= pos_y(snake) && food->y <= pos_y(snake) + CELL_HEIGHT)  &&
	    (food->x >= pos_x(snake) && food->x <= pos_x(snake) + CELL_WIDTH ) ){
		grow_snake(snake);
		change_food_pos(food, snake);
	}

	draw_food(view, food);

	SnakeCell *curr_cell = snake->head;

	while( curr_cell != NULL ) {

		if (SDL_RenderDrawRect(view->renderer, curr_cell->rect) != 0) {
			printf("Could not draw rectangle: %s\n", SDL_GetError());
		}
		SDL_RenderFillRect(view->renderer, curr_cell->rect);
		curr_cell = curr_cell->next;
	}

	SDL_RenderPresent(view->renderer);
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
