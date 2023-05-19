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
    // Définissez les propriétés et les méthodes spécifiques au joueur
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
        const int _screenWidth = 1280;
        const int _screenHeight = 720;
        Camera3D _camera = { 0 }; // TODO Fix les warnings
        Vector2 _mousePosition = { 0 };
        Vector2 _prevMousePosition = { 0 };
        Model _groundModel;
        Texture2D _texture1; // TODO Vector textures
        Texture2D _texture2;
        Vector3 _cubePosition;
    // Ajoutez d'autres propriétés et méthodes privées selon les besoins
};
