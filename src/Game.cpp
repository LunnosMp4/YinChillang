//
// Created by oyco on 19/05/23.
//

#include "Game.hpp"

Game::Game(): _player({ 0.0f, 1.5f, 0.0f })
{
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(_screenWidth, _screenHeight, "raylib [core] example - 3d camera mode");
    InitAudioDevice();

    _camera.position = (Vector3){ 100.0f, 40.0f, 100.0f };
    _camera.target = (Vector3){ 15.0f, 0.0f, 15.0f };
    _camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    _camera.fovy = 45.0f;
    _camera.projection = CAMERA_PERSPECTIVE;
    _cameraMovementEnabled = true;

    _playerModel = LoadModel("ressources/goat.glb");

    _playerModel.transform = MatrixMultiply(_playerModel.transform, MatrixRotateX(DEG2RAD * -90));

    _groundModel = LoadModel("ressources/YinYang.glb");
    _texture1 = LoadTexture("ressources/black-marble.png");
    _texture2 = LoadTexture("ressources/white-marble.png");

    _groundModel.transform = MatrixScale(50.0f, 2.0f, 50.0f);

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

    _musique = LoadMusicStream("ressources/music-inGame.mp3");
    SetMusicVolume(_musique, 0.3f);

    DisableCursor();
    SetTargetFPS(144);
}

Game::~Game()
{
    UnloadTexture(_texture1);
    UnloadTexture(_texture2);
    UnloadModel(_playerModel);
    UnloadModel(_groundModel);
    UnloadModel(_sceneModel);
    StopMusicStream(_musique);
    UnloadMusicStream(_musique);
    CloseAudioDevice();
    CloseWindow();
}

void Game::run()
{
    PlayMusicStream(_musique);
    while (!WindowShouldClose()) {
        update();
        UpdateMusicStream(_musique);
        draw();
    }
}

void Game::update()
{
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

void Game::draw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode3D(_camera);
    drawDebug();
    _player.draw();
    DrawModel(_playerModel, _player.getPosition(), 0.1f, WHITE);
    DrawModel(_groundModel, {0.0f, -3.0f, 0.0f}, 1.0f, WHITE);
    DrawModel(_sceneModel, {-310.0f, 291.0f, 0.0f}, 1.0f, WHITE);
    EndMode3D();
    DrawFPS(10, 10);
    EndDrawing();
}

void Game::drawDebug()
{
    if (!_debugMode)
        return;
    UpdateCamera(&_camera, false);
    DrawGrid(100, 1.0f);
    DrawCubeWires((Vector3){(_boxTable.max.x + _boxTable.min.x) / 2, (_boxTable.max.y + _boxTable.min.y) / 2, (_boxTable.max.z + _boxTable.min.z) / 2},
                  _boxTable.max.x - _boxTable.min.x, _boxTable.max.y - _boxTable.min.y, _boxTable.max.z - _boxTable.min.z, RED);
    DrawCircle3D({0.0f, 0.0f, 0.0f}, 50.0f, {0.0f, 90.0f, 0.0f}, 90.0f, Fade(GREEN, 0.5f));
}
