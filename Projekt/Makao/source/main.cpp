#include "headers\stateMachine.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800, 32), "Makao");
    sf::FloatRect area(0, 0, 800, 800);
    window.setView(sf::View(area));
    window.setFramerateLimit(30);
    stateMachine* game = new stateMachine;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (!game->update(event, window)) window.close();

            if (event.type == sf::Event::Closed) window.close();
        }
        window.clear(sf::Color::Color(0, 0, 128));
        game->draw(window);
        window.display();
    }

    return 0;
}
