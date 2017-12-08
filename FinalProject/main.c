#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include <math.h>

int main(int argc, char* argv[]) {
   if(argc != 2){
       printf("Incorrect number of arguments\n");
     exit(6);
   }
  Maze maze;
  IntMaze intMaze;
  init_vector(&maze);
  init_intVector(&intMaze);
  maze = parse_getline(argv[1], maze);
  int r1H = 0, r1W = 0, r2H = 0, r2W = 0, e1H, e1W, e2H, e2W;
  intMaze = convertToInt(maze, intMaze, &r1H, &r1W, &r2H, &r2W, &e1H, &e1W, &e2H, &e2W);

  IntMaze bfs1, bfs2, bfs3, bfs4, bfs5, bfs6, bfs7, bfs8;
  init_intVector(&bfs1);
  init_intVector(&bfs2);
  init_intVector(&bfs3);
  init_intVector(&bfs4);
  init_intVector(&bfs5);
  init_intVector(&bfs6);
  init_intVector(&bfs7);
  init_intVector(&bfs8);

  int i,j;
  for(i = 0; i <= vector_intHeight(&intMaze); i++){
      for(j = 0; j <= vector_intWidth(&intMaze); j++){
          insert_element_intVector(&bfs1, -1, i, j);
          insert_element_intVector(&bfs2, -1, i, j);
          insert_element_intVector(&bfs3, -1, i, j);
          insert_element_intVector(&bfs4, -1, i, j);
          insert_element_intVector(&bfs5, -1, i, j);
          insert_element_intVector(&bfs6, -1, i, j);
          insert_element_intVector(&bfs7, -1, i, j);
          insert_element_intVector(&bfs8, -1, i, j);
      }
  }
  insert_element_intVector(&bfs1, 0, r1H, r1W);
  insert_element_intVector(&bfs2, 0, r2H, r2W);
  insert_element_intVector(&bfs3, 0, e1H, e1W);
  insert_element_intVector(&bfs4, 0, e2H, e2W);
  insert_element_intVector(&bfs5, 0, e1H, e1W);
  insert_element_intVector(&bfs6, 0, e2H, e2W);

  bfs1 = search1(intMaze, bfs1, r1H, r1W, 0); //2D Array of points possible to move to from robot 1 start.  Can't move through robot 2
  bfs2 = search2(intMaze, bfs2, r2H, r2W, 0); //2D Array of points possible to move to from robot 2 start.  Can't move through robot 1
  bfs3 = search3(intMaze, bfs3, &bfs5, e1H, e1W, 0); //2D Array of points possible to move to from exit 1.  Ignores robot 2
  bfs4 = search4(intMaze, bfs4, &bfs6, e2H, e2W, 0); //2D Array of points possible to move to from exit 2.  Ignores robot 1
  insert_element_intVector(&bfs5, -2, r1H, r1W);
  insert_element_intVector(&bfs6, -2, r2H, r2W);
  bfs5 = search5(intMaze, bfs3, bfs5, r1H, r1W, access_element_intVector(&bfs3, r1H, r1W));
  bfs6 = search5(intMaze, bfs4, bfs6, r2H, r2W, access_element_intVector(&bfs4, r2H, r2W));
  bfs5 = search6(bfs5);
  bfs6 = search6(bfs6);

  for(i = 0; i <= vector_intHeight(&intMaze); i++){
     for(j = 0; j <= vector_intWidth(&intMaze); j++){
//         if((access_element_intVector(&bfs1, i, j) != -1 || access_element_intVector(&bfs3, i, j) != -1) && access_element_intVector(&bfs6, i, j) != -2 && access_element_intVector(&bfs6, i, j) != -3)
//             insert_element_intVector(&bfs7, access_element_intVector(&bfs1, i, j) + access_element_intVector(&bfs3, i, j), i, j);
//         if((access_element_intVector(&bfs2, i, j) != -1 || access_element_intVector(&bfs4, i, j) != -1) && access_element_intVector(&bfs5, i, j) != -2 && access_element_intVector(&bfs6, i, j) != -3)
//             insert_element_intVector(&bfs8, access_element_intVector(&bfs2, i, j) + access_element_intVector(&bfs4, i, j), i, j);
         if(access_element_intVector(&bfs1, i, j) != -1 && access_element_intVector(&bfs6, i, j) != -2 && access_element_intVector(&bfs6, i, j) != -3)
             insert_element_intVector(&bfs7, access_element_intVector(&bfs1, i, j) + access_element_intVector(&bfs3, i, j), i, j);
         if(access_element_intVector(&bfs2, i, j) != -1 && access_element_intVector(&bfs5, i, j) != -2 && access_element_intVector(&bfs6, i, j) != -3)
             insert_element_intVector(&bfs8, access_element_intVector(&bfs2, i, j) + access_element_intVector(&bfs4, i, j), i, j);
     }
  }



  printf("Character Maze:\n");
  printMaze(maze);
//  printf("\n\nInitial int maze:\n");
//  printIntMaze(intMaze);
//  printf("\n\nBFS1:\n");
//  printIntMaze(bfs1);
//  printf("\n\nBFS2:\n");
//  printIntMaze(bfs2);
//  printf("\n\nBFS3:\n");
//  printIntMaze(bfs3);
//  printf("\n\nBFS4:\n");
//  printIntMaze(bfs4);
//  printf("\n\nBFS5:\n");
//  printIntMaze(bfs5);
//  printf("\n\nBFS6:\n");
//  printIntMaze(bfs6);
//  printf("\n\nBFS7:\n");
//  printIntMaze(bfs7);
//  printf("\n\nBFS8:\n");
//  printIntMaze(bfs8);
//  printf("\n\n");

  int temp = 20000000;
  int temp2 = 20000000;
  int tempi = 0, tempj = 0, tempi2= 0, tempj2 = 0;
  if(access_element_intVector(&bfs1, e1H, e1W) > -1){
      //Robot 1 has direct path to exit
      printf("There is a direct path for robot 1 to exit 1 of length %d.\n", access_element_intVector(&bfs1, e1H, e1W));
      printDirect(maze, bfs5, -1, -1, r2H, r2W);
      printf("Robot 1 takes the path.\n");
      if(access_element_intVector(&bfs4, r2H, r2W) > -1){
          //Robot 2 also has direct path
          printDirect(maze, bfs6, -1, -1, -1, -1);
          printf("Robot 2 then takes a direct path to exit 2 of length %d.\n", access_element_intVector(&bfs4, r2H, r2W));
      }
      else{
          //Robot 2 does not have direct path
          printDiverge(maze, -1, -1, r2H, r2W);
          printf("There is no direct path no matter what from robot2 to exit2.\n");
      }
  }
  else{
      //Robot 1 does not have a direct path to exit
      printf("There is no direct path from robot1 to exit1.\n");
      if(access_element_intVector(&bfs2, e2H, e2W) > -1){
          //Robot 2 has direct path to exit
          printf("There is a direct path for robot 2 to exit 2 of length %d.\n", access_element_intVector(&bfs2, e2H, e2W));
          printDirect(maze, bfs6, r1H, r1W, -1, -1);
          printf("Robot 2 takes the path.\n");
          if(access_element_intVector(&bfs3, r1H, r1W) > -1){
              //Robot 1 has direct path after diversion
              printDirect(maze, bfs5, -1, -1, -1, -1);
            printf("Robot 1 then takes a direct path to exit 1 of length %d.\n", access_element_intVector(&bfs3, r1H, r1W));
          }
          else{
              //Robot 1 does not have direct path even after diversion
              printDiverge(maze, r1H, r1W, -1, -1);
            printf("There is no direct path no matter what from robot1 to exit1.\n");
          }
      }
      else{
          //Robot 2 also does not have a direct path to exit
          if(access_element_intVector(&bfs3, r1H, r1W) > -1){
              //Robot 1 has a possible path ignoring robot 2
              if(access_element_intVector(&bfs4, r2H, r2W) > -1){
                  //Robot 2 also has direct path ignoring robot 1
                  for(i = 0; i <= vector_intHeight(&intMaze); i++){
                    for(j = 0; j <= vector_intWidth(&intMaze); j++){
                        if(access_element_intVector(&bfs7, i, j) < temp && access_element_intVector(&bfs7, i, j) != -1){
                            temp = access_element_intVector(&bfs7, i, j);
                            tempi = i;
                            tempj = j;
                        }
                        if(access_element_intVector(&bfs8, i, j) < temp2 && access_element_intVector(&bfs8, i, j) != -1){
                            temp2 = access_element_intVector(&bfs8, i, j);
                            tempi2 = i;
                            tempj2 = j;
                        }
                    }
                  }
                  if(temp == 20000000 || temp2 == 20000000){
                      //They both impede each other and no diversion is possible
                      //printf("Brian sucks major cock?\n");
                      printf("This maze is unsolvable.\n");
                  }
                  else{
                      //There is a possible diversion
                      if(temp < temp2){
                          //Robot 2 diverges for robot 1 to pass
                          printDiverge(maze, tempi, tempj, r2H, r2W);
                        printf("Robot 1 moves to (%d, %d) of length %d.\n", tempj, tempi, access_element_intVector(&bfs1, tempi, tempj));
                        printDirect(maze, bfs6, tempi, tempj, -1, -1);
                        printf("Robot 2 then takes a direct path to exit 2 of length %d.\n", access_element_intVector(&bfs4, r2H, r2W));
                        printDiverge(maze, -1, -1, -1, -1);
                        printf("Robot 1 then moves to exit 1 for total length of %d.\n",  access_element_intVector(&bfs7, tempi, tempj));
                      }
                      else{
                          //Robot 1 diverges for robot 2 to pass
                          printDiverge(maze, r1H, r1W, tempi2, tempj2);
                        printf("Robot 2 moves to (%d, %d) of length %d.\n", tempj2, tempi2, access_element_intVector(&bfs2, tempi2, tempj2));
                        printDirect(maze, bfs5, -1, -1, tempi2, tempj2);
                        printf("Robot 1 then takes a direct path to exit 1 of length %d.\n", access_element_intVector(&bfs3, r1H, r1W));
                        printDiverge(maze, -1, -1, -1, -1);
                        printf("Robot 2 then moves to exit 2 for total length of %d.\n",  access_element_intVector(&bfs8, tempi2, tempj2));
                      }
                  }
              }
              else{
                  //Robot 2 does not have direct path no matter what but may be able to diverge
                  for(i = 0; i <= vector_intHeight(&intMaze); i++){
                    for(j = 0; j <= vector_intWidth(&intMaze); j++){
                        if(access_element_intVector(&bfs8, i, j) < temp && access_element_intVector(&bfs8, i, j) != -1){
                            temp = access_element_intVector(&bfs8, i, j);
                            tempi = i;
                            tempj = j;
                        }
                    }
                  }
                  if(temp == 20000000){
                      //Robot 2 cannot diverge
                      printf("This maze is unsolvable.\n");
                  }
                  else{
                      //Robot 2 diverges so robot 1 exits, robot 2 cannot reach exit
                      printDiverge(maze, r1H, r1W, tempi, tempj);
                      printf("Robot 2 moves to (%d, %d) of length %d.\n", tempj, tempi, access_element_intVector(&bfs2, tempi, tempj));
                      printDirect(maze, bfs5, -1, -1, tempi, tempj);
                      printf("Robot 1 then takes a direct path to exit 1 of length %d.\n", access_element_intVector(&bfs3, r1H, r1W));
                      printDiverge(maze, -1, -1, tempi, tempj);
                      printf("Robot 2 cannot reach his exit.\n");
                  }
              }
          }
          else{
              //Robot 1 does not have direct path no matter what
              if(access_element_intVector(&bfs4, r2H, r2W) > -1){
                  //robot1 no exit but robot2 exit with diversion
                  for(i = 0; i <= vector_intHeight(&intMaze); i++){
                    for(j = 0; j <= vector_intWidth(&intMaze); j++){
                        if(access_element_intVector(&bfs7, i, j) < temp && access_element_intVector(&bfs7, i, j) != -1){
                            temp = access_element_intVector(&bfs7, i, j);
                            tempi = i;
                            tempj = j;
                        }
                    }
                  }
                  if(temp == 20000000){
                      //Robot 1 cannot diverge
                      printf("This maze is unsolvable.\n");
                  }
                  else{
                      //robot 1 diverges for robot 2 to exit, robot 1 cannot reach exit
                      printDiverge(maze, tempi, tempj, r2H, r2W);
                      printf("Robot 1 moves to (%d, %d) of length %d.\n", tempj, tempi, access_element_intVector(&bfs1, tempi, tempj));
                      printDirect(maze, bfs6, tempi, tempj, -1, -1);
                      printf("Robot 2 then takes a direct path to exit 2 of length %d.\n", access_element_intVector(&bfs4, r2H, r2W));
                      printDiverge(maze, tempi, tempj, -1, -1);
                      printf("Robot 1 cannot reach his exit.\n");
                  }
              }
              else{
                  //robot2 and robot1 no exit no matter what
                  printf("Neither robot can reach the exit.\n");
              }
          }
      }
  }



  //free functions
  free_vector(&maze);
  free_intVector(&intMaze);
  free_intVector(&bfs1);
  free_intVector(&bfs2);
  free_intVector(&bfs3);
  free_intVector(&bfs4);
  free_intVector(&bfs5);
  free_intVector(&bfs6);
  free_intVector(&bfs7);
  free_intVector(&bfs8);
  return (EXIT_SUCCESS);
}

