//
// Created by oyco on 19/05/23.
//

#include "Game.hpp"

Game::Game() {
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera mode");

    _camera.position = (Vector3){ 0.0f, 40.0f, 40.0f };
    _camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    _camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    _camera.fovy = 45.0f;
    _camera.projection = CAMERA_PERSPECTIVE;

    Vector2 mousePosition = { 0 };
    Vector2 prevMousePosition = { 0 };

    _groundModel = LoadModel("ressources/yinyang.glb");
    _texture1 = LoadTexture("ressources/black-marble.png");
    _texture2 = LoadTexture("ressources/white-marble.png");

    _groundModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture2;
    _groundModel.materials[1].maps[MATERIAL_MAP_DIFFUSE].texture = _texture2;
    _groundModel.materials[2].maps[MATERIAL_MAP_DIFFUSE].texture = _texture1;

    _groundModel.transform = MatrixRotateX(DEG2RAD * 90);

    _cubePosition = { 0.0f, 0.0f, 0.0f };

    DisableCursor();
    SetTargetFPS(144);
}

Game::~Game() {
    UnloadTexture(_texture1);
    UnloadTexture(_texture2);
    UnloadModel(_groundModel);
    CloseWindow();
}

void Game::run() {
    while (!WindowShouldClose()) {
        update();
        draw();
    }
}

void Game::update() {
    _prevMousePosition = _mousePosition;
    _mousePosition = GetMousePosition();

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        UpdateCamera(&_camera, CAMERA_THIRD_PERSON);

    if (IsMouseButtonDown(MOUSE_MIDDLE_BUTTON))
    {
        float deltaX = (_mousePosition.x - _prevMousePosition.x) * 0.01f;
        float deltaY = (_mousePosition.y - _prevMousePosition.y) * 0.01f;

        float radius = sqrt(pow(_camera.target.x - _camera.position.x, 2) + pow(_camera.target.z - _camera.position.z, 2));
        float angle = atan2(_camera.target.z - _camera.position.z, _camera.target.x - _camera.position.x) + deltaX;

        _camera.target.x = _camera.position.x + radius * cos(angle);
        _camera.target.z = _camera.position.z + radius * sin(angle);
        _camera.target.y += deltaY;

        _prevMousePosition = _mousePosition;
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode3D(_camera);
}

void Game::draw() {
    DrawModel(_groundModel, {0.0f, -44.0f, 0.0f}, 1.0f, WHITE);

    DrawCube(_cubePosition, 2.0f, 2.0f, 2.0f, RED);
    DrawCubeWires(_cubePosition, 2.0f, 2.0f, 2.0f, MAROON);

    EndMode3D();
    DrawFPS(10, 10);
    EndDrawing();
}
