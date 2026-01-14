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
		ADCValue_Control();	
		Giu_Nong_Ban();
		Control_XiLanh_NongBan();
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
	Vi_tri = 0;
	RESET_ENCODER(); 

	//-----------------------------------
	xTaskCreate(taskRobotAnalytics, (signed char *)"taskRobotAnalytics", 256, NULL, 0, NULL);
	xTaskCreate(taskDieuKhienCoCau, (signed char *)"taskDieuKhienCoCau", 256, NULL, 0, NULL);
	
	target_BT_BanBong = 200;
	state_nang = 0;
	target_BT_Xoay = 386;
	taget_BT_Nong_Ban = 960 , lock_nang = 0;
	
  
	while (1)
	{
		while(SHARE) 
{			
					
				if(R1 && OPTIONS) Reset_khoangcach();
				///lay_khoan_cach_td(lazeTraiValue);
//				if(dalay == 0)lay_khoan_cach_td();
				if(BienTroNongBanValue < 800)Xoay_nong();
				if(BienTroNongBanValue < 800) LayGTLazeTudong();
				//Xoay_nong();
				nang_ha_nong_ban();		
				//calculateJoystickOutput(LJOY_LR, LJOY_UD);	
				Lay_Mau_GT_Laze();
				if(CB_NHAN_BONG_BO_BAN == 0 && sta_nap == 0)nap_bong_2();
//				erLayMauBT = abs(layMauBT - BienTroXoayValue)*1.8;//sang :  /trua:   /chieu:8
				Reset_Ham();
				kichxilanhbanbong();
				if(R2) BanBong1();
				Bu_Tru_Luc();
				laykc();
				nap_bong_backup();

//				if(!R1 && O) {power += 1;vTaskDelay(2000);}
//				if(!R1 && X) {power -= 1;vTaskDelay(2000);}
	
	
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
