// #include "cmsis_os.h"

// 19h42 18 03 2023

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "LID_HMI.h"
#include "doc_tay_game.h"
#include "config.h"

//#include "3SwerveWheel_Vu.h"
#include "4OmniControler.h"
#include "FreeRTOS.h"
#include "task.h"
#include "DieuKhienCoCau.h"
 //#include "ROBOTRUN.h"
#include "BasicFunction.h"
#include "San_Xanh.h"
#include "San_Do.h"

int erLayMauBT;


static void taskGyro(void *pvParameters)
{
	while (1)
	{
		//-------------------------------------------------------------
			
		//-----------------------------------------------------------------
		HMI_RUN_LOOP(17);
		USART_Cmd(USART3, ENABLE);
		vTaskDelay(15);
	}
}

static void taskDieuKhienCoCau(void *pvParameters)
{

	while (1)
	{
		//if(!R1 && O)		xoay_goc_tu_dong(200);
		if(SHARE)		robotGamePadControl(30,50,80);
		else				robotStop(20);
		Angle_0h();
		Angle_4h();
		Angle_8h();	
		//Cam = RX_USART6[0];
		ADCValue_Control();	
		Giu_Nong_Ban();
//		//tinhLucBan(lazeTraiValue);
//		TinhToanLucBan(lazeTraiValue);
//		//All_Data_Power(lazeTraiValue);
		if(!bit_xoayTay) Xoay_Nong_Ban();
		vTaskDelay(3);
	}
}
static void taskRobotAnalytics(void *pvParameters)
{
	while (1)
	{
		Curent_angle_4_wheel();
		if(dungDCThayTuan == 0) robotAnalytics();
		vTaskDelay(3);
	}
}
static void taskMain(void *pvParameters)
{
	Config_out_mode(); // khai b�o ngo ra cua mot chan bat ky
	Config_in_mode();  // khai bao ngo v�o cua mot chan bat ky
	// Config_pwm_time_t8();//cai dat timer8 o che do dieu xung
	//Config_pwm_time_t4(); // cai dat timer4 o che do dieu xung
	// Config_pwm_time_t9();//cai dat timer9 o che do RC SEVOR
	Config_encoder_timer2_timer3(); // doc encoder  timer 2, timer 3, timer 5 ,timer 9
	Config_encoder_timer1();
	Config_encoder_timer5();
	Config_encoder_timer4();
	// ngat_ngoai();			//chuy�n dung de doc sieu am ket hop timer7, hoac co the dung lam nut nh�n
	Config_ADC1_DMA(); // su dung  khi doc tin hieu laze hay cac t�n hieu ADC<3,3v
	// Config_int_time6();		//phuc vu cho chuong trinh hoat dong song song voi he thong v?i chu ky 1ms
	Config_int_time7();	  // su dung de doc sieu am, tang giam bien, ch�ng nhieu, v� c�c chuong tr�nh hoat dong khong song song voi he thong
	UART1_DMA_RX(115200); // usart giao tiep voi laban
	UART2_DMA_TX(115200); /// DIEU KHIEN DONG CO
	UART3_DMA_RX(115200); // usart giao tiep de doc gamepad
	// UART4_DMA_RX(115200);	//SU DUNG DE GIAO TIEP MACH DO LAI
	UART5_DMA_TX(921600); // GIAO TIEP MAN HINH HMI
	// if (SysTick_Config(SystemCoreClock / 1000))while (1);// 1ms truyen du lieu usart den cac slever
	UART6_DMA_RX(115200);
	
	// reset lai laban
	robotResetIMU();
	
	//---- reset he thong ve vi tri ban dau
	while(!Home_wheel_0h_Out() | !Home_wheel_4h_Out() | !Home_wheel_8h_Out());
	while(!Home_wheel_0h()| !Home_wheel_4h() | !Home_wheel_8h());
	
//	while( !Home_wheel_FR_Out());
//	while(!Home_whee l_FR());
	//Ban_1 = Ban_2 = Ban_3 = 10;
	Vi_tri = 0;
	RESET_ENCODER(); 

	//-----------------------------------
	xTaskCreate(taskRobotAnalytics, (signed char *)"taskRobotAnalytics", 256, NULL, 0, NULL);
	xTaskCreate(taskDieuKhienCoCau, (signed char *)"taskDieuKhienCoCau", 256, NULL, 0, NULL);
//	Ban_1 = 20 , Ban_1_next;
//	Ban_2 = 20 , Ban_2_next;
//	Ban_3 = 20 , Ban_3_next;
	state_nang = 0;
	target_BT_Xoay = 392;
	taget_BT_Nong_Ban = 980 , lock_nang = 0;
	
  
	while (1)
	{
		while(SHARE) 
{
	
				if(BienTroNongBanValue < 800)Xoay_nong();
				//Xoay_nong();
				nang_ha_nong_ban();		
//				calculateJoystickOutput(LJOY_LR, LJOY_UD);	
				Lay_Mau_GT_Laze();
				if(CB_NHAN_BONG_BO_BAN == 0 && sta_nap == 0)nap_bong_2();
//				erLayMauBT = abs(layMauBT - BienTroXoayValue)*1.8;//sang :  /trua:   /chieu:8
				Reset_Ham();
				kichxilanhbanbong();
				if(R2) BanBong1();
				Bu_Tru_Luc();
				nap_bong_backup();

//				if(!R1 && O) {power += 1;vTaskDelay(2000);}
//				if(!R1 && X) {power -= 1;vTaskDelay(2000);}
	
	
	
	
					//Lay_Mau_GT_Bien_tro();
//				if(!R1 && SQUARE  )						BanBong1();				
//				if(!R1 && TRIANGLE )					BanBong2();	
//	    	if(!R1 && X  )							BanBong3();	
//			  if(!R1 && O  )							BanBong4();	
				
      	//TinhToanLucBan();

	
				//nap_bongtest();	
				//ban_bong_tc();
				//BanBongDangCap();
				//testlaze();
				//Ban_Bong_test();
				//Xoay_nong_tu_chinh(5);
				//test_nang_ha_nong_ban();
				//Test_Xoay(10);  
//				if(!R1 && O) {power += 1;vTaskDelay(2000);}
//				if(!R1 && X) {power -= 1;vTaskDelay(2000);}
//				reset_ham();
				//ngat_len();
//				//tim_ro();			
				//	taget_BT_Nong_Ban = 150;
//				if(CB_NHAN_BONG_BO_BAN == 0) Danh_sach_ban(lazeTraiValue);	
			//		test_nang_ha_nong_ban();
//				Lay_bong();// GIU (X)
//				lay();     
//				//ban();
//				  if(!R1 && O)	banbong();
//				if(!R1 && TOUCHPAD) ban_bong();
	//			  ban_bong();
//					
//				if(!R1 && SQUARE ) Re_Bong();
//				if(!R1 && OPTIONS) banbong_tu_dong();    
		}
		robotStop(20);
	}
}


int main(void)
{
	xTaskCreate(taskMain, (signed char *)"taskMain", 256, NULL, 0, NULL);
	xTaskCreate(taskGyro, (signed char *)"taskGyro", 256, NULL, 0, NULL);

	vTaskStartScheduler(); // lenh nay cho phep cac tac vu da nhiem hoat dong.
}
