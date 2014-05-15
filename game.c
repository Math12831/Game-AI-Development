//CHECK OFF-BY-ONE ERRORS!

#include <stdlib.h>

#include "Game.h"

#define NUM_VERTICES 54
#define NUM_ARCS 72

#define NEIGHBOURS_PER_REGION 6
#define NEIGHBOURS_PER_VERTEX 3
#define NEIGHBOURS_PER_ARC 2

#define NUM_STUDENT_TYPES 6

#define INITIAL_THD 0
#define INITIAL_BPS 3
#define INITIAL_BQN 3
#define INITIAL_MJ  1
#define INITIAL_MTV 1
#define INITIAL_MMONEY 1

#define REGION_COLUMNS 5
#define VERTEX_COLUMNS 16

#define NULL_VERTEX -1
#define NULL_REGION -1
#define NULL_ARC -1

#define REGION_START {3, 2, 1, 2, 3}
#define REGION_HEIGHT {3, 4, 5, 4, 3}

//Stores the neighbours of a region - not all parts may be necessary
typedef struct _region {
    int regions[NEIGHBOURS_PER_REGION];
    int arcs[NEIGHBOURS_PER_REGION];
    int vertices[NEIGHBOURS_PER_REGION];
} region;

//Stores the neighbours of an arc - not all parts may be necessary
typedef struct _arc {
    int vertices[NEIGHBOURS_PER_ARC];
    int regions[NEIGHBOURS_PER_ARC];
} arc;

//Stores the neighbours of a vertex - not all parts may be necessary
typedef struct _vertex {
    int arcs[NEIGHBOURS_PER_VERTEX];
    int vertices[NEIGHBOURS_PER_VERTEX];
    int regions[NEIGHBOURS_PER_VERTEX];
} vertex;

typedef struct _game {
    //Game states
    int turn, mostPublications, mostArcs;
    
    //Player attributes
    int numStudents[NUM_UNIS][NUM_STUDENT_TYPES];  //This is a 2-D array
    int numKpiPoints[NUM_UNIS];
    int numCampuses[NUM_UNIS];
    int numGo8s[NUM_UNIS];
    int numArcs[NUM_UNIS];
    int numIps[NUM_UNIS];
    int numPublications[NUM_UNIS];
    
    //Contents
    int regionDiscipline[NUM_REGIONS];
    int regionDice[NUM_REGIONS];
    int vertexContents[NUM_VERTICES];
    int arcContents[NUM_ARCS];
    
    //Neighbours
    region regionNeighbours[NUM_REGIONS];  //What are the neighbours of each region?
    arc arcNeighbours[NUM_ARCS];                                           // arc?
    vertex vertexNeighbours[NUM_VERTICES];                                 // vertex?
} game;

//Helper functions
//I am not sure whether I have these correct
int vertexNum (int row, int column);    //Do this
int regionNum (int row, int column);    //Do this

//Add 1 - go left
//Subtract 1 - go right
//Check this works - for next function as well
int getVertex (Game g, path pathToVertex) {
    char* i = pathToVertex;
    int currentVertex = 0;
    int direction = 0;
    while (*i != 0) {
        vertex* neighbours = &g->vertexNeighbours[currentVertex];
        if (*i == 'L') {
            direction++;
        } else if (*i == 'R') {
            direction--;
        }
        currentVertex = neighbours->vertices[direction % NEIGHBOURS_PER_VERTEX];
        i++;
    }
    return currentVertex;
}

int getEdge (Game g, path pathToEdge) {
    char* i = pathToEdge;
    int currentVertex = 0;
    int currentEdge;
    int direction = 0;
    while (*i != 0) {
        vertex* neighbours = &g->vertexNeighbours[currentVertex];
        if (*i == 'L') {
            direction++;
        } else if (*i == 'R') {
            direction--;
        }
        currentVertex = neighbours->vertices[direction % NEIGHBOURS_PER_VERTEX];
        currentEdge = neighbours->arcs[direction % NEIGHBOURS_PER_VERTEX];
        i++;
    }
    return currentEdge;
}

