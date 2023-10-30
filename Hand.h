#include <iostream>
#include "Card.h"
using namespace std;

class Hand {
  private:
    int handSize; //holds array size
    Card *hand = new Card[15];
  public:
    Hand();
    void sortHand();
    void printHand(bool);
    void drawCard();
    void playCard(Card &, int);
    int unplayedCards();
    Card getCard(int);
    int findScore();
    char getCardColor(int);
    int getCardValue(int);
    ~Hand();
};