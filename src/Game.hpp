//
// Created by oyco on 19/05/23.
//

#pragma once

#include "YinChillang.hpp"
#include "GameObject/Obstacle.hpp"

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
        Camera3D _camera;

        std::vector<Obstacle> _obstacles;
        float _obstacleSpeed;
        float _spawnTimer;

        Model _playerModel;
        Model _groundModel;
        Model _sceneModel;

        Texture2D _texture1;
        Texture2D _texture2;

        BoundingBox _boxTable;
        BoundingBox _groundBoundingBox;

        Music _music;
        Sound _jump_goat;
        Sound _death;
};
