#include <iostream>
#include <cmath>
#include "raylib.h"

int main(void)
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera mode");

    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Vector2 mousePosition = { 0 };
    Vector2 prevMousePosition = { 0 };

    Model groundModel = LoadModel("ressources/yinyang.obj");
    Texture2D texture1 = LoadTexture("ressources/black-marble.png");
    Texture2D texture2 = LoadTexture("ressources/white-marble.png");

    groundModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture1;
    groundModel.materials[0].maps[MATERIAL_MAP_NORMAL].texture = texture2;

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

    SetTargetFPS(144);

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        prevMousePosition = mousePosition;
        mousePosition = GetMousePosition();

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            float deltaX = (mousePosition.x - prevMousePosition.x) * 0.01f;

            float radius = sqrt(pow(camera.position.x, 2) + pow(camera.position.z, 2));
            float angle = atan2(camera.position.z, camera.position.x) + deltaX;

            camera.position.x = radius * cos(angle);
            camera.position.z = radius * sin(angle);
        }

        if (IsMouseButtonDown(MOUSE_MIDDLE_BUTTON))
        {
            float deltaX = (mousePosition.x - prevMousePosition.x) * 0.01f;
            float deltaY = (mousePosition.y - prevMousePosition.y) * 0.01f;

            float radius = sqrt(pow(camera.target.x - camera.position.x, 2) + pow(camera.target.z - camera.position.z, 2));
            float angle = atan2(camera.target.z - camera.position.z, camera.target.x - camera.position.x) + deltaX;

            camera.target.x = camera.position.x + radius * cos(angle);
            camera.target.z = camera.position.z + radius * sin(angle);
            camera.target.y += deltaY;

            prevMousePosition = mousePosition;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(camera);

        // Draw the ground model
        DrawModel(groundModel, {0.0f, -100.0f, 0.0f}, 1.0f, WHITE);

        DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
        DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);

        EndMode3D();
        DrawFPS(10, 10);
        EndDrawing();
    }

    UnloadModel(groundModel);
    UnloadTexture(texture1);
    UnloadTexture(texture2);
    CloseWindow();

    return 0;
}
