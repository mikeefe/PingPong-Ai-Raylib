#include <stdio.h>
#include "raylib.h"


const int screen_width = 1280, screen_height = 800;

int player_score = 0;
int ai_score = 0;

//Structs
//Ball Movement
typedef struct
{
    int x, y, speedX, speedY;
    float radius;
} Ball;

//Player
typedef struct
{
    int x,y,width,height;
    float speed;
}Paddel;


//Set Var
Ball ball = {screen_width/2, screen_height/2, 10, 10, 15.f};
Paddel player = {10, screen_height/2-60, 25, 120, 6};
Paddel ai = {screen_width - 35, screen_height/2-60, 25, 120, 10};

