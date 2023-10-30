#include <iostream>
#include <cmath>
#include "Card.h"
using namespace std;

//For outputting Colored Text
#define ESC "\033["
#define RED_TXT "31"
#define YELLOW_TXT "33"
#define BLUE_TXT "34"
#define GREEN_TXT "32"
#define WILD_TXT "1" 
#define RESET "\033[m"

//Default constructor- will initialize to empty signal values
Card::Card() {
  color = 'E';
  value = 0;
}

//Using probability rules to randomly assign a given card a color and value
void Card::newCard() {
  int random = rand()%39;
  if (random%4 == 0) {
    color = 'R'; //Red
  }
  else if (random%4 == 1) {
    color = 'Y'; //Yellow
  }
  else if (random%4 == 2) {
    color = 'B'; //Blue 
  }
  else {
    color = 'G'; //Green
  }
  value = (random%9)+1;
  //TESTING: cout << endl << endl << "This Cards Value: " << value << endl << endl;
  if (random > 36) { //For wild cards
    color = 'W'; //Wild
    value = 50; //Worth 50 points 
  } 
}

//overloading the == operator to compare cards
bool Card::operator==(Card &right) {
  if (this->color == right.color || this->value == right.value) {
    return true;
  }
  //Modified functionality of Wild Card- The player can play it on any color, however the next user can play any card that they want
  else if (this->color == 'W' || right.color == 'W') {
    return true;
  }
  else {
    return false;
  }
}

//overloading the < operator to use later in the sortCard function
bool Card::operator<(Card &right) {
  if (color == right.color) {
    return (value < right.value);
  }
  else { //colors are different
    if (color == 'W') { //if it is a wild card
      return false;
    }
    else if (right.color == 'W') {
      return true;
    }
    else {
      return (color < right.color); 
    }
  }
}

//Will set the cards to signal values showcasing that they are played- will be easier to remove from array after sorting
void Card::cardPlayed() {
  color = '@';
  value = 0;
}

//Will print the cards in their corresponding colors
void Card::printCard() {
  if (color == 'R') { //Red Cards
    cout << ESC << ";" << RED_TXT << "m" << "|  Red " << value << " |" << RESET;
  }
  else if (color == 'B') { //Blue Cards
    cout << ESC << ";" << BLUE_TXT << "m" << "|  Blue " << value << " |" << RESET;
  }
  else if (color == 'Y') { //Yellow Cards
    cout << ESC << ";" << YELLOW_TXT << "m" << "| Yellow " << value << " |" << RESET;
  }
  else if (color == 'G') { //Green Cards
    cout << ESC << ";" << GREEN_TXT << "m" << "| Green " << value << " |" << RESET;
  }
  else if (color == 'W') { //Wild Cards- will Bold
    cout << ESC << ";" << WILD_TXT << "m" << "|  Wild  |" << RESET;
  }
  else {
    cout << "ERROR- Color: " << color << endl;
  }
}

//Overloaded = operator to simplify sorting method
void Card::operator=(Card *right) {
  this->color = right->color;
  this->value = right->value;
}

//getter function for value 
int Card::getValue() {
  return value;
}

char Card::getColor() {
  return color;
}

void Card::setValue(int n) {
  value = n;
}

void Card::setColor(char c) {
  color = c;
}