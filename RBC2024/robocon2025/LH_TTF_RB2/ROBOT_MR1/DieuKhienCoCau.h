//*****************************8 bien toan cuc *************************************
char xl_truot_lua, xl_kep_lua_tren, xl_kep_lua_duoi, xl_nang_lua,gt_kep_bong;
int vi_tri = 0, Cbcc = 0, Cbnv = 0, Cbnn = 0,vt_xl_nang_lua = 0;
char	On_Off_Ban = 0;
int xl_ban_bong = 0;
int Nang_vong_max = 322, Nang_vong_min = 105, i;
int Nang_goc_max = 540, Nang_goc_min = 300;
int touchpad_press =0;
int laybong =0;
int en_tru = 60;
int max_speed = 10;
int speed_tay_lua = 100;
int speed_xoay = 200;
float M_PI = 3.141592653589793238462643;
int xl_kepbong_state = 0;
int xl_nangkep_state = 0;
int ban_bong_state=0 ;
int ban_bong = 0;  
int gong_luc =0;
int kich_ban = 0;
int rebong = 0;
int kc_laser;
int lazeTraiValue_Ban;
//extern vu8 update;
extern speed_temp;
extern vu8	Cam;
extern float	JTL;
int final_force;
int kc_imu_1,kc_imu_2;
float result;
int force_F;
int degree;
char lock_nang = 0;
extern vs16 	IMU,IMUxoay;
int lay_mau_la_ban=0;
double alpha_rad, delta;
int final_F_chuyen;
int force_chuyen;
float result_chuyen;

int Ban = 0;
int state_giu = 1;
int track = 0 ;
int darebong = 0;
int sta_nap = 0;
int Kich_nong_ban = 0;
int da_ban = 0;
int i,b_chuyen_bong=0;
double khoan_cach_ban;
uint8_t bienTestLucChuyen = 50;
void robotLineRunLeft(vu8 speed);
void robotLineRunRight(vu8 speed);

int angleJoy = 0;
int speedJoy = 0;

void Tang_Giam_luc()
{
	if (R1 && O) {power_shot +=1; vTaskDelay(2000);}
	if (R1 && X) {power_shot -=1; vTaskDelay(2000);}
}


//********************************************************************
void TinhToanLucBan()
{
	float shot = 0;
	float LucMin = 86;
	float KhoangCachMin = 230  ;
	float KhoangCachLuc = 4;
	float UpdateLuc = 1; 
    shot = LucMin + ((float)(lazeTraiValue_Ban - KhoangCachMin) / KhoangCachLuc)*UpdateLuc ;	 
    if (lazeTraiValue_Ban >= 350) {
				shot =(int) shot;
        shot += 13;
    } 
//		if (lazeTraiValue_Ban >= 430) {
//				shot =(int) shot;
//        shot += 13;
//    }
		power_shot = shot;
		power_shot_GocCheo = shot - 2;
}

void Lay_Mau_GT_Laze()
{
	if(LJOY) {
		lazeTraiValue_Ban =	lazeTraiValue;
//		layMauBT = BienTroXoayValue;
//		Luu_luc = calculate(lazeTraiValue_Ban + erLayMauBT + 7);
	}
}

void TinhToanLucChuyen()
{
	float pass = 0;
	float LucMin_pass = 40;
	float KhoangCachMin_pass = 129  ;
	float KhoangCachLuc_pass = 4;
	float UpdateLuc_pass = 1; 
    pass = LucMin_pass + ((float)(UWB - KhoangCachMin_pass) / KhoangCachLuc_pass)*UpdateLuc_pass ;	 
    if (UWB >= 300) {
				pass =(int) pass;
        pass += 10;
    } 
//		if (UWB >= 430) {
//				pass =(int) pass;
//        pass += 13;
//    }
		power_pass = pass;
}

void nap_bong_2()
{
		//Lay_Mau_GT_Laze();
		//for(i=0;i<100;i++)	while( CB_NHAN_BONG_BO_BAN == 0 )  {Xoay_nong();if(wantExit()) break; vTaskDelay(1);}	
		
		Ban_1 = Ban_2 = Ban_3 = 13;
		Ban_1_back, Ban_2_back, Ban_3_back;
		
		for(i=0;i<100;i++)	while( CB_NHAN_BONG_BO_BAN == 1 )  {if(wantExit()) break; vTaskDelay(1);}
		vTaskDelay(10000);
		Ban_1 = 0, Ban_2 = 0, Ban_3 = 0;
		Ban_1_back, Ban_2_back, Ban_3_back;
		XI_LANH_BAN_BONG_OFF;
		Cylinder_ban = 184,Cylinder_ban_next;
		sta_nap = 1;
		//Lay_Mau_GT_Laze();
}

