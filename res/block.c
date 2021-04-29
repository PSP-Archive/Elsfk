#include <pspdisplay.h>
#include <time.h>
#include <stdlib.h> //RAND_MAX, srand, rand等一些函数定义在此
#include <stdio.h> //随机数包含头文件 与输入输出相关的头文件
#include <string.h>//关于字符串操作的头文件 memset

#include "block.h"

int xx=6;
int yy=0;
int curBlock=10;

BLOCK Blocks[19]=
{
  /*{x1,y1,x2,y2,x3,y3,x4,y4, FK_Type, next}*/
	{ {0,-2, 0,-1, 0, 0, 1, 0} ,	0,    1},  /*        */
	{ {-1, 0, 0, 0, 1,-1, 1, 0},	0,    2},  /*   #    */
	{ {0,-2, 1,-2, 1,-1, 1, 0} ,	0,    3},  /*   #    */
	{ {-1,-1,-1, 0, 0,-1, 1,-1},	0,    0},  /*   ##   */

	{ {0,-2, 0,-1, 0, 0, 1,-2} ,	1,    5},  /*        */
	{ {-1,-1,-1, 0, 0, 0, 1, 0},	1,    6},  /*   ##   */
	{ {0, 0, 1,-2, 1,-1, 1, 0} ,	1,    7},  /*   #    */
	{ {-1,-1, 0,-1, 1,-1, 1, 0},	1,    4},  /*   #    */

	{ {-1, 0, 0,-1, 0, 0, 1, 0},	2,    9},  /*        */
	{ {-1,-1, 0,-2, 0,-1, 0, 0},	2,   10},  /*        */
	{ {-1,-1, 0,-1, 0, 0, 1,-1},	2,   11},  /*   #    */
	{ {0,-2, 0,-1, 0, 0, 1,-1} ,	2,    8},  /*  ###   */

	{ {-1, 0, 0,-1, 0, 0, 1,-1},	3,   13},  /*   ##   */
	{ {0,-2, 0,-1, 1,-1, 1, 0} ,	3,   12},  /*  ##    */

	{ {-1,-1, 0,-1, 0, 0, 1, 0},	4,   15},  /*  ##    */ 
	{ {0,-1, 0, 0, 1,-2, 1,-1} ,	4,   14},  /*   ##   */ 

	{ {0,-3, 0,-2, 0,-1, 0, 0} ,    5,   17},  /*  #     */
	{ {-1, 0, 0, 0, 1, 0, 2, 0},    5,   16},  /*  ##    */
										       /*   #    */

	{ {0,-1, 0, 0, 1,-1, 1, 0} ,	6,   18},  /*  ##    */
										       /*   ##   */
};

void InitGameBlock(void)
{
	int i,j;

	//在这里给游戏区周围加上边框，不能超出范围 1<= X <=11
	for (i=0;i<13;i++)
	{
		for (j=0;j<18;j++)
		{
			if (i==0||i==12||j==17) GameBoard[i][j]=1;
			else GameBoard[i][j]=0;

			//if (i==0||i==12||j==16) DrawOneBlock(i,j,1);
			//else GameBoard[i][j]=0;
		}
	}
	
	updateScreen();
}

int GetNextBlock(void)
{
	int i;
	
	srand( (int)time(0) );
	i=rand()%28;
	
	if (i<12) return i;
	if (i<24) return (i-12)/2+12;
	return 18;
}

void DrawOneBlock(int dx, int dy, int blockStyle)
{
	if (dy<0) return;//超出游戏板顶部返回
	
	blitAlphaImageToScreen(0 ,0 , BLOCKSIZE, BLOCKSIZE, FKImage[blockStyle], 
						   (dx)* BLOCKSIZE, (dy)* BLOCKSIZE);
}

void DrawBlock(int block_index, int dx, int dy, int blockStyle)
{
	int i;
	
	for ( i=0; i<8; (i++,i++) )
	{
		DrawOneBlock( Blocks[block_index].xy[i]+dx, Blocks[block_index].xy[i+1]+dy, blockStyle );
	}
	updateScreen();
}

