/*
** Maxikan, 2023
** YinChillang
** File description:
** Wall
*/

#pragma once

#include "YinChillang.hpp"

class Wall {
    public:
        Wall(Vector3 pos, Vector3 size, float speed);

        void update();
        void draw();
        Vector3 getPosition();
        BoundingBox getBoundingBox();

        void updateColor();

    private:
        Vector3 _pos;
        Vector3 _size;
        float _speed;

        Color _color;
};
