#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

int* assignments(char* letters, char* firstLetter);
int check_equation(int* assignment, char* problem, char* letters);
int check_exists(int r, int* assign, size_t len);

int main(int argc, char* argv[]){
  int i = 0;
  int j = 0;
  char problem[100];
  char words[100];
  char firstLetter[100];
  char letters[100];

  srand(time(NULL));

  printf("input the word sum: ");
  fgets(problem, sizeof(problem), stdin);
  
  while(i<strlen(problem)-1) { //-1 is to remove \n
    if(problem[i] != 32){ //32 is the decimal version of the 'space' char
      words[j] = problem[i];
      j++;
    }
    i++;
  }

  for (int i = 0; i<strlen(words); i++){ //this section creates array of all letters, no duplicates
    
    if(strchr(letters, (int)words[i]) == NULL){ //checks if letter already in var letters, if not, add letter
      char stringify[2] = "\0"; //creates {\0, \0} buffer


      stringify[0] = words[i]; //makes first char of stringify the char, so char becomes null terminated string to be used with strcat
      strcat(letters, stringify); //append letter to letters variable
    }
  }


  char forFirstLetters[100]; //the worst solution to this lol
  strcpy(forFirstLetters, problem); //need to run strtok on this string again later so..
  
  char* token = strtok(forFirstLetters, " ");

  while(token != NULL){
    char stringify[2] = "\0";
    stringify[0] = token[0];

    strcat(firstLetter, stringify);
    token = strtok(NULL, " ");
  }

  printf("total letters: %s\n", letters);


  int* assignment = assignments(letters, firstLetter);
  
  char temp[100];
  strcpy(temp, problem);
  int test = check_equation(assignment, temp, letters);
  int funk = 0;
  
  while(test == 0){
    free(assignment);
    int* assignment = assignments(letters, firstLetter);
    strcpy(temp, problem);
    test = check_equation(assignment, temp, letters);
    funk++;
  }

  for (int i = 0; i < strlen(letters); i++){
    printf("%c : %i\n", letters[i], assignment[i]);
  }
  
}


int* assignments(char* letters, char* firstLetter){

  //static int assign[10] = {[0 ... 9] = 40}; //stores number assignments, initis all values to 40 to avoid random memory noise to interfere with the number selection process, only works with GNU I think, if not on gnu use this instead:
  //static int assign[10] = {40,40,40,40,40,40,40,40,40,40};
  int* assign = (int*)malloc(10);
  for (int i = 0; i <= sizeof(assign); i++){
    assign[i] = 41;
  }

  int hardCode[8] = {9, 5, 6, 7, 1, 0, 8, 2};
  
  for (int i = 0; i<strlen(letters); i++){
    //printf("letter working on: %c\n", letters[i]);
    //    printf("assign current is: ");
    //for (int j = 0; j < strlen(letters); j++){
    //printf("%i", assign[j]);
    //}
    //printf("\n");
    
    int r = rand()%10;
    while(check_exists(r, assign, strlen(letters)) == 1 ||(strchr(firstLetter, letters[i])!=NULL && r ==0)){
      //printf("Stuck at: %c, trying: %d\n", letters[i], r);
      r = rand()%10;
    }

    assign[i] = r;
    //assign[i] = hardCode[i];
  }

  return assign;
}

int check_FirstLetter(char* firstLetters, char letter){
  for (int i = 0; i < strlen(firstLetters); i++){
    if(letter == firstLetters[i]){
      return 1;
    }
  }
  return 0;
}

int check_exists(int r, int* assign, size_t len){
  int exists = 0;
  
  for (int j = 0; j < len-1; j++){
      if(r == assign[j]){
	exists = 1;
      }
    }
  return exists;
}

int check_equation(int* assignment, char* problem, char* letters){
    int left_total = 0;
    int right_total = 0;
    char answer[50];

    //printf("assign: ");
    //for (int i = 0; i < strlen(letters); i++){
    //printf("%i", assignment[i]);	
    //}
    //printf("\n");
    
    char* token = strtok(problem, " ");

    while(token!=NULL){
      int wordNumber = 0;
      char* next_token = strtok(NULL, " ");      
      
      if(next_token == NULL){
	strcpy(answer, token);
	break;
      }
      
      for (int i = 0; i < strlen(token); i++){
	char* e = strchr(letters, token[i]);
	int index = (int) (e-letters);
	
        wordNumber = wordNumber * 10 + assignment[index];
      }
      //printf("wordNumber = %i\n", wordNumber);
      left_total += wordNumber;
      token = next_token;
    }

    //right side (last word)of equation
    for (int i = 0; i < strlen(answer)-1; i++){
      char* e = strchr(letters, answer[i]);
      int index = (int) (e-letters);
	
      right_total = right_total * 10 + assignment[index];
    }
    
    //printf("leftTotal = %i\n", left_total);
    //printf("rightTotal = %i\n", right_total);

    if(left_total == right_total){
      return 1;
    }else {
      return 0; 
    }
}
