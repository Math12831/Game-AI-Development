/*
 * grid.c
 *
 *
 *
 */

#define BACK   0
#define LEFT   1
#define RIGHT  2

#define STRAIGHT_LEFT   0
#define STRAIGHT_RIGHT  1
#define UP_LEFT         2
#define UP_RIGHT        3
#define DOWN_LEFT       4
#define DOWN_RIGHT      5

#define FALSE  0
#define TRUE   1

#define NUM_COLUMN   12
#define NUM_ROW      11

typedef struct _point {
   int column, row;
   int valid;
   int connectSide;
   
   struct _point *up;
   struct _point *down;
   struct _point *side;
   
} point;

typedef point grid[NUM_COLUMN][NUM_ROW];

typedef struct _container {
   grid gameGrid;
} container;

typedef container *Container;

void initGrid (Container c);
void initColumn (Container c, int column,
                 int start, int num, int side,
                 int joinSide, int joinEnd);

int main (int argc, char *argv[]) {
   Container c = malloc(sizeof(container));
   return EXIT_SUCCESS;
}
