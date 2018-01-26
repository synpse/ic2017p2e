/*
 * This file is part of "Projeto de Introdução à Computação 2ª época 2017/2018"
 * (PIC2e1718).
 *
 * PIC2e1718 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * PIC2e1718 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with PIC2e1718. If not, see <http://www.gnu.org/licenses/>.
 * */

/**
 * @file
 * This file is an example of: a) how to use the API defined in the
 * showworld.h header (mandatory for the project); and, b) how to use the
 * concrete simple implementation of the API (provided by the
 * showworld_simple.c file).
 *
 * @author Nuno Fachada
 * @date 2018
 * @copyright [GNU General Public License version 3 (GPLv3)](http://www.gnu.org/licenses/gpl.html)
 * */

#include "showworld.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/** Horizontal world size. */
#define WORLD_X 20

/** Vertical world size. */
#define WORLD_Y 20

/** Number of human agents. */
#define NHUMANS 20

/** Number of zombie agents. */
#define NZOMBIES 20

/** Number of playable human agents. */
#define NHUMANS_PLAY 1

/** Number of playable zombie agents. */
#define NZOMBIES_PLAY 0

/**
 * Structure defining agent properties.
 *
 * @note This is an example which will probably not work in a fully functional
 * game. Students should develop their own implementation of agent in agent.h
 * and agent.c files, with new/destroy functions.
 * */
typedef struct {
    AGENT_TYPE type;        /**< Agent type.        */
    unsigned char playable; /**< Is agent playable? */
    unsigned short id;      /**< Agent ID.          */
} AGENT;

/* This function is an implementation of the definition provided by the
 * ::get_agent_info_at() function pointer. It only works for AGENT example
 * structure defined in this file. */
unsigned int example_get_ag_info(void *world, unsigned int x, unsigned int y);

/**
 * This `main` function is only an example of: a) how to use the API defined in
 * the showworld.h header (mandatory for the project); and, b) how to use the
 * concrete simple implementation of the API (provided in the
 * showworld_simple.c file).
 *
 * @return Always zero.
 * */
int main() {

    /* An instance of a SHOWWORLD world display. */
    SHOWWORLD *sw = NULL;

    /* A by-dimensional array of agent pointers, representing agents in a
       grid. In the final project the agent grid or world should be abstracted
       to specific world.c/world.h files, with new/destroy functions (see files
       from aula 12).
       All elements in this grid are initialized to NULL, i.e., they don't
       initially point to anything. */
    AGENT *grid[WORLD_X][WORLD_Y] = { NULL };

    /* Initialize world display. */
    sw = showworld_new(WORLD_X, WORLD_Y, example_get_ag_info);

    /* Initialize random number generator. */
    srand(time(NULL));

    /* ************************************* */
    /* Create and place human agents in grid */
    /* ************************************* */
    for (int i = 0; i < NHUMANS; ++i) {

        /* Determine random x and y coordinates. */
        unsigned int x = rand() % WORLD_X;
        unsigned int y = rand() % WORLD_Y;

        /* Check if there those coordinates are vacant, so we can put a new
           agent in them. */
        if (grid[x][y] == NULL) {

            /* Is current agent supposed to be playable? */
            unsigned char playable = (i < NHUMANS_PLAY);

            /* Create new agent and initialize its values. In a real project
               you should have agent_new() and agent_destroy() functions and
               not use malloc directly here. */
            AGENT *ag = malloc(sizeof(AGENT));
            ag->type = Human;
            ag->playable = playable;
            ag->id = (unsigned short) i;

            /* Put agent in grid. In a real project you should probably have
               a world_put() function or similar (like in Aula 12). */
            grid[x][y] = ag;

        } else {

            /* If we get here it's because the grid position already has an
               agent in it. In this case we need to obtain new random (x,y)
               coordinates, but we also need to decrement the counter so in
               the end we have the correct number of agents. */
            i--;
        }

    }

    /* ********************************************************************* */
    /* Create and place zombie agents in grid. This for loop is very similar */
    /* to the previous one for humans, so consider putting this common code  */
    /* in a function.                                                        */
    /* ********************************************************************* */
    for (int i = 0; i < NZOMBIES; ++i) {

        /* Determine random x and y coordinates. */
        unsigned int x = rand() % WORLD_X;
        unsigned int y = rand() % WORLD_Y;

        /* Check if there those coordinates are vacant, so we can put a new
           agent in them. */
        if (grid[x][y] == NULL) {

            /* Is current agent supposed to be playable? */
            unsigned char playable = (i < NZOMBIES_PLAY);

            /* Create new agent and initialize its values. In a real project
               you should have agent_new() and agent_destroy() functions and
               not use malloc directly here. */
            AGENT *ag = malloc(sizeof(AGENT));
            ag->type = Zombie;
            ag->playable = playable;
            ag->id = (unsigned short) i + NHUMANS;

            /* Put agent in grid. In a real project you should probably have
               a world_put() function or similar (like in Aula 12). */
            grid[x][y] = ag;

        } else {

            /* If we get here it's because the grid position already has an
               agent in it. In this case we need to obtain new random (x,y)
               coordinates, but we also need to decrement the counter so in
               the end we have the correct number of agents. */
            i--;
        }

    }

    /* ********************************************************************* */
    /* Show world using the simple_show_world() function. This function can  */
    /* be used in the first part of the project.                             */
    /* ********************************************************************* */
    showworld_update(sw, grid);

    /* Before finishing, ask user to press ENTER. */
    printf("Press ENTER to continue...");
    getchar();

    /* Destroy all agents. */
    for (int i = 0; i < WORLD_X; i++) {
        for (int j = 0; j < WORLD_Y; j++) {
            if (grid[i][j] != NULL) {
                /* In the final project we should have an agent_destroy()
                   function. */
                free(grid[i][j]);
            }
        }
    }

    /* Destroy world display. */
    showworld_destroy(sw);

    /* Bye. */
    return 0;
}

