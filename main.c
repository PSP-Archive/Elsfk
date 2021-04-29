#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <stdio.h> //���������ͷ�ļ� �����������ص�ͷ�ļ�
#include <psprtc.h>//pspʱ��ͷ�ļ�
#include <pspctrl.h>//���Ƽ�ͷ�ļ�

#include "datatype.h"
#include "common.h"
#include "graphics.h"
#include "hanzi.h"
#include "block.h"

//////////////////////////////////////////////////////////////////////////ȫ�ֱ���

//////////////////////////////////////////////////////////////////////////ȫ�ֱ���

PSP_MODULE_INFO("TETRIS", 0, 1, 1);//psp����
//PSP_MODULE_INFO("TETRIS", 0x1000, 1, 1);

//PSP_MAIN_THREAD_ATTR(0);//Define the main thread's attribute value (optional)

int main(int argc, char* argv[])
{
	/////////////////////////////////////////////////////////////////////////
	SetupCallbacks();
	pspDebugScreenInit();
    initGraphics();	
	/////////////////////////////////////////////////////////////////////////
	//static int upOrDownx=0, upOrDowny=0;//�����жϵ�ǰ״̬
	//int  exit_Flag_0=1; //��������ѭ���ı��
	int  exit_Flag_1=1; 
	//pspTime t;     //ʱ��ṹ��

	//int i;
	//int X_offset; //�ж��ܷ��ƶ��ı���
	//int delete_rows; //�ж����˶��ٿ췽��
	//bool isFastDown=false; //�Ƿ�����½��ı��
	//bool isPause=false; //�Ƿ���ͣ��Ϸ
	
	////////////////////////////////////////////////////////////////////////	
	/*sprintf(bk0_buffer, "res/png/bk0.png");
    myImage[0] = loadImage(bk0_buffer); 
	sprintf(bk1_buffer, "res/png/bk1.png");
    myImage[1] = loadImage(bk1_buffer); 
	sprintf(bk2_buffer, "res/png/bk2.png");
    myImage[2] = loadImage(bk2_buffer); 
	sprintf(choice_buffer, "res/png/choice.png");
    myImage[3] = loadImage(choice_buffer);*/ 

	sprintf(home_BK, "res/png/homebg.png");
	myImage[4] = loadImage(home_BK); 
	sprintf(Pause_buffer, "res/png/pause.png");
	myImage[7] = loadImage(Pause_buffer); 

	sprintf(FK0_buffer, "res/png/fangkuai0.png");
	FKImage[0] = loadImage(FK0_buffer); 
	sprintf(FK1_buffer, "res/png/fangkuai1.png");
	FKImage[1] = loadImage(FK1_buffer); 
	sprintf(FK2_buffer, "res/png/fangkuai2.png");
	FKImage[2] = loadImage(FK2_buffer); 
	sprintf(FK3_buffer, "res/png/fangkuai3.png");
	FKImage[3] = loadImage(FK3_buffer); 
	sprintf(FK4_buffer, "res/png/fangkuai4.png");
	FKImage[4] = loadImage(FK4_buffer); 
	sprintf(FK5_buffer, "res/png/fangkuai5.png");
	FKImage[5] = loadImage(FK5_buffer);
	sprintf(FK6_buffer, "res/png/fangkuai6.png");
	FKImage[6] = loadImage(FK6_buffer);
	sprintf(FK7_buffer, "res/png/fangkuai_BK.png");
	FKImage[7] = loadImage(FK7_buffer);
	/////////////////////////////////////////////////////////////////////////
	/*if (myImage[0])  
	{
		upOrDownx=0;
		upOrDowny=0;
		sceDisplayWaitVblankStart(); //�ȴ���Ļ��ֱɨ�����������ȥ������һ�½����
		blitAlphaImageToScreen(0 ,0 , SCREEN_WIDTH, SCREEN_HEIGHT, myImage[0], 0, 0);//�����ص�ͼƬ��ʾ����Ļ��
		updateScreen();//��ת��Ļ�������������޷���ʾ���µ�����
	}*/
	//////////////////////////////////////////////////////////////////////////

	/*sceRtcGetCurrentClockLocalTime(&t);	
	print("year is %d\n", t.year);
	print("month is %d\n", t.month);
	print("day is %d\n", t.day);
	print("hour is %d\n", t.hour);
	print("minutes is %d\n", t.minutes);
	print("seconds is %d\n", t.seconds);
	print("microseconds is %d\n", t.microseconds);
	print("\n");
	print("\n");
	print("currentBlock->name is %c\n", currentBlock.name);
	print("currentBlock->size is %d\n", currentBlock.size);
	print("currentBlock->FK_Type is %d\n", currentBlock.FK_Type);
	print("currentBlock->c[0][0] is %d\n", currentBlock.c[0][0]);
	print("currentBlock->c[0][1] is %d\n", currentBlock.c[0][1]);
	print("currentBlock->c[0][2] is %d\n", currentBlock.c[0][2]);
	print("currentBlock->c[0][3] is %d\n", currentBlock.c[0][3]);*/

	/*while (1 & exit_Flag_0)
	{
		if (upOrDownx==0 && upOrDowny==0)
		{
			switch(GetButton()) 
			{
				case PSP_CTRL_DOWN:
					Delay_S(1);
					if (myImage[1])  
					{
						upOrDownx=1;
						upOrDowny=0;
						sceDisplayWaitVblankStart(); //�ȴ���Ļ��ֱɨ�����������ȥ������һ�½����
						blitAlphaImageToScreen(0 ,0 , SCREEN_WIDTH, SCREEN_HEIGHT, myImage[1], 0, 0);//�����ص�ͼƬ��ʾ����Ļ��
						updateScreen();//��ת��Ļ�������������޷���ʾ���µ�����
					} 
					break;

				case PSP_CTRL_CIRCLE:
					Delay_S(1);
					upOrDownx=0;
					upOrDowny=1;
					exit_Flag_0=0;//����˴�������һ������ѭ����׼�������������ѭ��
					break;	
					
				default:
					break;
			}
		}
		if (upOrDownx==1 && upOrDowny==0)
		{
			switch(GetButton()) 
			{
				case PSP_CTRL_UP:
					Delay_S(1);
					if (myImage[0]) 
					{
						upOrDownx=0;
						upOrDowny=0;
						sceDisplayWaitVblankStart(); //�ȴ���Ļ��ֱɨ�����������ȥ������һ�½����
						blitAlphaImageToScreen(0 ,0 , SCREEN_WIDTH, SCREEN_HEIGHT, myImage[0], 0, 0);//�����ص�ͼƬ��ʾ����Ļ��
						updateScreen();//��ת��Ļ�������������޷���ʾ���µ�����
					}
					break;

				case PSP_CTRL_DOWN:
					Delay_S(1);
					if (myImage[2])
					{
						upOrDownx=2;
						upOrDowny=0;
						sceDisplayWaitVblankStart(); //�ȴ���Ļ��ֱɨ�����������ȥ������һ�½����
						blitAlphaImageToScreen(0 ,0 , SCREEN_WIDTH, SCREEN_HEIGHT, myImage[2], 0, 0);//�����ص�ͼƬ��ʾ����Ļ��
						updateScreen();//��ת��Ļ�������������޷���ʾ���µ�����
					} 
					break;

				case PSP_CTRL_CIRCLE:
					Delay_S(1);
					if (myImage[3])  
					{
						upOrDownx=1;
						upOrDowny=1;
						sceDisplayWaitVblankStart(); //�ȴ���Ļ��ֱɨ�����������ȥ������һ�½����
						blitAlphaImageToScreen(0 ,0 , SCREEN_WIDTH, SCREEN_HEIGHT, myImage[3], 0, 0);//�����ص�ͼƬ��ʾ����Ļ��
						updateScreen();//��ת��Ļ�������������޷���ʾ���µ�����
					} 
					break;
				default:
					break;
			}	
		}
		if (upOrDownx==2 && upOrDowny==0)
		{
			switch(GetButton()) 
			{
				case PSP_CTRL_UP:
					Delay_S(1);
					if (myImage[1]) 
					{
						upOrDownx=1;
						upOrDowny=0;
						sceDisplayWaitVblankStart(); //�ȴ���Ļ��ֱɨ�����������ȥ������һ�½����
						blitAlphaImageToScreen(0 ,0 , SCREEN_WIDTH, SCREEN_HEIGHT, myImage[1], 0, 0);//�����ص�ͼƬ��ʾ����Ļ��
						updateScreen();//��ת��Ļ�������������޷���ʾ���µ�����
					}
					break;

				case PSP_CTRL_CIRCLE:
					//�ͷ������Դ
					freeImage(myImage[0]);
					freeImage(myImage[1]);
					freeImage(myImage[2]);
					freeImage(myImage[3]);
					freeImage(myImage[4]);
					
					freeImage(FKImage[0]);
					freeImage(FKImage[1]);
					freeImage(FKImage[2]);
					freeImage(FKImage[3]);
					freeImage(FKImage[4]);
					freeImage(FKImage[5]);
					freeImage(FKImage[6]);
					freeImage(FKImage[7]);
					disableGraphics();//�ر�ͼ��ģʽ
					pspDebugScreenClear();//�ر�Debugģʽ
					sceKernelExitGame();//����ѭ�����˳�����
					sceKernelExitDeleteThread(0);
					break;

				default:
					break;
			}
		}
		if (upOrDownx==0 && upOrDowny==1)
		{
			switch( GetButton() ) 
			{
				case PSP_CTRL_CROSS:
					Delay_S(1);
					if (myImage[0]) 
					{
						upOrDownx=0;
						upOrDowny=0;
						sceDisplayWaitVblankStart(); //�ȴ���Ļ��ֱɨ�����������ȥ������һ�½����
						blitAlphaImageToScreen(0 ,0 , SCREEN_WIDTH, SCREEN_HEIGHT, myImage[0], 0, 0);//�����ص�ͼƬ��ʾ����Ļ��
						updateScreen();//��ת��Ļ�������������޷���ʾ���µ�����
					}
					break;
			}
		}
		if (upOrDownx==1 && upOrDowny==1)
		{
			switch( GetButton() ) 
			{
				case PSP_CTRL_CROSS:
					Delay_S(1);
					if (myImage[1]) 
					{
						upOrDownx=1;
						upOrDowny=0;
						sceDisplayWaitVblankStart(); //�ȴ���Ļ��ֱɨ�����������ȥ������һ�½����
						blitAlphaImageToScreen(0 ,0 , SCREEN_WIDTH, SCREEN_HEIGHT, myImage[1], 0, 0);//�����ص�ͼƬ��ʾ����Ļ��
						updateScreen();//��ת��Ļ�������������޷���ʾ���µ�����
					}
					break;
			}
		}
	}*/
	
	//////////////////////////////////////////////////////////////////////////
	draw_BackGround();
	
	InitGameBlock();
	CreateBlock(&currentBlock);
	DrawBlock(&currentBlock);
	UpdataGameBlock();
	//////////////////////////////////////////////////////////////////////////

	while (1 & exit_Flag_1)
	{
		/*if ( PSP_CTRL_START==GetButton() )  //start��ͣ�ͻָ���Ϸ
		{
			isPause=!isPause; 
		}*/

		/*if (isPause)
		{
			draw_Pause();

			if ( PSP_CTRL_SQUARE==GetButton() )  //������� �˳���Ϸ
			{
				exit_Flag_1=0;//����˴���������������ѭ����׼���˳����� 
			}
		}
		else*/
		{
			//draw_BackGround();


			if ( PSP_CTRL_TRIANGLE==GetButton() ) //���Ǽ���ת
			{
				RotateBlock(&currentBlock);
			}
					
			if ( PSP_CTRL_LEFT==GetButton() ) //���
			{
				MoveBlock(&currentBlock,-1,0);
			}

			if ( PSP_CTRL_RIGHT==GetButton() ) //�Ҽ�
			{
				MoveBlock(&currentBlock,1,0);
			}

			if ( PSP_CTRL_DOWN==GetButton() ) //�¼���������
			{
				//isFastDown=true;
				MoveBlock(&currentBlock,0,1);
			}

			if ( PSP_CTRL_SQUARE==GetButton() )  //������� �˳���Ϸ
			{
				exit_Flag_1=0;//����˴���������������ѭ����׼���˳����� 
			}
			
			/*if (isFastDown)
			{
				
			}
			else
			{
				
			}*/
		}

		UpdataGameBlock();
	}

	//�ͷ������Դ
	freeImage(FKImage[0]);
	freeImage(FKImage[1]);
	freeImage(FKImage[2]);
	freeImage(FKImage[3]);
	freeImage(FKImage[4]);
	freeImage(FKImage[5]);
	freeImage(FKImage[6]);
	freeImage(FKImage[7]);
	/*freeImage(myImage[0]);
	freeImage(myImage[1]);
	freeImage(myImage[2]);
	freeImage(myImage[3]);*/
	freeImage(myImage[4]);
	freeImage(myImage[7]);
	disableGraphics();    //�ر�ͼ��ģʽ
	pspDebugScreenClear();//�ر�Debugģʽ

	sceKernelExitGame();//����ѭ�����˳�����
	sceKernelExitDeleteThread(0);
	
	return 0;
}



	




