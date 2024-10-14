# Variables
CC = gcc
CFLAGS = -Wall -g
OBJ = main.o lst_co.o tab.o generation.o pathfinding.o
EXEC = maze

.PHONY: all run clean valgrind

# Règle par défaut pour compiler l'exécutable
all: $(EXEC) run clean

# Règle pour créer l'exécutable en reliant les fichiers objets
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

# Compilation des fichiers .o à partir des fichiers .c
main.o: main.c lst_co.h tab.h generation.h pathfinding.h
	$(CC) $(CFLAGS) -c main.c

lst_co.o: lst_co.c lst_co.h
	$(CC) $(CFLAGS) -c lst_co.c

tab.o: tab.c tab.h
	$(CC) $(CFLAGS) -c tab.c

generation.o: generation.c generation.h tab.h
	$(CC) $(CFLAGS) -c generation.c

pathfinding.o: pathfinding.c pathfinding.h tab.h lst_co.h
	$(CC) $(CFLAGS) -c pathfinding.c

run: $(EXEC)
	./$(EXEC)
# Nettoyage des fichiers objets et de l'exécutable
clean:
	rm -f *.o $(EXEC)

valgrind: $(EXEC)
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXEC)

