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

char lock_nang = 0;

int state_nap_bong =1;

int xl_kepbong_state = 0;
int xl_nangkep_state = 0;
int ban_bong_state=0 ;	

//extern vu8 update;
extern speed_temp;
extern vu8	Cam;
extern float	JTL;
void robotLineRunLeft(vu8 speed);
void robotLineRunRight(vu8 speed);
//======================Tinh Luc Ban & Goc Ban========================================

#define MOCCU 630     // Giá tri chuan tai giua sân
#define LUC_TAI_MOC 95 

#define LUC_MAX 150 
#define LUC_MIN 50
#define MAX_VI_TRI 20


//#define KHOANG_CACH_XA 500  // Ngu?ng kho?ng cách d? xác d?nh "xa"
//#define HESO_LUC_XA 0.9     // H? s? hi?u ch?nh l?c b?n khi ? xa
//#define CONG_THEM_LUC_XA 15


//#define KHOANG_CACH_XA_HON 600  // Ngu?ng kho?ng cách d? xác d?nh "xa"
//#define HESO_LUC_XA_HON 1           // H? s? hi?u ch?nh l?c b?n khi ? xa
//#define CONG_THEM_LUC_XA_HON 8

//#define lUC_BAN_VI_TRI_2_DIEM 30


int savedLucBan = 0;
extern float force;
float savedGocBan = 0;
int savedLazeValue = 0;
extern int lazeTraiValue ;

	
void updateLazeValue() {
   
    if (CB_NHAN_BONG_BO_BAN == 1) {
        
        lazeTraiValue; 
    }
}
void luu_bien_laze()
{
	if(CB_NHAN_BONG_BO_BAN == 1)
	{
		savedLazeValue = lazeTraiValue; 
	}
	else 
	{
		lazeTraiValue = savedLazeValue;
	}
}

void tinhLucBan(int lazeTraiValue) 
{
    float lucBan = 0;

    // Tính l?c b?n theo t? l? v?i kho?ng cách
    lucBan = LUC_TAI_MOC * ((float)lazeTraiValue / MOCCU);

    // Gi?i h?n giá tr? l?c b?n
    if (lucBan > LUC_MAX) {
        lucBan = LUC_MAX;
    } else if (lucBan < LUC_MIN) {
        lucBan = LUC_MIN;
    }

//    // Tính góc b?n
//    gocBan = GOC_TAI_MOC + ((float)(lazeTraiValue - MOCCU) / MOCCU) * (GOC_MAX - GOC_MIN);

//    if (lazeTraiValue > KHOANG_CACH_XA) {
//        gocBan *= HESO_GOC_XA;
//    }

//    if (lazeTraiValue > KHOANG_CACH_XA_HON) {
//        gocBan *= HESO_GOC_XA_HON;
//    }

//    if (gocBan > GOC_MAX) {
//        gocBan = GOC_MAX;
//    } else if (gocBan < GOC_MIN) {
//        gocBan = GOC_MIN;
//    }

    // Luu k?t qu?
    savedLucBan = lucBan;

    force = lucBan;
}

void Danh_sach_ban(int lazeTraiValue) 
{
    int range = 0;

  //Map Laze 
	//==========ngoai vao trong (1->4) // vi trí ban 3d cuoi san =================
    
		if 			(lazeTraiValue >= 531 && lazeTraiValue <= 630) {range = 1;} //	1 
		else if (lazeTraiValue >= 520 && lazeTraiValue <= 537) {range = 2;} // 	2
		else if (lazeTraiValue >= 505 && lazeTraiValue <= 510) {range = 3;} //	3
		else if (lazeTraiValue >= 517 && lazeTraiValue <= 522) {range = 4;} //	4
		else if (lazeTraiValue >= 538 && lazeTraiValue <= 539) {range = 5;} // 	5
		else if (lazeTraiValue >= 551 && lazeTraiValue <= 560) {range = 6;} // 	6
		else if (lazeTraiValue >= 561 && lazeTraiValue <= 570) {range = 7;} // 	7
		
		//============================!PENANTY!=======================================
		
//		else if (lazeTraiValue >= 330 && lazeTraiValue <= 338) {range = 8;} // 	8
//		
		//==========ngoai vao trong (1->4) // vi trí ban 3d cuoi san =================
		 else {
        // Neu ngoài pham vi, goi hàm tinhLucBan
        tinhLucBan(lazeTraiValue); 
        return; // Thoát sau khi x? lý
    }

    //Map Luc Ban
    switch (range) {case 1:  force = 73 ; break; //1 
//										case 2:  force = 228 ; break; //2
//										case 3:  force = 220	; break; // 3
//										case 4:  force = 235	; break; // 4
//										case 5:  force = 235	; break; // 5
//										case 6:  force = 240	; break; // 6
//										case 7:  force = 243	; break; // 7
//										case 8:  force = 165	; break; // PENANTY!
						default:
            break;
    }
}