//=========================================BAN BONG==============================
void Ban_bong(void){
//ban bong tr

//						if(CB_NHAN_BONG_BO_BAN == 0)
//						{	
							Tang_Giam_luc();
							lazeTraiValue_Ban = lazeTraiValue - 48;
							TinhToanLucBan();
							Ban_1_next, Ban_2_next, Ban_3_next;
							Ban_1 = Ban_2 = Ban_3 = power_shot + testluc; // power_shot , testluc							
						//}
						
}

 void Ban_bong_Goc_Cheo_1(void){
//ban bong sq
//						taget_BT_Nong_Ban = 540;
//						CamRotate = 2;
//	          Ban = 1;
//						if(CB_NHAN_BONG_BO_BAN == 0)
//						{
							//Tang_Giam_luc();
							lazeTraiValue_Ban = lazeTraiValue - 79 ; //Sang troi hoi am u : - 5 || sáng + 25 || Chieu: + 35 || hoi toi: - 54
							TinhToanLucBan();
							Ban_1 = Ban_2 = Ban_3 = power_shot; // power_shot , testluc
							Ban_1_next, Ban_2_next, Ban_3_next;
						//}
	}

	void Ban_bong_Goc_Cheo_2(void){
//ban bong X
//						taget_BT_Nong_Ban = 540;
//						CamRotate = 2;
//	          Ban = 1;
//						if(CB_NHAN_BONG_BO_BAN == 0)
//						{
							//Tang_Giam_luc();
							lazeTraiValue_Ban = lazeTraiValue + 15  ;// sang - 13 || chieu: + 15 || toi: -65
							TinhToanLucBan();
							Ban_1 = Ban_2 = Ban_3 = power_shot; // power_shot , testluc
							Ban_1_next, Ban_2_next, Ban_3_next;
//						}
	}
	
	
void Chuyen_Banh(void)
{
	TinhToanLucChuyen();
	Ban_1_next, Ban_2_next, Ban_3_next;
	Ban_1 = Ban_2 = Ban_3 = power_pass; //power_pass
} 

	
	
	void Ban_bong_Goc_Cheo_3(void){
//ban bong O
//						taget_BT_Nong_Ban = 540;
//						CamRotate = 2;
//	          Ban = 1;
//						if(CB_NHAN_BONG_BO_BAN == 0)
//						{
							lazeTraiValue_Ban = lazeTraiValue ; //sang -20 || chieu 
							TinhToanLucBan();
							Ban_1 = Ban_2 = Ban_3 = power_shot  ; // power_shot , testluc
							Ban_1_next, Ban_2_next, Ban_3_next;
//						}
	}
	
//void Chuyen_Bong(void)
//{
//if (L1&&!TOUCHPAD) {
//						CamRotate = 2;
//						taget_BT_Nong_Ban = 540;
//	          Ban = 1;
//            Ban_1 = Ban_2 = Ban_3 = final_F_chuyen;
//						Ban_1_next, Ban_2_next, Ban_3_next;

//						vTaskDelay(15000); // Wait for 1.5 seconds
//						Cylinder_ban = 250; // Activate the cylinder
//            vTaskDelay(10000);
//            Ban_1=  Ban_2 = Ban_3 = 0;
//						Ban = 0 ;
//            Cylinder_ban = 0;
//        }	
//}

// *****************************88 nang ha bo ban *********************************

void testnongban()
{
	if(O)
	{
		 Ban_1 = Ban_2 = Ban_3 = testluc;
		Ban_1_next, Ban_2_next, Ban_3_next;
	}
	else if (SQUARE)
	{
		 Ban_1 = Ban_2 = Ban_3 = 0;
	}
}

//**********************************************************************
void banxoay(vu8 speed)
{	
	if (SQUARE)							  CamRotate = speed, CamRotate_back;
	else if (O) 	            CamRotate = speed, CamRotate_next;
	else 											CamRotate = 2;

}


//void nangnong(void)
// {
// // len
//	if (!R2&&TRIANGLE)												state_giu = 0,	state_nang = 1, state_ha = 0, target_Nang_Ha = 980;//165
//	else if(bientronangbongValue >= 977 &&  target_Nang_Ha == 980 && state_giu == 0 )    Ban = 1;
//	 
//	 
//	 // xuong
//	if (!R2&&X)	
//	{ 	  
//				target_BT_Xoay = 480;			 
//				target_Nang_Ha = 70 ;


//		//out state_giu 
//				state_giu = 1;
//				Ban = 0;
//	 }
// else if(state_ha == 0&& target_Nang_Ha ==70  && bientronangbongValue < 80) 
//			{
//				state_nang = 0;
//				state_ha = 1;
//			 }	 
// }
// 
//void Re_bong(void)
//{
//						int i;
//            Ban_1 =136;
//						Ban_2 =23 , Ban_3 =23;
//						Ban_1_next, Ban_2_next, Ban_3_next;
//						for(i=0;i<100;i++)	while(CB_NHAN_BONG_BO_BAN == 0) {if(wantExit())	break; vTaskDelay(1);};		
//						if(R2)		
//						XI_LANH_BAN_BONG_ON;
//            vTaskDelay(7000);
//	          Ban_1=  Ban_2 = Ban_3 = 0;
//						XI_LANH_BAN_BONG_OFF;
//						vTaskDelay(5000);
//						Ban_1 =  Ban_2 =  Ban_3 = 8;
//						Ban_1_back, Ban_2_back, Ban_3_back;
//						for(i=0;i<100;i++)	while(CB_NHAN_BONG_BO_BAN == 1) {if(wantExit())	break; vTaskDelay(1);};
//						vTaskDelay(3000);					
//						Ban_1 = Ban_2 = Ban_3 = 0;	
//				}

