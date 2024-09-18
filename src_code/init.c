#include "../maze.h"

/**
 * init_instance - Initialize an SDL instance with a window and renderer.
 * @instance: The SDL_Instance to initialize.
 * 
 * Return: 1 if initialization fails, 0 on success.
 * 
 * Description: This function sets up an SDL window and renderer for the game. 
 * It initializes the SDL video subsystem, creates a centered window titled 
 * "MAZE" with specified width and height, and sets up an accelerated renderer 
 * with vertical sync. If any step fails, it cleans up and returns an error code.
 **/
int init_instance(SDL_Instance *instance)
{
	/* Initialize SDL video subsystem */
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("SDL_Init Error: %s\n", SDL_GetError());
		return (1);  // Return 1 if initialization fails
	}

	/* Create a window centered on the screen */
	instance->window = SDL_CreateWindow("MAZE", SDL_WINDOWPOS_CENTERED,
					    SDL_WINDOWPOS_CENTERED,
					    SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if (instance->window == NULL)
	{
		/* Clean up and return on failure */
		SDL_Quit();
		return (1);
	}

	/* Create a renderer with hardware acceleration and vertical sync */
	instance->renderer = SDL_CreateRenderer(instance->window, -1,
						SDL_RENDERER_ACCELERATED |
						SDL_RENDERER_PRESENTVSYNC);
	if (instance->renderer == NULL)
	{
		/* Destroy the window and quit SDL if renderer creation fails */
		SDL_DestroyWindow(instance->window);
		SDL_Quit();
		return (1);
	}
	
	/* Return 0 on successful initialization */
	return (0);
}

