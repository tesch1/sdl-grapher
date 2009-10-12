/*  sdl-grapher - SDL library
 *  Copyright (C) 2009 - Hans-Kristian Arntzen
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

#include "sdlgraph.h"

Uint32 * get_pixel_from_coordinates ( Graph * myGraph, float x, float y )
{
  	Uint32 * pixel;
  	
	int realWidth = get_width_from_coordinate(myGraph, x); 
  	
  	
	int realHeight = get_height_from_coordinate(myGraph, y);
  	
  	
  	if ( realHeight < 0 || realHeight >= myGraph->height || realWidth < 0 || realWidth >= myGraph->width )
		return NULL;
  	else
  	{
		pixel = myGraph->workingSurface->pixels;
		
		Uint32 width,height;
		width = realWidth;
		height = realHeight * myGraph->width;
		pixel += width + height;
		
		return pixel;
	}

}

Uint32 * get_pixel_from_window ( Graph * myGraph, int x, int y )
{
  	Uint32 * pixel;
  	
  	if ( y < 0 || y >= myGraph->height || x < 0 || x >= myGraph->width )
		return NULL;
  	else
  	{
		Uint32 width,height;
		width = x;
		height = y * myGraph->width;
		pixel = (Uint32*)myGraph->workingSurface->pixels + width + height;
		return pixel;
	}

}

int get_width_from_coordinate ( Graph * myGraph, float x )
{
  	int realWidth = (int)((float)myGraph->width * (x - myGraph->xMin) / (myGraph->xMax - myGraph->xMin));
	
	return realWidth;	
}

int get_height_from_coordinate ( Graph * myGraph, float y )
{
  	int realHeight = (int)((float)myGraph->height - (float)myGraph->height * (y - myGraph->yMin) / (myGraph->yMax - myGraph->yMin));
	
	return realHeight;	
}

void init_graph ( Graph * myGraph )
{
	
    myGraph->workingSurface = SDL_SetVideoMode(myGraph->width, myGraph->height, 32, SDL_SWSURFACE);
    SDL_WM_SetCaption("GRAPH OUTPUT", NULL);
    set_color(myGraph, 0xFF, 0xFF, 0xFF);
      
}

void draw_grid ( Graph * myGraph, int thickness, int length )
{
	
	
	int height, width;
	
	thickness = abs(thickness);
	length = abs(length);
	
	
	height = get_height_from_coordinate(myGraph, 0.0);
	width = get_width_from_coordinate(myGraph, 0.0);
	
	
	int countX, countY;
	
	int pitchX, pitchY;
	pitchX = get_width_from_coordinate(myGraph, myGraph->xScale) - width;
	pitchY = get_height_from_coordinate(myGraph, myGraph->yScale) - height;
	
	
	for ( countX = 0; countX < myGraph->width; countX++ )
	{
		
		
		if ( (countX - width) % pitchX == 0 )
		{
			
			for ( countY = height - length; countY <= height + length; countY++ )
			{
				print_pixel_by_window(myGraph, countX, countY);
			}
		}
		
		else
		{
			for ( countY = height - thickness; countY <= height + thickness; countY++ )
			{
				
		    
				print_pixel_by_window ( myGraph, countX, countY );
			}
		}
	}
	
	for ( countY = 0; countY < myGraph->height; countY++ )
	{
		
		if ( ((countY - height) % pitchY) == 0 )
		{
			
			for ( countX = width - length; countX <= width + length; countX++ )
			{
				
			   
				print_pixel_by_window ( myGraph, countX, countY );
			}
		}
		
		
		else
		{
			for ( countX = width - thickness; countX <= width + thickness; countX++ )
			{
			   
				print_pixel_by_window ( myGraph, countX, countY );
			}
		}
	}
	
	 
}

void print_pixel_by_window ( Graph * myGraph, int x, int y )
{
	Uint32 * pixel;
	SDL_Event event;
	if ( SDL_PollEvent ( &event ) )
	{
		if (event.type == SDL_QUIT)
		{
				quit();
		}
	}
	
	
		pixel = get_pixel_from_window( myGraph, x, y );
	
		if( pixel != NULL )
			*pixel = myGraph->color;
	
	
}
	
void print_pixel ( Graph * myGraph, float x, float y )
{
	Uint32 * pixel;
	SDL_Event event;
	if ( SDL_PollEvent ( &event ) )
	{
		if (event.type == SDL_QUIT)
		{
				quit();
		}
	}
	
		pixel = get_pixel_from_coordinates( myGraph, x, y );
	
		if( pixel != NULL )
			*pixel = myGraph->color;
	
}
	
void update_screen(Graph * myGraph)
{
	if (SDL_Flip(myGraph->workingSurface) != 0) quit();
}

void delay ( int time )
{
	int startTime = SDL_GetTicks();
	
	SDL_Event event;
	
	while ( (SDL_GetTicks() - startTime) < time )
	{
		if ( SDL_PollEvent ( &event ) )
		{
			if (event.type == SDL_QUIT)
			{
				quit();
			}
		}
		else 
			SDL_Delay( 1 );
	}
}

void clear_graph(Graph * myGraph)
{
	Uint32 color;
	color = SDL_MapRGB(myGraph->workingSurface->format, 0x00, 0x00, 0x00);
	SDL_FillRect(myGraph->workingSurface, NULL, color);
}

void idle()
{
	SDL_Event event;
	while ( 1 )
	{
		if ( SDL_PollEvent ( &event ) )
		{
			if (event.type == SDL_QUIT)
			{
				quit();
			}
		}
		else
			delay(1);
	}
}

void set_color(Graph * window, int r, int g, int b)
{
	window->color = SDL_MapRGB(window->workingSurface->format, r, g, b);
}
		
void quit()
{
	SDL_Quit();
	exit(0);
}
