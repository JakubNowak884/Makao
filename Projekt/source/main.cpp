#include "headers/StateMachine.h"
#include "headers/Resources.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Makao");
    sf::View area(sf::FloatRect(0, 0, 800, 800));
    window.setView(area);
    window.setFramerateLimit(30);
    std::shared_ptr<Resources> resources = std::make_shared<Resources>();
    try
    {
        resources->loadResources();
        resources->loadLanguage("polish");
    }
    //zapisanie komunikatu wyj?tku do pliku tekstowego
    catch (const char* error)
    {
        std::ofstream file;
        file.open("error.txt");
        file << error;
        file.close();
        return 0;
    }
    std::unique_ptr<StateMachine> game = std::make_unique<StateMachine>(resources);
    std::unique_ptr<sf::Sprite> background = std::make_unique<sf::Sprite>(resources->getTexture("background"));
    background->setPosition(-480, 0);
    bool fullScreen = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            try 
            {
                if (!game->update(event, window))
                    window.close();
            }
            catch (std::wstring error)
            {
                game->exception(error);
            }

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
                //je?li szeroko?? i wysoko?? okna przekroczy 800 piskeli ekran gry zostanie proporcjonalnie powi?kszony
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
        try
        {
            game->draw(window);
        }
        catch (std::wstring error)
        {
            game->exception(error);
        }
        window.display();
    }
    
    return 0;
}