//====================Vi Tri Ban Save==========================================
//	typedef struct {
//    float viTri;    // Giá tr? t? bi?n tr? laser
//    float lucBan;   // L?c b?n tuong ?ng
//    float gocBan;   // Góc b?n tuong ?ng
//} DuLieuBan;

//DuLieuBan danhSachBan[MAX_VI_TRI]; // M?ng luu d? li?u b?n
//int soLuongViTri = 0;              // S? lu?ng v? trí dã luu

//void luuGiaTriBan(float viTri, float lucBan, float gocBan) {
//    if (soLuongViTri < MAX_VI_TRI) {
//        danhSachBan[soLuongViTri].viTri = viTri;
//        danhSachBan[soLuongViTri].lucBan = lucBan;
//        danhSachBan[soLuongViTri].gocBan = gocBan;
//        soLuongViTri++;
//    }
//	}
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

	if (bientromamxoayCouter++ < 50)
	{
		bientromamxoay_SUM += bien_tro_nong_ban;
	}
	else
	{
		BienTroNongBanValue = bientromamxoay_SUM / 50;
		bientromamxoayCouter = 0;
		bientromamxoay_SUM = 0;
	}
	//-----------------------------------
	if (bientronangluaCouter++ < 50)
	{
		bientronanglua_SUM += bien_tro_xoay_nong;
	}
	else
	{
		BienTroXoayValue = bientronanglua_SUM / 50;
		bientronangluaCouter = 0;
		bientronanglua_SUM = 0;
	}
	//-----------------------------
	if (bientronangbongCouter++ < 50)
	{
		bientronangbong_SUM += bien_tro_xoay_nong;
	}
	else
	{
		bientronangbongValue = bientronangbong_SUM / 50;
		bientronangbongCouter = 0;
		bientronangbong_SUM = 0;
	}
}

// *****************************88 nang ha bo ban *********************************
void Nang_ha_bo_ban(vu8 speed)
{
	if( R1 && TRIANGLE)	Nong_Ban = speed, Nong_Ban_Up;
	
	else	if(R1 && X)	Nong_Ban = speed, Nong_Ban_Down;
	
	else					Nong_Ban = 2;
}

// *****************************88 nang ha bo ban *********************************
//******************** bang bong *************************
void banbong(void)
{
										if(CB_NHAN_BONG_BO_BAN == 0)
            				Ban_1 = 70, Ban_2 = 70, Ban_3 = 70;
										Ban_1_next, Ban_2_next, Ban_3_next;
										vTaskDelay(15000);
										XI_LANH_BAN_BONG_ON;
										vTaskDelay(8000);
  
										Ban_1 = 0, Ban_2 = 0, Ban_3 = 0;
										Ban_1_back, Ban_2_back, Ban_3_back;
										XI_LANH_BAN_BONG_OFF;

}
  void banbong_tu_dong(void)
{
										
										if(CB_NHAN_BONG_BO_BAN == 0)	
	            		  Ban_1 =  Ban_2 =  Ban_3 = force;
										Ban_1_next, Ban_2_next, Ban_3_next;
										vTaskDelay(13000);
										XI_LANH_BAN_BONG_ON;
										vTaskDelay(10000);
										Ban_1 = Ban_2 = Ban_3 = 0;
										XI_LANH_BAN_BONG_OFF;
										//XI_LANH_LAZE_OFF;
										//taget_BT_Nong_Ban = degree_F;
										XI_LANH_LAZE_OFF;
										
										
}

