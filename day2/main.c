#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long int second_part(char * line, size_t len){
   //parse range
  long int r_start = 0;
  long int r_end = 0;
  long int answer = 0; 

  for (int i = 0; i < len; i++) {
      //parse range start edge case
      if(i == 0){
        r_start = atol(line);
      } 
      
      //parse range end
      if(line[i] == '-'){
        r_end = atol(line + i + 1);
      }
       
      if(line[i] == ','){
        //parse range start
        r_start = atol(line + i + 1);
      }
      
      if(r_start == 0 || r_end == 0){
        continue;
      }
      //process range
      //printf("processing range %li - %li\n", r_start, r_end);
      for (long int p_i = r_start; p_i <= r_end; p_i++) {
        //edge case which we want to avoid when we calculate lenght of number 
        if(p_i == 0){
          continue; 
        }
        //check the length of the num. only even lenght numbers can have repeating pattern
        //int num_len = floor(log10(abs(i))) + 1;
        int num_len = log10(p_i) + 1;
        //+1 to \0 null terminator
        int s_num_size = (num_len + 1) * sizeof(char);
        char s_num[s_num_size]; 
        sprintf(s_num, "%li", p_i);
         
        //this number is candidate for repeating pattern
        int lps[num_len];
        int lps_i = 0; 
        lps[0] = 0;
        //Using Longest Prefix Suffix (LPS) algorithm
        for (int si = 1; si < num_len; si++) {
            //if no match we need to find last zero
            while (lps_i > 0 && s_num[si] != s_num[lps_i]) {
                lps_i = lps[lps_i - 1];
            }
            if (s_num[si] == s_num[lps_i]) {
              lps_i++;
            } 
            lps[si] = lps_i; 
        } 
        if(lps[num_len - 1] == 0){
         //cannot be periodic 
          continue;
        }

        int period_len = num_len - lps[num_len - 1];
        if (period_len > 0 && num_len % period_len == 0) {
          //printf("%li was periodic: ", p_i);
          //printf("[ ");
          //for (int r = 0; r < num_len; r++) {
          //  if(r == num_len - 1){
          //    printf("%d ", lps[r]);
          //  }else{
          //    printf("%d, ", lps[r]);
          //  }
          //}
          //printf("]\n");
          answer += p_i;
        }
      } 
      r_start = 0;
      r_end = 0;
  }
  return answer;

}
long int first_part(char * line, size_t len){
   //parse range
  long int r_start = 0;
  long int r_end = 0;
  long int answer2_1 = 0; 
  for (int i = 0; i < len; i++) {
      //parse range start edge case
      if(i == 0){
        r_start = atol(line);
      } 
      
      //parse range end
      if(line[i] == '-'){
        r_end = atol(line + i + 1);
      }
       
      if(line[i] == ','){
        //parse range start
        r_start = atol(line + i + 1);
      }
      
      if(r_start == 0 || r_end == 0){
        continue;
      }
      //process range
      //printf("processing range %li - %li\n", r_start, r_end);
      for (long int p_i = r_start; p_i <= r_end; p_i++) {
        //edge case which we want to avoid when we calculate lenght of number 
        if(p_i == 0){
          continue; 
        }
        //check the length of the num. only even lenght numbers can have repeating pattern
        //int num_len = floor(log10(abs(i))) + 1;
        int num_len = log10(p_i) + 1;
        if (num_len % 2 != 0) {
          continue;
        }

        int s_num_size = (num_len + 1) * sizeof(char);
        char s_num[s_num_size]; 
        sprintf(s_num, "%li", p_i);
        //this number is candidate for repeating pattern
        int num_len_half = num_len / 2;
        int is_repeating = 1;

        for (int si = 0; si < num_len_half; si++) {
            if(s_num[si] != s_num[si + num_len_half]){
              is_repeating = 0; 
              break;
            }
        } 
        if(is_repeating == 0){
          continue;
        }
        answer2_1 += p_i;
      } 
      r_start = 0;
      r_end = 0;
  }
  return answer2_1;

}

int main(int argc, char *argv[])
{
  char* file_name;
  
  if (argc < 2) {
    printf("using test file as input...\n");
    file_name="./day2.test.txt"; 
  } else {
    file_name=argv[1];
    printf("using file: %s\n", file_name);
  }

  FILE * fp; 
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  fp = fopen(file_name, "r");
  
  if(fp == NULL){
    perror("unable to open file");
    return 1;
  }
  
  //there is only one long line in the file
  read = getline(&line, &len, fp);
  if(read == -1){
    perror("no data in input file");
    return 1;
  }
  
  long int first_part_answer=first_part(line, len); 
  printf("\nfirst_part_answer: %li\n", first_part_answer);
  
  long int second_part_answer = second_part(line, len);
  printf("\nsecond_part_answer: %li\n", second_part_answer);
  fclose(fp);
  if (line) {
    free(line);
  }
  return 0;
}
