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

void Scenes::HandleScene(int SceneToLaunch, Scenes scene, Game game)
{
    if (SceneToLaunch == scene._Game)
        game.run();
    if (SceneToLaunch == scene._Menu)
        scene.StartMenu();
}
