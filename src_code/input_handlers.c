#include "../maze.h"

/**
 * check_key_release_events - Handle key release events.
 * @event: The SDL_Event structure containing information about which key was released.
 * @key_press: Pointer to a struct that tracks the state of significant keys (up, down, left, right).
 * 
 * Description: This function checks which directional key (up, down, left, or right) was released
 * and updates the corresponding value in the key_press struct to indicate the key is no longer pressed.
 **/
void check_key_release_events(SDL_Event event, keys *key_press)
{
	switch (event.key.keysym.sym)
	{
	case SDLK_UP:
		key_press->up = 0;  // Mark the 'up' key as released
		break;
	case SDLK_DOWN:
		key_press->down = 0;  // Mark the 'down' key as released
		break;
	case SDLK_RIGHT:
		key_press->right = 0;  // Mark the 'right' key as released
		break;
	case SDLK_LEFT:
		key_press->left = 0;  // Mark the 'left' key as released
		break;
	default:
		break;
	}
}

/**
 * check_key_press_events - Handle key press events.
 * @event: The SDL_Event structure containing information about which key was pressed.
 * @key_press: Pointer to a struct that tracks the state of significant keys (up, down, left, right).
 * 
 * Return: 1 if the ESC key was pressed (for exit), 0 otherwise.
 * 
 * Description: This function detects which directional key (up, down, left, or right) was pressed
 * and updates the corresponding value in the key_press struct. It also checks for the ESC key press
 * to determine if the user wants to exit the program.
 **/
int check_key_press_events(SDL_Event event, keys *key_press)
{
	if (event.key.keysym.scancode == 0x29)  // Escape key code
		return (1);  // Return 1 to signal program exit
	
	switch (event.key.keysym.sym)
	{
	case SDLK_UP:
		key_press->up = 1;  // Mark the 'up' key as pressed
		break;
	case SDLK_DOWN:
		key_press->down = 1;  // Mark the 'down' key as pressed
		break;
	case SDLK_RIGHT:
		key_press->right = 1;  // Mark the 'right' key as pressed
		break;
	case SDLK_LEFT:
		key_press->left = 1;  // Mark the 'left' key as pressed
		break;
	default:
		break;
	}
	return (0);  // Return 0 to continue program
}

/**
 * keyboard_events - Process all keyboard input events.
 * @key_press: Pointer to a struct that tracks the state of up/down/left/right key presses.
 * 
 * Return: 0 for standard events, 1 if the quit event or ESC is detected.
 * 
 * Description: This function polls SDL for any keyboard events (key presses and releases),
 * updating the state of the significant directional keys in key_press. If the quit event
 * (closing the window or pressing ESC) is detected, it returns 1 to signal program termination.
 **/
int keyboard_events(keys *key_press)
{
	SDL_Event event;

	/* Poll for any SDL events (keyboard or quit) */
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			return (1);  // Signal exit if the quit event is triggered
		case SDL_KEYDOWN:
			if (check_key_press_events(event, key_press))
				return (1);  // Signal exit if ESC is pressed
			break;
		case SDL_KEYUP:
			check_key_release_events(event, key_press);  // Handle key release
			break;
		default:
			break;
		}
	}
	return (0);  // Continue program execution
}

