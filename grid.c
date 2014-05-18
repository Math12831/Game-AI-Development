/*
 * grid.c
 *
 *
 *
 */

#include <stdlib.h>
#include <stdio.h>

#define LEFT   0
#define RIGHT  1

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
   initGrid(c);
   return EXIT_SUCCESS;
}

void initGrid (Container c) {
   int i = 0;
   while (i < NUM_COLUMN) {
      int column = i;
      int halfColumn;
      int start, num, side, joinSide, joinEnd;
      
      if (column >= (NUM_COLUMN / 2)) {
         halfColumn = (NUM_COLUMN - 1) - column;
      } else {
         halfColumn = column;
      }
      
      num = ((halfColumn + 1) / 2) + 3;
      start = 6 - num;
      
      side = column % 2;
      
      if (halfColumn == 0) {
         joinSide = FALSE;
      } else {
         joinSide = TRUE;
      }
      
      joinEnd = (halfColumn + 1) % 2;
      
   /* printf("column: %d,\thalfColumn: %d,\tnum: %d,\tstart: %d,\tside: %d,\tjoinSide: %d,\tjoinEnd: %d\n",
             column, halfColumn, num, start, side, joinSide, joinEnd); */
      
      initColumn(c, column, start, num, side, joinSide, joinEnd);    
      
      i++;
   }
}

void initColumn (Container c, int column,
                 int start, int num, int side,
                 int joinSide, int joinEnd) {
   
}
