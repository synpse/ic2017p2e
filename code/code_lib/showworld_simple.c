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
 * Implementation of the interface defined in showworld.h which displays an
 * ASCII-based visualization of the current state of the simulation world.
 *
 * @note Students should change or replace this file with a new implementation
 * making use of graphical or game library.
 *
 * @author Nuno Fachada
 * @date 2018
 * @copyright [GNU General Public License version 3 (GPLv3)](http://www.gnu.org/licenses/gpl.html)
 * */

#include "showworld.h"
#include <stdio.h>
#include <stdlib.h>
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_color.h"

/* The implementation of `SHOWWORLD` type used in this simple text-based world
 * visualization code. In this simple case, we only need to keep track of the
 * world dimensions and of the function pointer which knows how to read an
 * agent from the world data structure.
 *
 * For a more complex implementation, for example based on the g2 library,
 * it would also be necessary to keep the g2 device.
 * */
struct showworld {
    unsigned int xdim;
    unsigned int ydim;
    get_agent_info_at aginfo_func;
};

/* Initialize variable that holds the canvas */
ALLEGRO_DISPLAY *screen = NULL;

/* Initialize AGENT Images to NULL */
ALLEGRO_BITMAP *human = NULL;
ALLEGRO_BITMAP *zombie = NULL;
ALLEGRO_BITMAP *background = NULL;

/* Agents width and height */
int ag_w = 0, ag_h = 0;

/* Create a new display/visualization object for the simulation world.
 *
 * This function obeys the `showworld_new()` prototype defined in
 * `showworld.h`. */
SHOWWORLD *showworld_new(
    unsigned int xdim,
    unsigned int ydim,
    get_agent_info_at aginfo_func) {
	
    al_init();
    al_init_image_addon();

    SHOWWORLD *sw = NULL;
    sw = malloc(sizeof(SHOWWORLD));
    sw->xdim = xdim;
    sw->ydim = ydim;
    sw->aginfo_func = aginfo_func;
	
	/* Define agent width and height to fit on
    a 500 by 500 display */
    ag_w = 500/(sw->xdim);
    ag_h = 500/(sw->ydim);
 
	/* Initialize the window display */
    if((sw->xdim) == (sw->ydim)) {
      screen = al_create_display(500,500);
    }
	
	/* Load the images */
    human = al_load_bitmap("sprite_human.png");
    zombie = al_load_bitmap("sprite_zombie.png");
    background = al_load_bitmap("sprite_tile.png");
	
	/* Clear the background's color */
    al_clear_to_color(al_map_rgb(0,0,0));

	return sw;
}

/* Destroy a display/visualization object for the simulation world.
 *
 * This function obeys the `showworld_destroy()` prototype defined in
 * `showworld.h`. */
void showworld_destroy(SHOWWORLD *sw) {
	
    al_destroy_bitmap(human);
    al_destroy_bitmap(zombie);
	al_destroy_bitmap(background);
    al_destroy_display(screen);
    free(sw);
}

/* Update the simulation world display/visualization.
 *
 * This function obeys the `showworld_update()` prototype defined in
 * `showworld.h`. */
void showworld_update(SHOWWORLD *sw, void *w) {

    printf("\n");

    /* Cycle through all the rows */
    for (unsigned int y = 0; y < sw->ydim; ++y) {

        /* Cycle through all the columns for the current row */
        for (unsigned int x = 0; x < sw->xdim; ++x) {

            /* Get state of the world (in bit packed fashion) using the user
               supplied function. */
            unsigned int item = sw->aginfo_func(w, x, y);

            /* Extract the agent type (2 bits). */
            AGENT_TYPE ag_type = item & 0x3;
            /* Extract whether the agent is playable (1 bit). */
            unsigned char playable = (item >> 2) & 0x1;
            /* Extract the agent ID (16 bits). */
            unsigned short ag_id = (item >> 3) & 0xFFFF;

            /* Determine the agent type. */
            switch (ag_type) {

                /* If no agent is present at (x,y) just print the background */
                case None:
                    al_draw_scaled_bitmap(background, 0, 0, 50, 50,
                                          x*ag_w, y*ag_h,
                                          ag_w, ag_h, 0);
                    break;

                /* If human agent present at (x,y) print its png */
                case Human:
					if (playable || !playable) {
						/* draw human agent */
                    	al_draw_scaled_bitmap(human, 0, 0, 50, 50,
                                              x*ag_w, y*ag_h,
                                              ag_w, ag_h, 0);
						/* Print the agent ID in front of the 'h'/'H'. */
						printf("%02X ", ag_id);
						break;
					}

                /* If zombie agent present at (x,y) print its png */
                case Zombie:
					if (playable || !playable) {
						
                		/* draw zombie agent */
                    	al_draw_scaled_bitmap(zombie, 0, 0, 50, 50,
                                              x*ag_w, y*ag_h,
                                              ag_w, ag_h, 0);
						/* Print the agent ID in front of the 'h'/'H'. */
						printf("%02X ", ag_id);
						break;
					}
					
                /* Print '?' if unknown type detected. */
                default:
                    printf("?   ");

            }
        }
    }
	
	/* Function to see the objects */
    al_flip_display();

}
