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
        std::shared_ptr<Resources> resources;       /*!< Wska�nik na obiekt klasy przechowuj�cy zasoby gry. */
        sf::Text info;                              /*!< Teskt wy�wietlaj�cy informacje o graczu. */

        int ID;                                     /*!< Identyfikator gracza. */
        int delay;                                  /*!< Op�nienie gracza w turach. */
        int won;                                    /*!< Miejsce zaj�te przez gracza. */
        bool second = false;                        /*!< Zmienna informuj�ca czy zosta�a ju� zagrana przez gracza karta w danej turze. */

    public:
        std::vector<std::shared_ptr<Card>> hand;    /*!< Karty w r�ce gracza. */
        /**
           * \brief Konstruktor trzyargumentowy.
           * \param deck talia gry, z kt�rej przydzialane s� karty do r�ki gracza.
           * \param _resources wska�nik na obiekt klasy przechowuj�cy zasoby gry.
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
          * \brief Funkcja wywo�ywana gdy gracz dobiera kart�.
          * 
          * Je�li dobrana karta spe�nia warunki zagrania, jest ona automatycznie zagrywana, w przeciwnym wypadku gracz dobiera odpowiedni� liczb� kart.
          * \param actionCardIsActive zmienna informuj�ca czy aktualnie na gr� oddzia�uje efekt kt�rej� z kart.
          * \param currentSuit zmienna informuj�ca czy aktulanie w grze jest ��danie koloru.
          * \param currentFigure zmienna informuj�ca czy aktulanie w grze jest ��danie figury.
          * \param howMany zmienna informuj�ca ile gracz dobierze kart.
          * \return wska�nik na obiekt dobranej karty, je�li spe�nia ona warunki zagrania, w przeciwnym wypadku nullptr
          */
        Card* drawACard(std::list<std::shared_ptr<Card>>& deck, bool actionCardIsActive, suitNumber currentSuit, figureNumber currentFigure, int howMany = 1);
        /**
         * \brief Funkcja rysuj�ca na ekranie informacje o graczu oraz karty w jego r�ce.
         * \param window okno gry.
         */
        void draw(sf::RenderWindow& window);
    };

private:
    sf::Text wanting;                                   /*!< Teskt wy�wietlaj�cy informacje o aktualnym ��daniu. */
    sf::Text addDraw;                                   /*!< Teskt wy�wietlaj�cy informacje o ilo�ci kart do dobrania przez kolejnego gracza. */

    std::unique_ptr<Button> b_fold;                     /*!< Przycisk pasowania. */
    std::unique_ptr<Button> b_makao;                    /*!< Przycisk dobrania karty, je�li graczowi zosta�a w r�ce tylko jedna. */
    std::unique_ptr<Button> b_draw;                     /*!< Przycisk dobrania karty. */

protected:
    std::unique_ptr<Player> player;                     /*!< Wska�nik na obiekt klasy gracza. */
    std::vector<std::unique_ptr<AI>> bots;              /*!< Wektor wska�nik�w na obiekty klasy graczy komputerowych. */
    bool end = false;                                   /*!< Zmienna informuj�ca o ko�cu rozgrywki. */

    int amountOfPlayers = 0;                            /*!< Zmienna informuj�ca o ilo�ci graczy bior�cych udzia� w rozgrywce. */

    std::list<std::shared_ptr<Card>> deck;              /*!< Talia gry przechowywana w li�cie. */

    int turn = 1;                                       /*!< Zmienna informuj�ca o aktualnej turze. */
    int wonCounter = 0;                                 /*!< Licznik wygranych graczy. */

    bool actionCardIsActive = false;                    /*!< Zmienna informuj�ca czy aktualnie na gr� oddzia�uje efekt kt�rej� z kart. */
    int addDrawAmount = 1;                              /*!< Zmienna informuj�ca ile gracz dobierze kart. */
    bool four = false;                                  /*!< Zmienna informuj�ca czy na gr� oddzia�uje aktualnie efekt Czw�rki. */
    int jackID = 0;                                     /*!< Zmienna informuj�ca o tym kt�ry z graczy zagra� Waleta. */
    int delay = 0;                                      /*!< Zmienna informuj�ca na ile tur nast�pny gracz dostanie op�nienie. */
    suitNumber currentSuit = suitNumber::null;          /*!< Aktualnie ��dany kolor. */
    figureNumber currentFigure = figureNumber::null;    /*!< Aktualnie ��dana figura. */

    bool threadRunning = false;                         /*!< Zmienna informuj�ca czy aktualnie pracuje w�tek. */

public:
    /**
       * \brief Konstruktor dwuargumentowy.
       * \param _resources wska�nik na obiekt klasy przechowuj�cy zasoby gry.
       * \param onlyQueens zmienna informuj�ca o tym, czy talia ma zawiera� tylko Kr�lowe.
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
      * \brief Funkcja aktualizuj�ca tur�.
      */
    void bumpTurn();
    /**
       * \brief Funkcja realizuj�ca efekt zagranej karty.
       * \param current wska�nik na obiekt zagranej karty.
       * \param op�nienie gracza, kt�ry zagra� kart�.
       * \param ID identyfikator gracza, kt�ry zagra� kart�.
       * \param bot informacja czy karta zosta�a zagrana przez gracza komputerowego.
       * \return nowy stan gry, je�li zagran� kart� by� As lub Walet.
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

