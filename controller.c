#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "controller.h"
#include "view.h"
#include "snake.h"
#include "food.h"


int main(void){

	Snake *snake = create_snake(320, 350);
	View *view = init_view();
	Food *food = create_food();

	draw_snake(view, snake);
	draw_food(view, food);

	SDL_Event event;
	int playing = 1;
	while(playing) {
		while(SDL_PollEvent(&event)) {
			if(event.type == SDL_KEYDOWN) {
				SDL_Keycode keycode = event.key.keysym.sym;
				if(keycode == SDLK_ESCAPE) {
					playing = 0;
					break;
				} else if(keycode == SDLK_UP) {
					change_dir(snake, 0, -1 );
				} else if(keycode == SDLK_DOWN) {
					change_dir(snake, 0, 1);
				} else if(keycode == SDLK_RIGHT) {
					change_dir(snake, 1, 0);
				} else if(keycode == SDLK_LEFT) {
					change_dir(snake, -1, 0);
				} else if(keycode == SDLK_q) {
					SDL_Quit();
					return 0;
				} else if(keycode == SDLK_r) {
					destroy_snake(snake);
					snake = create_snake(320, 350);
					draw_snake(view, snake);
				}
			} else if(event.type == SDL_WINDOWEVENT) {
				if(event.window.event == SDL_WINDOWEVENT_CLOSE){
					SDL_Quit();
					return 0;
				}
			}
		}


		move_snake(snake);
		update_view(view, snake, food);
		SDL_Delay(50);

		int curr_y = pos_y(snake);
		int curr_x = pos_x(snake);

	  if( is_hit_wall(snake) || hit_itself(snake) ){
			destroy_snake(snake);
			destroy_food(food);
			snake = create_snake(320, 350);
			food = create_food();
			draw_snake(view, snake);
			draw_food(view, food);
		}
	}

	return 0;
}
