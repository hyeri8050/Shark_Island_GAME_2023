//
// board.c
// Shark Island Game
//
//Created by Hyeri Park on 2023/11/21 - 2023//11/23
//
#include <stdio.h>
#include <stdlib.h>

#include "board.h"

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

//=======변수 정의==========
//static : 접근 제한 (extern으로 접근 불가, 오로지 제공 함수로만 접근 OK) 
//1. 보드 상태 저장관련 변수 정의
static int board_status[N_BOARD]; //칸의 파손 여부 관련  
//2. 코인 관련 (보드 칸에 코인이 얼마나 있는지) 
static int board_coin[N_BOARD];  
//3. 상어의 위치
static int board_sharkPosition;
 
//보드 초기화  
int board_initBoard(void)
{   
    int i;
    
    for(i=0; i<N_BOARD; i++)
    {        
             //ㅑ번째 요소 설정  
             board_status[i] = BOARDSTATUS_OK ;
             board_coin[i] = 0;
    }
    
    for(i=0; i<N_COINPOS; i++)
    {
             int flag = 0;
             while(flag == 0)
             {
                    int allocPos = rand()%N_BOARD; //0~14 random 숫자 할당  
                    if(board_coin[allocPos] == 0) //==0이면 할당 X 
                    {
                        board_coin[allocPos] = rand()%MAX_COIN+1; //1~4
                        flag = 1; //while문을 빠져나감  
                    }
             } 
    }
    return 0;  
}
//전체 보드판의 상태 출력  
void board_printBoardStatus(void)
{
     int i;
     
     printf("=============BOARD STATUS==============\n");
     //for문 : board status의 파손 여부에 따른 결과 출력 (2가지 경우)  
     for (i=0; i<N_BOARD; i++)
     {
         printf("|");
         if (board_status[i] == BOARDSTATUS_NOK)
            printf("X");
         else
            printf("O");
     }
     printf("|\n");
     printf("=======================================\n");  
    
     return;   
}
//특정 칸의 파손 여부 출력 
int board_getBoardStatus(int pos)
{
    //배열 요소 반환
    return board_status[pos];   
}
//상어의 위치 출력  
//int board_getSharkPosition(void);
//상어 전진 명령  
//int board_stepShark(void);

//동전 습득 명령  
int board_getBoardCoin(int pos)
{
    //board_coin 배열의 값을 반환하면서 배열 값을 0으로 만듦 
    //동전의 양을 알려줌과 동시에 setting을 0으로  
    int coin = board_coin[pos]; //coin이라는 변수로 정의해야 0이 return되지 X  
    board_coin[pos] = 0;
    return coin;
}


