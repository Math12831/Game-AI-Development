//
//  legal.c
//  UNSW
//
//  Created by Nicholas Pizzino on 5/14/14.
//  Copyright (c) 2014 Pachino's Casinos. All rights reserved.
//

#define NOBODY 0
#define SOMEBODY 1

#include <stdio.h>
#include <stdlib.h>
#include "Game.h"

int validatePath (Game g, path pathToVertex);
int checkResources (Game g, int actionCode, action a);
int checkNoNeighbours (Game g, path pathToVertex);
//int checkDisciplineNumbers (Game g);

int isLegalAction (Game g, action a) {
    int tally = 0;
    int valid = TRUE;
    if (getWhoseTurn (g) != NO_ONE) {
        if (a.actionCode == BUILD_CAMPUS) {
            if (validatePath (g, a.destination) == FALSE && checkResources (g, a.actionCode, ) == FALSE) {
                tally ++;
            }
            if (checkNoNeighbours(g, a.destination) != NOBODY && getCampus (g, a.destination) != VACANT_VERTEX) {
                tally ++;
            }
            if (getARC (g, a.destination) != getWhoseTurn (g)) {
                tally ++;
            }
        } else if (a.actionCode == BUILD_GO8) {
            if (validatePath (g, a.destination) == FALSE && checkResources (g, a.actionCode, a) == FALSE) {
                tally ++;
            }
            if (getCampus (g, a.destination) != getWhoseTurn (g)) {
                tally ++;
            }
            int numberOfG08s = getGO8s (g, UNI_A);
            numberOfG08s += getGO8s (g, UNI_B);
            numberOfG08s += getGO8s (g, UNI_C);
            if (numberOfG08s >= 8) {
                tally ++;
            }
        } else if (a.actionCode == OBTAIN_ARC) {
            if (validatePath (g, a.destination) == FALSE && checkResources (g, a.actionCode, a) == FALSE) {
                tally ++;
            }
            if (getARC (g, a.destination) != VACANT_ARC) {
                tally ++;
            }
        } else if (a.actionCode == START_SPINOFF) {
            if (checkResources (g, a.actionCode, a) == FALSE) {
                tally ++;
            }
        } else if (a.actionCode == RETRAIN_STUDENTS) {
            int exchangeRate = getExchangeRate (g, getWhoseTurn (g), a.disciplineFrom, a.disciplineTo);
            if (exchangeRate != 3) {
                tally ++;
            }
            if (checkResources (g, a.actionCode, a) != TRUE) {
                tally ++;
            }
            if (a.disciplineFrom == STUDENT_THD) {
                tally ++;
            }
            
        }
    }
    if (tally > 0) {
        valid = FALSE;
    }
    return valid;
}

int checkResources (Game g, int actionCode, action a) {
    int player = getWhoseTurn (g);
    int resources = FALSE;
    int tally = 0;
    
    if (actionCode == BUILD_CAMPUS) {
        if (getStudents (g, player, STUDENT_BPS) == 0) {
            tally ++;
        }
        if (getStudents (g, player, STUDENT_BQN) == 0) {
            tally ++;
        }
        if (getStudents (g, player, STUDENT_MJ) == 0) {
            tally ++;
        }
        if (getStudents (g, player, STUDENT_MTV) == 0) {
            tally ++;
        } 
    } else if (actionCode == BUILD_GO8) {
        if (getStudents (g, player, STUDENT_MJ) <= 1) {
            tally ++;
        }
        if (getStudents (g, player, STUDENT_MMONEY) <= 2) {
            tally ++;
        }
    } else if (actionCode == OBTAIN_ARC) {
        if (getStudents (g, player, STUDENT_BPS) == 0) {
            tally ++;
        }
        if (getStudents (g, player, STUDENT_BQN) == 0) {
            tally ++;
        }
    } else if (actionCode == START_SPINOFF) {
        if (getStudents (g, player, STUDENT_MJ) == 0) {
            tally ++;
        }
        if (getStudents (g, player, STUDENT_MTV) == 0) {
            tally ++;
        }
        if (getStudents (g, player, STUDENT_MMONEY) == 0) {
            tally ++;
        }
    } else if (actionCode == RETRAIN_STUDENTS) {
        int exchangeRate = getExchangeRate (g, getWhoseTurn (g), a.disciplineFrom, a.disciplineTo);
        int disciplineFrom = a.disciplineFrom;
        
        if (getStudents (g, player, disciplineFrom) !<= (exchangeRate - 1)) {
            tally ++;
        }
    }
    
    if (tally == 0) {
        resources = TRUE;
    }
    
    getStudents (g, player, discipline)
    return resources;
}