void test_gocban(void)
{
	taget_BT_Nong_Ban = degree_F;

}
//void test_goc2() {
//    float h = 1.5; // Chi?u cao c?m bi?n
//    float H = 2.0; // Chi?u cao m?c tiêu

//    float goc = tinhGoc(H, h, lazeTraiValue);
//}
//*****************************************************************
//	if(SQUARE){
//  if(ban_bong_state == 0){
//				Ban_1 =180, Ban_2 = 180, Ban_3 = 180;
//				Ban_1_next, Ban_2_next, Ban_3_next;
//				ban_bong_state = 1;    
//  }
//	else{
//				Ban_1 = 0, Ban_2 = 0, Ban_3 = 0;
//				ban_bong_state = 0;
//	}
//  while(SQUARE); 
// }


void Re_Bong(void) 
{
	int i;
	{	
			XI_LANH_RE_BONG_RA;//
			taget_BT_Nong_Ban = 350;
			//while(BienTroNongBanValue > 380 )		vTaskDelay(10);
			for(i=0;i<100;i++)	while(CB_XL_DAY_BONG_RA == 0 )  {if(wantExit()) break; vTaskDelay(1);}
			vTaskDelay(7000);//
			XI_LANH_DAY_BONG_RA;
			vTaskDelay(500);
		
			XI_LANH_KEP_MO;
			for(i=0;i<100;i++)	while(CB_TANG_BONG == 0) {if(wantExit()) break; vTaskDelay(1);}
			for(i=0;i<100;i++)	while(CB_TANG_BONG == 1) {if(wantExit()) break; vTaskDelay(1);}
		
			vTaskDelay(700);
			XI_LANH_DAY_BONG_VAO;
			for(i=0;i<100;i++)	while(CB_TANG_BONG == 0) {if(wantExit()) break; vTaskDelay(1);}
			
			vTaskDelay(1500);
		
			XI_LANH_KEP_DONG;
			vTaskDelay(1000);
			XI_LANH_RE_BONG_VAO;//
	 		for(i=0;i<100;i++)	while(CB_XL_DAY_BONG_VAO == 0) {if(wantExit()) break; vTaskDelay(1);}
	}
}					  				  
 

 


//void Re_Bong(vu8 speed) {    
//   // Ki?m tra n?u nh?n phím L1
//        while (L1) { // T?o vòng l?p vô h?n d? mô t? hành d?ng nh?i bóng
//            if (CB_TANG_BONG == 0) { 
//                // Khi don bong vao
//                XI_LANH_THA_BONG_ON; 
//                XI_LANH_DAY_BONG_VAO;
//							  delay_ms(500);
//							  XI_LANH_KEP_MO; 
//                XI_LANH_DAY_BONG_RA;
//            }

//            if (CB_TANG_BONG == 1) { 
//                // Khi không có bóng, thuc hien:
//								// nha ra
//								XI_LANH_KEP_MO; 
//                XI_LANH_DAY_BONG_RA;
//            }
//            // Ki?m tra l?i tr?ng thái nút L1, n?u không nh?n n?a, thoát vòng l?p
//            if (!L1) {
//                break;
//            }
//					}
//				

////    static bool bong = false;  

////    if (L1&&CB_TANG_BONG==1) {	
////        Ban_1 = 40, Ban_2 = 40, Ban_3 = 40;
////			Ban_1_back, Ban_2_back, Ban_3_back;
////			
////        bong = false;  
////    } 
////    else if (!bong && CB_NHAN_BONG == 1) {
////        
////        XI_LANH_KEP_BONG_OFF;
////        bong = true;  
////    } 
////    else if (bong && CB_NHAN_BONG == 1) {
////        XI_LANH_THA_BONG_ON;
////        bong = false;  
////    } 
////		else if(O)
////		{
////			Ban_1 = 40, Ban_2 = 40, Ban_3 = 40;
////			Ban_1_back, Ban_2_back, Ban_3_back;
////		}
////    else if (L2) {
////        Ban_1 = 0, Ban_2 = 0, Ban_3 = 0;
////    }

