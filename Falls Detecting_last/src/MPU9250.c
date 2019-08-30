#include "include.h"
#include "MPUIIC.h"



//���ֽ�д��*******************************************
unsigned char TX_DATA[4];     //��ʾ�ݻ�����
unsigned char BUF[10];       //�������ݻ�����				 //IIC�õ�
unsigned int A_X,A_Y,A_Z;    //X,Y,Z��
unsigned int G_X,G_Y,G_Z;    //X,Y,Z��
unsigned int M_X,M_Y,M_Z;    //X,Y,Z��

unsigned char Single_Write(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data)		     //void
{
  MPU_IIC_Start();
  //�����豸��ַ+д�ź�//MPU_IIC_Send_Byte(((REG_Address & 0x0700) >>7) | SlaveAddress & 0xFFFE);//���ø���ʼ��ַ+������ַ 
  MPU_IIC_Send_Byte(SlaveAddress);
  if(MPU_IIC_Wait_Ack())	//�ȴ�Ӧ��
  {
    MPU_IIC_Stop();		 
    return 1;		
  }
  MPU_IIC_Send_Byte(REG_Address );   //���õ���ʼ��ַ      
  MPU_IIC_Wait_Ack();	
  MPU_IIC_Send_Byte(REG_data);
  MPU_IIC_Wait_Ack();   
  MPU_IIC_Stop(); 
  return 0;
}

//���ֽڶ�ȡ*****************************************
unsigned char Single_Read(unsigned char SlaveAddress,unsigned char REG_Address)
{   
  unsigned char REG_data;     	
  MPU_IIC_Start();
  MPU_IIC_Send_Byte(SlaveAddress); //I2C_SendByte(((REG_Address & 0x0700) >>7) | REG_Address & 0xFFFE);//���ø���ʼ��ַ+������ַ 
  if(MPU_IIC_Wait_Ack())	//�ȴ�Ӧ��
  {
    MPU_IIC_Stop();		 
    return 1;		
  }
  MPU_IIC_Send_Byte((uint8_t) REG_Address);   //���õ���ʼ��ַ      
  MPU_IIC_Wait_Ack();
  MPU_IIC_Send_Byte(SlaveAddress+1);
  MPU_IIC_Wait_Ack();
  
  REG_data= MPU_IIC_Read_Byte(0);
  MPU_IIC_Stop();
  //return TRUE;
  return REG_data;
  
}	


//IIC����д
//addr:������ַ 
//reg:�Ĵ�����ַ
//len:д�볤��
//buf:������
//����ֵ:0,����
//    ����,�������
uint8_t MPU_Write_Len(uint8_t addr,uint8_t reg,uint8_t len,uint8_t *buf)
{
  uint8_t i; 
  MPU_IIC_Start(); 
  MPU_IIC_Send_Byte((addr<<1)|0);//����������ַ+д����	
  if(MPU_IIC_Wait_Ack())	//�ȴ�Ӧ��
  {
    MPU_IIC_Stop();		 
    return 1;		
  }
  MPU_IIC_Send_Byte(reg);	//д�Ĵ�����ַ
  MPU_IIC_Wait_Ack();		//�ȴ�Ӧ��
  for(i=0;i<len;i++)
  {
    MPU_IIC_Send_Byte(buf[i]);	//��������
    if(MPU_IIC_Wait_Ack())		//�ȴ�ACK
    {
      MPU_IIC_Stop();	 
      return 1;		 
    }		
  }    
  MPU_IIC_Stop();	 
  return 0;	
} 



