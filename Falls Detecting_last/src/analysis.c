#include "include.h"
#include "analysis.h"
#include<stdbool.h>
#include<math.h>
#define HU 3.14159/180
int gyo_fal[3]={1,2,3};
int n_gyo_fal[3]={1,2,3};
double gyo_fall_percent=0.6;

void up_angel(void)
{
	  //uart4_Printf("up!");
	  double q0q0,q0q1,q0q2,q1q1,q1q3,q2q2,q2q3,q3q3,q1q2,q0q3;
	  double gc[3];
	  double ac[3];
	  double norm;
	  double gbx,gby,gbz;
	  double ex,ey,ez;
	  int angelz;
	  gc[0]=(gx-dev_gyo[0])/100;
	  gc[1]=(gy-dev_gyo[1])/100;
	  gc[2]=(gz-dev_gyo[2])/100;
	  ac[0]=ax/100;
	  ac[1]=ay/100;
	  ac[2]=az/100;
	
    q0q0 = q0 * q0;
    q0q1 = q0 * q1;
    q0q2 = q0 * q2;
    q1q1 = q1 * q1;
    q1q3 = q1 * q3;
    q2q2 = q2 * q2;
    q2q3 = q2 * q3;
    q3q3 = q3 * q3;
    q1q2 = q1 * q2;
    q0q3 = q0 * q3;


    gc[0] = gc[0] / 32768 * 500;
    gc[1] = gc[1] / 32768 * 500;
    gc[2] = gc[2] / 32768 * 500;

    ac[0] = ac[0] / 32768 / 500;
    ac[1] = ac[1] / 32768 / 500;
    ac[2] = ac[2] / 32768 / 500;
    //uart4_Printf("up!");
    wce[0] = 2 * gc[0] * (0.5 - q2q2 - q3q3) + 2 * gc[1] * (q1q2 - q0q3) + 2 * gc[2] * (q1q3 + q0q2);
    wce[1] = 2 * gc[0] * (q1q2 + q0q3) + 2 * gc[1] * (0.5 - q1q1 - q3q3) + 2 * gc[2] * (q2q3 - q0q1);
    wce[2] = 2 * gc[0] * (q1q3 - q0q2) + 2 * gc[1] * (q2q3 + q0q1) + 2 * gc[2] * (0.5 - q1q1 - q2q2);

    norm=sqrt(ac[0]*ac[0]+ac[1]*ac[1]+ac[2]*ac[2]);
   if(fabs(norm)<1e-12)
        return;
	 uart4_Printf("up2!");
    ac[0]/=norm;
    ac[1]/=norm;
    ac[2]/=norm;
    gbx = 2 * (q1q3 - q0q2);
    gby = 2 * (q0q1 + q2q3);
    gbz = q0q0 - q1q1 - q2q2 + q3q3;

    ex = (ac[1] * gbz - ac[2] * gby);
    ey = (ac[2] * gbx - ac[0] * gbz);
    ez = (ac[0] * gby - ac[1] * gbx);


    exInt += ex * IMU_I * INTEGRAL_CONSTANT;
    eyInt += ey * IMU_I * INTEGRAL_CONSTANT;
    ezInt += ez * IMU_I * INTEGRAL_CONSTANT;

    gc[0] += ex * IMU_P + exInt;
    gc[1] += ey * IMU_P + eyInt;
    gc[2] += ez * IMU_P + ezInt;

    q0 = q0 + (-q1 * gc[0] - q2 * gc[1] - q3 * gc[2]) * HALF_T;
    q1 = q1 + (q0 * gc[0] + q2 * gc[2] - q3 * gc[1]) * HALF_T;
    q2 = q2 + (q0 * gc[1] - q1 * gc[2] + q3 * gc[0]) * HALF_T;
    q3 = q3 + (q0 * gc[2] + q1 * gc[1] - q2 * gc[0]) * HALF_T;

    norm = sqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
    //uart4_Printf("up!");
    if(fabs(norm)<1e-12)
        return;
		//uart4_Printf("up3!");
    q0 /= norm;
    q1 /= norm;
    q2 /= norm;
    q3 /= norm;
    attitude[0] = asin(-2 * q1 * q3 + 2 * q0 * q2) * 57.3;
    attitude[1] = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2 * q2 + 1) * 57.3;
    attitude[2] = atan2(2 * q1q2 + 2 * q0q3, -2 * q2q2 - 2 * q3q3 + 1) * 57.3;
		//int tanxx=tan(attitude[0]/57.3)*1000;
		//int tanyy=tan(attitude[1]/57.3)*1000;
		//uart4_Printf("tanxx:%d tanyy:%d\n\n",tanxx,tanyy);
		//int args=tan(attitude[0]/57.3)*tan(attitude[1]/57.3)/
		//sqrt((tan(attitude[0]/57.3))*(tan(attitude[0]/57.3))+
		//(tan(attitude[1]/57.3))*(tan(attitude[1]/57.3)))*100;
		
		angelz=atan2(sqrt((tan(attitude[0]/57.3))*(tan(attitude[0]/57.3))+
			(tan(attitude[2]/57.3))*(tan(attitude[2]/57.3))),
		tan(attitude[0]/57.3)*tan(attitude[2]/57.3)
		)*100*57.3;
		//int kaifang=10000*sqrt((tan(attitude[0]/57.3))*(tan(attitude[0]/57.3))+
			//(tan(attitude[1]/57.3))*(tan(attitude[1]/57.3)));
		//int tancheng=1000000*tan(attitude[0]/57.3)*tan(attitude[1]/57.3);
		//int tanx=100000*tan(attitude[0]/57.3);
		//int tany=100000*tan(attitude[1]/57.3);
		//int tanz=10000000*tan(attitude[2]/57.3);
		//uart4_Printf("kaifang:%d tancheng:%d\n\n",kaifang,tancheng);
		//uart4_Printf("tanx:%d tany:%d tanz:%d\n\n",tanx,tany,tanz);
		//uart4_Printf("args:%d\n\n",args);
		uart4_Printf("angelz:%d\n\n",angelz);
}

