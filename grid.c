/*
 * grid.c
 * Author: James Arcus, james.arcus64@gmail.com
 * 
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "Game.h"

#define LEFT   0
#define RIGHT  1

#define IMPOSSIBLE_DIRECTION -1

#define STRAIGHT_LEFT   0
#define UP_RIGHT        1
#define DOWN_RIGHT      2

#define STRAIGHT_RIGHT  3
#define UP_LEFT         4
#define DOWN_LEFT       5

#define NUM_COLUMN   12
#define NUM_ROW      11

typedef struct _point {
   int column, row;
   int valid;
   int connectSide;
   
   struct _point *up;
   struct _point *down;
   struct _point *side;
   
   // Data about point goes here
   
} point;

typedef point grid[NUM_COLUMN][NUM_ROW];

// Simulates game struct usage
typedef struct _container {
   grid gameGrid;
} container;

typedef container *Container;

void initGrid (Container c);
void initColumn (Container c, int column,
                 int start, int num, int side,
                 int joinSide, int joinEnd);
void testGrid (Container c);
point *traversePath(path p);

// Sample main function that tests the grid system
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
            printf("Point at gameGrid[%d][%d] has coordinates (%d,%d), has neighbours at",
                   i, j, currentPoint->column, currentPoint->row);           
            if (currentPoint->up != NULL) {
               printf(" up: (%d,%d)", currentPoint->up->column, currentPoint->up->row);
            } else {
               printf(" up:  NULL");
            }
            if (currentPoint->down != NULL) {
               printf(" down: (%d,%d)", currentPoint->down->column, currentPoint->down->row);
            } else {
               printf(" down:  NULL");
            }
            if (currentPoint->side != NULL) {
               printf(" side: (%d,%d)", currentPoint->side->column, currentPoint->side->row);
            } else {
               printf(" side:  NULL");
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
               currentPoint->up   = &(c->gameGrid[column - 1][currentRow - 1]);
               currentPoint->down = &(c->gameGrid[column - 1][currentRow + 1]);
            } else {
               currentPoint->up   = &(c->gameGrid[column + 1][currentRow - 1]);
               currentPoint->down = &(c->gameGrid[column + 1][currentRow + 1]);
            }
            
         } else if (currentRow == start) {
            if (side == RIGHT) {
               currentPoint->up   = NULL;
               currentPoint->down = &(c->gameGrid[column - 1][currentRow + 1]);
            } else {
               currentPoint->up   = NULL;
               currentPoint->down = &(c->gameGrid[column + 1][currentRow + 1]);
            }
         } else {
            if (side == RIGHT) {
               currentPoint->up   = &(c->gameGrid[column - 1][currentRow - 1]);
               currentPoint->down = NULL;
            } else {
               currentPoint->up   = &(c->gameGrid[column + 1][currentRow - 1]);
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

point *traversePath(Container c, path p) {
   char *i = p;
   point *prev = NULL;
   point *current = &(c->gameGrid[5][0]);
   while (*i != 0) {
      int direction = computeDirection(prev, current);
      
      if (*i == 'L') {
      
      } else if (*i == 'R') {
      
      } else {
      
      }
      
      i++;
   }
}

// Computes direction of travel from 
int computeDirection(point *from, point *to) {
   if (from == NULL) {
      from = to;
   }
   
   int verticalDisp = to->column - from->column;
   int horizontalDisp = to->row - from->row;
   int direction;
   
   if (abs(verticalDisp) > 1 || abs(horizontalDisp) > 1) {
      direction = IMPOSSIBLE_DIRECTION;
   } else if (verticalDisp == 0 && horizontalDisp == 0) {
      direction = DOWN_RIGHT; // Default direction to face inward from start
   } else if (verticalDisp == 1) {
      if (horizontalDisp == 1) {
         direction = DOWN_RIGHT;
      } else { // horizontalDisp == -1
         direction = DOWN_LEFT;
      }
   } else if (verticalDisp == -1) {
      if (horizontalDisp == 1) {
         direction = UP_RIGHT;
      } else { // horizontalDisp == -1
         direction = UP_LEFT;
      }
   } else { // verticalDisp == 0
      if (horizontalDisp == 1) {
         direction = RIGHT;
      } else { // horizontalDisp == -1
         direction = LEFT;
      }
   }
   
   return direction;
}












