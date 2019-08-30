#include "include.h"
#include "MPUIIC.h"



//单字节写入*******************************************
unsigned char TX_DATA[4];     //显示据缓存区
unsigned char BUF[10];       //接收数据缓存区				 //IIC用到
unsigned int A_X,A_Y,A_Z;    //X,Y,Z轴
unsigned int G_X,G_Y,G_Z;    //X,Y,Z轴
unsigned int M_X,M_Y,M_Z;    //X,Y,Z轴

unsigned char Single_Write(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data)		     //void
{
  MPU_IIC_Start();
  //发送设备地址+写信号//MPU_IIC_Send_Byte(((REG_Address & 0x0700) >>7) | SlaveAddress & 0xFFFE);//设置高起始地址+器件地址 
  MPU_IIC_Send_Byte(SlaveAddress);
  if(MPU_IIC_Wait_Ack())	//等待应答
  {
    MPU_IIC_Stop();		 
    return 1;		
  }
  MPU_IIC_Send_Byte(REG_Address );   //设置低起始地址      
  MPU_IIC_Wait_Ack();	
  MPU_IIC_Send_Byte(REG_data);
  MPU_IIC_Wait_Ack();   
  MPU_IIC_Stop(); 
  return 0;
}

//单字节读取*****************************************
unsigned char Single_Read(unsigned char SlaveAddress,unsigned char REG_Address)
{   
  unsigned char REG_data;     	
  MPU_IIC_Start();
  MPU_IIC_Send_Byte(SlaveAddress); //I2C_SendByte(((REG_Address & 0x0700) >>7) | REG_Address & 0xFFFE);//设置高起始地址+器件地址 
  if(MPU_IIC_Wait_Ack())	//等待应答
  {
    MPU_IIC_Stop();		 
    return 1;		
  }
  MPU_IIC_Send_Byte((uint8_t) REG_Address);   //设置低起始地址      
  MPU_IIC_Wait_Ack();
  MPU_IIC_Send_Byte(SlaveAddress+1);
  MPU_IIC_Wait_Ack();
  
  REG_data= MPU_IIC_Read_Byte(0);
  MPU_IIC_Stop();
  //return TRUE;
  return REG_data;
  
}	


//IIC连续写
//addr:器件地址 
//reg:寄存器地址
//len:写入长度
//buf:数据区
//返回值:0,正常
//    其他,错误代码
uint8_t MPU_Write_Len(uint8_t addr,uint8_t reg,uint8_t len,uint8_t *buf)
{
  uint8_t i; 
  MPU_IIC_Start(); 
  MPU_IIC_Send_Byte((addr<<1)|0);//发送器件地址+写命令	
  if(MPU_IIC_Wait_Ack())	//等待应答
  {
    MPU_IIC_Stop();		 
    return 1;		
  }
  MPU_IIC_Send_Byte(reg);	//写寄存器地址
  MPU_IIC_Wait_Ack();		//等待应答
  for(i=0;i<len;i++)
  {
    MPU_IIC_Send_Byte(buf[i]);	//发送数据
    if(MPU_IIC_Wait_Ack())		//等待ACK
    {
      MPU_IIC_Stop();	 
      return 1;		 
    }		
  }    
  MPU_IIC_Stop();	 
  return 0;	
} 



//IIC连续读
//addr:器件地址
//reg:要读取的寄存器地址
//len:要读取的长度
//buf:读取到的数据存储区
//返回值:0,正常
//    其他,错误代码
uint8_t MPU_Read_Len(uint8_t addr,uint8_t reg,uint8_t len,uint8_t *buf)
{ 
  MPU_IIC_Start(); 
  MPU_IIC_Send_Byte((addr<<1)|0);//发送器件地址+写命令	
  if(MPU_IIC_Wait_Ack())	//等待应答
  {
    MPU_IIC_Stop();		 
    return 1;		
  }
  MPU_IIC_Send_Byte(reg);	//写寄存器地址
  MPU_IIC_Wait_Ack();		//等待应答
  MPU_IIC_Start();
  MPU_IIC_Send_Byte((addr<<1)|1);//发送器件地址+读命令	
  MPU_IIC_Wait_Ack();		//等待应答 
  while(len)
  {
    if(len==1)*buf=MPU_IIC_Read_Byte(0);//读数据,发送nACK 
    else *buf=MPU_IIC_Read_Byte(1);		//读数据,发送ACK  
    len--;
    buf++; 
  }    
  MPU_IIC_Stop();	//产生一个停止条件 
  return 0;	
}



