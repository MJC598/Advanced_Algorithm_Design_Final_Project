#ifndef H_VECTOR_H
#define H_VECTOR_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INIT_VECTOR_SIZE 128

enum vector_errors
{
	OUT_OF_BOUNDS = 69,
};

typedef struct vector
{
	char** data;
	int height;
  	int width;
	int heightcapacity;
  int widthcapacity;
}Maze;

typedef struct intVector{
	size_t** data;
	int height;
	int width;
	int heightcapacity;
	int widthcapacity;
}IntMaze;

typedef struct stack{
	size_t* data;
	size_t height;
	size_t heightcapacity;
}Stack;

void init_vector(struct vector* v);
void init_intVector(struct intVector* v);
void init_stack(struct stack* v);
char access_element_vector(struct vector* v, size_t height, size_t width);
char access_element_intVector(struct intVector* v, size_t height, size_t width);
void insert_element_vector(struct vector* v, char element_to_insert, int height, int width);
void insert_element_intVector(struct intVector* v, int element_to_insert, int height, int width);
void free_vector(struct vector* v);
void free_intVector(struct intVector* v);
int vector_height(struct vector* v);
int vector_intHeight(struct intVector* v);
int vector_width(struct vector* v);
int vector_intWidth(struct intVector* v);
Maze parse_getline(char* input, Maze maze);
void printMaze(Maze maze);
void printIntMaze(IntMaze maze);
IntMaze convertToInt(Maze maze, IntMaze intMaze, int *r1H, int *r1W, int *r2H, int *r2W, int *e1H, int *e1W, int *e2H, int *e2W);
IntMaze search1(IntMaze intMaze, IntMaze search, int i, int j, size_t weight);
IntMaze search2(IntMaze intMaze, IntMaze search, int i, int j, size_t weight);
IntMaze search3(IntMaze intMaze, IntMaze search, int i, int j, size_t weight);
IntMaze search4(IntMaze intMaze, IntMaze search, int i, int j, size_t weight);
Stack* push(size_t data, Stack* stack);
size_t pop(Stack* stack);

#endif
