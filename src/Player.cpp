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
        // rotate player
        _playerModel.transform = MatrixRotateY(DEG2RAD * 180);
        _playerModel.transform = MatrixMultiply(_playerModel.transform, MatrixRotateX(DEG2RAD * 90));
    }
    if (IsKeyDown(KEY_S)) { // Reculer
        _position.z += _speed * GetFrameTime();
        _boundingPlayer.min.z += _speed * GetFrameTime();
        _boundingPlayer.max.z += _speed * GetFrameTime();
        // rotate player
        _playerModel.transform = MatrixRotateY(DEG2RAD * 0);
        _playerModel.transform = MatrixMultiply(_playerModel.transform, MatrixRotateX(DEG2RAD * -90));
    }
    if (IsKeyDown(KEY_A)) { // Gauche
        _position.x -= _speed * GetFrameTime();
        _boundingPlayer.min.x -= _speed * GetFrameTime();
        _boundingPlayer.max.x -= _speed * GetFrameTime();
        _playerModel.transform = MatrixRotateY(DEG2RAD * 270);
        _playerModel.transform = MatrixMultiply(_playerModel.transform, MatrixRotateZ(DEG2RAD * -90));

    }
    if (IsKeyDown(KEY_D)) { // Droite
        _position.x += _speed * GetFrameTime();
        _boundingPlayer.min.x += _speed * GetFrameTime();
        _boundingPlayer.max.x += _speed * GetFrameTime();
        _playerModel.transform = MatrixRotateY(DEG2RAD * 90);
        _playerModel.transform = MatrixMultiply(_playerModel.transform, MatrixRotateZ(DEG2RAD * 90));
    }

    if (IsKeyDown(KEY_W) && IsKeyDown(KEY_A)) { // Avancer + Gauche
        _playerModel.transform = MatrixRotateY(DEG2RAD * 225);
        _playerModel.transform = MatrixMultiply(_playerModel.transform, MatrixRotate({ 1.0f, 0.0f, -1.0f }, DEG2RAD * 90));
    }
    if (IsKeyDown(KEY_W) && IsKeyDown(KEY_D)) { // Avancer + Droite
        _playerModel.transform = MatrixRotateY(DEG2RAD * 135);
        _playerModel.transform = MatrixMultiply(_playerModel.transform, MatrixRotate({ 1.0f, 0.0f, 1.0f }, DEG2RAD * 90));
    }
    if (IsKeyDown(KEY_S) && IsKeyDown(KEY_A)) { // Reculer + Gauche
        _playerModel.transform = MatrixRotateY(DEG2RAD * 315);
        _playerModel.transform = MatrixMultiply(_playerModel.transform, MatrixRotate({ -1.0f, 0.0f, -1.0f }, DEG2RAD * 90));
    }
    if (IsKeyDown(KEY_S) && IsKeyDown(KEY_D)) { // Reculer + Droite
        _playerModel.transform = MatrixRotateY(DEG2RAD * 45);
        _playerModel.transform = MatrixMultiply(_playerModel.transform, MatrixRotate({ -1.0f, 0.0f, 1.0f }, DEG2RAD * 90));
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
    if (_position.y <= 0.0f) {
        _position.y = 0.0f;
        _velocity.y = 0.0f;
        _isGrounded = true;
    }

    _shadowPosition = { _position.x, -1.0f, _position.z };
}

void Player::draw()
{
    DrawModel(_playerModel, _position, 0.1f, WHITE);
    DrawCylinder(_shadowPosition, 5.0f, 5.0f, 0.1f, 30, Fade(BLACK, 0.5f));
}