//得到加速度值(原始值)
//ax,ay,az:陀螺仪x,y,z轴的原始读数(带符号)
//返回值:0,成功
//    其他,错误代码
uint8_t MPU9250_Get_Accelerometer(short *ax,short *ay,short *az)
{
  uint8_t buf[6],res;  
  res=MPU_Read_Len(0X68,ACCEL_XOUT_H,6,buf);
  if(res==0)
  {
    *ax=((uint16_t)buf[0]<<8)|buf[1];  
    *ay=((uint16_t)buf[2]<<8)|buf[3];  
    *az=((uint16_t)buf[4]<<8)|buf[5];
  } 	
  return res;;
}
//得到陀螺仪值(原始值)
//gx,gy,gz:陀螺仪x,y,z轴的原始读数(带符号)
//返回值:0,成功
//    其他,错误代码
uint8_t MPU9250_Get_Gyroscope(short *gx,short *gy,short *gz)
{
  uint8_t buf[6],res;  
  res=MPU_Read_Len(0X68,GYRO_XOUT_H,6,buf);
  if(res==0)
  {
    *gx=((uint16_t)buf[0]<<8)|buf[1];  
    *gy=((uint16_t)buf[2]<<8)|buf[3];  
    *gz=((uint16_t)buf[4]<<8)|buf[5];
  } 	
  return res;;
}  


/*
int MPU9250_Init(void)
{
  uint8_t value;
  MPU_Read_Len(MPU9250_I2C_ADDR,(WHO_AM_I),1,&value);//获取器件ID
   uartPrintf(UARTR2,"id=%hd\n",value);
  if(value==0x71)
  {
    MPU_Write_Len(MPU9250_I2C_ADDR,PWR_MGMT_1,1,(uint8_t *)0x80);  //电源管理,复位MPU9250  内部20M晶振
    MPU_Write_Len(MPU9250_I2C_ADDR,SMPLRT_DIV,1,(uint8_t *)0x07);//陀螺仪采样率1000/(1+7)=125HZ
    MPU_Write_Len(MPU9250_I2C_ADDR,CONFIG,1,(uint8_t *)0x06); //低通滤波器 0x06 5hz
    MPU_Write_Len(MPU9250_I2C_ADDR,ACCEL_CONFIG,1,(uint8_t *)0x18); //加速度计测量范围 0X18 正负16g
    MPU_Write_Len(MPU9250_I2C_ADDR,ACCEL_CONFIG2,1,(uint8_t *)0x00); //加速度采样频率460HZ
    return 0;
  }
  return 1;
}
*/

//初始化MPU9250，
void Init_MPU9250(void)
{
MPU_IIC_Init();//初始化IIC总线
Single_Write(GYRO_ADDRESS,PWR_MGMT_1, 0x00);	//解除休眠状态
Single_Write(GYRO_ADDRESS,SMPLRT_DIV, 0x02);
Single_Write(GYRO_ADDRESS,CONFIG, 0x00);//0x00);
Single_Write(GYRO_ADDRESS,GYRO_CONFIG, 0x18);   //量程2000deg/s
Single_Write(GYRO_ADDRESS,ACCEL_CONFIG, 0x01);  //量程2g
}

//******读取MPU9250数据****************************************/
/*short MPU9250_Get_Gyro_y()
{
  short x,y,z;
  MPU9250_Get_Gyroscope(&x,&y,&z);
  int i=0;
  for(i=QSIZE-1;i>=1;i--)
  {
    g_GyroFilteringY[i]=g_GyroFilteringY[i-1];
  }
  g_GyroFilteringY[0]=y;
  short sum=0;
  for(i=0;i<QSIZE;i++)
    sum+=g_GyroFilteringY[i];
  return sum/QSIZE;
  //return y;
}*/

short MPU9250_Get_Gyro_y()
{
  short x,y,z;
  MPU9250_Get_Gyroscope(&x,&y,&z);
  return y;
}

short MPU9250_Get_Gyro_z()
{
  short x,y,z;
  MPU9250_Get_Gyroscope(&x,&y,&z);
  return z;
}
short MPU9250_Get_Gyro_x()
{
  short x,y,z;
  MPU9250_Get_Gyroscope(&x,&y,&z);
  return x;
}
short MPU9250_Get_Acc()
{
  short x,y,z;
  MPU9250_Get_Accelerometer(&x,&y,&z);
  return x;
}


void TestMPU9250(void)
{
  short aacx,aacy,aacz;	//加速度传感器原始数据
  short gyrox,gyroy,gyroz;	//陀螺仪原始数据

  //Init_MPU9250();            //初始化MPU6050

    MPU9250_Get_Accelerometer(&aacx,&aacy,&aacz);	//得到加速度传感器数据
    MPU9250_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//得到陀螺仪数据

    gx=gyrox*gyro_size/big_size;//deg/s
    gy=gyroy*gyro_size/big_size;
    gz=gyroz*gyro_size/big_size;
    ax=aacx*acce_size/big_size;//m/s
    ay=aacy*acce_size/big_size;
    az=aacz*acce_size/big_size;
}


