#include <iostream>
#include <cmath>
#include "Hand.h"
//#include "Card.h"
using namespace std;


Hand::Hand(){ 
  handSize = 0;
  for (int i = 0; i < 7; i++) {
    this->drawCard();
  }
}

//Sorting the hand using selection sort
void Hand::sortHand() {
  Card *temp = new Card();
  int smallestIndex;
  for (int i = 0; i < handSize; i++) {
    *temp = *(hand+i); //the current lowest card in the array
    smallestIndex = i;
    for (int j = i+1; j < handSize; j++) {
      if (*(hand+j) < *temp) { //if card is less than temp
        smallestIndex = j;
        *temp = *(hand+smallestIndex);
      }
    }
    *(hand+smallestIndex) = *(hand+i); //swapping
    *(hand+i) = *temp;
  }
} 

void Hand::printHand(bool printFront) { 
  if (!printFront) { //prints CPU
    for (int i = 0; i < handSize; i++) {
      cout << "|  UNO  |";
    }
  }
  else { //prints Userhand
    for (int i = 0; i < handSize; i++) {
      (hand+i)->printCard();
    }
  }
}

void Hand::drawCard() { 
  Card *temp = new Card();
  if (handSize < 15) {
    temp->newCard();
    *(hand+handSize) = temp;
    handSize++;
  } 
  else {
    cout << "Max hand size met" << endl;
  } 
}

void Hand::playCard(Card &current, int i){ 
  current.setColor(hand[i].getColor());
  current.setValue(hand[i].getValue());
  (hand+i)->cardPlayed();
  if (handSize > 1) {
    for (int j = i; j < handSize-1; j++) {
      *(hand+j) = *(hand+j+1);
    }
  }
  handSize--;
}

int Hand::unplayedCards(){ 
  return handSize;
}

//Will return the card at a given index
Card Hand::getCard(int i) {
  return *(hand+i-1);
}

//Will calculate the final scores at the end of the game
int Hand::findScore() {
  int total = 0;
  for (int card = 0; card < handSize; card++) {
    total += ((hand+card)->getValue());
  }
  return total;
}

char Hand::getCardColor(int index){
  return (hand+index)->getColor();
}

int Hand::getCardValue(int index) {
  return (hand+index)->getValue();
}

//Deconstructor to free up memory
Hand::~Hand(){ 
  delete [] hand;
}
