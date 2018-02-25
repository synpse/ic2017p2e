#ifndef COORDINATES_H
#define COORDINATES_H

#include "jogo.h"

/**
 * Structure defining coordinates' properties.
 * */
typedef struct {
    int x, y;
} COORDINATES;

/**
 * Function to return distance between two coordinates
 *
 * @param x1 origin x
 * @param x2 destination x
 * @param y1 origin y
 * @param y2 destination y
 * */
int distance_vn(int x1, int y1, int x2, int y2);

/**
 * Function to limit grid
 *
 * @param actual_x Actual x position
 * @param actual_y Actual y position
 * @param move_x destination x
 * @param move_y destination y
 * */
COORDINATES border (int actual_x, int actual_y, int move_x, int move_y);

/**
 * Function to find nearest zombie
 *
 * @param grid array of pointers that hold `AGENT` objects
 * @param agentsShuffle array of pointers that hold `AGENT` objects to shuffle
 * @param agent current agent playing
 * */
void find_zombie(AGENT *grid[WORLD_X][WORLD_Y], AGENT **agentsShuffle,
                 int agent);

/**
 * Function to find nearest human
 *
 * @param grid array of pointers that hold `AGENT` objects
 * @param agentsShuffle array of pointers that hold `AGENT` objects to shuffle
 * @param agent current agent playing
 * @param NHUMANS total number of humans
 * @param NAGENTS total number of agents
 * */
void find_human(AGENT *grid[WORLD_X][WORLD_Y], AGENT **agentsShuffle,
                int agent, int *NHUMANS, int NAGENTS);

#endif
