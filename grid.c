/*
 * grid.c
 * Author: James Arcus, james.arcus64@gmail.com
 * Bugs found, do not use yet.
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
void testGrid (Container c);

int main (int argc, char *argv[]) {
   Container c = malloc(sizeof(container));
   initGrid(c);
   testGrid(c);
   return EXIT_SUCCESS;
}

void testGrid (Container c) {
   int i = 0;
   while (i < NUM_COLUMN) {
      int j = 0;
      while (j < NUM_ROW) {
         
         point *currentPoint = &(c->gameGrid[i][j]);
         
         if (currentPoint->valid == TRUE) {
            printf("Point at gameGrid[%d][%d] has coordinates (%d,%d), has neighbours at", i, j, currentPoint->column, currentPoint->row);           
            if (currentPoint->up != NULL) {
               printf(" (%d,%d)", currentPoint->up->column, currentPoint->up->row);
            }
            if (currentPoint->down != NULL) {
               printf(" (%d,%d)", currentPoint->down->column, currentPoint->down->row);
            }
            if (currentPoint->side != NULL) {
               printf(" (%d,%d)", currentPoint->side->column, currentPoint->side->row);
            }
            printf("\n");
         }
         
         j++;
      }
      
      i++;
   }   
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
      
      initColumn(c, column, start, num, side, joinSide, joinEnd);    
      
      i++;
   }
}

void initColumn (Container c, int column,
                 int start, int num, int side,
                 int joinSide, int joinEnd) {
   int i = 0;
   while (i < NUM_ROW) {
      int currentRow = i;
      point *currentPoint = &(c->gameGrid[column][currentRow]);
      
      currentPoint->column = column;
      currentPoint->row = currentRow;
      currentPoint->connectSide = side;
      
      if ((currentRow >= start) && (currentRow <= start + ((num - 1) * 2)) &&
            ((currentRow - start) % 2 == 0)) {
         
         currentPoint->valid = TRUE;
                  
         if (joinSide == TRUE) {
         
            if (side == RIGHT) {
               currentPoint->side = &(c->gameGrid[column + 1][currentRow]);
            } else {
               currentPoint->side = &(c->gameGrid[column - 1][currentRow]);
            }
                     
         } else {
            currentPoint->side = NULL;
         }
         
         if (joinEnd == TRUE || ((currentRow != start) &&
               (currentRow != start + ((num - 1) * 2)))) {
         
            if (side == RIGHT) {
               currentPoint->up   = &(c->gameGrid[column - 1][currentRow + 1]);
               currentPoint->down = &(c->gameGrid[column - 1][currentRow - 1]);
            } else {
               currentPoint->up   = &(c->gameGrid[column + 1][currentRow + 1]);
               currentPoint->down = &(c->gameGrid[column + 1][currentRow - 1]);
            }
            
         } else if (currentRow == start) {
            if (side == RIGHT) {
               currentPoint->up   = NULL;
               currentPoint->down = &(c->gameGrid[column - 1][currentRow - 1]);
            } else {
               currentPoint->up   = NULL;
               currentPoint->down = &(c->gameGrid[column + 1][currentRow - 1]);
            }
         } else {
            if (side == RIGHT) {
               currentPoint->up   = &(c->gameGrid[column - 1][currentRow + 1]);
               currentPoint->down = NULL;
            } else {
               currentPoint->up   = &(c->gameGrid[column + 1][currentRow + 1]);
               currentPoint->down = NULL;
            }
         }
         
      } else {         
         currentPoint->valid = FALSE;
         currentPoint->up = NULL;
         currentPoint->down = NULL;
         currentPoint->side = NULL;
      }     

      i++; 
   }
}
