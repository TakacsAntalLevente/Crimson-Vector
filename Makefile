CC = cc
CFLAGS = -std=c99 -Wall -Wextra -O2
SRC = src/main.c src/camera.c src/player.c src/world.c src/renderer.c
OUT = CrimsonVector

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) -lraylib -lm

clean:
	rm -f $(OUT)