#include "../maze.h"

/**
 * get_line_count - Calculate the total number of lines in a file
 * @file_string: The path to the file to be read
 * 
 * This function opens a file and counts the number of lines it contains.
 * It returns the number of lines, or 0 if the file cannot be opened.
 * 
 * Return: The number of lines found in the file, or 0 on failure
 **/
size_t get_line_count(char *file_string)
{
	FILE *maze_file;
	char *line = NULL;
	size_t lines = 0;
	size_t line_len = 0;
	ssize_t read;

	maze_file = fopen(file_string, "r");
	if (maze_file == NULL)
	{
		fprintf(stderr, "File does not exist\n");
		return (0);
	}

	// Read each line until the end of the file, counting the lines
	while ((read = getline(&line, &line_len, maze_file)) != -1)
	{
		lines++;
	}
	fclose(maze_file);
	free(line);

	return (lines);
}

/**
 * get_char_count - Count the number of characters in a string
 * @line: The string whose characters need to be counted
 * 
 * This function iterates through the provided string and counts
 * the number of characters until the null terminator is encountered.
 * 
 * Return: The total number of characters in the string
 **/
size_t get_char_count(char *line)
{
	size_t char_count = 0;

	// Loop through the string until the null terminator
	while (line[char_count] != '\0')
		char_count++;
	return (char_count);
}

/**
 * plot_grid_points - Update the maze grid with specific points (player, win, or walls)
 * @maze: The 2D array representing the maze grid
 * @play: Pointer to the player's current x/y position
 * @win: Pointer to the coordinates of the win square
 * @cur_char: The current character being processed in the file line
 * @maze_line: The current line index in the maze grid
 * @line: The current line being read from the file
 * @found_win: Pointer to a flag that indicates whether the win square has been found
 * 
 * This function processes each character from a line of the maze file. Depending on the
 * character ('p' for player, 'w' for win, or '0' for empty space), it updates the maze
 * grid and sets the player's and win coordinates.
 **/
void plot_grid_points(char **maze, double_s *play, int_s *win, size_t cur_char,
		      size_t maze_line, char *line, int *found_win)
{
	if (line[cur_char] == 'p')  // Player's starting position
	{
		play->y = cur_char;
		play->x = maze_line;
		maze[maze_line][cur_char] = '0';  // Mark player's position as an empty space
	}
	else if (line[cur_char] == 'w')  // Win position
	{
		*found_win = 1;
		win->y = cur_char;
		win->x = maze_line;
		maze[maze_line][cur_char] = '0';  // Mark win's position as an empty space
	}
	else
	{
		// Default case: mark the character directly in the maze grid
		if (line[cur_char] == '0' && *found_win == 0)
		{
			win->y = cur_char;  // Assume this is the win position until 'w' is found
			win->x = maze_line;
		}
		maze[maze_line][cur_char] = line[cur_char];  // Store the current character in the grid
	}
}

/**
 * create_map - Build the 2D map of the maze based on a file
 * @file_string: The path to the maze file containing its layout
 * @play: Pointer to the player's initial position (x/y)
 * @win: Pointer to the win square's coordinates (x/y)
 * @map_h: Pointer to the height of the maze (number of lines in the file)
 * 
 * This function reads the maze file and creates a dynamic 2D array representing
 * the maze layout. It also sets the player's starting position and the win
 * square's location. Memory for the maze is allocated dynamically.
 * 
 * Return: Pointer to the 2D array representing the maze, or NULL if an error occurs
 **/
char **create_map(char *file_string, double_s *play, int_s *win, size_t *map_h)
{
	FILE *maze_file;
	char **maze, *line = NULL;
	ssize_t read = 0;
	size_t line_count, maze_line, char_count, cur_char, bufsize;
	int found_win = 0;

	// Initialize variables and get the number of lines in the maze file
	line_count = get_line_count(file_string);
	*map_h = line_count;  // Set the height of the maze to the number of lines
	if (line_count == 0)
		return (NULL);  // Exit if the file is empty or can't be read

	// Allocate memory for the 2D maze grid
	maze = malloc(sizeof(int *) * line_count);
	if (maze == NULL)
		return (NULL);  // Exit if memory allocation fails

	// Open the maze file for reading
	maze_file = fopen(file_string, "r");
	if (maze_file == NULL)
		return (NULL);  // Exit if the file can't be opened

	// Read each line from the maze file and populate the maze grid
	read = getline(&line, &bufsize, maze_file);
	while (read != -1)
	{
		char_count = get_char_count(line);  // Count the number of characters in the line

		// Allocate memory for the current line in the maze
		maze[maze_line] = malloc(sizeof(char) * char_count + 1);
		if (maze == NULL)
			return (NULL);  // Exit if memory allocation fails

		// Plot each point (player, win, or maze elements) onto the grid
		for (cur_char = 0; cur_char < char_count; cur_char++)
		{
			plot_grid_points(maze, play, win, cur_char, maze_line, line, &found_win);
		}

		maze_line++;  // Move to the next line in the maze grid
		read = getline(&line, &bufsize, maze_file);  // Read the next line from the file
	}

	// Clean up and close the file
	fclose(maze_file);
	free(line);
	return (maze);  // Return the completed maze grid
}