Maze parse_getline(char* input, Maze maze) {
  int counter = 0;
  int width = 0;
  int s = 0, f = 0, e = 0, l = 0;
  int i;
  FILE* fp = fopen(input, "r");

  //check for issues opening file
  if(fp == NULL){
      printf("File does not open.\n");
      exit(5);
  }
  char* line = NULL;
  size_t nbytes = 0;
  int linelen=0;
  while ((linelen=getline(&line, &nbytes, fp)) != -1) {
    line[linelen-1] = '\0';
    for(i=0; i < linelen - 1; i++){
        if(line[i] == 'F'){
            f++;
        }
        if(line[i] == 'E'){
            e++;
        }
        if(line[i] == 'S'){
            s++;
        }
        if(line[i] == 'L'){
            l++;
        }
    }



    if(width < linelen){
        width = linelen;
    }
    int j = 0;
    for(j = 0; j < linelen; j++){
        insert_element_vector(&maze, line[j], counter, j);
    }
  counter++;
}
  if(l != 1 || s != 1 || e != 1 || f != 1){
        printf("Parsing Error.\n");
        exit(7);
    }
  free(line);
  fclose(fp);

  //check for issues closing file
  if(!fp){
      printf("File failed to close.\n");
      exit(7);
  }
  return(maze);
}