//void Khoidong()
//{
//	if(X && CB_NHAN_BONG_BO_BAN == 0 )
//	{
//			Ban_1 =136;
//			Ban_2 =23 , Ban_3 =23;
//			Ban_1_next, Ban_2_next, Ban_3_next;
//	} 
//	while(R2)
//	{
//		XI_LANH_BAN_BONG_ON;
//		Ban_1 =  Ban_2 =  Ban_3 = 8;
//		Ban_1_back, Ban_2_back, Ban_3_back;
//		for(i=0;i<100;i++) while(CB_NHAN_BONG_BO_BAN == 1) {if(wantExit())	break; vTaskDelay(1);};
//		Ban_1 = Ban_2 = Ban_3 = 0;		
//	}
//}

// 

 
 
/////////// lazer******************88

//#define MOCCU 401       
//#define LUC_TAI_MOC 110
//#define LUC_MAX 250
//#define LUC_MIN 50


//#define SMOOTHING_FACTOR 0.1  

//float filtered_lazeValue = 0;

//void lucbanlazer(float lazeTruocValue) {
//    float gocBan = 0;
//    float lucBan = 0;
//    float corrected_distance;  // Khai b?o bi?n ? d?y tru?c c?c c?u l?nh th?c thi

//    filtered_lazeValue = (SMOOTHING_FACTOR * lazeTruocValue) + ((1 - SMOOTHING_FACTOR) * filtered_lazeValue);

//    corrected_distance = sqrt((filtered_lazeValue * filtered_lazeValue));  // S? d?ng bi?n sau khi khai b?o
//    lucBan = LUC_TAI_MOC * (corrected_distance / MOCCU);

//    if (lucBan > LUC_MAX) {
//        lucBan = LUC_MAX;
//    } else if (lucBan < LUC_MIN) {
//        lucBan = LUC_MIN;
//    }

//    force_F = lucBan;    
//    final_force = force_F;

//			 if (force_F == 49) result = 10; 
//			else if (force_F == 50) result = 10; 
//			else if (force_F == 51) result = 10; 
//			else if (force_F == 52) result = 10; 
//			else if (force_F == 51) result = 10; 
//			else if (force_F == 52) result = 10; 
//			 if (force_F >= 85 && force_F <= 89) { 
//        result = 9.90; // Gi? nguy?n 10
//    }  
//				if (force_F >= 90 && force_F <= 94) { 
//        result = 9.8; // Gi? nguy?n 10
//    }  
//				if (force_F >= 95 && force_F <= 97) { 
//        result = 9.75; // Gi? nguy?n 10
//    }  
//				if (force_F >= 98 && force_F <= 103) { 
//        result = 9.70; // Gi? nguy?n 10
//    }
//				final_force = force_F * (result)/10 ;		
//		}

		
		
		
//		
//#define MOCCU_CHUYEN 2500       
//#define LUC_TAI_MOC_CHUYEN 75
//#define LUC_MAX_CHUYEN 250
//#define LUC_MIN_CHUYEN 50

//#define SMOOTHING_FACTOR_CHUYEN 0.1  

//float filtered_distance_chuyen = 0;

//void lucchuyenbong(float received_distance) {
//    float gocChuyen = 0;
//    float lucChuyen = 0;
//    float corrected_distance;  

//    filtered_distance_chuyen = (SMOOTHING_FACTOR_CHUYEN * received_distance) + ((1 - SMOOTHING_FACTOR_CHUYEN) * filtered_distance_chuyen);

//    corrected_distance = sqrt((filtered_distance_chuyen * filtered_distance_chuyen));  
//    lucChuyen = LUC_TAI_MOC_CHUYEN * (corrected_distance / MOCCU_CHUYEN);

//    if (lucChuyen > LUC_MAX_CHUYEN) {
//        lucChuyen = LUC_MAX_CHUYEN;
//    } else if (lucChuyen < LUC_MIN_CHUYEN) {
//        lucChuyen = LUC_MIN_CHUYEN;
//    }


//    force_chuyen = lucChuyen;    
//    final_F_chuyen = force_chuyen;

//    if (force_chuyen == 50) result_chuyen = 10;
//			
//		final_F_chuyen = force_chuyen * (result_chuyen)/10 ;		
//}
		
//		
//#include <math.h>
//#include <stdio.h>

//#define OFFSET_TOLERANCE 3
//#define CENTER 100
//#define MAX_SPEED 22
//#define MIN_SPEED 13

//int calculateSpeed(int received_offset) {
//    int speed;
//    int distanceFromCenter;
//    float speedRatio;

//    // Tính kho?ng cách t? tâm
//    distanceFromCenter = abs(received_offset - CENTER);

//    // N?u trong vùng ch?t, không quay
//    if (distanceFromCenter <= OFFSET_TOLERANCE) {
//        return 0;
//    }

//    // Tính t? l? t?c d? (s? d?ng sigmoid)
//    speedRatio = 1.0 / (1.0 + expf(-0.08f * (distanceFromCenter - 1)));

//    // Tính t?c d?
//    speed = (int)(MIN_SPEED + (MAX_SPEED - MIN_SPEED) * speedRatio);

