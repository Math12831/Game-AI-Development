#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "Game.h"

#define WIN_KPI 150

int main (int argc, char *argv[]);

void getArray(int array[], int num);
int rollDice();
action getMove();
void printGame(Game g);

int main (int argc, char *argv[]) {
  int discipline[NUM_REGIONS];
  int dice[NUM_REGIONS];
  
  printf("Enter the discipline codes of the regions: ");
  getArray(discipline, NUM_REGIONS);
  printf("Enter the dice values of the regions: ");
  getArray(dice, NUM_REGIONS);
  
  Game g = newGame(discipline, dice);
  int currentPlayer = NO_ONE;
  int diceValue;
  while (getKPIpoints(g, currentPlayer) < WIN_KPI) {
    diceValue = rollDice();
    throwDice(g, diceValue);
    currentPlayer = getWhoseTurn(g);
    printGame(g);
    
    action move = getMove(g);
    while (move.actionCode != PASS){
      assert(isLegalAction(g, move) == TRUE);
      if (move.actionCode == START_SPINOFF) {
        diceValue = rollDice();
        if (diceValue <= 4 || diceValue >= 10) { // Gives probability of 1/3
          move.actionCode = OBTAIN_IP_PATENT;
        } else {
          move.actionCode = OBTAIN_PUBLICATION;
        }
      }
      makeAction(g, move);
      move = getMove();
    }
  }
  
  return EXIT_SUCCESS;
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
  printf("Enter the dice roll: ");
  scanf("%d", &random);
  return random;
}

action getMove() {
  action move;
  char currentMove[24];
  
  int valid = FALSE;
  while (valid != TRUE) {
    printf("Enter the action code to perform: ");
    scanf("%s", currentMove);
    
    if (strcmp(currentMove, "PASS") == 0) {
      move.actionCode = PASS;
      valid = TRUE;
      
    } else if (strcmp(currentMove, "BUILD_CAMPUS") == 0) {
      move.actionCode = BUILD_CAMPUS;
      printf("Enter the location in path format: ");
      scanf("%s", move.destination);
      valid = TRUE;
      
    } else if (strcmp(currentMove, "BUILD_GO8") == 0) {
      move.actionCode = BUILD_GO8;
      printf("Enter the location in path format: ");
      scanf("%s", move.destination);
      valid = TRUE;
      
    } else if (strcmp(currentMove, "OBTAIN_ARC") == 0) {
      move.actionCode = OBTAIN_ARC;
      printf("Enter the location in path format: ");
      scanf("%s", move.destination);
      valid = TRUE;
      
    } else if (strcmp(currentMove, "START_SPINOFF") == 0) {
      move.actionCode = START_SPINOFF;
      valid = TRUE;
      
    } else if (strcmp(currentMove, "RETRAIN_STUDENTS") == 0) {
      move.actionCode = RETRAIN_STUDENTS;
      printf("Enter the discipline number to convert from: ");
      scanf("%d", &(move.disciplineFrom));
      printf("Enter the discipline number to convert from: ");
      scanf("%d", &(move.disciplineTo));
      valid = TRUE;
      
    } else {
      printf("Action not valid!\n");
      
    }
    
  }
  
  return move;
}

void printGame(Game g) {
  int currentPlayer = getWhoseTurn(g);
  printf("It is the turn of player %d\n", currentPlayer);
  printf("They have %d KPI points\n", getKPIpoints(g, currentPlayer));
  printf("They have %d ARCs\n", getARCs(g, currentPlayer));
  printf("They have %d GO8s\n", getGO8s(g, currentPlayer));
  printf("They have %d campuses\n", getCampuses(g, currentPlayer));
  printf("They have %d IPs\n", getIPs(g, currentPlayer));
  printf("They have %d publications\n", getPublications(g, currentPlayer));
  printf("They have %d ThDs, %d BPSs, %d B?s, %d MJs, %d MTVs and %d M$s",
          getStudents(g, currentPlayer, STUDENT_THD), getStudents(g, currentPlayer, STUDENT_BPS),
          getStudents(g, currentPlayer, STUDENT_BQN), getStudents(g, currentPlayer, STUDENT_MJ),
          getStudents(g, currentPlayer, STUDENT_MTV), getStudents(g, currentPlayer, STUDENT_MMONEY));
  
  return;
}
