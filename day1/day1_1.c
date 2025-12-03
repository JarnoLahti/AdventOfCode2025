#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
  char* file_name;
  
  if (argc < 2) {
    printf("using test file as input...\n");
    file_name="./day1_1.test.txt"; 
  } else {
    file_name=argv[1];
    printf("using file: %s\n", file_name);
  }
  FILE * fp;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  
  int zero_passes = 0;
  int zero_stops = 0;
  int curr_pos = 50;
  int min = 0;
  int max = 99;
  int max_steps = max + 1; 
  
  fp = fopen(file_name, "r");
  
  if(fp == NULL){
    perror("unable to open file");
  }
  
  int canPassZero = 0;
  while ((read = getline(&line, &len, fp)) != -1) {
    char * num_part = line + 1; 
    int num = atoi(num_part);
    //Get the overflow
    int turn_steps = (num % max_steps);
    printf("[parsed]: %d  ", num);
    int rounds = floor(num / max_steps);
    zero_passes+=rounds;
    printf("[rounds]: %d  ", rounds);

    canPassZero = curr_pos != 0;
    if(line[0] == 'R') {
        curr_pos += turn_steps;
    } else {
        curr_pos -= turn_steps; 
    }

    printf("[turn_steps %c]: %d ", line[0], turn_steps);
    printf("[curr_pos b4 norm]: %d  ", curr_pos);
    
    //check if we have rotated over the range
    if(curr_pos > max){
      curr_pos = curr_pos - max_steps;
      if (canPassZero == 1 && curr_pos != 0) {
        printf("went over 0 ");
        zero_passes++;
      }
    } else if (curr_pos < min) {
      curr_pos = max_steps - (curr_pos * -1);
      if (canPassZero == 1 && curr_pos != 0) {
        printf("went over 0");
        zero_passes++;
      }
    }
    
    if (curr_pos == 0) {
      zero_stops++; 
    }
    
    printf("[curr_pos after]: %d  ", curr_pos);
    printf("[zero_passes]: %d  ", zero_passes);
    printf("[zero_stops]: %d  ", zero_stops);
    printf("\n");
  } 
  fclose(fp);
  if(line){
    free(line);
  }
  printf("password: %d\n", zero_stops);
  printf("click password: %d", zero_passes + zero_stops);
}