IntMaze convertToInt(Maze maze, IntMaze intMaze, int *r1H, int *r1W, int *r2H, int *r2W, int *e1H, int *e1W, int *e2H, int *e2W){
  int i, j;
  for(i = 0; i <= vector_height(&maze); i++){
    for(j = 0; j <= vector_width(&maze); j++){
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
        *e1H = i;
        *e1W = j;
      }
      else if(temp == end2){
        insert_element_intVector(&intMaze, 5, i, j);
        *e2H = i;
        *e2W = j;
      }
    }
  }
  for(i = 0; i < vector_intHeight(&intMaze); i++){
    for(j = 0; j < vector_intWidth(&intMaze); j++){
        if(access_element_intVector(&intMaze, i, j) == 2){
            *r1H = i;
            *r1W = j;
            if(i != vector_intHeight(&intMaze)){
                if(access_element_intVector(&intMaze, i + 1, j) == 0){
                    insert_element_intVector(&intMaze, 6, i + 1, j);
                }
                if(j != vector_intWidth(&intMaze)){
                    if(access_element_intVector(&intMaze, i + 1, j + 1) == 0){
                        insert_element_intVector(&intMaze, 6, i + 1, j + 1);
                    }
                }
                if(j != 0){
                    if(access_element_intVector(&intMaze, i + 1, j - 1) == 0){
                        insert_element_intVector(&intMaze, 6, i + 1, j - 1);
                    }
                }
            }

            if(i != 0){
                if(access_element_intVector(&intMaze, i - 1, j) == 0){
                    insert_element_intVector(&intMaze, 6, i - 1, j);
                }
                if(j != vector_intWidth(&intMaze)){
                    if(access_element_intVector(&intMaze, i - 1, j + 1) == 0){
                        insert_element_intVector(&intMaze, 6, i - 1, j + 1);
                    }
                }
                if(j != 0){
                    if(access_element_intVector(&intMaze, i - 1, j - 1) == 0){
                        insert_element_intVector(&intMaze, 6, i - 1, j - 1);
                    }
                }
            }

            if(j != vector_intWidth(&intMaze)){
                if(access_element_intVector(&intMaze, i, j + 1) == 0){
                    insert_element_intVector(&intMaze, 6, i, j + 1);
                }
            }

            if(j != 0){
                if(access_element_intVector(&intMaze, i, j - 1) == 0){
                    insert_element_intVector(&intMaze, 6, i, j - 1);
                }
            }
        }

        if(access_element_intVector(&intMaze, i, j) == 3){
            *r2H = i;
            *r2W = j;
            if(i != vector_intHeight(&intMaze)){
                if(access_element_intVector(&intMaze, i + 1, j) == 0){
                    insert_element_intVector(&intMaze, 7, i + 1, j);
                }
                if(j != vector_intWidth(&intMaze)){
                    if(access_element_intVector(&intMaze, i + 1, j + 1) == 0){
                        insert_element_intVector(&intMaze, 7, i + 1, j + 1);
                    }
                }
                if(j != 0){
                    if(access_element_intVector(&intMaze, i + 1, j - 1) == 0){
                        insert_element_intVector(&intMaze, 7, i + 1, j - 1);
                    }
                }
            }

            if(i != 0){
                if(access_element_intVector(&intMaze, i - 1, j) == 0){
                    insert_element_intVector(&intMaze, 7, i - 1, j);
                }
                if(j != vector_intWidth(&intMaze)){
                    if(access_element_intVector(&intMaze, i - 1, j + 1) == 0){
                        insert_element_intVector(&intMaze, 7, i - 1, j + 1);
                    }
                }
                if(j != 0){
                    if(access_element_intVector(&intMaze, i - 1, j - 1) == 0){
                        insert_element_intVector(&intMaze, 7, i - 1, j - 1);
                    }
                }
            }

            if(j != vector_intWidth(&intMaze)){
                if(access_element_intVector(&intMaze, i, j + 1) == 0){
                    insert_element_intVector(&intMaze, 7, i, j + 1);
                }
            }

            if(j != 0){
                if(access_element_intVector(&intMaze, i, j - 1) == 0){
                    insert_element_intVector(&intMaze, 7, i, j - 1);
                }
            }
        }
    }
  }
  return(intMaze);
}

void printMaze(Maze maze){
  int i, j;
  int height = vector_height(&maze);
  int width = vector_width(&maze);
  for(i = 0; i < height + 1; i++){
    for(j = 0; j < width + 1; j++){
      printf("%c", access_element_vector(&maze, i, j));
    }
    printf("\n");
  }
}

void printDiverge(Maze maze, int r1h, int r1w, int r2h, int r2w){
  int i, j;
  int height = vector_height(&maze);
  int width = vector_width(&maze);
  for(i = 0; i <= height; i++){
    for(j = 0; j < width - 1; j++){
        if(i == r1h && j == r1w)
            printf("%c", 'S');
        else if(i == r2h && j == r2w)
            printf("%c", 'F');
        else if(access_element_vector(&maze, i, j) == 'S')
            printf("%c", ' ');
        else if(access_element_vector(&maze, i, j) == 'F')
            printf("%c", ' ');
        else
            printf("%c", access_element_vector(&maze, i, j));
    }
    printf("\n");
  }
}

