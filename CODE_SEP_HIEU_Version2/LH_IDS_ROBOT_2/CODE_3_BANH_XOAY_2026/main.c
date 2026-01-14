#include "stm32f4xx.h"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "LID_HMI.h" 
#include "doc_tay_game.h"

#include "config.h"

#include "CODE_DK_3_BANH_XOAY.c"

#include "Quet_Nut.c"

										


#include "2026_co_cau_kungfu.c"
#include "2026_chay_tu_dong.c"



///////////////////////////////////////////////
void DATA_SPEED_RUN_LOOP();
extern int robot_start;
int main(void)
{ 
	
	//SystemInit();
/*
	HÀM OUTPUT:
	-	GPIO_ToggleBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) 											ÐAO TRANG THAI CUA CHAN
	-	GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal)       GHI TRANG THAI 0 HOAC 1 RA CHAN
	-	GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)												GHI MUC 0 RA CHAN
	- GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)													GHI MUC 1 RA CHAN
	HAM INPUT:
	-	GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)                 DOC TRANG THAI CUA NGO VAO
*/	
  Config_out_mode();//khai báo ngo ra cua mot chan bat ky	
	Config_in_mode();//khai bao ngo vào cua mot chan bat ky
/*
	CÓ 5 BO TIMER DE DOC ENCODER BANG TIMER
	HAM DOC ENCODER:
	- ENCODER = READ_ENCODER(TIMER)
	HAM RESET ENCODER:
	-	RESET_ENCODER(u8 TIMER)
*/
	Config_encoder_timer1();//doc encoder timer 1,  timer 2, timer 3, timer 5 
	Config_encoder_timer2_timer3();//doc encoder timer 1,  timer 2, timer 3, timer 5 
	Config_encoder_timer4();//cai dat timer4 o che do dieu xung
	Config_encoder_timer5();//doc encoder timer 1,  timer 2, timer 3, timer 5 
/*
	ADC CÓ 14 KENH , 4 KENH CUOI CUA LAZE _ADC1_Value[X]
	LAZE_1=_ADC1_Value[11]
	LAZE_2=_ADC1_Value[12]
	LAZE_3=_ADC1_Value[13]
	LAZE_4=_ADC1_Value[14]
*/
	Config_ADC1_DMA();//su dung  khi doc tin hieu laze hay cac tín hieu ADC<3,3v	
/*
	TIMER 6 VAF TIMER 7 KHONG DUOC KET NOI NGOAI VI NEN DUOC SU DUNG LAM BO DINH THOI

*/
  Config_int_time6();//phuc vu cho chuong trinh hoat dong song song voi he thong v?i chu ky 1ms
	//Config_int_time7();//su dung de doc sieu am, tang giam bien, chông nhieu, và các chuong trình hoat dong khong song song voi he thong
/*
	5 BO UART SU DUNG BO DMA DE GIAO TIEP VOI NGOAI VI
	UART1 XUAT RA GIA TRI: IMU
	UART2 DIEU KHIEN MACH DRIVER
	UART3 GIAO TIEP HC05 GAMEPAD GP_BTN[0]-->GP_BTN[7] 
	UART4 DU PHONG
	UART5 GIAO TIEP MAN HINH HMI
*/
	TIM_Cmd(TIM6,DISABLE);
	//TIM_Cmd(TIM7,DISABLE);
	
	UART1_DMA_RX(115200);	//usart giao tiep voi laban
	UART3_DMA_TX_RX(115200);///usart giao tiep de doc gamepad 
	UART6_DMA_RX(115200);	//SU DUNG DE GIAO TIEP MACH DO LAI
	UART4_DMA_RX(115200);
	UART5_DMA_TX(921600);///GIAO TIEP MAN HINH HMI
	UART2_DMA_TX(115200);///DIEU KHIEN DONG CO
	 //ngat_ngoai();
	 
	delay_ms(10);
	TIM_Cmd(TIM6,ENABLE);
	//TIM_Cmd(TIM7,ENABLE);
	delay_ms(10);
	START_IMU();// RESET IMU VE 0
  MAIN_CONTROL(0,0,0,1,0);
  delay_ms(100);
//-------------------------------------------------	
  DAI_RTOS_V1();//KHOI TAO HE DIEU HANH RTOS
//-------------------------------------------------	
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX HAM MAIN BAO GOM 4 TIEU TRINH XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
/*
													CAC TIEU TRINH HOAT DONG THEO DONG HO THOI GIAN CUA BO SYTEMTICK

			SW XANH DO PIN B1 
			LED XANH DO PIN C15
			LED TRANG THAI PIN D7
*/
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX TIEU TRINH 1 XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
static void Task_Main(void *pvParameters) {

		for(;;) {
			if(robot_start == 1) Robot_Start(); // Khoi Dong Robot
			update_laser_truoc();
			 Camera_uart4 = RX_USART4[0];
			quet_tay_game();
    }
}

			  

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX TIEU TRINH 2 XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
static void Task_HMI(void *pvParameters) { 
		for(;;) {				

				HMI_RUN_LOOP(41);//CANG GIAM SO DONG HIEN THI THI TOC DO QUET CANG NHANH
             //TIMER_RC();
				vTaskDelay(10);// NEU GIAM TOC DO THI DE BI TREO MAN HINH					
		}
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX TIEU TRINH 3 XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
static void Task_Control_1(void *pvParameters) {   

		for(;;) {
			
//====== SU DUNG CO CAU ======================================
			
			TestDC_RA_VAO(50); /// Ra vao tay Kep _ TAM GIAC và  X
			Test_Tay_Kep(); /// Dong Mo Tay Kep R1 và R2
			Test_Lay_VK();  /// TOUCHPAD Reset
//			Bit_tay_ra_vao(); /// 2 Ham nay dung tu dong ra vao tay kep nha, bo chung ham nay vao Co_Cau_Tay() cung dc
//			Co_Cau_Tay(); /// Ra vao tay Kep _ TAM GIAC và  X
			Nang_Ha_Tay_Kep();  ///Nang Ha Tay Kep O và VUONG
			if(OPTIONS)Test_Day_KFS();  /// OPTIONS DAY KFS Và Bám TOUCHPAD Reset
			
//==============================================================
			
			if(CB_XI_LANH_DAY_KFS == 1)
			{
				XI_LANH_GIU_KFS_SAU_ON;
				XI_LANH_DAY_KFS_VAO;
			}
			if(TOUCHPAD)
			{
				XI_LANH_GIU_KFS_SAU_OFF;
			}
			
					if(R1)
					{ 
						XI_LANH_KEP_ON;
					}
					else if(L1)
					{
						XI_LANH_KEP_OFF;
					}
		//===============================			
					
			if(R2){ XI_LANH_TAY_KEP_LEN ; }
			else if(L2 > 10) {XI_LANH_TAY_KEP_XUONG;}
			
			vTaskDelay(12);
								
			
		}			
}
  
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX TIEU TRINH 4 XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
static void Task_Control_2(void *pvParameters) {  
		for(;;) {
//				if (gp_get_mode_uart() == 13) {			

//					
//					
//					
//				}		  	
//				vTaskDelay(1);				
				
				//------------------------------------			
//																	  GPIO_ToggleBits(GPIOB, GPIO_Pin_15);	 //chan 16 // SAI DC
//																		GPIO_ToggleBits(GPIOA, GPIO_Pin_8);	 	 // chan 15/// SAI DC
//																		GPIO_ToggleBits(GPIOB, GPIO_Pin_14);		 // chan 14 // SAI DC
//																		GPIO_ToggleBits(GPIOD, GPIO_Pin_14);	 // chan 13 // SAI DC
//																		GPIO_ToggleBits(GPIOB, GPIO_Pin_13); // SAI DC
//                                  //  GPIO_ToggleBits(GPIOD, GPIO_Pin_11);
//																		GPIO_ToggleBits(GPIOB, GPIO_Pin_12); // SAI DC
//                                    GPIO_ToggleBits(GPIOD, GPIO_Pin_10); // SAI DC
//                              
//                                    GPIO_ToggleBits(GPIOB, GPIO_Pin_11);
//                                    GPIO_ToggleBits(GPIOA, GPIO_Pin_11);
//                                    GPIO_ToggleBits(GPIOB, GPIO_Pin_10);
//                                    GPIO_ToggleBits(GPIOA, GPIO_Pin_12);
//                                    GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
//                                    GPIO_ToggleBits(GPIOB, GPIO_Pin_6);
//                                    GPIO_ToggleBits(GPIOB, GPIO_Pin_0);
//                                    GPIO_ToggleBits(GPIOB, GPIO_Pin_7);
                                   //vTaskDelay(20000);
//

//																		GPIO_WriteBit(GPIOB, GPIO_Pin_15, 1);	 //chan 16
//                                    GPIO_WriteBit(GPIOA, GPIO_Pin_8, 1);	 	 // chan 15
//                                    GPIO_WriteBit(GPIOB, GPIO_Pin_14, 1);		 // chan 14
//                                    GPIO_WriteBit(GPIOD, GPIO_Pin_14, 1);	 // chan 13
//                                    GPIO_WriteBit(GPIOB, GPIO_Pin_13, 1);
//                                    GPIO_WriteBit(GPIOD, GPIO_Pin_11, 1);
//                                    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 1);
//                                    GPIO_WriteBit(GPIOD, GPIO_Pin_10, 1); // chan 9
//                              
//                                    GPIO_WriteBit(GPIOB, GPIO_Pin_11, 1);
//                                    GPIO_WriteBit(GPIOA, GPIO_Pin_11, 1);
//                                    GPIO_WriteBit(GPIOB, GPIO_Pin_10, 1);
//                                    GPIO_WriteBit(GPIOA, GPIO_Pin_12, 1);
//                                    GPIO_WriteBit(GPIOD, GPIO_Pin_15, 1);
//                                    GPIO_WriteBit(GPIOB, GPIO_Pin_6, 1);
//                                    GPIO_WriteBit(GPIOB, GPIO_Pin_0, 1);
//                                    GPIO_WriteBit(GPIOB, GPIO_Pin_7, 1);
			vTaskDelay(1);													
			 
		}			
}
