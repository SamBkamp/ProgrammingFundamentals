#include <stdio.h>

int main(int argc, char* argv[]){
  char* desiredGrade;
  float minScore;
  float currentScore;
  float percentWeight;

  printf("Enter desired Grade: ");
  scanf("%c", desiredGrade);

  printf("Enter minimum score required for the desired grade: ");
  scanf("%f", &minScore);

  
  printf("Enter current average score: ");
  scanf("%f", &currentScore);

  
  printf("Enter the final grade as a percent of course grade: ");
  scanf("%f", &percentWeight);

  float score_req = (minScore * 100 - currentScore * (100-percentWeight))/percentWeight;

  printf("You need a score of %f on the final to achieve a %s\n", score_req, desiredGrade);
  
}
