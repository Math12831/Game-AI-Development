#include <stdio.h>
#include <stdlib.h>
#include "Game.h"

// Given to us by project

// Game g  = newGame(..);
// Int currentPlayer = 0;
// While(getKPI(g, currentPlayer) < WIN_KPI) {
// diceValue = rollDice();
// throwDice(g, diceValue);
// action move = bestMove(g);
// While (move != PASS) {
// Assert(isLegal(g, move);
// If(move.actionCode == START_SPINOFF) {
// diveValue = rollDice();
// Decide
// }
// makeAction(g, move);
// }
// currentPlayer = nextPlayer(currentPlayer);
// }

#define WIN_KPI 150

int main (int argc, char *argv[]);

void getArray(int array[], int num);
int rollDice();
action getMove(Game g);

int main (int argc, char *argv[]) {
  int discipline[NUM_REGIONS];
  int dice[NUM_REGIONS];
  
  getArray(discipline, NUM_REGIONS);
  getArray(dice, NUM_REGIONS);
  
  Game g = newGame(discipline, dice);
  int currentPlayer = NO_ONE;
  int diceValue;
  while (getKPIpoints(g, currentPlayer) < WIN_KPI) {
    diceValue = rollDice();
    throwDice(g, diceValue);
    currentPlayer = getWhoseTurn(g);
    
    action move = getMove(g);
    while (move.actionCode != PASS){
      assert(isLegalAction(g, move));
      if (move.actionCode == START_SPINOFF) {
        diceValue = rollDice();
        if (diceValue <= 4 || dicevalue >= 10) { // Gives probability of 1/3
          move.actionCode = OBTAIN_IP_PATENT;
        } else {
          move.actionCode = OBTAIN_PUBLICATION;
        }
      }
      makeAction(g, move);
      move = getMove();
    }
  }
}

// Reads in an array of numbers
// into array[], of lenght num.
// Numbers must be comma separated
// with no whitespace.
void getArray(int array[], int num) {
  int i = 0;
  while (i < num) {
    scanf("%d,", &array[i]);
    i++;
  }
  return;
}

int rollDice() {
  int random;
  scanf("%d", &random);
  return random;
}

action getMove(Game g) {
  action move;
  // TODO: Write getMove
  return move;
}
