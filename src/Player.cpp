//
// Created by oyco on 20/05/23.
//

#include "Player.hpp"

Player::Player(Vector3 position)
{
    _position = position;
    _boundingPlayer = { { position.x - 2.5f, position.y - 2.5f, position.z - 2.5f }, { position.x + 2.5f, position.y + 2.5f, position.z + 2.5f } };
    _velocity = { 0.0f, 0.0f, 0.0f };
    _jumpHeight = 30.0f;
    _gravity = 70.0f;
    _isGrounded = true;
    _speed = 30.0f;
    _isDead = false;
    isAnimating = false;
    _animationDuration = 1.0f;
    _isAnimationTriggered = false;
    _waitDuration = 3.0f;
    _waitTimeElapsed = 0.0f;
    _isWaiting = false;
    _isRotating = false;
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

void Player::animate()
{
    if (isAnimating) {
        _animationTimeElapsed += GetFrameTime();
        if (_animationTimeElapsed >= _animationDuration) {
            _position = _targetPosition;
            isAnimating = false;
            _isWaiting = true; // Start waiting
            _waitTimeElapsed = 0.0f;
        } else {
            float t = _animationTimeElapsed / _animationDuration;
            _position = Vector3Lerp(_startPosition, _targetPosition, t);
        }
    }

    if (_isWaiting) {
        _waitTimeElapsed += GetFrameTime();
        if (_waitTimeElapsed >= _waitDuration) {
            _isWaiting = false;
            _isRotating = true;
        }
    }

    if (_isRotating) {
        _playerModel.transform = MatrixRotateX(DEG2RAD * -110.0f);
        _isRotating = false;
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
    _shadowScale = 3 - _position.y / 6;

    _shadowPosition = { _position.x, 0.0f, _position.z };
    animate();
}

void Player::draw()
{
    DrawModel(_playerModel, _position, 0.1f, WHITE);
    DrawCylinder(_shadowPosition, _shadowScale, _shadowScale, 0.1f, 30, Fade(BLACK, 0.5f));
}

void Player::setDead(bool isDead) {
    _isDead = isDead;
    if (!_isDead)
        return;

    if (_isAnimationTriggered)
        return;

    _startPosition = _position;
    _targetPosition = { 0.0f, 40.0f, 90.0f };
    _animationTimeElapsed = 0.0f;
    isAnimating = true;
    _isAnimationTriggered = true;

    _velocity = { 0.0f, 0.0f, 0.0f };
    _isGrounded = true;
    _playerModel.transform = MatrixIdentity();
    _playerModel.transform = MatrixRotateX(DEG2RAD * -90);
}