//}

void Lay_bong()
{
	if(laybong == 0)
	{
		XI_LANH_KEP_DONG;
		XI_LANH_RE_BONG_VAO;
	}
	if(laybong ==1 ) 
	{		XI_LANH_RE_BONG_RA;
		if(CB_XL_DAY_BONG_RA)
		{
			XI_LANH_KEP_MO;
		}
			//
	}
	if(laybong == 2) 
	{		
			XI_LANH_KEP_DONG;
		  //vTaskDelay(3000);
		  XI_LANH_RE_BONG_VAO;
		laybong = 0;
	}
	if (laybong == 3)
	{
		if(CB_NHAN_BONG_BO_BAN == 0)
		XI_LANH_RE_BONG_RA;
		XI_LANH_KEP_DONG;
	}
}	
void lay()
{
	if(!R1&&X)
	{
		while(X)
		vTaskDelay(30);
		laybong++;		
	}
}
	

//*********************** ÐUA BÓNG VÀO PHAN BAN ***************************
void dua_bong(void)
     {			
		int i; 
//		XI_LANH_LAZE_ON;
		Ban_1 = 62 ,   Ban_2 = 62,  Ban_3 = 62;
		Ban_1_back, Ban_2_back, Ban_3_back;
//		while(BienTroNongBanValue > 380 )		 {if(wantExit()) break; vTaskDelay(1);}
//		XI_LANH_KEP_MO;
		vTaskDelay(1500);
//		for(i=0;i<100;i++)	while( CB_NHAN_BONG_BO_BAN == 1)  {if(wantExit()) break; vTaskDelay(1);}
//		Ban_1 = 0, Ban_2 = 0, Ban_3 = 0;
//		Ban_1_back, Ban_2_back, Ban_3_back;
//		XI_LANH_KEP_DONG;
		//XI_LANH_RE_BONG_RA;
//		taget_BT_Nong_Ban = degree_F;
		
		//force = savedLucBan;
		//laybong = 1;
		//laybong = 3;
}


//**********************************************************************
void banxoay(vu8 speed)
{
	 if (L1 && SQUARE)													  Mor_CamRotate = speed, Mor_CamRotate_next;
	 else if (L1 && O) 	                          Mor_CamRotate = speed, Mor_CamRotate_back;
	 else	                                        Mor_CamRotate = 2;
}
 void nangcam(vu8 speed)
 {
	 if (TRIANGLE)													Mor_NangHa = speed, Mor_Nang;
	 else if (X && CB_HOME_NANG_HA == 1) 		Mor_NangHa = speed, Mor_Ha;
	 else																		Mor_NangHa = 2;
 }
 
 
// void tim_ro(void)
//{
//	if(R2)
//	{
//		if(Cam > 101)					Mor_CamRotate = 10, Mor_CamRotate_next;
//		else if(Cam < 99)		  Mor_CamRotate = 10, Mor_CamRotate_back;
//		else									Mor_CamRotate = 2;
//	}
//}
//**********************************************************************

//void xl_nang_kep_bong()
//{
//	if (R1)
//	{
//		
//		XI_LANH_THA_BONG_ON;		
//		XI_LANH_DAY_BONG_RA;
//		XI_LANH_RE_BONG_RA;
//		XI_LANH_KEP_DONG;
//		XI_LANH_BAN_BONG_ON;
//		
//	}
//	else if (R2) {
////		XI_LANH_THA_BONG_OFF;		
////		XI_LANH_DAY_BONG_VAO;
////		XI_LANH_RE_BONG_VAO;
////		XI_LANH_KEP_MO;
////		XI_LANH_BAN_BONG_OFF;
//	}
//}	

