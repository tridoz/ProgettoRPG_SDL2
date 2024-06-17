#include    "../header/game.h"

using namespace std;

//GLOBAL VARIABLES/*
SDL_Window *window;
SDL_Renderer *renderer;

SDL_Rect bg;
textures texture_set;

vector<weapon> weapon_displaced_by_player;
vector<weapon> weapon_displaced_by_enemy;

vector<enemy> enemies;

player MAIN_PG;
TTF_Font* my_personal_font;
SDL_Color text_color = {255, 255, 255, 255};
SDL_Event e;
string texts[NUMBER_OF_TEXTS];

    
void gestisci_input_tastiera(){

    //if( SDL_HasIntersection(MAIN_PG.get_player_rect() , map_set[STATO_GIOCATORE].get_walking_zone() ) ){

        if(keystate[SDL_SCANCODE_W] && keystate[SDL_SCANCODE_A] ){

            MAIN_PG.set_Y( MAIN_PG.get_Y() - MAIN_PG.calculate_moving_speed(1 ));
            MAIN_PG.set_X( MAIN_PG.get_X() - MAIN_PG.calculate_moving_speed(1) );
            player_image_angle = 135;

        }else if(keystate[SDL_SCANCODE_W] && keystate[SDL_SCANCODE_D] ){

            MAIN_PG.set_Y( MAIN_PG.get_Y() - MAIN_PG.calculate_moving_speed(1));
            MAIN_PG.set_X( MAIN_PG.get_X() + MAIN_PG.calculate_moving_speed(1));     
            player_image_angle = 225;

        }else if(keystate[SDL_SCANCODE_S] && keystate[SDL_SCANCODE_A] ){

            MAIN_PG.set_Y( MAIN_PG.get_Y() + MAIN_PG.calculate_moving_speed(1));
            MAIN_PG.set_X( MAIN_PG.get_X() - MAIN_PG.calculate_moving_speed(1));           
            player_image_angle = 45;

        }else if(keystate[SDL_SCANCODE_S] && keystate[SDL_SCANCODE_D] ){

            MAIN_PG.set_Y( MAIN_PG.get_Y() + MAIN_PG.calculate_moving_speed(1));
            MAIN_PG.set_X( MAIN_PG.get_X() + MAIN_PG.calculate_moving_speed(1));          
            player_image_angle = 315;

        }else if(keystate[SDL_SCANCODE_W]){


            MAIN_PG.set_Y( MAIN_PG.get_Y() - MAIN_PG.calculate_moving_speed(0));
            player_image_angle = 180;

            if(MAIN_PG.get_Y() < 0 ){
                MAIN_PG.set_Y( MAIN_MAP_HEIGTH );
            }

        }else if(keystate[SDL_SCANCODE_S]){

            MAIN_PG.set_Y( MAIN_PG.get_Y() + MAIN_PG.calculate_moving_speed(0) );
            player_image_angle = 0;

            if(MAIN_PG.get_Y() > MAIN_MAP_HEIGTH ){
                MAIN_PG.set_Y( MAIN_MAP_Y_POSITION );
            }

        }else if(keystate[SDL_SCANCODE_A]){

            MAIN_PG.set_X( MAIN_PG.get_X() - MAIN_PG.calculate_moving_speed(0));
            player_image_angle = 90;
            if(MAIN_PG.get_X() < MAIN_MAP_X_POSITION){
                MAIN_PG.set_X( MAIN_MAP_WIDTH + MAIN_MAP_X_POSITION );
            }

        }else if(keystate[SDL_SCANCODE_D]){

            MAIN_PG.set_X( MAIN_PG.get_X() + MAIN_PG.calculate_moving_speed(0));
            player_image_angle = 270;
            if(MAIN_PG.get_X() > MAIN_MAP_WIDTH + MAIN_MAP_X_POSITION ){
                MAIN_PG.set_X( MAIN_MAP_X_POSITION );
            }

        }

}

