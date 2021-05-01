#pragma once

#include <vector>
#include <list>
#include <algorithm>
#include <random>
#include <iterator>
#include <iostream>

#include "gameState.h"

class game :
    public gameState
{
public:
    class Player
    {
        sf::Text info;

        int ID;
        int delay;
        int won;

    public:
        std::vector<std::shared_ptr<card>> hand;

        Player(std::list<std::shared_ptr<card>>& deck, sf::Font& font, int _ID);

        int getID();
        int getWon();
        int& getDelay();

        void decrementDelay(int value = 1);
        void setWon(int _won);
        void setDelay(int _delay);
        void setTextColor(sf::Color color);

        card* drawACard(std::list<std::shared_ptr<card>>& deck, bool actionCardIsActive, suitNumber currentSuit, figureNumber currentFigure, int howMany = 1);
        void draw(sf::RenderWindow& window);
    };

private:
    sf::Text wanting;

    std::unique_ptr<button> b_fold;
    std::unique_ptr<button> b_makao;
    std::unique_ptr<button> b_draw;

protected:
    std::unique_ptr<sf::Texture> textureSuit;
    sf::Font font;

    std::unique_ptr<Player> player;

    int amountOfPlayers = 0;

    std::list<std::shared_ptr<card>> deck;
    bool second = false;

    int turn = 1;
    int wonCounter = 0;

    bool actionCardIsActive = false;
    int addDrawAmount = 1;
    bool four = false;
    int jackID = 0;
    int delay = 0;
    suitNumber currentSuit = suitNumber::null;
    figureNumber currentFigure = figureNumber::null;

public:
    game(Resources* _resources, bool onlyQueens = false);
    virtual ~game() {};
    void setCurrentSuit(suitNumber _suit);
    void setCurrentFigure(figureNumber _figure);
    virtual AI* getAI(int number);
    std::vector<std::shared_ptr<card>>& getHand();
    int getAmountOfPlayers();
    int getWon();
    void bumpTurn();
    gameStateNumber cardDoThings(card* current, int& _delay, int ID, bool bot = false);
    virtual gameStateNumber update(sf::Event event, sf::RenderWindow& window);
    virtual void draw(sf::RenderWindow& window);
};

