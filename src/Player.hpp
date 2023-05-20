//
// Created by oyco on 20/05/23.
//

#pragma once

#include "YinChillang.hpp"

class Player: public GameObject
{
    public:
        explicit Player(Vector3 position);
        ~Player();
        void update();
        void draw();
        void move();
        void setModel(Model model) { _modelPlayer = model; }
        Vector3 getPosition() { return _position; }
        BoundingBox getBoundingBox() { return _boundingPlayer; }

    private:
        Model _modelPlayer;
        Vector3 _position{};
        Vector3 _shadowPosition{};
        Vector3 _velocity{};
        float _jumpHeight;
        float _gravity;
        bool _isGrounded;
        float _speed;
        BoundingBox _boundingPlayer{};
};
