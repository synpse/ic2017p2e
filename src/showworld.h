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
 * Header file for generic function to show/update the visualization of the
 * current state of the simulation world.
 *
 * @note Students should **not** change this file.
 *
 * @author Nuno Fachada
 * @date 2017
 * @copyright [GNU General Public License version 3 (GPLv3)](http://www.gnu.org/licenses/gpl.html)
 * */

/**
 * Type of agent.
 * */
enum agent_type {
    None = 0x0,   /**< No agent present.     */
    Human = 0x1,  /**< Human agent present.  */
    Zombie = 0x2  /**< Zombie agent present. */
};

/**
 * Show/update the visualization the current state of the simulation world.
 *
 * @param world Generic pointer to object representing the simulation world.
 * @param xdim Horizontal dimension of the simulation world (number of columns).
 * @param ydim Vertical dimension of the simulation world (number of rows).
 * @param get_item_at Function which obtains the type of agent in the
 * simulation world at coordinates (_x_,_y_).
 * */
void show_world(
    void *world,
    unsigned int xdim,
    unsigned int ydim,
    unsigned short (*get_item_at)(void *world, int x, int y));
