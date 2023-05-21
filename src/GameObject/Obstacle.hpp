//
// Created by oyco on 20/05/23.
//

#pragma once

#include "YinChillang.hpp"

class Obstacle {
    public:
        Obstacle(Vector3 pos, Vector3 sz, float spd);

        void update();
        void draw();
        BoundingBox getBoundingBox();
        void destroy();
        Vector3 getPosition();
        void updateColor();

    private:
        Color _color;
        Vector3 position;
        Vector3 _size;
        float _speed;
};