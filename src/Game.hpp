//
// Created by oyco on 19/05/23.
//

#pragma once

#include "YinChillang.hpp"

class Enemy {
    // Définissez les propriétés et les méthodes spécifiques à l'ennemi
};

class Level {
    // Définissez les propriétés et les méthodes pour gérer les niveaux du jeu
};

class Game
{
    public:
        Game();
        ~Game();

        void run();
        void update();
        void draw();
        void drawDebug();

        const int _screenWidth = 1280;
        const int _screenHeight = 720;
    private:
        bool _debugMode;
        Player _player;
        Enemy _enemy;
        Level _level;
        bool _cameraMovementEnabled;
        Camera3D _camera;
        Vector2 _mousePosition;
        Vector2 _prevMousePosition;
        Model _playerModel;
        Model _groundModel;
        Model _sceneModel;
        Texture2D _texture1; // TODO Vector textures
        Texture2D _texture2;
        BoundingBox _boxTable;
        BoundingBox _groundBoundingBox;
        Music _musique;
    // Ajoutez d'autres propriétés et méthodes privées selon les besoins
};
