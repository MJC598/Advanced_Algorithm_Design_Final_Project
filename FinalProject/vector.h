
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
	int** data;
	int height;
	int width;
	int heightcapacity;
	int widthcapacity;
}IntMaze;

void init_vector(struct vector* v);
void init_intVector(struct intVector* v);
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
IntMaze convertToInt(Maze maze, IntMaze intMaze);

#endif
