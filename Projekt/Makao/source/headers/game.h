#pragma once

#include <vector>
#include <list>
#include <algorithm>
#include <random>
#include <iterator>

#include "gameState.h"
#include "cards\card_ace.h"
#include "cards\card_two.h"
#include "cards\card_three.h"
#include "cards\card_four.h"
#include "cards\card_five.h"
#include "cards\card_six.h"
#include "cards\card_seven.h"
#include "cards\card_eight.h"
#include "cards\card_nine.h"
#include "cards/card_ten.h"
#include "cards\card_jack.h"
#include "cards\card_queen.h"
#include "cards\card_king.h"

class game :
    public gameState
{
    sf::Texture texture;

    button* b_fold;
    button* b_draw;

    std::vector<card*> hand;

protected:
    sf::Font font;

    std::list<card*> deck;
    bool second = false;
    int turn;
    int won;
    int wonCounter;

    bool addDraw;
    int addDrawAmount;

public:
    game();
    ~game();
    virtual AI* getAI(int number);
    int getWon() override;
    void drawACard(int howMany = 1);
    void cardDoThings(card* current);
    virtual gameStateNumber update(sf::Event event, sf::RenderWindow& window);
    virtual void draw(sf::RenderWindow& window);
};

