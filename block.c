#include <pspdisplay.h>
#include <time.h>
#include <stdlib.h> //RAND_MAX, srand, rand��һЩ���������ڴ�
#include <stdio.h> //���������ͷ�ļ� �����������ص�ͷ�ļ�
#include <string.h>//�����ַ���������ͷ�ļ� memset

#include "block.h"

void InitGameBlock(void)
{
	int i,j;

	for (i=0;i<13;i++)
	{
		for (j=0;j<18;j++)
		{
			if (i==0 || i==12 || j==17) //����Ϸ����ϱ߿򣬲��ܳ�����Χ 1<= X <=11
			{
				GameBoard[i][j]=1;
			}
			else 
			{
				GameBoard[i][j]=0;
			}

			GameColor[i][j]=0; //��ʼ����ɫֵΪ0
		}
	}

	currentBlock.bx=6;//��ʼ������λ��
	currentBlock.by=0;
}

//����һ������ģ��
void CreateBlock(BLOCK *_block)
{
	memset(_block->c,0,16); //��ʼ��������������ȫ����0

	srand(time(0));//��ʱ�������������
	switch( (int)(rand()%7)/*���������*/ )
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
	if (dy<0) return;//������Ϸ�嶥������
	
	GameBoard[dx][dy]=1;
	GameColor[dx][dy]=blockStyle;
}

//ͨ��ģ����������
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
	if (dy<0) return;//������Ϸ�嶥������
	
	GameBoard[dx][dy]=0;
	GameColor[dx][dy]=7;//��7����ɫΪ����ɫ
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
	if (myImage[7]) //�����ͣ�ˣ�������Ϊ��ͣ����
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

