//
// Created by oyco on 19/05/23.
//

#include "Game.hpp"

Game::Game(): _player({ 0.0f, 1.5f, 0.0f }), _screenWidth(1280), _screenHeight(720) {
    InitWindow(_screenWidth, _screenHeight, "raylib [core] example - 3d camera mode");

    _camera.position = (Vector3){ 80.0f, 40.0f, 80.0f };
    _camera.target = (Vector3){ 15.0f, 0.0f, 15.0f };
    _camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    _camera.fovy = 45.0f;
    _camera.projection = CAMERA_PERSPECTIVE;
    _cameraMovementEnabled = true;

    _groundModel = LoadModel("ressources/yinyang.glb");
    _texture1 = LoadTexture("ressources/black-marble.png");
    _texture2 = LoadTexture("ressources/white-marble.png");

    _groundModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture2;
    _groundModel.materials[1].maps[MATERIAL_MAP_DIFFUSE].texture = _texture2;
    _groundModel.materials[2].maps[MATERIAL_MAP_DIFFUSE].texture = _texture1;
    _groundModel.transform = MatrixRotateX(DEG2RAD * 90);
    _groundBoundingBox = GetMeshBoundingBox(_groundModel.meshes[0]);

    _sceneModel = LoadModel("ressources/isometric_japanese_room.glb");
    // rescale
    _sceneModel.transform = MatrixScale(10.0f, 300.0f, 10.0f);
    _sceneModel.transform = MatrixMultiply(_sceneModel.transform, MatrixRotateX(DEG2RAD * -90));
    // rotate


    printf("Ground model size: %f, %f, %f\n", _groundBoundingBox.max.x - _groundBoundingBox.min.x,
           _groundBoundingBox.max.y - _groundBoundingBox.min.y, _groundBoundingBox.max.z - _groundBoundingBox.min.z);
    _boxTable = BoundingBox{
            (Vector3){-510.0f, -100.0f, -510.0f},
            (Vector3){510.0f, 2.0f, 510.0f}
    };


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

    // Vérifier si la position du joueur est à l'intérieur de la boîte englobante
    if (CheckCollisionBoxes(_player.getBoundingBox(), _boxTable) && !_debugMode) {
        _player.move();
    }
    if (IsKeyPressed(KEY_P)) {
        _debugMode = !_debugMode;
    }
    _player.update();

    if (IsMouseButtonDown(MOUSE_MIDDLE_BUTTON)) {
        float deltaX = (_mousePosition.x - _prevMousePosition.x) * 0.01f;
        float deltaY = (_mousePosition.y - _prevMousePosition.y) * 0.01f;

        float radius = sqrt(pow(_camera.target.x - _camera.position.x, 2) + pow(_camera.target.z - _camera.position.z, 2));
        float angle = atan2(_camera.target.z - _camera.position.z, _camera.target.x - _camera.position.x) + deltaX;

        _camera.target.x = _camera.position.x + radius * cos(angle);
        _camera.target.z = _camera.position.z + radius * sin(angle);
        _camera.target.y += deltaY;

        _prevMousePosition = _mousePosition;
    }
}

void Game::draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode3D(_camera);
    drawDebug();
    _player.draw();
    DrawModel(_groundModel, {0.0f, -44.0f, 0.0f}, 1.0f, WHITE);
    DrawModel(_sceneModel, {-310.0f, 270.0f, 0.0f}, 1.0f, WHITE);

    EndMode3D();
    DrawFPS(10, 10);
    EndDrawing();
}

void Game::drawDebug() {
    if (!_debugMode)
        return;
    UpdateCamera(&_camera, false);
    DrawGrid(100, 1.0f);
    DrawCubeWires((Vector3){(_boxTable.max.x + _boxTable.min.x) / 2, (_boxTable.max.y + _boxTable.min.y) / 2, (_boxTable.max.z + _boxTable.min.z) / 2},
                  _boxTable.max.x - _boxTable.min.x, _boxTable.max.y - _boxTable.min.y, _boxTable.max.z - _boxTable.min.z, RED);
    DrawCircle3D({0.0f, 0.0f, 0.0f}, 50.0f, {0.0f, 90.0f, 0.0f}, 90.0f, Fade(GREEN, 0.5f));
}