void nang_ha_nong_ban(void)
{
	if(R1 && TRIANGLE)				state_nang = 1, state_ha = 0, taget_BT_Nong_Ban = 615, lock_nang = 0;
	
	if( R1 && X){
	target_BT_Xoay = 520;
	while(BienTroXoayValue<= 540 && BienTroXoayValue >= 505) {if(wantExit()) break; vTaskDelay(1);}	
	taget_BT_Nong_Ban = 52 , lock_nang = 0;
	}
	else if (taget_BT_Nong_Ban <=55   && state_ha == 0 && BienTroNongBanValue < 65 ){
	state_nang = 0;  
	state_ha = 1;
	}
}
//  void test_nang_ha_nong_ban(vu8 speed)
//{
//	if(TRIANGLE)				state_nang = 1, state_ha = 0, taget_BT_Nong_Ban = 1000;
//	
//	if(X)
//	{		
//		taget_BT_Nong_Ban = 160;
//	}
//	else if (taget_BT_Nong_Ban == 160 && state_ha == 0 && BienTroNongBanValue < 180 ){
//	
//	state_nang = 0;
//	state_ha = 1;
//	}
//}
//void ban_bong()
//{
//if (R2) {			Ban_1 = 100, Ban_2 = 100, Ban_3 = 100;
//								Ban_1_next, Ban_2_next, Ban_3_next;
//}
//else 	{			Ban_1 = 0, Ban_2 = 0, Ban_3 = 0;
//						Ban_1_next, Ban_2_next, Ban_3_next;
//}

//}
//-----------------------------------------RESET MAM XOAY-----------------------------------------------------
void Giu_Nong_Ban()
{
	if (taget_BT_Nong_Ban < Min_BT_Nong_Ban)
		taget_BT_Nong_Ban = Min_BT_Nong_Ban;
	if (taget_BT_Nong_Ban > Max_BT_Nong_Ban)
		taget_BT_Nong_Ban = Max_BT_Nong_Ban;

	if (abs(BienTroNongBanValue - taget_BT_Nong_Ban) > 5 && lock_nang == 0)
	{
		speed_temp = abs(BienTroNongBanValue - taget_BT_Nong_Ban);
		if (BienTroNongBanValue > taget_BT_Nong_Ban)
		{
			Nong_Ban_Down;
			if (speed_temp > 50) 
				speed_temp = 50; 	
			if (speed_temp < 30)  
					speed_temp = 30;
		}
		else 
		{
			Nong_Ban_Up;
			if (speed_temp > 100) 
				speed_temp = 100;
			if (speed_temp < 30)  
				speed_temp = 30;
		}
		Nong_Ban = speed_temp; 
	}
	else  
	{
		Nong_Ban = 2;
		lock_nang = 1;
	}

	if (state_nang == 0)  
		Nong_Ban = 0;
}


void Xoay_Nong_Ban()
{
	if (target_BT_Xoay < Min_BT_Xoay )
		target_BT_Xoay = Min_BT_Xoay;
	if (target_BT_Xoay > Max_BT_Xoay)
		target_BT_Xoay = Max_BT_Xoay;

	if (abs(BienTroXoayValue - target_BT_Xoay) > 1)
	{
		if (BienTroXoayValue > target_BT_Xoay)
			Mor_CamRotate_back;
		else
			Mor_CamRotate_next;

		speed_temp = abs(BienTroXoayValue - target_BT_Xoay);
		if (speed_temp > 10) // 50
			speed_temp = 10;
		if (speed_temp < 3 ) 							
			speed_temp = 3;
		Mor_CamRotate = speed_temp;
	}
	else
		Mor_CamRotate = 2;
}

void test_nang_ha_nong_ban(void)
{
	if (R1 && X && (taget_BT_Nong_Ban < Max_BT_Nong_Ban))
		taget_BT_Nong_Ban++, vTaskDelay(1000);
	else if (R1 && TRIANGLE && (taget_BT_Nong_Ban > Min_BT_Nong_Ban))
		taget_BT_Nong_Ban--, vTaskDelay(1000);
}

