//CHECK OFF-BY-ONE ERRORS!

#include <stdlib.h>

#include "Game.h"

#define NUM_VERTICES 54
#define NUM_ARCS 72

#define NEIGHBOURS_PER_REGION 6
#define REGIONS_PER_VERTEX 3
#define VERTICES_PER_ARC 2
#define REGIONS_PER_ARC 2

#define NUM_STUDENT_TYPES 6

#define INITIAL_THD 0
#define INITIAL_BPS 3
#define INITIAL_BQN 3
#define INITIAL_MJ  1
#define INITIAL_MTV 1
#define INITIAL_MMONEY 1

//Stores the neighbours of a region - not all parts may be necessary
typedef struct _region {
    int region[NEIGHBOURS_PER_REGION];
    int arcs[NEIGHBOURS_PER_REGION];
    int vertices[NEIGHBOURS_PER_REGION];
} region;

//Stores the neighbours of an arc - not all parts may be necessary
typedef struct _arc {
    int vertices[VERTICES_PER_ARC];
    int regions[REGIONS_PER_ARC];
} arc;

//Stores the neighbours of a vertex - not all parts may be necessary
typedef struct _vertex {
    int left_arc, right_arc, down_arc;
    int left_vertex, right_vertex, down_vertex;
    int regions[REGIONS_PER_VERTEX];
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
int getVertex (Game g, path pathToVertex) {
    char* i = pathToVertex;
    int current_vertex = 0;
    while (*i != 0) {
        vertex* neighbours = &g->vertex_neighbours[current_vertex]
        if (*i == 'L') {
            current_vertex = neighbours->left_vertex;
        } else if (*i == 'R') {
            current_vertex = neighbours->right_vertex;
        } else {
            current_vertex = neighbours->back_vertex;
        }
        i++;
    }
    return current_vertex;
}

int getEdge (Game g, path pathToEdge) {
    char* i = pathToVertex;
    int current_vertex = 0;
    int current_edge;
    while (*i != 0) {
        vertex* neighbours = &g->vertex_neighbours[current_vertex]
        if (*i == 'L') {
            current_vertex = neighbours->left_vertex;
            current_edge = neighbours->left_edge;
        } else if (*i == 'R') {
            current_vertex = neighbours->right_vertex;
            current_edge = neighbours->right_edge;
        } else {
            current_vertex = neighbours->back_vertex;
             current_edge = neighbours->back_edge;
        }
        i++;
    }
    return current_edge;
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
    
    //Initialise the contents of each region/arc/vertex
    i = 0;
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
    
    //Intitialise number of students to 0 for each player and discipline
    i = 0;
    while (i < NUM_UNIS) {
        g->num_students[i][STUDENT_THD] = INITIAL_THD;
        g->num_students[i][STUDENT_BPS] = INITIAL_BPS;
        g->num_students[i][STUDENT_BQN] = INITIAL_BQN;
        g->num_students[i][STUDENT_MJ] = INITIAL_MJ;
        g->num_students[i][STUDENT_MTV] = INITIAL_MTV;
        g->num_students[i][STUDENT_MMONEY] = INITIAL_MMONEY;
        i++;
    }
    
    //Do things
    
    return g;
}


void disposeGame (Game g) {
    free(g);
    //Do more things?
}

void makeAction(Game g, action a) {
    int turn = getWhoseTurn(g);
    if (a.actionCode == BUILD_CAMPUS) {
        g->vertex_contents[getVertex(a.destination)] = turn;
        g->num_students[turn][STUDENT_BPS]--;
        g->num_students[turn][STUDENT_BQN]--;
        g->num_students[turn][STUDENT_MJ]--;
        g->num_students[turn][STUDENT_MTV]--;
    } else if (a.actionCode == BUILD_GO8) {
        g->vertex_contents[getVertex(a.destination)] += NUM_UNIS;
        g->num_students[turn][STUDENT_MJ] -= 2;
        g->num_students[turn][STUDENT_MMONEY] -= 3;
    } else if (a.actionCode == OBTAIN_ARC) {
        g->arc_contents[getEdge(a.destination)] = getWhoseTurn(g);
        g->num_students[turn][STUDENT_BPS]--;
        g->num_students[turn][STUDENT_BQN]--;
    } else if (a.actionCode == START_SPINOFF) {
        ;   //Generate publication / IP
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
    return g->vertex_contents[getVertex(pathToVertex)];
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

