#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int increment_if_roll(const char * buff, int idx, int * rolls);

int first(FILE * fp){
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  
  //determinate file size
  fseek(fp, 0, SEEK_END);
  long file_size = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  
  char *buffer = malloc(file_size + 1);
  char *temp = malloc(file_size + 1);
  if(buffer == NULL || temp == NULL){
    free(buffer);
    free(temp);
    perror("failed to malloc buffers");
    return 0;
  }
  
  //get row and col count
  int cols = 0;
  int rows = 1;

  int cols_read_done = 0;
  fread(temp, 1, file_size, fp);
  
  int buff_len = 0;
  for (int i = 0; i < file_size; i++) {
    if(temp[i] == '\n'){
      rows++; 
      //after first row we are done with cols a.k.a char count
      cols_read_done = 1;
    }
    
    if(cols_read_done != 1){
      cols++; 
    } 
    
    if(temp[i] != '\n'){
      buffer[buff_len++] = temp[i];
    }
  }
  free(temp);
  //remember null termination! 
  buffer[buff_len] = '\0';
  
  //process
  int answer = 0;
  int rolls_around = 0;
  int last_row = cols * (rows - 1);
  for (int i = 0; i < buff_len; i++) {
    //no need to check surroundings if not a roll
    if(buffer[i] != '@'){
      continue;
    }

    //check top
    if(i >= cols){
      //we have moved past first row and can start checking the top row 
      //top left
      if(i % cols != 0){
        //increment_if_roll(buffer, i - cols - 1, &rolls_around);  
        if(increment_if_roll(buffer, i - cols - 1, &rolls_around) == 1){
         printf("top left at idx %d\n", i);
        }
      }
      //top right
      if(i % cols < cols - 1){
        //increment_if_roll(buffer, i - cols + 1, &rolls_around);  
        if(increment_if_roll(buffer, i - cols + 1, &rolls_around) == 1){
         printf("top right at idx %d\n", i);
        }
      }
      //top middle is available always after first row
      //increment_if_roll(buffer, i - cols, &rolls_around);
      if(increment_if_roll(buffer, i - cols, &rolls_around) == 1){
        printf("top at idx %d\n", i);
      }
    }
    
    //left
    if(i % cols != 0){
      //increment_if_roll(buffer, i - 1, &rolls_around);  
      if(increment_if_roll(buffer, i - 1, &rolls_around) == 1){
        printf("left at idx %d\n", i);
      }
    }
    
    //right
    if(i % cols < cols - 1){
      //increment_if_roll(buffer, i + 1, &rolls_around);  
      if(increment_if_roll(buffer, i + 1, &rolls_around) == 1){
        printf("right at idx %d\n", i);
      }
    }
    
    //bottom
    if(i < last_row){
      //bottom left
      if(i % cols != 0){
        //increment_if_roll(buffer, i + cols - 1, &rolls_around);  
        if(increment_if_roll(buffer, i + cols - 1, &rolls_around) == 1){
          printf("bottom left at idx %d\n", i);
        }
      }
      //bottom right
      if(i % cols < cols - 1){
        //increment_if_roll(buffer, i + cols + 1, &rolls_around);  
        if(increment_if_roll(buffer, i + cols + 1, &rolls_around) == 1){
          printf("bottom right at idx %d\n", i);
        }
      }
      //bottom middle is available always before last row
      if(increment_if_roll(buffer, i + cols, &rolls_around) == 1){
        printf("bottom middle at idx %d\n", i);
      }
    }
    //printf("%d rolls around idx %d\n", rolls_around, i);
    if (rolls_around < 4) {
      answer++;
    }
    rolls_around = 0;
  }
  //printf("%s\n", buffer);
  //printf("cols: %d || rows: %d\n", cols, rows);
  free(buffer); 
  return answer;
}

int increment_if_roll(const char * buff, int idx, int *rolls){
  if(buff[idx] == '@'){
    //printf("roll found from idx: %d\n", idx);
    (*rolls)++;
    return 1;
  }
  return 0;
}

int main(int argc, char *argv[])
{
  char* file_name;
  
  if (argc < 2) {
    printf("using test file as input...\n");
    file_name="./day4.test.txt"; 
  } else {
    file_name=argv[1];
    printf("using file: %s\n", file_name);
  }

  FILE * fp; 
  fp = fopen(file_name, "r");
  
  if(fp == NULL){
    perror("unable to open file");
    return 1;
  }
  
  int first_part_answer=first(fp); 
  printf("\nfirst_part_answer: %d\n", first_part_answer);
  rewind(fp);
  //unsigned long long second_part_answer = first(fp);
  //printf("\nsecond_part_answer: %llu\n", second_part_answer);
  fclose(fp);
  return 0;
}
