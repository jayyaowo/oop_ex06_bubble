#include "raylib.h"
#include <iostream>
#include <vector>

const float RADIUS_TABLE[] = { 10.0f, 20.0f, 30.0f, 40.0f };    // 半徑：小、中、大
const Color COLOR_TABLE[]  = { RED, BLACK, GREEN, BLUE };       // 顏色
const int SCORE_TABLE[]    = { 50, 0, 30, 10 };

class bubble{
    private:
        Vector2 position;
        Vector2 speed;
        float radius;
        Color color;
        int scoreValue;
        bool exists;
    public:
        bubble(float x, float y, int level)
        {
            position = {x, y};
            exists = true;

            radius = RADIUS_TABLE[level];
            color = COLOR_TABLE[level];
            scoreValue = SCORE_TABLE[level];

            float speedWeight = (float)(5 - level) / 3.0f;   // 小泡泡移動較快
            speed.x = (float)(GetRandomValue(-100, 100)) / 100.0f;
            speed.y = (float)(GetRandomValue(-300, 100)) / 100.0f * speedWeight;
        }
        int getScoreValue() { return scoreValue; }

        void update()
        {
            position.x += speed.x;
            position.y += speed.y;

            if(position.y + radius < 0) {exists = false;}
        }
        
        void draw()
        {
            if(exists)
                DrawCircleV(position, radius, color);
        }

        bool isExist() {return exists;}

        bool isClicked(Vector2 mousePoint) 
        {
            return exists && 
                CheckCollisionPointCircle(mousePoint, position, radius);
        }

        void Deactivate() { exists = false; }
};


int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "BUBBLE GAME");
    std::vector<bubble> bubbles;
    float spawnTimer = 0.0f;
    float difficultyTimer = 0.0f;
    int score = 0;

    SetTargetFPS(60);

    while (!WindowShouldClose()) 
    {
        float deltaTime = GetFrameTime();
        difficultyTimer += deltaTime;
        
        //生成氣泡
        spawnTimer += deltaTime;
        if(spawnTimer >= 0.5f)
        {
            float x = (float)GetRandomValue(0, screenWidth);
            float y = (float)screenHeight + 50.0f; // 從畫面下方生成
            //----黑球生成機率隨時間增加----
            int blackChance = (int)(difficultyTimer / 10.0f);
            if(blackChance > 30) blackChance = 30;

            int level;
            if(GetRandomValue(0, 100) < blackChance)
            {
                level = 1; // 黑球
            }
            else
            {
                int other[] = {0, 2, 3}; // 紅 綠 藍 球
                level = other[GetRandomValue(0, 2)];
            }
            bubbles.emplace_back(x, y, level);
            spawnTimer = 0.0f;
        }
        //滑鼠點擊
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Vector2 mousePoint = GetMousePosition();
            for(int i = bubbles.size() - 1; i >= 0; i--)
            {
                if(bubbles[i].isClicked(mousePoint)) // 點到氣泡
                {
                    if(bubbles[i].getScoreValue() == 0)
                        score = 0; // 點到黑球分數歸零
                    else
                        score += bubbles[i].getScoreValue();
                    
                    bubbles[i].Deactivate();    
                    break; 
                }
                
            }
        }
        
        //更新氣泡
        for(int i = 0; i < bubbles.size(); i++)
        {
            bubbles[i].update();
        }
        
        //繪製
        BeginDrawing();
        ClearBackground(RAYWHITE);
        for(int i = 0; i < bubbles.size(); i++)
        {
            bubbles[i].draw();
        }
        //顯示分數
        DrawText(TextFormat("SCORE: %d", score), 20, 20, 30, DARKGRAY);
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
