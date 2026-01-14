
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>


vu8 DATA_SPEED[60]={          
										255,0,1,0,0,
										255,0,2,0,0,
										255,0,3,0,0,
										255,0,4,0,0,
										255,0,5,0,0,
										255,0,6,0,0,
										255,7,0,0,            
										255,0,8,0,0,
										255,0,9,0,0,
                    255,0,10,0,0,
//										255,0,9,0,0,
//										255,0,10,0,0,
                    255,0,11,0,0,
										255,12,0,0,
//									
};


///////////////////////
//    servo_tx_buf[0] = 0xFF;
//    servo_tx_buf[1] = 0xFF;
//    servo_tx_buf[2] = id;
//    servo_tx_buf[3] = 0x07;
//    servo_tx_buf[4] = 0x03;
//    servo_tx_buf[5] = 0x2A;
//    servo_tx_buf[6] = (pos >> 8) & 0xFF;
//    servo_tx_buf[7] = pos & 0xFF;
//    servo_tx_buf[8] = (time >> 8) & 0xFF;
//    servo_tx_buf[9] = time & 0xFF;

//    for (int i = 2; i < 10; i++)
//        checksum += servo_tx_buf[i];
//    servo_tx_buf[10] = ~checksum;


//vu8 DATA_RC[15]={          
//										255,255,1,0x07,0x03,0x2A,0,0,0,0,0,

//						
//};


int DC_RC_TRAI,DC_RC_PHAI,DC_RC_SAU,dma_busy; 
vs32 TOC_DO_DAT; 
float  CHAY_VA_XOAY,GIA_TOC,TOC_DO,HUONG,MAT_ROBOT  ;
//int LAY_LAN_DAU=0;
vs32 Dc_Trai_Xoay_Trai , Dc_Phai_Xoay_Trai , Dc_Sau_Xoay_Trai ,DC_nang_trai,DC_nang_sau,DC_nang_phai; //ham cua IMU>0     
vs32 Dc_Trai_Xoay_Phai, Dc_Phai_Xoay_Phai , Dc_Sau_Xoay_Phai; //ham cua IMU<0
vs32 goc_banh_trai,goc_banh_phai,goc_banh_sau  ,servo_value_trai , servo_value_sau,servo_value_phai,nang_chan_trai, nang_vitme,nang_chan_sau, nang_chan_phai,goc_rc_banh_trai,goc_rc_banh_phai,goc_rc_banh_sau ;
extern u8  bien_xuong_200,bien_leo_200,keo_chan_sau,keo_chan_truoc;

extern u8 flag_xuong,flag_len, bien_cam_bien_truoc_1,bien_cam_bien_sau_1 ,flag_400,flag_200, bien_da_hoan_thanh_leo  ; 
extern vs32 sai_so_laze;
vs32 _GOC_TRAI_CX,_GOC_PHAI_CX,_GOC_SAU_CX,_GOC_LECH_ROBO,chieu_trai,chieu_phai,chieu_sau;
vs32 _TOC_DO_BT,_TOC_DO_BP,_TOC_DO_BS;

vs32 t7,BEN_NGAT;
extern vu16 laser_truoc, laser_2, laser_3, laser_4, laser_5;
 

 

//================= ROBOCON KUNGFU 2026 =================================================================================================

//xxxxxxxxxxxxxxxxxxxxxxxxxx BIEN SU DUNG ROBOCON KUNGFU 2026 xxxxxxxxxxxxxxxxxxxxxxxxxxx
vs32 toc_do_test = 0;	

s32 muc_tieu_xung = 0, xung_con_lai = 0;

u8 HOME_FLAG = 0, touchpad_flag = 0, PREV_HOME = 0, prev_TOUCHPAD = 0, vi_tri = 0;

bool cho_phep_chay = false, dung_chay = false;


//xxxxxxxxxxxxxxxxxxxxxxxxxx INPUT ROBOCON 2026 xxxxxxxxxxxxxxxxxxxxxxxxxxx   
  
#define  CB_BANH_TRUOC_1          GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_14)
#define  CB_BANH_TRUOC_2					GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_15)

#define  CB_BANH_SAU_1				  	GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3)                          
#define  CB_BANH_SAU_2				  	GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2)

#define CB_kep_mui_giao           GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_10)//
#define CB_sau_lung               GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_1) //
#define CB_xilanh_day_kfs          GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_4)  //

#define CB_kep_KFS                !GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0) //


#define CB_TAY_TRONG              GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13)
#define CB_TAY_NGOAI              GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_14)

#define CB_HT_ngoai               GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_7)  // cam bien tay kep mui giao o ngoai
#define CB_HT_trong               GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_13)  // cam bien tay kep mui giao o trong


//xxxxxxxxxxxxxxxxxxxxxxxxxx ENCODER ROBOCON 2026 xxxxxxxxxxxxxxxxxxxxxxxxxxx
//#define ENCODER_BANH_PHAI							abs(READ_ENCODER_3())
//#define ENCODER_BANH_TRAI			   			abs(READ_ENCODER_1())
//#define ENCODER_BANH_SAU			   	    abs(READ_ENCODER_2())

#define ENCODER_TAY_KEP       			               READ_ENCODER_2()	   // abs(READ_ENCODER_2())    // RA: -72700
#define RESET_ENCODER_TAY_KEP                     (RESET_ENCODER(2))
//xxxxxxxxxxxxxxxxxxxxxxxxxx OUTPUT ROBOCON 2026 xxxxxxxxxxxxxxxxxxxxxxxxxxx

#define xilanh_tay_KFS_xuong          GPIO_WriteBit(GPIOD, GPIO_Pin_11, 1); 
#define xilanh_tay_KFS_len            GPIO_WriteBit(GPIOD, GPIO_Pin_11, 0);

#define xilanh_kep                    GPIO_WriteBit(GPIOB, GPIO_Pin_12,1);  
#define xilanh_nha                    GPIO_WriteBit(GPIOB, GPIO_Pin_12,0);


#define xilanh_giu_kfs_truoc          GPIO_WriteBit(GPIOD, GPIO_Pin_14,1);
#define xilanh_nha_kfs_truoc          GPIO_WriteBit(GPIOD, GPIO_Pin_14,0);

#define xilanh_giu_kfs_sau            GPIO_WriteBit(GPIOB, GPIO_Pin_14,1);
#define xilanh_nha_kfs_sau            GPIO_WriteBit(GPIOB, GPIO_Pin_14,0);   

#define xilanh_kep_kfs               	GPIO_WriteBit(GPIOA, GPIO_Pin_8,1);
#define xilanh_nha_kfs                GPIO_WriteBit(GPIOA, GPIO_Pin_8,0);

#define xilanh_day_kfs_ra             GPIO_WriteBit(GPIOB,GPIO_Pin_15,1);	
#define xilanh_day_kfs_vo             GPIO_WriteBit(GPIOB,GPIO_Pin_15,0);	

#define xilanh_len                    GPIO_WriteBit(GPIOD, GPIO_Pin_10,0);
#define xilanh_xuong                  GPIO_WriteBit(GPIOD, GPIO_Pin_10,1);


//xxxxxxxxxxxxxxxxxxxxxxxxxx ADC ROBOCON 2026 xxxxxxxxxxxxxxxxxxxxxxxxxxx


//================= ROBOCON  2026 =================================================================================================





#define ADC_CHANNELS     14      
#define MEDIAN_SIZE      5       
#define AVERAGE_SIZE     50    



// ======= BIáº¾N TOÃ€N Cá»¤C =======
uint16_t _ADC1_Value[ADC_CHANNELS];     
uint16_t _ADC1_Filtered[ADC_CHANNELS];  


// ======= Bá»˜ NHá»š Äá»†M =======
static uint16_t median_buf[ADC_CHANNELS][MEDIAN_SIZE];
static uint16_t avg_buf[ADC_CHANNELS][AVERAGE_SIZE];
static uint8_t avg_index = 0;


#define 	ADC1_DR_ADDRESS    ((uint32_t)0x4001204C)
////////////////////////NHUNG CHAN MAC DINH/////////////////////////////////////////

/////////////////////// --KHAI BAO DINH NGHIA PWM-- /////////////////////////////////////

#define	DIA_CHI_START1 													DATA_SPEED[0]=255
#define	DIA_CHI_P1 														   DATA_SPEED[1]=0
#define	ID1 		 															DATA_SPEED[2]=1
#define	banh_trai(A)											         ((DATA_SPEED[4]=A&0xFF)| (DATA_SPEED[3]=(A>>8)&0xFF))

#define	DIA_CHI_START2 													DATA_SPEED[5]=255
#define	DIA_CHI_P2 														   DATA_SPEED[6]=0
#define	ID2 		 															DATA_SPEED[7]=2/////5--30--2
#define	dong_co_nang_trai(B)											   ((DATA_SPEED[9]=B&0xFF)| (DATA_SPEED[8]=(B>>8)&0xFF))


//--------------cum phai----------------


#define	DIA_CHI_START3 													  	DATA_SPEED[10]=255
#define	DIA_CHI_P3 														   	  DATA_SPEED[11]=0
#define	ID3 		 																	  DATA_SPEED[12]=3
#define	banh_sau(C)											      	    ((DATA_SPEED[14]=C&0xFF)| (DATA_SPEED[13]=(C>>8)&0xFF))


