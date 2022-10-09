#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float* find(long a, long b, long c);

int main(int argc, char* argv[]){
  if(argc < 4){
    printf("input 3 numbers");
    return 0;
  }

  long a = strtol(argv[1], (char **)NULL, 10);
  long b = strtol(argv[2], (char **)NULL, 10);
  long c = strtol(argv[3], (char **)NULL, 10);

  float* results = find(a, b, c);
  printf("len: %lu\n", sizeof(results)/4);
  for (int i = 0; i < sizeof(results)/4; i++){
    printf("%f\n", results[i]);
    
  }
}


float* find(long a, long b, long c){
  float x1;
  float x2;
  int len;
  
  if(pow(b,2) > 4 * a * c){
    len = 2;
    x1 = ((b*-1) + sqrt(pow(b,2)-(4*a*c)))/(2*a);
    x2 = ((b*-1) - sqrt(pow(b,2)-(4*a*c)))/(2*a); 
  }else if(pow(b,2) == 4 * a * c){
    len = 1;
    x2 = ((b*-1) - sqrt(pow(b,2)-(4*a*c)))/(2*a); 
  }


  float* roots = (float*)malloc(sizeof(float) * len);
  roots[0] = x1;
  roots[1] = x2;
  
  return roots;
}
