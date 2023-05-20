//
// Created by oyco on 20/05/23.
//

#include "Player.hpp"

Player::Player(Vector3 position)
{
    _position = position;
    _boundingPlayer = { { position.x - 2.5f, position.y - 2.5f, position.z - 2.5f }, { position.x + 2.5f, position.y + 2.5f, position.z + 2.5f } };
    _velocity = { 0.0f, 0.0f, 0.0f };
    _jumpHeight = 26.0f;
    _gravity = 60.0f;
    _isGrounded = true;
    _speed = 20.0f;
}

Player::~Player() = default;

void Player::move()
{
    if (IsKeyDown(KEY_W)) { // Avancer
        _position.z -= _speed * GetFrameTime();
        _boundingPlayer.min.z -= _speed * GetFrameTime();
        _boundingPlayer.max.z -= _speed * GetFrameTime();
    }
    if (IsKeyDown(KEY_S)) { // Reculer
        _position.z += _speed * GetFrameTime();
        _boundingPlayer.min.z += _speed * GetFrameTime();
        _boundingPlayer.max.z += _speed * GetFrameTime();
    }
    if (IsKeyDown(KEY_A)) { // Gauche
        _position.x -= _speed * GetFrameTime();
        _boundingPlayer.min.x -= _speed * GetFrameTime();
        _boundingPlayer.max.x -= _speed * GetFrameTime();
    }
    if (IsKeyDown(KEY_D)) { // Droite
        _position.x += _speed * GetFrameTime();
        _boundingPlayer.min.x += _speed * GetFrameTime();
        _boundingPlayer.max.x += _speed * GetFrameTime();
    }
}

void Player::update()
{
    // Handle jumping
    if (IsKeyPressed(KEY_SPACE) && _isGrounded) {
        _velocity.y = _jumpHeight;
        _isGrounded = false;
    }

    // Apply gravity
    if (!_isGrounded) {
        _velocity.y -= _gravity * GetFrameTime();
    }

    // Update player position and bounding box based on velocity
    _position.y += _velocity.y * GetFrameTime();
    _boundingPlayer.min.y += _velocity.y * GetFrameTime();
    _boundingPlayer.max.y += _velocity.y * GetFrameTime();

    // Check if the player has reached the ground
    if (_position.y <= 1.5f) {
        _position.y = 1.5f;
        _velocity.y = 0.0f;
        _isGrounded = true;
    }

    _shadowPosition = { _position.x, -1.0f, _position.z };
}

void Player::draw()
{
    DrawCube(_position, 5.0f, 5.0f, 5.0f, RED);
    DrawCubeWires(_position, 5.0f, 5.0f, 5.0f, MAROON);
    DrawCube(_shadowPosition, 5.0f, 0.1f, 5.0f, Fade(BLACK, 0.5f));
}
