#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "jogo.h"

/**
 * Function to move playable `AGENT` objects
 *
 * @param grid array of pointers that hold `AGENT` objects
 * @param agentsShuffle array of pointers that hold `AGENT` objects to shuffle
 * @param agent current agent playing
 * @param NHUMANS total number of humans
 * @param NAGENTS total number of agents
 * */
void playable_move(AGENT *grid[WORLD_X][WORLD_Y], AGENT **agentsShuffle,
              int agent, int *NHUMANS, int NAGENTS);

/**
 * Function to move AI zombie `AGENT` objects
 *
 * @param grid array of pointers that hold `AGENT` objects
 * @param agentsShuffle array of pointers that hold `AGENT` objects to shuffle
 * @param x current x coordinates
 * @param y current y coordinates
 * @param xcoord x of nearest enemy `AGENT` found
 * @param ycoord y of nearest enemy `AGENT` found
 * @param agent current agent playing
 * @param NHUMANS total number of humans
 * @param NAGENTS total number of agents
 * */
void zombie_move(AGENT *grid[WORLD_X][WORLD_Y], AGENT **agentsShuffle, int x, int y,
                 int xcoord, int ycoord, int agent, int *NHUMANS, int NAGENTS);

/**
 * Function to move AI human `AGENT` objects
 *
 * @param grid array of pointers that hold `AGENT` objects
 * @param agentsShuffle array of pointers that hold `AGENT` objects to shuffle
 * @param x current x coordinates
 * @param y current y coordinates
 * @param xcoord x of nearest enemy `AGENT` found
 * @param ycoord y of nearest enemy `AGENT` found
 * @param agent current agent playing
 * */
void human_move(AGENT *grid[WORLD_X][WORLD_Y], AGENT **agentsShuffle,
                int x, int y, int xcoord, int ycoord, int agent);

#endif
