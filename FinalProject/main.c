#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int main(int argc, char* argv[]) {
  // if(argc != 3){
  //   exit(INCORRRECT_NUM_ARGS);
  // }
  Maze maze;
  init_vector(&maze);
  maze = parse_getline(argv[1], maze);
  int i, j;
  int height = vector_height(&maze);
  printf("%d\n", height);
  int width = vector_width(&maze);
  printf("%d\n", width);
  for(i = 0; i < height; i++){
    for(j = 0; j < width; j++){
      printf("%c", access_element_vector(&maze, i, j));
    }
    printf("\n");
  }
  free_vector(&maze);
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
		line[linelen-1] = '\0'; //removing the newline and adding the NULL character
		//do whatever with line
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