void printDirect(Maze maze, IntMaze direct, int r1h, int r1w, int r2h, int r2w){
  int i, j;
  int height = vector_height(&maze);
  int width = vector_width(&maze);
  for(i = 0; i <= height; i++){
    for(j = 0; j < width - 1; j++){
        if(access_element_vector(&maze, i, j) == 'E')
            printf("E");
        else if(access_element_vector(&maze, i, j) == 'L')
            printf("L");
        else if(access_element_intVector(&direct, i, j) == -2)
            printf("+");
        else if(i == r1h && j == r1w)
            printf("%c", 'S');
        else if(i == r2h && j == r2w)
            printf("%c", 'F');
        else if(access_element_vector(&maze, i, j) == 'S')
            printf("%c", ' ');
        else if(access_element_vector(&maze, i, j) == 'F')
            printf("%c", ' ');
        else
            printf("%c", access_element_vector(&maze, i, j));
    }
    printf("\n");
  }
}

void printIntMaze(IntMaze intMaze){
  long i, j, x, count = 0;
  int height = vector_intHeight(&intMaze);
  int width = vector_intWidth(&intMaze);
  for(i = 0; i <= height; i++){
    for(j = 0; j <= width; j++){
        x = access_element_intVector(&intMaze, i, j);
        printf("%d", x);
//        if(x == -1)
//            printf("%s", "x");
//        else if(x == 0)
//            printf("%s", "$");
//        else if(x/10 == 0)
//            printf("%d", abs(x));
//        else if(x/10 >= 1 && x/10 <= 9)
//            printf("0%d", abs(x));
//        else if(x/10 >= 10 && x/10 <= 99)
//            printf("%d", abs(x));
//        else{
//            printf("%s", "FUK");
//            count++;
//        }
    }
    printf("\n");
  }
}

IntMaze search1(IntMaze intMaze, IntMaze search, int i, int j, int weight){
    Stack s;
    init_stack(&s);
    Pos p;
    push(&s, i, j, weight);
    while(!isEmpty(&s)){
        p = pop(&s);
            if(getHeight(p) != vector_intHeight(&intMaze)){ //check to make sure not at bottom of map
                if(access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p)) == 0 || access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p)) == 4 || access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p)) == 6){ //check
                    if(access_element_intVector(&search, getHeight(p) + 1, getWidth(p)) == -1 || access_element_intVector(&search, getHeight(p) + 1, getWidth(p)) > getWeight(p) + 1){
                        if(getWeight(p) >= 0){
                            insert_element_intVector(&search, getWeight(p) + 1, getHeight(p) + 1, getWidth(p));
                            push(&s, getHeight(p) + 1, getWidth(p), getWeight(p) + 1);
                        }
                    }
                }

                if(getWidth(p) != vector_intWidth(&intMaze)){
                    if(access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p) + 1) == 0 || access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p) + 1) == 4 || access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p) + 1) == 6){
                        if(access_element_intVector(&search, getHeight(p) + 1, getWidth(p) + 1) == -1 || access_element_intVector(&search, getHeight(p) + 1, getWidth(p) + 1) > getWeight(p) + 1){
                            if(getWeight(p) >= 0){
                            insert_element_intVector(&search, getWeight(p) + 1, getHeight(p) + 1, getWidth(p) + 1);
                            push(&s, getHeight(p) + 1, getWidth(p) + 1, getWeight(p) + 1);
                            }
                        }
                    }
                }
                if(getWidth(p) != 0){
                    if(access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p) - 1) == 0 || access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p) - 1) == 4 || access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p) - 1) == 6){
                        if(access_element_intVector(&search, getHeight(p) + 1, getWidth(p) - 1) == -1 || access_element_intVector(&search, getHeight(p) + 1, getWidth(p) - 1) > getWeight(p) + 1){
                            if(getWeight(p) >= 0){
                            insert_element_intVector(&search, getWeight(p) + 1, getHeight(p) + 1, getWidth(p) - 1);
                            push(&s, getHeight(p) + 1, getWidth(p) - 1, getWeight(p) + 1);
                            }
                        }
                    }
                }
            }

            if(getHeight(p) != 0){ //current position is not along the top of the map
                if(access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p)) == 0 || access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p)) == 4 || access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p)) == 6){
                    if(access_element_intVector(&search, getHeight(p) - 1, getWidth(p)) == -1 || access_element_intVector(&search, getHeight(p) - 1, getWidth(p)) > getWeight(p) + 1){
                        if(getWeight(p) >= 0){
                        insert_element_intVector(&search, getWeight(p) + 1, getHeight(p) - 1, getWidth(p));
                        push(&s, getHeight(p) - 1, getWidth(p), getWeight(p) + 1);
                        }
                    }
                }
                if(getWidth(p) != vector_intWidth(&intMaze)){
                    if(access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p) + 1) == 0 || access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p) + 1) == 4 || access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p) + 1) == 6){
                        if(access_element_intVector(&search, getHeight(p) - 1, getWidth(p) + 1) == -1 || access_element_intVector(&search, getHeight(p) - 1, getWidth(p) + 1) > getWeight(p) + 1){
                            if(getWeight(p) >= 0){
                            insert_element_intVector(&search, getWeight(p) + 1, getHeight(p) - 1, getWidth(p) + 1);
                            push(&s, getHeight(p) - 1, getWidth(p) + 1, getWeight(p) + 1);
                            }
                        }
                    }
                }
                if(getWidth(p) != 0){
                    if(access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p) - 1) == 0 || access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p) - 1) == 4 || access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p) - 1) == 6){
                        if(access_element_intVector(&search, getHeight(p) - 1, getWidth(p) - 1) == -1 || access_element_intVector(&search, getHeight(p) - 1, getWidth(p) - 1) > getWeight(p) + 1){
                            if(getWeight(p) >= 0){
                            insert_element_intVector(&search, getWeight(p) + 1, getHeight(p) - 1, getWidth(p) - 1);
                            push(&s, getHeight(p) - 1, getWidth(p) - 1, getWeight(p) + 1);
                            }
                        }
                    }
                }
            }

            if(getWidth(p) != vector_intWidth(&intMaze)){
                if(access_element_intVector(&intMaze, getHeight(p), getWidth(p) + 1) == 0 || access_element_intVector(&intMaze, getHeight(p), getWidth(p) + 1) == 4 || access_element_intVector(&intMaze, getHeight(p), getWidth(p) + 1) == 6){
                    if(access_element_intVector(&search, getHeight(p), getWidth(p) + 1) == -1 || access_element_intVector(&search, getHeight(p), getWidth(p) + 1) > getWeight(p) + 1){
                        if(getWeight(p) >= 0){
                        insert_element_intVector(&search, getWeight(p) + 1, getHeight(p), getWidth(p) + 1);
                        push(&s, getHeight(p), getWidth(p) + 1, getWeight(p) + 1);}
                    }
                }
            }

            if(getWidth(p) != 0){
                if(access_element_intVector(&intMaze, getHeight(p), getWidth(p) - 1) == 0 || access_element_intVector(&intMaze, getHeight(p), getWidth(p) - 1) == 4 || access_element_intVector(&intMaze, getHeight(p), getWidth(p) - 1) == 6){
                    if(access_element_intVector(&search, getHeight(p), getWidth(p) - 1) == -1 || access_element_intVector(&search, getHeight(p), getWidth(p) - 1) > getWeight(p) + 1){
                        if(getWeight(p) >= 0){
                        insert_element_intVector(&search, getWeight(p) + 1, getHeight(p), getWidth(p) - 1);
                        push(&s, getHeight(p), getWidth(p) - 1, getWeight(p) + 1);}
                    }
                }
            }
    }
    return search;
}

