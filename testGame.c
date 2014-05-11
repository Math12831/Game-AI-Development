/*
/*
 *  testGame.c
 *
 *  Created by Nicholas Pizzino on 30/04/14.
 *  Update 1.0 (Missing Decleration Of Variables/Data)
 *  Update 1.1 (Included Some Basic Tests)
 *  Update 1.2 (Included Basic Tests And Legal Moves Tests)
 *
 */

#include "Game.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void testBasics();

// 1. Is there a campus on this vertex?
// *Implimented*
int getCampus(Game g, path pathToVertex);

// 2. Whose turn is it?
// *Implimented*
int getWhoseTurn (Game g);

// 3. Who owns this arc?
// *Implimented*
int getARC(Game g, path pathToEdge);

// 4. What dice value produces students in the specified region?
// *Implimented*
int getDiceValue (Game g, int regionID);

// 5. What students are produced by the discipline?
// *Implimented*
int getDiscipline (Game g, int regionID);

// 6. Who has the most arcs?
// *Implimented*
int getMostARCs (Game g);

// 7. Who has the most publications?
// *Implimented*
int getMostPublications (Game g);

// 8. Does Player X have Y arcs, where X and Y are provided integral variables.
// *Implimented*
int getARCs (Game g, int player);

// 9. Does Player X have Y publications, where X and Y are provided integral variables.
// *Implimented*
int getPublications (Game g, int player);

// 10. What is the turn number?
// *Implimented*
int getTurnNumber (Game g);

// 11. Does Player X have Y KPI Points, where X and Y are given integral variables.
// *Implimented*
int getKPIpoints (Game g, int player);

// 12. Does Player X have Y IPs, where X and Y are given integral variables.
// *Implimented*
int getIPs (Game g, int player);

// 13. Does Player X have Y students, where X and Y are given integral variables.
// *Implimented*
int getStudents (Game g, int player, int discipline);

// 14. Is this the correct exchange rate if the player were to go from Discipline X to Discipline Y, where X and Y are given variables.
// *Implimented*
int getExchangeRate (Game g, int player,
                     int disciplineFrom, int disciplineTo);

// 15. Does Player X have Y campuses, where X and Y are given integral variables.
// *Implimented*
int getCampuses (Game g, int player);

// 16. Does Player X have Y upgraded G08 campuses, where X and Y are given integral variables.
// *Implimented*
int getGO8s (Game g, int player);

// Legal Action Testing

// 1. Is this a valid arc construction?
// 2. Does this move go to a vacant vertex?
// 3. Can we place a Campus on this vertex?
// 4. Can we upgrade this vertex to a G08?
// 5. Does the player have the 4 required students to pay for that campus?
// *Implimented*
int isLegalAction (Game g, action a);

int main(int argc, char * argv[]) {
    assert (NUM_REGIONS == 19);
    assert (PATH_LIMIT == 150);
    testBasics();
    printf("You have passed the Basics!");
    printf("You have passed the Legal Move Testing!");
    printf("All Tests Passed, You Are Awesome!");
}

