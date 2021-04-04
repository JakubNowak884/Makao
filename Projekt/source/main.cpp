#include "headers\stateMachine.h"

#include <iostream>
#include <conio.h>

int main()
{
    /*
    sf::IpAddress ip = "185.238.122.73";
    //std::cout << sf::IpAddress::getLocalAddress();
    //std::cout << sf::IpAddress::getPublicAddress();
    sf::TcpSocket socket;
    char connectionType;
    char mode = 'd';
    char buffer[2000];
    std::size_t received;
    std::string text = "Connected to: ";

    std::cout << "s for server c for client" << std::endl;
    std::cin >> connectionType;

    if (connectionType == 's')
    {
        sf::TcpListener listener;
        listener.listen(2000);
        listener.accept(socket);
        text += "Server";
        mode = 's';
    }
    else if (connectionType == 'c')
    {
        socket.connect(ip, 2000);
        text += "Client";
        mode = 'r';
    }

    socket.send(text.c_str(), text.length() + 1);

    socket.receive(buffer, sizeof(buffer), received);

    std::cout << buffer << std::endl;

    std::string currentText = "test";

    unsigned char znak = 0;

    while (true)
    {
        if (kbhit())
            znak = getch();
        switch (znak)
        {
        case 97:
            text = "test a";
            break;
        case 98:
            text = "test b";
            break;
        default:
            text = "test def";
            break;
        }
        socket.send(text.c_str(), text.length() + 1);
        socket.receive(buffer, sizeof(buffer), received);
        currentText = buffer;
        std::cout << "Current text: " << currentText << std::endl;
        system("cls");
    }

    system("pause");
    */
    
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
