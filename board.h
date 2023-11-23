//
// board.h
// Shark Island Game
//
//Created by Hyeri Park on 2023/11/21 - 2023//11/23
//

//==========prototyping================
//Modeling the status
#define BOARDSTATUS_OK                1 //칸 OK 
#define BOARDSTATUS_NOK               0 //칸 파손  

//보드 초기화  
int board_initBoard(void);

//전체 보드판의 상태 출력  
void board_printBoardStatus(void);

//특정 칸의 파손 여부 출력 
int board_getBoardStatus(int pos);

//상어의 위치 출력  
int board_getSharkPosition(void);

//상어 전진 명령  
int board_stepShark(void);

//동전 습득 명령  
int board_getBoardCoin(int pos);
 