#define	DIA_CHI_START4 														   DATA_SPEED[15]=255
#define	DIA_CHI_P4 														         DATA_SPEED[16]=0
#define	ID4 		 														      	DATA_SPEED[17]=4
#define	dong_co_nang_sau(D)											         ((DATA_SPEED[19]=D&0xFF)| (DATA_SPEED[18]=(D>>8)&0xFF))
//--------------cum sau ----------------

#define	DIA_CHI_START5 														   DATA_SPEED[20]=255
#define	DIA_CHI_P5														         DATA_SPEED[21]=0
#define	ID5 		 																   DATA_SPEED[22]=5
#define	banh_phai(E)												            ((DATA_SPEED[24]=E&0xFF)| (DATA_SPEED[23]=(E>>8)&0xFF))

#define	DIA_CHI_START6 														   DATA_SPEED[25]=255
#define	DIA_CHI_P6 														         DATA_SPEED[26]=0
#define	ID6 		 															  	   DATA_SPEED[27]=6
#define	dong_co_nang_phai(F)										            ((DATA_SPEED[29]=F&0xFF)| (DATA_SPEED[28]=(F>>8)&0xFF))

//==-------------------------------------------------


// #define TRAI=DATA_SPEED[2]|PHAI=DATA_SPEED[18]|SAU=DATA_SPEED[10];
////////////////////////////////////////////////////////////////////

#define	DIA_CHI_START7   			   DATA_SPEED[30]=255    // Ðong co nâng -- cau H
#define	ID7 		 			  	      DATA_SPEED[31]=7
#define  DONG_CO_len 	  			   DATA_SPEED[32]=1
#define  DONG_CO_xuong 	    	      DATA_SPEED[32]=0
#define	DONG_CO_nang   				DATA_SPEED[33]



#define	DIA_CHI_START8 								DATA_SPEED[34]=255
#define	DIA_CHI_P8 									  DATA_SPEED[35]=0
#define	ID8 		 											DATA_SPEED[36]=8
#define	DC_nang_trai(G)						((DATA_SPEED[38]=G&0xFF)| (DATA_SPEED[37]=(G>>8)&0xFF))


#define	DIA_CHI_START9 								DATA_SPEED[39]=255 // ban banh theo pid 3phase
#define	DIA_CHI_P9 										DATA_SPEED[40]=0
#define	ID9 		 											DATA_SPEED[41]=9
#define	DC_nang_sau(H)				  				((DATA_SPEED[43]=H&0xFF)| (DATA_SPEED[42]=(H>>8)&0xFF))


#define	DIA_CHI_START10 								DATA_SPEED[44]=255 // ban banh theo pid 3phase
#define	DIA_CHI_P10 										DATA_SPEED[45]=0
#define	ID10 		 											DATA_SPEED[46]=9
#define	DC_nang_phai(M)				  				((DATA_SPEED[48]=M&0xFF)| (DATA_SPEED[47]=(M>>8)&0xFF))




#define	DIA_CHI_START11 								DATA_SPEED[49]=255 // ban banh theo pid 3phase
#define	DIA_CHI_P11									 	DATA_SPEED[50]=0
#define	ID11 		 										   	DATA_SPEED[51]=9
#define	DC_vitme(N)				  			   	((DATA_SPEED[53]=N&0xFF)| (DATA_SPEED[52]=(N>>8)&0xFF))



//#define	DIA_CHI_START12 								DATA_SPEED[54]=255 // cau H 
//#define	DIA_CHI_P12									  	DATA_SPEED[55]=0
//#define	ID12 		 										   	DATA_SPEED[56]=9
//#define	DC_TAY(Q)				  			    	((DATA_SPEED[58]=N&0xFF)| (DATA_SPEED[57]=(N>>8)&0xFF))



#define	DIA_CHI_START12   		DATA_SPEED[54]=255    // Ðong co nâng -- cau H
#define	ID12 		 			  	    DATA_SPEED[55]=12
#define DC_TAY_RA 	  			  DATA_SPEED[56]=0
#define DC_TAY_VO 	    	    DATA_SPEED[56]=1
#define	DC_TAY   		    	   	DATA_SPEED[57]



//////////////////////// RC////////////////////////////

#define SERVO_COUNT 3
#define SERVO_PACKET_LEN 11
uint8_t servo_tx_buf[SERVO_COUNT][SERVO_PACKET_LEN];
uint8_t dma_tx_all[SERVO_COUNT * SERVO_PACKET_LEN]; // 33 byte



  uint16_t RC1 = 2048;
  uint16_t RC2 = 2048;
  uint16_t RC3 = 2048;
   

//=============================ADC DMI=====================================



//=============================ENCODER======================================
#define ENCODER_TIMER1	(num_over_t1<<16)|TIM_GetCounter(TIM1)
#define ENCODER_TIMER2	(num_over_t2<<16)|TIM_GetCounter(TIM2)
#define ENCODER_TIMER3	(num_over_t3<<16)|TIM_GetCounter(TIM3)
#define ENCODER_TIMER4	(num_over_t4<<16)|TIM_GetCounter(TIM4)
#define ENCODER_TIMER5	(num_over_t5<<16)|TIM_GetCounter(TIM5)
//#define RESET_ENCODER_SAU		RESET_ENCODER(2)
//#define RESET_ENCODER_PHAI		RESET_ENCODER(1);



#define MAU_TAY_PHAI_1 DATA_COLOR[13]//TAY PHAI
#define MAU_TAY_PHAI DATA_COLOR[14]//TAY PHAI

#define MAU_TAY_TRAI_1 DATA_COLOR[12]//TAY PHAI
#define MAU_TAY_TRAI DATA_COLOR[15]//TAY PHAI

#define MAU_SAN DATA_COLOR[11]//TAY PHAI



#define TOA_DO_BONG MANG_GAME[0]//TAY PHAI


////////////////////////KHAI BAO HE DIEU HANH RTOS//////////////////////////////////////////////////


//xTaskHandle Chu_trinh_1, Chu_trinh_2, Chu_trinh_3,Chu_trinh_4;

static void Task_Main(void *pvParameters);
static void Task_HMI(void *pvParameters);  
static void Task_Control_1(void *pvParameters);
static void Task_Control_2(void *pvParameters);
vs32 CHAY_TU_DONG_THEO_LAZE_0(vs32 chieu_chay,vs32 laze_chuan,float he_so_dap_ung_laze);

////////////////////////KHAI BAO HE DIEU HANH RTOS//////////////////////////////////////////////////

///////////////////////KET THUC KHAI BAO NHUNG CHAN MAC DINH/////////////////////////////////////////

vs32 	sieu_am,num_over_t1,num_over_t2, num_over_t3, num_over_t4, num_over_t5,HMI_LOOP,LAZE_TRAI,LAZE_PHAI,CANH_HUYEN,LAZE_TRUOC,LAZE_SAU, GOC_TAY_RE,doi_dau_trai,doi_dau_phai,doi_dau_sau;
vs16 	IMU,HUONG_LG,IMU_X,IMU_Y,NGHIENG,TRUNG_BINH_SUM_ADC,VI_TRI_CHUONG_TRINH=0,DONG_CO_RC1;
vu8 	data_tx_gyro,en_gyro;
vu8 	RxBuffer_compass[2],RX_USART1[15],DATA_COLOR[20];//TAY GAME, LA BAN
//vu16 _ADC1_Value[15];
unsigned int captpix[128];   
char chuoi_line[128];
uint8_t GP_BTN [15];
uint8_t MANG_GAME[15];
vs32 angle =0;

vs32 goc_banh_trai_cu,goc_banh_phai_cu,goc_banh_sau_cu;

vs32 HUONG_GAME,HUONG_GAME_CT,ENCODER_HALL;
vs32 HUONG_NGIENG, HUONG_NGIENG_L;


uint8_t flag_R1,flag_R2;


//------------------------------------ DELAY MICROSECOND--------------------------------------------
void delay_us(vu32 num)
{
	__IO uint32_t index = 0;

	/* default system clock is 180MHz */
	for(index = (18 * num); index != 0; index--);
}
//------------------------------------ DELAY MILISECOND--------------------------------------------
void delay_ms(vu32 num)
{
	__IO uint32_t index = 0;

	/* default system clock is 180MHz */
	for(index = (18000 * num); index != 0; index--);
}

///////////////////////////////////////////////

//---------------------------- KHAI BAO NGO RA -----------------------------
void Config_out_mode(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOC, ENABLE);
	///////khai báo nhung chan hien thi tren main C15,D7
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_11|GPIO_Pin_14|GPIO_Pin_10|GPIO_Pin_15;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15|GPIO_Pin_8|GPIO_Pin_9; //LED XANH DO
  GPIO_Init(GPIOC, &GPIO_InitStructure); 
	///////khai báo nhung chan OUTPUT A0,A1,A8,A12,B0,B6,B7,B8,B9,B10,B11,B12,B13,B14,B15

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_8|GPIO_Pin_12|GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10
			|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
 ////////

}

