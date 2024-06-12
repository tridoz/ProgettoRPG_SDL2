#include<time.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<iostream>
#include<math.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>

SDL_Texture* loadImageTexture(SDL_Renderer *renderer, const char *filename){
    SDL_Surface *surface = IMG_Load(filename);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void set_loading_bar(char *s){
    free(s);
    s = (char*)malloc(sizeof(char) * 2);
    s[0] = '#';
    s[1] = '\0';
}

void display_loading_screen(){
    srand(time(NULL));

    char *s = (char*)malloc(sizeof(char));
    set_loading_bar(s);

    for(int i = 0 ; i<100 ; i++){
        system("clear");
        printf("LOADING TEXTURES        [%s] %d %%\n", s, i);
        usleep( rand()%330000);
        s = (char*)realloc(s, sizeof(char) * (i+3) );
        s[i+2] = '\0';
        s[i+1] = '#';
    }

    set_loading_bar(s);

    for(int i = 0 ; i<100 ; i++){
        system("clear");
        printf("LOADING TEXTURES        [COMPLETE]\n");
        printf("GENERATING TERRAIN      [%s] %d %%\n", s,i);
        usleep( rand()%330000);
        s = (char*)realloc(s, sizeof(char) * (i+3) );
        s[i+2] = '\0';
        s[i+1] = '#';
    }

    set_loading_bar(s);

    for(int i = 0 ; i<100 ; i++){
        system("clear");
        printf("LOADING TEXTURES        [COMPLETE]\n");
        printf("GENERATING TERRAIN      [COMPLETE]\n");
        printf("GENERATING USLESS SHIT  [%s] %d %%\n", s,i);
        usleep( rand()%330000);
        s = (char*)realloc(s, sizeof(char) * (i+3) );
        s[i+2] = '\0';
        s[i+1] = '#';
    }
    
    set_loading_bar(s);

    for(int i = 0 ; i<100 ; i++){
        system("clear");
        printf("LOADING TEXTURES        [COMPLETE]\n");
        printf("GENERATING TERRAIN      [COMPLETE]\n");
        printf("GENERATING USLESS SHIT  [COMPLETE]\n");
        printf("READING YOUR FILES      [%s] %d %%\n", s,i);
        usleep( rand()%330000);
        s = (char*)realloc(s, sizeof(char) * (i+3) );
        s[i+2] = '\0';
        s[i+1] = '#';
    }

    system("clear");
    printf("LOADING TEXTURES        [COMPLETE]\n");
    printf("GENERATING TERRAIN      [COMPLETE]\n");
    printf("GENERATING USLESS SHIT  [COMPLETE]\n");
    printf("READING YOUR FILES      [COMPLETE] (you have some serious staff there bro, is suspicius)\n");
    printf("PRESS A KEY TO PLAY:");
    fflush(stdin);
    getchar();
    fflush(stdin);
    system("clear");
    printf("\n\n\n\n\n\n\n\n\n\t\t\t\t___________                  .__  ____________________  ________ \n");
    printf("\t\t\t\t\\_   _____/__________  _____ |__| \\______   \\______   \\/  _____/ \n");
    printf("\t\t\t\t |    __)/ __ \\_  __ \\/     \\|  |  |       _/|     ___/   \\  __\n");
    printf("\t\t\t\t |     \\  ___/|  | \\/  Y Y  \\  |  |    |   \\|    |   \\    \\_\\  \\\n");
    printf("\t\t\t\t \\___  / \\___  >__|  |__|_|  /__|  |____|_  /|____|    \\______  /\n");
    printf("\t\t\t\t     \\/      \\/            \\/             \\/                  \\/ \n");
    usleep(5000000);

    free(s);

}

void display_death_screen(){
    printf("                               _____.___.________   ____ ___  ________  .______________________                        \n");
    printf("                               \\__  |   |\\_____  \\ |    |   \\ \\______ \\ |   \\_   _____/\\______ \\                       \n");
    printf("                                /   |   | /   |   \\|    |   /  |    |  \\|   ||    __)_  |    |  \\                      \n");
    printf("                                \\____   |/    |    \\    |  /   |    `   \\   ||        \\ |    `   \\                     \n");
    printf("                                / ______|\\_______  /______/   /_______  /___/_______  //_______  /                     \n");
    printf("                                \\/               \\/                   \\/            \\/         \\/                      \n");
    printf("                .__   __              .___                __            _____  ___.                    .___            \n");
    printf("__  _  _______  |  | |  | __ ____   __| _/   ____  __ ___/  |_    _____/ ____\\ \\_ |__   ___________  __| _/___________ \n");
    printf("\\ \\/ \\/ /\\__  \\ |  | |  |/ // __ \\ / __ |   /  _ \\|  |  \\   __\\  /  _ \\   __\\   | __ \\ /  _ \\_  __ \\/ __ |/ __ \\_  __ \\n");
    printf(" \\     /  / __ \\|  |_|    <\\  ___// /_/ |  (  <_> )  |  /|  |   (  <_> )  |     | \\_\\ (  <_> )  | \\/ /_/ \\  ___/|  | \\/\n");
    printf("  \\/\\_/  (____  /____/__|_ \\___  >____ |   \\____/|____/ |__|    \\____/|__|     |___  /\\____/|__|  \\____ |\\___  >__|   \n");
    printf("              \\/          \\/    \\/     \\/                                           \\/                  \\/    \\/       \n");
}

void display_victory_screen(){
    printf("        _________  ________    _______    __________________    ____________________ ___.____       ________________.___________    _______    _________      \n");
    printf("        \\_   ___ \\ \\_____  \\   \\      \\  /  _____/\\______   \\  /  _  \\__    ___/    |   \\   |     /  _  \\__    ___/|   \\_____  \\   \\      \\  /   _____/      \n");
    printf("        /    \\  \\/  /   |   \\  /   |   \\/   \\  ___ |       _/ /  /_\\  \\|    |  |    |   /    |    /  /_\\  \\|    |   |   |/   |   \\  /   |   \\ \\_____  \\       \n");
    printf("        \\     \\____/    |    \\/    |    \\    \\_\\  \\|    |   \\/    |    \\    |  |    |  /|    |___/    |    \\    |   |   /    |    \\/    |    \\/        \\      \n");
    printf("         \\______  /\\_______  /\\____|__  /\\______  /|____|_  /\\____|__  /____|  |______/ |_______ \\____|__  /____|   |___\\_______  /\\____|__  /_______  /      \n");
    printf("                \\/         \\/         \\/        \\/        \\/         \\/                         \\/       \\/                     \\/         \\/        \\/       \n");
    printf("                          .___      _____              __             .___        .__  .__      __  .__               ________ ________  ________    _________\n");
    printf(" ___.__. ____  __ __    __| _/_____/ ____\\____ _____ _/  |_  ____   __| _/ _____  |  | |  |   _/  |_|  |__   ____    /  _____/ \\_____  \\ \\______ \\  /   _____/\n");
    printf("<   |  |/  _ \\|  |  \\  / __ |/ __ \\   __\\/ __ \\\\__  \\   __\\/ __ \\ / __ |  \\__  \\ |  | |  |   \\   __\\  |  \\_/ __ \\  /   \\  ___  /   |   \\ |    |  \\ \\_____  \\ \n");
    printf(" \\___  (  <_> )  |  / / /_/ \\  ___/|  | \\  ___/ / __ \\|  | \\  ___// /_/ |   / __ \\|  |_|  |__  |  | |   Y  \\  ___/  \\    \\_\\  \\/    |    \\|    `   \\/        \\n");
    printf(" / ____|\\____/|____/  \\____ |\\___  >__|  \\___  >____  /__|  \\___  >____ |  (____  /____/____/  |__| |___|  /\\___  >  \\______  /\\_______  /_______  /_______  /\n");
    printf(" \\/                        \\/    \\/          \\/     \\/          \\/     \\/       \\/                       \\/     \\/          \\/         \\/        \\/        \\/ \n");
}