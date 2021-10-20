#ifndef FOOD_CONSTS
#define FOOD_WIDTH 5
#define FOOD_HEIGHT 5
#endif

// Forward declaration
typedef struct snake Snake;

typedef SDL_Rect Food;


// FUNCTION PROTOTYPES //
Food *create_food(void);

void change_food_pos(Food *food, Snake *snake);

void destroy_food(Food *food);
