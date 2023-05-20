/*
** EPITECH PROJECT, 2023
** YinChillang
** File description:
** Scenes
*/

#ifndef SCENES_HPP_
    #define SCENES_HPP_
    #include "YinChillang.hpp"
    #include "Game.hpp"

class Scenes {
    public:
        Scenes();
        ~Scenes();

        void startMenu(Game game);
        void handleScene(int SceneToLaunch);
    protected:
    private:
        bool _IsRunning = false;
        int _Menu = 0;
        int _Game = 1;
        int _End = 2;
};

#endif /* !SCENES_HPP_ */
