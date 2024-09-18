#include "../maze.h"

/**
 * check_ray_dir - Determines the direction and distance for the ray to move.
 * @step: The x and y step direction (-1 for left/up, 1 for right/down).
 * @dist_side: The distance to the next side (x/y) of the map grid.
 * @ray_pos: The starting position of the ray in the maze.
 * @coord: The current grid coordinates (x/y) of the player.
 * @dist_del: The change in distance between two sides of a grid square.
 * @ray_dir: The x/y direction of the ray vector (positive or negative).
 * 
 * Description: Based on the ray's direction (positive or negative), this 
 * function calculates whether the ray moves left or right, up or down, and 
 * computes the distance to the next grid boundary. This is essential for 
 * determining the next step in the ray-casting algorithm used to find walls 
 * in the maze.
 **/
void check_ray_dir(int_s *step, double_s *dist_side, double_s ray_pos,
		   int_s coord, double_s dist_del, double_s ray_dir)
{
	/* Determine if ray moves left or right on the x-axis */
	if (ray_dir.x < 0)
	{
		step->x = -1;  /* Move left */
		dist_side->x = (ray_pos.x - coord.x) * dist_del.x;  /* Distance to next x boundary */
	}
	else
	{
		step->x = 1;  /* Move right */
		dist_side->x = (coord.x + 1.0 - ray_pos.x) * dist_del.x;  /* Distance to next x boundary */
	}

	/* Determine if ray moves up or down on the y-axis */
	if (ray_dir.y < 0)
	{
		step->y = -1;  /* Move up */
		dist_side->y = (ray_pos.y - coord.y) * dist_del.y;  /* Distance to next y boundary */
	}
	else
	{
		step->y = 1;  /* Move down */
		dist_side->y = (coord.y + 1 - ray_pos.y) * dist_del.y;  /* Distance to next y boundary */
	}
}

/**
 * get_wall_dist - Calculates the distance from the player to the next wall.
 * @map: The 2D array representing the maze map (with '0' as empty space and '1' as walls).
 * @dist_side: Current x/y distance to the next side of a grid square.
 * @coord: Player's current x/y coordinates in the map.
 * @step: The direction of movement (x/y axis: -1 for negative, 1 for positive).
 * @dist_del: The distance delta (change) between grid lines on x/y axes.
 * @hit_side: Output value indicating whether the ray hit a wall on the N/S or E/W side.
 * @ray_dir: The x/y direction of the ray being cast from the player.
 * @ray_pos: The initial position of the ray being cast.
 * Return: The distance from the player to the wall along the ray's path.
 *
 * Description: Using a ray-casting algorithm, this function tracks the movement 
 * of the ray in discrete steps across the grid. It checks whether the ray hits a wall 
 * at each step and calculates the exact distance from the player's position to the 
 * first wall encountered.
 **/
double get_wall_dist(char **map, double_s *dist_side, int_s *coord,
		      int_s *step, double_s *dist_del, int *hit_side,
		      double_s *ray_dir, double_s *ray_pos)
{
	double wall_dist;
	int hit_wall = 0;  /* Flag to check if the wall has been hit */

	while (hit_wall == 0)
	{
		/* Move the ray to the next grid square based on distance */
		if (dist_side->x < dist_side->y)
		{
			dist_side->x += dist_del->x;  /* Increment distance to next x grid boundary */
			coord->x += step->x;  /* Move in the x direction */
			*hit_side = 0;  /* Hit a N/S wall */
		}
		else
		{
			dist_side->y += dist_del->y;  /* Increment distance to next y grid boundary */
			coord->y += step->y;  /* Move in the y direction */
			*hit_side = 1;  /* Hit an E/W wall */
		}

		/* Check if the ray has hit a wall (non-zero character in the map) */
		if (map[coord->x][coord->y] > '0')
			hit_wall = 1;
	}

	/* Calculate the actual distance from the player to the wall */
	if (*hit_side == 0)
		wall_dist = (coord->x - ray_pos->x + (1 - step->x) / 2) / ray_dir->x;  /* Wall hit on N/S */
	else
		wall_dist = (coord->y - ray_pos->y + (1 - step->y) / 2) / ray_dir->y;  /* Wall hit on E/W */
	
	return (wall_dist);
}

