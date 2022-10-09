#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* search(char* input, char* dict);

int main(int argc, char* argv[]){

  FILE* dict = fopen("dictionary.txt", "rb");

  fseek(dict, 0, SEEK_END);
  long size = ftell(dict);

  rewind(dict);
  //  char buffer[siz + 1];
  char* buffer = (char*) malloc(size+1);
  fread(buffer, 1, size, dict);
  fclose(dict);

  
  //chat cycle

  char input[5];
  
  printf("> ");
  fgets(input, 5, stdin);
  input[strlen(input) - 1] = '\0'; //remove \n at the end of the input

  while(strcmp(input, "q") != 0) {
    char* cpy = strdup(buffer); //because strtok is destructive
    search(input, cpy);
    printf("> ");
    fgets(input, 5, stdin);
    input[strlen(input) - 1] = '\0';
  }

  free(buffer);
  return 1;
  
}


char* search(char* input, char* dict) {
  clock_t start, end;
  double cpu_time_used;
  start = clock();
  
  printf("words found '%s':\n", input);
  
  for (char* token = strtok(dict, "\n"); token != NULL; token = strtok(NULL, "\n")){
    if(strstr(token, input) != NULL){
      printf("%s\n", token);
    }
  }

  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("CPU Time: %f\n", cpu_time_used);
  return input;
}