IntMaze search2(IntMaze intMaze, IntMaze search, int i, int j, int weight){
    Stack s;
    init_stack(&s);
    Pos p;
    push(&s, i, j, weight);
    while(!isEmpty(&s)){
        p = pop(&s);
            if(getHeight(p) != vector_intHeight(&intMaze)){
                if(access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p)) == 0 || access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p)) == 5 || access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p)) == 7){
                    if(access_element_intVector(&search, getHeight(p) + 1, getWidth(p)) == -1 || access_element_intVector(&search, getHeight(p) + 1, getWidth(p)) > getWeight(p) + 1){
                        insert_element_intVector(&search, getWeight(p) + 1, getHeight(p) + 1, getWidth(p));
                        push(&s, getHeight(p) + 1, getWidth(p), getWeight(p) + 1);
                    }
                }
                if(getWidth(p) != vector_intWidth(&intMaze)){
                    if(access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p) + 1) == 0 || access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p) + 1) == 5 || access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p) + 1) == 7){
                        if(access_element_intVector(&search, getHeight(p) + 1, getWidth(p) + 1) == -1 || access_element_intVector(&search, getHeight(p) + 1, getWidth(p) + 1) > getWeight(p) + 1){
                            insert_element_intVector(&search, getWeight(p) + 1, getHeight(p) + 1, getWidth(p) + 1);
                            push(&s, getHeight(p) + 1, getWidth(p) + 1, getWeight(p) + 1);
                        }
                    }
                }
                if(getWidth(p) != 0){
                    if(access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p) - 1) == 0 || access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p) - 1) == 5 || access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p) - 1) == 7){
                        if(access_element_intVector(&search, getHeight(p) + 1, getWidth(p) - 1) == -1 || access_element_intVector(&search, getHeight(p) + 1, getWidth(p) - 1) > getWeight(p) + 1){
                            insert_element_intVector(&search, getWeight(p) + 1, getHeight(p) + 1, getWidth(p) - 1);
                            push(&s, getHeight(p) + 1, getWidth(p) - 1, getWeight(p) + 1);
                        }
                    }
                }
            }

            if(getHeight(p) != 0){
                if(access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p)) == 0 || access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p)) == 5 || access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p)) == 7){
                    if(access_element_intVector(&search, getHeight(p) - 1, getWidth(p)) == -1 || access_element_intVector(&search, getHeight(p) - 1, getWidth(p)) > getWeight(p) + 1){
                        insert_element_intVector(&search, getWeight(p) + 1, getHeight(p) - 1, getWidth(p));
                        push(&s, getHeight(p) - 1, getWidth(p), getWeight(p) + 1);
                    }
                }
                if(getWidth(p) != vector_intWidth(&intMaze)){
                    if(access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p) + 1) == 0 || access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p) + 1) == 5 || access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p) + 1) == 7){
                        if(access_element_intVector(&search, getHeight(p) - 1, getWidth(p) + 1) == -1 || access_element_intVector(&search, getHeight(p) - 1, getWidth(p) + 1) > getWeight(p) + 1){
                            insert_element_intVector(&search, getWeight(p) + 1, getHeight(p) - 1, getWidth(p) + 1);
                            search = search2(intMaze, search, getHeight(p) - 1, getWidth(p) + 1, getWeight(p) + 1);
                        }
                    }
                }
                if(getWidth(p) != 0){
                    if(access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p) - 1) == 0 || access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p) - 1) == 5 || access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p) - 1) == 7){
                        if(access_element_intVector(&search, getHeight(p) - 1, getWidth(p) - 1) == -1 || access_element_intVector(&search, getHeight(p) - 1, getWidth(p) - 1) > getWeight(p) + 1){
                            insert_element_intVector(&search, getWeight(p) + 1, getHeight(p) - 1, getWidth(p) - 1);
                            push(&s, getHeight(p) - 1, getWidth(p) - 1, getWeight(p) + 1);
                        }
                    }
                }
            }

            if(getWidth(p) != vector_intWidth(&intMaze)){
                if(access_element_intVector(&intMaze, getHeight(p), getWidth(p) + 1) == 0 || access_element_intVector(&intMaze, getHeight(p), getWidth(p) + 1) == 5 || access_element_intVector(&intMaze, getHeight(p), getWidth(p) + 1) == 7){
                    if(access_element_intVector(&search, getHeight(p), getWidth(p) + 1) == -1 || access_element_intVector(&search, getHeight(p), getWidth(p) + 1) > getWeight(p) + 1){
                        insert_element_intVector(&search, getWeight(p) + 1, getHeight(p), getWidth(p) + 1);
                        push(&s, getHeight(p), getWidth(p) + 1, getWeight(p) + 1);
                    }
                }
            }

            if(getWidth(p) != 0){
                if(access_element_intVector(&intMaze, getHeight(p), getWidth(p) - 1) == 0 || access_element_intVector(&intMaze, getHeight(p), getWidth(p) - 1) == 5 || access_element_intVector(&intMaze, getHeight(p), getWidth(p) - 1) == 7){
                    if(access_element_intVector(&search, getHeight(p), getWidth(p) - 1) == -1 || access_element_intVector(&search, getHeight(p), getWidth(p) - 1) > getWeight(p) + 1){
                        insert_element_intVector(&search, getWeight(p) + 1, getHeight(p), getWidth(p) - 1);
                        push(&s, getHeight(p), getWidth(p) - 1, getWeight(p) + 1);
                    }
                }
            }
    }
    return search;
}

