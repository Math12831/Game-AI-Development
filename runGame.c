#include <stdio.h>
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

int main (int argc, char *argv[]) {
  int discipline[NUM_REGIONS];
  int dice[NUM_REGIONS];
  
  getArray(discipline, NUM_REGIONS);
  getArray(dice, NUM_REGIONS);
  
  Game g = newGame(discipline, dice);
  while (getKPIpoints(Game g, int player) < WIN_KPI) {
    // TODO: Add loop body
    
  }
}

// Reads in an array of numbers 
void getArray(int array[], int num) {
  int i = 0;
  while (i < num) {
    scanf("%d,", &array[i]);
    i++;
  }
  return;
}
