#include"constant.h"
#include<time.h>

int keystate[NUM_KEYS];

bool isMoving = false;
double angle = 0;

bool quit = false;
bool died = false;

char restart = 0;

double projectile_speed = 30;
double player_image_angle = 0;

int level = 2;

clock_t time_passed_for_enemy = clock();
clock_t time_passed_for_weapon = clock();

int score = 1;