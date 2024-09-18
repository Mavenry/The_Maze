#include "../maze.h"

/**
 * get_line_count - Counts the number of lines in a file.
 * @file_string: The file path to the maze layout.
 * Return: The total number of lines in the file, or 0 if the file cannot be opened.
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

	/* Count each line in the file */
	while ((read = getline(&line, &line_len, maze_file)) != -1)
	{
		lines++;
	}
	fclose(maze_file);
	free(line);

	return (lines);
}

/**
 * get_char_count - Counts the number of characters in a line.
 * @line: The string representing a single line from the file.
 * Return: The number of characters in the string (excluding null terminator).
 **/
size_t get_char_count(char *line)
{
	size_t char_count = 0;

	/* Iterate through the string until the null terminator */
	while (line[char_count] != '\0')
		char_count++;
	return (char_count);
}

/**
 * plot_grid_points - Maps specific characters in the maze to points.
 * @maze: The 2D array representing the maze.
 * @play: The player's x and y position in the maze.
 * @win: The x and y coordinates of the winning square.
 * @cur_char: Current character being processed in the line.
 * @maze_line: The current line number being processed in the maze.
 * @line: The current line being read from the file.
 * @found_win: Flag indicating if the win square has been found.
 * 
 * Description: Processes each character of the maze, mapping player 'p', 
 * win 'w', and other maze elements to their respective positions in the 
 * 2D array. Adjusts the player's start position and marks the win square.
 **/
void plot_grid_points(char **maze, double_s *play, int_s *win, size_t cur_char,
		      size_t maze_line, char *line, int *found_win)
{
	if (line[cur_char] == 'p')  /* Player's starting position */
	{
		play->y = cur_char;
		play->x = maze_line;
		maze[maze_line][cur_char] = '0';  /* Mark player's start as an empty space */
	}
	else if (line[cur_char] == 'w')  /* Win position */
	{
		*found_win = 1;
		win->y = cur_char;
		win->x = maze_line;
		maze[maze_line][cur_char] = '0';  /* Mark win square as an empty space */
	}
	else
	{
		/* If the win square is not found yet, mark the first '0' as the win square */
		if (line[cur_char] == '0' && *found_win == 0)
		{
			win->y = cur_char;
			win->x = maze_line;
		}
		maze[maze_line][cur_char] = line[cur_char];  /* Set the current character in the maze */
	}
}

/**
 * create_map - Creates a 2D array to represent the maze from the file.
 * @file_string: The path to the maze layout file.
 * @play: Structure to hold player's x and y position.
 * @win: Structure to hold the win square's x and y coordinates.
 * @map_h: Pointer to store the height (number of lines) of the maze.
 * Return: A 2D array representing the maze, or NULL if it fails.
 *
 * Description: Reads the maze layout from a file, dynamically allocates
 * memory for the 2D maze array, and populates the player's start position
 * and win position based on characters in the file.
 **/
char **create_map(char *file_string, double_s *play, int_s *win, size_t *map_h)
{
	FILE *maze_file;
	char **maze, *line = NULL;
	ssize_t read = 0;
	size_t line_count, maze_line, char_count, cur_char, bufsize;
	int found_win = 0;

	found_win = 0;
	maze_line = 0;
	line_count = get_line_count(file_string);  /* Get number of lines in the maze file */
	*map_h = line_count;  /* Store the maze height */
	if (line_count == 0)
		return (NULL);
	maze = malloc(sizeof(int *) * line_count);  /* Allocate memory for 2D maze array */
	if (maze == NULL)
		return (NULL);
	maze_file = fopen(file_string, "r");  /* Open the maze file */
	if (maze_file == NULL)
		return (NULL);
	read = getline(&line, &bufsize, maze_file);
	while (read != -1)  /* Read each line of the maze file */
	{
		char_count = get_char_count(line);  /* Get the character count for each line */
		maze[maze_line] = malloc(sizeof(char) * char_count + 1);  /* Allocate memory for each line */
		if (maze == NULL)
			return (NULL);
		for (cur_char = 0; cur_char < char_count; cur_char++)
		{
			/* Map each character in the line to a specific point in the maze */
			plot_grid_points(maze, play, win, cur_char, maze_line, line, &found_win);
		}
		maze_line++;
		read = getline(&line, &bufsize, maze_file);  /* Read the next line */
	}
	fclose(maze_file);  /* Close the maze file */
	free(line);  /* Free the buffer for reading lines */
	return (maze);
}

