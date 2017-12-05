#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int main(int argc, char* argv[]) {
  // if(argc != 3){
  //   exit(INCORRRECT_NUM_ARGS);
  // }
  Maze maze;
  IntMaze intMaze;
  init_vector(&maze);
  init_intVector(&intMaze);
  maze = parse_getline(argv[1], maze);
  intMaze = convertToInt(maze, intMaze);
  printMaze(maze);
  printIntMaze(intMaze);
  free_vector(&maze);
  free_intVector(&intMaze);
  return (EXIT_SUCCESS);
}

Maze parse_getline(char* input, Maze maze) {
  int counter = 0;
  int width = 0;
  FILE* fp = fopen(input, "r");
	char* line = NULL;
	size_t nbytes = 0;
  int linelen=0;
	while ((linelen=getline(&line, &nbytes, fp)) != -1) {
		line[linelen-1] = '\0';
    if(width < linelen){
      width = linelen;
    }
    int j = 0;
    for(j = 0; j < linelen; j++){
          insert_element_vector(&maze, line[j], counter, j);
    }
    counter++;
	}
	free(line);
  return(maze);
}

IntMaze convertToInt(Maze maze, IntMaze intMaze){
  int i, j;
  for(i = 0; i < vector_height(&maze); i++){
    for(j = 0; j < vector_width(&maze); j++){
      char temp = access_element_vector(&maze, i, j);
      char space = ' ';
      char hash = '#';
      char rob1 = 'S';
      char rob2 = 'F';
      char end1 = 'E';
      char end2 = 'L';
      if(temp == space){
        insert_element_intVector(&intMaze, 0, i, j);
      }
      else if(temp == hash){
        insert_element_intVector(&intMaze, 1, i, j);
      }
      else if(temp == rob1){
        insert_element_intVector(&intMaze, 2, i, j);
      }
      else if(temp == rob2){
        insert_element_intVector(&intMaze, 3, i, j);
      }
      else if(temp == end1){
        insert_element_intVector(&intMaze, 4, i, j);
      }
      else if(temp == end2){
        insert_element_intVector(&intMaze, 5, i, j);
      }
    }
  }
  return(intMaze);
}

void printMaze(Maze maze){
  int i, j;
  int height = vector_height(&maze);
  int width = vector_width(&maze);
  for(i = 0; i < height; i++){
    for(j = 0; j < width; j++){
      printf("%c", access_element_vector(&maze, i, j));
    }
    printf("\n");
  }
}

void printIntMaze(IntMaze intMaze){
  int i, j;
  int height = vector_intHeight(&intMaze);
  int width = vector_intWidth(&intMaze);
  for(i = 0; i <= height; i++){
    for(j = 0; j <= width; j++){
      printf("%d", access_element_intVector(&intMaze, i, j));
    }
    printf("\n");
  }
}
