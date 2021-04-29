#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "datatype.h"//文件中包含了bool，所以加此头文件
#include "graphics.h"

#define BLOCKSIZE   16	//方块大小

#define Left   0
#define Right  1
#define Down   2
#define Up     3

typedef struct           
{
	int c[4][4];    
    int bx;               
    int by; 
	int FK_Type;
	int size;
}BLOCK;

BLOCK currentBlock;

int GameBoard[13][18];
int GameColor[13][18];

//图片缓存
char FK0_buffer[256];
char FK1_buffer[256];
char FK3_buffer[256];
char FK2_buffer[256];
char FK4_buffer[256];
char FK5_buffer[256];
char FK6_buffer[256];
char FK7_buffer[256];

Image *FKImage[8]; //用于每个小方块的缓存

/*char bk0_buffer[256];//图片缓存
char bk1_buffer[256];
char bk2_buffer[256];*/
char home_BK[256];
char Pause_buffer[256];
//char choice_buffer[256];

Image *myImage[8]; //用于背景图片的缓存

//////////////////////////////////////////////////////////////////////////以下函数对外公开

extern void InitGameBlock(void);

extern void CreateBlock(BLOCK *_block);

extern void DrawBlock(BLOCK *_block);

extern void EraseBlock(BLOCK *_block);

extern void RotateBlock(BLOCK *_block);

extern bool MoveBlock(BLOCK *_block, int dx, int dy);

extern void draw_BackGround(void); 

extern void draw_Pause(void);

extern void UpdataGameBlock(void);

//////////////////////////////////////////////////////////////////////////以下函数不对外公开,内部使用

void DrawOneBlock(int dx, int dy, int blockStyle);

void EraseOneBlock(int dx, int dy);

bool CanMove(BLOCK *_block, int dx, int dy);

#endif

