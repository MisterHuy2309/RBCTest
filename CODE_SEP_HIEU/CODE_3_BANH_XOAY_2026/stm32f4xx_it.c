/**
  ******************************************************************************
  * @file    TIM/6Steps/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    30-September-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include <stdio.h>
#include <stdlib.h>

/** @addtogroup STM32F4xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup TIM_6Steps
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void timer_do_line();	

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

void config_uart3_1(u32 baudrate);



/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
__weak void SVC_Handler(void)
{}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
__weak void PendSV_Handler(void)
{}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
	extern vu8 en_gyro;
	vu32 _view_systick=0;
	u8 _index_gyro=0;
void gp_update_uart ();	
void HMI_TRAN(vs32 so_dong);
void HMI_RUN_LOOP(vs32 _cause);
	
//__weak  void SysTick_Handler(void)
//{
//	static u32 tam_gyro=0,_HMI=0;
//	if(++tam_gyro>10)// sau 20ms thi lay imu 1 lan
//	{	tam_gyro=0;
//		if(en_gyro==1)
//		{ 	
//			USART1->DR='z';
//		//	USART3->DR=toc_do_dc_ban;
//			_index_gyro=0;
//			gp_update_uart();	
//		
//		}
//	}
//	///////////////////////HMI

//	
//	
//}



/******************************************************************************/
/*            STM32F4xx Peripherals Interrupt Handlers                        */
/******************************************************************************/

/**
  * @brief  This function handles TIM1 Trigger and commutation and TIM11 
  *         global interrupts requests.
  * @param  None
  * @retval None
  */


//xxxxxxxxxxxxxxxxxxxxxxxxxxx
extern vu8 RxBuffer_compass[2],RX_USART1[15];
extern vs16 IMU,IMU_X,IMU_Y,NGHIENG,DONG_CO_RC1;


void USART1_IRQHandler(void)// ngat  uart1 RX
{ 
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!= RESET)
    {      
			 USART_ClearFlag(USART1, USART_FLAG_RXNE);
//			USART1->SR = (uint16_t)~USART_FLAG_RXNE;
//			 RxBuffer_compass[_index_gyro++]=USART1->DR;
//			 if(_index_gyro>1)
//			 {
//				IMU=(RxBuffer_compass[0]<<8)|RxBuffer_compass[1];
//			 }

			 
//			 _view_systick++;
		}
		
		
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

extern uint8_t MANG_GAME[15],DATA_COLOR[20];
void DMA1_Stream4_IRQHandler(void)// ngat DMA uart1 RX
{
	    
			DMA_ClearITPendingBit(DMA1_Stream4,DMA_IT_TCIF4);
			//if(MANG_GAME[7]!=1)config_uart3_1(115200);
	
}
/////////////////////////

///////////
extern vu8 send_data;

///////////
void DMA2_Stream1_IRQHandler(void) 
{
    if (DMA_GetITStatus(DMA2_Stream1, DMA_IT_TCIF1) != RESET) 
    {
        DMA_ClearITPendingBit(DMA2_Stream1, DMA_IT_TCIF1);
        UART6_ProcessData();
        send_data = 1;
    }
}
/////////////////////adc////////////////////

void DMA2_Stream0_IRQHandler(void)
{
    if (DMA_GetITStatus(DMA2_Stream0, DMA_IT_TCIF0)) {
        ADC1_Update_Filter();    // Cập nhật giá trị lọc
        DMA_ClearITPendingBit(DMA2_Stream0, DMA_IT_TCIF0);
    }
}

