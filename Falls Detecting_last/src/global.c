#include "global.h"
#include<stdbool.h>
/*三轴陀螺仪*/
int gx=0;
int gy=0;
int gz=0;
/*三轴加速度计*/
int ax=0;
int ay=0;
int az=0;
uint8_t g_rxBuffer0;
uint8_t g_rxBuffer2;
uint8_t g_rxBuffer4;
short LED_Color=0;
/*三轴angel,init=0*/
float angel[3]={0,0,0};

/*count*/
int i=0;

/*analysis module*/
int pg[3]={0,0,0};
bool sample[4][Win]={0};
int all[3]={0,0,0};
int forsample=0;
int Result_all[4]={0,0,0,0};
float q[4]={1,0,0,0};//quaternion
float v_err_i[3]={0,0,0};//error integral
int dev_gyo[3];//deviation error
float Ki=0.001;
float Kp=0.3;
bool ring=false;//warn signal: mean falling occurred
float acc_percent=0.6;
float angel_percent=0.6;
float gyo_percent=0.6;
int cos_x[2];
int cos_y[2];
int cos_z[2];

/*up_angel*/
double q0=1.0;
double q1=0.0;
double q2=0.0;
double q3=0.0;
double wce[3]={0.0,0.0,0.0};
double attitude[3]={0.0,0.0,0.0};
double exInt=0.0;
double eyInt=0.0;
double ezInt=0.0;