//---------------------------- KHAI BAO NGO VAO -----------------------------
void Config_in_mode(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOE  , ENABLE);
	///////khai báo NÚT NHAN XANH DO tren main 
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
//	
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	///////khai báo nhung chan IN tren main 
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_13|GPIO_Pin_14;	
	GPIO_Init(GPIOC, &GPIO_InitStructure);
   
   GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0|GPIO_Pin_1;	
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6
				|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_10|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

}

//---------------------------- KHAI BAO TIMER6 -----------------------------
void Config_int_time6(void)
{
 	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  NVIC_InitStructure.NVIC_IRQChannel = TIM6_DAC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
    
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
	TIM_TimeBaseInitStructure.TIM_Prescaler=50;//50
  TIM_TimeBaseInitStructure.TIM_Period=999;//999;//1ms
  TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//
  TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStructure);
  
  TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
  TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
  TIM_SetCounter(TIM6, 0); 
 TIM_Cmd(TIM6,ENABLE);
}
//---------------------------- KHAI BAO TIMER7 -----------------------------
void Config_int_time7(void)
{
 	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
    
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
	TIM_TimeBaseInitStructure.TIM_Prescaler=50;//500;
  TIM_TimeBaseInitStructure.TIM_Period=99;//999;//1ms
  TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//
  TIM_TimeBaseInit(TIM7, &TIM_TimeBaseInitStructure);
  
  TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
  TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
  TIM_SetCounter(TIM7, 0); 
  TIM_Cmd(TIM7,ENABLE);
}

//---------------------------- KHAI BAO PWM TIMER4 -----------------------------
void Config_pwm_time_t4(void)
{
 	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOC, ENABLE);
		
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4); // ch1
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);// ch2
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);// ch3
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);  //ch4
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_15|GPIO_Pin_13|GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
		/*
	TIM_TimeBaseStructure.TIM_Period = 839800000; // 84Mhz/839800000 = 0.1 (Hz)
TIM_TimeBaseStructure.TIM_Prescaler = 0; // Maximum TIM5 clock: 84.000.000Hz
TIM_TimeBaseStructure.TIM_ClockDivision = 0;
TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	*/
	TIM_TimeBaseInitStructure.TIM_Prescaler=84000000/(2000*255); // fpwm=2khz
  TIM_TimeBaseInitStructure.TIM_Period=256;
  TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV2;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);
  
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_Cmd(TIM4,ENABLE);
  TIM_SetCounter(TIM4, 0);
   
  TIM_OC1Init(TIM4, &TIM_OCInitStructure);
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);

}


//---------------------------- KHAI BAO ENCODER TIMER 2,3-----------------------------
void Config_encoder_timer2_timer3(void)
{
 	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
  GPIO_InitTypeDef  GPIO_InitStructure;
	 NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB, ENABLE);
	
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource15, GPIO_AF_TIM2); // tim2
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_TIM2);

  GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_TIM3); // tim3
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_TIM3);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;	
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
//  GPIO_InitStructure.GPIO_Pin = ;
//  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	TIM_TimeBaseInitStructure.TIM_Prescaler=0;
  TIM_TimeBaseInitStructure.TIM_Period=65535;
  TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
    
  TIM_ICInitStructure.TIM_Channel=TIM_Channel_1|TIM_Channel_2;
  TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Falling;
  TIM_ICInitStructure.TIM_ICFilter=20;
  TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;
  TIM_ICInit(TIM2, &TIM_ICInitStructure);
  TIM_ICInit(TIM3, &TIM_ICInitStructure);
	
  TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling, TIM_ICPolarity_Falling);
  TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling, TIM_ICPolarity_Falling);

  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
  TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
  
  TIM_Cmd(TIM2,ENABLE); 
	TIM_Cmd(TIM3,ENABLE);
	
  TIM_SetCounter(TIM2, 0); 
	TIM_SetCounter(TIM3, 0);
    
 ////////////
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  /* Enable the TIM3 gloabal Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}


//---------------------------- KHAI BAO ENCODER TIMER 1-----------------------------
void Config_encoder_timer1(void)
{
 	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
  GPIO_InitTypeDef  GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE , ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;	
  GPIO_Init(GPIOE, &GPIO_InitStructure);

	TIM_TimeBaseInitStructure.TIM_Prescaler=0;
  TIM_TimeBaseInitStructure.TIM_Period=65535;
  TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);
  
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_TIM1); // tim5
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_TIM1);

		
  TIM_ICInitStructure.TIM_Channel=TIM_Channel_1|TIM_Channel_2;
  TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Falling;
  TIM_ICInitStructure.TIM_ICFilter=200;
  TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;
  TIM_ICInit(TIM1, &TIM_ICInitStructure);	
  TIM_EncoderInterfaceConfig(TIM1, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling, TIM_ICPolarity_Falling);
  TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
  TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
  TIM_Cmd(TIM1,ENABLE); 	
  TIM_SetCounter(TIM1, 0); 
   ///////////////////////////
		TIM1->EGR = 0;           // Generate an update event
    TIM1->CR1 = 1;           // Enable the counter
   /////////////////
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_TIM10_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
//---------------------------- KHAI BAO ENCODER TIMER 1-----------------------------
void Config_encoder_timer4(void)
{
 	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
  GPIO_InitTypeDef  GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD , ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;	
  GPIO_Init(GPIOD, &GPIO_InitStructure);

	TIM_TimeBaseInitStructure.TIM_Prescaler=0;
  TIM_TimeBaseInitStructure.TIM_Period=65535;
  TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);
  
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4); // tim5
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
	
  TIM_ICInitStructure.TIM_Channel=TIM_Channel_1|TIM_Channel_2;
  TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Falling;
  TIM_ICInitStructure.TIM_ICFilter=200;
  TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;
  TIM_ICInit(TIM4, &TIM_ICInitStructure);	
  TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling, TIM_ICPolarity_Falling);
  TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
  TIM_Cmd(TIM4,ENABLE); 	
  TIM_SetCounter(TIM4, 0); 
   ///////////////////////////
		TIM4->EGR = 0;           // Generate an update event
    TIM4->CR1 = 1;           // Enable the counter
   /////////////////
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
//---------------------------- KHAI BAO ENCODER TIMER 1-----------------------------
void Config_encoder_timer5(void)
{
 	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
  GPIO_InitTypeDef  GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA , ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;	
  GPIO_Init(GPIOA, &GPIO_InitStructure);

	TIM_TimeBaseInitStructure.TIM_Prescaler=0;
  TIM_TimeBaseInitStructure.TIM_Period=65535;
  TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//
  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseInitStructure);
  
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM5); // tim5
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM5);

		
  TIM_ICInitStructure.TIM_Channel=TIM_Channel_1|TIM_Channel_2;
  TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Falling;
  TIM_ICInitStructure.TIM_ICFilter=200;
  TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;
  TIM_ICInit(TIM5, &TIM_ICInitStructure);	
  TIM_EncoderInterfaceConfig(TIM5, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling, TIM_ICPolarity_Falling);
  TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
  TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
  TIM_Cmd(TIM5,ENABLE); 	
  TIM_SetCounter(TIM5, 0); 
   ///////////////////////////
		TIM5->EGR = 0;           // Generate an update event
    TIM5->CR1 = 1;           // Enable the counter
   /////////////////
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

//---------------------------- KHAI BAO ADC DMA----------------------------- 
void Config_ADC1_DMA(void)
{
  ADC_InitTypeDef       ADC_InitStructure;
  ADC_CommonInitTypeDef ADC_CommonInitStructure;
  DMA_InitTypeDef       DMA_InitStructure;
  GPIO_InitTypeDef      GPIO_InitStructure;
   NVIC_InitTypeDef NVIC_InitStructure;
   
  /* Enable ADC3, DMA2 and GPIO clocks ****************************************/
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2 | RCC_AHB1Periph_GPIOA |RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
      /* --- Enable DMA interrupt --- */
   DMA_ITConfig(DMA2_Stream0, DMA_IT_TC, ENABLE);  // Ngáº¯t khi truyá»n xong
   //DMA_ITConfig(DMA2_Stream0, DMA_IT_HT, ENABLE);  // (tÃ¹y chá»n) ngáº¯t giá»¯a chá»«ng

   NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream0_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);

  /* DMA2 Stream0 channel0 configuration **************************************/
  DMA_InitStructure.DMA_Channel = DMA_Channel_0;  
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC1_DR_ADDRESS;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&_ADC1_Value;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_BufferSize = 14;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA2_Stream0, &DMA_InitStructure);
  
  DMA_Cmd(DMA2_Stream0, ENABLE);
  ADC_TempSensorVrefintCmd(ENABLE); // Báº­t Ä‘o Vrefint Ä‘á»ƒ tá»± kiá»ƒm tra á»•n Ä‘á»‹nh nguá»“n

//	config_ngat_dma();// cau hinh ngat dma phai dat sau lenh enable kenh dma.

  /* Configure ADC1 Channel7 pin as analog input ******************************/
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
  /* ADC Common Init **********************************************************/
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div8;
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;//ADC_DMAAccessMode_1;//
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
  ADC_CommonInit(&ADC_CommonInitStructure);

  /* ADC3 Init ****************************************************************/
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//CH?NH DO PHAN GIAI
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_ExternalTrigConv =ADC_ExternalTrigConv_T1_CC1;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfConversion = 14;
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC3 regular channel7 configuration *************************************/	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 2, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 3, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 4, ADC_SampleTime_480Cycles);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 5, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 6, ADC_SampleTime_480Cycles);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 7, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 8, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 9, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 10, ADC_SampleTime_480Cycles);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 11, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 12, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 13, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 14, ADC_SampleTime_480Cycles); // cac so rank la so thu tu chuyen doi adc 

 /* Enable DMA request after last transfer (Single-ADC mode) */
  ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);
  
