#include "../maze.h"

/**
 * main - Entry point for the maze game
 * @argc: The number of command-line arguments passed to the program
 * @argv: The array of command-line arguments, including file paths for maze levels
 * 
 * This is the main function responsible for initializing the game, handling player input,
 * rendering the maze, checking win conditions, and managing levels. It continues to loop
 * through the levels until the player either wins or quits the game. Upon winning, it
 * prints a congratulatory message.
 * 
 * Return: 1 if the game fails to start or encounters an error, otherwise 0 on successful exit
 **/
int main(int argc, char *argv[])
{
	SDL_Instance instance;  // Holds the SDL instance for rendering
	level *levels;           // Array of levels, each represented by a maze
	int lvl, win_value, num_of_levels;
	keys key_press = {0, 0, 0, 0};  // Struct to track keyboard input for movement

	lvl = win_value = 0;  // Initialize level and win flag
	num_of_levels = argc;  // Number of levels equals number of command-line arguments
	if (num_of_levels < 2)
		return (1);  // Exit if no levels are provided

	// Build the game world using the maze files passed via command-line arguments
	levels = build_world_from_args(argc, argv);
	if (levels == NULL)
		return (1);  // Exit if level creation fails

	// Initialize the SDL instance for rendering the maze and handling input
	if (init_instance(&instance) != 0)
		return (1);  // Exit if SDL initialization fails

	// Main game loop
	while (1)
	{
		// Check for player input and quit if necessary
		if (keyboard_events(&key_press))
		{
			free_memory(instance, levels[lvl].map, levels[lvl].height);  // Free memory on quit
			break;  // Exit game loop if the player quits
		}

		// Handle player movement and update their position based on keyboard input
		movement(key_press, &levels[lvl].plane, &levels[lvl].dir, &levels[lvl].play,
			 levels[lvl].map);

		// Check if the player has reached the win spot in the current level
		if (check_win(levels[lvl].play, levels[lvl].win, &win_value))
		{
			free_map(levels[lvl].map, levels[lvl].height);  // Free the current map
			lvl++;  // Move to the next level
			if (lvl == argc - 1)  // Check if all levels have been completed
				break;  // Exit game loop if the player has finished all levels
			win_value = 0;  // Reset win flag for the next level
		}

		// Render the maze and the player's position on the screen
		draw(instance, levels[lvl].map, levels[lvl].play, levels[lvl].dir,
		     levels[lvl].plane);
	}

	// Clean up SDL resources and close the window
	close_SDL(instance);

	// If the player completed all levels, print a win message
	if (win_value)
		print_win();

	return (0);
}

