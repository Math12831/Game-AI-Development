/*
 *  testGame.c
 *
 *  Created by Nicholas Pizzino on 30/04/14.
 *  Update 1.0 (Missing Decleration Of Variables/Data)
 *
 */

#import "game.c"

#define NUM_UNIS 3

// Player ID of each university
#define NO_ONE 0
#define UNI_A 1
#define UNI_B 2
#define UNI_C 3

// Contents of an ARC
#define VACANT_ARC 0
#define ARC_A 1
#define ARC_B 2
#define ARC_C 3

// Contents of a VERTEX
#define VACANT_VERTEX 0  
#define CAMPUS_A 1
#define CAMPUS_B 2
#define CAMPUS_C 3
#define GO8_A 4
#define GO8_B 5
#define GO8_C 6

// Action Codes
#define PASS 0
#define BUILD_CAMPUS 1
#define BUILD_GO8 2
#define OBTAIN_ARC 3
#define START_SPINOFF 4
#define OBTAIN_PUBLICATION 5
#define OBTAIN_IP_PATENT 6
#define RETRAIN_STUDENTS 7

// Disciplines
#define STUDENT_THD 0
#define STUDENT_BPS 1
#define STUDENT_BQN 2
#define STUDENT_MJ  3
#define STUDENT_MTV 4
#define STUDENT_MMONEY 5

#define NUM_REGIONS 19
#define PATH_LIMIT 150

#define TRUE 1
#define FALSE 0


typedef struct _game * Game;

// 1. Is there a campus on this vertex?
int getCampus(Game g, path pathToVertex);

// 2. Is there an upgraded campus on this vertex?
int getGO8s(Game g, path pathToVertex);

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
    assert (getCampus(g, 0) == TRUE);
    assert (getCampus(g, RD0) == TRUE);
    assert (getCampus(g, R0) == FALSE);
    assert (getCampus(g, RDDLDD0) == TRUE);
    assert (getCampus(g, DD0) == TRUE);
    
    assert (getGO8s (g, 0) == TRUE);
    assert (getGO8s (g, RD0) == FALSE);
    assert (getGO8s (g, RDDLDD0) == TRUE);
    assert (getGO8s (g, DDDDDD0) == TRUE);
    assert (getGO8s (g, RRRRDDRRDD0) == TRUE);
    
    printf("All tests passed, you are Awesome!");
}
