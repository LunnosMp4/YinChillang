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
    // TODO @Lys: Créer l'instance game dans la classe Scenes et n'evoie pas en paramètre scenes dans scenes
    Game game;
    Scenes scene;

    scene.HandleScene(1, scene, game);
    return 0;
}