void moveProjectile(){
    for( std::vector<enemy>::size_type i = 0 ; i<weapon_displaced_by_player.size() ; i++){
        weapon_displaced_by_player[i].weapon_rect.x += weapon_displaced_by_player[i].moving_x;
        weapon_displaced_by_player[i].weapon_rect.y -= weapon_displaced_by_player[i].moving_y;

        int x = weapon_displaced_by_player[i].weapon_rect.x;
        int y = weapon_displaced_by_player[i].weapon_rect.y;

        if( (x < MAIN_MAP_X_POSITION )|| ( x > MAIN_MAP_X_POSITION + MAIN_MAP_WIDTH) ){
            weapon_displaced_by_player.erase( i + weapon_displaced_by_player.begin());
        }

        if( (y < MAIN_MAP_Y_POSITION )|| ( y > MAIN_MAP_X_POSITION + MAIN_MAP_HEIGTH) ){
            weapon_displaced_by_player.erase( i + weapon_displaced_by_player.begin());     
        }
    }

    for( std::vector<enemy>::size_type i = 0 ; i<weapon_displaced_by_enemy.size() ; i++){
        weapon_displaced_by_enemy[i].weapon_rect.x += weapon_displaced_by_enemy[i].moving_x;
        weapon_displaced_by_enemy[i].weapon_rect.y -= weapon_displaced_by_enemy[i].moving_y;

        int x = weapon_displaced_by_enemy[i].weapon_rect.x;
        int y = weapon_displaced_by_enemy[i].weapon_rect.y;

        if( (x < MAIN_MAP_X_POSITION )|| ( x > MAIN_MAP_X_POSITION + MAIN_MAP_WIDTH) ){
            weapon_displaced_by_enemy.erase( i + weapon_displaced_by_enemy.begin());
        }else if( (y < MAIN_MAP_Y_POSITION )|| ( y > MAIN_MAP_X_POSITION + MAIN_MAP_HEIGTH) ){
            weapon_displaced_by_enemy.erase( i + weapon_displaced_by_enemy.begin());     
        }    
    }
    
}

void checkWeapon(){

    if(keystate[SDL_SCANCODE_1]){
        texture_set.weapon_image = loadImageTexture(renderer, fireball_image);
    }else if(keystate[SDL_SCANCODE_2]){
        texture_set.weapon_image = loadImageTexture(renderer, bolt_image);
    }else if(keystate[SDL_SCANCODE_3]){
        texture_set.weapon_image = loadImageTexture(renderer, void_orb_image);
    }else if(keystate[SDL_SCANCODE_4]){
        texture_set.weapon_image = loadImageTexture(renderer, poison_spit_image);
    }
}

void set_structs(){
   bg  = {MAIN_MAP_X_POSITION, MAIN_MAP_Y_POSITION, MAIN_MAP_WIDTH, MAIN_MAP_HEIGTH};

    texture_set.background  = loadImageTexture(renderer, MAIN_ROOM_MAP);
    texture_set.stats_image = loadImageTexture(renderer, stats_panel);
    texture_set.weapon_image = loadImageTexture(renderer, no_weapon);

}

void print_data_on_terminal(){
    printf("PLAYER:\n");
    printf("\tPOSITION: x[%.2f] -> y[%.2f] ", MAIN_PG.get_X() , MAIN_PG.get_Y() );
}

void print_memory_data(){
    printf("\n\nMEMORY:\n");
    printf("weapond_displaced size[%ld]\n", weapon_displaced_by_player.size());
    printf("size of rectangle set[%ld]\n", sizeof(bg));
    printf("size of texture set[%ld]\n", sizeof(texture_set));
    printf("size of player[%ld]\n", sizeof(MAIN_PG));
    printf("size of font[%ld]\n", sizeof(my_personal_font));
    printf("size of enemy[%ld]",enemies.size());
}


void print_projectiles(){
    for(std::vector<enemy>::size_type i = 0 ; i<weapon_displaced_by_player.size() ; i++){
        SDL_RenderDrawRect(renderer, &weapon_displaced_by_player[i].weapon_rect);
        SDL_RenderCopyEx(renderer, weapon_displaced_by_player[i].weapon_texture, NULL, &weapon_displaced_by_player[i].weapon_rect, weapon_displaced_by_player[i].angle , NULL, SDL_FLIP_NONE);
    }

    for( std::vector<enemy>::size_type i = 0 ; i<weapon_displaced_by_enemy.size() ; i++){
        SDL_RenderDrawRect(renderer, &weapon_displaced_by_enemy[i].weapon_rect);
        SDL_RenderCopyEx(renderer, weapon_displaced_by_enemy[i].weapon_texture, NULL, &weapon_displaced_by_enemy[i].weapon_rect, weapon_displaced_by_enemy[i].angle , NULL, SDL_FLIP_NONE);
    }
}

