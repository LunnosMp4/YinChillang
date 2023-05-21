/*
** Maxikan, 2023
** YinChillang
** File description:
** Wall
*/

#include "Wall.hpp"

Wall::Wall(Vector3 pos, Vector3 size, float speed)
: _pos(pos), _size(size), _speed(speed) {}

void Wall::update()
{
    Wall::updateColor();
    _pos.x -= _speed * GetFrameTime();
}

void Wall::draw()
{
    DrawCube(_pos, _size.x, _size.y, _size.z, _color);
}

Vector3 Wall::getPosition()
{
    return _pos;
}

BoundingBox Wall::getBoundingBox()
{
    return {
        (Vector3){_pos.x - _size.x / 2, _pos.y - _size.y / 2, _pos.z - _size.z / 2},
        (Vector3){_pos.x + _size.x / 2, _pos.y + _size.y / 2, _pos.z + _size.z / 2}
    };
}

void Wall::updateColor()
{
    float time = GetTime() * 0.1f;
    float r = (sinf(time * _speed) + 1.0f) * 0.5f;
    float g = (sinf(time * _speed + PI * 2.0f / 3.0f) + 1.0f) * 0.5f;
    float b = (sinf(time * _speed + PI * 4.0f / 3.0f) + 1.0f) * 0.5f;
    _color = { static_cast<unsigned char>(r * 255), static_cast<unsigned char>(g * 255), static_cast<unsigned char>(b * 255), 255 };
}