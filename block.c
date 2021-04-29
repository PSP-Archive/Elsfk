#include <pspdisplay.h>
#include <time.h>
#include <stdlib.h> //RAND_MAX, srand, rand等一些函数定义在此
#include <stdio.h> //随机数包含头文件 与输入输出相关的头文件
#include <string.h>//关于字符串操作的头文件 memset

#include "block.h"

void InitGameBlock(void)
{
	int i,j;

	for (i=0;i<13;i++)
	{
		for (j=0;j<18;j++)
		{
			if (i==0 || i==12 || j==17) //给游戏板加上边框，不能超出范围 1<= X <=11
			{
				GameBoard[i][j]=1;
			}
			else 
			{
				GameBoard[i][j]=0;
			}

			GameColor[i][j]=0; //初始化颜色值为0
		}
	}

	currentBlock.bx=6;//初始化方块位置
	currentBlock.by=0;
}

//创建一个方块模板
void CreateBlock(BLOCK *_block)
{
	memset(_block->c,0,16); //初始化，将方块数组全部清0

	srand(time(0));//用时间来设随机种子
	switch( (int)(rand()%7)/*产生随机数*/ )
	{
		case 0:
			_block->size=2;    _block->FK_Type=0;
			_block->c[0][0]=1; _block->c[0][1]=1;
			_block->c[1][0]=1; _block->c[1][1]=1;
			break;
		case 1:
			_block->size=3;    _block->FK_Type=1;
			_block->c[1][0]=1; _block->c[1][1]=1;
			_block->c[1][2]=1; _block->c[2][1]=1;
			break;
		case 2:
			_block->size=3;    _block->FK_Type=2;
			_block->c[1][0]=1; _block->c[1][1]=1;
			_block->c[1][2]=1; _block->c[2][2]=1;
			break;
		case 3:
			_block->size=3;    _block->FK_Type=3;
			_block->c[0][2]=1; _block->c[1][0]=1;
			_block->c[1][1]=1; _block->c[1][2]=1;
			break;
		case 4:
			_block->size=3;    _block->FK_Type=4;
			_block->c[0][0]=1; _block->c[1][0]=1;
			_block->c[1][1]=1; _block->c[2][1]=1;
			break;
		case 5:
			_block->size=3;	   _block->FK_Type=5;
			_block->c[0][1]=1; _block->c[1][0]=1;
			_block->c[1][1]=1; _block->c[2][0]=1;
			break;
		case 6:
			_block->size=4;    _block->FK_Type=6;
			_block->c[1][0]=1; _block->c[1][1]=1;
			_block->c[1][2]=1; _block->c[1][3]=1;
		default: 
			break; 
	}
}

void DrawOneBlock(int dx, int dy, int blockStyle)
{
	if (dy<0) return;//超出游戏板顶部返回
	
	GameBoard[dx][dy]=1;
	GameColor[dx][dy]=blockStyle;
}

//通过模板来画方块
void DrawBlock(BLOCK *_block)
{
	int i, j;

	for(i=0; i<_block->size; i++)
	{
		for(j=0; j<_block->size; j++)
		{
			if(_block->c[i][j]==1)
			{
				DrawOneBlock(_block->bx +i, _block->by +j, _block->FK_Type);
			}
		}
	}
}

void EraseOneBlock(int dx, int dy)
{
	if (dy<0) return;//超出游戏板顶部返回
	
	GameBoard[dx][dy]=0;
	GameColor[dx][dy]=7;//第7种颜色为背景色
}

void EraseBlock(BLOCK *_block)
{
	int i, j;

	for(i=0; i<_block->size; i++)
	{
		for(j=0; j<_block->size; j++)
		{
			if(_block->c[i][j]==1)
			{
				EraseOneBlock(_block->bx +i, _block->by +j);
			}
		}
	}
}

void RotateBlock(BLOCK *_block)
{
	int temp;

	EraseBlock(_block);

	switch(_block->size)
	{
		case 3:
			temp=_block->c[0][0]; _block->c[0][0]=_block->c[0][2]; _block->c[0][2]=_block->c[2][2]; _block->c[2][2]=_block->c[2][0]; _block->c[2][0]=temp;
			temp=_block->c[0][1]; _block->c[0][1]=_block->c[1][2]; _block->c[1][2]=_block->c[2][1]; _block->c[2][1]=_block->c[1][0]; _block->c[1][0]=temp;
			break;

		case 4:
			_block->c[0][1]=1-_block->c[0][1]; _block->c[2][1]=1-_block->c[2][1]; _block->c[3][1]=1-_block->c[3][1];
			_block->c[1][0]=1-_block->c[1][0]; _block->c[1][2]=1-_block->c[1][2]; _block->c[1][3]=1-_block->c[1][3];
			break;
			
		default: 
			break;
	}

	DrawBlock(_block);
}

bool CanMove(BLOCK *_block, int dx, int dy)
{
	int i,j;
	
    for(i=0; i<_block->size; i++)
    {
        for(j=0; j<_block->size; j++)
        {
            if(_block->c[i][j])
            {
                if( currentBlock.bx+ i+ dx >2 || currentBlock.bx+ i+ dx <9 )     
				{
					return true;
				}

				if (currentBlock.by+ i+ dy<0) continue;

                if( !GameBoard[currentBlock.bx+ i+ dx][currentBlock.by+ j+ dy] )   
				{
					return true;
				}
            }
        }
    }

    return false;
}

bool MoveBlock(BLOCK *_block, int dx, int dy)
{
	bool isMove;

	isMove=CanMove(_block, dx, dy);
	
    if(isMove)
    {
		EraseBlock(_block);

		currentBlock.bx+=dx;
		currentBlock.by+=dy;

		DrawBlock(_block);
    }
	else
	{
		GameBoard[8][8]=1;
		GameColor[8][8]=1;
	}

	return isMove;
}

void draw_BackGround(void)
{
	if (myImage[4])
	{
		sceDisplayWaitVblankStart(); 
		blitAlphaImageToScreen(0 ,0 , SCREEN_WIDTH, SCREEN_HEIGHT, myImage[4], 0, 0);//homebg.png
	} 
}

void draw_Pause(void)
{
	if (myImage[7]) //如果暂停了，背景变为暂停画面
	{
		sceDisplayWaitVblankStart(); 
		blitAlphaImageToScreen(0 ,0 , SCREEN_WIDTH, SCREEN_HEIGHT, myImage[7], 0, 0);//pause.png
		updateScreen();
	} 
}

void UpdataGameBlock(void)
{
	int i,j;

	draw_BackGround();

	for (i=0; i<13; i++)
	{
		for (j=0; j<17; j++)
		{
			if ( GameBoard[i][j] )
			{
				blitAlphaImageToScreen(0 ,0 , BLOCKSIZE, BLOCKSIZE, FKImage[ GameColor[i][j] ], 
									   (i)* BLOCKSIZE, (j)* BLOCKSIZE);
			}
		}
	}
	updateScreen();
}