void print_data_panel(){
    SDL_Surface* textSurface;
    SDL_Texture* textTexture;

    for(int i = 0 ; i<NUMBER_OF_TEXTS ; i++){
        textSurface = TTF_RenderText_Solid(my_personal_font, texts[i].c_str() , text_color );
        textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_FreeSurface(textSurface);
        SDL_Rect dstRect = {50, (55*i), 50, 400};
        SDL_QueryTexture(textTexture, nullptr, nullptr, &dstRect.w, &dstRect.h);
        SDL_RenderCopy(renderer, textTexture, nullptr, &dstRect);
    }

    SDL_DestroyTexture(textTexture);

}

void generate_enemies(){
    srand(time(NULL));
    
    
    clock_t end = clock();
    int milliseconds = end-time_passed_for_enemy;

    if( milliseconds > time_passed_for_enemy/level){
        int enemy_type = rand()%100;

        if(enemy_type < 15)
            enemy_type = 4;
        else if(enemy_type < 30)
            enemy_type = 3;
        else if(enemy_type < 50)
            enemy_type = 2;
        else
            enemy_type = 1;
        
        time_passed_for_enemy = clock();
        enemy x;
        
        switch(enemy_type){
            case 1:
                x.set_enemy(renderer, zombi_image , 100, 7, 1);
                enemies.push_back(x);   
                break;

            case 2:
                x.set_enemy(renderer, slime_image , 150, 5, 2);
                enemies.push_back(x);
                break;

            case 3:
                x.set_enemy(renderer, bee_image , 50, 10, 3);
                enemies.push_back(x);
                break;

            case 4:
                x.set_enemy(renderer, ghost_image , 500, 3, 4);
                enemies.push_back(x);
                break;
        }    
    }


}

void print_enemy(){
    for(std::vector<enemy>::size_type i = 0 ; i<enemies.size() ; i++){
        SDL_RenderDrawRect(renderer, enemies[i].get_enemy_rect());
        SDL_RenderCopy(renderer, enemies[i].get_enemy_texture(), NULL,  enemies[i].get_enemy_rect());
    }
}

void move_enemies(){
    for(std::vector<enemy>::size_type i = 0; i<enemies.size() ; i++){
        if(enemies[i].get_healt() <= 0){
            enemies.erase(enemies.begin() + i);
            continue;
        }


        int playerX = MAIN_PG.get_X(), playerY = MAIN_PG.get_Y();

        double dX = (double)enemies[i].get_X() - playerX;
        double dY = playerY - (double)enemies[i].get_Y(); 

        double ip = sqrt( pow(dX, 2) + pow(dY, 2));

        angle =  acos(  dY / ip)  ;
        
        dX = enemies[i].get_moving_speed() * sin(angle);
        dY = enemies[i].get_moving_speed() * cos(angle);

        if(playerX < enemies[i].get_X()){
            dX = -dX;
        }

        
        enemies[i].set_X( dX );
        enemies[i].set_Y( dY );

    }
}

void take_damage(){
    MAIN_PG.take_damage( weapon_displaced_by_enemy );
    for( std::vector<enemy>::size_type i = 0 ; i<enemies.size() ; i++){
        enemies[i].take_damage( weapon_displaced_by_player );
    }
}

void enemies_shoot(){
    srand(time(NULL));
    for( std::vector<enemy>::size_type i = 0 ; i<enemies.size() ; i++){
         clock_t end = clock();
        
        int milliseconds = end-time_passed_for_weapon;

        if( (100-20*level) < rand()%100  && milliseconds > time_passed_for_weapon/level ){
            time_passed_for_weapon = clock();
            int playerX = MAIN_PG.get_X() , playerY = MAIN_PG.get_Y();
            int enemyX = enemies[i].get_X(), enemyY = enemies[i].get_Y();

            double dX = (double)playerX - (double)enemyX;
            double dY = (double)enemyY - (double)playerY; 

            double ip = sqrt( pow(dX, 2) + pow(dY, 2));

            angle =  acos(  dY / ip)  ;
            
            dX = projectile_speed * sin(angle);
            dY = projectile_speed * cos(angle);
            double angle_weapon = angle;

            if( playerX < enemyX){
                dX = -dX;
                angle_weapon = -angle_weapon;
            }


            switch( enemies[i].get_weapon_type() ){
                case 1:
                    weapon_displaced_by_enemy.push_back( { loadImageTexture(renderer, zombi_weapon) , {enemyX, enemyY, 40, 40} , 20, ( angle_weapon * 180 / M_PI ) , dX, dY } );
                    break;
                case 2:
                    weapon_displaced_by_enemy.push_back( { loadImageTexture(renderer, slime_weapon) , {enemyX, enemyY, 40, 40} , 30, ( angle_weapon * 180 / M_PI ) , dX, dY } );
                    break;
                case 3:
                   weapon_displaced_by_enemy.push_back( { loadImageTexture(renderer, bee_weapon) , {enemyX, enemyY, 40, 40} , 50, ( angle_weapon * 180 / M_PI ) , dX, dY } );
                    break;
                case 4:
                    weapon_displaced_by_enemy.push_back( { loadImageTexture(renderer, ghost_image) , {enemyX, enemyY, 40, 40} , 10, ( angle_weapon * 180 / M_PI ) , dX, dY } );
                    break;

            }
        }
    }


}

