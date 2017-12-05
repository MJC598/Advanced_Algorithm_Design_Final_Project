#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int main(int argc, char* argv[]) {
  // if(argc != 3){
  //   exit(INCORRRECT_NUM_ARGS);
  // }
  Maze maze;
  init_vector(&maze);
  parse_getline(argv[1], maze);
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

void parse_getline(char* input, Maze maze) {
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
    // printf("Content: %s\n", line);
    int j = 0;
    // char wall = '#';
    // char start = 'S';
    // char first = 'F';
    // char end = 'E';
    // char last = 'L';

    for(j = 0; j < linelen - 1; j++){
      // printf("line[j] = %c\n", line[j]);
      // if(strcmp(&line[j], &wall) == 0 || strcmp(&line[j], &start) == 0 || strcmp(&line[j], &first) == 0 || strcmp(&line[j], &end) == 0 || strcmp(&line[j], &last) == 0){
        // printf("Entered if statement; line[j] = %c\n", line[j]);
        // if(counter == 4){
          // printf("Entered counter == 4 if statement\n");
          insert_element_vector(&maze, line[j], j, counter);
          printf("%c", access_element_vector(&maze, j, counter));
        // }
        // printf("%c ", access_element_vector(&maze, counter, j));
      // printf("%c ", access_element_vector(&maze, counter, j));
      // }
      // printf("%c ", access_element_vector(&maze, counter, j));
    }
    printf("\n");
    counter++;

	}
  // printf("%c \n", maze[22][40]);

	free(line);
}