void testBasics() {
    
    int discipline[] = {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, STUDENT_MTV, STUDENT_BPS, STUDENT_MTV, STUDENT_BQN, STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS};
    int dice[] = {9,10,8,12,6,5,3,11,3,11,4,6,4,12,9,2,8,10,5};
    int diceNumber = 0;
    Game g = newGame (discipline, dice);
    action a;
    
    // First Move
    // 1. Is there a campus on this vertex?
    // 2. Whose turn is it?
    // 4. What dice value produces students in the specified region?
    // 5. What students are produced by the discipline?
    // 6. Who has the most arcs?
    // 7. Who has the most publications?
    // 8. Does Player X have Y arcs, where X and Y are provided integral variables.
    // 9. Does Player X have Y publications, where X and Y are provided integral variables.
    // 10. What is the turn number?
    // 11. Does Player X have Y KPI Points, where X and Y are given integral variables.
    // 12. Does Player X have Y IPs, where X and Y are given integral variables.
    // 13. Does Player X have Y students, where X and Y are given integral variables.
    // 14. Is this the correct exchange rate if the player were to go from Discipline X to Discipline Y, where X and Y are given variables.
    // 15. Does Player X have Y campuses, where X and Y are given integral variables.
    // 16. Does Player X have Y upgraded G08 campuses, where X and Y are given integral variables.
    assert (getWhoseTurn(g) == NO_ONE);
    assert (getMostARCs(g) == NO_ONE);
    assert (getCampuses(g, UNI_A) == 0);
    assert (getCampuses(g, UNI_B) == 0);
    assert (getCampuses(g, UNI_C) == 0);
    assert (getGO8s(g, UNI_A) == 0);
    assert (getGO8s(g, UNI_B) == 0);
    assert (getGO8s(g, UNI_C) == 0);
    assert (getTurnNumber(g) == NO_ONE);
    assert (getStudents(g, UNI_A, STUDENT_BPS) == 3);
    assert (getStudents(g, UNI_A, STUDENT_BQN) == 3);
    assert (getStudents(g, UNI_A, STUDENT_MTV) == 1);
    assert (getStudents(g, UNI_A, STUDENT_MJ) == 1);
    assert (getStudents(g, UNI_A, STUDENT_MMONEY) == 1);
    assert (getStudents(g, UNI_A, STUDENT_THD) == 1);
    assert (getKPIpoints(g, UNI_A) == 20);
    assert (getKPIpoints(g, UNI_B) == 20);
    assert (getKPIpoints(g, UNI_C) == 20);
    assert (getARCs(g, UNI_A) == 0);
    assert (getARCs(g, UNI_B) == 0);
    assert (getARCs(g, UNI_C) == 0);
    
    while (diceNumber < 19) {
        assert (getDiceValue(g, diceNumber) == dice[diceNumber]);
        diceNumber ++;
    }
    diceNumber = 0;
    while (diceNumber < 19) {
        assert (getDiscipline(g, diceNumber) == discipline[diceNumber]);
        diceNumber ++;
    }
    
    assert (getMostPublications(g) == NO_ONE);
    assert (getPublications(g, UNI_A) == 0);
    assert (getPublications(g, UNI_B) == 0);
    assert (getPublications(g, UNI_C) == 0);
    assert (getIPs(g, UNI_A) == 0);
    assert (getIPs(g, UNI_B) == 0);
    assert (getIPs(g, UNI_C) == 0);
    
    char *path = "";
    a.actionCode = 0;
    assert (isLegalAction(g, a) == FALSE);
    a.actionCode = 3;
    strcpy(path, "L");
    strcpy(a.destination, path);
    assert (isLegalAction(g, a) == FALSE);
    a.actionCode = 1;
    strcpy(path, "LR");
    strcpy(a.destination, path);
    assert (isLegalAction(g, a) == FALSE);
    
    throwDice(g, 2);
    assert (getTurnNumber(g) == 0);
    assert (getWhoseTurn(g) == UNI_A);
    a.actionCode = 0;
    assert (isLegalAction (g, a));
    makeAction(g, a);
    assert (getCampus(g, path) == CAMPUS_A);
    strcpy(path, "RBRBRBRBRBLBLBLBLB");
    assert (getCampus(g, path) == CAMPUS_A);
    strcpy(path, "RRLRL");
    assert (getCampus(g, path) == CAMPUS_B);
    
    assert (getStudents(g, UNI_B, STUDENT_BPS) == 3);
    assert (getStudents(g, UNI_B, STUDENT_BQN) == 3);
    assert (getStudents(g, UNI_B, STUDENT_MTV) == 1);
    assert (getStudents(g, UNI_B, STUDENT_MJ) == 1);
    assert (getStudents(g, UNI_B, STUDENT_MMONEY) == 1);
    assert (getStudents(g, UNI_B, STUDENT_THD) == 1);
    
    throwDice(g, 2);
    assert (getWhoseTurn(g) == UNI_B);
    assert (isLegalAction (g, a));
    makeAction(g, a);
    strcpy(path, "RLRLR");
    assert (getCampus(g, path) == VACANT_VERTEX);
    strcpy(path, "RLRLRLLRLRLLL");
    assert (getCampus(g, path) == CAMPUS_A);
    
    assert (getStudents(g, UNI_C, STUDENT_BPS) == 3);
    assert (getStudents(g, UNI_C, STUDENT_BQN) == 3);
    assert (getStudents(g, UNI_C, STUDENT_MTV) == 1);
    assert (getStudents(g, UNI_C, STUDENT_MJ) == 1);
    assert (getStudents(g, UNI_C, STUDENT_MMONEY) == 1);
    assert (getStudents(g, UNI_C, STUDENT_THD) == 1);
    
    throwDice(g, 2);
    assert (getWhoseTurn(g) == UNI_C);
    assert (isLegalAction (g, a));
    makeAction(g, a);
    strcpy(path, "LRLRL");
    assert (getCampus(g, path) == CAMPUS_C);
    strcpy(path, "RRLRL");
    assert (getCampus(g, path) == CAMPUS_B);
    strcpy(path, "RRLRLLRLRL");
    assert (getCampus(g, path) == CAMPUS_C);
    
    // Second Move
    // 3. Who owns this arc?
    assert (getMostARCs(g) == NO_ONE);
    assert (getWhoseTurn(g) == UNI_A);
    
    throwDice(g, 2);
    a.actionCode = 3;
    strcpy(path, "L");
    strcpy(a.destination, path);
    assert (isLegalAction (g, a));
    makeAction(g, a);
    assert (getARC(g, path) == ARC_A);
    assert (getCampus(g, path) == VACANT_VERTEX);
    assert (getMostARCs(g) == UNI_A);
    assert (getKPIpoints(g, UNI_A) == 22);
    
    throwDice(g, 2);
    assert (getWhoseTurn(g) == UNI_B);
    strcpy(path, "RRLR");
    strcpy(a.destination, path);
    assert (isLegalAction (g, a));
    makeAction(g, a);
    assert (getARC(g, path) == ARC_B);
    assert (getCampus(g, path) == VACANT_VERTEX);
    strcpy(path, "L");
    assert (getARC(g, path) == ARC_A);
    assert (getKPIpoints(g, UNI_B) == 22);
    
    throwDice(g, 2);
    assert (getWhoseTurn(g) == UNI_C);
    strcpy(path, "RLRLRLRRL");
    strcpy(a.destination, path);
    assert (isLegalAction (g, a));
    makeAction(g, a);
    assert (getARC(g, path) == ARC_C);
    assert (getCampus(g, path) == VACANT_VERTEX);
    strcpy(path, "L");
    assert (getARC(g, path) == ARC_A);
    strcpy(path, "RRLR");
    assert (getARC(g, path) == ARC_B);
    assert (getKPIpoints(g, UNI_C) == 22);
    
    assert (getARCs(g, UNI_A) == 1);
    assert (getARCs(g, UNI_B) == 1);
    assert (getARCs(g, UNI_C) == 1);
    
    // Third Move
    assert (getCampuses(g, UNI_A) == 0);
    assert (getCampuses(g, UNI_B) == 0);
    assert (getCampuses(g, UNI_C) == 0);
    
    throwDice(g, 2);
    strcpy(path, "LR");
    strcpy(a.destination, path);
    assert (isLegalAction (g, a));
    makeAction(g, a);
    assert (getARC(g, path) == ARC_A);
    assert (getCampus(g, path) == VACANT_VERTEX);
    strcpy(path, "L");
    assert (getARC(g, path) == ARC_A);
    assert (getCampus(g, path) == VACANT_VERTEX);
    assert (getMostARCs(g) == UNI_A);
    assert (getCampuses(g, UNI_A) == 1);
    assert (getKPIpoints(g, UNI_A) == 24);
    
    throwDice(g, 2);
    strcpy(path, "RL");
    strcpy(a.destination, path);
    assert (isLegalAction (g, a) == FALSE);
    
    strcpy(path, "RRL");
    strcpy(a.destination, path);
    assert (isLegalAction (g, a));
    makeAction(g, a);
    assert (getARC(g, path) == ARC_B);
    assert (getCampus(g, path) == VACANT_VERTEX);
    strcpy(path, "RRLR");
    assert (getARC(g, path) == ARC_B);
    assert (getCampus(g, path) == VACANT_VERTEX);
    strcpy(path, "LR");
    assert (getARC(g, path) == ARC_A);
    assert (getCampuses(g, UNI_B) == 1);
    assert (getKPIpoints(g, UNI_B) == 24);
    
    throwDice(g, 2);
    strcpy(path, "RLRLRLRR");
    strcpy(a.destination, path);
    assert (isLegalAction (g, a));
    makeAction(g, a);
    assert (getARC(g, path) == ARC_C);
    assert (getCampus(g, path) == VACANT_VERTEX);
    strcpy(path, "RLRLRLRRL");
    assert (getARC(g, path) == ARC_C);
    assert (getCampus(g, path) == VACANT_VERTEX);
    strcpy(path, "LR");
    assert (getARC(g, path) == ARC_A);
    strcpy(path, "RRL");
    assert (getARC(g, path) == ARC_B);
    assert (getCampuses(g, UNI_C) == 1);
    assert (getKPIpoints(g, UNI_C) == 24);
    
    assert (getARCs(g, UNI_A) == 2);
    assert (getARCs(g, UNI_B) == 2);
    assert (getARCs(g, UNI_C) == 2);
    
    a.actionCode = 3;
    strcpy(path, "LRR");
    strcpy(a.destination, path);
    assert (isLegalAction(g, a) == FALSE);
    
    // Fourth Move
    assert (getGO8s(g, UNI_A) == 0);
    assert (getGO8s(g, UNI_B) == 0);
    assert (getGO8s(g, UNI_C) == 0);
    
    throwDice(g, 2);
    a.actionCode = 1;
    strcpy(path, "RL");
    strcpy(a.destination, path);
    assert (isLegalAction (g, a));
    makeAction(g, a);
    assert (getCampus(g, path) == CAMPUS_A);
    assert (getARC(g, path) == ARC_A);
    assert (getKPIpoints(g, UNI_A) == 34);
    
    throwDice(g, 2);
    strcpy(path, "RRL");
    strcpy(a.destination, path);
    assert (isLegalAction (g, a));
    makeAction(g, a);
    assert (getCampus(g, path) == CAMPUS_B);
    assert (getARC(g, path) == ARC_B);
    strcpy(path, "RL");
    assert (getCampus(g, path) == CAMPUS_A);
    assert (getKPIpoints(g, UNI_B) == 34);
    
    throwDice(g, 7);
    strcpy(path, "RLRLRLRR");
    strcpy(a.destination, path);
    assert (isLegalAction (g, a));
    makeAction(g, a);
    assert (getCampus(g, path) == CAMPUS_C);
    assert (getARC(g, path) == ARC_C);
    strcpy(path, "RL");
    assert (getCampus(g, path) == CAMPUS_A);
    strcpy(path, "RRL");
    assert (getCampus(g, path) == CAMPUS_B);
    assert (getKPIpoints(g, UNI_A) == 34);
    
    assert (getStudents(g, UNI_A, STUDENT_BPS) == 0);
    assert (getStudents(g, UNI_A, STUDENT_BQN) == 0);
    assert (getStudents(g, UNI_A, STUDENT_MTV) == 0);
    assert (getStudents(g, UNI_A, STUDENT_MJ) == 0);
    assert (getStudents(g, UNI_A, STUDENT_MMONEY) == 0);
    assert (getStudents(g, UNI_A, STUDENT_THD) == 2);
    assert (getStudents(g, UNI_B, STUDENT_THD) == 2);
    assert (getStudents(g, UNI_C, STUDENT_THD) == 2);
    
    a.actionCode = 2;
    strcpy(path, "LR");
    strcpy(a.destination, path);
    assert (isLegalAction(g, a) == FALSE);
    strcpy(path, "RRL");
    strcpy(a.destination, path);
    assert (isLegalAction(g, a) == FALSE);
    strcpy(path, "RLRLRLRR");
    strcpy(a.destination, path);
    assert (isLegalAction(g, a) == FALSE);
    
}
