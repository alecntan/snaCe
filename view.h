#ifndef CELL_CONSTS
#define CELL_WIDTH 	   20
#define CELL_HEIGHT    20
#define RECT_HEIGHT    20
#define RECT_WIDTH     20
#define WINDOW_WIDTH   640
#define WINDOW_HEIGHT  480
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

int pos_y(Snake *snake);

int pos_x(Snake *snake);

void draw_food(View *view, Food *food);

void change_food_pos(Food *food, Snake *snake);

int is_hit_wall(Snake *snake);
