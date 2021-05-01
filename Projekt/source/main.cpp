#include "headers\stateMachine.h"
#include "headers\Resources.h"

#include <iostream>
#include <conio.h>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Makao");
    sf::View area(sf::FloatRect(0, 0, 800, 800));
    window.setView(area);
    window.setFramerateLimit(30);
    std::unique_ptr<Resources> resources = std::make_unique<Resources>();
    resources->loadResources();
    std::unique_ptr<stateMachine> game = std::make_unique<stateMachine>(resources.get());
    std::unique_ptr<sf::Sprite> background = std::make_unique<sf::Sprite>(resources->getTexture("background"));
    background->setPosition(-480, 0);
    bool fullScreen = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (!game->update(event, window)) window.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F11)
            {
                if (fullScreen)
                {
                    window.create(sf::VideoMode(800, 800), "Makao");
                    sf::View area2(sf::FloatRect(0, 0, 800, 800));
                    window.setView(area2);
                    window.setFramerateLimit(30);
                    fullScreen = false;
                }
                else
                {
                    window.create(sf::VideoMode::getDesktopMode(), "Makao", sf::Style::Fullscreen);
                    sf::View area2(sf::FloatRect(-460, 0, 1720, 800));
                    window.setView(area2);
                    window.setFramerateLimit(30);
                    fullScreen = true;
                }

            }

            if (event.type == sf::Event::Resized)
            {
                if ((event.size.width) >= 800 && (event.size.height) >= 800)
                {
                    sf::View area2(sf::FloatRect(-float((event.size.width * 0.9f - 800)/2), 0, event.size.width * 0.9f, 800));
                    window.setView(sf::View(area2));
                }
                else
                {
                    sf::View area2(sf::FloatRect(0, 0, 800, 800));
                    window.setView(sf::View(area2));
                }
            }

            if (event.type == sf::Event::Closed) window.close();
        }
        window.draw(*background.get());
        game->draw(window);
        window.display();
    }
    
    return 0;
}