//ADC_MultiModeDMARequestAfterLastTransferCmd(ENABLE);
  /* Enable ADC1 DMA */
  ADC_DMACmd(ADC1, ENABLE);
   
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);
	ADC_SoftwareStartConv(ADC1);
   

}

//---------------------------- KHAI BAO UART 1-----------------------------
void UART1_DMA_RX(u32 baudrate)
{		
		DMA_InitTypeDef DMA_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
    USART_InitTypeDef USART_InitStructure;
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
   /*-------------------------- GPIO Configuration ----------------------------*/
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOA, &GPIO_InitStructure);
   /* Connect USART pins to AF */
   GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
   GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

   USART_InitStructure.USART_BaudRate = baudrate;
   USART_InitStructure.USART_WordLength = USART_WordLength_8b;
   USART_InitStructure.USART_StopBits = USART_StopBits_1;
   USART_InitStructure.USART_Parity = USART_Parity_No;
   USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
   USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
   USART_Init(USART1, &USART_InitStructure); 
   USART_Cmd(USART1, ENABLE);
//////////////////////////////////////
////   while()
  // USART1->DR='a';
 //  delay_ms(100);

/////////////////////////////////////
   /* Configure the Priority Group to 2 bits */
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
   /* Enable the UART4 RX DMA Interrupt */
   NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream2_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
	
	 DMA_DeInit(DMA2_Stream2);
   DMA_InitStructure.DMA_Channel = DMA_Channel_4;
   DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory; // Receive
   DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)RX_USART1;
   DMA_InitStructure.DMA_BufferSize =10;//imu//(uint16_t)sizeof(Buffer);
   DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART1->DR;
   DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
   DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
   DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
   DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
   DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
   DMA_InitStructure.DMA_Priority = DMA_Priority_High;
   DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
   DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
   DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
   DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single; 
   DMA_Init(DMA2_Stream2, &DMA_InitStructure); 
   /* Enable DMA Stream Half Transfer and Transfer Complete interrupt */
   USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE); // Enable USART Rx DMA Request
	 DMA_ITConfig(DMA2_Stream2, DMA_IT_TC, ENABLE);  
   /* Enable the DMA RX Stream */
   DMA_Cmd(DMA2_Stream2, ENABLE);
	 

}
//---------------------------- KHAI BAO UART 3-----------------------------
//void UART3_DMA_RX(u32 baudrate)
//{		
//		DMA_InitTypeDef DMA_InitStructure;
//		NVIC_InitTypeDef NVIC_InitStructure;
//    USART_InitTypeDef USART_InitStructure;
//		GPIO_InitTypeDef GPIO_InitStructure;
//		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
//		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
//		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
//   /*-------------------------- GPIO Configuration ----------------------------*/
//   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
//   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//   GPIO_Init(GPIOD, &GPIO_InitStructure);
//   /* Connect USART pins to AF */
//   GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_USART3);
//   GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_USART3);

//   USART_InitStructure.USART_BaudRate = baudrate;
//   USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//   USART_InitStructure.USART_StopBits = USART_StopBits_1;
//   USART_InitStructure.USART_Parity = USART_Parity_No;
//   USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
//   USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
//   USART_Init(USART3, &USART_InitStructure); 
//   USART_Cmd(USART3, ENABLE);

///////////////////////////////////////////////	   
//   
//   /* Configure the Priority Group to 2 bits */
//   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//   /* Enable the UART4 RX DMA Interrupt */
//   NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream1_IRQn;
//   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//   NVIC_Init(&NVIC_InitStructure);
//	////////////////////////
//	 DMA_DeInit(DMA1_Stream1);
//   DMA_InitStructure.DMA_Channel = DMA_Channel_4;
//   DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory; // Receive
//   DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t) GP_BTN;
//   DMA_InitStructure.DMA_BufferSize = 10;//(uint16_t)sizeof(Buffer);
//   DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART3->DR;
//   DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
//   DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
//   DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
//   DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
//   DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
//   DMA_InitStructure.DMA_Priority = DMA_Priority_High;
//   DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
//   DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
//   DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
//   DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single; 
//   DMA_Init(DMA1_Stream1, &DMA_InitStructure); 
//   /* Enable the USART Rx DMA request */
//   USART_DMACmd(USART3, USART_DMAReq_Rx, ENABLE); 
//   /* Enable DMA Stream Half Transfer and Transfer Complete interrupt */
//   USART_DMACmd(USART3, USART_DMAReq_Rx, ENABLE); // Enable USART Rx DMA Request
//	 DMA_ITConfig(DMA1_Stream1, DMA_IT_TC, ENABLE);  
//   /* Enable the DMA RX Stream */
//   //   USART3->DR='a';
//  // delay_ms(500);
//   //USART3->DR='z';

//   
//   ///////////////////////////////////////////// tx mÃ³i thÃªm/////////////////////////////////////////////
//    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
////   /* Enable the UART4 RX DMA Interrupt */
//   NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream3_IRQn;
//   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
//   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
//   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//   NVIC_Init(&NVIC_InitStructure);
//	////////////////////////////////////////////////
//	 DMA_DeInit(DMA1_Stream3);
//   DMA_InitStructure.DMA_Channel = DMA_Channel_4;
//   DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral; // Receive
//   DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)DATA_RC;
//   DMA_InitStructure.DMA_BufferSize =(uint16_t)sizeof(DATA_RC);//(uint16_t)sizeof(Buffer_SPEED)-1 ;
//   DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART3->DR;
//   DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
//   DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
//   DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
//   DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
//   DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
//   DMA_InitStructure.DMA_Priority = DMA_Priority_High;
//   DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
//   DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
//   DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
//   DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single; 
//   DMA_Init(DMA1_Stream3, &DMA_InitStructure); 
//   /* Enable the USART Rx DMA request */
//   USART_DMACmd(USART3, USART_DMAReq_Tx, ENABLE); 
//   /* Enable DMA Stream Half Transfer and Transfer Complete interrupt */
//   USART_DMACmd(USART3, USART_DMAReq_Tx, ENABLE); // Enable USART Rx DMA Request
//	 DMA_ITConfig(DMA1_Stream3, DMA_IT_TC, ENABLE);  
//   /* Enable the DMA RX Stream */
//   
//   
//   ////////////////////////////////////////
//   
//      DMA_Cmd(DMA1_Stream1, ENABLE);	
//   DMA_Cmd(DMA1_Stream3, ENABLE);	
//   
//   
//   
//   
//}

void UART3_DMA_TX_RX(uint32_t baudrate)
{		
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    DMA_InitTypeDef DMA_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

    /*-------------------------- GPIO Configuration ----------------------------*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;     // TX: PD8, RX: PD9
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_USART3);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_USART3);

    /*-------------------------- USART Configuration ----------------------------*/
    USART_InitStructure.USART_BaudRate = baudrate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART3, &USART_InitStructure);
    USART_Cmd(USART3, ENABLE);

    /*-------------------------- NVIC Configuration ----------------------------*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream1_IRQn;      // RX
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream3_IRQn;      // TX
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /*-------------------------- DMA RX Configuration ----------------------------*/
    DMA_DeInit(DMA1_Stream1);
    DMA_InitStructure.DMA_Channel = DMA_Channel_4;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART3->DR;
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)GP_BTN;  // buffer nháº­n
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
    DMA_InitStructure.DMA_BufferSize = 10;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
    DMA_Init(DMA1_Stream1, &DMA_InitStructure);

    USART_DMACmd(USART3, USART_DMAReq_Rx, ENABLE);
    DMA_ITConfig(DMA1_Stream1, DMA_IT_TC, ENABLE);
    DMA_Cmd(DMA1_Stream1, ENABLE);

    /*-------------------------- DMA TX Configuration ----------------------------*/
    DMA_DeInit(DMA1_Stream3);
    DMA_InitStructure.DMA_Channel = DMA_Channel_4;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART3->DR;
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)dma_tx_all;
    DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
    DMA_InitStructure.DMA_BufferSize = SERVO_COUNT * SERVO_PACKET_LEN;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;       // âœ… Ä‘á»ƒ circular náº¿u Timer trigger
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
    DMA_Init(DMA1_Stream3, &DMA_InitStructure);

    USART_DMACmd(USART3, USART_DMAReq_Tx, ENABLE);
    DMA_ITConfig(DMA1_Stream3, DMA_IT_TC, ENABLE);
    DMA_Cmd(DMA1_Stream3, ENABLE);
}


