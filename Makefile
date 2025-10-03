#Variables
CC = gcc
CFLAGS = -W -Wall -Wextra -Wundef -Wshadow -Wpointer-arith -Wcast-align -Werror -I./deps -g3
EXEC = maze 
SRC = $(wildcard ./src/*.c)
OBJ = $(SRC:./src/%.c=./obj/%.o)
DEPS = $(wildcard ./deps/*.h)

SH=bash
DOC_DIR = doc/
OBJ_DIR = obj/
DOXYGEN = doxygen
VALGRIND_FLAG = --leak-check=full --show-leak-kinds=all --track-origins=yes 

#Complie, run and clean
all : $(EXEC) test clean

#Compile the program according to EXEC, OBJETS, CC, LDFLAGS
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

#Generate the .o files in a temporary directory "obj" which is created just before the files .o creation
obj/%.o:  src/%.c obj $(DEPS)
	$(CC) $(CFLAGS) -o $@ -c $<

#Create the temporary directory "obj"
obj:
	mkdir obj

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
	rm -fr $(OBJ_DIR)
	rm -fr $(DOC_DIR)
	rm -f stats/result_gen.csv stats/result_path.csv stats/fig_gen.png stats/fig_path.png

#Run valgrind
valgrind: 
	valgrind $(VALGRIND_FLAG) ./$(EXEC)

.PHONY: clean valgrind all doc stat test
