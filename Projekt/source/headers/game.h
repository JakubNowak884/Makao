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
        sf::Text info;

        int ID;
        int delay;
        int won;

    public:
        std::vector<card*> hand;

        Player(std::list<card*>& deck, sf::Font& font, int _ID);

        int getID();
        int getWon();
        int& getDelay();

        void decrementDelay(int value = 1);
        void setWon(int _won);
        void setDelay(int _delay);
        void setTextColor(sf::Color color);

        card* drawACard(std::list<card*>& deck, bool actionCardIsActive, suitNumber currentSuit, figureNumber currentFigure, int howMany = 1);
        void draw(sf::RenderWindow& window);
    };

private:
    sf::Text wanting;

    std::unique_ptr<button> b_fold;
    std::unique_ptr<button> b_makao;
    std::unique_ptr<button> b_draw;

    int jackID = 0;

protected:
    std::unique_ptr<sf::Texture> textureSuit;
    sf::Font font;

    std::unique_ptr<Player> player;

    int amountOfPlayers = 0;

    std::list<card*> deck;
    bool second = false;
    int turn = 1;
    int wonCounter = 0;

    bool actionCardIsActive = false;
    int addDrawAmount = 1;
    bool four = false;
    int delay = 0;
    suitNumber currentSuit = suitNumber::null;
    figureNumber currentFigure = figureNumber::null;

public:
    game();
    void setCurrentSuit(suitNumber _suit) override;
    void setCurrentFigure(figureNumber _figure) override;
    virtual AI* getAI(int number);
    std::vector<card*>& getHand() override;
    int getAmountOfPlayers() override;
    int getWon();
    void bumpTurn();
    gameStateNumber cardDoThings(card* current, int& _delay, int ID, bool bot = false);
    virtual gameStateNumber update(sf::Event event, sf::RenderWindow& window);
    virtual void draw(sf::RenderWindow& window);
};

