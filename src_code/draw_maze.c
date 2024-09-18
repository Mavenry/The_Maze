#include "../maze.h"

/**
 * draw - Render the game visuals (background, walls) on the screen.
 * @instance: The SDL instance containing the game window and renderer.
 * @map: 2D array representing the maze layout with walls and empty spaces.
 * @play: The player's current x/y position in the maze.
 * @dir: The direction vector representing where the player is facing.
 * @plane: The projection plane for the player's field of view.
 * 
 * Description: This function handles drawing both the background (sky and 
 * floor) and the walls of the maze, updating the screen with each frame.
 **/
void draw(SDL_Instance instance, char **map, double_s play, double_s dir,
	  double_s plane)
{
	draw_background(instance);  // Draw the sky and floor
	draw_walls(map, play, instance, dir, plane);  // Draw the maze walls
	SDL_RenderPresent(instance.renderer);  // Display the final rendered image
}

/**
 * draw_background - Render the sky and the floor.
 * @instance: The SDL instance containing the renderer.
 * 
 * Description: This function draws a gradient for the sky and floor using 
 * specific colors for dawn sky and light brown ground, creating the background 
 * of the game.
 **/
void draw_background(SDL_Instance instance)
{
	size_t x;

	for (x = 0; x <= SCREEN_WIDTH; x++)
	{
		/* Draw the dawn sky (soft orange) */
		SDL_SetRenderDrawColor(instance.renderer, 255, 178, 102, 0xFF);  // Dawn sky color
		SDL_RenderDrawLine(instance.renderer, x, 0, x, SCREEN_HEIGHT / 2);

		/* Draw the lighter brown ground */
		SDL_SetRenderDrawColor(instance.renderer, 89, 60, 30, 0xFF);   // Ground color
		SDL_RenderDrawLine(instance.renderer, x, SCREEN_HEIGHT / 2, x, SCREEN_HEIGHT);
	}
}

/**
 * draw_walls - Render the walls of the maze using raycasting.
 * @map: A 2D array representing the maze layout with walls.
 * @play: The player's current x/y position in the maze.
 * @instance: The SDL instance containing the renderer.
 * @dir: The direction vector representing where the player is facing.
 * @plane: The projection plane for rendering the player's field of view.
 * 
 * Description: This function uses raycasting to compute and draw the maze walls 
 * based on the player's position and direction. It calculates the distance from 
 * the player to the walls and renders the walls accordingly.
 **/
void draw_walls(char **map, double_s play, SDL_Instance instance, double_s dir,
		double_s plane)
{
	double_s ray_pos, ray_dir, dist_side, dist_del;
	double wall_dist, cam_x;
	int_s coord, step;
	int wall_height, wall_start, wall_end, screen_x, hit_side;

	for (screen_x = 0; screen_x < SCREEN_WIDTH; screen_x++)
	{
		hit_side = 0;  // Reset hit side for each ray
		cam_x = 2 * screen_x / (double)SCREEN_WIDTH - 1;  // Calculate camera x-coordinate for ray
		ray_pos.x = play.x;
		ray_pos.y = play.y;
		ray_dir.x = dir.x + plane.x * cam_x;  // Calculate ray direction
		ray_dir.y = dir.y + plane.y * cam_x;
		coord.x = (int)ray_pos.x;
		coord.y = (int)ray_pos.y;

		// Calculate distance between grid lines (x and y)
		dist_del.x = sqrt(1 + (ray_dir.y * ray_dir.y) / (ray_dir.x * ray_dir.x));
		dist_del.y = sqrt(1 + (ray_dir.x * ray_dir.x) / (ray_dir.y * ray_dir.y));

		// Determine which direction to step (left/right or up/down)
		check_ray_dir(&step, &dist_side, ray_pos, coord, dist_del, ray_dir);

		// Calculate distance to the wall
		wall_dist = get_wall_dist(map, &dist_side, &coord, &step,
					  &dist_del, &hit_side, &ray_dir, &ray_pos);

		// Calculate height and position of the wall slice
		wall_height = (int)(SCREEN_HEIGHT / wall_dist);
		wall_start = -wall_height / 2 + SCREEN_HEIGHT / 2;
		if (wall_start < 0)
			wall_start = 0;
		wall_end = wall_height / 2 + SCREEN_HEIGHT / 2;
		if (wall_end >= SCREEN_HEIGHT)
			wall_end = SCREEN_HEIGHT - 1;

		// Choose the wall color based on the map and hit side
		choose_color(instance, map, coord, hit_side);

		// Render the wall slice
		SDL_RenderDrawLine(instance.renderer, screen_x, wall_start,
				   screen_x, wall_end);
	}
}

/**
 * choose_color - Set the color for drawing the wall slice.
 * @instance: The SDL instance containing the renderer.
 * @map: The 2D array representing the maze layout with walls.
 * @coord: The current coordinates in the map where the wall was hit.
 * @hit_side: Indicator of whether the wall was hit on the N/S or E/W side.
 * 
 * Description: Depending on the wall type and which side (N/S or E/W) was hit, 
 * this function sets the color used to render the wall. Each wall type (1-4) 
 * has a different base color and a slightly darker shade for shadows.
 **/
void choose_color(SDL_Instance instance, char **map, int_s coord, int hit_side)
{
	switch (map[coord.x][coord.y])
	{
		case '1':
			/* Set color for deep blue walls */
			if (hit_side == 0)
				SDL_SetRenderDrawColor(instance.renderer, 0x00, 0x34, 0x66, 0xFF);  // Dark blue
			else
				SDL_SetRenderDrawColor(instance.renderer, 0x00, 0x28, 0x4D, 0xFF);  // Navy shadow
			break;
		case '2':
			/* Set color for dark green walls */
			if (hit_side == 0)
				SDL_SetRenderDrawColor(instance.renderer, 0x00, 0x5F, 0x37, 0xFF);  // Dark forest green
			else
				SDL_SetRenderDrawColor(instance.renderer, 0x00, 0x47, 0x2B, 0xFF);  // Shadow green
			break;
		case '3':
			/* Set color for charcoal gray walls */
			if (hit_side == 0)
				SDL_SetRenderDrawColor(instance.renderer, 0x36, 0x36, 0x36, 0xFF);  // Charcoal
			else
				SDL_SetRenderDrawColor(instance.renderer, 0x2C, 0x2C, 0x2C, 0xFF);  // Darker gray
			break;
		case '4':
			/* Set color for burnt orange walls */
			if (hit_side == 0)
				SDL_SetRenderDrawColor(instance.renderer, 0xD9, 0x6B, 0x00, 0xFF);  // Burnt orange
			else
				SDL_SetRenderDrawColor(instance.renderer, 0xA3, 0x52, 0x00, 0xFF);  // Dark burnt orange
			break;
		default:
			/* Set color for steel gray walls */
			if (hit_side == 0)
				SDL_SetRenderDrawColor(instance.renderer, 0x4B, 0x4B, 0x4B, 0xFF);  // Steel gray
			else
				SDL_SetRenderDrawColor(instance.renderer, 0x3A, 0x3A, 0x3A, 0xFF);  // Shadow gray
			break;
	}
}

