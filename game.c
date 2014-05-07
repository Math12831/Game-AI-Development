
// Samuel Thompson, Nicholas Pizzino, George Kottler
// Draft Game.c

#include <stdlib.h>

#include "Game.h"

#define NUM_VERTICES 54
#define NUM_ARCS 72

#define NEIGHBOURS_PER_REGION 6
#define REGIONS_PER_VERTEX 3
#define VERTICES_PER_ARC 2
#define REGIONS_PER_ARC 2

#define NUM_STUDENT_TYPES 6

// ---------------------------------------------------- Storage --------------------------------------------------------- //

// Stores the neighbours of a region - not all parts may be necessary
typedef struct _region {
    int region[NEIGHBOURS_PER_REGION];
    int arcs[NEIGHBOURS_PER_REGION];
    int vertices[NEIGHBOURS_PER_REGION];
} region;

// Stores the neighbours of an arc - not all parts may be necessary
typedef struct _arc {
    int vertices[VERTICES_PER_ARC];
    int regions[REGIONS_PER_ARC];
} arc;

// Stores the neighbours of a vertex - not all parts may be necessary
typedef struct _vertex {
    int left_arc, right_arc, down_arc;
    int left_vertex, right_vertex, down_vertex;
    int regions[REGIONS_PER_VERTEX];
} vertex;

typedef struct _game {
    // Game states
    int turn;
    
    // Player attributes
    int num_students[NUM_UNIS][NUM_STUDENT_TYPES];  // This the decleration of a 2-D array
    int num_kpi_points[NUM_UNIS];
    int num_campuses[NUM_UNIS];
    int num_go8s[NUM_UNIS];
    int num_arcs[NUM_UNIS];
    int num_ips[NUM_UNIS];
    int num_publications[NUM_UNIS];
    
    // Contents
    int region_discipline[NUM_REGIONS];
    int region_dice[NUM_REGIONS];
    int vertex_contents[NUM_VERTICES];
    int arc_contents[NUM_ARCS];
    
    // Neighbours
    region region_neighbours[NUM_REGIONS];  // What are the neighbours of each region?
    arc arc_neighbours[NUM_ARCS];                                           // Arc?
    vertex vertex_neighbours[NUM_VERTICES];                                 // Vertex?
} game;


// ---------------------------------------------------- Setters --------------------------------------------------------- //

Game newGame (int discipline[], int dice[]) {
    // Declare variables
    int i, j;
    
    // Allocate game
    Game g = malloc(sizeof(game));
    
    // Initialise variables
    g->turn = -1;
    
    // Initialise the contents of each region/arc/vertex
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
    
    // Intitialise number of students to 0 for each player and discipline
    i = 0;
    while (i < NUM_UNIS) {
        j = 0;
        while (i < NUM_STUDENT_TYPES) {
            g->num_students[i][j] = 0;
            j++;
        }
        i++;
    }
    
    // Do Things - to be implimented in later updates
    
    return g;
}


void disposeGame (Game g) {
    free(g);
    // Should there be more things to do?
}

void throwDice (Game g, int diceScore) {
    int i, j;
    
    i = 0;
    while (i < NUM_REGIONS) {
        
        // Check if this region's number has been rolled
        if (g->region_dice[i] == diceScore) {
            j = 0;
            while (j < NEIGHBOURS_PER_REGION) {
                // If this vertex contains a campus...
                int v_contents = g->vertex_contents[g->region_neighbours[i].vertices[j]];
                if (v_contents != VACANT_VERTEX) {
                    // Increase the number of students at that university
                    g->num_students[(v_contents % NUM_UNIS) - 1][i]++;
                }
                ++j;
            }
        }
        ++i;
    }
}

// ---------------------------------------------------- Getters --------------------------------------------------------- //

int getDiscipline (Game g, int regionID) {
    return g->region_discipline[regionID];
}

int getDiceValue (Game g, int regionID) {
    return g->region_dice[regionID];
}

int getTurnNumber (Game g) {
    return g->turn;
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

int getKPIpoints (Game g, int player) {
    return g->num_kpi_points[player];
}

int getARCs (Game g, int player) {
    return g->num_arcs[player];
}


int getGO8s (Game g, int player) {
    return g->num_go8s[player];
}

int getCampuses (Game g, int player) {
    return g->num_campuses[player];
}

int getIPs (Game g, int player) {
    return g->num_ips[player];
}

int getPublications (Game g, int player) {
    return g->num_publications[player];
}

int getStudents (Game g, int player, int discipline) {
    return g->num_students[player][discipline]; // This is the syntax on how you get an element in a 2-D array
}