//***************************** xoay nong ban bang tay **************************************
//void Xoay_nong_ban(vu8 speed)
//{
//	if(R1 && SQUARE)					Mor_CamRotate = speed, Mor_CamRotate_next;
//	else	if(R1 && O)					Mor_CamRotate = speed, Mor_CamRotate_back;
//	else											Mor_CamRotate = 2;
//}
void Xoay_nong (void)
{
	if (R1 && O && (target_BT_Xoay < Max_BT_Xoay))
		target_BT_Xoay++, vTaskDelay(300);
	else if (R1 && SQUARE && (target_BT_Xoay > Min_BT_Xoay))
		target_BT_Xoay--, vTaskDelay(300);
}
void xoay_goc_tu_dong(int angle)
{
	robotRotate(angle, 0.2,0);
//		if (!R1 && O && (angle < Max_BT_Xoay))
//		target_BT_Xoay++ , vTaskDelay(500);
//	else if (!R1 && O && (target_BT_Xoay > Min_BT_Xoay))
//		target_BT_Xoay--, vTaskDelay(500);
}
void ban_bong()
{
	
		if(CB_NHAN_BONG_BO_BAN == 0 && taget_BT_Nong_Ban >= 900) 
		{
//		taget_BT_Nong_Ban = 1000;
//		while(BienTroNongBanValue > 970 )		 {if(wantExit()) break; vTaskDelay(1);}
//		vTaskDelay(10000);			
		Ban_1 = 155,  Ban_2 = 155 ,  Ban_3 = 155;    
		Ban_1_next, Ban_2_next, Ban_3_next;
		vTaskDelay(10000);
		XI_LANH_BAN_BONG_ON;
		vTaskDelay(10000);
		Ban_1 = 0 ,   Ban_2 = 0 ,  Ban_3 = 0;
		Ban_1_next, Ban_2_next, Ban_3_next;
		XI_LANH_BAN_BONG_OFF;
		XI_LANH_NONG_BAN_OFF;
		//taget_BT_Nong_Ban = 170;
  	//target_BT_Xoay = 766;
	}
}
void ban()
{
	if(TOUCHPAD)
	while(TOUCHPAD)
	vTaskDelay(30);
	touchpad_press++;
}

void Test_Xoay(vu8 speed)
{
	if(R1 && O)
	{
		Mor_CamRotate = speed, Mor_CamRotate_next;
	}
	else if (R1 && SQUARE)
	{
		Mor_CamRotate = speed, Mor_CamRotate_back;
	}
	else Mor_CamRotate = 0;
}



//=======================Nap Bong=====================================================
 void nap_bong(void)
 {			
		int i; 		
		Ban_1 = Ban_2 = Ban_3 = 20;
		Ban_1_back, Ban_2_back, Ban_3_back;
		vTaskDelay(10);
		for(i=0;i<100;i++)	while(CB_NHAN_BONG_BO_BAN != 1 )
		{
		Xoay_nong();
		if(wantExit()) break; vTaskDelay(1);	
		}
		Ban_1 = 0, Ban_2 = 0, Ban_3 = 0;
		Ban_1_back, Ban_2_back, Ban_3_back;
		
		
}
  //{if(wantExit()) break; vTaskDelay(1);}	
 
//	taget_BT_Nong_Ban = 975;
//	state_nang = 1, state_ha = 0,lock_nang = 0;
		//taget_BT_Nong_Ban = 1000;
		//state_nang = 1, state_ha = 0;
		//taget_BT_Nong_Ban = 1000;
		//while(BienTroNongBanValue > 1001 )		 {if(wantExit()) break; vTaskDelay(1);}
		//vTaskDelay(1500);

void reset_ham()
{
	if(L2 &&  CB_NHAN_BONG_BO_BAN == 1)
	{
		Ban_1 = 0, Ban_2 = 0, Ban_3 = 0;
		Ban_1_back, Ban_2_back, Ban_3_back;
		//XI_LANH_NONG_BAN_OFF;
		//taget_BT_Nong_Ban = 35;
		state_ha = 0;
		state_nang = 0;
		//lock_nang = 0;				
	}
}




