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
 * Header file of a simple function which shows/updates an ASCII-based
 * visualization of the current state of the simulation world.
 *
 * @note Students should change or replace this file in the second part of the
 * project.
 *
 * @author Nuno Fachada
 * @date 2017
 * @copyright [GNU General Public License version 3 (GPLv3)](http://www.gnu.org/licenses/gpl.html)
 * */

#ifndef SIMPLE_SHOWWORLD_H
#define SIMPLE_SHOWWORLD_H

#include "showworld.h"

/* Simple function which shows/updates an ASCII-based visualization of the
 * current state of the simulation world. This function follows the type
 * definition ::show_world() specified in showworld.h. */
void simple_show_world(
    void *world,
    unsigned int xdim,
    unsigned int ydim,
    get_agent_info_at ag_info);

#endif
