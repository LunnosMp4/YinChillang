/*
** EPITECH PROJECT, 2023
** YinChillang
** File description:
** Scenes
*/

#include "Scenes.hpp"
#include "Game.hpp"

void Scenes::startMenu() {}

void Scenes::handleScene(int SceneToLaunch)
{
    Game game;

    if (SceneToLaunch == _Game)
        game.run();
    if (SceneToLaunch == _Menu)
        startMenu();
}
