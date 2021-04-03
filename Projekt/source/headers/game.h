#pragma once

#include <vector>
#include <list>
#include <algorithm>
#include <random>
#include <iterator>

#include "gameState.h"

class game :
    public gameState
{
public:
    class Player
    {
        int ID;
        int delay;
        int won;

    public:
        std::vector<card*> hand;

        Player(std::list<card*>& deck, int _ID);

        int getID();
        int getWon();
        int& getDelay();

        void decrementDelay(int value = 1);
        void setWon(int _won);

        card* drawACard(std::list<card*>& deck, bool actionCardIsActive, suitNumber currentSuit, figureNumber currentFigure, int howMany = 1);
        void draw(sf::RenderWindow& window);
    };

private:
    sf::Texture textureSuit;
    sf::Text wanting;

    std::unique_ptr<button> b_fold;
    std::unique_ptr<button> b_draw;

    int delay = 0;
    int jackID = 0;

protected:
    sf::Font font;

    std::unique_ptr<Player> player;

    std::list<card*> deck;
    bool second = false;
    int turn = 1;
    int wonCounter = 0;

    bool actionCardIsActive = false;
    int addDrawAmount = 1;
    suitNumber currentSuit = suitNumber::null;
    figureNumber currentFigure = figureNumber::null;

public:
    game();
    ~game();
    void setCurrentSuit(suitNumber _suit) override;
    void setCurrentFigure(figureNumber _figure) override;
    virtual AI* getAI(int number);
    gameStateNumber cardDoThings(card* current, int& _delay, int ID);
    virtual gameStateNumber update(sf::Event event, sf::RenderWindow& window);
    virtual void draw(sf::RenderWindow& window);
};