IntMaze search3(IntMaze intMaze, IntMaze search, IntMaze *path, int i, int j, int weight){
    Stack s;
    init_stack(&s);
    Pos p;
    push(&s, i, j, weight);
    while(!isEmpty(&s)){
        p = pop(&s);
            if(getHeight(p) != vector_intHeight(&intMaze)){
                if(access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p)) == 0 || access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p)) == 2 || access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p)) == 6 || access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p)) == 3 || access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p)) == 7){
                    if(access_element_intVector(&search, getHeight(p) + 1, getWidth(p)) == -1 || access_element_intVector(&search, getHeight(p) + 1, getWidth(p)) > getWeight(p) + 1){
                        insert_element_intVector(&search, getWeight(p) + 1, getHeight(p) + 1, getWidth(p));
                        insert_element_intVector(path, 0, getHeight(p) + 1, getWidth(p));
                        push(&s, getHeight(p) + 1, getWidth(p), getWeight(p) + 1);
                    }
                }
                if(getWidth(p) != vector_intWidth(&intMaze)){
                    if(access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p) + 1) == 0 || access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p) + 1) == 2 || access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p) + 1) == 6 || access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p) + 1) == 3 || access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p) + 1) == 7){
                        if(access_element_intVector(&search, getHeight(p) + 1, getWidth(p) + 1) == -1 || access_element_intVector(&search, getHeight(p) + 1, getWidth(p) + 1) > getWeight(p) + 1){
                            insert_element_intVector(&search, getWeight(p) + 1, getHeight(p) + 1, getWidth(p) + 1);
                            insert_element_intVector(path, 0, getHeight(p) + 1, getWidth(p) + 1);
                            push(&s, getHeight(p) + 1, getWidth(p) + 1, getWeight(p) + 1);
                        }
                    }
                }
                if(getWidth(p) != 0){
                    if(access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p) - 1) == 0 || access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p) - 1) == 2 || access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p) - 1) == 6 || access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p) - 1) == 3 || access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p) - 1) == 7){
                        if(access_element_intVector(&search, getHeight(p) + 1, getWidth(p) - 1) == -1 || access_element_intVector(&search, getHeight(p) + 1, getWidth(p) - 1) > getWeight(p) + 1){
                            insert_element_intVector(&search, getWeight(p) + 1, getHeight(p) + 1, getWidth(p) - 1);
                            insert_element_intVector(path, 0, getHeight(p) + 1, getWidth(p) - 1);
                            push(&s, getHeight(p) + 1, getWidth(p) - 1, getWeight(p) + 1);
                        }
                    }
                }
            }

            if(getHeight(p) != 0){
                if(access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p)) == 0 || access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p)) == 2 || access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p)) == 6 || access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p)) == 3 || access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p)) == 7){
                    if(access_element_intVector(&search, getHeight(p) - 1, getWidth(p)) == -1 || access_element_intVector(&search, getHeight(p) - 1, getWidth(p)) > getWeight(p) + 1){
                        insert_element_intVector(&search, getWeight(p) + 1, getHeight(p) - 1, getWidth(p));
                        insert_element_intVector(path, 0, getHeight(p) - 1, getWidth(p));
                        push(&s, getHeight(p) - 1, getWidth(p), getWeight(p) + 1);
                    }
                }
                if(getWidth(p) != vector_intWidth(&intMaze)){
                    if(access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p) + 1) == 0 || access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p) + 1) == 2 || access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p) + 1) == 6 || access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p) + 1) == 3 || access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p) + 1) == 7){
                        if(access_element_intVector(&search, getHeight(p) - 1, getWidth(p) + 1) == -1 || access_element_intVector(&search, getHeight(p) - 1, getWidth(p) + 1) > getWeight(p) + 1){
                            insert_element_intVector(&search, getWeight(p) + 1, getHeight(p) - 1, getWidth(p) + 1);
                            insert_element_intVector(path, 0, getHeight(p) - 1, getWidth(p) + 1);
                            push(&s, getHeight(p) - 1, getWidth(p) + 1, getWeight(p) + 1);
                        }
                    }
                }
                if(getWidth(p) != 0){
                    if(access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p) - 1) == 0 || access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p) - 1) == 2 || access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p) - 1) == 6 || access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p) - 1) == 3 || access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p) - 1) == 7){
                        if(access_element_intVector(&search, getHeight(p) - 1, getWidth(p) - 1) == -1 || access_element_intVector(&search, getHeight(p) - 1, getWidth(p) - 1) > getWeight(p) + 1){
                            insert_element_intVector(&search, getWeight(p) + 1, getHeight(p) - 1, getWidth(p) - 1);
                            insert_element_intVector(path, 0, getHeight(p) - 1, getWidth(p) - 1);
                            push(&s, getHeight(p) - 1, getWidth(p) - 1, getWeight(p) + 1);
                        }
                    }
                }
            }

            if(getWidth(p) != vector_intWidth(&intMaze)){
                if(access_element_intVector(&intMaze, getHeight(p), getWidth(p) + 1) == 0 || access_element_intVector(&intMaze, getHeight(p), getWidth(p) + 1) == 2 || access_element_intVector(&intMaze, getHeight(p), getWidth(p) + 1) == 6 || access_element_intVector(&intMaze, getHeight(p), getWidth(p) + 1) == 3 || access_element_intVector(&intMaze, getHeight(p), getWidth(p) + 1) == 7){
                    if(access_element_intVector(&search, getHeight(p), getWidth(p) + 1) == -1 || access_element_intVector(&search, getHeight(p), getWidth(p) + 1) > getWeight(p) + 1){
                        insert_element_intVector(&search, getWeight(p) + 1, getHeight(p), getWidth(p) + 1);
                        insert_element_intVector(path, 0, getHeight(p), getWidth(p) + 1);
                        push(&s, getHeight(p), getWidth(p) + 1, getWeight(p) + 1);
                    }
                }
            }

            if(getWidth(p) != 0){
                if(access_element_intVector(&intMaze, getHeight(p), getWidth(p) - 1) == 0 || access_element_intVector(&intMaze, getHeight(p), getWidth(p) - 1) == 2 || access_element_intVector(&intMaze, getHeight(p), getWidth(p) - 1) == 6 || access_element_intVector(&intMaze, getHeight(p), getWidth(p) - 1) == 3 || access_element_intVector(&intMaze, getHeight(p), getWidth(p) - 1) == 7){
                    if(access_element_intVector(&search, getHeight(p), getWidth(p) - 1) == -1 || access_element_intVector(&search, getHeight(p), getWidth(p) - 1) > getWeight(p) + 1){
                        insert_element_intVector(&search, getWeight(p) + 1, getHeight(p), getWidth(p) - 1);
                         insert_element_intVector(path, 0, getHeight(p), getWidth(p) - 1);
                        push(&s, getHeight(p), getWidth(p) - 1, getWeight(p) + 1);
                    }
                }
            }
    }
            return search;
}

