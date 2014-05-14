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
    int region[NEIGHBOURS_PER_REGION];
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
    int turn, most_publications, most_arcs;
    
    //Player attributes
    int num_students[NUM_UNIS][NUM_STUDENT_TYPES];  //This is a 2-D array
    int num_kpi_points[NUM_UNIS];
    int num_campuses[NUM_UNIS];
    int num_go8s[NUM_UNIS];
    int num_arcs[NUM_UNIS];
    int num_ips[NUM_UNIS];
    int num_publications[NUM_UNIS];
    
    //Contents
    int region_discipline[NUM_REGIONS];
    int region_dice[NUM_REGIONS];
    int vertex_contents[NUM_VERTICES];
    int arc_contents[NUM_ARCS];
    
    //Neighbours
    region region_neighbours[NUM_REGIONS];  //What are the neighbours of each region?
    arc arc_neighbours[NUM_ARCS];                                           // arc?
    vertex vertex_neighbours[NUM_VERTICES];                                 // vertex?
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
        vertex* neighbours = &g->vertex_neighbours[current_vertex];
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
    char* i = pathToVertex;
    int currentVertex = 0;
    int currentEdge;
    int direction = 0;
    while (*i != 0) {
        vertex* neighbours = &g->vertex_neighbours[current_vertex];
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
    int row, col;
    int colStart[] = {3, 2, 1, 2, 3};
    int colEnd[] = {7, 8, 9, 8, 7};
    col = 0;
    while (col < REGION_COLUMNS) {
        row = colStart[col];
        while (row <= colEnd[col]) {
            //Regions
            g->region_neighbours[i].regions[0] = regionNum(row - 2, col);
            g->region_neighbours[i].regions[1] = regionNum(row - 1, col + 1);
            g->region_neighbours[i].regions[2] = regionNum(row + 1, col + 1);
            g->region_neighbours[i].regions[3] = regionNum(row + 2, col);
            g->region_neighbours[i].regions[4] = regionNum(row + 1, col - 1);
            g->region_neighbours[i].regions[5] = regionNum(row - 1, col - 1);
            
            //Arcs
            
            //Vertices
            g->region_neighbours[i].vertices[0] = vertexNum(row - 1, col * 3 + 2);
            g->region_neighbours[i].vertices[1] = vertexNum(row, col * 3 + 3);
            g->region_neighbours[i].vertices[2] = vertexNum(row + 1,  col * 3 + 2);
            g->region_neighbours[i].vertices[3] = vertexNum(row + 1,  col * 3 + 1);
            g->region_neighbours[i].vertices[4] = vertexNum(row,  col);
            g->region_neighbours[i].vertices[5] = vertexNum(row - 1,  col * 3 + 1);
            
            row += 2;
        }
        col++;
    }
}

//Finish this
void initaliseVertexNeighbours (Game g) {
    int row, col;
    int colStart[];  //Do this
    int colEnd[];    //Do this
    col = 0;
    while (col < VERTEX_COLUMNS) {
        row = colStart[col];
        while (row <= colEnd[col]) {
            if (col % 2 == 0) {
                //Regions
                g->vertex_neighbours[i].vertices[0] = regionNum(row, (col + 1) / 3);
                g->vertex_neighbours[i].vertices[0] = regionNum(row + 1, (col - 1) / 3);
                g->vertex_neighbours[i].vertices[0] = regionNum(row - 1, (col - 1) / 3);
                
                //Arcs
            
                //Vertices
                g->vertex_neighbours[i].vertices[0] = vertexNum(row, col + 1);
                g->vertex_neighbours[i].vertices[1] = vertexNum(row + 1, col - 1);
                g->vertex_neighbours[i].vertices[2] = vertexNum(row - 1, col - 1);
            } else {
                //Regions
                g->vertex_neighbours[i].vertices[0] = regionNum(row, (col + 1) / 3);
                g->vertex_neighbours[i].vertices[0] = regionNum(row + 1, (col + 1) / 3);
                g->vertex_neighbours[i].vertices[0] = regionNum(row - 1, (col - 1) / 3);
                
                //Arcs
                
                //Vertices
                g->vertex_neighbours[i].vertices[0] = vertexNum(row - 1, col + 1);
                g->vertex_neighbours[i].vertices[1] = vertexNum(row + 1, col + 1);
                g->region_neighbours[i].vertices[2] = vertexNum(row, col - 1);
            }
            
            row += 2;
        }
        col++;
    }
}

//Finish this
void initaliseArcNeighbours (Game g) {
}

void initaliseNeighbours(Game g) {
    initialiseRegionNeighbours(g);
    initialiseVertexNeighbours(g);
    initialiseArcNeighbours(g);
}

void inititaliseContents(Game g, int discipline[], int dice[]) {
    int i = 0;
    while (i < NUM_REGIONS) {
        g->region_discipline[i] = discipline[i];
        g->region_dice[i] = dice[i];
        i++;
    }
    i = 0;
    while (i < NUM_ARCS) {
        g->arc_contents[i] = VACANT_ARC;
        i++;
    }
    i = 0;
    while (i < NUM_VERTICES) {
        g->vertex_contents[i] = VACANT_VERTEX;
        i++;
    }
}