//---------------------------- KHAI BAO UART 4-----------------------------
void UART4_DMA_RX(u32 baudrate)
{		
		DMA_InitTypeDef DMA_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
    USART_InitTypeDef USART_InitStructure;
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
   /*-------------------------- GPIO Configuration ----------------------------*/
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOA, &GPIO_InitStructure);
   /* Connect USART pins to AF */
   GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_UART4);
   GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_UART4);

   USART_InitStructure.USART_BaudRate = baudrate;
   USART_InitStructure.USART_WordLength = USART_WordLength_8b;
   USART_InitStructure.USART_StopBits = USART_StopBits_1;
   USART_InitStructure.USART_Parity = USART_Parity_No;
   USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
   USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
   USART_Init(UART4, &USART_InitStructure); 
   USART_Cmd(UART4, ENABLE);

/////////////////////////////////////////////	   
   
   /* Configure the Priority Group to 2 bits */
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
   /* Enable the UART4 RX DMA Interrupt */
   NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream2_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
	
	 DMA_DeInit(DMA1_Stream2);
   DMA_InitStructure.DMA_Channel = DMA_Channel_4;
   DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory; // Receive
   DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)MANG_GAME;
   DMA_InitStructure.DMA_BufferSize = 8;//(uint16_t)sizeof(Buffer);
   DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&UART4->DR;
   DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
   DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
   DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
   DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
   DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
   DMA_InitStructure.DMA_Priority = DMA_Priority_High;
   DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
   DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
   DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
   DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single; 
   DMA_Init(DMA1_Stream2, &DMA_InitStructure); 
   /* Enable the USART Rx DMA request */
   USART_DMACmd(UART4, USART_DMAReq_Rx, ENABLE); 
   /* Enable DMA Stream Half Transfer and Transfer Complete interrupt */
   USART_DMACmd(UART4, USART_DMAReq_Rx, ENABLE); // Enable USART Rx DMA Request
	 DMA_ITConfig(DMA1_Stream2, DMA_IT_TC, ENABLE);  
   /* Enable the DMA RX Stream */
   DMA_Cmd(DMA1_Stream2, ENABLE);	
}

//---------------------------- KHAI BAO UART 5-----------------------------
// Ð?nh nghia buffer và bi?n toàn c?c
#define RX_BUFFER_SIZE 128
extern uint8_t RX_Buffer[RX_BUFFER_SIZE];
extern uint8_t HMI_Data[12];
extern volatile uint8_t HMI_Data_Ready; // C? báo nh?n xong d? li?u
extern volatile uint16_t RX_Count; // Ð?m s? l?n nh?n

// Khai báo hàm
void UART5_DMA_TX_RX(u32 baudrate);
void UART5_Process_Received_Data(void);


#define VI_TRI_1  								HMI_Data[0]
#define VI_TRI_2  								HMI_Data[1]
#define VI_TRI_3  								HMI_Data[2]
#define VI_TRI_4  								HMI_Data[3]
#define VI_TRI_5  								HMI_Data[4]
#define VI_TRI_6  								HMI_Data[5]
#define VI_TRI_7  								HMI_Data[6]
#define VI_TRI_8  								HMI_Data[7]
#define VI_TRI_9  								HMI_Data[8]
#define VI_TRI_10  								HMI_Data[9]
#define VI_TRI_11 								HMI_Data[10]
#define VI_TRI_12  								HMI_Data[11]



uint8_t RX_Buffer[RX_BUFFER_SIZE];
uint8_t HMI_Data[12] = {0};
volatile uint8_t HMI_Data_Ready = 0;
volatile uint16_t RX_Count = 0;

void UART5_DMA_TX_RX(u32 baudrate)
{		
    DMA_InitTypeDef DMA_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    
    // Enable clocks
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOC, ENABLE);
    
    /*-------------------------- GPIO Configuration ----------------------------*/
    // TX Pin - PD2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    
    // RX Pin - PC12
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    
    // Connect USART pins to AF
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_UART5);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_UART5);
    
    /*-------------------------- USART Configuration ----------------------------*/
    USART_InitStructure.USART_BaudRate = baudrate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
    USART_Init(UART5, &USART_InitStructure);
    
    /*-------------------------- NVIC Configuration ----------------------------*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    
    // UART5 TX DMA Interrupt
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream7_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    // UART5 RX DMA Interrupt
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    // UART5 Interrupt
    NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    /*-------------------------- DMA TX Configuration ----------------------------*/
    DMA_DeInit(DMA1_Stream7);
    
    DMA_InitStructure.DMA_Channel = DMA_Channel_4;
    DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)Buffer_HMI;
    DMA_InitStructure.DMA_BufferSize = (uint16_t)sizeof(Buffer_HMI)-1;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&UART5->DR;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    
    DMA_Init(DMA1_Stream7, &DMA_InitStructure);
    DMA_ITConfig(DMA1_Stream7, DMA_IT_TC, ENABLE);
    
    /*-------------------------- DMA RX Configuration ----------------------------*/
    DMA_DeInit(DMA1_Stream0);
    
    DMA_InitStructure.DMA_Channel = DMA_Channel_4;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)RX_Buffer;
    DMA_InitStructure.DMA_BufferSize = RX_BUFFER_SIZE;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&UART5->DR;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    
    DMA_Init(DMA1_Stream0, &DMA_InitStructure);
    
    // Enable IDLE interrupt
    USART_ITConfig(UART5, USART_IT_IDLE, ENABLE);
    
    // Enable USART DMA
    USART_DMACmd(UART5, USART_DMAReq_Tx, ENABLE);
    USART_DMACmd(UART5, USART_DMAReq_Rx, ENABLE);
    
    // Enable DMA Stream
    DMA_Cmd(DMA1_Stream0, ENABLE);
    
    // Enable UART5
    USART_Cmd(UART5, ENABLE);
}

// Hàm x? lý d? li?u nh?n du?c
void UART5_Process_Received_Data(void)
{
    uint16_t recv_len;
    uint16_t i, j;
    
    // Tính s? byte dã nh?n
    recv_len = RX_BUFFER_SIZE - DMA_GetCurrDataCounter(DMA1_Stream0);
    
    RX_Count++; // Ð?m s? l?n vào hàm này (d? debug)
    
    // DEBUG: Ki?m tra có nh?n du?c d? li?u không
    if(recv_len == 0) {
        return; // Không có d? li?u
    }
    
    // Tìm header 0x55 0x0C
    for(i = 0; i < recv_len - 1; i++) {
        if(RX_Buffer[i] == 0x55 && RX_Buffer[i+1] == 0x0C) {
            // Ki?m tra d? d? li?u (c?n ít nh?t 14 bytes)
            if(i + 14 <= recv_len) {
                // Copy 12 byte d? li?u (b? qua 0x55 0x0C)
                for(j = 0; j < 12; j++) {
                    HMI_Data[j] = RX_Buffer[i + 2 + j];
                }
                
                HMI_Data_Ready = 1; // Ðánh d?u dã nh?n xong
                
                return; // Ðã tìm th?y và x? lý xong
            }
        }
    }
}
/*-------------------------- Data Processing ----------------------------*/

void UART5_IRQHandler(void)
{
    uint32_t temp;
    
    if(USART_GetITStatus(UART5, USART_IT_IDLE) != RESET) {
        // Clear IDLE flag (B?T BU?C ph?i làm nhu này)
        temp = UART5->SR;
        temp = UART5->DR;
        (void)temp; // Tránh warning
        
        // X? lý d? li?u
        UART5_Process_Received_Data();
    }
}

///////////////////////////////



#define HEADER_BYTE  0xAA
#define UART_BUFFER_SIZE 15
vu8 RX_USART6[UART_BUFFER_SIZE];
vu8	Cam;
vu8 received_offset = 0;  
int received_uwb = 0;	
vu8 send_data = 0;
void UART6_DMA_RX(u32 baudrate)
{		
	 DMA_InitTypeDef DMA_InitStructure;
	 NVIC_InitTypeDef NVIC_InitStructure;
   USART_InitTypeDef USART_InitStructure;
	 GPIO_InitTypeDef GPIO_InitStructure;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
   /*-------------------------- GPIO Configuration ----------------------------*/
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOC, &GPIO_InitStructure);
   /* Connect USART pins to AF */
   GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_USART6);
   GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_USART6);

   USART_InitStructure.USART_BaudRate = baudrate;
   USART_InitStructure.USART_WordLength = USART_WordLength_8b;
   USART_InitStructure.USART_StopBits = USART_StopBits_1;
   USART_InitStructure.USART_Parity = USART_Parity_No;
   USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
   USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
   USART_Init(USART6, &USART_InitStructure); 
   USART_Cmd(USART6, ENABLE);

   /* Configure the Priority Group to 2 bits */
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
   /* Enable the UART4 RX DMA Interrupt */
   NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream1_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
	
	 DMA_DeInit(DMA2_Stream1);
   DMA_InitStructure.DMA_Channel = DMA_Channel_5;
   DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory; // Receive
   DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)RX_USART6;
   DMA_InitStructure.DMA_BufferSize = UART_BUFFER_SIZE;//(uint16_t)sizeof(DATA_COLOR);
   DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART6->DR;
   DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
   DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
   DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
   DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
   DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
   DMA_InitStructure.DMA_Priority = DMA_Priority_High;
   DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
   DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
   DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
   DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single; 
   DMA_Init(DMA2_Stream1, &DMA_InitStructure); 
   /* Enable DMA Stream Half Transfer and Transfer Complete interrupt */
   USART_DMACmd(USART6, USART_DMAReq_Rx, ENABLE); // Enable USART Rx DMA Request
	 DMA_ITConfig(DMA2_Stream1, DMA_IT_TC, ENABLE);  
   /* Enable the DMA RX Stream */
   DMA_Cmd(DMA2_Stream1, ENABLE);
}

