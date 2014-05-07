/*
 *  testGame.c
 *
 *  Created by Nicholas Pizzino on 30/04/14.
 *  Update 1.0 (Missing Decleration Of Variables/Data)
 *  Update 1.1 (Included Basic Tests)
 *
 */

#import "Game.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void testBasics();
void testLegalMoves();

// 2. Is there an upgraded campus on this vertex?
int getCampus(Game g, path pathToVertex);

// 3. Whose turn is it?
int getWhoseTurn (Game g);

// 4. Who owns this arc?
int getARC(Game g, path pathToEdge);

// 5. What is the Dice Value of this turn?
int getDiceValue (Game g, int regionID);

// 6. What is the discipline of this face?
int getDiscipline (Game g, int regionID);

// 7. Who has the most arcs?
int getMostARCs (Game g);

// 8. Who has the most publications?
int getMostPublications (Game g);

// 9. Does Player X have Y arcs, where X and Y are provided integral variables.
int getARCs (Game g, int player);

// 10. Does Player X have Y publications, where X and Y are provided integral variables.
int getPublications (Game g, int player);

// 11. What is the turn number?
int getTurnNumber (Game g);

// 12. Does Player X have Y KPI Points, where X and Y are given integral variables.
int getKPIpoints (Game g, int player);

// 13. Does Player X have Y IPs, where X and Y are given integral variables.
int getIPs (Game g, int player);

// 14. Does Player X have Y students, where X and Y are given integral variables.
int getStudents (Game g, int player, int discipline);

// 15. Is this the correct exchange rate if the player were to go from Discipline X to Discipline Y, where X and Y are given variables.
int getExchangeRate (Game g, int player,
                     int disciplineFrom, int disciplineTo);

// 16. Does Player X have Y campuses, where X and Y are given integral variables.
int getCampuses (Game g, int player);

// 17. Does Player X have Y upgraded G08 campuses, where X and Y are given integral variables.
int getGO8s (Game g, int player);

// Legal Action Testing

// 1. Is this a valid arc construction?
// 2. Does this move go to a vacant vertex?
// 3. Can we place a Campus on this vertex?
// 4. Can we upgrade this vertex to a G08?
// 5. Does the player have the 4 required students to pay for that campus?
int isLegalAction (Game g, action a);

int main(int argc, char * argv[]) {
    testBasics();
    printf("You have passed the Basics!");
    testLegalMoves();
    printf("You have passed the Legal Move Testing!");
    printf("All Tests Passed, You Are Awesome!");
}

void testBasics() {
    
    int discipline[] = {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV,STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN, STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS};
    int dice[] = {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5};
    
    Game g = newGame (discipline, dice);
    
    char *path = "RB";
    
    // 1. Is there a campus on this vertex?
    assert (getCampus(g, path) == TRUE);
    assert (getCampus(g, path) == TRUE);
    assert (getCampus(g, path) == TRUE);
    assert (getCampus(g, path) == TRUE);
    assert (getCampus(g, path) == TRUE);
}
