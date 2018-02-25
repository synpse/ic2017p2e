#include "movement.h"
#include "coordinates.h"
#include <stdlib.h>
#include <stdio.h>

void playable_move(AGENT *grid[WORLD_X][WORLD_Y], AGENT **agentsShuffle,
              int agent, int *NHUMANS, int NAGENTS) {
    int dx;
    int dy;
    char input_str[30];
    int input;
    COORDINATES destination;
    int x = agentsShuffle[agent]->x;
    int y = agentsShuffle[agent]->y;

    printf("\nYour ID: %x / Coords: X: %d Y: %d\n",
    agentsShuffle[agent]->id, agentsShuffle[agent]->x, agentsShuffle[agent]->y);
    printf("Choose where to move your Agent\n");
    printf("\n7    8    9\n\n4    A    6\n\n1    2    3\n");

    fgets(input_str, sizeof(input), stdin);
    input = atoi(input_str);


    switch (input) {
        case 7:
            dx = -1;
            dy = -1;
            break;
        case 8:
            dx = 0;
            dy = -1;
            break;
        case 9:
            dx = 1;
            dy = -1;
            break;
        case 4:
        dx = -1;
        dy = 0;
            break;
        case 6:
        dx = 1;
        dy = 0;
            break;
        case 1:
        dx = -1;
        dy = 1;
            break;
        case 2:
        dx = 0;
        dy = 1;
            break;
        case 3:
        dx = 1;
        dy = 1;
            break;
    }

    destination = border(x, y, dx, dy);

    if (grid[destination.x][destination.y] == NULL) {

        /* Destination in grid receives agent from actual position. */
        grid[destination.x][destination.y] = grid[x][y];
        /* Change position in the array we use to shuffle */
        agentsShuffle[agent]->x = destination.x;
        agentsShuffle[agent]->y = destination.y;

        /* Old position is now NULL */
        grid[x][y] = NULL;
    }
    else {
        if ((grid[x][y]->type == Zombie) &&
        (grid[destination.x][destination.y]->type == Human)) {

            /* Transform human into zombie */
            grid[destination.x][destination.y]->type = Zombie;
            /* One less human */
            (*NHUMANS)--;

            /* Change type in array that we use to shuffle */
            for (int i = 0; i < NAGENTS; i++) {
                if ((agentsShuffle[i] != NULL) &&
                (agentsShuffle[i]->x == destination.x) &&
                (agentsShuffle[i]->y == destination.y)) {
                    agentsShuffle[i]->type = Zombie;
                }
            }
        }
    }
}

void zombie_move(AGENT *grid[WORLD_X][WORLD_Y], AGENT **agentsShuffle, int x, int y,
                 int xcoord, int ycoord, int agent, int *NHUMANS, int NAGENTS) {

    COORDINATES destination;
    int dx, dy;

    /* If actual agent coord X - enemy coord X < 0 then destination X = 1 */
    if (agentsShuffle[agent]->x - xcoord < 0) {
        dx = 1;
    }
    /* If actual agent coord X - enemy coord X == 0 then destination X = 0 */
    if (agentsShuffle[agent]->x - xcoord == 0) {
        dx = 0;
    }
    /* If actual agent coord X - enemy coord X > 0 then destination X = -1 */
    if (agentsShuffle[agent]->x - xcoord > 0) {
        dx = -1;
    }


    if (agentsShuffle[agent]->y - ycoord < 0) {
        dy = 1;
    }

    if (agentsShuffle[agent]->y - ycoord == 0) {
        dy = 0;
    }

    if (agentsShuffle[agent]->y - ycoord > 0) {
        dy = -1;
    }

    destination = border(x, y, dx, dy);

    if (grid[destination.x][destination.y] == NULL) {

        /* Destination in grid receives agent from actual position. */
        grid[destination.x][destination.y] = grid[x][y];
        /* Change position in the array we use to shuffle */
        agentsShuffle[agent]->x = destination.x;
        agentsShuffle[agent]->y = destination.y;

        /* Old position is now NULL */
        grid[x][y] = NULL;
    }
    else {
        if (grid[destination.x][destination.y]->type == Human) {
            /* Transform human into zombie */
            grid[destination.x][destination.y]->type = Zombie;
            /* One less human */
            (*NHUMANS)--;
        }

        /* Change type in array that we use to shuffle */
        for (int i = 0; i < NAGENTS; i++) {
            if ((agentsShuffle[i] != NULL) &&
            (agentsShuffle[i]->x == destination.x) &&
            (agentsShuffle[i]->y == destination.y)) {
                agentsShuffle[i]->type = Zombie;
            }
        }
    }
}

void human_move(AGENT *grid[WORLD_X][WORLD_Y], AGENT **agentsShuffle,
                int x, int y, int xcoord, int ycoord, int agent) {

    COORDINATES destination;
    int dx, dy;

    /* If actual agent coord X - enemy coord X < 0 then destination X = -1 */
    if (agentsShuffle[agent]->x - xcoord < 0) {
        dx = -1;
    }
    /* If actual agent coord X - enemy coord X == 0 then destination X = 0 */
    if (agentsShuffle[agent]->x - xcoord == 0) {
        dx = 0;
    }
    /* If actual agent coord X - enemy coord X > 0 then destination X = 1 */
    if (agentsShuffle[agent]->x - xcoord > 0) {
        dx = 1;
    }


    if (agentsShuffle[agent]->y - ycoord < 0) {
        dy = -1;
    }

    if (agentsShuffle[agent]->y - ycoord == 0) {
        dy = 0;
    }

    if (agentsShuffle[agent]->y - ycoord > 0) {
        dy = 1;
    }

    destination = border(x, y, dx, dy);

    if (grid[destination.x][destination.y] == NULL) {

        /* Destination in grid receives agent from actual position. */
        grid[destination.x][destination.y] = grid[x][y];
        /* Change position in the array we use to shuffle */
        agentsShuffle[agent]->x = destination.x;
        agentsShuffle[agent]->y = destination.y;

        /* Old position is now NULL */
        grid[x][y] = NULL;
    }
}
