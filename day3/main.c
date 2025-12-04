#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long long battery_switcher(FILE * fp, int batt_count){
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  unsigned long long answer = 0; 
  
  while ((read = getline(&line, &len, fp)) != -1) {

    int s_len = 0;
    if (line[read - 1] == '\n') {
      s_len = read - 1;  
    }else{
      s_len = read;
    }
    int idx_list[batt_count];
    for (int x = 0; x < batt_count; x++) {
      idx_list[x] = -1;
    }
    char row_answer[batt_count + 1];
    int curr_j = 0;

    for (int i = 0; i < s_len; i++) {
      //all found
      if(curr_j == batt_count){
        break;
      }
      //first occurence
      if(idx_list[curr_j] == -1){
        idx_list[curr_j] = i;
      }
  
      //shortcut 1
      if (line[i] - '0' == 9) {
        idx_list[curr_j] = i;
        curr_j++; 
        continue;
      }

      if(line[idx_list[curr_j]] - '0' < line[i] - '0'){
        idx_list[curr_j] = i;
      }

      //if there are not enough numbers left to fill the 12 num req
      //we need to take the shortcut and pick the current largest at this point
      //and move on with the next number
      if (i + (batt_count - curr_j) == s_len) {
        //printf("curr_j: %d  i + (bit_len - curr_j): %d\n", curr_j, (bit_len - curr_j));
        i = idx_list[curr_j];
        curr_j++;
      }
    }
    //printf("[ ");
    for (int a = 0; a < batt_count; a++) {
      row_answer[a] = line[idx_list[a]];
      //printf("%d, ",idx_list[a]);
    }
    //printf(" ]\n");
    row_answer[batt_count] = '\0';
    //printf("row_answer: %s\n", row_answer);
    answer += strtoull(row_answer, NULL, 10);
  }
  if(line){
    free(line);
  }
  return answer;
}

int main(int argc, char *argv[])
{
  char* file_name;
  
  if (argc < 2) {
    printf("using test file as input...\n");
    file_name="./day3.test.txt"; 
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
  
  unsigned long long first_part_answer=battery_switcher(fp, 2); 
  printf("\nfirst_part_answer: %llu\n", first_part_answer);
  rewind(fp);
  unsigned long long second_part_answer = battery_switcher(fp, 12);
  printf("\nsecond_part_answer: %llu\n", second_part_answer);
  fclose(fp);
  return 0;
}
