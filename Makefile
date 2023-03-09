OBJS = game.cpp player.cpp bullet.cpp enemy.cpp drop.cpp stage1.cpp

CC = g++

# -w suppresses all warnings
COMPILER_FLAGS = -w

LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

OBJ_NAME = game

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
