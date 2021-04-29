#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "datatype.h"//�ļ��а�����bool�����ԼӴ�ͷ�ļ�
#include "graphics.h"

#define BLOCKSIZE   16	//�����С

#define Left   0
#define Right  1
#define Down   2
#define Up     3

typedef struct
{
	int xy[8];
	int FK_Type;
	int next;
}BLOCK;

extern int xx;
extern int yy;
extern int curBlock;

extern BLOCK Blocks[19];

unsigned int GameBoard[13][18];

unsigned int GameColor[13][18];

//ͼƬ����
char FK0_buffer[256];
char FK1_buffer[256];
char FK3_buffer[256];
char FK2_buffer[256];
char FK4_buffer[256];
char FK5_buffer[256];
char FK6_buffer[256];
char FK7_buffer[256];
Image *FKImage[8]; //����ÿ��С����Ļ���

//////////////////////////////////////////////////////////////////////////���º������⹫��
extern void InitGameBlock(void);

extern int GetNextBlock(void);

/* block_index- ����������0~19
 * dx- ����X����
 * dy- ����Y����
 * BlockStyle- ������0~7�����з��7Ϊ��ɫ���������������õ�
 */
extern void DrawBlock(int block_index, int dx, int dy, int blockStyle);

extern bool CanMove(int block_index, int x, int y, int dir);

extern void MoveBlock(int block_index, int *x, int *y, int dir);

extern bool CanRoll(int block_index, int x, int y, int *offset);

extern void RollBlock(int *block_index, int *x, int y, int offset);

extern int DeleteRows(int y);

//extern void UpdataGameBlock(void);

//////////////////////////////////////////////////////////////////////////���º��������⹫��,�ڲ�ʹ��

extern void DrawOneBlock(int dx, int dy, int blockStyle);

bool CanMoveOne(int block_index, int x, int y);

bool IsRowFull(int y);

void DeleteRow(int y);

#endif
