#include"game.h"

int main(void){
    sf::RenderWindow window(sf::VideoMode(800, 600), "Lunare");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.draw(game);
        window.clear();
        window.display();
    }

    return 0;
}