//
// Created by oyco on 19/05/23.
//

#pragma once

#include "YinChillang.hpp"

class Enemy {
    // Définissez les propriétés et les méthodes spécifiques à l'ennemi
};

class Level {
    // Définissez les propriétés et les méthodes pour gérer les niveaux du jeu
};

class Game
{
    public:
        Game();
        ~Game();

        void run();
        void update();
        void draw();
        void drawDebug();
        Camera3D getCamera() const { return _camera; };
        Model getPlayerModel() const { return _playerModel; };

    private:
        bool _debugMode = false;
        Player _player;
        Enemy _enemy;
        Level _level;
        bool _cameraMovementEnabled;
        Camera3D _camera;
        Vector2 _mousePosition;
        Vector2 _prevMousePosition;
        Model _playerModel;
        Model _groundModel;
        Model _sceneModel;
        Texture2D _texture1;
        Texture2D _texture2;
        BoundingBox _boxTable;
        BoundingBox _groundBoundingBox;
        Music _music;
        Sound _jump_chevre;
        Sound _jump_chevre_hard;
        std::vector<Obstacle> _obstacles;
        float _obstacleSpeed;
        float _gameDifficulty;
        float _spawnTimer;
};