bool CanMoveOne(int block_index, int dx, int dy)
{
	int i;
	
	for (i=0; i<8; i++,i++)
	{
		if ( Blocks[block_index].xy[i]+ dx<1 || Blocks[block_index].xy[i]+ dx>11 ) return false;
		if ( Blocks[block_index].xy[i+1]+ dy<0 ) continue;
		if ( GameBoard[Blocks[block_index].xy[i]+ dx][Blocks[block_index].xy[i+1]+ dy] ) return false;
	}

	return true;
}

bool CanMove(int block_index, int x, int y, int dir)
{
	bool canMove=false;

	switch(dir)
	{
		case Left:
			if ( CanMoveOne(block_index, x-1, y) ) canMove= true;
			break;

		case Right:
			if ( CanMoveOne(block_index, x+1, y) ) canMove= true;
			break;

		case Down:
			if ( CanMoveOne(block_index, x, y+1) ) canMove= true;
			break;

		default:
			break;
	}
	
	return canMove;
}

void MoveBlock(int block_index, int *x, int *y, int dir)
{
	DrawBlock(block_index, *x, *y, 7); //先擦除旧的方块

	switch(dir)
	{
		case Left:
			(*x)--;
			break;

		case Right:
			(*x)++;
			break;

		case Down:
			(*y)++;
			break;

		default:
			break;
	}
	
	DrawBlock(block_index, *x, *y, Blocks[block_index].FK_Type);//再绘制新的方块
}

bool CanRoll(int block_index, int x, int y, int *offset)
{
	int i;
	int NextBlack_index;
	static int arrOffset[5]={0,-1,1,-2,2};
	
	NextBlack_index= Blocks[block_index].next;

	for (i=0; i<5; i++)
	{
		if ( CanMoveOne(NextBlack_index, x+arrOffset[i], y) )
		{
			*offset=arrOffset[i];   
			return true;             
		}                            
	}

	return false; 
}

void RollBlock(int *block_index, int *x, int y, int offset)
{
	DrawBlock(*block_index, *x, y, 7);//先擦除旧的方块
	*block_index= Blocks[*block_index].next; //再获得旋转后的坐标值
	*x += offset;
	DrawBlock(*block_index, *x, y, Blocks[*block_index].FK_Type);//最后将方块画出来
}

bool IsRowFull(int y)
{
	int i;

	for (i=1;i<=10;i++)
	{
		if (!GameBoard[i][y]) return false;
	}
	
	return true;
}

void DeleteRow(int y)
{
	int i, j;

	for (j=y; j>=2; j--)
	{
		for (i=1;i<=10;i++)
		{
			if ( GameBoard[i][j]==GameBoard[i][j-1] ) continue;

			if (GameBoard[i][j-1]==1)
			{
				GameBoard[i][j]=1;
			}
			else
			{
				GameBoard[i][j]=0;
			}
		}
	}
}

int DeleteRows(int y)
{
	int i,rows=0;
	for (i=0;i<=3;i++) // 最多消4行
	{
		while (IsRowFull(y)) //
		{
			DeleteRow(y);
			rows++;
			i++;
		}
		y--; //检测上一行
		if (y<1) break; //超出游戏板顶部
	}
	return rows; //返回消去的行数
}

void UpdataGameBlock(void)
{
	int i,j;

	for (i=1; i<=11; i++)
	{
		for (j=0; j<=16; j++)
		{
			if ( GameBoard[i][j] )
			{
				blitAlphaImageToScreen(0 ,0 , BLOCKSIZE, BLOCKSIZE, FKImage[ GameColor[ Blocks[curBlock].xy[i]+xx ][ Blocks[curBlock].xy[i+1]+yy ] ], 
									   (i)* BLOCKSIZE, (j)* BLOCKSIZE);
			}
		}
	}
	updateScreen();
}







