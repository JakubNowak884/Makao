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
    sf::Texture textureSuit;
    sf::Text wanting;

    button* b_fold;
    button* b_draw;

    std::vector<card*> hand;

    int delay;
    int myDelay;
    int jackID;

protected:
    sf::Font font;

    std::list<card*> deck;
    bool second = false;
    int turn;
    int won;
    int wonCounter;

    bool actionCardIsActive;
    int addDrawAmount;
    suitNumber currentSuit;
    figureNumber currentFigure;

public:
    game();
    ~game();
    void setCurrentSuit(suitNumber _suit) override;
    void setCurrentFigure(figureNumber _figure) override;
    virtual AI* getAI(int number);
    int getWon() override;
    card* drawACard(int howMany = 1);
    gameStateNumber cardDoThings(card* current, int& _delay, int ID);
    virtual gameStateNumber update(sf::Event event, sf::RenderWindow& window);
    virtual void draw(sf::RenderWindow& window);
};

