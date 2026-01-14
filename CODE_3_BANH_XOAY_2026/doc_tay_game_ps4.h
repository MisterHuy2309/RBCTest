
// ***************    khai bao bit giao tiep SPI     ******************
//
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SPI_MISO        (GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_12))

#define SPI_MOSI_0      GPIO_WriteBit(GPIOG, GPIO_Pin_13, (BitAction)(0))
#define SPI_MOSI_1      GPIO_WriteBit(GPIOG, GPIO_Pin_13, (BitAction)(1))

#define SPI_CS_0        GPIO_WriteBit(GPIOG, GPIO_Pin_15, (BitAction)(0))
#define SPI_CS_1        GPIO_WriteBit(GPIOG, GPIO_Pin_15, (BitAction)(1))

#define SPI_SCK_0       GPIO_WriteBit(GPIOG, GPIO_Pin_14, (BitAction)(0))
#define SPI_SCK_1       GPIO_WriteBit(GPIOG, GPIO_Pin_14, (BitAction)(1))

//#define SPI_MISO    PINA.7
//#define SPI_MOSI    PORTA.6
//#define SPI_CS        PORTA.5
//#define SPI_SCK        PORTA.4

//  ************ Dat bien nut nhan  *****************

#define GP_MASK_SELECT         0x01
#define GP_MASK_START        0x08
#define GP_MASK_UP            0x10
#define GP_MASK_RIGHT        0x20
#define GP_MASK_DOWN        0x40
#define GP_MASK_LEFT        0x80
#define GP_MASK_L2            0x01
#define GP_MASK_R2            0x02
#define GP_MASK_L1            0x04
#define GP_MASK_R1            0x08
#define GP_MASK_TRIANGLE    0x10
#define GP_MASK_O           0x20
#define GP_MASK_X           0x40
#define GP_MASK_SQUARE      0x80
#define GP_MASK_RJOY        0x02
#define GP_MASK_LJOY        0x04

#define GP_MODE_DIGITAL               0x41
#define GP_MODE_NEGCON                0x23
#define GP_MODE_ANALOGUE_RED_LED      0x73 // bat analog
#define GP_MODE_ANALOGUES_RED_LED     0x42 // bat analog
#define GP_MODE_ANALOGUE_GREEN_LED    0x53 // tat analog
#define GP_MODE_NONE                  0xff

#define SELECT        (GP_BTN[0] & GP_MASK_SELECT) //254
#define START        	(GP_BTN[0] & GP_MASK_START)   //247
#define LJOY        	(GP_BTN[0] & GP_MASK_RJOY)     //253
#define RJOY        	(GP_BTN[0] & GP_MASK_LJOY)     //251

#define TOI           (GP_BTN[0] & GP_MASK_UP)
#define PHAI        	(GP_BTN[0] & GP_MASK_RIGHT)
#define LUI        		(GP_BTN[0] & GP_MASK_DOWN)
#define TRAI        	(GP_BTN[0] & GP_MASK_LEFT)
//#define UP           (GP_BTN[0] & GP_MASK_UP)
//#define RIGHT       	(GP_BTN[0] & GP_MASK_RIGHT)
//#define DOWN       		(GP_BTN[0] & GP_MASK_DOWN)
//#define LEFT        	(GP_BTN[0] & GP_MASK_LEFT)

#define L2            (GP_BTN[1] & GP_MASK_L2)
#define R2            (GP_BTN[1] & GP_MASK_R2)
#define L1            (GP_BTN[1] & GP_MASK_L1)
#define R1            (GP_BTN[1] & GP_MASK_R1)

#define TAM_GIAC    	(GP_BTN[1] & GP_MASK_TRIANGLE)
#define O            	(GP_BTN[1] & GP_MASK_O)
#define X            	(GP_BTN[1] & GP_MASK_X)
#define VUONG        	(GP_BTN[1] & GP_MASK_SQUARE)

#define NUM_TRAI_BUTTON 253 //MANG 0
#define NUM_PHAI_BUTTON 251 //MANG 0

