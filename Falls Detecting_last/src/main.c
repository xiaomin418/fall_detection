#include "include.h"
#include "analysis.h"
#define PIT_DETECING_HANDLER PIT0_IRQHandler


int count=0;
int cr=0;
int zhu=0;
int flag=1;
int main(void){
		
		int color_control=0;
		int k=0;
		BOARD_InitPins();
    BOARD_BootClockRUN();
		init_LED();
		pit_init(T);
		Init_MPU9250();
		uart2_init();
		uart4_init();
		uart0_init();
	 init_acc_gyo();
	init_gpio_irq3();
	init_gpio_irq2();
	i=0;
	while(1){
		if(i>k){
			zhu++;
			k=i;
		
			update();//data update
			
			if((count++)%5==0)
			{
				if(fall_judge())
					ring=true;
				else
					ring=false;
			}
			//uart2_Printf("i:%d\n",i);
      //if(ring)
			// uart2_Printf("%d %d re:%d\n\n",gx,pg[0],Result_all[1]);
			//else
				//uart4_Printf("False cr:%d %d %d %d re:%d\n\n",cr,forsample,count,zhu,Result_all[1]);
			if(i%100==0)
				uart4_Printf("False cr:%d %d %d %d re:%d\n\n",cr,forsample,count,zhu,Result_all[1]);
			//end analysis
			pg[0]=gx;
			pg[1]=gy;
			pg[2]=gz;
			//LED_Color=(LED_Color+1)%8;
			if(ring==true&&flag==1){
				gpio_set(PTC4, 1);
				uart2_Printf("老人摔倒了！");
				flag=700;
		}
			else if(ring==false&&flag<200){
				gpio_set(PTC4, 0);
			}
			if(flag>1)
				flag--;
			if(LED_Color==1&&color_control==0){
				uart2_Printf("老人摔倒了！");
				color_control=100;
			}
			else if(LED_Color==7&&color_control==0){
				uart2_Printf("老人没有摔倒，请放心！");
				color_control=100;
			}
			if(color_control>0){
				color_control--;
				if(color_control==0)
					LED_Color=0;
			}
			//if (g_ButtonPress)
        //{
           // g_ButtonPress = false;
					//LED_Color=(LED_Color+1)%8;
        //}
		//delay_ms();
		}
		//i++;
		
	}
}



void PIT_DETECING_HANDLER(void)
{
    /* Clear interrupt flag.*/
    PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, kPIT_TimerFlag);
    //LED_Color=(LED_Color+1)%8;
		TestMPU9250();
		//uart4_Printf("hhh%c\n",g_rxBuffer);
		//LED_Color=0;
		//if(ax>0)
			//LED_Color+=4;
		//if(ay>0)
			//LED_Color+=2;
		//if(az>0)
			//LED_Color+=1;
		i++;
	 zhu++;
	 if(ring==false)
		 set_LED(LED_Color);
	 else if(ring&&cr<10)
	 {
		 set_LED(6);
		 //gpio_set(PTC4, 1);
		 cr++;
	 }
	 else if(ring)
	 {
		 cr=0;
		 ring=false;
		 //gpio_set(PTC4, 0);
	 }
	 
}
