#include <raylib.h>
#include <raymath.h>
#include <iostream>

const int screenWidth = 1000;
const int screenHeight = 800;

// working on getting a image to be loaded
// need to find out Unload Image Problem needs a type seems to be a funciton call not type
// Have to use 
// DrawTexture() for drawling instead of
// DrawShape() 

void monitor() { SetWindowMonitor(0); };
Vector2 getNorm(Vector2 v) { return Vector2Normalize(v); };

class NPC 
{
public:
    // bad guy
    Image image = LoadImage("resources/redbug.png");
    Texture2D texture = LoadTextureFromImage(image);
    UnloadImage(image); // might need to make a copy constructor and deconsturctor for this.
    Vector2 position = { (float)screenWidth/2, (float)screenHeight/2 };
    Vector2 resetPos = position;
    float size = 10.0f;
    float velocity = 100.0f;
    Color color = BLACK;
    int damage = 1;

    // good guy
    Image otherImage = LoadImage("resources/exterminator.png");
    Texture2D otherTexture = LoadTextureFromImage(otherImage);
    UnloadImage(otherImage); // might need to make a copy constructor and deconsturctor for this.
    Vector2 otherPosition = { 900, (float)screenHeight/2 };
    Vector2 resetOtherPos = otherPosition;
    float otherSize = 50.0f;
    Color otherColor = RED;
    int otherHealth = 100;
    int resetOtherHealth = otherHealth;

    void Draw() 
    { 
        DrawTexture(image, position.x, position.y, color);
        DrawCircleV(otherPosition, otherSize, otherColor); 
        DrawCircleV(position, size, color); 
    }

    void Update(Vector2 norm, float dt) 
    {
        Vector2MoveTowards(position, otherPosition, 1000);

        // npc movement
        if(position.y < otherPosition.y) position.y += norm.y * velocity * dt;
        if(position.y > otherPosition.y) position.y -= norm.y * velocity * dt;
        if(position.x < otherPosition.x) position.x += norm.x * velocity * dt;
        if(position.x > otherPosition.x) position.x -= norm.x * velocity * dt;

        //player movement
        if(IsKeyDown(KEY_A)) otherPosition.x -= otherPosition.x * dt;
        if(IsKeyDown(KEY_D)) otherPosition.x += otherPosition.x * dt;
        if(IsKeyDown(KEY_W)) otherPosition.y -= otherPosition.y * dt;
        if(IsKeyDown(KEY_S)) otherPosition.y += otherPosition.y * dt;
    }

    void checkCollision() 
    {
        // Area Limits 
        if((otherPosition.x + otherSize) >= GetScreenWidth()) otherPosition.x = GetScreenWidth() - otherSize;
        else if (otherPosition.x <= 0) otherPosition.x = 0;

        if((otherPosition.y + otherSize) >= GetScreenHeight()) otherPosition.y = GetScreenHeight() - otherSize;
        else if (otherPosition.y <= 0) otherPosition.y = 0;

        // okay check if are touching
        bool areTouching = CheckCollisionCircles(position, size, otherPosition, otherSize);
        if(areTouching) 
        {
            otherHealth = otherHealth - damage;
            std::cout << "Health: " << otherHealth << '\n'; 
            areTouching = false;

            // reset on death 
            if(otherHealth <= 0 )
            {
                std::cout << "You are Dead!\n";
                position = resetPos;
                otherPosition = resetOtherPos;
                otherHealth = resetOtherHealth;
            }
        }
    }
};

class Ux 
{
public:
    void Draw(Vector2 norm) 
    {
        DrawRectangle(10, 10, 250, 120, Fade(SKYBLUE, 0.5f));
        DrawRectangleLines(10, 10, 250, 120, BLUE);

        DrawText("DEBUG INFO: ", 15, 15, 20, PINK);
        DrawFPS(900, 15);
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

        BeginDrawing();
        {
            ClearBackground(BLACK);
            npc.Draw();
            npc.Update(norm, dt);
            npc.checkCollision();
        }
        EndDrawing();
        ui.Draw(norm);
    }
    UnloadTexture(npc.texture);
    UnloadTexture(npc.otherTexture);
    CloseWindow();

    return 0;
}
