#include "../maze.h"

/**
 * print_win - Display a congratulatory message when the player wins the game
 * 
 * This function prints a formatted "win" message on the screen when the player
 * successfully completes the maze. The message is designed using ASCII art.
 **/
void print_win(void)
{
	printf("\n\n\n\n\n\n\n\n\n\n");
	printf("     \\ //   __    ||   ||\n");
	printf("      \\/  //  \\  ||   ||\n");
	printf("      //  ||    || ||   ||\n");
	printf("     //    \\__//   \\_//\n\n");
	printf("\\      //\\      //   ||     ||\\   ||\n");
	printf(" \\    //  \\    //    ||     || \\  ||\n");
	printf("  \\  //    \\  //     ||     ||  \\ ||\n");
	printf("   \\//      \\//      ||     ||   \\||\n");
	printf("\n\n\n\n\n\n\n\n\n\n");
}

/**
 * check_win - Determine if the player has reached the win spot in the maze
 * @play: Structure holding the player's current x/y coordinates
 * @win: Structure holding the x/y coordinates of the win space
 * @win_value: Pointer to an integer that gets updated to 1 if the player reaches the win spot
 * 
 * This function checks if the player's current position matches the win space coordinates.
 * If the player is at the win spot, it updates the win_value to 1 and returns 1 to indicate
 * that the player has won. Otherwise, it returns 0.
 * 
 * Return: 1 if the player has reached the win space, otherwise 0
 **/
int check_win(double_s play, int_s win, int *win_value)
{
	if ((int) play.x == win.x && (int) play.y == win.y)
	{
		*win_value = 1;
		return (1);
	}
	return (0);
}