//    return speed;
//}
//void xoaytam(int received_offset) { 
//  int received_speed = calculateSpeed(received_offset);
//	if(R2){
//				track = 1;
//        if (abs(received_offset - CENTER) <= OFFSET_TOLERANCE) {
//	           CamRotate = 2;
//        } 
//        else if (received_offset < CENTER - OFFSET_TOLERANCE) {
//            CamRotate_back, CamRotate = received_speed;
//        } 
//        else if (received_offset > CENTER + OFFSET_TOLERANCE) {
//            CamRotate_next, CamRotate = received_speed;
//        }
//		 }
//}
		
		
//void calculate_angle() {
//    float angle_deg;
//    float angle_rad = atan2f((float)LJOY_LR - 127.5f, (float)LJOY_UD - 127.5f); 
//    angle_deg = angle_rad * (180.0f / M_PI);

//    if (angle_deg < 0) {
//        angle_deg += 360.0f; 
//    }
//    if (LJOY_UD == 126 && LJOY_LR == 127) { 
//        angle_deg = 20000;
//    }

//    
//    if (angle_deg <= 180.0f) {
//        angle_deg = angle_deg * 10; 
//    } else {
//        angle_deg = (angle_deg - 360.0f) * 10; 
//    }

//    JTA = angle_deg - 450; 
//}

void nuot_bong(void)
{
	int i;
	if(RJOY)
	{
		Ban_1 =  Ban_2 =  Ban_3 = 13;
		Ban_1_back, Ban_2_back, Ban_3_back;

	  for(i=0;i<100;i++)	while(CB_NHAN_BONG_BO_BAN == 1) {if(wantExit())	break; vTaskDelay(1);};
		vTaskDelay(3000);
		Cylinder_ban = 184,Cylinder_ban_next;
		Ban_1 = Ban_2 = Ban_3 = 0;
	}
}
	
//nuot truot
//if (R1) {
//        if (R1) { 
//            Ban_1 = Ban_2 = Ban_3 = 120;
//						Ban_1_next, Ban_2_next, Ban_3_next;
//            while (R1) {
//                vTaskDelay(100); 
//            }
//						
//            Ban_1 = Ban_2 = Ban_3 = 30;
//						Ban_1_back, Ban_2_back, Ban_3_back;
//						for(i=0;i<100;i++)	while(CB_NHAN_BONG_BO_BAN==1) {if(wantExit())	break; vTaskDelay(1);};
//						vTaskDelay(3000);
//						Cylinder_nang = 250;
//						Ban_1 = 0, Ban_2 = 0, Ban_3 = 0;

//        }
//    }	




//void reset(void){
// if(OPTIONS) {
//    // Reset các giá tr? ban d?u
//    Ban_1 = Ban_2 = Ban_3 = 0;
//		track = 0;
//    target_BT_Xoay = 507;
//     if (target_BT_Xoay < Min_BT_Xoay)
//         target_BT_Xoay = Min_BT_Xoay;
//     if (target_BT_Xoay > Max_BT_Xoay)
//         target_BT_Xoay = Max_BT_Xoay;
//		 
//    // Ki?m tra và di?u khi?n d?ng co xoay v? v? trí 480
//    if (abs(BienTroXoayValue - target_BT_Xoay) > 3) {
//        if (BienTroXoayValue > target_BT_Xoay) {
//            CamRotate_back;
//            CamRotate = 10; 
//        }
//        else {
//            CamRotate_next;
//            CamRotate = 10;
//        }
//    }
//    else {
//        CamRotate = 2;
//    }
//    
//    // Ki?m tra gi?i h?n an toàn
//    if(BienTroXoayValue > 620) CamRotate = 0;
//    if(BienTroXoayValue < 250) CamRotate = 0;
// }
//}
//void Nang_Ha_Nong_Ban(void)
//{
//	if (R1 && X && (taget_BT_Xoay < Max_BT_Xoay))
//		taget_BT_Xoay++, vTaskDelay(300);
//	else if (R1 && TRIANGLE && (taget_BT_Xoay > Min_BT_Xoay))
//		taget_BT_Xoay--, vTaskDelay(400);
//}


//====================================================================================


// char CB_line_trai, CB_line_phai, Nho_trai_truoc, Nho_trai_sau, Nho_phai_truoc, Nho_phai_truoc;
//void robotGamePadControl(vu8 speedMin, vu8 speedMax)
//{
//	int tocdo = 20, td_x = 5;
//	float tocdoXoay = 0;
//	int rJoy_LR = (RJOY_LR >= 5 && RJOY_LR <= 250) ? 1 : 0;
//	int lJoy_LR = (LJOY_LR >= 5 && LJOY_LR <= 250) ? 1 : 0;

//	if (UP && DOWN && RIGHT && LEFT && rJoy_LR)
//	{				  // Khong dieu khien
//		robotStop(0); // truot banh

//		return;
//	}
//	/*_____________________________//___________________________*/

//	/********************** TOC DO ****************************/
//	/*_____________________________//___________________________*/
//	if (!L1)
//		tocdo = speedMax, tocdoXoay = 0.5;
//	else
//		tocdo = speedMin, tocdoXoay = 0.3;

