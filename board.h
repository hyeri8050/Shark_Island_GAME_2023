//
// board.h
// Shark Island Game
//
//Created by Hyeri Park on 2023/11/21 - 2023//11/23
//

//==========prototyping================
//Modeling the status
#define BOARDSTATUS_OK                1 //ĭ OK 
#define BOARDSTATUS_NOK               0 //ĭ �ļ�  

//���� �ʱ�ȭ  
int board_initBoard(void);

//��ü �������� ���� ���  
void board_printBoardStatus(void);

//Ư�� ĭ�� �ļ� ���� ��� 
int board_getBoardStatus(int pos);

//����� ��ġ ���  
int board_getSharkPosition(void);

//��� ���� ���  
int board_stepShark(void);

//���� ���� ���  
int board_getBoardCoin(int pos);
 
