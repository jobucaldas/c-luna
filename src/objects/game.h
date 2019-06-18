#ifndef "GAME_H"
#define "GAME_H"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Sistem.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
using namespace std;

class game
{
private:

public:
    game();
    virtual ~game();
    //funções
    void updateSFMLEvents();
    void update();
    void render();
    void run();


};
#endif