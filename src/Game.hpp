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

class Game {
    public:
        Game();
        ~Game();

        void run();
        void update();
        void draw();
        void drawDebug();

    private:
        bool _debugMode;
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
        Model _sceneModel;
        Texture2D _texture1; // TODO Vector textures
        Texture2D _texture2;
        BoundingBox _boxTable;
        BoundingBox _groundBoundingBox;
        Music _musique;
    // Ajoutez d'autres propriétés et méthodes privées selon les besoins
};