/////// RX ____VES2____HUY /////////////////
//void UART6_ProcessData(void) {
//    int i;
//    vu8 len;
//    uint8_t checksum;
//    uint8_t calc_sum;
//    
//    len = RX_USART6[1];
//    checksum = RX_USART6[2 + len];
//    calc_sum = RX_USART6[0] + len;
//    for(i=0;i<len;i++){
//        calc_sum += RX_USART6[2 + i];
//    }
//    calc_sum &= 0xFF;
//    
//    if(RX_USART6[0]==HEADER_BYTE && checksum==calc_sum){
//        send_data=1;
//    } else send_data=0;
//}



///Nhan Rx_HUY___V1 ///


void UART6_ProcessData(void) {
		int i;
    vu8 len      = RX_USART6[1];
    uint8_t checksum = RX_USART6[2 + len];
    uint8_t calc_sum = HEADER_BYTE + len;

    for(i=0; i<len; i++){
        calc_sum += RX_USART6[2 + i];
    }
    calc_sum &= 0xFF;

    if(RX_USART6[0] == HEADER_BYTE && checksum == calc_sum){
        send_data = 1;
    } else {
        send_data = 0;
    }
}


//---------------------------- KHAI BAO UART 2-----------------------------
void UART2_DMA_TX(u32 baudrate)
{		
		DMA_InitTypeDef DMA_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
    USART_InitTypeDef USART_InitStructure;
		GPIO_InitTypeDef GPIO_InitStructure;
	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
   /*-------------------------- GPIO Configuration ----------------------------*/
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOD, &GPIO_InitStructure);

   /* Connect USART pins to AF */
   GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2);
   GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2);
	

   USART_InitStructure.USART_BaudRate = baudrate;
   USART_InitStructure.USART_WordLength = USART_WordLength_8b;
   USART_InitStructure.USART_StopBits = USART_StopBits_1;
   USART_InitStructure.USART_Parity = USART_Parity_No;
   USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
   USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
   USART_Init(USART2, &USART_InitStructure); 
   USART_Cmd(USART2, ENABLE);


/////////////////////////////////
 /* Configure the Priority Group to 2 bits */
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
   /* Enable the UART4 RX DMA Interrupt */
   NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream6_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
	
	 DMA_DeInit(DMA1_Stream6);
   DMA_InitStructure.DMA_Channel = DMA_Channel_4;
   DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral; // Receive
   DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)DATA_SPEED;
   DMA_InitStructure.DMA_BufferSize =(uint16_t)sizeof(DATA_SPEED);//(uint16_t)sizeof(Buffer_SPEED)-1 ;
   DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART2->DR;
   DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
   DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
   DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
   DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
   DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
   DMA_InitStructure.DMA_Priority = DMA_Priority_High;
   DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
   DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
   DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
   DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single; 
   DMA_Init(DMA1_Stream6, &DMA_InitStructure); 
   /* Enable the USART Rx DMA request */
   USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE); 
   /* Enable DMA Stream Half Transfer and Transfer Complete interrupt */
   USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE); // Enable USART Rx DMA Request
	 DMA_ITConfig(DMA1_Stream6, DMA_IT_TC, ENABLE);  
   /* Enable the DMA RX Stream */
   DMA_Cmd(DMA1_Stream6, ENABLE);	

}


//---------------------------- KHAI BAO NGAT NGOAI-----------------------------
void ngat_ngoai(void)   
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
	EXTI_InitTypeDef  EXTI_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOC, ENABLE); 
	/* Enable SYSCFG clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	/* Configure PB5 PB6 pin as input floating */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 |GPIO_Pin_6;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	/* Connect EXTI Line5, Line6 to PB5,PB6 pin */
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource8);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource9);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource5);
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource6);
	/* Configure EXTI Line5, Line6 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line8|EXTI_Line9|EXTI_Line5|EXTI_Line6 ;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;  
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	/* Enable and set EXTI Line5, Line6 Interrupt to the lowest priority */
	NVIC_InitStructure.NVIC_IRQChannel =EXTI9_5_IRQn  ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
   
}
////////////////////////
//void DATA_RC1(vs32 RC1,vs32 id_rc)
//{
//        uint8_t i;
//        uint8_t checksum = 0;

//   
//   
//   

//        // Giáº£ sá»­ máº£ng dá»¯ liá»‡u báº¡n dÃ¹ng tÃªn lÃ  DATA_RC[]
//        // vÃ  Ä‘á»™ dÃ i dá»¯ liá»‡u = 10 byte (tÃ¹y báº¡n Ä‘iá»u chá»‰nh)
//        RC_ID=id_rc;
//        RC_1(RC1);		         // ((DATA_RC[7]=A&0xFF)|(DATA_RC[6]=(A>>8)&0xFF)) // tá»‘c Ä‘á»™
//        RC_TIMER1(0);	         // ((DATA_RC[B]=A&0xFF)|(DATA_RC[B]=(A>>8)&0xFF))

//        for (i = 2; i < 10; i++)
//            checksum += DATA_RC[i];

//        RC_CHECK_SUM = ~checksum;

//}

//=============================================================================================================== ===================================================       
            
uint8_t JOHO_Checksum(uint8_t *packet)
{
    uint16_t sum = 0;
    uint8_t len = packet[3]; // LEN byte trong packet

    // C?NG T? index 2 d?n index (2 + len) **BAO G?M**
    for (uint8_t i = 2; i <= (uint8_t)(2 + len); i++)
        sum += packet[i];

    return (uint8_t)(255 - (sum & 0xFF));
}



void JOHO_CreatePacket(uint8_t id, uint16_t pos, uint16_t time, uint8_t *buf)
{
    buf[0] = 0xFF;
    buf[1] = 0xFF;
    buf[2] = id;
    buf[3] = 0x07;      // LEN (nhu b?n dang dùng)
    buf[4] = 0x03;      // CMD
    buf[5] = 0x2A;      // ADDR
    buf[6] = (pos >> 8) & 0xFF;
    buf[7] = pos & 0xFF;
    buf[8] = (time >> 8) & 0xFF;
    buf[9] = time & 0xFF;
    buf[10] = JOHO_Checksum(buf);
}

	void Prepare_JOHO_Buffer(uint16_t pos1, uint16_t pos2, uint16_t pos3)
	{
			JOHO_CreatePacket(1, pos1, 200, servo_tx_buf[0]);
			JOHO_CreatePacket(2, pos2, 200, servo_tx_buf[1]);
			JOHO_CreatePacket(3, pos3, 200, servo_tx_buf[2]);

			memcpy(&dma_tx_all[0],  servo_tx_buf[0], SERVO_PACKET_LEN);
			memcpy(&dma_tx_all[11], servo_tx_buf[1], SERVO_PACKET_LEN);
			memcpy(&dma_tx_all[22], servo_tx_buf[2], SERVO_PACKET_LEN);
		
	}


	void TIMER_RC(void)
	{
													 if (dma_busy == 0) // Chá»‰ gá»­i khi DMA ráº£nh
							 {
									 Prepare_JOHO_Buffer(RC1, RC2, RC3);

									 DMA1_Stream3->M0AR = (uint32_t)dma_tx_all;
									 DMA1_Stream3->NDTR = SERVO_COUNT * SERVO_PACKET_LEN;

									 DMA_ClearFlag(DMA1_Stream3, DMA_FLAG_TCIF3);
									 DMA_Cmd(DMA1_Stream3, ENABLE);
								  
									 dma_busy = 1;
							 }
							 
	}

	
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
////void JOHO_CreateTorquePacket_AppStyle(uint8_t id, uint16_t torque, uint8_t *buf)
////{
////    uint8_t low = torque & 0xFF;
////    uint8_t high = (torque >> 8) & 0xFF;

////    // Gói th? nh?t - ghi byte th?p
////    buf[0] = 0xFF;
////    buf[1] = 0xFF;
////    buf[2] = id;
////    buf[3] = 0x04;
////    buf[4] = 0x03;
////    buf[5] = 0x10;
////    buf[6] = low;
////    uint8_t sum1 = 0;
////    for (uint8_t i = 2; i < 7; i++) sum1 += buf[i];
////    buf[7] = ~sum1;

////    // Gói th? hai - ghi byte cao
////    buf[8]  = 0xFF;
////    buf[9]  = 0xFF;
////    buf[10] = id;
////    buf[11] = 0x04;
////    buf[12] = 0x03;
////    buf[13] = 0x11;
////    buf[14] = high;
////    uint8_t sum2 = 0;
////    for (uint8_t i = 10; i < 15; i++) sum2 += buf[i];
////    buf[15] = ~sum2;
////}
//void JOHO_CreateTorquePacket_AppStyle(uint8_t id, uint16_t torque, uint8_t *buf)
//{
//    uint8_t low = torque & 0xFF;
//    uint8_t high = (torque >> 8) & 0xFF;

