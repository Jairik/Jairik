#include <cmath>
#include <ctime>
#include <iostream>
#include "Hand.h"
using namespace std;

string pName;
bool drawCard = true, winner = false, valid = false, goodInput = false,
     found;
void endGameMessage(string[], int i);
void PrintInstructions();
void checkInput(char &, int &);

int main() {
  srand(time(NULL)); // Seeding random number generator
  cout << "\033[" << ";" << "1" << "m" << "Welcome to UNO!" << "\033[m" << endl;
  PrintInstructions();
  cout << "Please enter your name to start: ";
  cin >> pName;
  cout << "Perfect! Setting up hands now..." << endl;
  Hand *Player = new Hand();
  Player->sortHand();
  Hand *CPU1 = new Hand();
  CPU1->sortHand();
  Hand *CPU2 = new Hand();
  CPU2->sortHand();
  Card *current = new Card(); // Creating the card in play
  current->newCard();         // Setting it to a random card
  while (current->getColor() == 'W') { // Making sure the first card isn't a wild card
    current->newCard();
  }
  cout << "The game is now set!" << endl << "Starting now..." << endl << endl;
  cout << "First Card: " << endl;
  current->printCard(); // prints the current card
  Hand hands[] = {*Player, *CPU1, *CPU2}; // Will make the for loop easier
  string names[] = {pName, "CPU1", "CPU2"};
  while (!winner) {
    for (int i = 0; i < 3; i++) {
      hands[i].sortHand();
      cout << endl << endl << "It is " << names[i] << "'s turn" << endl;
      //Player's Turn
      if (i == 0) { 
        cout << "Current Card: "; current->printCard(); cout << endl; 
        char tempColor; //user input of card Color
        char tempValue; //user input of card Value
        hands[i].printHand(true);
        cout << endl << "Select Card to Play: ";
        cin >> tempColor >> tempValue;
        tempValue = (static_cast<int>(tempValue) - 48); //avoiding inifnite loop
        found = false;
        if (tempColor == 'D') {
          hands[i].drawCard();
          cout << names[i] << " drew a ";
    (hands[i].getCard(hands[i].unplayedCards())).printCard(); // printing the card drawn
          found = true;  // avoid the "card not found" message
        } 
        else {
          for (int j = 0; j < hands[i].unplayedCards(); j++) { // looking at every card in hand
            if (tempColor == hands[i].getCardColor(j) && (tempValue == hands[i].getCardValue(j) || tempColor == 'W')) {// if Card is in hand
              if (hands[i].getCard(j+1) == *current) { // and if the card is the current card played
                hands[i].playCard(*current, j);   // play the card
                cout << names[i] << " played a "; // display message
                current->printCard();             // pring the current card
                found = true;
                break; // should break out of j-indexed for loop
              }
            }
          }
          if (found == false) {
            cout << "Card not found, drawing card instead..." << endl;
            hands[i].drawCard();
            cout << names[i] << " drew a ";
            (hands[i].getCard(hands[i].unplayedCards())).printCard(); // printing the card drawn
          }
        }
      }
      //CPU's Turn, if i == 1 or i == 2
      else { 
        drawCard = true; //will draw card unless found in the hand array
        // Look for card in hand that matches current
        for (int j = 0; j < hands[i].unplayedCards(); j++) {
          if (hands[i].getCard(j+1) == *current) { // Card is in hand
            hands[i].playCard(*current, j);
            cout << names[i] << " played a ";
            current->printCard();
            cout << endl;
            drawCard = false;
            break; //so two cards aren't selected
          }
        }
        if (drawCard) {
        hands[i].drawCard();
        cout << names[i] << " drew a card" << endl;
      }
      }
      if (i > 0) {
        hands[i].printHand(false); // Printing the CPU's hands- only the backs of the cards
      }
      if (hands[i].unplayedCards() == 1) {
        cout << endl << "\033[" << ";" << "1" << "m" << names[i] << " has UNO!" << "\033[m" << endl;
      } else if (hands[i].unplayedCards() == 0) {
        winner = true;
        endGameMessage(names, i);
        for (int t = 0; t < 3; t++) {
          cout << names[t] << ": " << hands[t].findScore();
          cout << endl;
        }
        cout << endl << "Thank you for playing UNO!" << endl;
        break; //should break out of for loop
      }
    }
  }
}

// Prints out the basic endgame information, to save space in main
void endGameMessage(string names[], int i) {
  cout << "\033["
       << ";"
       << "1"
       << "m" << names[i] << " won the game!"
       << "\033[m" << endl;
  cout << "Final Scores: " << endl;
}

/* Will check the initial user input to see if the color and value align with an
  actual card. If it doesn't, it will ask for the numbers until valid input is
  recieved */
void checkInput(char &tcolor, int &tvalue) {
  while (!goodInput) {
    if ((tcolor != 'B' || tcolor != 'Y' || tcolor != 'G' || tcolor != 'R') &&
        (tvalue > 0 && tvalue < 10)) {
      if (tcolor != 'W' && tvalue != 50) {
        if (tcolor != 'D') {
          cout << "Incorrect input- does not align to possible card. Please try again: ";
          cin >> tcolor >> tvalue;
          goodInput = false;
        }
      }
    }
    goodInput = true;
  }
}

/* Prints user Instructions at the beggining of the game- primary purpose is to
   clean up main*/
void PrintInstructions() {
  cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
  cout << "Here are the intructions: " << endl;
  cout << "When playing a card, first input the first letter of the color "
          "followed by the value"
       << endl;
  cout << "For example: B 5 (Blue 5)" << endl << "G 9 (Green 9)" << endl;
  cout << "To play a Wild card, enter W 50" << endl;
  cout << "To draw a card, input D 0" << endl;
  cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl
       << endl;
}