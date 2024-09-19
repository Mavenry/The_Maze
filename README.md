# The_Maze 
Background  
The aim of this project is to build a 3D game using raycasting!

Tasks  

1. Walls  
In this initial phase, you need to:  
- Create a window using SDL2  
- Implement raycasting to draw walls in the window  
- Camera rotation during execution isn't required, but you should implement a way to modify the camera angle in the code for testing purposes after recompiling  
- Ensure the walls' colors are distinct from the ground/ceiling  
- No need for map parsing from a file, but allow map modification directly in the code (e.g., using arrays)

2. Wall Orientation  
You should render walls with different colors based on their orientation:
- Walls facing NORTH and SOUTH should have a different color than those facing EAST and WEST  

3. Camera Rotation  
Enable camera rotation during gameplay:
- For example, rotate the camera when pressing the left/right arrows or by moving the mouse like in FPS games  

4. Camera Movement  
Allow camera movement during gameplay:
- For instance, use the keys **W**, **A**, **S**, **D** to control the camera's movement  

5. Collision Detection  
Handle player collisions (the camera is now referred to as the player):
- The player should not be able to walk through walls  
- Optionally, make the player slide along walls instead of being stopped completely  

6. Map Parsing  
Implement a map parser to load maps from files:
- You can define your own standards for the map format (e.g., wall characters, empty space characters, file extensions)  
- Your program should accept the map file path as a parameter during execution  

7. Drawing the Map  
Render the map in the game window:
- You have full freedom on where and how to display the map  
- Provide an option to enable/disable the map display during gameplay  
- Include the player's line of sight in the map display  

8. Coding Style & Documentation  
Ensure your code follows the Holberton School's coding style and documentation guidelines.  
- Verify your own code by following the instructions in the provided repository.  
- Make sure to keep your repository clean, as all files will be checked, even those not explicitly required.

9. Textures  
Add textures to the walls for a more detailed appearance.

10. Multi-tasking  
Allow the player to move and rotate simultaneously:
- For instance, if **W** and **D** are pressed, the player should move forward and right at the same time.  

11. Ground and Ceiling Textures  
Add textures to the ground and/or ceiling to enhance the game's visual appeal.

12. Weapons  
Incorporate weapon textures for the player.

13. Enemies  
Add enemies to the game for an additional challenge.

14. Rain  
Add a rain effect and provide a key to toggle it on and off.

15. Extra Features  
Get creative by adding advanced options such as shadows, special lighting effects, etc.

<img width="349" alt="flowchart" src="https://github.com/user-attachments/assets/6956f281-b1e8-4f0a-bc85-e4ab3b0d6596">