void Ban_Bong_Can_Luc()
{
	
		if(CB_NHAN_BONG_BO_BAN == 0 ) 
		{
 		//taget_BT_Nong_Ban = 475;
		//while(BienTroNongBanValue > 500 )		 {if(wantExit()) break; vTaskDelay(1);}
		//vTaskDelay(10000);
		lock_nang = 1;
		Ban_1 = Ban_2 =  Ban_3 = power_shot; //force , power ,power_shot
		Ban_1_next, Ban_2_next, Ban_3_next;
		vTaskDelay(13000);
			
		XI_LANH_BAN_BONG_ON;
		vTaskDelay(10000);
		Ban_1 = 0 ,   Ban_2 = 0 ,  Ban_3 = 0;
		Ban_1_next, Ban_2_next, Ban_3_next;
		XI_LANH_BAN_BONG_OFF;
		XI_LANH_NONG_BAN_OFF;
//		vTaskDelay(8000);
//		target_BT_Xoay = 520;
//		state_ha = 1;
//		state_nang = 0;
//		lock_nang = 0;
//  	target_BT_Xoay = 766;
	}
}
void Xoay_nong_tu_chinh(vu8 speed)
{
	if(R1 + O)                  Mor_CamRotate = speed, Mor_CamRotate_next;
	else if (R1 + SQUARE)				Mor_CamRotate = speed, Mor_CamRotate_next;
	else												Mor_CamRotate = 2;
}


///############################# CACULATOR POWER SHOT ################################################################
void TinhToanLucBan(int lazeTraiValue)
{
	float shot = 0;
	float LucMin = 58;
	float KhoangCachMin = 390 ;
	float KhoangCachLuc = 5;
	float UpdateLuc = 1; 
    shot = LucMin + ((float)(lazeTraiValue - KhoangCachMin) / KhoangCachLuc)*UpdateLuc ;	 
		if(lazeTraiValue >= 500) 
		{
		shot =(int) shot;
		shot += 2;
		}
		power_shot = shot;
}
//############################# DATA POWER FROM EXCEL   #########################################################
void All_Data_Power(int lazeTraiValue) {
    int range = 0;
	
    if 			(lazeTraiValue >= 395 && lazeTraiValue <= 398) { range = 1; power_shot = 60; }
    else if (lazeTraiValue >= 399 && lazeTraiValue <= 402) { range = 2; power_shot = 62; }
    else if (lazeTraiValue >= 403 && lazeTraiValue <= 406) { range = 3; power_shot = 64; }
    else if (lazeTraiValue >= 407 && lazeTraiValue <= 410) { range = 4; power_shot = 66; }
    else if (lazeTraiValue >= 411 && lazeTraiValue <= 414) { range = 5; power_shot = 68; }
    else if (lazeTraiValue >= 415 && lazeTraiValue <= 418) { range = 6; power_shot = 70; }
    else if (lazeTraiValue >= 419 && lazeTraiValue <= 422) { range = 7; power_shot = 72; }
    else if (lazeTraiValue >= 423 && lazeTraiValue <= 426) { range = 8; power_shot = 74; }
    else if (lazeTraiValue >= 427 && lazeTraiValue <= 430) { range = 9; power_shot = 76; }
    else if (lazeTraiValue >= 431 && lazeTraiValue <= 434) { range = 10; power_shot	= 78; }
    else if (lazeTraiValue >= 435 && lazeTraiValue <= 438) { range = 11; power_shot = 80; }
    else if (lazeTraiValue >= 439 && lazeTraiValue <= 442) { range = 12; power_shot = 82; }
    else if (lazeTraiValue >= 443 && lazeTraiValue <= 446) { range = 13; power_shot = 84; }
    else if (lazeTraiValue >= 447 && lazeTraiValue <= 450) { range = 14; power_shot = 86; }
    else if (lazeTraiValue >= 451 && lazeTraiValue <= 454) { range = 15; power_shot = 87; }
    else if (lazeTraiValue >= 455 && lazeTraiValue <= 458) { range = 16; power_shot = 88; }
    else if (lazeTraiValue >= 459 && lazeTraiValue <= 462) { range = 17; power_shot = 89; }
    else if (lazeTraiValue >= 463 && lazeTraiValue <= 466) { range = 18; power_shot = 89; }
    else if (lazeTraiValue >= 467 && lazeTraiValue <= 470) { range = 19; power_shot = 89; }
    else if (lazeTraiValue >= 471 && lazeTraiValue <= 474) { range = 20; power_shot = 88; }
    else if (lazeTraiValue >= 475 && lazeTraiValue <= 478) { range = 21; power_shot = 90; }
    else {
        TinhToanLucBan(lazeTraiValue); 
        return;
    }
}


