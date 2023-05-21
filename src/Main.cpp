/*
** EPITECH PROJECT, 2023
** YinChillang
** File description:
** Main
*/

#include "YinChillang.hpp"
#include "Game.hpp"
#include "Scenes/Scenes.hpp"

float randomFloatBetween(float start, float end) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(start, end);
    return dis(gen);
}

int main()
{
    Scenes scene;

    scene.handleScene(0);
    return 0;
}