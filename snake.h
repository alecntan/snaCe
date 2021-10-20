#ifndef CELL_CONSTS
#define SNAKE_WIDTH	20
#define SNAKE_HEIGHT 20
#endif

/// STRUCT DEFINTIONS ///
typedef struct snakeCell {
	SDL_Rect *rect;

	struct snakeCell *next;


} SnakeCell;

typedef struct snake {
	struct snakeCell *head;
	struct snakeCell *tail;

	int length;
	int next_x;
	int next_y;

	int dirVector[2];
	int vectorLength;
} Snake;



/// FUNCTION PROTOTYPES ///

Snake *create_snake(int initPosX, int initPosY);

void destroy_snake(Snake *snake);

void move_snake(Snake *snake);

void change_dir(Snake *snake, int x_dir, int y_dir);

void grow_snake(Snake *snake);

int pos_y(Snake *snake);

int pos_x(Snake *snake);

int hit_itself(Snake *snake);
