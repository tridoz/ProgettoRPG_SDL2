#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<vector>

#include"image_files.h"

#include"functions.h"
#include"constant.h"

#include"structures.h"

using namespace std;

class enemy{

    private:
        float healt;
        float moving_speed;
        int spawn_point;
        int x, y;
        int weapon_type;
        SDL_Rect enemy_rect;
        SDL_Texture* enemy_texture;

    public:

        enemy(){}

        void set_enemy(SDL_Renderer* r, const char *texture_file_name, float healt, float moving_speed, int weapon_type){
            srand(time(NULL));
 
            spawn_point = rand()%4;

            /*
                0 = north;
                1 = east;
                2 = south;
                3 = west;
            */

            switch(spawn_point){
                case 0:
                    x = rand()%MAIN_MAP_WIDTH;
                    y = 0;
                    enemy_rect = {x, y, 100, 100};
                    break;
                case 1:
                    x = MAIN_MAP_WIDTH;
                    y = rand()%MAIN_MAP_HEIGTH;
                    enemy_rect =  { x, y, 100, 100};
                    break;
                case 2:
                    x = rand()%MAIN_MAP_WIDTH;
                    y = MAIN_MAP_HEIGTH;
                    enemy_rect = { x, y, 100, 100};
                    break;
                case 3:
                    x = 0;
                    y = rand()%MAIN_MAP_HEIGTH;
                    enemy_rect = { x, y, 100, 100};
                    break;
            }           

            enemy_texture = loadImageTexture(r, texture_file_name);
            this->healt = healt;
            this->moving_speed = moving_speed;       
            this->weapon_type = weapon_type;

        }

        void take_damage(vector<weapon> to_check){
            for(std::vector<weapon>::size_type i = 0 ; i<to_check.size() ; i++){
                if( SDL_HasIntersection( &to_check[i].weapon_rect , &enemy_rect )){
                    healt -= to_check[i].damage;
                    to_check.erase(to_check.begin() + i );
                }

                if(healt <= 0){
                    to_check.erase( to_check.begin() + i);
                    score++;
                    return;
                }

            } 

        }

        int get_spawn_point(){ return this->spawn_point; }
        float get_healt(){ return healt; }
        float get_X(){ return enemy_rect.x; }
        float get_Y(){ return enemy_rect.y; }
        int get_weapon_type(){return weapon_type; }
        void set_X(int num){ enemy_rect.x += num; }
        void set_Y(int num){ enemy_rect.y += num; }
        float get_moving_speed(){ return moving_speed; }
        int get_SX(){ return x; }
        int get_SY(){ return y; }

        SDL_Rect *get_enemy_rect(){ return &enemy_rect; }
        SDL_Texture *get_enemy_texture(){ return enemy_texture; }
        


        
};


class player{
    private:

        float healt;
        float moving_speed;
        float damage;

        int direction;
        bool change_map;
        
        SDL_Texture* pg_image;
        SDL_Rect player_rectangle;
    
    public:

        player(){
            healt = 100;            
            moving_speed = 10;
        }
    
        void set_player(SDL_Renderer *r, float damage){
            pg_image = loadImageTexture(r, player_image);
            player_rectangle = {INITIAL_SPAWN_COORDINATE_X, INITIAL_SPAWN_COORDINATE_Y, WIDTH_PG_IMAGE, HEIGTH_PG_IMAGE};
            this->damage = damage;
        }

        SDL_Texture* get_player_image(){
            return pg_image;
        }

        SDL_Rect* get_player_rect(){
            return &player_rectangle;
        }

        float calculate_moving_speed(bool diagonal){

            if(diagonal){
                return moving_speed  * DIAGONAL_FACTOR;
            }

            return moving_speed ;

        }
        
        float get_healt(){ return healt; }
        
        float get_X(){ return player_rectangle.x; }

        float get_Y(){ return player_rectangle.y; }

        float get_damage(){return damage; }

        void set_X(int num){ player_rectangle.x = num; }

        void set_Y(int num){ player_rectangle.y = num; }

        void take_damage(vector<weapon> to_check){
            for(std::vector<weapon>::size_type i = 0 ; i<to_check.size() ; i++){

                if( SDL_HasIntersection( &to_check[i].weapon_rect , &player_rectangle )){
                    healt -= to_check[i].damage;
                    to_check.erase( to_check.begin() + i );
                }

                if(healt <= 0){
                    quit = true;
                    return;
                }
                        
            } 

        }

       
      
};

