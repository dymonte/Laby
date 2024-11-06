#Les variables
CC = gcc
CFLAGS = -W -Wall -Wextra -Wundef -Wshadow -Wpointer-arith -Wcast-align -Werror -I./deps
EXEC = maze 
SRC = $(wildcard ./src/*.c)
OBJ = $(SRC:./src/%.c=./obj/%.o)
DEPS = $(wildcard ./deps/*.h)


DOC_DIR = doc/
OBJ_DIR = obj/
DOXYGEN = doxygen
VALGRIND_FLAG = --leak-check=full --show-leak-kinds=all --track-origins=yes 

#Complie, run and clean
all : $(EXEC) run clean

#Run the program
run : $(EXEC)
	./$(EXEC)


#Compile the program according to EXEC, OBJETS, CC, LDFLAGS
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

#Generate the .o files in a temporary directory "obj" which is created just before the files .o creation
obj/%.o:  src/%.c obj $(DEPS)
	$(CC) $(CFLAGS) -o $@ -c $<

#Create the temporary directory "obj"
obj:
	mkdir obj

doc: $(DOC_DIR)
	$(DOXYGEN) ./Doxyfile
	cd $(DOC_DIR)/latex && make pdf
	cp -fr $(DOC_DIR)/latex/refman.pdf ./


$(DOC_DIR):
	mkdir $(DOC_DIR)

#Clean everything
clean: doc/ doc/latex
	rm -f $(EXEC)
	rm -fr $(OBJ_DIR)
	rm -fr $(DOC_DIR)

#Run valgrind
valgrind: 
	valgrind $(VALGRIND_FLAG) ./$(EXEC)

.PHONY: clean valgrind run all doc