/////////////////////////
void DMA2_Stream2_IRQHandler(void)// ngat DMA uart1 RX
{
	    
			DMA_ClearITPendingBit(DMA2_Stream2,DMA_IT_TCIF2);
			if(RX_USART1[9]!=13){
               USART_Cmd(USART1, DISABLE);
			}
			else{
				IMU=(RX_USART1[0]<<8)|RX_USART1[1];
            IMU_X=(RX_USART1[2]<<8)|RX_USART1[3];
				IMU_Y=(RX_USART1[4]<<8)|RX_USART1[5];
			}
	
}
void DMA2_Stream5_IRQHandler(void)// ngat DMA uart1 RX
{
	    
			DMA_ClearITPendingBit(DMA2_Stream5,DMA_IT_TCIF5);
			//IMU=(RxBuffer_compass[1]<<8)|RxBuffer_compass[0];
			
	
	
}
//XXXXXXXXXXXXXXXXXXXXXXXX
void gp_get_mode_uart();

void DMA1_Stream1_IRQHandler(void) // USART3 RX DMA Transfer Complete Interrupt
{
	int i;
  if (DMA_GetITStatus(DMA1_Stream1, DMA_IT_TCIF1))
  {

               DMA_ClearITPendingBit(DMA1_Stream1, DMA_IT_TCIF1);
               	gp_update_uart();
		
							//	gp_get_mode_uart();
							
              
  }

}  
/**************************************************************************************/

void DMA1_Stream0_IRQHandler(void) // UART5_RX
{
  /* Test on DMA Stream Transfer Complete interrupt */
  if (DMA_GetITStatus(DMA1_Stream0, DMA_IT_TCIF0))
  {
    /* Clear DMA Stream Transfer Complete interrupt pending bit */
    DMA_ClearITPendingBit(DMA1_Stream0, DMA_IT_TCIF0);
  }
}

/**************************************************************************************/

void DMA1_Stream7_IRQHandler(void) // UART5_TX
{
  /* Test on DMA Stream Transfer Complete interrupt */
  if (DMA_GetITStatus(DMA1_Stream7, DMA_IT_TCIF7))
  {
    /* Clear DMA Stream Transfer Complete interrupt pending bit */
//HMI_RUN_LOOP(17);
DMA_Cmd(DMA1_Stream7, DISABLE);

			//while(USART_GetFlagStatus(UART5,USART_FLAG_TXE)==RESET){};
    DMA_ClearITPendingBit(DMA1_Stream7, DMA_IT_TCIF7);
  }
}
///////////////////////////////////
void DMA1_Stream6_IRQHandler(void) // UART2_TX
{
  /* Test on DMA Stream Transfer Complete interrupt */
  if (DMA_GetITStatus(DMA1_Stream6, DMA_IT_TCIF6))
  {

			//DMA_Cmd(DMA1_Stream6, DISABLE);

    DMA_ClearITPendingBit(DMA1_Stream6, DMA_IT_TCIF6);
  }
}

/**************************************************************************************/


void DMA1_Stream2_IRQHandler(void)
{
	
		DMA_ClearITPendingBit(DMA1_Stream2, DMA_IT_TCIF4);
}



extern  void TIMER_RC(void);
int vong_quet_rc,data_rc;
extern int DC_RC_TRAI,DC_RC_PHAI,DC_RC_SAU,dma_busy; 

void DMA1_Stream3_IRQHandler(void)
{
	
		  /* Test on DMA Stream Transfer Complete interrupt */
  if (DMA_GetITStatus(DMA1_Stream3, DMA_IT_TCIF3))
  {
      
        DMA_ClearFlag(DMA1_Stream3, DMA_FLAG_TCIF3);
        DMA_Cmd(DMA1_Stream3, DISABLE);
        dma_busy = 0;   // Đã gửi xong
  }
}

//=============================================================
extern vu8 	data_tx_gyro;
extern vs32 t7,BEN_NGAT;
void TIMER_8_CHAN();
void HMI_RUN_LOOP(vs32 _cause);
void RUN_SW();
//void gp_get_mode_uart();
void TIM6_DAC_IRQHandler(void)// INTERRUPTS TIM6
{ 
  TIM_ClearITPendingBit(TIM6, TIM_IT_Update);//x�a co ngat
			USART1->DR=data_tx_gyro;		
      RUN_SW();
   //   TIMER_RC();
      USART_Cmd(USART3, ENABLE);
			USART_Cmd(USART6, ENABLE);
			USART_Cmd(USART1, ENABLE);

}

