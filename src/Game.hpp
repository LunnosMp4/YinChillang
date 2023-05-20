//
// Created by oyco on 19/05/23.
//

#pragma once

#include "raylib.h"
#include "raymath.h"
#include <cmath>
#include <fstream>

class GameObject {
    // Définissez les propriétés et les méthodes communes à tous les objets de jeu
};

class Player : public GameObject {
    public:
        Player(Vector3 position) {
            _position = position;
            _velocity = { 0.0f, 0.0f, 0.0f };
            _jumpHeight = 8.0f;
            _gravity = 9.81f;
            _isGrounded = true;
            _speed = 10.0f;  // vitesse de déplacement
        }

        void update() {

            // Handle jumping
            if (IsKeyPressed(KEY_SPACE) && _isGrounded) {
                _velocity.y = _jumpHeight;
                _isGrounded = false;
            }

            // Gestion du mouvement du joueur
            if (IsKeyDown(KEY_W)) { // Avancer
                _position.z += _speed * GetFrameTime();
            }
            if (IsKeyDown(KEY_S)) { // Reculer
                _position.z -= _speed * GetFrameTime();
            }
            if (IsKeyDown(KEY_A)) { // Gauche
                _position.x -= _speed * GetFrameTime();
            }
            if (IsKeyDown(KEY_D)) { // Droite
                _position.x += _speed * GetFrameTime();
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
        }

        void draw() {
            DrawCube(_position, 2.0f, 2.0f, 2.0f, RED);
        }

    private:
        Vector3 _position;
        Vector3 _velocity;
        float _jumpHeight;
        float _gravity;
        bool _isGrounded;
        float _speed;
};

class Enemy : public GameObject {
    // Définissez les propriétés et les méthodes spécifiques à l'ennemi
};

class Level {
    // Définissez les propriétés et les méthodes pour gérer les niveaux du jeu
};

class Game {
    public:
        Game();
        ~Game();

        void run();
        void update();
        void draw();
        void close();

    private:
        Player _player;
        Enemy _enemy;
        Level _level;
        bool _cameraMovementEnabled;
        const int _screenWidth;
        const int _screenHeight;
        Camera3D _camera;
        Vector2 _mousePosition;
        Vector2 _prevMousePosition;
        Model _groundModel;
        Texture2D _texture1; // TODO Vector textures
        Texture2D _texture2;
        BoundingBox _boxTable;
    // Ajoutez d'autres propriétés et méthodes privées selon les besoins
};
