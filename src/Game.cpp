//
// Created by oyco on 19/05/23.
//

#include "Game.hpp"

Game::Game(): _player({ 0.0f, 0.0f, 0.0f }), _obstacleSpeed(20.0f), _spawnTimer(0.0f) {
    /* System */
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "YinChillang");
    ToggleFullscreen();
    InitAudioDevice();
    DisableCursor();
    SetTargetFPS(144);

    /* Camera */
    _camera.position = (Vector3){ 0.0f, 50.0f, 100.0f };
    _camera.target = (Vector3){ 15.0f, 0.0f, 15.0f };
    _camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    _camera.fovy = 45.0f;
    _camera.projection = CAMERA_PERSPECTIVE;

    /* Player */
    _playerModel = LoadModel("ressources/goat.glb");
    _playerModel.transform = MatrixMultiply(_playerModel.transform, MatrixRotateX(DEG2RAD * -90));
    _playerModel.transform = MatrixMultiply(_playerModel.transform, MatrixRotateY(DEG2RAD * -65));
    _player.setModel(_playerModel);

    /* Table */
    _groundModel = LoadModel("ressources/YinYang.glb");
    _texture1 = LoadTexture("ressources/black-marble.png");
    _texture2 = LoadTexture("ressources/white-marble.png");
    _groundModel.transform = MatrixScale(50.0f, 2.0f, 50.0f);
    _groundBoundingBox = GetMeshBoundingBox(_groundModel.meshes[0]);

    /* Scene */
    _sceneModel = LoadModel("ressources/room.glb");
    _sceneModel.transform = MatrixMultiply(_sceneModel.transform, MatrixRotateX(DEG2RAD * -90));

    /* Box of collision */
    _boxTable = BoundingBox{
            (Vector3){-510.0f, -100.0f, -510.0f},
            (Vector3){510.0f, 2.0f, 510.0f}
    };

    _score = 0;

    /* Music */
    _music = LoadMusicStream("ressources/music-inGame.mp3");
    SetMusicVolume(_music, 0.3f);
    _jump_goat = LoadSound("ressources/chevre.mp3");
    SetSoundVolume(_jump_goat, 0.4f);
    _death = LoadSound("ressources/greg.mp3");
    SetSoundVolume(_death, 1.7f);
    _player.greg = _death;
}

Game::~Game()
{
    UnloadTexture(_texture1);
    UnloadTexture(_texture2);
    UnloadModel(_groundModel);
    UnloadModel(_sceneModel);
    UnloadModel(_playerModel);
    StopMusicStream(_music);
    UnloadMusicStream(_music);
    UnloadSound(_jump_goat);
    UnloadSound(_death);
    CloseAudioDevice();
    CloseWindow();
}

void Game::run()
{
    PlayMusicStream(_music);
    while (!WindowShouldClose()) {
        update();
        if (IsKeyPressed(KEY_SPACE) && !_player.isDead()) {
            SetSoundPitch(_jump_goat, randomFloatBetween(1.0f, 0.5f));
            PlaySound(_jump_goat);
        }
        UpdateMusicStream(_music);
        draw();
        _spawnTimer += GetFrameTime();
        if (IsKeyPressed(KEY_ESCAPE))
            break;
        if (_player.isDead() && !_player.isAnimating && IsKeyPressed(KEY_ENTER)) {
            _player.InitPlayer({ 0.0f, 0.0f, 0.0f });
            SetMusicVolume(_music, 0.3f);
            _obstacles.clear();
            _spawnTimer = 0.0f;
            _obstacleSpeed = 20.0f;
            if (_player.isDead())
                _score = 0;
        }
    }
}

void Game::update()
{
    if (IsKeyPressed(KEY_F11)) {
        int display = GetCurrentMonitor();
        if (IsWindowFullscreen()){
            ToggleFullscreen();
            SetWindowSize(1280, 720);
        } else {
            ToggleFullscreen();
            SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display));
        }
    }

    if (!_debugMode && !_player.isDead())
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
        if (obstacle.getPosition().x < -100.0f) {
            _obstacles.erase(_obstacles.begin());
            _score += 1;
            break;
        }
        if (obstacle.isCollideWithPlayer(_player.getBoundingBox()) && !_debugMode) {
            SetMusicVolume(_music, 0.1f);
            _player.setDead(true);
            break;
        }
    }

    if (!_debugMode) {
        float latency = 0.01f;
        if (_player.isDead())
            latency = 1.0f;
        _camera.target.x = Lerp(_camera.target.x, _player.getPosition().x, latency);
        _camera.target.y = Lerp(_camera.target.y, _player.getPosition().y + 3.0f, latency);
        _camera.target.z = Lerp(_camera.target.z, _player.getPosition().z, latency);
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        _camera.fovy = 5.0f;
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        _camera.fovy = 45.0f;

    float spawnInterval = GetRandomValue(2000, 5000) / 1000.0f;
    if (_spawnTimer >= spawnInterval) {
        Vector3 spawnPosition = { 100.0f, 5, static_cast<float>(GetRandomValue(-51, 51)) };
        Obstacle newObstacle(spawnPosition, _obstacleSpeed);
        _obstacleSpeed += 2.0f;
        newObstacle.type = static_cast<ObstacleType>(GetRandomValue(0, 1));
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
        if (obstacle.type == CIRCLE)
            obstacle.drawCircle();
        else if (obstacle.type == WALL)
            obstacle.drawWall();
    }

    DrawModel(_groundModel, {0.0f, -2.0f, 0.0f}, 1.0f, WHITE);
    DrawModel(_sceneModel, {0.0f, -10.0f, 5.0f}, 10.0f, WHITE);

    EndMode3D();
    DrawFPS(10, 10);
    DrawText(TextFormat("Score: %d", _score), GetScreenWidth() / 2 - MeasureText(TextFormat("Score: %d", _score), 50) / 2, 10, 50, (Color){(unsigned char)(sin(GetTime() * 2.0f) * 127.0f + 127.0f), (unsigned char)(sin(GetTime() * 2.0f + 2.0f) * 127.0f + 127.0f), (unsigned char)(sin(GetTime() * 2.0f + 4.0f) * 127.0f + 127.0f), 255});
    
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
