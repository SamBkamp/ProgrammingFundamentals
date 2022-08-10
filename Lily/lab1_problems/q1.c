#include <stdio.h>
#include <math.h>

int main(int argc, char* argv[]){
  int a;
  int b;
  int c;
  
  printf("enter values of a,b and c, delimted by a space: ");
  scanf("%d %d %d", &a, &b, &c);

  //solving w quadratic equation

  //(-b +/- sqrt(b^2-4(a)(c))))/2a

  float x1 = ((b*-1) + sqrt(pow(b,2)-(4*a*c)))/(2*a);
  float x2 = ((b*-1) - sqrt(pow(b,2)-(4*a*c)))/(2*a); 
  printf("answer1: %f\nanswer2: %f\n", x1, x2);
 }
