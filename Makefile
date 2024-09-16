# compiler to use
CC=gcc

# Flags to create object files with
CFLAGS=-g -Wall -Werror -Wextra -pedantic
# Flags to link the SDL2 library
SDL_FLAGS=-I/usr/local/include/SDL2 -L/usr/lib/x86_64-linux-gnu -lSDL2 -lm

# All C program files
SRC=./src_code/create_maze.c ./src_code/maze_world.c ./src_code/distance_check.c ./src_code/draw_maze.c ./src_code/input_handlers.c ./src_code/free.c ./src_code/init.c ./src_code/maze_runner.c ./src_code/player_movement.c ./src_code/main_win.c
# The names of all object files
OBJ=$(SRC:.c=.o)
# Executable name
NAME=maze

# Removal command
RM=rm

# Compile all files into the executable
# CFLAGS will only be used when creating object files
# SDL_FLAGS includes necessary libraries to link
all: $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(SDL_FLAGS)

# Remove all Emacs temp files (~)
clean:
	$(RM) -f *~

# Remove all object files (.o)
oclean:
	$(RM) -f $(OBJ)

# Remove temp files, object files, and executable
fclean: clean oclean
	$(RM) -f $(NAME)

# Run full clean and recompile all files
re: fclean all
