/*
** EPITECH PROJECT, 2023
** YinChillang
** File description:
** Main
*/

#include "YinChillang.hpp"
#include "Game.hpp"
#include "Scenes.hpp"

int main()
{
    Game game; // TODO: init la game ici donc mettre les params nécessaires
    Scenes scene;

    scene.HandleScene(1, scene, game);
    // game.run();
    return 0;
}
