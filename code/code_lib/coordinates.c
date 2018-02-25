#include "coordinates.h"
#include "movement.h"
#include <stdio.h>
#include <stdlib.h>

/* Function that returns distance between 2 coordinates */
int distance_vn(int x1, int y1, int x2, int y2) {
    int xdist = abs(x2 - x1);
    int ydist = abs(y2-y1);
    int dist = xdist + ydist;

    return dist;
}

/* Function that takes care of agent movement, preventing leaving the grid. */
COORDINATES border (int actual_x, int actual_y, int move_x, int move_y) {
    COORDINATES dest;

    move_x = actual_x + move_x;
    move_y = actual_y + move_y;

    if (move_x >= WORLD_X) {
        move_x -= 1;
    }

    if (move_x < 0) {
        move_x += 1;
    }

    if (move_y >= WORLD_Y) {
        move_y -= 1;
    }

    if (move_y < 0) {
        move_y += 1;
    }

    dest.x = move_x;
    dest.y = move_y;

    return dest;
}

/* Human find nearest Zombie */
void find_zombie(AGENT *grid[WORLD_X][WORLD_Y],
                 AGENT **agentsShuffle, int agent) {

    int radius;
    int dx;
    int dy;
    int x = agentsShuffle[agent]->x;
    int y = agentsShuffle[agent]->y;
    int FLAG = 0;
    int max_search;


    if (WORLD_X > WORLD_Y) {
        max_search = WORLD_X;
    }
    else {
        max_search = WORLD_Y;
    }

    /* Print human agent playing ID and coordinates */
    printf("\nHuman playing:%x | X:%d Y:%d\n", agentsShuffle[agent]->id, x, y);

    /* Start Von Neumann search */
    for (radius = 1; radius <= max_search; radius++) {
        if (FLAG == 1) break;
        for (dx = -radius; dx <= radius; dx++) {
            if (FLAG == 1) break;
            for (dy = -radius; dy <= radius; dy++) {

                if (distance_vn(x, y, x + dx, y + dy) == radius) {
                    int xcoord = x + dx;
                    int ycoord = y + dy;
                    if (xcoord >= WORLD_X) xcoord = WORLD_X-1;
                    else if (xcoord < 0) xcoord = 0;
                    if (ycoord >= WORLD_Y) ycoord = WORLD_Y - 1;
                    else if (ycoord < 0) ycoord = 0;
                    if (grid[xcoord][ycoord] != NULL) {
                        if (grid[xcoord][ycoord]->type == Zombie) {
                            printf("Nearest Zombie ID: %d at COORDS: %d, %d\n",
                            grid[xcoord][ycoord]->id, xcoord, ycoord);
                            human_move(grid, agentsShuffle, x, y,
                                       xcoord, ycoord, agent);
                            FLAG = 1;
                            break;
                        }
                    }
                }
            }
        }
    }
}

/* Zombie find nearest Human */
void find_human(AGENT *grid[WORLD_X][WORLD_Y],
                AGENT **agentsShuffle, int agent, int *NHUMANS, int NAGENTS) {
    int radius;
    int dx;
    int dy;
    int x = agentsShuffle[agent]->x;
    int y = agentsShuffle[agent]->y;
    int FLAG = 0;
    int max_search;


    if (WORLD_X > WORLD_Y) {
        max_search = WORLD_X;
    }
    else {
        max_search = WORLD_Y;
    }

    /* Print human agent playing ID and coordinates */
    printf("\nZombie playing:%x | X:%d Y:%d\n", agentsShuffle[agent]->id, x, y);

    /* Start Von Neumann search */
    for (radius = 1; radius <= max_search; radius++) {
        if (FLAG == 1) break;
        for (dx = -radius; dx <= radius; dx++) {
            if (FLAG == 1) break;
            for (dy = -radius; dy <= radius; dy++) {

                if (distance_vn(x, y, x + dx, y + dy) == radius) {
                    int xcoord = x + dx;
                    int ycoord = y + dy;
                    if (xcoord >= WORLD_X) xcoord = WORLD_X-1;
                    else if (xcoord < 0) xcoord = 0;
                    if (ycoord >= WORLD_Y) ycoord = WORLD_Y - 1;
                    else if (ycoord < 0) ycoord = 0;
                    if (grid[xcoord][ycoord] != NULL) {
                        if (grid[xcoord][ycoord]->type == Human) {
                            printf("Nearest Human ID: %d at COORDS: %d, %d\n",
                            grid[xcoord][ycoord]->id, xcoord, ycoord);
                            zombie_move(grid, agentsShuffle, x, y,
                                        xcoord, ycoord, agent, NHUMANS, NAGENTS);
                            FLAG = 1;
                            break;
                        }
                    }
                }
            }
        }
    }
}