//	//--------- chay cac huong -----------
//	if (!UP && DOWN && RIGHT && LEFT && L2)
//		robotRun(0, tocdo);
//	else if (UP && !DOWN && RIGHT && LEFT && L2)
//		robotRun(1800, tocdo);
//	else if (UP && DOWN && !RIGHT && LEFT && L2)
//		robotRun(900, tocdo);
//	else if (UP && DOWN && RIGHT && !LEFT && L2)
//		robotRun(-900, tocdo);

//	else if (!UP && DOWN && !RIGHT && LEFT && L2)
//		robotRun(450, tocdo);
//	else if (!UP && DOWN && RIGHT && !LEFT && L2)
//		robotRun(-450, tocdo);
//	else if (UP && !DOWN && !RIGHT && LEFT && L2)
//		robotRun(1350, tocdo);
//	else if (UP && !DOWN && RIGHT && !LEFT && L2)
//		robotRun(-1350, tocdo);

//	//-------------- Dang chay va Khong chay nua, chi xoay ----------------
//	if (UP && DOWN && RIGHT && LEFT && !rJoy_LR && lJoy_LR && robotIsRun())
//		robotStop(0);

//	//-------------- Xoay ----------------
//	if (rJoy_LR)
//		robotRotateStop();
//	else if (RJOY_LR < 5) 
//	{
//		if (robotIsRun())
//			robotRotateFree(tocdoXoay, 0);
//		else
//			robotRotateFree(tocdoXoay, 0);
//	}
//	else if (RJOY_LR > 250)
//	{
//		if (robotIsRun())
//			robotRotateFree(-tocdoXoay, 0);
//		else
//			robotRotateFree(-tocdoXoay, 0);
//		//			robotLineRunLeft(20);//
//	}

//	else
//		robotRotateStop();
//}

//////-------------------------------------------------------------
void ADCValue_Control(void)
{
	// khai bao lazer
	static unsigned int lazeSauCouter = 0, lazeSau_SUM = 0;
	static unsigned int lazeTruocCouter = 0, lazeTruoc_SUM = 0;
	static unsigned int lazePhaiCouter = 0, lazePhai_SUM = 0;
	static unsigned int lazeTraiCouter = 0, lazeTrai_SUM = 0;

	// Bien tro vi tri co cau
	static unsigned int bientromamxoayCouter = 0, bientromamxoay_SUM = 0;
	static unsigned int bientronangluaCouter = 0, bientronanglua_SUM = 0;
	static unsigned int bientronangbongCouter = 0, bientronangbong_SUM = 0;
	////----------------TINH TOAN LAZER---------------
	if (lazeSauCouter++ < 100)
	{
		lazeSau_SUM += cam_bien_laze_sau;
	}
	else
	{
		lazeSauValue = lazeSau_SUM / 100;
		lazeSauCouter = 0;
		lazeSau_SUM = 0;
	}
	//-------------------------------------------
	if (lazeTruocCouter++ < 100)
	{
		lazeTruoc_SUM += cam_bien_laze_truoc;
	}
	else
	{
		lazeTruocValue = lazeTruoc_SUM / 100;
		lazeTruocCouter = 0;
		lazeTruoc_SUM = 0;
	}
	//------------------------------
	if (lazePhaiCouter++ < 100)
	{
		lazePhai_SUM += cam_bien_laze_phai;
	}
	else
	{
		lazePhaiValue = lazePhai_SUM / 100;
		lazePhaiCouter = 0;
		lazePhai_SUM = 0;
	}
	//-----------------------------------------
	if (lazeTraiCouter++ < 120)
	{
		lazeTrai_SUM += cam_bien_laze_trai;
	}
	else
	{
		lazeTraiValue = lazeTrai_SUM / 120;
		lazeTraiCouter = 0;
		lazeTrai_SUM = 0;
	}
	//-----------------TINH TOAN BIEN TRO---------------

	if (bientromamxoayCouter++ < 10)
	{
		bientromamxoay_SUM += bien_tro_xoay_nong;
	}
	else
	{
		BienTroXoayValue = bientromamxoay_SUM / 10;
		bientromamxoayCouter = 0;
		bientromamxoay_SUM = 0;
	}
	//-----------------------------------
	if (bientronangluaCouter++ < 50)
	{
		bientronanglua_SUM += bien_tro_nang_lua;
	}
	else
	{
		bientronangluaValue = bientronanglua_SUM / 50;
		bientronangluaCouter = 0;
		bientronanglua_SUM = 0;
	}
	//-----------------------------
	if (bientronangbongCouter++ < 50)
	{
		bientronangbong_SUM += bien_tro_nang_bong;
	}
	else
	{
		bientronangbongValue = bientronangbong_SUM / 50;
		bientronangbongCouter = 0;
		bientronangbong_SUM = 0;
	}
}


 
 

//	if (taget_BT_Nong_Ban < Min_BT_Nong_Ban)
//		taget_BT_Nong_Ban = Min_BT_Nong_Ban;
//	if (taget_BT_Nong_Ban > Max_BT_Nong_Ban)
//		taget_BT_Nong_Ban = Max_BT_Nong_Ban;

//	if (abs(BienTroNongBanValue - taget_BT_Nong_Ban) > 1)
//	{
//		if (BienTroNongBanValue > taget_BT_Nong_Ban)
//			Cylinder_back;
//		else
//			Cylinder_next;

