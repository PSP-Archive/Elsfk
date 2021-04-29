#include <pspkernel.h>
#include <pspctrl.h>
#include <pspdisplay.h>

#include "datatype.h"
#include "common.h"

#define CTRL_REPEAT_TIME 0x40000

/* Exit callback */
int Exit_callback(int arg1, int arg2, void *common) 
{
	sceKernelExitGame();
	
	return 0;
}

/* Callback thread */
int CallbackThread(SceSize args, void *argp) 
{
	int cbid;
	cbid = sceKernelCreateCallback("Exit Callback", Exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);
	sceKernelSleepThreadCB();

	return 0;
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void) 
{
	int thid = 0;
	thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
	if(thid >= 0) 
	{
		sceKernelStartThread(thid, 0, 0);		
	}
	
	return thid;
}

//延时函数
void Delay_S(int time)
{
	int i, x;
	for (i=0; i<time; i++)
	{
		for (x = 0; x < 10; x++) 
		{
			sceDisplayWaitVblankStart();
		}
	}
}

//获得按键函数
unsigned int GetButton(void)
{
	SceCtrlData btn;
	static unsigned int last_btn = 0;
	static unsigned int last_tick = 0;

	sceCtrlReadBufferPositive(&btn,1);
	if (btn.Buttons == last_btn) 
	{
		if (btn.TimeStamp - last_tick < CTRL_REPEAT_TIME) return 0;
		return last_btn;
	}
	last_tick = btn.TimeStamp;
	last_btn  = btn.Buttons;
	
	return last_btn;
}

