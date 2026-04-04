#include <raylib.h>
#include <raymath.h>
#include <iostream>

const int screenWidth = 1000;
const int screenHeight = 800;

void monitor() { SetWindowMonitor(0); };
float getMag(Vector2 v) { return Vector2Length(v); };
Vector2 getNorm(Vector2 v) { return Vector2Normalize(v); };

Vector2 getDiff(Vector2 v1, Vector2 v2)
{
    Vector2 diff = Vector2Subtract(v1, v2);
    return diff;
};

class NPC 
{
    public:
        Vector2 position = {(float)screenWidth/2, (float)screenHeight/2};
        float size = 10.0f;
        float velocity = 100.0f;
        Color color = GREEN;

        // testing y first 
        Vector2 otherPosition = {900, (float)screenHeight/2};
        float otherSize = 50.0f;
        Color otherColor = RED;

        void Draw() 
        { 
            DrawCircleV(otherPosition, otherSize, otherColor); 
            DrawCircleV(position, size, color); 
        }

        void Update(Vector2 norm, float dt) 
        {
            // if(IsKeyDown(KEY_W)) position.y -= norm.y * velocity * dt; 
            // if(IsKeyDown(KEY_S)) position.y += norm.y * velocity * dt; 
            // if(IsKeyDown(KEY_A)) position.x -= norm.x * velocity * dt; 
            // if(IsKeyDown(KEY_D)) position.x += norm.x * velocity * dt; 

            Vector2 theDiff = getDiff(position, otherPosition);
            float theMag = getMag(theDiff);
            Vector2 theDirection = {theDiff.x / theMag, theDiff.y / theMag};
            // std::cout << "theDirection [0]: " << theDirection.x << '\n'; 
            // std::cout << "theDirection [1]: " << theDirection.y << '\n'; 
            
            // need to find a better way 
            // but it works WOOOOO
            Vector2MoveTowards(position, otherPosition, 1000);
            if(position.y < otherPosition.y) { position.y += norm.y * velocity * dt; }
            if(position.y > otherPosition.y) { position.y -= norm.y * velocity * dt; }
            if(position.x < otherPosition.x) { position.x += norm.x * velocity * dt; }
            if(position.x > otherPosition.x) { position.x -= norm.x * velocity * dt; }
        }
};

class Ux 
{
    public:
        void Draw(Vector2 norm, float mag) 
        {
            DrawRectangle(10, 10, 250, 120, Fade(SKYBLUE, 0.5f));
            DrawRectangleLines(10, 10, 250, 120, BLUE);

            DrawText("DEBUG INFO: ", 15, 15, 20, PINK);
            DrawFPS(900, 15);
            DrawText(TextFormat("MAG: %f", mag), 15, 50, 20, WHITE);
            DrawText(TextFormat("NORM [0]: %f", norm.x), 15, 70, 20, WHITE);
            DrawText(TextFormat("NORM [1]: %f", norm.y), 15, 90, 20, WHITE);
        };
};

int main() 
{
    InitWindow(screenWidth, screenHeight, "Hello World!\n");
    NPC npc;
    Ux ui;
    monitor();

    SetTargetFPS(144);
    while(!WindowShouldClose()) 
    {
        float dt = GetFrameTime();
        Vector2 norm = getNorm(npc.position);
        float mag = getMag(npc.position);

        BeginDrawing();
        {
            ClearBackground(BLACK);
            npc.Draw();
            npc.Update(norm, dt);
        }
        EndDrawing();
        ui.Draw(norm, mag);
    }
    CloseWindow();

    return 0;
}
