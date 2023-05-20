/*
** EPITECH PROJECT, 2023
** YinChillang
** File description:
** Scenes
*/

#include "Scenes.hpp"
#include "Game.hpp"

Scenes::Scenes() {}

Scenes::~Scenes()
{
}

void Scenes::startMenu(Game game)
{
    int selectedLevel = 1;
    bool levelSelected = false;

    while (!WindowShouldClose()) {
        if (!levelSelected) {
            if (IsKeyPressed(KEY_UP)) {
                selectedLevel--;
                if (selectedLevel < 1)
                    selectedLevel = 3;
            } else if (IsKeyPressed(KEY_DOWN)) {
                selectedLevel++;
                if (selectedLevel > 3)
                    selectedLevel = 1;
            } else if (IsKeyPressed(KEY_ENTER))
                levelSelected = true;
        }
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("YinChillang", 20, 20, 50, DARKGRAY);

        DrawText(selectedLevel == 1 ? "> Level 1" : "Level 1", 20, 100, 20, selectedLevel == 1 ? RED : DARKGRAY);
        DrawText(selectedLevel == 2 ? "> Level 2" : "Level 2", 20, 130, 20, selectedLevel == 2 ? RED : DARKGRAY);
        DrawText(selectedLevel == 3 ? "> Level 3" : "Level 3", 20, 160, 20, selectedLevel == 3 ? RED : DARKGRAY);

        if (levelSelected) {
            DrawText(TextFormat("Level %d selected!", selectedLevel), 20, 200, 20, DARKGRAY);
            game.run();
        }
        EndDrawing();
    }
}

void Scenes::handleScene(int SceneToLaunch)
{
    Game game;

    if (SceneToLaunch == _Game)
        game.run();
    if (SceneToLaunch == _Menu)
        startMenu(game);
}
