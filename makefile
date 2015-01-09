all: maze

maze:
	gcc -g maze.c -o maze

clean:
	rm maze
