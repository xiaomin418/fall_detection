
#include "include.h"
//#include "fun.h"
/*
GPIO_MemMapPtr p3 = GET_PORT(PTE3);
uint32_t pin_index3 = GET_PIN_INDEX(PTE3);

GPIO_MemMapPtr p4 = GET_PORT(PTE4);
uint32_t pin_index4 = GET_PIN_INDEX(PTE4);
#define MPU_SDA_IN()  gpio_set_mode(PTE3,Input,1)
#define MPU_SDA_OUT() gpio_set_mode(PTE3,Output,1)

#define PTE4_OUT(value)     p4->PDOR = (p4->PDIR & ~(1u << pin_index4)) | (((unsigned int)!!value) << pin_index4);
#define PTE3_OUT(value)     p3->PDOR = (p3->PDIR & ~(1u << pin_index3)) | (((unsigned int)!!value) << pin_index3);
#define PTE3_IN(value)     PTE_BASE_PTR->PDIR.PDIR3

#define MPU_IIC_SCL(value)        PTE4_OUT 		//SCL
#define MPU_IIC_SDA_OUT(value)    PTE3_OUT		//SDA	 
#define MPU_IIC_SDA_IN     PTE3_IN		//SDA*/
#define MPU_SDA_IN()  gpio_set_mode(PTB3,Input,HIGH)
#define MPU_SDA_OUT() gpio_set_mode(PTB3,Output,HIGH)

#define PTB2_OUT    GPIOB->PDORs.PDOR2 		//SCL
#define PTB3_OUT    GPIOB->PDORs.PDOR3		//SDA	 
#define PTB3_IN     GPIOB->PDIRs.PDIR3		//SDA

#define MPU_IIC_SCL        PTB2_OUT 		//SCL
#define MPU_IIC_SDA_OUT    PTB3_OUT		//SDA	 
#define MPU_IIC_SDA_IN     PTB3_IN		//SDA

void MPU_IIC_Delay(void)
{
  delay_us(2);
}


void MPU_IIC_Init(void)
{					     
  gpio_set_mode(PTB3,Input,1);
  gpio_set_mode(PTB2,Output,1);
  gpio_set(PTB2,HIGH);//PTB2����
}

//����IIC��ʼ�ź�
void MPU_IIC_Start(void)
{
  MPU_SDA_OUT();     //sda�����
  MPU_IIC_SDA_OUT=1;	  	  
  MPU_IIC_SCL=1;
  MPU_IIC_Delay();
  MPU_IIC_SDA_OUT=0;//START:when CLK is high,DATA change form high to low 
  MPU_IIC_Delay();
  MPU_IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void MPU_IIC_Stop(void)
{
  MPU_SDA_OUT();//sda�����
  MPU_IIC_SCL=0;
  MPU_IIC_SDA_OUT=0;//STOP:when CLK is high DATA change form low to high
  MPU_IIC_Delay();
  MPU_IIC_SCL=1; 
  MPU_IIC_SDA_OUT=1;//����I2C���߽����ź�
  MPU_IIC_Delay();							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
uint8_t MPU_IIC_Wait_Ack(void)
{
  uint8_t ucErrTime=0;
  MPU_SDA_IN();      //SDA����Ϊ����  
  MPU_IIC_Delay();	   
  MPU_IIC_SCL=1;
  MPU_IIC_Delay();	 
  while(MPU_IIC_SDA_IN)
  {
    ucErrTime++;
    if(ucErrTime>250)
    {
      MPU_IIC_Stop();
      return 1;//û��Ӧ���ź�
    }
  }
  MPU_IIC_SCL=0;//ʱ�����0 	   
  return 0;  
} 
//����ACKӦ��
void MPU_IIC_Ack(void)
{
  MPU_IIC_SCL=0;
  MPU_SDA_OUT();
  MPU_IIC_SDA_OUT=0;
  MPU_IIC_Delay();
  MPU_IIC_SCL=1;
  MPU_IIC_Delay();
  MPU_IIC_SCL=0;
}
//������ACKӦ��		    
void MPU_IIC_NAck(void)
{
  MPU_IIC_SCL=0;
  MPU_SDA_OUT();
  MPU_IIC_SDA_OUT=1;
  MPU_IIC_Delay();
  MPU_IIC_SCL=1;
  MPU_IIC_Delay();
  MPU_IIC_SCL=0;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void MPU_IIC_Send_Byte(uint8_t txd)
{                        
  uint8_t t;   
  MPU_SDA_OUT(); 	    
  MPU_IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
  for(t=0;t<8;t++)
  {              
    MPU_IIC_SDA_OUT=(txd&0x80)>>7;
    txd<<=1; 	  
    MPU_IIC_SCL=1;
    MPU_IIC_Delay(); 
    MPU_IIC_SCL=0;	
    MPU_IIC_Delay();
  }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
uint8_t MPU_IIC_Read_Byte(unsigned char ack)
{
  unsigned char i,receive=0;
  MPU_SDA_IN();//SDA����Ϊ����
  for(i=0;i<8;i++ )
  {
    MPU_IIC_SCL=0; 
    MPU_IIC_Delay();
    MPU_IIC_SCL=1;
    receive<<=1;
    if(MPU_IIC_SDA_IN)receive++;   
    MPU_IIC_Delay(); 
  }					 
  if (!ack)
    MPU_IIC_NAck();//����nACK
  else
    MPU_IIC_Ack(); //����ACK   
  return receive;
}
