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
  char* token = strtok(forFirstLetters, " "); //this section just gets all the first letters for the assignment() function
  while(token != NULL){
    char stringify[2] = "\0";//generates string of len 2 of null bytes
    stringify[0] = token[0]; //makes first char the token, thus turning the character into a string so I can use it with strcat()

    strcat(firstLetter, stringify); //if you use str cat w/ a char it will seg fault, so thats why i made this stringify nonsense
    token = strtok(NULL, " ");
  }
  
  int* assignment = assignments(letters, firstLetter); //generate first assignment  
  char temp[100];
  strcpy(temp, problem); //makes new temporary string because the strtok() in check_equation() messes up the string so I recopy the the original string into temp every time 
  int test = check_equation(assignment, temp, letters); //checks if first assignment generates valid combination
  
  while(test == 0){ //if not, then;
    free(assignment); //free up memory allocated by assignments()
    int* assignment = assignments(letters, firstLetter); //generate new assignment
    strcpy(temp, problem); //recopy the problem into temp, to send to check_equation
    test = check_equation(assignment, temp, letters); //check if assignment generates valid combination
  }
  for (int i = 0; i < strlen(letters); i++){
    printf("%c : %i\n", letters[i], assignment[i]); //this part just prints the valid letter assignments
  }  
}


int* assignments(char* letters, char* firstLetter){  //this function generates number assignments for each letter
  int* assign = (int*)malloc(10); //allocates the space for the number assignments to return back  
  for (int i = 0; i <= sizeof(assign); i++){
    assign[i] = 41; //this part just writes over the allocated space with number 41 so theres no random noise in the memory that would interfere w/ the number selection process
  }  
  for (int i = 0; i<strlen(letters); i++){//iterates through the letters 
    int r = rand()%10; //generates random number
    while(check_exists(r, assign, strlen(letters)) == 1 ||(strchr(firstLetter, letters[i])!=NULL && r ==0)){ //checks if already assigned, and if number is 0 AND a first letter
      r = rand()%10; //if it is already assigned etc it regenerates 
    }
    assign[i] = r; //generates until it matches all criteria then adds it to the int array
  }
  return assign; 
}


int check_exists(int r, int* assign, size_t len){ //simple function to see if number exists in int array
  int exists = 0;
  for (int j = 0; j < len-1; j++){
      if(r == assign[j]){
	exists = 1;
      }
    }
  return exists;
}

int check_equation(int* assignment, char* problem, char* letters){ //this function checks to see if the equation is valid
    int left_total = 0;
    int right_total = 0;
    char answer[50]; 
    char* token = strtok(problem, " ");

    while(token!=NULL){ //iterates through all the words in the word sum
      int wordNumber = 0;
      char* next_token = strtok(NULL, " ");      
      
      if(next_token == NULL){ //checks to see if current token is the last one, if so then break (as this is the stuff behind the = sign)
	strcpy(answer, token); //stores it somewhere else
	break;
      }
      
      for (int i = 0; i < strlen(token); i++){ //iterates through letters in the current word
	char* e = strchr(letters, token[i]);
	int index = (int) (e-letters); //finds offset of where letter is, to use as index for the assignments 
        wordNumber = wordNumber * 10 + assignment[index]; //uses math to concatonate numbers together (times by 10 to add 0 on the end, then + the new number, eg 3 + 4 = 3 *10 -> 30 -> 30+4 -> 34, hence 3+ 4 = 34 if that makes sense)
      }
      left_total += wordNumber; //add number together to get left side total
      token = next_token;
    }
    for (int i = 0; i < strlen(answer)-1; i++){ //do the same thing as above, but with right side 
      char* e = strchr(letters, answer[i]);
      int index = (int) (e-letters);//find offset
	
      right_total = right_total * 10 + assignment[index]; //concat number
    }    
    if(left_total == right_total){ //check if the totals before the = and behind the equals is the same, if yes, number assignments are valid
      return 1;
    }else {
      return 0; //if not then rip
    }
}