//		speed_temp = abs(BienTroNongBanValue - taget_BT_Nong_Ban)*10;
//		if (speed_temp > 250) // 50
//			speed_temp = 250;
//		if (speed_temp < 50) 
//			speed_temp = 50;

//		Cylinder = speed_temp;
//	}
//	else
//		Cylinder = 0;
//}



//void Nang_Ha_Nong_Ban_abs(void)
//{
//	if (R1 && X && (taget_BT_Nong_Ban < Max_BT_Nong_Ban))
//		taget_BT_Nong_Ban++, vTaskDelay(300);
//	else if (R1 && TRIANGLE && (taget_BT_Nong_Ban > Min_BT_Nong_Ban))
//		taget_BT_Nong_Ban--, vTaskDelay(300);
//}

////*******************************************************************


///////NONG BAN
void Nong_Ban()
{
	if (taget_BT_Nong_Ban < Min_BT_Nong_Ban )
		taget_BT_Nong_Ban = Min_BT_Nong_Ban;
	if (taget_BT_Nong_Ban > Max_BT_Nong_Ban)
		taget_BT_Nong_Ban = Max_BT_Nong_Ban;

	if (abs(bientronangluaValue - taget_BT_Nong_Ban) > 5)
	{
		if (bientronangluaValue > taget_BT_Nong_Ban)  Nongban_next;
		else                                       Nongban_back;

		speed_temp = abs(bientronangluaValue - taget_BT_Nong_Ban);
		if (speed_temp > 250) // 50
			speed_temp = 250;	
		if (speed_temp < 250) 							
			speed_temp = 250;
		
		Nongban = speed_temp;
	}
	else
		Nongban = 2;
//	
	if(bientronangluaValue > 650) Nongban = 0;
	if(bientronangluaValue < 520) Nongban = 0;
}


//////////NANG HA

void Giu_nang_ha()
{
	
	if (target_Nang_Ha < Min_Nang_Ha)
		target_Nang_Ha = Min_Nang_Ha;
	if (target_Nang_Ha > Max_Nang_Ha)
		target_Nang_Ha = Max_Nang_Ha;

	if (abs(bientronangbongValue - target_Nang_Ha) > 3)
	{
		if (bientronangbongValue > target_Nang_Ha)	nang_back;
		else																				nang_next;

		speed_temp = abs(bientronangbongValue - target_Nang_Ha)*2;
		if (speed_temp > 250)
				speed_temp = 250;
		
		if (speed_temp < 30)
				speed_temp = 30;
		
		
		if (bientronangbongValue < 70) speed_temp = 20;
		else if (bientronangbongValue < 100) speed_temp = 50;
					
		nang_ha = speed_temp;
	}
	else nang_ha = 2;
	if(state_nang == 0)  nang_ha = 0;
	
	
	}


void Nang_Ha_Nong_Ban(void)
{
	if (R2 && X && (target_Nang_Ha < Max_Nang_Ha))
		target_Nang_Ha++, vTaskDelay(300);
	else if (R2 && TRIANGLE && (target_Nang_Ha > Min_Nang_Ha))
		target_Nang_Ha--, vTaskDelay(400);
}

///////XOAY nONG
// void Xoay_Nong_Ban()
// {
//     if (target_BT_Xoay < Min_BT_Xoay)
//         target_BT_Xoay = Min_BT_Xoay;
//     if (target_BT_Xoay > Max_BT_Xoay)
//         target_BT_Xoay = Max_BT_Xoay;

//     if (abs(BienTroXoayValue - target_BT_Xoay) > 3)
//     {
//         if (BienTroXoayValue > target_BT_Xoay)  CamRotate_back;
//         else                                     CamRotate_next;

//         speed_temp = abs(BienTroXoayValue - target_BT_Xoay)*10;
//         if (speed_temp > 10)                             
//             speed_temp = 10;
        
//         CamRotate = speed_temp;
//     }
//     else
//         CamRotate = 2;

		

//     if(BienTroXoayValue > 620) CamRotate = 0;
//     if(BienTroXoayValue < 250) CamRotate = 0;

// }

void Xoay_nong (void)
{
	if (O && (target_BT_Xoay < Max_BT_Xoay))
		target_BT_Xoay++, vTaskDelay(650);
	else if (SQUARE && (target_BT_Xoay > Min_BT_Xoay))
		target_BT_Xoay --, vTaskDelay(650);
}
//////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

