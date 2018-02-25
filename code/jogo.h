#ifndef JOGO_H
#define JOGO_H

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

 #define WORLD_X 20
 #define WORLD_Y 20
 //extern const int WORLD_X;
 //extern const int WORLD_Y;
 extern int NZOMBIES; 
 extern int NHUMANS;
 extern int NZOMBIES_PLAY;
 extern int NHUMANS_PLAY;
 extern int TURNS;

#include "showworld.h"

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
    int x;                 /**< Coordinate X.       */
    int y;                 /**< Coordinate Y.       */
} AGENT;

/* This function is an implementation of the definition provided by the
 * ::get_agent_info_at() function pointer. It only works for AGENT example
 * structure defined in this file. */
unsigned int example_get_ag_info(void *world, unsigned int x, unsigned int y);

#endif
