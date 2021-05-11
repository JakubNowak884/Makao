#pragma once

#include <vector>
#include <list>
#include <algorithm>
#include <random>
#include <iterator>

#include "GameState.h"

class Game :
    public GameState
{
public:
    class Player
    {
        std::shared_ptr<Resources> resources;       /*!< WskaŸnik na obiekt klasy przechowuj¹cy zasoby gry. */
        sf::Text info;                              /*!< Teskt wyœwietlaj¹cy informacje o graczu. */

        int ID;                                     /*!< Identyfikator gracza. */
        int delay;                                  /*!< OpóŸnienie gracza w turach. */
        int won;                                    /*!< Miejsce zajête przez gracza. */
        bool second = false;                        /*!< Zmienna informuj¹ca czy zosta³a ju¿ zagrana przez gracza karta w danej turze. */

    public:
        std::vector<std::shared_ptr<Card>> hand;    /*!< Karty w rêce gracza. */
        /**
           * \brief Konstruktor trzyargumentowy.
           * \param deck talia gry, z której przydzialane s¹ karty do rêki gracza.
           * \param _resources wskaŸnik na obiekt klasy przechowuj¹cy zasoby gry.
           * \param _ID identyfikator gracza.
           */
        Player(std::list<std::shared_ptr<Card>>& deck, std::shared_ptr<Resources> _resources, int _ID);

        int getID();
        int getWon();
        int& getDelay();
        bool getSecond();

        void setSecond(bool _second);
        void decrementDelay(int value = 1);
        void setWon(int _won);
        void setDelay(int _delay);
        void setTextColor(sf::Color color);
        /**
          * \brief Funkcja wywo³ywana gdy gracz dobiera kartê.
          * 
          * Jeœli dobrana karta spe³nia warunki zagrania, jest ona automatycznie zagrywana, w przeciwnym wypadku gracz dobiera odpowiedni¹ liczbê kart.
          * \param actionCardIsActive zmienna informuj¹ca czy aktualnie na grê oddzia³uje efekt którejœ z kart.
          * \param currentSuit zmienna informuj¹ca czy aktulanie w grze jest ¿¹danie koloru.
          * \param currentFigure zmienna informuj¹ca czy aktulanie w grze jest ¿¹danie figury.
          * \param howMany zmienna informuj¹ca ile gracz dobierze kart.
          * \return wskaŸnik na obiekt dobranej karty, jeœli spe³nia ona warunki zagrania, w przeciwnym wypadku nullptr
          */
        Card* drawACard(std::list<std::shared_ptr<Card>>& deck, bool actionCardIsActive, suitNumber currentSuit, figureNumber currentFigure, int howMany = 1);
        /**
         * \brief Funkcja rysuj¹ca na ekranie informacje o graczu oraz karty w jego rêce.
         * \param window okno gry.
         */
        void draw(sf::RenderWindow& window);
    };

private:
    sf::Text wanting;                                   /*!< Teskt wyœwietlaj¹cy informacje o aktualnym ¿¹daniu. */
    sf::Text addDraw;                                   /*!< Teskt wyœwietlaj¹cy informacje o iloœci kart do dobrania przez kolejnego gracza. */

    std::unique_ptr<Button> b_fold;                     /*!< Przycisk pasowania. */
    std::unique_ptr<Button> b_makao;                    /*!< Przycisk dobrania karty, jeœli graczowi zosta³a w rêce tylko jedna. */
    std::unique_ptr<Button> b_draw;                     /*!< Przycisk dobrania karty. */

protected:
    std::unique_ptr<Player> player;                     /*!< WskaŸnik na obiekt klasy gracza. */
    std::vector<std::unique_ptr<AI>> bots;              /*!< Wektor wskaŸników na obiekty klasy graczy komputerowych. */
    bool end = false;                                   /*!< Zmienna informuj¹ca o koñcu rozgrywki. */

    int amountOfPlayers = 0;                            /*!< Zmienna informuj¹ca o iloœci graczy bior¹cych udzia³ w rozgrywce. */

    std::list<std::shared_ptr<Card>> deck;              /*!< Talia gry przechowywana w liœcie. */

    int turn = 1;                                       /*!< Zmienna informuj¹ca o aktualnej turze. */
    int wonCounter = 0;                                 /*!< Licznik wygranych graczy. */

    bool actionCardIsActive = false;                    /*!< Zmienna informuj¹ca czy aktualnie na grê oddzia³uje efekt którejœ z kart. */
    int addDrawAmount = 1;                              /*!< Zmienna informuj¹ca ile gracz dobierze kart. */
    bool four = false;                                  /*!< Zmienna informuj¹ca czy na grê oddzia³uje aktualnie efekt Czwórki. */
    int jackID = 0;                                     /*!< Zmienna informuj¹ca o tym który z graczy zagra³ Waleta. */
    int delay = 0;                                      /*!< Zmienna informuj¹ca na ile tur nastêpny gracz dostanie opóŸnienie. */
    suitNumber currentSuit = suitNumber::null;          /*!< Aktualnie ¿¹dany kolor. */
    figureNumber currentFigure = figureNumber::null;    /*!< Aktualnie ¿¹dana figura. */

    bool threadRunning = false;                         /*!< Zmienna informuj¹ca czy aktualnie pracuje w¹tek. */

public:
    /**
       * \brief Konstruktor dwuargumentowy.
       * \param _resources wskaŸnik na obiekt klasy przechowuj¹cy zasoby gry.
       * \param onlyQueens zmienna informuj¹ca o tym, czy talia ma zawieraæ tylko Królowe.
       * \see GameState::GameState(std::shared_ptr<Resources> _resources)
       */
    Game(std::shared_ptr<Resources> _resources, bool onlyQueens = false);
    virtual ~Game() {};

    void setCurrentSuit(suitNumber _suit);
    void setCurrentFigure(figureNumber _figure);
    virtual AI* getAI(int number);
    std::vector<std::shared_ptr<Card>>& getHand();
    int getAmountOfPlayers();

    int getWon();
    /**
      * \brief Funkcja aktualizuj¹ca turê.
      */
    void bumpTurn();
    /**
       * \brief Funkcja realizuj¹ca efekt zagranej karty.
       * \param current wskaŸnik na obiekt zagranej karty.
       * \param opóŸnienie gracza, który zagra³ kartê.
       * \param ID identyfikator gracza, który zagra³ kartê.
       * \param bot informacja czy karta zosta³a zagrana przez gracza komputerowego.
       * \return nowy stan gry, jeœli zagran¹ kart¹ by³ As lub Walet.
       */
    gameStateNumber cardDoThings(Card* current, int& _delay, int ID, bool bot = false);
    /**
      * \see GameState::update(sf::Event event, sf::RenderWindow& window)
      */
    virtual gameStateNumber update(sf::Event event, sf::RenderWindow& window) override;
    /**
       * \see GameState::draw(sf::RenderWindow& window)
       */
    virtual void draw(sf::RenderWindow& window) override;
};

