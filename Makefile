CC = gcc
FLAGS = -g -Wall -std=c11
INC = ./include
OBJ = ./obj
SRC = ./src
OBJECTS = \
	$(OBJ)/json-data.o\
	$(OBJ)/json-list.o\
	$(OBJ)/json-object.o

APPLICATIONS = main

all: $(OBJECTS) $(APPLICATIONS)	

%: $(SRC)/%.c $(OBJECTS)
	$(CC) $(FLAGS) -I $(INC) $(OBJ)/*.o $< -o $@

run: 
	./main

dev: $(OBJECTS) $(APPLICATIONS)
	valgrind --leak-check=full ./main

clean:
	rm -rf $(OBJ)/*.o ./main

$(OBJ)/%.o: $(SRC)/%.c $(INC)/%.h
	$(CC) -c $< -I $(INC) -o $@
