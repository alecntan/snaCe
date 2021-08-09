#ifndef FOOD_CONSTS
#define FOOD_WIDTH 5
#define FOOD_HEIGHT 5
#endif



typedef SDL_Rect Food;


// FUNCTION PROTOTYPES //
Food *create_food(void);

void destroy_food(Food *food);