void initialiseStudents(Game g) {
    int i = 0;
    while (i < NUM_UNIS) {
        g->num_students[i][STUDENT_THD] = INITIAL_THD;
        g->num_students[i][STUDENT_BPS] = INITIAL_BPS;
        g->num_students[i][STUDENT_BQN] = INITIAL_BQN;
        g->num_students[i][STUDENT_MJ] = INITIAL_MJ;
        g->num_students[i][STUDENT_MTV] = INITIAL_MTV;
        g->num_students[i][STUDENT_MMONEY] = INITIAL_MMONEY;
        i++;
    }
}

//Setters
Game newGame (int discipline[], int dice[]) {
    //Declare variables
    int i;
    
    //Allocate game
    Game g = malloc(sizeof(game));
    
    //Initialise variables
    g->turn = -1;
    g->most_arcs = NO_ONE;
    g->most_publications = NO_ONE;
    
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
        g->vertex_contents[getVertex(g, a.destination)] = turn;
        g->num_students[turn][STUDENT_BPS]--;
        g->num_students[turn][STUDENT_BQN]--;
        g->num_students[turn][STUDENT_MJ]--;
        g->num_students[turn][STUDENT_MTV]--;
    } else if (a.actionCode == BUILD_GO8) {
        g->vertex_contents[getVertex(g, a.destination)] += NUM_UNIS;
        g->num_students[turn][STUDENT_MJ] -= 2;
        g->num_students[turn][STUDENT_MMONEY] -= 3;
    } else if (a.actionCode == OBTAIN_ARC) {
        g->arc_contents[getEdge(g, a.destination)] = turn;
        g->num_students[turn][STUDENT_BPS]--;
        g->num_students[turn][STUDENT_BQN]--;
    } else if (a.actionCode == OBTAIN_PUBLICATION) {
        g->num_students[turn][STUDENT_MJ]--;
        g->num_students[turn][STUDENT_MTV]--;
        g->num_students[turn][STUDENT_MMONEY]--;
    } else if (a.actionCode == OBTAIN_IP_PATENT) {
        g->num_students[turn][STUDENT_MJ]--;
        g->num_students[turn][STUDENT_MTV]--;
        g->num_students[turn][STUDENT_MMONEY]--;
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
        if (g->region_dice[i] == diceScore) {
            j = 0;
            while (j < NEIGHBOURS_PER_REGION) {
                //If this vertex contains a campus
                int v_contents = g->vertex_contents[g->region_neighbours[i].vertices[j]];
                if (v_contents != VACANT_VERTEX) {
                    //Increase the number of students at that university
                    g->num_students[(v_contents % NUM_UNIS) - 1][i]++;
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
            g->num_students[i][STUDENT_THD] += g->num_students[i][STUDENT_MTV] + g->num_students[i][STUDENT_BQN];
            g->num_students[i][STUDENT_BQN] = 0;
            g->num_students[i][STUDENT_MTV] = 0;
            i++;
        }
    }
}

//Getters
int getDiscipline (Game g, int regionID) {
    return g->region_discipline[regionID];
}

int getDiceValue (Game g, int regionID) {
    return g->region_dice[regionID];
}

int getTurnNumber (Game g) {
    return g->turn;
}

int getMostARCs (Game g) {
    return g->most_arcs;
}

int getMostPublications (Game g) {
    return g->most_publications;
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
    return g->vertex_contents[getVertex(g, pathToVertex)];
}

// Protect against being called with NO_ONE

int getKPIpoints (Game g, int player) {
    int val;
    if (player == NO_ONE) {
        val = 0;
    } else {
        val = g->num_kpi_points[player - 1];
    }
    return val;
}

int getARCs (Game g, int player) {
    int val;
    if (player == NO_ONE) {
        val = 0;
    } else {
        val = g->num_arcs[player - 1];
    }
    return val;
}


int getGO8s (Game g, int player) {
    int val;
    if (player == NO_ONE) {
        val = 0;
    } else {
        val = g->num_go8s[player - 1];
    }
    return val;
}

int getCampuses (Game g, int player) {
    int val;
    if (player == NO_ONE) {
        val = 0;
    } else {
        val = g->num_campuses[player - 1];
    }
    return val;
}

int getIPs (Game g, int player) {
    int val;
    if (player == NO_ONE) {
        val = 0;
    } else {
        val = g->num_ips[player - 1];
    }
    return val;
}

int getPublications (Game g, int player) {
    int val;
    if (player == NO_ONE) {
        val = 0;
    } else {
        val = g->num_publications[player - 1];
    }
    return val;
}

int getStudents (Game g, int player, int discipline) {
    int val;
    if (player == NO_ONE) {
        val = 0;
    } else {
        val = g->num_students[player - 1][discipline]; //This is how you get an element in a 2-D array
    }
    return val;
}
