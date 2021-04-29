#ifndef _COMMOM_H_
#define _COMMOM_H_

extern int Exit_callback(int arg1, int arg2, void *common);

extern int CallbackThread(SceSize args, void *argp);

extern int SetupCallbacks(void);

extern void Delay_S(int time);

extern unsigned int GetButton(void);

#endif