void Giu_Nong_Ban()
{
	if (taget_BT_Nong_Ban < Min_BT_Nong_Ban)
		taget_BT_Nong_Ban = Min_BT_Nong_Ban;
	if (taget_BT_Nong_Ban > Max_BT_Nong_Ban)
		taget_BT_Nong_Ban = Max_BT_Nong_Ban;

	if (abs(bientronangluaValue - taget_BT_Nong_Ban) > 5 && lock_nang == 0)
	{
		speed_temp = (abs(bientronangluaValue - taget_BT_Nong_Ban))*3;
		if (bientronangluaValue > taget_BT_Nong_Ban)
		{
			Nongban_next;
			if(bientronangluaValue >= 935)
			{
				speed_temp = 100;
			}
			else
			{
			
			if (speed_temp > 250) //200
				speed_temp = 250; 	
			if (speed_temp < 30)  //10
					speed_temp = 30;
			}
		}
		else 
		{
			Nongban_back;
			if (speed_temp > 220)  //250
				speed_temp = 220;
			if (speed_temp < 10)  //150
				speed_temp = 10;		//100
		}
		Nongban = speed_temp; 
	}
	else  
	{
		Nongban = 5;
		lock_nang = 1;
	}

	if (state_nang == 0)  
		Nongban = 0;
}
////
void nang_ha_nong_ban(void) // min 40 max 930  /// min 83 max 982
{
	if(!R1 && TRIANGLE)	{
		state_nang = 1, state_ha = 0, taget_BT_Nong_Ban = 95 + Troi_Bientro , lock_nang = 0 , XI_LANH_RE_BONG_ON;
	}
	else if(!R1 && X){
	taget_BT_Nong_Ban = 975 + Troi_Bientro , lock_nang = 0 , XI_LANH_RE_BONG_OFF;
	}
	else if (taget_BT_Nong_Ban >=935  && state_ha == 0 && bientronangluaValue > 935 ){
	state_nang = 0;  
	state_ha = 1;
	}
}

//////////////////////////////////////////////////////////////////////////////



void ReBanhDangCapThoThay(int M1, int M2, int M3)
{
    if( R2)
		{
			XI_LANH_RE_BONG_ON;
			Ban_1_next, Ban_2_next, Ban_3_next;
      Ban_1 = M1;
			Ban_2 = M2;
			Ban_3 = M3;

		}
}


void kichxilanhbanbong()
{
	if (TOUCHPAD)
	{
		XI_LANH_BAN_BONG_ON;
		vTaskDelay(7000);
		XI_LANH_BAN_BONG_OFF;
		Ban_1_next, Ban_2_next, Ban_3_next;
      Ban_1 = 0;
			Ban_2 = 0;
			Ban_3 = 0;
		//lay_mau_la_ban=6;
		Cylinder_ban =0,Cylinder_ban_next;
		b_chuyen_bong=0;
		darebong = 0;
		sta_nap = 0;

	}
		
	}
//	else if ( TOUCHPAD )
//	{
//		XI_LANH_BAN_BONG_ON;
//		vTaskDelay(7000);
//		Ban_1 =  Ban_2 =  Ban_3 = 20;
//		Ban_1_back, Ban_2_back, Ban_3_back;
//	  for(i=0;i<100;i++)	while(CB_NHAN_BONG_BO_BAN == 1) {if(wantExit())	break; vTaskDelay(1);};
//		vTaskDelay(3000);
//		Cylinder_ban = 184,Cylinder_ban_next;
//		Ban_1 = Ban_2 = Ban_3 = 0;
//	}


void reset_ham(void)
{
	if(OPTIONS)
	{
		Ban_1 = Ban_2 = Ban_3 = 0;
		Kich_nong_ban = 0;
		//ban_bong = 0;
		//kich_ban = 0;
		b_chuyen_bong=0;
		darebong = 0;
		XI_LANH_RE_BONG_OFF;
	}
	if(OPTIONS &&  CB_NHAN_BONG_BO_BAN == 1)
	{
		Ban_1 = Ban_2 = Ban_3 = 0;
		Kich_nong_ban = 0;
		//ban_bong = 0;
		Cylinder_ban = 0 , Cylinder_ban_back;
		//kich_ban = 0;
		//lock_nang = 0;
		//state_nang = 0;
		b_chuyen_bong=0;
	}
}


//void calculateJoystickOutput(int x, int y) {
//    // Tính toán góc t? tr?c Y và theo chi?u kim d?ng h?
//    int raw_angle = (int)(atan2(x, y) * (1800.0 / 3.14)); // Nhân 10 d? tang d? chính xác
//    if (raw_angle < 0) {
//        raw_angle += 3600; // Chuy?n d?i t? kho?ng -1800-1800 thành 0-3600
//    }
//    angleJoy = raw_angle; // Ðua v? kho?ng 0-360 d?

//    // Tính toán d? dài du?ng chéo (magnitude)
//    speedJoy = (int)sqrt(x * x + y * y); // Magnitude s? là giá tr? nguyên
//}
void calculateJoystickOutput(int x, int y) {
    // Offset trung tâm joystick (tùy ch?nh n?u c?n)
    const int center = 125;

    // Chu?n hóa giá tr? x, y t? joystick v? t?a d? v?i g?c (0,0) ? gi?a
    int normX = x - center;
    int normY = y - center;

    // Tính toán góc (theo d?, nhân 10 d? tang d? chính xác)
    int raw_angle = (int)(atan2(normX, normY) * (1800.0 / 3.14159265)); // 1800 = 180 * 10

    if (raw_angle < 0) {
        raw_angle += 3600; // Chuy?n t? [-1800,1800] -> [0,3600]
    }

    angleJoy = raw_angle;

    // Tính toán d? l?n vector (magnitude)
    speedJoy = (int)sqrt(normX * normX + normY * normY);
}

void testtialaze()
{
	if(O)
	{
			 Cylinder_ban = 254 , Cylinder_ban_next;
	}
	else {	 Cylinder_ban = 0 , Cylinder_ban_back;
}
}

//int gong_luc =0;
//int kich_ban = 0;


