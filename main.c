#include <stdio.h>
#include <stdlib.h>
#include <time.h> //add time header  
#include "board.h" //add board.h -main.c에서 board.h 호출이 가능하도록 prototyping 

#define MAX_DIE          6
#define MAX_CHARNAME     200
//board_status macro 정의
#define N_BOARD                      15
//coin macro 정의
#define N_COINPOS                    12
#define MAX_COIN                     4 

//player macro 정의
#define N_PLAYER                     4
#define PLAYERSTATUS_LIVE            0
#define PLAYERSTATUS_DIE             1
#define PLAYERSTATUS_END             2

//Player관련 변수 선언  
int player_position[N_PLAYER];
char player_name[N_PLAYER][MAX_CHARNAME];
int player_coin[N_PLAYER];
int player_status[N_PLAYER];
char player_statusString[3][MAX_CHARNAME] = {"LIVE", "DIE", "END"};

void opening(void)
{
  printf("=======================================\n");
  printf("***************************************\n");
  printf("           SHARK ISLAND GAME           \n");
  printf("***************************************\n");   
  printf("=======================================\n");  
}

void printPlayerPosition(int player)
{
     int i;
     
     for(i=0; i<N_BOARD; i++)
     {
              printf("|");
              if (player_position[player] == i)
                 printf("%c", player_name[player][0]);
              else
              {
                  if (board_getBoardStatus(i) == BOARDSTATUS_NOK)
                     printf("X");
                  else
                     printf(" ");
              }
     }
     printf("|\n");
}

void printPlayerStatus(void)
{
     int i;
     printf("player status ---\n");
     for (i=0; i<N_PLAYER; i++)
     {
         printf("%s : pos %i, coin %i, status %s\n", player_name[i], player_position[i], player_coin[i],
                    player_statusString[player_status[i]]);
         printPlayerPosition(i);
     }
     printf("-----------------\n");
}

void checkDie(void)
{
     int i;
     for (i=0; i<N_PLAYER; i++)
     {
         if(board_getBoardStatus(player_position[i]) == BOARDSTATUS_NOK)
         {
             player_status[i]  = PLAYERSTATUS_DIE;
             //사망 상태 출력 
             printf("Player %s die!", player_name[i]);
         }
     } 
}

int game_end(void)
{
    int i;
    int flag_end = 1;
    
    //if all the players are died
    for (i=0; i<N_PLAYER; i++)
    {
        if (player_status[i] == PLAYERSTATUS_LIVE)
        {
           flag_end = 0;
           break;
        }
    }
    
    return flag_end;
}

int getALivePlayer(void)
{
    int i;
    int cnt = 0;
    
    for (i=0; i<N_PLAYER; i++)
    {
        if (player_status[i] == PLAYERSTATUS_END)
           cnt++;
    }
    
    return cnt;
}

char* getWinner(void)
{
    int i;
    int winner = 0;
    int max_coin = -1;
    
    for (i=0; i<N_PLAYER; i++)
    {
        if (player_status[i] == PLAYERSTATUS_LIVE && player_coin[i] > max_coin)
        {
           max_coin = player_coin[i];
           winner = i;
        }
    }
    
    return player_name[winner];
}
    
      
        

int rolldie(void)
{
    return rand()%MAX_DIE+1; //1~6
}
int main(int argc, char *argv[])
{
  int i;
  int turn = 0; //반복문이 돌 때 몇 번째 플레이어가 하고 있는지를 나타냄  
  
  srand((unsigned)time(NULL)); //random function
  
  //step 0. opening
  opening(); //opening 함수 호출  
  
  //step 1-1. initialize & determine players number
  board_initBoard();
  
  //Step 1-2. Player initialization
  for(i=0; i<N_PLAYER; i++)
  {
       player_position[i] = 0;
       player_coin[i] = 0;
       player_status[i] = PLAYERSTATUS_LIVE;  
       printf("Player %i's name: ", i);
       scanf("%s", player_name[i]); //pointer이므로 넣을 필요 X 
  }
   
  //step 2. An iterative sentence - repeat each player's turn  //반복문 
  do { 
       int step = rolldie();
       int coinResult; 
       char c;
       int pos = player_position[turn];
       
       if(player_status[turn] != PLAYERSTATUS_LIVE)
       {
           turn = (turn+1)%N_PLAYER;
           continue; 
       }
       
       //step 2-1.print players & board condition
       board_printBoardStatus();
       
       for(i=0; i<N_PLAYER; i++)
                printPlayerPosition(i);  
       printPlayerStatus();
       
       
       //step 2-2. Roll the dice
       printf("%s turn!! ", player_name[turn]);
       printf("Press any key to roll a die : \n");
       scanf("%d", &c);
       fflush(stdin); 
       step = rolldie();
       
     
       //step 2-3. Move
       player_position[turn] += step;
       if(player_position[turn] >= N_BOARD)
       {
          player_position[turn] = N_BOARD-1;
       }
       
       if(player_position[turn] == N_BOARD-1)
       {
          player_status[turn] = PLAYERSTATUS_END;
          printf("Player %s reached to the end!! (coin : %d)\n", player_name[turn], player_coin[turn]);
       }
       printf("Die result : %d, Player moved to %d!\n",step, player_position[turn]); 

       //step 2-4. Pick up coins (or coin)
       coinResult = board_getBoardCoin(player_position[turn]);
       
       if (coinResult > 0)
       {        
          player_coin[turn] += coinResult;
          printf("-> Lucky! %s got %i coins :) \n", player_name[turn], coinResult); 
       }
       else
           printf("-> No coins at this location!\n");
           
       //step 2-5. Next Turn 
       turn = (turn + 1)%N_PLAYER; //N_PLAYER만큼만 반복하기 위해(wrap around) 
     
       //step 2-6. Shark's movement (Condition: When all players turn around)
       if (turn == 0)
       {
          //상어 동작
          int shark_pos = board_stepShark();
          printf("Shark moved to %i\n", shark_pos);
          //check die
          checkDie(); 
       }

  } while(!game_end());  
  
  //step 3. Result (Calculate a winner and print the result)  
  int alivePlayers = getALivePlayer();
  char *winner = getWinner();
  
  printf("Game Over!!\n");
  printf("%d players are alive!\n", alivePlayers);
  printf("Winner is player %s\n", winner);
  
  system("PAUSE");	
  return 0;
}
