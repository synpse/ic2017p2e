
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "simple_showworld.h"

/** Horizontal world size. */
#define WORLD_X 20

/** Vertical world size. */
#define WORLD_Y 20

/**
 * Structure defining agent properties.
 *
 * @note This is an example which will probably not work in a fully functional
 * game. Students should develop their own implementation of ::get_agent_info()
 * and agent/world data structures.
 * */
typedef struct {
    AGENT_TYPE type;        /**< Agent type.        */
    unsigned char playable; /**< Is agent playable? */
    unsigned short id;      /**< Agent ID.          */
} AGENT;

/**
 * Structure defining world properties.
 *
 * @note This is an example which will probably not work in a fully functional
 * game. Students should develop their own implementation of ::get_agent_info()
 * and agent/world data structures.
 * */
typedef struct {
    AGENT *grid;        /**< World is a grid composed of agents. */
    unsigned int xsize; /**< Horizontal world size.              */
    unsigned int ysize; /**< Vertical world size.                */
} WORLD;

/* This function is an implementation of the definition provided by the
 * get_agent_info() function pointer. It only works for AGENT and WORLD
 * example structures defined in this file. */
unsigned int example_get_ag_info(void *world, unsigned int x, unsigned int y);
