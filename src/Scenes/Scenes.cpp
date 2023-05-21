/*
** EPITECH PROJECT, 2023
** YinChillang
** File description:
** Scenes
*/

#include "Scenes.hpp"
#include "Game.hpp"

Scenes::Scenes()
{

}

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
            } else if (IsKeyPressed(KEY_ENTER)) {
                if (selectedLevel == 1) {
                    levelSelected = true;
                    game.run();
                    _IsRunning = true;
                } else if (selectedLevel == 2)
                    CloseWindow();
                else if (selectedLevel == 3)
                    CloseWindow();
            }
        }
        if (IsKeyPressed(KEY_ESCAPE))
            break;
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("YinChillang", 150, 50, 100, DARKGRAY);

        DrawText(selectedLevel == 1 ? "> Play" : "Play", 150, 200, 40, selectedLevel == 1 ? RED : DARKGRAY);
        DrawText(selectedLevel == 2 ? "> Quit" : "Quit", 150, 250, 40, selectedLevel == 2 ? RED : DARKGRAY);
        DrawText(selectedLevel == 3 ? "> Quit mais c'est le 2" : "Quit mais c'est le 2", 150, 300, 40, selectedLevel == 3 ? RED : DARKGRAY);
        BeginMode3D(game.getCamera());
        DrawModel(game.getPlayerModel(), (Vector3){30.0f, -50.0f, 30.0f}, 1.0f, WHITE);
        EndMode3D();
        EndDrawing();
    }
    CloseWindow();
}

void Scenes::handleScene(int SceneToLaunch)
{
    Game game;

    if (SceneToLaunch == _Menu)
        startMenu(game);
    if (SceneToLaunch == _Game)
        game.run();
}
