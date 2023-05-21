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
        void setModel(Model model) { _playerModel = model; }
        Vector3 getPosition() { return _position; }
        BoundingBox getBoundingBox() { return _boundingPlayer; }
        void setDead(bool dead) { _isDead = dead; }
        bool isDead() { return _isDead; }

    private:
        Model _playerModel;
        Vector3 _position{};
        Vector3 _shadowPosition{};
        Vector3 _velocity{};
        float _jumpHeight;
        float _gravity;
        bool _isGrounded;
        float _speed;
        bool _isDead;
        BoundingBox _boundingPlayer{};
};
