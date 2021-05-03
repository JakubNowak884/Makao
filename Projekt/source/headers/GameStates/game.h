#pragma once

#include <vector>
#include <list>
#include <algorithm>
#include <random>
#include <iterator>
#include <iostream>

#include "GameState.h"

class Game :
    public GameState
{
public:
    class Player
    {
        Resources* resources;
        sf::Text info;

        int ID;
        int delay;
        int won;

    public:
        std::vector<std::shared_ptr<Card>> hand;

        Player(std::list<std::shared_ptr<Card>>& deck, Resources* _resources, int _ID);

        int getID();
        int getWon();
        int& getDelay();

        void decrementDelay(int value = 1);
        void setWon(int _won);
        void setDelay(int _delay);
        void setTextColor(sf::Color color);

        Card* drawACard(std::list<std::shared_ptr<Card>>& deck, bool actionCardIsActive, suitNumber currentSuit, figureNumber currentFigure, int howMany = 1);
        void draw(sf::RenderWindow& window);
    };

private:
    sf::Text wanting;
    sf::Text addDraw;

    std::unique_ptr<Button> b_fold;
    std::unique_ptr<Button> b_makao;
    std::unique_ptr<Button> b_draw;

protected:
    std::unique_ptr<Player> player;
    std::vector<std::unique_ptr<AI>> bots;
    bool end = false;
    long sleepDuration = 1;

    int amountOfPlayers = 0;

    std::list<std::shared_ptr<Card>> deck;
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
    Game(Resources* _resources, bool onlyQueens = false);
    virtual ~Game() {};
    void setCurrentSuit(suitNumber _suit);
    void setCurrentFigure(figureNumber _figure);
    virtual AI* getAI(int number);
    std::vector<std::shared_ptr<Card>>& getHand();
    int getAmountOfPlayers();
    int getWon();
    void bumpTurn();
    void botsTakesTurn(bool withThread = true);
    gameStateNumber cardDoThings(Card* current, int& _delay, int ID, bool bot = false);
    virtual gameStateNumber update(sf::Event event, sf::RenderWindow& window);
    virtual void draw(sf::RenderWindow& window);
};

