#include <stdio.h>
#include <stdlib.h>
#include <time.h> //add time header  
#include "board.h" //add board.h -main.c에서 board.h 호출이 가능하도록 prototyping 

#define MAX_DIE          6

void opening(void)
{
  printf("=======================================\n");
  printf("***************************************\n");
  printf("           SHARK ISLAND GAME           \n");
  printf("***************************************\n");   
  printf("=======================================\n");  
}

//test for 11.21
int rolldie(void)
{
    return rand()%MAX_DIE+1; //1~6
}
int main(int argc, char *argv[])
{
  int pos = 0;
  
  srand((unsigned)time(NULL)); //random function
  
  //step 0. opening
  opening(); //opening 함수 호출  
  
  //step 1. initialize & determine players number
  board_initBoard();
  
  //step 2. An iterative sentence - repeat each player's turn  //반복문 
  do { 
       int step = rolldie();
       int coinResult; 
       char c;
       
       board_printBoardStatus();
       
       pos += step;
       
       printf("Press any key to roll a die : ");
       scanf("%d", &c);
       fflush(stdin);
       
       printf("Die result : %d, Player moved to %d!\n",step, pos); 
       coinResult = board_getBoardCoin(pos);
       
     //step 2-1.print players condition
     //step 2-2. Roll the dice
     //step 2-3. Move
     //step 2-4. Pick up coins (or coin)
     //step 2-5. Next Turn 
     //step 2-6. Shark's movement (Condition: When all players turn around)
 //if(/*조건:*/)
     //How shark moves
  } while(1);  
  //step 3. Result (Calculate a winner and print the result)  
  system("PAUSE");	
  return 0;
}
