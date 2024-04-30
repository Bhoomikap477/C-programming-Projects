#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){
  int randomNo, guessedNo;
  int NoOfGuess = 0;
  srand(time(NULL));

   printf("Welcometo World of Guessing Numbers!..");

   randomNo = rand() % 100 +1;
   
  do{
    printf("Pls enter your guess ( 1- 100 )");
    scanf("%d",&guessedNo);
    NoOfGuess++;
    if(guessedNo < randomNo){
      printf("Guess larger number\n");
    }else if(guessedNo > randomNo){
      printf("Guess the smaller number");
    }else{
      printf("Congrats!...You have successfully guessed the number in %d attempts..",NoOfGuess);
    }

  }while(guessedNo != randomNo);

  printf("Thank you for playing !... Bye");
}