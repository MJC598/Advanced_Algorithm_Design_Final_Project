#include "DFSvector.h"

void init_vector(struct vector* v){
	v->data = malloc(sizeof(char *) * INIT_VECTOR_SIZE);
  int i;
  for(i = 0; i < INIT_VECTOR_SIZE; i++)
  	v->data[i] = malloc(sizeof(char) * INIT_VECTOR_SIZE);
	v->height = 0;
  v->width = 0;
	v->heightcapacity = INIT_VECTOR_SIZE;
  v->widthcapacity = INIT_VECTOR_SIZE;
}

void init_intVector(struct intVector* v){
	v->data = malloc(sizeof(int *) * INIT_VECTOR_SIZE);
  int i;
  for(i = 0; i < INIT_VECTOR_SIZE; i++)
  	v->data[i] = malloc(sizeof(int) * INIT_VECTOR_SIZE);
	v->height = 0;
  v->width = 0;
	v->heightcapacity = INIT_VECTOR_SIZE;
  v->widthcapacity = INIT_VECTOR_SIZE;
}

void init_stack(struct Stack* v){
  	int i;
  	for(i = 0; i < INIT_VECTOR_SIZE; i++){
  		v->data = malloc(sizeof(int) * INIT_VECTOR_SIZE);
	}
	v->height = 0;
	v->heightcapacity = INIT_VECTOR_SIZE;
}

char access_element_vector(struct vector* v, size_t height, size_t width)
{
	if(height > v->height)
		exit(OUT_OF_BOUNDS);
  if(width > v->width)
    exit(OUT_OF_BOUNDS);
	return v->data[width][height];
}

char access_element_intVector(struct intVector* v, size_t height, size_t width){
	if(height > v->height)
		exit(OUT_OF_BOUNDS);
  if(width > v->width)
    exit(OUT_OF_BOUNDS);
	return v->data[width][height];
}

void insert_element_vector(struct vector* v, char element_to_insert, int height, int width)
{
	if(v->heightcapacity == v->height){
    	int i;
    	for(i = 0; i < v->widthcapacity; i++){
			v->data[i] = realloc(v->data[i], sizeof(char) * v->heightcapacity * 2);
			v->heightcapacity *= 2;
  		}
	}

  	if(v->widthcapacity == v->width){
		v->data = realloc(v->data, sizeof(char *) * v->widthcapacity * 2);
    	int i;
    	for(i = v->widthcapacity; i < v->widthcapacity * 2; i++)
    		v->data[i] = malloc(sizeof(char) * v->heightcapacity);
    	v->widthcapacity *= 2;
	}
	v->data[width][height] = element_to_insert;
	if(height > v-> height){
    	v->height = height;
	}
  	if(width > v-> width){
  		v->width = width;
	}
}

void insert_element_intVector(struct intVector* v, int element_to_insert, int height, int width)
{
	if(v->heightcapacity == v->height){
    int i;
    for(i = 0; i < v->widthcapacity; i++){
			v->data[i] = realloc(v->data[i], sizeof(int) * v->heightcapacity * 2);
			v->heightcapacity *= 2;
  	}
	}

  if(v->widthcapacity == v->width){
	v->data = realloc(v->data, sizeof(int *) * v->widthcapacity * 2);
    int i;
    for(i = v->widthcapacity; i < v->widthcapacity * 2; i++)
    	v->data[i] = malloc(sizeof(int) * v->heightcapacity);
    v->widthcapacity *= 2;
	}
	v->data[width][height] = element_to_insert;
	if(height > v-> height){
    	v->height = height;
	}
  	if(width > v-> width){
  		v->width = width;
	}
}

void free_vector(struct vector* v){
  int i;
  for(i = 0; i < v->height; i++)
    free(v->data[i]);
  free(v->data);
	v->height = 0;
  v->width = 0;
}

void free_intVector(struct intVector* v){
  int i;
  for(i = 0; i < v->height; i++)
    free(v->data[i]);
  free(v->data);
	v->height = 0;
  v->width = 0;
}

int vector_height(struct vector* v){
  return v -> height;
}

int vector_intHeight(struct intVector* v){
  return v -> height;
}

int vector_width(struct vector* v){
  return v -> width;
}

int vector_intWidth(struct intVector* v){
  return v -> width;
}

Stack* push(size_t data, Stack* stack){
	if(stack->heightcapacity == stack->height){
    	int i;
    	for(i = 0; i < stack->heightcapacity; i++){
			stack->data = realloc(stack->data, sizeof(int) * v->heightcapacity * 2);
			stack->heightcapacity *= 2;
  		}
	}
	stack->data[height] = element_to_insert;
	height++;
	return stack;
}

size_t pop(Stack* stack){
	if(height > v->height){
		exit(OUT_OF_BOUNDS);
	}
	return v->data[height];
}
