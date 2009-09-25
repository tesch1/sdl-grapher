#ifndef GRAPH_H
#define GRAPH_H

#include <SDL/SDL.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

/* TODO: 
 * Error handling
 */

struct graph {
	
	float xMin;          /* Indicates the smallest value the graph window will show on the x-axis. */
	float xMax;			 /* Largest x */
	float xScale;		 /* Indicates the distance between the "landmarks" on the x-axis */
	float yMin;			 /* Same as indicated over, just on the y-axis */
	float yMax;
	float yScale;
	int width;			 /* When the SDL window is initialized, these values will decide the size of it in pixels */
    int height;
    
    Uint32 color;        /* When a pixel is printed to the screen, this variable will be used to determine which color
						  * is to be printed on the screen */
    
    SDL_Surface * workingSurface; /* This is the main SDL_Surface that is used transparently in most functions below */
};


void drawGrid(struct graph *, int, int);
/* This function will draw a grid to the SDL_Surface in the graph-struct. The function also takes
 * thickness of grid and length of the "landmarks" on the grid. 0 length/thickness indicates smallest possible
 * e.g. ( 1 pixel width ) */

Uint32 * get_pixel_from_coordinates ( struct graph *, float, float );
/* Returns a pointer to a certain pixel by the means of giving it coordinates on the graph */

Uint32 * get_pixel_from_window ( struct graph *, int, int );
/* Returns a pointer to a certain pixel by the means of giving it the coorinates on the SDL window itself. 
 * e.g ( 0, 0) will always return the top-left pixel */

int get_width_from_coordinate ( struct graph *, float x );
/* Returns the x coordinate on the SDL window itself by using a graph coordinate */

int get_height_from_coordinate ( struct graph *, float y );
/* Returns the y coordinate */

void init_graph ( struct graph * );
/* Initializes the graph. Sets up an SDL window. This function must be executed before any other API functions!
 * The struct it takes as input must be properly filled in before calling this. */

void print_pixel ( struct graph *, float, float );
/* Prints a pixel to the surface in the struct by using graph coordinates */

void print_pixel_by_window ( struct graph *, int, int );
/* Prints a pixel to the surface in the struct by using SDL window coordinates */

void updateScreen(struct graph *);
/* Updates the screen. Performance tip: When printing many points to the screen, do not
 * refresh screen for every print. Print some points, then refresh. */

void delay ( int );
/* Halts further execution of the application. (Useful for animation)
 * Input is given in milliseconds. e.g. delay(1000); halts for 1 second. */

void clear_graph(struct graph *);
/* Clears the graph, returning it to the initial black state.
 * (Still need to updateScreen to see the result! */

void idle();
/* Will idle here until user quits program. */

void setColor(struct graph *, int, int, int);
/* Sets the color in the struct given in normal 24-bit RGB format */

void quit();
/* Instantly quits the program */
	
#endif
