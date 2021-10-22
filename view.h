#ifndef CELL_CONSTS
#define CELL_WIDTH 	   20
#define CELL_HEIGHT    20
#define RECT_HEIGHT    20
#define RECT_WIDTH     20
#define WINDOW_WIDTH   640
#define WINDOW_HEIGHT  480

#define SNAKE_WIDTH	20
#define SNAKE_HEIGHT 20

#define FOOD_WIDTH 5
#define FOOD_HEIGHT 5

#endif


// Forward declarations
typedef struct snake Snake;
typedef SDL_Rect Food;


typedef struct view {

	SDL_Window *window;
	SDL_Renderer *renderer;

}View;

View *init_view(void);

void draw_snake(View *view, Snake *snake);

void update_view(View *view, Snake *snake, Food *food);

void draw_food(View *view, Food *food);

