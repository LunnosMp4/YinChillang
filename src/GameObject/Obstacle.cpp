//
// Created by oyco on 20/05/23.
//

#include "Obstacle.hpp"

Obstacle::Obstacle()
{
    wall_s._pos = { 100.0f, -3, (float)GetRandomValue(-51, 51) };
    wall_s._size = { (float)GetRandomValue(1, 5), 10.0f, 100.0f };
    wall_s._speed = 50.0f;

    wall_s._spawnIntervalMin = 1.0f;
    wall_s._spawnIntervalMax = 5.0f;
    wall_s._spawnInterval = GetRandomValue(wall_s._spawnIntervalMin, wall_s._spawnIntervalMax);

    wall_s._spawnTimer = 0.0f;

    _obstacleType = 1;
}

void Obstacle::update()
{
    wall_s._spawnTimer += GetFrameTime();
    wall_s._pos = { 100.0f, -3, (float)GetRandomValue(-51, 51) };
    wall_s._size = { (float)GetRandomValue(1, 5), 10.0f, 100.0f };
    wall_s._spawnInterval = GetRandomValue(wall_s._spawnIntervalMin, wall_s._spawnIntervalMax);

    switch (_obstacleType) {
        case 1:
            for (auto& wall : walls)
                wall.update();
            if (wall_s._spawnTimer < wall_s._spawnInterval)
                break;
            Wall newWall(wall_s._pos, wall_s._size, wall_s._speed);
            walls.push_back(newWall);
            wall_s._speed += 5.0f;
            wall_s._spawnTimer = 0.0f;
            break;
    }
}

void Obstacle::draw()
{
    switch (_obstacleType) {
        case 1:
            for (auto& wall : walls)
                wall.draw();
            break;
        default:
            break;
    }
}