//    // --- Gói 1: ghi byte th?p vào d?a ch? 0x10 ---
//    buf[0] = 0xFF;
//    buf[1] = 0xFF;
//    buf[2] = id;
//    buf[3] = 0x04;
//    buf[4] = 0x03;
//    buf[5] = 0x10;   // Ð?a ch? th?p
//    buf[6] = low;
//    uint8_t sum1 = 0;
//    for (uint8_t i = 2; i < 7; i++) sum1 += buf[i];
//    buf[7] = ~sum1;

//    // --- Gói 2: ghi byte cao vào d?a ch? 0x11 ---
//    buf[8]  = 0xFF;
//    buf[9]  = 0xFF;
//    buf[10] = id;
//    buf[11] = 0x04;
//    buf[12] = 0x03;
//    buf[13] = 0x11;  // Ð?a ch? cao
//    buf[14] = high;
//    uint8_t sum2 = 0;
//    for (uint8_t i = 10; i < 15; i++) sum2 += buf[i];
//    buf[15] = ~sum2;
//}


//=========================================================================================================================================


//----------------------------  SEND UART-----------------------------
void SEND_UART(u8 _UART,u8 _GIA_TRI)
{
	if(_UART==1) 		{  USART_SendData(USART1, (uint8_t) _GIA_TRI); 	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET){} }
	else if(_UART==3) {  USART_SendData(USART2, (uint8_t) _GIA_TRI); 	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET){} }
	else if(_UART==4) {  USART_SendData(UART4, (uint8_t) _GIA_TRI); 	while (USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET){} }
	else if(_UART==5) {  USART_SendData(UART5, (uint8_t) _GIA_TRI); 	while (USART_GetFlagStatus(UART5, USART_FLAG_TC) == RESET){} }

}
////////////////////////////////////////////////////////////////////////
s32 READ_ENCODER_1(void)
{
								vs32 enNew,enOld = ENCODER_TIMER1;
								int i=0;
								
								while( i < 2)
								{
									enNew = ENCODER_TIMER1;
									if(abs(enNew) - abs(enOld) < 50000) i++;
									enOld = enNew;
									if(i>65000)break;
								}

								return enNew;
}
///
s32 READ_ENCODER_1_SCALED(void)
{
								vs32 enNew,enOld = ENCODER_TIMER1;
								int i=0;
								
								while( i < 2)
								{
									enNew = ENCODER_TIMER1;
									if(abs(enNew) - abs(enOld) < 50000) i++;
									enOld = enNew;
									if(i>65000)break;
								}

								return enNew/100;
}

s32 READ_ENCODER_2(void)
{
								vs32 enNew,enOld = ENCODER_TIMER2;
								int i=0;
								
								while( i < 2)
								{
									enNew = ENCODER_TIMER2;
									if(abs(enNew) - abs(enOld) < 50000) i++;
									enOld = enNew;
									if(i>65000)break;
								}

								return enNew;
}
////
s32 READ_ENCODER_3(void)
{
								vs32 enNew,enOld = ENCODER_TIMER3;
								int i=0;
								
								while( i < 2)
								{
									enNew = ENCODER_TIMER3;
									if(abs(enNew) - abs(enOld) < 50000) i++;
									enOld = enNew;
									if(i>65000)break;
								}

								return enNew;
}
////////

s32 READ_ENCODER_4(void)
{
								vs32 enNew,enOld = ENCODER_TIMER4;
								int i=0;
								
								while( i < 2)
								{
									enNew = ENCODER_TIMER4;
									if(abs(enNew) - abs(enOld) < 50000) i++;
									enOld = enNew;
									if(i>65000)break;
								}

								return enNew;
}	

///////

s32 READ_ENCODER_5(void)
{
								vs32 enNew,enOld = ENCODER_TIMER5;
								int i=0;
								
								while( i < 2)
								{
									enNew = ENCODER_TIMER5;
									if(abs(enNew) - abs(enOld) < 50000) i++;
									enOld = enNew;
									if(i>65000)break;
								}

								return enNew;
}

//---------------------------- RESET ENCODER-----------------------------
void RESET_ENCODER(u8 TIMER)
{
	if(TIMER==1) 	{	TIM1->CNT = 0;num_over_t1 = 0;	}
	else if(TIMER==2) {	TIM2->CNT = 0;num_over_t2 = 0;}	
	else if(TIMER==3) {	TIM3->CNT = 0;num_over_t3 = 0;}
	else if(TIMER==4) {	TIM4->CNT = 0;num_over_t4 = 0;}
	else if(TIMER==5) {	TIM5->CNT = 0;num_over_t5 = 0;}	

}

/////////////////////////////////

uint16_t Median5(uint16_t *arr)
{
    uint16_t temp[MEDIAN_SIZE];
    uint16_t i, j, t;
    
    memcpy(temp, arr, MEDIAN_SIZE * sizeof(uint16_t));

    for (i = 0; i < MEDIAN_SIZE - 1; i++)
    {
        for (j = i + 1; j < MEDIAN_SIZE; j++)
        {
            if (temp[i] > temp[j])
            {
                t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }
        }
    }
    return temp[MEDIAN_SIZE / 2];
}


uint16_t AverageN(uint16_t *arr)
{
    uint32_t sum = 0;
    uint16_t i;
    for (i = 0; i < AVERAGE_SIZE; i++)
        sum += arr[i];
    return (uint16_t)(sum / AVERAGE_SIZE);
}


void ADC1_Update_Filter(void)
{
    uint16_t ch, i;
    for (ch = 0; ch < ADC_CHANNELS; ch++)
    {
        
        for (i = MEDIAN_SIZE - 1; i > 0; i--)
            median_buf[ch][i] = median_buf[ch][i - 1];

      
        median_buf[ch][0] = _ADC1_Value[ch];

    
        {
            uint16_t median_val = Median5(median_buf[ch]);
            avg_buf[ch][avg_index] = median_val;
        }
    }

    avg_index++;
    if (avg_index >= AVERAGE_SIZE)
        avg_index = 0;

    for (ch = 0; ch < ADC_CHANNELS; ch++)
    {
        _ADC1_Filtered[ch] = AverageN(avg_buf[ch]);
    }
}




//---------------------------- RESET IMU-----------------------------
void START_IMU(void)
{ 
	u32 i;
  en_gyro=0;

		//SEND_UART(1,'a');
		data_tx_gyro='a';
		delay_ms(100);
  
  en_gyro=1;
  data_tx_gyro='z';
	//delay_ms(1000);
}

void RESET_IMU(void)
{ 
	u32 i;
  en_gyro=0;

		//SEND_UART(1,'a');
		data_tx_gyro='a';
		delay_ms(100);
  
  en_gyro=1;
  data_tx_gyro='z';
}

//xxxxxxxxxxxxxxxxxxxxxxxxxxx ham ting do nghieng xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void tinhDoNghieng(float IMU_X, float IMU_Y) {
   
    const float PI = 3.141592653589793238462643;

    HUONG_NGIENG = atan2(IMU_Y, IMU_X) * (1800.0 / PI); 

    
    HUONG_NGIENG_L = sqrt(IMU_X * IMU_X + IMU_Y * IMU_Y);
		
    
}

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx



//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//---------------------------- TRUYEN DU LIEU VAO MANG-----------------------------
void HMI_TRAN(vs32 _so_dong) {
	
		vs32 _i,_chua_cac_bit=0;
		char _ghep_bit[40];
		char _chu_cac_bit[40];

		_ghep_bit[0]=0;
		_chu_cac_bit[0]=0;
	
		switch (_so_dong) {
			
		//xxxxxxxxxxxxxxxxxxxxxxxxxx THONG TIN TONG QUAN CUA ROBOT (0-20) xxxxxxxxxxxxxxxxxxxxxxxxxxx			
				case 0:
						if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)){
								GPIO_WriteBit(GPIOC,GPIO_Pin_15,1);
								GPIO_SetBits(GPIOD, GPIO_Pin_7);
								HMI_DMI("--- PAGE 1 --- SAN DO IMU: ",IMU,0);
						} else {
								GPIO_WriteBit(GPIOC,GPIO_Pin_15,0);
								GPIO_ResetBits(GPIOD, GPIO_Pin_7);
								HMI_DMI("--- PAGE 1 --- SAN XANH IMU: ",	IMU,0);
						}								
						break;
										
				case 1:
						HMI_DMI("servo_value_phai: ", servo_value_phai, 1);													
						break;
									
				case 2:
						HMI_DMI("servo_value_sau: ", servo_value_sau, 2);										
						break;
									
				case 3:
						HMI_DMI("servo_value_trai: ", servo_value_trai, 3);				
						break;
									
				case 4:
						HMI_DMI("goc_banh_phai: ", goc_banh_phai, 4);						
						break;
									
				case 5:
						HMI_DMI("goc_banh_sau: ", goc_banh_sau, 5);
						break;
									
				case 6:
						HMI_DMI("goc_banh_trai: ", goc_banh_trai, 6);
						break;
