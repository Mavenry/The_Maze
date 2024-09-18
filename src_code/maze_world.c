#include "../maze.h"

/**
 * build_world_from_args - Constructs the game world from the provided level files
 * @num_of_lvls: The total number of levels (command-line arguments passed)
 * @level_files: Array of strings representing file paths for each level
 * 
 * This function creates a series of levels for the game by reading the maze layout
 * from each file provided as a command-line argument. It dynamically allocates memory
 * for an array of level structures, and each level is populated with its map, player's
 * starting position, win condition, and other necessary data. The function will return
 * NULL if any error occurs during map creation or memory allocation.
 * 
 * Return: Pointer to an array of levels if successful, or NULL on failure
 **/
level *build_world_from_args(int num_of_lvls, char *level_files[])
{
	level stage = {NULL, 0, {0, 0}, {2, 2}, {-1, 0}, {0, 0.5} };  // Initialize a default stage
	level *levels;
	int i, lvl;

	// Allocate memory for an array of levels, one for each level file
	levels = malloc(sizeof(level) * (num_of_lvls - 1));
	if (levels == NULL)
		return (NULL);  // Return NULL if memory allocation fails

	lvl = 0;
	// Iterate through each level file starting from the first argument (index 1)
	for (i = 1; i < num_of_lvls; i++, lvl++)
	{
		// Create the map for the current level and set up the stage properties
		stage.map = create_map(level_files[i], &stage.play, &stage.win,
				       &stage.height);
		if (stage.map == NULL)
			return (NULL);  // Return NULL if map creation fails

		// Store the current stage in the levels array
		levels[lvl] = stage;
	}
	return (levels);  // Return the array of levels
}

