#include <SDL2/SDL.h>

typedef struct{
    SDL_Rect bg;
    SDL_Rect sp;
}rectangles;

typedef struct{
    SDL_Texture *background;
    SDL_Texture *stats_image;
    SDL_Texture *weapon_image;
}textures;

typedef struct{
    SDL_Texture *weapon_texture;
    SDL_Rect weapon_rect;
    float damage;
    double angle;
    double moving_x;
    double moving_y;
    
}weapon;