void TIM7_IRQHandler(void)
{
	//BEN_NGAT++;
//t7=TIM_GetCounter(TIM7);
//TIM_SetCounter(TIM7, 0); 	
TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
	////////////////////////////////////////////////////

	// GPIO_ToggleBits(GPIOD, GPIO_Pin_7);
}
///////////////////////////////////////////////////////////////////////
extern vs32 num_over_t1,num_over_t5;
void TIM1_UP_TIM10_IRQHandler(void)// INTERRUPTS TIM1 OR TIM10 OVERFLOW
{ 
	
	  if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM1, TIM_IT_Update);//x�a co ngat
		if(TIM1->CR1&TIM_CounterMode_Down)num_over_t1--;	
		else num_over_t1++; 
  }
	

}

void TIM1_TRG_COM_TIM11_IRQHandler(void)
{
  
}

extern vs32 num_over_t2;
void TIM2_IRQHandler(void)
{
  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	if(TIM2->CR1&TIM_CounterMode_Down)num_over_t2--;	
	else num_over_t2++;
}
////////////////////
extern vs32 num_over_t3;
void TIM3_IRQHandler(void)
{
  TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	if(TIM3->CR1&TIM_CounterMode_Down)num_over_t3--;	
	else num_over_t3++;	
}
//////////
extern vs32 num_over_t4;
void TIM4_IRQHandler(void)
{
  TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	if(TIM4->CR1&TIM_CounterMode_Down)num_over_t4--;	
	else num_over_t4++;	
}
////////////////////////////////////