//#define RJOY_LR       		(GP_BTN[2]) //=0 la Left, 255 la Right
//#define RJOY_UD        	(GP_BTN[3]) //=0 la Up, 255 la Down
//#define LJOY_LR         	(GP_BTN[4]) //=0 la Left, 255 la Right
//#define LJOY_UD         	(GP_BTN[5]) //=0 la Up, 255 la Down

#define NUM_PHAI_CHIEU_TRAI_PHAI       		(GP_BTN[2]) //=0 la Left, 255 la Right
#define NUM_PHAI_CHIEU_LEN_XUONG        	(GP_BTN[3]) //=0 la Up, 255 la Down
#define NUM_TRAI_CHIEU_TRAI_PHAI         	(GP_BTN[4])-128 //=0 la Left, 255 la Right
#define NUM_TRAI_CHIEU_LEN_XUONG         	(GP_BTN[5])-128 //=0 la Up, 255 la Down

//    *************    khai bao bien toan cuc     ***********
extern   vs32 HUONG_GAME,HUONG_GAME_CT ;
extern   uint8_t GP_BTN [15];
extern   uint8_t MANG_GAME [15];

//    ******************    chuong trinh con    **************


void gp_update_uart (void)
{
   vs32 tac_chien_dien_tu=((MANG_GAME[0]+MANG_GAME[1]+MANG_GAME[2]+MANG_GAME[3]+MANG_GAME[4]+MANG_GAME[5]+MANG_GAME[6])/7);

   float CANH_A,CANH_B;
               if( (tac_chien_dien_tu==MANG_GAME[7])&&(tac_chien_dien_tu>0)){
              //    USART3->DR='a';
                  
                  GP_BTN[0] = MANG_GAME[0]; //SLCT JOYR JOYL STRT UP   RGHT DOWN LEFT
                  GP_BTN[1] = MANG_GAME[1]; //L2   R2   L1   R1   /\   O    X    |_|
                  GP_BTN[2] = MANG_GAME[2]; //Right Joy 0x00 = Left  0xFF = Right
                  GP_BTN[3] = MANG_GAME[3]; //Right Joy 0x00 = Up    0xFF = Down
                  GP_BTN[4] = MANG_GAME[4]; //Left Joy  0x00 = Left  0xFF = Right
                  GP_BTN[5] = MANG_GAME[5]; //Left Joy  0x00 = Up    0xFF = Down
                  //////////////////////////////////////////////
                              CANH_A=GP_BTN[4]-132;CANH_B=GP_BTN[5]-123;
                                 if(CANH_A==0)CANH_A=1;
                                 if(CANH_B==0)CANH_B=1;	
                                 HUONG_GAME_CT= (abs(CANH_A)+abs(CANH_B))/2;
                              if ((abs(CANH_B)<10)&&(abs(CANH_A)<10)) HUONG_GAME=0;   
                              else if ((CANH_B>0)&&(CANH_A<0)) HUONG_GAME=(atan(CANH_A/CANH_B)*(1800/3.1415))+1800;  
                              else if ((CANH_B>0)&&(CANH_A>0)) HUONG_GAME=-1800+(atan(CANH_A/CANH_B)*(1800/3.1415));  
                              else HUONG_GAME=(atan(CANH_A/CANH_B)*(1800/3.1415)); 
                              
              }
               
              

               else if(tac_chien_dien_tu==0){

					GP_BTN[0] = 255; //SLCT JOYR JOYL STRT UP   RGHT DOWN LEFT
					GP_BTN[1] = 255; //L2   R2   L1   R1   /\   O    X    |_|
					GP_BTN[2] = 128; //Right Joy 0x00 = Left  0xFF = Right
					GP_BTN[3] = 128; //Right Joy 0x00 = Up    0xFF = Down
					GP_BTN[4] = 128; //Left Joy  0x00 = Left  0xFF = Right
					GP_BTN[5] = 128; //Left Joy  0x00 = Up    0xFF = Down

                  
               }
               else  {
                  if( tac_chien_dien_tu!=MANG_GAME[7]) {
                     USART_Cmd(USART3, DISABLE);
                    
                  }
               }



               
           

 }
///////////////////////////////
unsigned char gp_get_mode_uart (void)
{
   
    return MANG_GAME[6];
} 


