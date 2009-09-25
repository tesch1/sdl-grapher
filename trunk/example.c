#include <sdlgraph.h>

int main()
{
	struct graph myGraph;
	
	myGraph.xMin = -10.0;
	myGraph.xMax = 10.0;
	myGraph.xScale = 1.0;
	myGraph.yMin = -10.0;
	myGraph.yMax = 10.0;
	myGraph.yScale = 1.0;
	myGraph.width = 500;
	myGraph.height = 500;
	
	/* Sets some initial values for the graph. These MUST be defined before you run
	 * init_graph()! */
	
	init_graph(&myGraph); /* Initialized the graph, which gives you a normal SDL window */
	
	drawGrid(&myGraph, 0, 2); /* Draws a grid in origo. With thickness 0 (1 pixel), and after each xScale or yScale, draw
									some "landmarks". These will be 5 pixels high (2*2 + 1). */

	int count;
        float x, y;

    setColor(&myGraph, 0, 0xFF, 0); /* Normal RGB fashion. Sets all points written to screen to be green */
    
	for ( count = -100; count < 100; count++ )
	{
		x = count/10.0; /* x will go from -10 to 10 with interval 0.1 */
		y = 5.0*sin(x)/x; /* y is the result of f(x) = 5*sin(x)/x. You might run into "diving by zero" errors. :D */

		print_pixel(&myGraph, x, y); /* Prints a pixel to the screen on the graph coordinated (x,y).
										Since this goes through a loop, you print out the entire graph. */
		delay(10);					 /* Waits 10ms between each point printed. */
		updateScreen(&myGraph);      /* Updates the screen. You now have a cool graph animation :D */
	}
	
	delay(2000); /* Waits two seconds ... */
	
	clear_graph(&myGraph); /* Clears out the graph */
	
	setColor(&myGraph, 0, 0, 0xFF); /* Changes color to be blue */
	
	drawGrid(&myGraph, 1, 250); /* Draws a full grid on the screen */
	
	updateScreen(&myGraph);
	
	setColor(&myGraph, 0xFF, 0xFF, 0xFF); 
	
	for ( count = -1000; count < 1000; count++ )
	{
		x = count/100.0;
		
		y = exp(x);
		delay(10);
		print_pixel(&myGraph, x, y);
		updateScreen(&myGraph);
		
		/* Prints out the exp(x) function */ 
	}
	

	idle(); /* Waits for the user to exit the program. */
	quit(); /* Quits ... baibai! */



	
	return 0;
}