void initaliseRegionNeighbours (Game g) {
    int row, col, currentRegion;
    int colStart[] = {3, 2, 1, 2, 3};
    int colEnd[] = {7, 8, 9, 8, 7};
    col = 0;
    while (col < REGION_COLUMNS) {
        row = colStart[col];
        while (row <= colEnd[col]) {
            currentRegion = regionNum(row, col);
            
            //Regions
            g->regionNeighbours[currentRegion].regions[0] = regionNum(row - 2, col);
            g->regionNeighbours[currentRegion].regions[1] = regionNum(row - 1, col + 1);
            g->regionNeighbours[currentRegion].regions[2] = regionNum(row + 1, col + 1);
            g->regionNeighbours[currentRegion].regions[3] = regionNum(row + 2, col);
            g->regionNeighbours[currentRegion].regions[4] = regionNum(row + 1, col - 1);
            g->regionNeighbours[currentRegion].regions[5] = regionNum(row - 1, col - 1);
            
            //Arcs
            
            //Vertices
            g->regionNeighbours[currentRegion].vertices[0] = vertexNum(row - 1, col * 3 + 2);
            g->regionNeighbours[currentRegion].vertices[1] = vertexNum(row, col * 3 + 3);
            g->regionNeighbours[currentRegion].vertices[2] = vertexNum(row + 1,  col * 3 + 2);
            g->regionNeighbours[currentRegion].vertices[3] = vertexNum(row + 1,  col * 3 + 1);
            g->regionNeighbours[currentRegion].vertices[4] = vertexNum(row,  col);
            g->regionNeighbours[currentRegion].vertices[5] = vertexNum(row - 1,  col * 3 + 1);
            
            row += 2;
        }
        col++;
    }
}

//Finish this
void initaliseVertexNeighbours (Game g) {
    int row, col, currentVertex;
    int colStart[];  //Do this
    int colEnd[];    //Do this
    col = 0;
    while (col < VERTEX_COLUMNS) {
        row = colStart[col];
        while (row <= colEnd[col]) {
            currentVertex = vertexNum(row, col);
            
            if (col % 2 == 0) {
                //Regions
                g->vertexNeighbours[currentVertex].vertices[0] = regionNum(row, (col + 1) / 3);
                g->vertexNeighbours[currentVertex].vertices[1] = regionNum(row + 1, (col - 1) / 3);
                g->vertexNeighbours[currentVertex].vertices[2] = regionNum(row - 1, (col - 1) / 3);
                
                //Arcs
                
                //Vertices
                g->vertexNeighbours[currentVertex].vertices[0] = vertexNum(row, col + 1);
                g->vertexNeighbours[currentVertex].vertices[1] = vertexNum(row + 1, col - 1);
                g->vertexNeighbours[currentVertex].vertices[2] = vertexNum(row - 1, col - 1);
            } else {
                //Regions
                g->vertexNeighbours[currentVertex].vertices[0] = regionNum(row, (col + 1) / 3);
                g->vertexNeighbours[currentVertex].vertices[1] = regionNum(row + 1, (col + 1) / 3);
                g->vertexNeighbours[currentVertex].vertices[2] = regionNum(row - 1, (col - 1) / 3);
                
                //Arcs
                
                //Vertices
                g->vertexNeighbours[currentVertex].vertices[0] = vertexNum(row - 1, col + 1);
                g->vertexNeighbours[currentVertex].vertices[1] = vertexNum(row + 1, col + 1);
                g->regionNeighbours[currentVertex].vertices[2] = vertexNum(row, col - 1);
            }
            
            row += 2;
        }
        col++;
    }
}

//Finish this
void initaliseArcNeighbours (Game g) {
}

void initaliseNeighbours (Game g) {
    initialiseRegionNeighbours(g);
    initialiseVertexNeighbours(g);
    initialiseArcNeighbours(g);
}

void inititaliseContents(Game g, int discipline[], int dice[]) {
    int i = 0;
    while (i < NUM_REGIONS) {
        g->regionDiscipline[i] = discipline[i];
        g->regionDice[i] = dice[i];
        i++;
    }
    i = 0;
    while (i < NUM_ARCS) {
        g->arcContents[i] = VACANT_ARC;
        i++;
    }
    i = 0;
    while (i < NUM_VERTICES) {
        g->vertexContents[i] = VACANT_VERTEX;
        i++;
    }
}

void initialiseStudents(Game g) {
    int i = 0;
    while (i < NUM_UNIS) {
        g->numStudents[i][STUDENT_THD] = INITIAL_THD;
        g->numStudents[i][STUDENT_BPS] = INITIAL_BPS;
        g->numStudents[i][STUDENT_BQN] = INITIAL_BQN;
        g->numStudents[i][STUDENT_MJ] = INITIAL_MJ;
        g->numStudents[i][STUDENT_MTV] = INITIAL_MTV;
        g->numStudents[i][STUDENT_MMONEY] = INITIAL_MMONEY;
        i++;
    }
}

//Setters
Game newGame (int discipline[], int dice[]) {
    //Allocate game
    Game g = malloc(sizeof(game));
    
    //Initialise variables
    g->turn = -1;
    g->mostArcs = NO_ONE;
    g->mostPublications = NO_ONE;
    
    initialiseContents(g, discipline, dice);
    initialiseStudents(g);
    initialiseNeighbours(g);
    
    //Do things
    
    return g;
}


void disposeGame (Game g) {
    free(g);
    //Do more things?
}

