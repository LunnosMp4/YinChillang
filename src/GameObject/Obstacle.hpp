//
// Created by oyco on 20/05/23.
//

#pragma once

#include "YinChillang.hpp"

class Obstacle {
    public:
        Obstacle();

        void update();
        void draw();

        std::vector<Wall> walls;
    private:
        struct WallSettings {
            Vector3 _pos;
            Vector3 _size;
            float _speed;

            float _spawnIntervalMin;
            float _spawnIntervalMax;
            float _spawnInterval;

            float _spawnTimer;
        };

        WallSettings wall_s;

        int _obstacleType;
};