void chuyen_bong(void)
{
	if(!R1 && O && bientronangluaValue > 910)
	{
		b_chuyen_bong =1;
		rebong = 0;
		state_nang = 1, state_ha = 0, taget_BT_Nong_Ban = 95 + Troi_Bientro , lock_nang = 0 , XI_LANH_RE_BONG_ON;
	}
}

int calculate(int K) {
		int i;
    int A[] = {100, 120, 125, 135, 140, 165, 170, 205, 210, 220, 225, 250, 255, 265, 270, 295, 300, 315, 320, 335, 340, 350, 355, 375, 380, 410};
    int B[] = {45, 45, 45, 47, 48, 55, 56, 66, 68, 70, 71, 77, 78, 82, 83, 96, 96, 99, 99, 103, 103, 104, 104, 114, 116, 127};

    for (i = 0; i < 25; i++) {
        if (K >= A[i] && K <= A[i+1]) {
					if(K >= 390 && K <= 410) return (B[i] + (K - A[i]) * (B[i+1] - B[i]) / (A[i+1] - A[i])) - 5 	;
						else return B[i] + (K - A[i]) * (B[i+1] - B[i]) / (A[i+1] - A[i]);
            //return B[i] + (K - A[i]) * (B[i+1] - B[i]) / (A[i+1] - A[i]);
        }
    }
    return 99;
}






//void ban_bong_theo_la_ban ()
//{
//	//HIEU
//	if(LJOY_UD > 200) {
//			while(LJOY_UD > 200) {if(wantExit())	break; vTaskDelay(1);};
//			lay_mau_la_ban+=1;
//		}
//	
//	if(lay_mau_la_ban==1){
//		kc_imu_1=IMU;
//		kc_laser=lazeTraiValue;
//		vTaskDelay(1);
//		lay_mau_la_ban=2;
//}
//	else if(lay_mau_la_ban==3){
//		kc_imu_2=IMU;
//		vTaskDelay(1);
//		lay_mau_la_ban=4;
//	}
//	if(lay_mau_la_ban>=5)
//	{
//		lay_mau_la_ban=0;
//	 kc_imu_2=kc_imu_1=kc_laser=0;
//	}
//	
//}
//void tinh_luc()
//{
//	// HIEU
//	if(kc_imu_1>kc_imu_2){
//	alpha_rad = (abs((kc_imu_1-kc_imu_2)/10)) * 3.14/ 180.0;
//	}
//	if(kc_imu_1<kc_imu_2){
//			alpha_rad = (abs((kc_imu_2-kc_imu_1)/10)) * 3.14/ 180.0;
//	}
//		
//	delta = pow(2 * kc_laser * cos(alpha_rad), 2) - (4 * ((kc_laser*kc_laser) - (90*90)));
//  khoan_cach_ban = ((2 * kc_laser * cos(alpha_rad) + sqrt(delta)) / 2)-90;
//	
//	}
//void TinhToanLucBan_h_VIP1()
//{
//	float shot = 0;
//	float LucMin = 92;
//	float KhoangCachMin = 360  ;
//	float KhoangCachLuc = 5;
//	float UpdateLuc = 1; 
//    shot = LucMin + ((float)(khoan_cach_ban - KhoangCachMin) / KhoangCachLuc)*UpdateLuc ;	 
//    if (khoan_cach_ban >= 400) {
//				shot =(int) shot;
//        shot += 6;
//    } if (khoan_cach_ban >= 430) {
//				shot =(int) shot;
//        shot += 13;
//    }
//		power_shot = shot;
//		if(lay_mau_la_ban>=1)
//		{
//			
//			Ban_1_next, Ban_2_next, Ban_3_next;
//			if(kc_laser>=450){
//			Ban_1 = shot-3;
//			Ban_2 = shot-3;
//			Ban_3 = shot-3;
//			}
//			if(kc_laser<450){
//			Ban_1 = shot+5;
//			Ban_2 = shot+5;
//			Ban_3 = shot+5;	
//				
//				
//			}
//			
//		}
//		
//			
//			
//		}

//		
//void tinh_luc_v2()
//{
//	if(LJOY_UD > 200) {
//			while(LJOY_UD > 200) {if(wantExit())	break; vTaskDelay(1);};
//			lay_mau_la_ban+=1;
//		}
//	
//	if(lay_mau_la_ban==1){
//kc_laser=lazeTraiValue;
//kc_imu_1=IMU;
//vTaskDelay(1);
//lay_mau_la_ban=2;
//	}
//	
//	
//	
//	
//	
//	
//}	
//		
//		
//		
//		
//void chien_thuat_qua_san()
//{
//	if(nhan_nut_chay == 1 && CB1 == 0 && CB2 == 1 && CB3 == 1 )
//	{
//		RobotRun(900 , 100);
//		encoder (100);
//	}
//	else if( nhan_nut_chay == 1 &&  CB1 == 0 && CB2 ==0 && CB3==0 )
//	{
//		RobotRun(0 , 100);
//		encoder (100);
//	}
//	else if (nhan_nut_chay == 1 && CB1 == 1 && CB2 == 1 && CB3 == 0)
//	{
//		RobotRun(-900 , 100);
//		 encoder (100);
//	}
//

