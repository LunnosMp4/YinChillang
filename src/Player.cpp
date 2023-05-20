//
// Created by oyco on 20/05/23.
//

#include "Player.hpp"

Player::Player(Vector3 position) {
    _position = position;
    _velocity = { 0.0f, 0.0f, 0.0f };
    _jumpHeight = 8.0f;
    _gravity = 9.81f;
    _isGrounded = true;
    _speed = 10.0f;  // vitesse de déplacement
}

Player::~Player() {

}

void Player::move() {
    if (IsKeyDown(KEY_W)) { // Avancer
        _position.z -= _speed * GetFrameTime();
    }
    if (IsKeyDown(KEY_S)) { // Reculer
        _position.z += _speed * GetFrameTime();
    }
    if (IsKeyDown(KEY_A)) { // Gauche
        _position.x -= _speed * GetFrameTime();
    }
    if (IsKeyDown(KEY_D)) { // Droite
        _position.x += _speed * GetFrameTime();
    }
}

void Player::update() {

    // Handle jumping
    if (IsKeyPressed(KEY_SPACE) && _isGrounded) {
        _velocity.y = _jumpHeight;
        _isGrounded = false;
    }

    // Apply gravity
    if (!_isGrounded) {
        _velocity.y -= _gravity * GetFrameTime();
    }

    // Update player position based on velocity
    _position.y += _velocity.y * GetFrameTime();

    // Check if the player has reached the ground
    if (_position.y <= 0.0f) {
        _position.y = 0.0f;
        _velocity.y = 0.0f;
        _isGrounded = true;
    }

    _shadowPosition = { _position.x, -1.0f, _position.z };
}

void Player::draw() {
    DrawCube(_position, 2.0f, 2.0f, 2.0f, RED);
    DrawCubeWires(_position, 2.0f, 2.0f, 2.0f, MAROON);
    DrawCube(_shadowPosition, 2.0f, 0.1f, 2.0f, Fade(BLACK, 0.5f));
}