// TODO: Increase KPI
void makeAction(Game g, action a) {
    int turn = getWhoseTurn(g);
    if (a.actionCode == BUILD_CAMPUS) {
        g->numCampuses[turn]++;
        g->numKpiPoints[turn] += 10;
        g->vertexContents[getVertex(g, a.destination)] = turn;
        g->numStudents[turn][STUDENT_BPS]--;
        g->numStudents[turn][STUDENT_BQN]--;
        g->numStudents[turn][STUDENT_MJ]--;
        g->numStudents[turn][STUDENT_MTV]--;
    } else if (a.actionCode == BUILD_GO8) {
        g->numGo8s[turn]++;
        g->numKpiPoints[turn] += 10;
        g->vertexContents[getVertex(g, a.destination)] += NUM_UNIS;
        g->numStudents[turn][STUDENT_MJ] -= 2;
        g->numStudents[turn][STUDENT_MMONEY] -= 3;
    } else if (a.actionCode == OBTAIN_ARC) {
        g->numArcs[turn]++;
        g->numKpiPoints[turn] += 2;
        g->arcContents[getEdge(g, a.destination)] = turn;
        g->numStudents[turn][STUDENT_BPS]--;
        g->numStudents[turn][STUDENT_BQN]--;
    } else if (a.actionCode == OBTAIN_PUBLICATION) {
        g->numPublications[turn]++;
        g->numKpiPoints[turn] += 10;
        g->numStudents[turn][STUDENT_MJ]--;
        g->numStudents[turn][STUDENT_MTV]--;
        g->numStudents[turn][STUDENT_MMONEY]--;
    } else if (a.actionCode == OBTAIN_IP_PATENT) {
        g->numIps[turn]++;
        g->numKpiPoints[turn] += 10;
        g->numStudents[turn][STUDENT_MJ]--;
        g->numStudents[turn][STUDENT_MTV]--;
        g->numStudents[turn][STUDENT_MMONEY]--;
    }
}

void throwDice (Game g, int diceScore) {
    int i, j;
    
    // Advance game by turn
    g->turn++;
    
    //Increase students
    i = 0;
    while (i < NUM_REGIONS) {
        //If this region's number has been rolled
        if (g->regionDice[i] == diceScore) {
            j = 0;
            while (j < NEIGHBOURS_PER_REGION) {
                //If this vertex contains a campus
                int v_contents = g->vertexContents[g->regionNeighbours[i].vertices[j]];
                if (v_contents != VACANT_VERTEX) {
                    //Increase the number of students at that university
                    g->numStudents[(v_contents % NUM_UNIS) - 1][i]++;
                }
                j++;
            }
        }
        i++;
    }
    
    //Change students
    if (diceScore == 7) {
        i = 1;
        while (i <= NUM_UNIS) {
            g->numStudents[i][STUDENT_THD] += g->numStudents[i][STUDENT_MTV] + g->numStudents[i][STUDENT_BQN];
            g->numStudents[i][STUDENT_BQN] = 0;
            g->numStudents[i][STUDENT_MTV] = 0;
            i++;
        }
    }
}

//Getters
int getDiscipline (Game g, int regionID) {
    return g->regionDiscipline[regionID];
}

int getDiceValue (Game g, int regionID) {
    return g->regionDice[regionID];
}

int getTurnNumber (Game g) {
    return g->turn;
}

int getMostARCs (Game g) {
    return g->mostArcs;
}

int getMostPublications (Game g) {
    return g->mostPublications;
}

int getWhoseTurn (Game g) {
    int turn;
    if (g->turn == -1) {
        turn = NO_ONE;
    } else {
        turn = (g->turn % NUM_UNIS) + 1;
    }
    return turn;
}

int getCampus(Game g, path pathToVertex) {
    return g->vertexContents[getVertex(g, pathToVertex)];
}

// Protect against being called with NO_ONE

int getKPIpoints (Game g, int player) {
    int val;
    if (player == NO_ONE) {
        val = 0;
    } else {
        val = g->numKpiPoints[player - 1];
    }
    return val;
}

int getARCs (Game g, int player) {
    int val;
    if (player == NO_ONE) {
        val = 0;
    } else {
        val = g->numArcs[player - 1];
    }
    return val;
}


int getGO8s (Game g, int player) {
    int val;
    if (player == NO_ONE) {
        val = 0;
    } else {
        val = g->numGo8s[player - 1];
    }
    return val;
}

int getCampuses (Game g, int player) {
    int val;
    if (player == NO_ONE) {
        val = 0;
    } else {
        val = g->numCampuses[player - 1];
    }
    return val;
}

int getIPs (Game g, int player) {
    int val;
    if (player == NO_ONE) {
        val = 0;
    } else {
        val = g->numIps[player - 1];
    }
    return val;
}

int getPublications (Game g, int player) {
    int val;
    if (player == NO_ONE) {
        val = 0;
    } else {
        val = g->numPublications[player - 1];
    }
    return val;
}

int getStudents (Game g, int player, int discipline) {
    int val;
    if (player == NO_ONE) {
        val = 0;
    } else {
        val = g->numStudents[player - 1][discipline]; //This is how you get an element in a 2-D array
    }
    return val;
}
