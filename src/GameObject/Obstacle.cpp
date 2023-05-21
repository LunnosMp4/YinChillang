//
// Created by oyco on 20/05/23.
//

#include "Obstacle.hpp"

Obstacle::Obstacle(Vector3 pos, float spd) : _position(pos), _speed(spd) {
    _radius = GetRandomValue(10, 30);
    _nbCubes = _radius * 3;
    _random_effect_color = GetRandomValue(0, 4.0);

    /* Remplie la liste de bounding boxes à 0 */
    for (int i = 0; i < _nbCubes; i++)
        _boundingBoxes.push_back({(Vector3) {0, 0, 0}, (Vector3) {0, 0, 0}});
}


/* UPDATE */
void Obstacle::updateColor()
{
    float time = GetTime() * 0.1f;
    float r = (sinf(time * _speed) + 1.0f) * 0.5f;
    float g = (sinf(time * _speed + PI * 2.0f / 3.0f) + 1.0f) * 0.5f;
    float b = (sinf(time * _speed + PI * 4.0f / 3.0f) + 1.0f) * 0.5f;

    _color = { static_cast<unsigned char>(r * 255), static_cast<unsigned char>(g * 255), static_cast<unsigned char>(b * 255), 255 };
}

void Obstacle::update()
{
    _position.x -= _speed * GetFrameTime();
}

/* DRAW */
void Obstacle::drawCircle()
{
    const int numSegments = _nbCubes;
    const float angleIncrement = (2.0f * PI) / numSegments;

    for (int i = 0; i < numSegments; ++i) {
        const float angle = angleIncrement * i;
        const float x1 = _radius * cosf(angle);
        const float y1 = _radius * sinf(angle);
        Vector3 position = {_position.x + y1, _position.y - 4.5f, _position.z + x1};

        DrawCube(position, 1.0f, 1.0f, 1.0f, {static_cast<unsigned char>(_color.r + _random_effect_color * i), static_cast<unsigned char>(_color.g + _random_effect_color * i), static_cast<unsigned char>(_color.b + _random_effect_color * i), _color.a});
        _boundingBoxes[i] = {
                position,
                position
        };
    }
}

void Obstacle::drawWall() {
    int count = 0;

    for (int i = _nbCubes; i > 0; i--) {
        Vector3 position = {_position.x, _position.y - 2, (_position.z - _nbCubes) + 2 * i};
        DrawCube(position, 1.0f, 1.0f, 1.0f,
                 {static_cast<unsigned char>(_color.r + _random_effect_color * i), static_cast<unsigned char>(_color.g + _random_effect_color * i),
                  static_cast<unsigned char>(_color.b + _random_effect_color * i), _color.a});
        _boundingBoxes[count++] = {{position.x + 0.5f, position.y - 2.0f, position.z - 0.5f},
                                   {position.x + 0.5f, position.y - 0.5f, position.z + 0.5f}};
    }
}

/* UTILS */
bool Obstacle::isCollideWithPlayer(BoundingBox player)
{
    for (std::vector<BoundingBox>::size_type i = 0; i < _boundingBoxes.size(); i++) {
        if (CheckCollisionBoxes(player, _boundingBoxes[i]))
            return true;
    }
    return false;
}

Vector3 Obstacle::getPosition()
{
    return _position;
}