//
// Created by oyco on 19/05/23.
//

#include "Game.hpp"

Game::Game(): _player({ 0.0f, 0.0f, 0.0f }), _obstacleSpeed(10.0f), _gameDifficulty(1.0f), _spawnTimer(0.0f)
{
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "YinChillang");
    InitAudioDevice();

    _camera.position = (Vector3){ 0.0f, 50.0f, 100.0f };
    _camera.target = (Vector3){ 15.0f, 0.0f, 15.0f };
    _camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    _camera.fovy = 45.0f;
    _camera.projection = CAMERA_PERSPECTIVE;
    _cameraMovementEnabled = true;

    _playerModel = LoadModel("ressources/goat.glb");
    _playerModel.transform = MatrixMultiply(_playerModel.transform, MatrixRotateX(DEG2RAD * -90));
    _playerModel.transform = MatrixMultiply(_playerModel.transform, MatrixRotateY(DEG2RAD * -65));
    _player.setModel(_playerModel);

    _groundModel = LoadModel("ressources/YinYang.glb");
    _texture1 = LoadTexture("ressources/black-marble.png");
    _texture2 = LoadTexture("ressources/white-marble.png");

    _groundModel.transform = MatrixScale(50.0f, 2.0f, 50.0f);
    _groundBoundingBox = GetMeshBoundingBox(_groundModel.meshes[0]);

    _sceneModel = LoadModel("ressources/room.glb");
    _sceneModel.transform = MatrixMultiply(_sceneModel.transform, MatrixRotateX(DEG2RAD * -90));

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
        _spawnTimer += GetFrameTime();
        if (IsKeyPressed(KEY_ESCAPE))
            break;
    }
}

void Game::update()
{
    _prevMousePosition = _mousePosition;
    _mousePosition = GetMousePosition();

    // Vérifier si la position du joueur est à l'intérieur de la boîte englobante
    //if (CheckCollisionBoxes(_player.getBoundingBox(), _boxTable) && !_debugMode) {
    //}
    if (!_debugMode)
        _player.move();

    if (IsKeyPressed(KEY_P)) {
        if (_debugMode) {
            _debugMode = false;
        } else {
            _debugMode = true;
        }
    }
    _player.update();

    for (auto& obstacle : _obstacles) {
        obstacle.update();
        obstacle.updateColor();

        if (CheckCollisionBoxes(obstacle.getBoundingBox(), _player.getBoundingBox()) && !_debugMode) {
            std::cout << "Collision !" << std::endl;
        }
    }

    if (!_debugMode) {
        float latency = 0.01f;
        _camera.target.x = Lerp(_camera.target.x, _player.getPosition().x, latency);
        _camera.target.y = Lerp(_camera.target.y, _player.getPosition().y + 3.0f, latency);
        _camera.target.z = Lerp(_camera.target.z, _player.getPosition().z, latency);
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        _camera.fovy = 5.0f;
    }
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        _camera.fovy = 45.0f;
    }

    float spawnInterval = GetRandomValue(2000, 5000) / 1000.0f;
    if (_spawnTimer >= spawnInterval) {
        Vector3 spawnPosition = { 51.0f, -3, GetRandomValue(-51, 51) };
        Vector3 spawnSize = { GetRandomValue(1, 5), 10.0f, 100.0f };
        Obstacle newObstacle(spawnPosition, spawnSize, _obstacleSpeed);
        _obstacles.push_back(newObstacle);
        _spawnTimer = 0.0f;
    }
}

void Game::draw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode3D(_camera);
    drawDebug();
    _player.draw();
    for (auto& obstacle : _obstacles) {
        obstacle.draw();
    }
    DrawModel(_groundModel, {0.0f, -3.0f, 0.0f}, 1.0f, WHITE);
    DrawModel(_sceneModel, {0.0f, -10.0f, 5.0f}, 10.0f, WHITE);
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
