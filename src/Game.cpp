//
// Created by oyco on 19/05/23.
//

#include "Game.hpp"

Game::Game(): _player({ 0.0f, 0.0f, 0.0f }), _screenWidth(1280), _screenHeight(720) {
    InitWindow(_screenWidth, _screenHeight, "raylib [core] example - 3d camera mode");

    _camera.position = (Vector3){ 0.0f, 40.0f, 40.0f };
    _camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
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
    _player.update();
    _player.move();

    // Vérifier si la position du joueur est à l'intérieur de la boîte englobante
//    if (CheckCollisionBoxes(_player.getBoundingBox(), _boxTable)) {
//        _player.setPosition(_player.getPreviousPosition());
//    }


    BoundingBox cameraBox = { (Vector3){ _camera.position.x - 0.5f, _camera.position.y - 1.0f, _camera.position.z - 0.5f },
                              (Vector3){ _camera.position.x + 0.5f, _camera.position.y + 1.0f, _camera.position.z + 0.5f } };

    if (CheckCollisionBoxes(cameraBox, _boxTable)) {
        _cameraMovementEnabled = false;
        _camera.position.y += 0.1f;
    } else
        _cameraMovementEnabled = true;

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && _cameraMovementEnabled)
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
}

void Game::draw() {
    BeginMode3D(_camera);
    BeginDrawing();
    _player.draw();
    DrawModel(_groundModel, {0.0f, -44.0f, 0.0f}, 1.0f, WHITE);

    EndMode3D();

    if (_mousePosition.x > 0 && _mousePosition.x < _screenWidth && _mousePosition.y > 0 && _mousePosition.y < _screenHeight)
            DrawCircle(_mousePosition.x, _mousePosition.y, 10, RED);

    DrawFPS(10, 10);
    EndDrawing();
}