IntMaze search4(IntMaze intMaze, IntMaze search, IntMaze *path, int i, int j, int weight){
    Stack s;
    init_stack(&s);
    Pos p;
    push(&s, i, j, weight);
    while(!isEmpty(&s)){
        p = pop(&s);
            if(getHeight(p) != vector_intHeight(&intMaze)){
                if(access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p)) == 0 || access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p)) == 3 || access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p)) == 7 || access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p)) == 2 || access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p)) == 6){
                    if(access_element_intVector(&search, getHeight(p) + 1, getWidth(p)) == -1 || access_element_intVector(&search, getHeight(p) + 1, getWidth(p)) > getWeight(p) + 1){
                        insert_element_intVector(&search, getWeight(p) + 1, getHeight(p) + 1, getWidth(p));
                        insert_element_intVector(path, 0, getHeight(p) + 1, getWidth(p));
                        push(&s, getHeight(p) + 1, getWidth(p), getWeight(p) + 1);
                    }
                }
                if(getWidth(p) != vector_intWidth(&intMaze)){
                    if(access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p) + 1) == 0 || access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p) + 1) == 3 || access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p) + 1) == 7 || access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p) + 1) == 2 || access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p) + 1) == 6){
                        if(access_element_intVector(&search, getHeight(p) + 1, getWidth(p) + 1) == -1 || access_element_intVector(&search, getHeight(p) + 1, getWidth(p) + 1) > getWeight(p) + 1){
                            insert_element_intVector(&search, getWeight(p) + 1, getHeight(p) + 1, getWidth(p) + 1);
                            insert_element_intVector(path, 0, getHeight(p) + 1, getWidth(p) + 1);
                            push(&s, getHeight(p) + 1, getWidth(p) + 1, getWeight(p) + 1);
                        }
                    }
                }
                if(getWidth(p) != 0){
                    if(access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p) - 1) == 0 || access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p) - 1) == 3 || access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p) - 1) == 7 || access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p) - 1) == 2 || access_element_intVector(&intMaze, getHeight(p) + 1, getWidth(p) - 1) == 6){
                        if(access_element_intVector(&search, getHeight(p) + 1, getWidth(p) - 1) == -1 || access_element_intVector(&search, getHeight(p) + 1, getWidth(p) - 1) > getWeight(p) + 1){
                            insert_element_intVector(&search, getWeight(p) + 1, getHeight(p) + 1, getWidth(p) - 1);
                            insert_element_intVector(path, 0, getHeight(p) + 1, getWidth(p) - 1);
                            push(&s, getHeight(p) + 1, getWidth(p) - 1, getWeight(p) + 1);
                        }
                    }
                }
            }

            if(getHeight(p) != 0){
                if(access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p)) == 0 || access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p)) == 3 || access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p)) == 7 || access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p)) == 2 || access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p)) == 6){
                    if(access_element_intVector(&search, getHeight(p) - 1, getWidth(p)) == -1 || access_element_intVector(&search, getHeight(p) - 1, getWidth(p)) > getWeight(p) + 1){
                        insert_element_intVector(&search, getWeight(p) + 1, getHeight(p) - 1, getWidth(p));
                         insert_element_intVector(path, 0, getHeight(p) - 1, getWidth(p));
                        push(&s, getHeight(p) - 1, getWidth(p), getWeight(p) + 1);
                    }
                }
                if(getWidth(p) != vector_intWidth(&intMaze)){
                    if(access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p) + 1) == 0 || access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p) + 1) == 3 || access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p) + 1) == 7 || access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p) + 1) == 2 || access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p) + 1) == 6){
                        if(access_element_intVector(&search, getHeight(p) - 1, getWidth(p) + 1) == -1 || access_element_intVector(&search, getHeight(p) - 1, getWidth(p) + 1) > getWeight(p) + 1){
                            insert_element_intVector(&search, getWeight(p) + 1, getHeight(p) - 1, getWidth(p) + 1);
                            insert_element_intVector(path, 0, getHeight(p) - 1, getWidth(p) + 1);
                            push(&s, getHeight(p) - 1, getWidth(p) + 1, getWeight(p) + 1);
                        }
                    }
                }
                if(getWidth(p) != 0){
                    if(access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p) - 1) == 0 || access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p) - 1) == 3 || access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p) - 1) == 7 || access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p) - 1) == 2 || access_element_intVector(&intMaze, getHeight(p) - 1, getWidth(p) - 1) == 6){
                        if(access_element_intVector(&search, getHeight(p) - 1, getWidth(p) - 1) == -1 || access_element_intVector(&search, getHeight(p) - 1, getWidth(p) - 1) > getWeight(p) + 1){
                            insert_element_intVector(&search, getWeight(p) + 1, getHeight(p) - 1, getWidth(p) - 1);
                            insert_element_intVector(path, 0, getHeight(p) - 1, getWidth(p) - 1);
                            push(&s, getHeight(p) - 1, getWidth(p) - 1, getWeight(p) + 1);
                        }
                    }
                }
            }

            if(getWidth(p) != vector_intWidth(&intMaze)){
                if(access_element_intVector(&intMaze, getHeight(p), getWidth(p) + 1) == 0 || access_element_intVector(&intMaze, getHeight(p), getWidth(p) + 1) == 3 || access_element_intVector(&intMaze, getHeight(p), getWidth(p) + 1) == 7 || access_element_intVector(&intMaze, getHeight(p), getWidth(p) + 1) == 2 || access_element_intVector(&intMaze, getHeight(p), getWidth(p) + 1) == 6){
                    if(access_element_intVector(&search, getHeight(p), getWidth(p) + 1) == -1 || access_element_intVector(&search, getHeight(p), getWidth(p) + 1) > getWeight(p) + 1){
                        insert_element_intVector(&search, getWeight(p) + 1, getHeight(p), getWidth(p) + 1);
                        insert_element_intVector(path, 0, getHeight(p), getWidth(p) + 1);
                        push(&s, getHeight(p), getWidth(p) + 1, getWeight(p) + 1);
                    }
                }
            }

            if(getWidth(p) != 0){
                if(access_element_intVector(&intMaze, getHeight(p), getWidth(p) - 1) == 0 || access_element_intVector(&intMaze, getHeight(p), getWidth(p) - 1) == 3 || access_element_intVector(&intMaze, getHeight(p), getWidth(p) - 1) == 7 || access_element_intVector(&intMaze, getHeight(p), getWidth(p) - 1) == 2 || access_element_intVector(&intMaze, getHeight(p), getWidth(p) - 1) == 6){
                    if(access_element_intVector(&search, getHeight(p), getWidth(p) - 1) == -1 || access_element_intVector(&search, getHeight(p), getWidth(p) - 1) > getWeight(p) + 1){
                        insert_element_intVector(&search, getWeight(p) + 1, getHeight(p), getWidth(p) - 1);
                        insert_element_intVector(path, 0, getHeight(p), getWidth(p) - 1);
                        push(&s, getHeight(p), getWidth(p) - 1, getWeight(p) + 1);
                    }
                }
            }
    }
            return search;
}


