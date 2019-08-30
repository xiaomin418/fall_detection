#include<stdbool.h>
#include "stdint.h"
#define gyro_size 200000
#define acce_size 1960
#define big_size 32768
#define Win 300
#define  T 100
#define HALF_T 50
#define Move 10

#define GB 19990
#define GD 29900
#define GP 2
#define GP2 2

#define AD -1451
#define AD2 -1180
#define AP 2
#define AP2 2
#define Ininum 100

#define ANGD 4500
#define ANGP 2

/*up_angel*/
#define IMU_P 20
#define IMU_I 0.005
#define INTEGRAL_CONSTANT 0.01

/*三轴陀螺仪*/
extern int gx;
extern int gy;
extern int gz;
/*三轴加速度计*/
extern int ax;
extern int ay;
extern int az;
extern uint8_t g_rxBuffer0;
extern uint8_t g_rxBuffer2;
extern uint8_t g_rxBuffer4;
extern short LED_Color;
/*三轴angel,init=0*/
extern float angel[3];

/*count*/
extern int i;

extern int pg[3];
extern bool sample[4][Win];
extern int all[3];
extern int forsample;
extern int Result_all[4];
extern float q[4];//quaternion
extern float v_err_i[3];//error integral
extern int dev_gyo[3];//deviation error
extern float Ki;
extern float Kp;
extern bool ring;
extern float acc_percent;
extern float angel_percent;
extern float gyo_percent;
extern int cos_x[2];
extern int cos_y[2];
extern int cos_z[2];

/*up_angel*/
extern double q0;
extern double q1;
extern double q2;
extern double q3;
extern double wce[3];
extern double attitude[3];
extern double exInt;
extern double eyInt;
extern double ezInt;