void TIM5_IRQHandler(void)
{
  TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
	if(TIM5->CR1&TIM_CounterMode_Down)num_over_t5--;	
	else num_over_t5++;	
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void SPI1_IRQHandler(void)
{ 
}

/**
  * @brief  This function handles SPI2 global interrupt request.
  * @param  None
  * @retval None
  */
void SPI3_IRQHandler(void)
{ 
	
	
}

/////////////////////////////
extern vs32 DO_RONG_XUNG_1,ENCODER_HALL;
  void EXTI2_IRQHandler(void)
  {int tang,bien_sieu_am;
		
//    if(EXTI_GetITStatus(EXTI_Line2) != RESET)
//    {
//			
//			
//      GPIO_ToggleBits(GPIOA,GPIO_Pin_5);				
//			if (GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)==1){TIM_SetCounter(TIM7,0);	}				
//			else if (GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)==0){

//								sieu_am=TIM_GetCounter(TIM7);	
//							}	
//      EXTI->PR = EXTI_Line2;		
//    }
  }
	
////////////////////////////////////////////	
	  void EXTI0_IRQHandler(void)
  {
				if(EXTI_GetITStatus(EXTI_Line0) != RESET)
					{
//							GPIO_ToggleBits(GPIOC,GPIO_Pin_15);
//								if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==1){TIM_SetCounter(TIM6,0);	}				
//								else if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0){
//													DO_RONG_XUNG_1=TIM_GetCounter(TIM6);	
//												}	
//								EXTI->PR = EXTI_Line0;	
//												
					}							
  }
	
	
	
//	//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	void EXTI9_5_IRQHandler(void) {
//    uint8_t state_Pin8, state_Pin9, state_Pin5;

//    //  PC8 (GPIO_Pin_8)
//    if (EXTI_GetITStatus(EXTI_Line8) != RESET) {
//        GPIO_ToggleBits(GPIOD, GPIO_Pin_7);
//        
//        state_Pin8 = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_8);
//        state_Pin9 = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_9);
//        state_Pin5 = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5);

//        if (state_Pin8 == 1) {
//            if ((state_Pin9 == 1) && (state_Pin5 == 0)) {
//                ENCODER_HALL++;
//            } else if ((state_Pin9 == 0) && (state_Pin5 == 1)) {
//                ENCODER_HALL--;
//            }
//        } else {
//            if ((state_Pin9 == 0) && (state_Pin5 == 1)) {
//                ENCODER_HALL++;
//            } else if ((state_Pin9 == 1) && (state_Pin5 == 0)) {
//                ENCODER_HALL--;
//            }
//        }

//        EXTI_ClearITPendingBit(EXTI_Line8);
//    }

//    // PC9 (GPIO_Pin_9)
//    if (EXTI_GetITStatus(EXTI_Line9) != RESET) {
//        GPIO_ToggleBits(GPIOD, GPIO_Pin_7);

//        state_Pin8 = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_8);
//        state_Pin9 = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_9);
//        state_Pin5 = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5);

//        if (state_Pin9 == 1) {
//            if ((state_Pin8 == 0) && (state_Pin5 == 1)) {
//                ENCODER_HALL++;
//            } else if ((state_Pin8 == 1) && (state_Pin5 == 0)) {
//                ENCODER_HALL--;
//            }
//        } else {
//            if ((state_Pin8 == 1) && (state_Pin5 == 0)) {
//                ENCODER_HALL++;
//            } else if ((state_Pin8 == 0) && (state_Pin5 == 1)) {
//                ENCODER_HALL--;
//            }
//        }

//        EXTI_ClearITPendingBit(EXTI_Line9);
//    }

//    //  PE5 (GPIO_Pin_5)
//    if (EXTI_GetITStatus(EXTI_Line5) != RESET) {
//        state_Pin8 = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_8);
//        state_Pin9 = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_9);
//        state_Pin5 = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5);

//        if (state_Pin5 == 1) {
//            if ((state_Pin8 == 1) && (state_Pin9 == 0)) {
//                ENCODER_HALL++;
//            } else if ((state_Pin8 == 0) && (state_Pin9 == 1)) {
//                ENCODER_HALL--;
//            }
//        } else {
//            if ((state_Pin8 == 0) && (state_Pin9 == 1)) {
//                ENCODER_HALL++;
//            } else if ((state_Pin8 == 1) && (state_Pin9 == 0)) {
//                ENCODER_HALL--;
//            }
//        }

//        EXTI_ClearITPendingBit(EXTI_Line5);
//    }
//}


// Bien luu do rong xung va trang thai pha
volatile int32_t pulseWidth1 = 0;
volatile int32_t pulseWidth2 = 0;
volatile int32_t pulseWidth3 = 0;

volatile int32_t timerStart1 = 0;
volatile int32_t timerStart2 = 0;
volatile int32_t timerStart3 = 0;

volatile int8_t phaseFlag1 = 0;
volatile int8_t phaseFlag2 = 0;
volatile int8_t phaseFlag3 = 0;

void EXTI9_5_IRQHandler(void) {
    uint8_t state_Pin8 = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_8);
    uint8_t state_Pin9 = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_9);
    uint8_t state_Pin5 = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5);

    // Kiem tra ngat tu pha 1 (PC8)
    if (EXTI_GetITStatus(EXTI_Line8) != RESET) {
//        if (state_Pin8 == 1) {
//            timerStart1 = TIM_GetCounter(TIM7);  // Bat dau do
//            phaseFlag1 = 1;
//        } else if (phaseFlag1 == 1) {
//            pulseWidth1 = TIM_GetCounter(TIM7) - timerStart1;  // Ket thuc do
//            phaseFlag1 = 0;
//        }

        // Cap nhat Encoder
        if (state_Pin8 == 1) {
						/////////////////////////
						t7=TIM_GetCounter(TIM7)+(99*BEN_NGAT);
						BEN_NGAT=0;
						TIM_SetCounter(TIM7, 0); 
						//////////////////////////////////////////////		
            if ((state_Pin9 == 1) && (state_Pin5 == 0)) {
                ENCODER_HALL++;
            } else if ((state_Pin9 == 0) && (state_Pin5 == 1)) {
                ENCODER_HALL--;
            }
        } else {
					
				//	t7=TIM_GetCounter(TIM7)+;
            if ((state_Pin9 == 0) && (state_Pin5 == 1)) {
                ENCODER_HALL++;
            } else if ((state_Pin9 == 1) && (state_Pin5 == 0)) {
                ENCODER_HALL--;
            }
        }
        
        EXTI_ClearITPendingBit(EXTI_Line8);
    }

    // Kiem tra ngat tu pha 2 (PC9)
    if (EXTI_GetITStatus(EXTI_Line9) != RESET) {
        if (state_Pin9 == 1) {
            timerStart2 = TIM_GetCounter(TIM7);  // Bat dau do
            phaseFlag2 = 1;
        } else if (phaseFlag2 == 1) {
            pulseWidth2 = TIM_GetCounter(TIM7) - timerStart2;  // Ket thuc do
            phaseFlag2 = 0;
        }

        // Cap nhat Encoder
        if (state_Pin9 == 1) {
            if ((state_Pin8 == 0) && (state_Pin5 == 1)) {
                ENCODER_HALL++;
            } else if ((state_Pin8 == 1) && (state_Pin5 == 0)) {
                ENCODER_HALL--;
            }
        } else {
            if ((state_Pin8 == 1) && (state_Pin5 == 0)) {
                ENCODER_HALL++;
            } else if ((state_Pin8 == 0) && (state_Pin5 == 1)) {
                ENCODER_HALL--;
            }
        }
        
        EXTI_ClearITPendingBit(EXTI_Line9);
    }

    // Kiem tra ngat tu pha 3 (PE5)
    if (EXTI_GetITStatus(EXTI_Line5) != RESET) {
        if (state_Pin5 == 1) {
            timerStart3 = TIM_GetCounter(TIM7);  // Bat dau do
            phaseFlag3 = 1;
        } else if (phaseFlag3 == 1) {
            pulseWidth3 = TIM_GetCounter(TIM7) - timerStart3;  // Ket thuc do
            phaseFlag3 = 0;
        }

        // Cap nhat Encoder
        if (state_Pin5 == 1) {
            if ((state_Pin8 == 1) && (state_Pin9 == 0)) {
                ENCODER_HALL++;
            } else if ((state_Pin8 == 0) && (state_Pin9 == 1)) {
                ENCODER_HALL--;
            }
        } else {
            if ((state_Pin8 == 0) && (state_Pin9 == 1)) {
                ENCODER_HALL++;
            } else if ((state_Pin8 == 1) && (state_Pin9 == 0)) {
                ENCODER_HALL--;
            }
        }

        EXTI_ClearITPendingBit(EXTI_Line5);
    }
}

// Ham tinh do rong xung lon nhat tu ba pha
uint32_t DO_RONG_XUNG() {
    uint32_t maxPulseWidth = pulseWidth1;

    // Lay gia tri lon nhat giua ba pha
    if (pulseWidth2 > maxPulseWidth) {
        maxPulseWidth = pulseWidth2;
    }
    if (pulseWidth3 > maxPulseWidth) {
        maxPulseWidth = pulseWidth3;
    }

    return maxPulseWidth;  // Tra ve do rong xung lon nhat
}




//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX


			  void EXTI15_10_IRQHandler(void)
  {
				if(EXTI_GetITStatus(EXTI_Line15) != RESET)
					{
//							GPIO_ToggleBits(GPIOC,GPIO_Pin_15);
//								if (GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_15)==1){TIM_SetCounter(TIM7,0);	}				
//								else if (GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_15)==0){
//													DO_RONG_XUNG_1=TIM_GetCounter(TIM7);	
//												}	
//								EXTI->PR = EXTI_Line15;	
												
					}		
  }


/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
