#include <stdlib.h>
#include <stdio.h>


int main(int argc, char* argv[]){

}


int* check_elbow(symbols, x, y, direction, count, last){
  if(count == 3){
    int* path = (int)malloc(6);
    return path; 
  }

  if(direction == NULL){
    for (int i = 0; i < 4; i++){            
      if(i%2 == 0){
	int* test = check_elbow(symbols, x, y + (i-1), i, count+1, symbols[y][x]);
	if(test != -1){
	  test.append([x, y]);
	  return test;
	}else {
	  int* test = check_elbow(symbols, x + (i-2), y, i, count+1, symbols[y][x]);
	  if(test != -1){
	    test.append([x, y]);
	    return test;
	  }
	}
      }
   } else {
     if symbols[y][x] != last {
	 return -1; 
       }

     if(direction % 2 == 0) {
       for (int i = 1; i < 5; i+=2){
	 int* test = check_elbow(symbols, x + (i-2), y, i, count + 1, symbols[y][x]);
	 if(test != -1){
	   test.append([x][y]);
	   return test;
	 }	 
       }
     }else {
       for (int i = 0; i < 4; i+=2){
	 int* test = check_elbow(symbols, x, y + (i-1), i, count + 1, symbols[y][x]);
	 if (test != 1){
	   test.append([x, y]);
	   return test;
	 }
       }
     }
   }
  }
}



void init(fileName, sizeOfGame){
  if(fileName == NULL){
    int time = 120;
    int score = 0;
    int* board = (int*)malloc(sizeOfGame * sizeOfGame);
    for (int i = 0; i < sizeOfGame; i++){
      int* line[sizeOfGame];
      for (int j == 0; j < sizeOfGame; j++){
	line[j] = rand() % 10
      }
      board[i] = line
    }
  }else {
    FILE* fp = fopen(fileName, "r");
    fseek(dict, 0, SEEK_END);
    long size = ftell(dict);
    
    rewind(dict);
    char* buffer = (char*) malloc(size+1);
    fread(buffer, 1, size, dict);
    fclose(dict);

    int score, time;
    int* board;
    char* token = strtok(buffer, "\n");
    score = token;
    token = strtok(NULL, "\n");
    time = token;

    for (char* boardToken = strtok(token, "_"); boardToken != NULL; boardToken = strtok(NULL, "_")){
       
    }

  }
}
