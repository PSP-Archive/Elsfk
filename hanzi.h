#ifndef _HANZI_H_
#define _HANZI_H_

#define uchar unsigned char

//���庺����ʾλ�õĺ�
#define x_16  320
#define y_16  115
#define x_24  320
#define y_24  5
#define Line_Color ( ARGB(255,0,255,0) )
//�������εĺ�
#define bLeftRect   5
#define bTopRect    10
#define bRightRect  310
#define bBottomRect 260
//�������μ���ĺ�
#define h_num_b 20
#define w_num_b 26
#define interval_b 10
//����С���εĺ�
#define sLeftRect   237
#define sTopRect    20
#define sRightRect  277
#define sBottomRect 60
//����С���μ���ĺ�
#define h_num_s 4
#define w_num_s 4
#define interval_s 10
//�������ߵĺ�
#define operate_line_x0   205
#define operate_line_y0   10
#define operate_line_x1   205
#define operate_line_y1   260

extern void Draw_One_Hz(int x,int y, int col,uchar HHzz);

extern void Draw_Hz_16(int x, int y, int col, uchar Hz[]);

extern void Draw_Hz_24(int x, int y, int col, uchar Hz[]);

extern void Write_16(void);

extern void Write_24(void);

#endif 
