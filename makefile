CC=gcc
DEPS= snake.h view.h controller.h food.h

run_snake: snake.c view.c controller.c food.c
	gcc -o run_snake snake.c view.c controller.c food.c `sdl2-config --cflags --libs`
