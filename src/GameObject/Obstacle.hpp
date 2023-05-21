//
// Created by oyco on 20/05/23.
//

#pragma once

#include "YinChillang.hpp"

class Obstacle {
    public:
        Obstacle(Vector3 pos, Vector3 sz, float spd)
                : position(pos), size(sz), speed(spd) {}

        void update() {
            position.x -= speed * GetFrameTime();
        }

        void draw() {
            DrawCube(position, size.x, size.y, size.z, RED);
        }

        BoundingBox getBoundingBox() {
            return {
                    (Vector3){position.x - size.x / 2, position.y - size.y / 4, position.z - size.z / 2},
                    (Vector3){position.x + size.x / 2, position.y + size.y / 4, position.z + size.z / 2}
            };
        }

        void destroy() {
            delete this;
        }

        Vector3 getPosition() {
            return position;
        }

    private:
        Vector3 position;
        Vector3 size;
        float speed;
};