#include "../maze.h"

/**
 * rotate - Rotate the player's camera view either left or right
 * @plane: The 2D projection plane representing the player's field of view
 * @dir: The direction vector of the player, indicating where they are facing
 * @rot_dir: The rotation direction, -1 for rotating right, 1 for rotating left
 * 
 * This function updates the player's direction and camera projection plane by
 * rotating both vectors based on the provided rotation direction. The rotation
 * speed determines how fast the camera rotates. The rotation is handled using
 * trigonometric functions to apply a small incremental change to the direction
 * and projection plane.
 **/
void rotate(double_s *plane, double_s *dir, int rot_dir)
{
	double rotate_speed, old_dir_x, old_plane_x;

	rotate_speed = 0.03 * rot_dir;  // Set rotation speed with direction
	old_dir_x = dir->x;
	// Rotate the direction vector using trigonometric functions
	dir->x = dir->x * cos(rotate_speed) - dir->y * sin(rotate_speed);
	dir->y = old_dir_x * sin(rotate_speed) + dir->y * cos(rotate_speed);
	old_plane_x = plane->x;
	// Rotate the projection plane similarly to maintain the field of view
	plane->x = plane->x * cos(rotate_speed) - plane->y * sin(rotate_speed);
	plane->y = old_plane_x * sin(rotate_speed) + plane->y * cos(rotate_speed);
}

/**
 * movement - Handle player movement and camera rotation
 * @key_press: Struct holding the state of the player's input (up, down, left, right)
 * @plane: The 2D projection plane representing the player's field of view
 * @dir: The direction vector of the player
 * @play: The player's current position in the map (x, y coordinates)
 * @map: 2D array representing the game map (walls, open spaces)
 * 
 * This function handles player movement (forward, backward) and rotation (left, right).
 * It checks for player input and updates the player's position and view direction
 * accordingly. Movement is constrained by the game map to prevent walking through walls.
 * If the player attempts to move into a wall ('1'), movement is blocked.
 **/
void movement(keys key_press, double_s *plane, double_s *dir, double_s *play,
	      char **map)
{
	double move_speed = 0.07;  // Speed at which the player moves

	// Rotate the camera right if the right key is pressed
	if (key_press.right)
	{
		rotate(plane, dir, -1);
	}
	// Rotate the camera left if the left key is pressed
	if (key_press.left)
		rotate(plane, dir, 1);

	// Move the player forward if the up key is pressed, checking for walls
	if (key_press.up)
	{
		// Move forward along the x-axis, only if the space is not a wall ('0')
		if (map[(int)(play->x + dir->x * move_speed)][(int)play->y] == '0')
			play->x += dir->x * move_speed;
		// Move forward along the y-axis
		if (map[(int)play->x][(int)(play->y + dir->y * move_speed)] == '0')
			play->y += dir->y * move_speed;
	}

	// Move the player backward if the down key is pressed, checking for walls
	if (key_press.down)
	{
		// Move backward along the x-axis
		if (map[(int)(play->x - dir->x * move_speed)][(int)play->y] == '0')
			play->x -= dir->x * move_speed;
		// Move backward along the y-axis
		if (map[(int)play->x][(int)(play->y - dir->y * move_speed)] == '0')
			play->y -= dir->y * move_speed;
	}
}

