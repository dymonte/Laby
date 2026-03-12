#Variables
CC = gcc
CFLAGS = -W -Wall -Wextra -Wundef -Wshadow -Wpointer-arith -Wcast-align  -I./deps -g3
EXEC = maze 
SRC = $(filter-out ./src/affichage3D.c ./src/test3D.c, $(wildcard ./src/*.c))
BIN = $(SRC:./src/%.c=./bin/%.o)
DEPS = $(wildcard ./inc/*.h)

SH=bash
DOC_DIR = doc/
BIN_DIR = bin/
DOXYGEN = doxygen
VALGRIND_FLAG = --leak-check=full --show-leak-kinds=all --track-origins=yes 

#Complie, run and clean
all : $(EXEC) test3D affichage3D

all-test : $(EXEC) test clean

#Compile the program according to EXEC, BINETS, CC, LDFLAGS
$(EXEC): $(BIN)
	$(CC) $(CFLAGS) -o $@ $^ -Iinc/

affichage3D: bin/generation.o bin/tab.o bin/tools.o bin/lst_co.o bin/affichage3D.o
	gcc -o $@ $^ -lGL -lGLU -lglut -lm

test3D: bin/generation.o bin/tab.o bin/tools.o bin/lst_co.o bin/test3D.o
	gcc -o $@ $^ -lGL -lGLU -lglut -lm
	

#Generate the .o files in a temporary directory "bin" which is created just before the files .o creation
bin/%.o:  src/%.c bin $(DEPS)
	$(CC) $(CFLAGS) -o $@ -c $< -Iinc/

#Create the temporary directory "bin"
bin:
	mkdir bin

# Generate the documentation
doc: $(DOC_DIR)
	$(DOXYGEN) ./Doxyfile
	cd $(DOC_DIR)/latex && make pdf
	cp -fr $(DOC_DIR)/latex/refman.pdf ./

stat: $(EXEC) stats/result_gen.csv stats/result_path.csv
	$(SH) stats/generate_stats.sh

stats/result_gen.csv: 
	touch $@
	echo "width=height;nb_cells;time" >>$@

stats/result_path.csv: 
	touch $@
	echo "width=height;nb_cells;time" >>$@

test: $(EXEC)
	$(SH) ./test.sh

$(DOC_DIR):
	mkdir $(DOC_DIR)

#Clean everything
clean:
	rm -f $(EXEC)
	rm -fr $(BIN_DIR)
	rm -fr $(DOC_DIR)
	rm -f stats/result_gen.csv stats/result_path.csv stats/fig_gen.png stats/fig_path.png

#Run valgrind
valgrind: 
	valgrind $(VALGRIND_FLAG) ./$(EXEC)

.PHONY: clean valgrind all doc stat test
