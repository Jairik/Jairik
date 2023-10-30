#include <iostream>
using namespace std;

//Card Colors: 'R' == Red, 'B' == Blue, 'G' == Green, 'Y' == Yellow, 'W' == Wild, '@' == Empty
//Card Value: Numbers on card, Wild cards = 50, Empty card is signaled by a 0

class Card {
  private:
    char color;
    int value;
  public:
    Card(); //Will create an empty card
    void newCard();
    bool operator==(Card &);
    bool operator<(Card &);
    void cardPlayed();
    void printCard();
    int getValue();
    char getColor();
    void operator=(Card *);
    void setValue(int);
    void setColor(char);
};