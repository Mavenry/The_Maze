#include "../maze.h"

/**
 * free_memory - Frees all allocated resources, including the map and SDL instance.
 * @instance: SDL_Instance containing the window and renderer.
 * @map: 2D array representing the map of the play space.
 * @map_h: The height of the map (number of rows in the 2D array).
 *
 * Description: This function calls `free_map` to free the dynamically
 * allocated memory for the 2D map array, and `close_SDL` to properly
 * shut down the SDL instance by destroying the window and renderer.
 **/
void free_memory(SDL_Instance instance, char **map, size_t map_h)
{
	free_map(map, map_h);  /* Free the 2D map array */
	close_SDL(instance);   /* Close the SDL window and renderer */
}

/**
 * free_map - Frees the memory used by the map 2D array.
 * @map: 2D array representing the map of the play space.
 * @map_h: The height of the map (number of rows in the 2D array).
 *
 * Description: Iterates through each row of the 2D map array and frees
 * the memory allocated for each row. The number of rows is determined
 * by the value of map_h.
 **/
void free_map(char **map, size_t map_h)
{
	size_t i = 0;

	/* Free each row of the 2D array */
	while (i < map_h)
	{
		free(map[i]);
		i++;
	}
}

/**
 * close_SDL - Closes the SDL window and renderer.
 * @instance: SDL_Instance structure containing the SDL window and renderer.
 *
 * Description: Properly shuts down SDL by destroying the window and renderer,
 * and calling SDL_Quit() to clean up all initialized SDL subsystems.
 **/
void close_SDL(SDL_Instance instance)
{
	SDL_DestroyRenderer(instance.renderer);  /* Destroy the SDL renderer */
	SDL_DestroyWindow(instance.window);      /* Destroy the SDL window */
	SDL_Quit();                              /* Clean up all SDL subsystems */
}

