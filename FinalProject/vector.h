#ifndef H_VECTOR_H
#define H_VECTOR_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INIT_VECTOR_SIZE 128

enum vector_errors
{
	OUT_OF_BOUNDS = 0,
};

struct vector
{
	char** data;
	int height;
        int width;
	int heightcapacity;
        int widthcapacity;
};

void init_vector(struct vector* v);
char access_element_vector(struct vector* v, size_t index);
void insert_element_vector(struct vector* v, int element_to_insert, int weight);
void free_vector(struct vector* v);
int vector_height(struct vector* v);
int vector_width(struct vector* v);

#endif
