//
// board.c
// Shark Island Game
//
//Created by Hyeri Park on 2023/11/21 - 2023//11/23
//
#include <stdio.h>
#include <stdlib.h>

#include "board.h"

//board_status macro ����
#define N_BOARD                      15
//coin macro ����
#define N_COINPOS                    12
#define MAX_COIN                     4 
//player macro ����
#define N_PLAYER                     4
#define PLAYERSTATUS_LIVE            0
#define PLAYERSTATUS_DIE             1
#define PLAYERSTATUS_END             2

//=======���� ����==========
//static : ���� ���� (extern���� ���� �Ұ�, ������ ���� �Լ��θ� ���� OK) 
//1. ���� ���� ������� ���� ����
static int board_status[N_BOARD]; //ĭ�� �ļ� ���� ����  
//2. ���� ���� (���� ĭ�� ������ �󸶳� �ִ���) 
static int board_coin[N_BOARD];  
//3. ����� ��ġ
static int board_sharkPosition;
 
//���� �ʱ�ȭ  
int board_initBoard(void)
{   
    int i;
    
    for(i=0; i<N_BOARD; i++)
    {        
             //����° ��� ����  
             board_status[i] = BOARDSTATUS_OK ;
             board_coin[i] = 0;
    }
    
    for(i=0; i<N_COINPOS; i++)
    {
             int flag = 0;
             while(flag == 0)
             {
                    int allocPos = rand()%N_BOARD; //0~14 random ���� �Ҵ�  
                    if(board_coin[allocPos] == 0) //==0�̸� �Ҵ� X 
                    {
                        board_coin[allocPos] = rand()%MAX_COIN+1; //1~4
                        flag = 1; //while���� ��������  
                    }
             } 
    }
    return 0;  
}
//��ü �������� ���� ���  
void board_printBoardStatus(void)
{
     int i;
     
     printf("=============BOARD STATUS==============\n");
     //for�� : board status�� �ļ� ���ο� ���� ��� ��� (2���� ���)  
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
//Ư�� ĭ�� �ļ� ���� ��� 
int board_getBoardStatus(int pos)
{
    //�迭 ��� ��ȯ
    return board_status[pos];   
}
//����� ��ġ ���  
//int board_getSharkPosition(void);
//��� ���� ���  
//int board_stepShark(void);

//���� ���� ���  
int board_getBoardCoin(int pos)
{
    //board_coin �迭�� ���� ��ȯ�ϸ鼭 �迭 ���� 0���� ���� 
    //������ ���� �˷��ܰ� ���ÿ� setting�� 0����  
    int coin = board_coin[pos]; //coin�̶�� ������ �����ؾ� 0�� return���� X  
    board_coin[pos] = 0;
    return coin;
}


