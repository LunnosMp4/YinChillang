//
// Created by oyco on 20/05/23.
//

#include "Obstacle.hpp"

Obstacle::Obstacle(Vector3 pos, Vector3 sz, float spd)
: position(pos), _size(sz), _speed(spd) {}

void Obstacle::update()
{
    position.x -= _speed * GetFrameTime();
}

void Obstacle::draw()
{
    DrawCube(position, _size.x, _size.y, _size.z, _color);
}

BoundingBox Obstacle::getBoundingBox()
{
    return {
        (Vector3){position.x - _size.x / 2, position.y - _size.y / 4, position.z - _size.z / 2},
        (Vector3){position.x + _size.x / 2, position.y + _size.y / 4, position.z + _size.z / 2}
    };
}

void Obstacle::destroy()
{
    delete this;
}

Vector3 Obstacle::getPosition()
{
    return position;
}

void Obstacle::updateColor()
{
    float time = GetTime() * 0.1f;
    float r = (sinf(time * _speed) + 1.0f) * 0.5f;
    float g = (sinf(time * _speed + PI * 2.0f / 3.0f) + 1.0f) * 0.5f;
    float b = (sinf(time * _speed + PI * 4.0f / 3.0f) + 1.0f) * 0.5f;
    _color = { static_cast<unsigned char>(r * 255), static_cast<unsigned char>(g * 255), static_cast<unsigned char>(b * 255), 255 };
}
