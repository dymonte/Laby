#Les variables
CC = gcc
CFLAGS = -W -Wall -Wextra -Wundef -Wshadow -Wpointer-arith -Wcast-align -Werror
EXEC = maze 
SRC = $(wildcard ./*.c)
OBJ = $(SRC:./%.c=./%.o)
DEPS = $(wildcard ./*.h)
VALGRIND_FLAG = --leak-check=full --show-leak-kinds=all --track-origins=yes 


#Compile le programme en fonction de EXEC, OBJETS, CC, LDFLAGS
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

#Génère les fichiers .o dans un répertoire "temporaire" obj qui est créer juste avant la création des fichiers .o
obj/%.o: src/%.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ -c $<


#Supprimer les dossiers obj, doc et supprimer main.exe
clean:
	rm -f $(EXEC)

format:
	@for file in $(SRC) $(DEPS); do \
		clang-format -i $$file; \
	done

valgrind: 
	valgrind $(VALGRIND_FLAG) ./$(EXEC)

.PHONY: clean format valgrind
