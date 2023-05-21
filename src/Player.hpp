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

        void InitPlayer(Vector3 position);
        void update();
        void draw();
        void move();
        void animate();
        void setModel(Model model) { _playerModel = model; }
        void setPosition(Vector3 position) { _position = position; }
        Vector3 getPosition() { return _position; }
        BoundingBox getBoundingBox() { return _boundingPlayer; }
        void setDead(bool dead);
        bool isDead() { return _isDead; }

    public:
        bool isAnimating;
        Sound greg;

    private:
        Model _playerModel;
        Vector3 _position{};
        Vector3 _shadowPosition{};
        float _shadowScale;
        Vector3 _velocity{};
        float _jumpHeight;
        float _gravity;
        bool _isGrounded;
        float _speed;
        bool _isDead;
        BoundingBox _boundingPlayer{};
        Vector3 _startPosition;
        Vector3 _targetPosition;
        float _animationDuration;
        float _animationTimeElapsed;
        bool _isAnimationTriggered;
        float _waitDuration;
        float _waitTimeElapsed;
        bool _isWaiting;
        bool _isRotating;
};
