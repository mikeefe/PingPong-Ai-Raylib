#include "var.h"

void ResetBall()
{
    ball.x = GetScreenWidth()/2;
    ball.y = GetScreenHeight()/2;

    int speedRand[] = {-1,1};
    ball.speedX *= speedRand[GetRandomValue(0,1)];
    ball.speedY *= speedRand[GetRandomValue(0,1)];

}

void PlayerLogic()
{
    //Movement Player
    if(IsKeyDown(KEY_UP))
    {
        player.y = player.y - player.speed;
    }
    if(IsKeyDown(KEY_DOWN))
    {
        player.y = player.y + player.speed;
    }

    //Player World Limit
    if(player.y <=0)
    {
        player.y = 0;
    }
    if(player.y + player.height >= GetScreenHeight())
    {
        player.y = GetScreenHeight() - player.height;
    }
}

void AiLogic(int ball_y)
{
    //Ai Movement
    if(ai.y + ai.height/2 > ball_y)
    {
        ai.y = ai.y - ai.speed;
    }
    if(ai.y + ai.height/2 <= ball_y)
    {
        ai.y = ai.y + ai.speed;
    }

    //Ai Limit
    if(ai.y <=0)
    {
        ai.y = 0;
    }
    if(ai.y + ai.height >= GetScreenHeight())
    {
        ai.y = GetScreenHeight() - ai.height;
    }
}

void Collision()
{
    Vector2 ballPosition = (Vector2){ball.x,ball.y};
    Rectangle recPlayer = (Rectangle){player.x, player.y, player.width, player.height};
    Rectangle recAi = (Rectangle){ai.x, ai.y, ai.width, ai.height};


    if(CheckCollisionCircleRec(ballPosition, ball.radius, recPlayer))
    {
        ball.speedX *= -1;
    }if(CheckCollisionCircleRec(ballPosition, ball.radius, recAi))
    {
        ball.speedX *= -1;
    }
}

void Draw()
{
    DrawLine(screen_width/2, 0, screen_width/2, screen_height, WHITE);

    //Ball
    DrawCircle(ball.x, ball.y, ball.radius, WHITE);

    //Player
    DrawRectangle(player.x, player.y, player.width, player.height, WHITE);

    //Ai
    DrawRectangle(ai.x, ai.y, ai.width, ai.height, WHITE);
}

void UpdateWorld()
{
    //Movement BALL
    ball.x += ball.speedX;
    ball.y += ball.speedY;

    //Collision Top and Bottom
    if((float)ball.y + ball.radius >= (float)GetScreenHeight() || (float)ball.y - ball.radius <= 0)
    {
        ball.speedY *= -1;
    }

    //Score
    if((float)ball.x + ball.radius >= (float)GetScreenWidth())
    {
        ai_score++;
        ResetBall();
    }
    if((float)ball.x - ball.radius <= 0)
    {
        player_score++;
        ResetBall();
    }
}


int main(void)
{

    InitWindow(screen_width, screen_height, "My game !");
    SetTargetFPS(60);


    while (WindowShouldClose() == false)
    {
        BeginDrawing();


        PlayerLogic();
        AiLogic(ball.y);
        Collision();
        UpdateWorld();

        Draw();
        DrawText(TextFormat("%i",ai_score), screen_width/4-20, 20, 80, WHITE);
        DrawText(TextFormat("%i",player_score), 3 * screen_width/4-20, 20, 80, WHITE);

        ClearBackground(BLACK);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