IntMaze search5(IntMaze intMaze, IntMaze search, IntMaze path, int i, int j, int weight){
    Stack s;
    init_stack(&s);
    Pos p;
    int curr = 0;
    int brian = weight;
    push(&s, i, j, weight);
    while(!isEmpty(&s)){
        p = pop(&s);
        curr = getWeight(p);
        if(getWidth(p) != vector_intWidth(&intMaze)){
                if(access_element_intVector(&path, getHeight(p), getWidth(p) + 1) == 0){
                    if(access_element_intVector(&search, getHeight(p), getWidth(p) + 1) == curr - 1 && curr == brian && curr >= 0){
                        insert_element_intVector(&path, -2, getHeight(p), getWidth(p) + 1);
                        push(&s, getHeight(p), getWidth(p) + 1, getWeight(p) - 1);
                        brian--;
                    }
                }
            }

            if(getWidth(p) != 0){
                if(access_element_intVector(&path, getHeight(p), getWidth(p) - 1) == 0){
                    if(access_element_intVector(&search, getHeight(p), getWidth(p) - 1) == curr - 1 && curr == brian && curr >= 0){
                        insert_element_intVector(&path, -2, getHeight(p), getWidth(p) - 1);
                        push(&s, getHeight(p), getWidth(p) - 1, getWeight(p) - 1);
                        brian--;
                    }
                }
            }

            if(getHeight(p) != 0){
                if(access_element_intVector(&path, getHeight(p) - 1, getWidth(p)) == 0){
                    if(access_element_intVector(&search, getHeight(p) - 1, getWidth(p)) == curr - 1 && curr == brian && curr >= 0){
                        insert_element_intVector(&path, -2, getHeight(p) - 1, getWidth(p));
                        push(&s, getHeight(p) - 1, getWidth(p), getWeight(p) - 1);
                        brian--;
                    }
                }
            }
            if(getHeight(p) != vector_intHeight(&intMaze)){
                if(access_element_intVector(&path, getHeight(p) + 1, getWidth(p)) == 0){
                    if(access_element_intVector(&search, getHeight(p) + 1, getWidth(p)) == curr - 1 && curr == brian &&curr >= 0){
                        insert_element_intVector(&path, -2, getHeight(p) + 1, getWidth(p));
                        push(&s, getHeight(p) + 1, getWidth(p), getWeight(p) - 1);
                        brian--;
                    }
                }
                if(getWidth(p) != vector_intWidth(&intMaze)){
                    if(access_element_intVector(&path, getHeight(p) + 1, getWidth(p) + 1) == 0){
                        if(access_element_intVector(&search, getHeight(p) + 1, getWidth(p) + 1) == curr -1 && curr == brian && curr >= 0){
                            insert_element_intVector(&path, -2, getHeight(p) + 1, getWidth(p) + 1);
                            push(&s, getHeight(p) + 1, getWidth(p) + 1, getWeight(p) - 1);
                            brian--;
                        }
                    }
                }
                if(getWidth(p) != 0){
                    if(access_element_intVector(&path, getHeight(p) + 1, getWidth(p) - 1) == 0){
                        if(access_element_intVector(&search, getHeight(p) + 1, getWidth(p) - 1) == curr - 1 && curr == brian && curr >= 0){
                            insert_element_intVector(&path, -2, getHeight(p) + 1, getWidth(p) - 1);
                            push(&s, getHeight(p) + 1, getWidth(p) - 1, getWeight(p) - 1);
                            brian--;
                        }
                    }
                }
            }

            if(getHeight(p) != 0){
                if(getWidth(p) != vector_intWidth(&intMaze)){
                    if(access_element_intVector(&path, getHeight(p) - 1, getWidth(p) + 1) == 0){
                        if(access_element_intVector(&search, getHeight(p) - 1, getWidth(p) + 1) == curr - 1 && curr == brian && curr >= 0){
                            insert_element_intVector(&path, -2, getHeight(p) - 1, getWidth(p) + 1);
                            push(&s, getHeight(p) - 1, getWidth(p) + 1, getWeight(p) - 1);
                            brian--;
                        }
                    }
                }
                if(getWidth(p) != 0){
                    if(access_element_intVector(&path, getHeight(p) - 1, getWidth(p) - 1) == 0){
                        if(access_element_intVector(&search, getHeight(p) - 1, getWidth(p) - 1) == curr - 1 && curr == brian && curr >= 0){
                            insert_element_intVector(&path, -2, getHeight(p) - 1, getWidth(p) - 1);
                            push(&s, getHeight(p) - 1, getWidth(p) - 1, getWeight(p) - 1);
                            brian--;
                        }
                    }
                }
            }


    }
            return path;
}

IntMaze search6(IntMaze path){
    int i, j;
    for(i = 0; i <= vector_intHeight(&path); i++){
      for(j = 0; j <= vector_intWidth(&path); j++){
            if(i != vector_intHeight(&path)){
                if(access_element_intVector(&path, i, j) == -2){
                    if(access_element_intVector(&path, i + 1, j) == 0){
                        insert_element_intVector(&path, -3, i + 1, j);
                    }
                }
                if(j != vector_intWidth(&path)){
                    if(access_element_intVector(&path, i, j) == -2){
                        if(access_element_intVector(&path, i + 1, j + 1) == 0){
                            insert_element_intVector(&path, -3, i + 1, j + 1);
                        }
                    }
                }
                if(j != 0){
                    if(access_element_intVector(&path, i, j) == -2){
                        if(access_element_intVector(&path, i + 1, j - 1) == 0){
                            insert_element_intVector(&path, -3, i + 1, j - 1);
                        }
                    }
                }
            }

            if(i != 0){
                if(access_element_intVector(&path, i, j) == -2){
                    if(access_element_intVector(&path, i - 1, j) == 0){
                        insert_element_intVector(&path, -3, i - 1, j);
                    }
                }
                if(j != vector_intWidth(&path)){
                    if(access_element_intVector(&path, i, j) == -2){
                        if(access_element_intVector(&path, i - 1, j + 1) == 0){
                            insert_element_intVector(&path, -3, i - 1, j + 1);
                        }
                    }
                }
                if(j != 0){
                    if(access_element_intVector(&path, i, j) == -2){
                        if(access_element_intVector(&path, i - 1, j - 1) == 0){
                            insert_element_intVector(&path, -3, i - 1, j - 1);
                        }
                    }
                }
            }

            if(j != vector_intWidth(&path)){
                if(access_element_intVector(&path, i, j) == -2){
                    if(access_element_intVector(&path, i, j + 1) == 0){
                        insert_element_intVector(&path, -3, i, j + 1);
                    }
                }
            }

            if(j != 0){
                if(access_element_intVector(&path, i, j) == -2){
                    if(access_element_intVector(&path, i, j - 1) == 0){
                        insert_element_intVector(&path, -3, i, j - 1);
                    }
                }
            }
        }
    }
    return path;
}
