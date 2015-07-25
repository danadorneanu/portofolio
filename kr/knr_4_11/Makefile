OBJ_PATH = ~/obj/
BIN_PATH = ~/bin/
default:
	gcc -c main.c -o $(OBJ_PATH)main.o -Wall 
	gcc -c getop.c -o $(OBJ_PATH)getop.o -Wall 
	gcc -c stack.c -o $(OBJ_PATH)stack.o -Wall
	gcc -c getch.c -o $(OBJ_PATH)getch.o -Wall
	gcc -o $(BIN_PATH)knr_4_11 $(OBJ_PATH)main.o $(OBJ_PATH)getop.o $(OBJ_PATH)stack.o $(OBJ_PATH)getch.o -lm

debug:
	gcc -c main.c -g -lm
	gcc -c getop.c -g
	gcc -c stack.c -g
	gcc -c getch.c -g 
	gcc -o knr_4_11 main.o getop.o stack.o getch.o -g
run:
	$(BIN_PATH)knr_4_11
