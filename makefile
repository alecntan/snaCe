CC=gcc
DEPS= model.h view.h

run_snake: model.c view.c controller.c 
	gcc -o run_snake model.c view.c controller.c `sdl2-config --cflags --libs`