/**
 * This function is an implementation of the ::get_agent_info_at() function
 * definition. It only works for the ::AGENT structure defined in this example,
 * and considers the agent world as a 2D grid of agent pointers (as defined in
 * main).
 *
 * It basically receives a pointer to a 2D grid of agent pointers, obtains the
 * AGENT pointer in the given coordinates, and returns the agent information in
 * a bit-packed `unsigned int`.
 *
 * @note This is an example which will probably not work in a fully functional
 * game. Students should develop their own implementation of
 * ::get_agent_info_at() and agent/world data structures.
 *
 * @param w Generic pointer to object representing the simulation world.
 * @param x Horizontal coordinate of the simulation world from where to fetch
 * the agent information.
 * @param y Vertical coordinate of the simulation world from where to fetch
 * the agent information.
 * @return An integer containing bit-packed information about an agent, as
 * follows: bits 0-1 (agent type), bit 2 (is agent playable), bits 3-18 (agent
 * ID). Bits 19-31 are available for student-defined agent extensions.
 * */
unsigned int example_get_ag_info(void *w, unsigned int x, unsigned int y) {

    /* The agent information to return. */
    unsigned int ag_info = 0;

    /* Convert generic pointer to world to a 2D grid of agent pointers (in
       practice we are reinterpreting the grid as 1D). */
    AGENT **grid = (AGENT **) w;

    /* Check if the given (x,y) coordinates are within bounds of the world. */
    if ((x >= WORLD_X) || (y >= WORLD_Y)) {

        /* If we got here, then the coordinates are off bounds. As such we will
           report that the requested agent is of unknown type. No need to
           specify agent ID or playable status, since the agent is unknown. */
        ag_info = Unknown;

    } else {

        /* Given coordinates are within bounds, let's get and pack the request
           agent information. */

        /* Obtain agent at specified coordinates. */
        AGENT *ag = grid[x * WORLD_Y + y];

        /* Is there an agent at (x,y)? */
        if (ag == NULL) {

            /* If there is no agent at the (x,y) coordinates, set agent type to
               None. No need to specify agent ID or playable status, since
               there is no agent here. */
            ag_info = None;

        } else {

            /* If we get here it's because there is an agent at (x,y). Bit-pack
               all the agent information as specified by the get_agent_info_at
               function pointer definition. */
            ag_info = (ag->id << 3) | (ag->playable << 2) | ag->type;

        }

    }

    /* Return the requested agent information. */
    return ag_info;
}