//IIC������
//addr:������ַ
//reg:Ҫ��ȡ�ļĴ�����ַ
//len:Ҫ��ȡ�ĳ���
//buf:��ȡ�������ݴ洢��
//����ֵ:0,����
//    ����,�������
uint8_t MPU_Read_Len(uint8_t addr,uint8_t reg,uint8_t len,uint8_t *buf)
{ 
  MPU_IIC_Start(); 
  MPU_IIC_Send_Byte((addr<<1)|0);//����������ַ+д����	
  if(MPU_IIC_Wait_Ack())	//�ȴ�Ӧ��
  {
    MPU_IIC_Stop();		 
    return 1;		
  }
  MPU_IIC_Send_Byte(reg);	//д�Ĵ�����ַ
  MPU_IIC_Wait_Ack();		//�ȴ�Ӧ��
  MPU_IIC_Start();
  MPU_IIC_Send_Byte((addr<<1)|1);//����������ַ+������	
  MPU_IIC_Wait_Ack();		//�ȴ�Ӧ�� 
  while(len)
  {
    if(len==1)*buf=MPU_IIC_Read_Byte(0);//������,����nACK 
    else *buf=MPU_IIC_Read_Byte(1);		//������,����ACK  
    len--;
    buf++; 
  }    
  MPU_IIC_Stop();	//����һ��ֹͣ���� 
  return 0;	
}



//�õ����ٶ�ֵ(ԭʼֵ)
//ax,ay,az:������x,y,z���ԭʼ����(������)
//����ֵ:0,�ɹ�
//    ����,�������
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
//�õ�������ֵ(ԭʼֵ)
//gx,gy,gz:������x,y,z���ԭʼ����(������)
//����ֵ:0,�ɹ�
//    ����,�������
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
  MPU_Read_Len(MPU9250_I2C_ADDR,(WHO_AM_I),1,&value);//��ȡ����ID
   uartPrintf(UARTR2,"id=%hd\n",value);
  if(value==0x71)
  {
    MPU_Write_Len(MPU9250_I2C_ADDR,PWR_MGMT_1,1,(uint8_t *)0x80);  //��Դ����,��λMPU9250  �ڲ�20M����
    MPU_Write_Len(MPU9250_I2C_ADDR,SMPLRT_DIV,1,(uint8_t *)0x07);//�����ǲ�����1000/(1+7)=125HZ
    MPU_Write_Len(MPU9250_I2C_ADDR,CONFIG,1,(uint8_t *)0x06); //��ͨ�˲��� 0x06 5hz
    MPU_Write_Len(MPU9250_I2C_ADDR,ACCEL_CONFIG,1,(uint8_t *)0x18); //���ٶȼƲ�����Χ 0X18 ����16g
    MPU_Write_Len(MPU9250_I2C_ADDR,ACCEL_CONFIG2,1,(uint8_t *)0x00); //���ٶȲ���Ƶ��460HZ
    return 0;
  }
  return 1;
}
*/

//��ʼ��MPU9250��
void Init_MPU9250(void)
{
MPU_IIC_Init();//��ʼ��IIC����
Single_Write(GYRO_ADDRESS,PWR_MGMT_1, 0x00);	//�������״̬
Single_Write(GYRO_ADDRESS,SMPLRT_DIV, 0x02);
Single_Write(GYRO_ADDRESS,CONFIG, 0x00);//0x00);
Single_Write(GYRO_ADDRESS,GYRO_CONFIG, 0x18);   //����2000deg/s
Single_Write(GYRO_ADDRESS,ACCEL_CONFIG, 0x01);  //����2g
}

//******��ȡMPU9250����****************************************/
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
  short aacx,aacy,aacz;	//���ٶȴ�����ԭʼ����
  short gyrox,gyroy,gyroz;	//������ԭʼ����

  //Init_MPU9250();            //��ʼ��MPU6050

    MPU9250_Get_Accelerometer(&aacx,&aacy,&aacz);	//�õ����ٶȴ���������
    MPU9250_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//�õ�����������

    gx=gyrox*gyro_size/big_size;//deg/s
    gy=gyroy*gyro_size/big_size;
    gz=gyroz*gyro_size/big_size;
    ax=aacx*acce_size/big_size;//m/s
    ay=aacy*acce_size/big_size;
    az=aacz*acce_size/big_size;
}


