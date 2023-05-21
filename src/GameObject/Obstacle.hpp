//
// Created by oyco on 20/05/23.
//

#pragma once

#include "YinChillang.hpp"

enum ObstacleType {
    CIRCLE = 0,
    WALL = 1
};

class Obstacle {
    public:
        Obstacle(Vector3 pos, float spd);

        void drawCircle();
        void drawWall();

        bool isCollideWithPlayer(BoundingBox player);
        Vector3 getPosition();

        void update();
        void updateColor();
        ObstacleType type;

    private:
        Color _color;
        Vector3 _position;
        float _speed;
        float _radius;
        float _random_effect_color;
        int _nbCubes;
        std::vector<BoundingBox> _boundingBoxes;
};