//						snprintf(_ghep_bit, sizeof(_ghep_bit), "%d_%d",
//								HOME_FLAG,
//								touchpad_flag																									
//            );
//						HMI_PUTS("nut(HO_TO): ", _ghep_bit, 6);		
//						break;
									
				case 7:
						HMI_DMI("banh_phai: ", _TOC_DO_BP, 7);										
						break;
							
				case 8:
						HMI_DMI("banh_sau: ",_TOC_DO_BS, 8);													
						break;
									
				case 9:
						HMI_DMI("banh_trai: ", _TOC_DO_BT, 9);					
						break;
									
				case 10:
						HMI_DMI("_ADC1_Filtered[10] : ", _ADC1_Filtered[10]  , 10);	 																
						break;
									
				case 11:
						HMI_DMI("laser_truoc: ", laser_truoc, 11);						
						break;
									
				case 12:
						HMI_DMI("_ADC1_Filtered: ", _ADC1_Filtered[3] , 12);						
						break;
									
				case 13: 
						HMI_DMI("nang_chan_trai: ", nang_chan_trai, 13);					
						break;
									
				case 14:
						HMI_DMI("nang_chan_sau: ",nang_chan_sau , 14);					
						break;
									
				case 15:
						HMI_DMI("nang_chan_phai: ", nang_chan_phai, 15);										
						break;
				

									
				case 16:
				// HMI_DMI("O :",O,16);  						
				// hien thi phan ngo vao
						snprintf(_ghep_bit, sizeof(_ghep_bit), "%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d",
								GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_8),
                GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_7),
                GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_10),
                GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_4),
                GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_12),
                GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3),
                GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_13),
                GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4),
                              
                GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_14),
                GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3),
                GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_15),
                GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2),
                GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_14),
                GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_1),
                GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13),
                GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0)
            );                                 
						HMI_PUTS("In: ", _ghep_bit, 16);								
						break;
						
				case 17:
				//	HMI_DMI("X :",X,17);  						
				// hien thi phan ngo ra
						snprintf(_ghep_bit, sizeof(_ghep_bit), "%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d",
								GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_15),
                GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_8),
                GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_14),
                GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_14),
                GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_13),
                GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_11),
                GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_12),
                GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_10),
                              
                GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_11),
                GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_11),
                GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_10),
                GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_12),
                GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_15),
                GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_6),
                GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_0),
                GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_7)
            ); 
						HMI_PUTS("OUT: ", _ghep_bit, 17);					
						break;	
						
						case 18:
						HMI_DMI("READ_ENCODER_2: ", ENCODER_TAY_KEP, 18);										
						break;
						
						case 19:
						HMI_DMI("READ_ENCODER_3: ", READ_ENCODER_3(), 19);										
						break;
				case 20:
						snprintf(_ghep_bit, sizeof(_ghep_bit), " %d %d %d %d %d %d %d %d %d %d %d %d%",
								VI_TRI_1, //1
								VI_TRI_2, //2
								VI_TRI_3, //3
								VI_TRI_4,	//4
								VI_TRI_5, //5
								VI_TRI_6,// 6
								VI_TRI_7, //7
								VI_TRI_8, //8
								VI_TRI_9, //9
								VI_TRI_10, // 10
								VI_TRI_11, // 11
								VI_TRI_12 // 12
            ); 
						HMI_PUTS("Bit_HMI: ", _ghep_bit, 20);											
						break;
							
				case 21:
						if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)){
								GPIO_WriteBit(GPIOC,GPIO_Pin_15,1);
								GPIO_SetBits(GPIOD, GPIO_Pin_7);
								HMI_DMI("--- PAGE 1 --- SAN DO IMU: ",IMU,21);
						} else {
								GPIO_WriteBit(GPIOC,GPIO_Pin_15,0);
								GPIO_ResetBits(GPIOD, GPIO_Pin_7);
								HMI_DMI("--- PAGE 1 --- SAN XANH IMU: ",	IMU,21);
						}								
						break;
									
				case 22:
						HMI_DMI("nang_chan_trai: ", nang_chan_trai, 22);					
						break;
									
				case 23:
						HMI_DMI("nang_chan_sau: ", nang_chan_sau , 23);	 																
						break;
									
				case 24:
						HMI_DMI("nang_chan_phai: ", nang_chan_phai, 24);						
						break;
									
				case 25:
		//				HMI_DMI("ENCODER_BANH_PHAI: ", ENCODER_BANH_PHAI , 25);						
						break;
									
				case 26: 
				//		HMI_DMI("ENCODER_BANH_SAU: ", ENCODER_BANH_SAU, 26);	
						break;
									 
				case 27:
				 HMI_DMI("flag_R2: ", flag_R2, 27);		
						break;
									
				case 28:
					  HMI_DMI("flag_R1: ", flag_R1, 28);	
						break;
				case 29:
					//	HMI_DMI("bien_nang: ", bien_nang, 29);	
						break;
									
				case 30: 
						HMI_DMI("IMU_Y: ", IMU_Y, 30);					
						break;
									
				case 31:
						snprintf(_ghep_bit, sizeof(_ghep_bit), " %d %d %d %d %d %d %d %d %d %d %d %d%",
								VI_TRI_1, //1
								VI_TRI_2, //2
								VI_TRI_3, //3
								VI_TRI_4,	//4
								VI_TRI_5, //5
								VI_TRI_6,// 6
								VI_TRI_7, //7
								VI_TRI_8, //8
								VI_TRI_9, //9
								VI_TRI_10, // 10
								VI_TRI_11, // 11
								VI_TRI_12 // 12
            ); 
						HMI_PUTS("Bit_HMI: ", _ghep_bit, 31);					
											
						break;
									
				case 32:
						HMI_DMI("_ADC2_Filtered[11]: ", _ADC1_Filtered[11], 32);										
						break;						
				case 33:
						HMI_DMI("_ADC1_Filtered[12]: ", _ADC1_Filtered[12], 33);						
						break;
									
				case 34: 
						HMI_DMI("_ADC1_Filtered[13]: ", _ADC1_Filtered[13], 34);	
						break;
									 
				case 35:
				   HMI_DMI("_ADC1_Filtered[14]: ", _ADC1_Filtered[14], 35);	
						break;
									
				case 36:
				//	HMI_DMI("X :",X,17);  						
				// hien thi phan ngo ra
//						snprintf(_ghep_bit, sizeof(_ghep_bit), "%d %d %d %d %d %d %d %d %d%",
////								RX_USART6[0],
////								RX_USART6[1],
//								RX_USART6[2],
//								RX_USART6[3],
//								RX_USART6[4],
//								RX_USART6[5],
//								RX_USART6[6],
//								RX_USART6[7],
//								RX_USART6[8],
//								RX_USART6[9]
//            ); 
					//	HMI_PUTS("Bit_ESP: ", _ghep_bit, 36);					
						//break;
				case 37:
						HMI_DMI("sai_so_laze: ", sai_so_laze, 37);	
						break;
									
				case 38: 
						HMI_DMI("BAT: ", BAT, 38);					
						break;
									
				case 39:
					HMI_DMI("laser_2 : ",laser_2 , 39);					
						break;
									
				case 40:
						HMI_DMI("laser_3: ", laser_3, 40);										
						break;		
						
						
						


	






						
		//xxxxxxxxxxxxxxxxxxxxxxxxxx THONG TIN CAC CO CAU (20-38) xxxxxxxxxxxxxxxxxxxxxxxxxxx								
		}		
}


















//////////////////////////
void DATA_SPEED_RUN_LOOP()///TOC DO <254
	{int _k,_i;

	DMA_Cmd(DMA1_Stream6,ENABLE);
						
		}
//---------------------------- GUI TUNG MANG DI LAN LUOT-----------------------------
void HMI_RUN_LOOP(vs32 _cause)
{
	if(HMI_LOOP>_cause)HMI_LOOP=0;
	else HMI_LOOP++;
	HMI_TRAN(HMI_LOOP);
	}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx HÊ DIEU HANH THOI GIAN THUC xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
/*	
	hàm khoi tao chay song song bang bo thu vien FREE RT OS
	khi su dung hàm này thì 3 hàm ngat sau khong còn su dung bình thuong duoc nua\
			void SVC_Handler(void)
			void PendSV_Handler(void)
			void SysTick_Handler(void)
	vi no danh de phuc vu cho chuong trinh chay song song
{
	
*/
void DAI_RTOS_V1(void)	
  {	
	
	/* thu tu cac lenh-----------------------------------------------------------------------------------------
	//xTaskCreate								//	khoi tao tac vu
	//led_task									//	la ten cua tac vu duoc tro den hàm chua ten tác vu do
	//( signed char * ) NULL		//	chuoi chua ten tac vu, co the dat tuy y hoc de NULL
	//configMINIMAL_STACK_SIZE	//	so bien ma task su dung
	//NULL											//	
	//0													//	do uu tien cua tac vu, cang lon thi uu tien cang cao
	//&xtask3										//	nhiem vu xu li
	*///--------------------------------------------------------------------------------------------------------
    xTaskCreate(Task_Main, 		(signed char*)"Task_Main", 				256, NULL, 1,NULL );
    xTaskCreate(Task_HMI, 			(signed char*)"Task_HMI", 			256, NULL, 4, NULL);
    xTaskCreate(Task_Control_1, (signed char*)"Task_Control_1", 256, NULL, 2, NULL);
    xTaskCreate(Task_Control_2, (signed char*)"Task_Control_2", 256, NULL, 3, NULL);
    vTaskStartScheduler();

}
