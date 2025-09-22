CC = clang++

CFLAGS = -Wall -I./libraries -I./libraries/glfw/include

EXEC = Simulation
OBJECTS = main.o Particle.o Visualizer.o BruteForce.o glad.o

VERSION = c++23

Simulation: main.o Particle.o Visualizer.o BruteForce.o glad.o
	@$(CC) $(CFLAGS) -std=$(VERSION) -o $(EXEC) $(OBJECTS) -L./build/src -lglfw3 -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
	@rm -f $(OBJECTS)
	@./$(EXEC)

main.o: main.cpp Particle.h BruteForce.h Visualizer.h Constants.h
	@$(CC) $(CFLAGS) -std=$(VERSION) -c main.cpp

Particle.o: Particle.cpp Particle.h
	@$(CC) $(CFLAGS) -std=$(VERSION) -c Particle.cpp

Visualizer.o: Visualizer.cpp Visualizer.h
	@$(CC) $(CFLAGS) -std=$(VERSION) -c Visualizer.cpp

BruteForce.o: BruteForce.cpp BruteForce.h Constants.h
	@$(CC) $(CFLAGS) -std=$(VERSION) -c BruteForce.cpp

glad.o: glad.c
	@gcc $(CFLAGS) -c glad.c


.PHONY: clean
clean: 
	@rm -f $(EXEC) $(OBJECTS)