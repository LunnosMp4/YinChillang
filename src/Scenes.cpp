/*
** EPITECH PROJECT, 2023
** YinChillang
** File description:
** Scenes
*/

#include "Scenes.hpp"
#include "Game.hpp"

Scenes::Scenes() {}

Scenes::~Scenes() {}

void Scenes::StartMenu()
{
    
}

void Scenes::HandleScene(int SceneToLaunch)
{
    Game game;

    if (SceneToLaunch == _Game)
        game.run();
    if (SceneToLaunch == _Menu)
        StartMenu();
}
