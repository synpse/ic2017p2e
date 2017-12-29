/*
 * This file is part of "2º Projeto de Introdução à Computação 2017/2018"
 * (2oPIC1718).
 *
 * 2oPIC1718 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * 2oPIC1718 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with 2oPIC1718. If not, see <http://www.gnu.org/licenses/>.
 * */

/**
 * @file
 * Implementation of a simple function which shows/updates an ASCII-based
 * visualization of the current state of the simulation world.
 *
 * @note Students should change or replace this file in the second part of the
 * project.
 *
 * @author Nuno Fachada
 * @date 2017
 * @copyright [GNU General Public License version 3 (GPLv3)](http://www.gnu.org/licenses/gpl.html)
 * */

#include "simple_showworld.h"
#include <stdio.h>

/**
 * Simple function which shows/updates an ASCII-based visualization of the
 * current state of the simulation world. This function follows the type
 * definition ::show_world() specified in showworld.h.
 *
 * @param world Generic pointer to object representing the simulation world.
 * @param xdim Horizontal dimension of the simulation world (number of columns).
 * @param ydim Vertical dimension of the simulation world (number of rows).
 * @param ag_info Pointer to function which obtains the type of agent in the
 * simulation world at coordinates (_x_,_y_).
 * */
void simple_show_world(
    void *world,
    unsigned int xdim,
    unsigned int ydim,
    get_agent_info_at ag_info) {

    printf("\n");

    /* Cycle through all the rows */
    for (unsigned int y = 0; y < ydim; ++y) {

        /* Cycle through all the columns for the current row */
        for (unsigned int x = 0; x < xdim; ++x) {

            /* Get state of the world (in bit packed fashion) using the user
               supplied function. */
            unsigned int item = ag_info(world, x, y);

            /* Extract the agent type (2 bits). */
            AGENT_TYPE ag_type = item & 0x3;
            /* Extract whether the agent is playable (1 bit). */
            unsigned char playable = (item >> 2) & 0x1;
            /* Extract the agent ID (16 bits). */
            unsigned short ag_id = (item >> 3) & 0xFFFF;

            /* Determine the agent type. */
            switch (ag_type) {

                /* If no agent is present at (x,y) just print a dot. */
                case None:
                    printf(" .  ");
                    break;

                /* If human agent present at (x,y) print 'h' or 'H'. */
                case Human:
                    if (playable) {
                        /* Uppercase 'H' for player-controlled human agent. */
                        printf("H");
                    } else {
                        /* Lowercase 'h' for AI-controlled human agent. */
                        printf("h");
                    }
                    /* Print the agent ID in front of the 'h'/'H'. */
                    printf("%02X ", ag_id);
                    break;

                /* If zombie agent present at (x,y) print 'z' or 'Z'. */
                case Zombie:
                    if (playable) {
                        /* Uppercase 'Z' for player-controlled zombie agent. */
                        printf("Z");
                    } else {
                        /* Lowercase 'z' for AI-controlled zombie agent. */
                        printf("z");
                    }
                    /* Print the agent ID in front of the 'h'/'H'. */
                    printf("%02X ", ag_id);
                    break;

                /* Print '?' if unknown type detected. This should *never*
                   happen. */
                default:
                    printf("?   ");

            }
        }

        /* Print two newlines after each row. */
        printf("\n\n");

    }

    /* Print a newline after world is shown/updated. */
    printf("\n");

}
