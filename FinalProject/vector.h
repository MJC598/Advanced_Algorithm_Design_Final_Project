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

typedef struct position{
    size_t height;
    size_t width;
    size_t weight;
}Pos;

typedef struct stack{
	Pos* data;
	size_t height;
	size_t heightcapacity;
}Stack;

void init_vector(struct vector* v);
void init_intVector(struct intVector* v);
void init_stack(struct stack* v);
char access_element_vector(struct vector* v, size_t height, size_t width);
int access_element_intVector(struct intVector* v, size_t height, size_t width);
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
IntMaze search1(IntMaze intMaze, IntMaze search, int i, int j, int weight);
IntMaze search2(IntMaze intMaze, IntMaze search, int i, int j, int weight);
IntMaze search3(IntMaze intMaze, IntMaze search, IntMaze *path, int i, int j, int weight);
IntMaze search4(IntMaze intMaze, IntMaze search, IntMaze *path, int i, int j, int weight);
IntMaze search5(IntMaze intMaze, IntMaze search, IntMaze path, int i, int j, int weight);
IntMaze search6(IntMaze path);
void push(Stack* stack, int height, int width, int weight);
Pos pop(Stack* stack);
int isEmpty(Stack* s);
int getHeight(Pos s);
int getWidth(Pos s);
int getWeight(Pos s);
void printDirect(Maze maze, IntMaze direct, int r1h, int r1w, int r2h, int r2w);
void printDiverge(Maze maze, int r1h, int r1w, int r2h, int r2w);

#endif