void __init__(){
    //display_loading_screen();
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    memset(keystate, 0, NUM_KEYS * sizeof(int) );
    window = SDL_CreateWindow("is that RPG??" , SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGTH, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    my_personal_font = TTF_OpenFont("../../images/font/font.ttf" , 36);
    MAIN_PG.set_player(renderer, 50);
    set_texts();
    set_structs();    
}

void __dispose__(){
    SDL_DestroyTexture(MAIN_PG.get_player_image());
    SDL_DestroyTexture(texture_set.background);
    SDL_DestroyTexture(texture_set.stats_image);
    SDL_DestroyTexture(texture_set.weapon_image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(my_personal_font);
    SDL_Quit(); 
}

int main(void){

game: 

   __init__();

    while(!quit){

        while(SDL_PollEvent(&e)){

            if(e.type == SDL_QUIT){
                quit = true;
            }else if(e.type == SDL_KEYDOWN && e.key.keysym.scancode < NUM_KEYS){
                keystate[e.key.keysym.scancode] = 1;
            }else if(e.type == SDL_KEYUP && e.key.keysym.scancode < NUM_KEYS){
                keystate[e.key.keysym.scancode] = 0;
            }


            if( e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT ){


                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                double dX = (double)mouseX - MAIN_PG.get_X();
                double dY = MAIN_PG.get_Y() - (double)mouseY; 

                double ip = sqrt( pow(dX, 2) + pow(dY, 2));

                angle =  acos(  dY / ip)  ;
                
                dX = projectile_speed * sin(angle);
                dY = projectile_speed * cos(angle);
                double angle_weapon = angle;

                if( mouseX < MAIN_PG.get_X()){
                    dX = -dX;
                    angle_weapon = -angle_weapon;
                }

                weapon_displaced_by_player.push_back( { texture_set.weapon_image, { (int)MAIN_PG.get_X()  , (int)MAIN_PG.get_Y() , 30, 50}, MAIN_PG.get_damage(),  ( angle_weapon * 180 / M_PI ) , dX, dY } );
                mouseX = 0;
                mouseY = 0;
            }

        }

        gestisci_input_tastiera();
        checkWeapon();

        generate_enemies();
        move_enemies();
        enemies_shoot();
        moveProjectile();

        //pulisco il terminale
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        //imposto il tenderer in modo da poter cambiare l'opacita di quello che viene designato
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

        //setto il colore a 0 trasparente 
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

        //disegno lo sfondo
        SDL_RenderDrawRect(renderer, &bg);
        SDL_RenderCopy(renderer, texture_set.background, NULL, &bg);

        //disegno il pannello delle statistiche (da riempire)

        //disegno il personaggio
        SDL_RenderDrawRect(renderer, MAIN_PG.get_player_rect());

        SDL_RenderCopyEx(renderer, MAIN_PG.get_player_image() , NULL, MAIN_PG.get_player_rect() , player_image_angle, NULL, SDL_FLIP_NONE);

        //disegno l'arma. 
        print_projectiles();
        print_enemy();

        SDL_RenderPresent(renderer);

        if(score % 10 == 0)
            level++;


        //print_data_on_terminal();
        //print_memory_data();
        take_damage();
        
    }

        //distruggo tutto quello che devo distruggere
    __dispose__();

    
    printf("\n\nRestart? [y/n] ? " );
    fflush(stdin);
    scanf("%c" , &restart);



    if(restart == 'y' || restart == 'Y' || restart == 's' || restart == 'S'){
        system("clear");
        quit = false;
        died = false;
        goto game;
        
    }




    return 0;
}