bool acc_judge(void)//judge through accelerate
{
	if(Result_all[0]<GP)//gyo hasn't change
		return false;
	int azz;
	azz=ax*cos_x[0]/cos_x[1]+ay*cos_y[1]/cos_y[1]+az*cos_z[0]/cos_z[1];
	if (azz<AD)
		return true;
	else
		return false;
}
bool acc_judge2(void)//judge through accelerate
{
	if(Result_all[2]<ANGP)//gyo hasn't change
		return false;
	int azz;
	azz=ax*cos_x[0]/cos_x[1]+ay*cos_y[1]/cos_y[1]+az*cos_z[0]/cos_z[1];
	if (azz<AD2)
		return true;
	else
		return false;
}
bool gyo_judge(void)
{
	//if()
	
	if((gx-dev_gyo[0]>GD||gy-dev_gyo[1]>GD||gz-dev_gyo[2]>GD||
		gx-dev_gyo[0]<-GD||gy-dev_gyo[1]<-GD||gz-dev_gyo[2]<-GD)
		&&(gx-dev_gyo[0]-pg[0]>GB||gy-dev_gyo[1]-pg[1]>GB||gz-dev_gyo[2]-pg[2]>GB||
	   gx-dev_gyo[0]-pg[0]<-GB||gy-dev_gyo[1]-pg[1]<-GB||gz-dev_gyo[2]-pg[2]<-GB))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool angel_judge(void)
{
	if(Result_all[0]<GP)
		return false;
	int angelz;
	angelz=atan2(sqrt((tan(attitude[0]/57.3))*(tan(attitude[0]/57.3))+
			(tan(attitude[2]/57.3))*(tan(attitude[2]/57.3))),
		tan(attitude[0]/57.3)*tan(attitude[2]/57.3)
		)*100*57.3;
	if(angelz>ANGD)
		return true;
	else
		return false;
}
bool fall_judge(void)
{
	if(Result_all[1]>GP||Result_all[3]>ANGP)
		return true;
	else
		return false; 
} 
void  update(void)//update all data
{
	  up_angel();//update angel
		//Result_all[0]=Result_all[0]+angel_judge()-sample[0][forsample];//?? 
		//sample[0][forsample]=angel_judge();
		
		Result_all[0]=Result_all[0]+gyo_judge()-sample[0][forsample];//update angel
		sample[0][forsample]=gyo_judge();
	
	  Result_all[1]=Result_all[1]+acc_judge()-sample[1][forsample];//update accelerate
		sample[1][forsample]=acc_judge();

	  Result_all[2]=Result_all[2]+angel_judge()-sample[2][forsample];//update accelerate
		sample[2][forsample]=angel_judge();
	
	  Result_all[2]=Result_all[2]+angel_judge()-sample[2][forsample];//update accelerate
		sample[2][forsample]=angel_judge();
	
	  Result_all[3]=Result_all[3]+acc_judge2()-sample[3][forsample];//update accelerate
		sample[3][forsample]=acc_judge2();
	  
    forsample=(forsample+1)%Win;
}
void init_acc_gyo(void)
{
	int k=0;
	int ini_acc[3];
	int sum_acc[6]={0,0,0,0,0,0};
	while(k<Ininum){
		if(i>k)
		{
		sum_acc[0] += ax;
		sum_acc[1] += ay;
		sum_acc[2] += az;
		sum_acc[3] += gx;
		sum_acc[4] += gy;
		sum_acc[5] += gz;
		k++;
		//uart4_Printf("i:%d\n",k);
		//uart4_Printf("ax:%d ay:%d az:%d\n",ax,ay,az);
		//uart4_Printf("gx:%d gy:%d gz:%d\n",gx,gy,gz);
		//uart4_Printf("sum0:%d sum1:%d sum2:%d\n\n",sum_acc[0],sum_acc[1],sum_acc[2]);
		//uart4_Printf("sum3:%d sum4:%d sum5:%d\n\n",sum_acc[3],sum_acc[4],sum_acc[5]);
		}
	}
	ini_acc[0]=sum_acc[0]/Ininum;
	ini_acc[1]=sum_acc[1]/Ininum;
	ini_acc[2]=sum_acc[2]/Ininum;
	dev_gyo[0]=sum_acc[3]/Ininum;
	dev_gyo[1]=sum_acc[4]/Ininum;
	dev_gyo[2]=sum_acc[5]/Ininum;
	//uart4_Printf("sum0:%d sum1:%d sum2:%d\n\n",sum_acc[0],sum_acc[1],sum_acc[2]);
	//uart4_Printf("ini_acc0:%d ini_acc1:%d ini_acc2:%d\n\n",ini_acc[0],ini_acc[1],ini_acc[2]);
	//uart4_Printf("dev0:%d dev1:%d dev2:%d\n\n",dev_gyo[0],dev_gyo[1],dev_gyo[2]);
	int sum=sqrt(ini_acc[0]*ini_acc[0]+ini_acc[1]*ini_acc[1]+ini_acc[2]*ini_acc[2]);
	//uart4_Printf("sum:%d\n\n",sum);
	cos_x[0]=ini_acc[0];
	cos_y[0]=ini_acc[1];
	cos_z[0]=ini_acc[2];
	cos_x[1]=sum;
	cos_y[1]=sum;
	cos_z[1]=sum;
}








