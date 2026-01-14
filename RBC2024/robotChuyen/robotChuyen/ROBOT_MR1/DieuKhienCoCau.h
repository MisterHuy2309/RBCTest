// *****************************8 bien toan cuc *************************************
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
int state_xl_on = 0;
int state_xl_off = 1;
//extern vu8 update;
extern speed_temp;
extern vu8	Cam;
extern float	JTL;
void robotLineRunLeft(vu8 speed);
void robotLineRunRight(vu8 speed);
//======================Tinh Luc Ban & Goc Ban========================================

#define MOCCU 530     // Gi� tri chuan tai giua s�n
#define LUC_TAI_MOC 200
#define GOC_TAI_MOC 380

#define LUC_MAX 240  
#define LUC_MIN 100
#define MAX_VI_TRI 20

#define GOC_MAX 380
#define GOC_MIN 250


#define KHOANG_CACH_XA 500  // Ngu?ng kho?ng c�ch d? x�c d?nh "xa"
#define HESO_LUC_XA 0.9 
#define HESO_GOC_XA 0.9	// H? s? hi?u ch?nh l?c b?n khi ? xa
#define CONG_THEM_LUC_XA 15


#define KHOANG_CACH_XA_HON 600  // Ngu?ng kho?ng c�ch d? x�c d?nh "xa"
#define HESO_LUC_XA_HON 1           // H? s? hi?u ch?nh l?c b?n khi ? xa
#define CONG_THEM_LUC_XA_HON 8
#define HESO_GOC_XA_HON 1

#define lUC_BAN_VI_TRI_2_DIEM 30


int savedLucBan = 0;
extern float force;
float savedGocBan = 0;
int savedLazeValue = 0;
extern int lazeTraiValue ;
extern float degree_F;
	
void updateLazeValue() {
   
    if (CB_NHAN_BONG_BO_BAN == 1) {
        
        lazeTraiValue; 
    }
}
//void luu_bien_laze()
//{
//	if(CB_NHAN_BONG_BO_BAN == 1)
//	{
//		savedLazeValue = UWB; 
//	}
//	else 
//	{
//		UWB = savedLazeValue;
//	}
//}

void tinhLucBan(int UWB) 
{
    float lucBan = 0;
		float gocBan = 0;
    // T�nh l?c b?n theo t? l? v?i kho?ng c�ch
    lucBan = LUC_TAI_MOC * ((float)UWB / MOCCU);

    // Gi?i h?n gi� tr? l?c b?n
    if (lucBan > LUC_MAX) {
        lucBan = LUC_MAX;
    } else if (lucBan < LUC_MIN) {
        lucBan = LUC_MIN;
    }

//    // T�nh g�c b?n
    gocBan = GOC_TAI_MOC + ((float)(UWB - MOCCU) / MOCCU) * (GOC_MAX - GOC_MIN);

//    if (UWB > KHOANG_CACH_XA) {
//        gocBan *= HESO_GOC_XA;
//    }

//    if (UWB > KHOANG_CACH_XA_HON) {
//        gocBan *= HESO_GOC_XA_HON;
//    }

    if (gocBan > GOC_MAX) {
        gocBan = GOC_MAX;
    } else if (gocBan < GOC_MIN) {
        gocBan = GOC_MIN;
    }

    // Luu k?t qu?

    force = lucBan;
		degree_F = gocBan;
}

void Danh_sach_ban(int lazeTraiValue) 
{
    int range = 0;

  //Map Laze 
	//==========ngoai vao trong (1->4) // vi tr� ban 3d cuoi san =================
    
		if 			(lazeTraiValue >= 540 && lazeTraiValue <= 630) {range = 1;} //	1 
//		else if (lazeTraiValue >= 520 && lazeTraiValue <= 537) {range = 2;} // 	2
//		else if (lazeTraiValue >= 505 && lazeTraiValue <= 510) {range = 3;} //	3
//		else if (lazeTraiValue >= 517 && lazeTraiValue <= 522) {range = 4;} //	4
//		else if (lazeTraiValue >= 538 && lazeTraiValue <= 539) {range = 5;} // 	5
//		else if (lazeTraiValue >= 551 && lazeTraiValue <= 560) {range = 6;} // 	6
//		else if (lazeTraiValue >= 561 && lazeTraiValue <= 570) {range = 7;} // 	7
		
		//============================!PENANTY!=======================================
		
//		else if (lazeTraiValue >= 330 && lazeTraiValue <= 338) {range = 8;} // 	8
//		
		//==========ngoai vao trong (1->4) // vi tr� ban 3d cuoi san =================
		 else {
        // Neu ngo�i pham vi, goi h�m tinhLucBan
        tinhLucBan(lazeTraiValue); 
        return; // Tho�t sau khi x? l�
    }

    //Map Luc Ban
    switch (range) {case 1:  force = 170 ; break; //1 
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
//    float viTri;    // Gi� tr? t? bi?n tr? laser
//    float lucBan;   // L?c b?n tuong ?ng
//    float gocBan;   // G�c b?n tuong ?ng
//} DuLieuBan;

//DuLieuBan danhSachBan[MAX_VI_TRI]; // M?ng luu d? li?u b?n
//int soLuongViTri = 0;              // S? lu?ng v? tr� d� luu

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
	
	static unsigned int UWBCouter = 0, UWB_SUM = 0;

	// Bien tro vi tri co cau
	static unsigned int bientromamxoayCouter = 0, bientromamxoay_SUM = 0;
	static unsigned int bientronangluaCouter = 0, bientronanglua_SUM = 0;
	static unsigned int bientronangbongCouter = 0, bientronangbong_SUM = 0;
	////----------------TINH TOAN LAZER---------------
//	if (lazeSauCouter++ < 100)
//	{
//		lazeSau_SUM += cam_bien_laze_sau;
//	}
//	else
//	{
//		lazeSauValue = lazeSau_SUM / 100;
//		lazeSauCouter = 0;
//		lazeSau_SUM = 0;
//	}
//	//-------------------------------------------
//	if (lazeTruocCouter++ < 100)
//	{
//		lazeTruoc_SUM += cam_bien_laze_truoc;
//	}
//	else
//	{
//		lazeTruocValue = lazeTruoc_SUM / 100;
//		lazeTruocCouter = 0;
//		lazeTruoc_SUM = 0;
//	}
//	//------------------------------
//	if (lazePhaiCouter++ < 100)
//	{
//		lazePhai_SUM += cam_bien_laze_phai;
//	}
//	else
//	{
//		lazePhaiValue = lazePhai_SUM / 100;
//		lazePhaiCouter = 0;
//		lazePhai_SUM = 0;
//	}
//	//-----------------------------------------
//	if (lazeTraiCouter++ < 120)
//	{
//		lazeTrai_SUM += cam_bien_laze_trai;
//	}
//	else
//	{
//		lazeTraiValue = lazeTrai_SUM / 120;
//		lazeTraiCouter = 0;
//		lazeTrai_SUM = 0;
//	}
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
	
	//-----------------------------
	if (UWBCouter++ < 300)
	{
		UWB_SUM += UWB;
	}
	else
	{
		UWBValue = UWB_SUM / 300;
		UWBCouter = 0;
		UWB_SUM = 0;
	}
}

// *****************************88 nang ha bo ban *********************************
void Nang_ha_bo_ban(vu8 speed)
{
	if( R1 && TRIANGLE)	Nong_Ban = speed, Nong_Ban_Up;
	
	else	if(R1 && X)	Nong_Ban = speed, Nong_Ban_Down;
	
	else					Nong_Ban = 0;
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
//    float H = 2.0; // Chi?u cao m?c ti�u

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
//   // Ki?m tra n?u nh?n ph�m L1
//        while (L1) { // T?o v�ng l?p v� h?n d? m� t? h�nh d?ng nh?i b�ng
//            if (CB_TANG_BONG == 0) { 
//                // Khi don bong vao
//                XI_LANH_THA_BONG_ON; 
//                XI_LANH_DAY_BONG_VAO;
//							  delay_ms(500);
//							  XI_LANH_KEP_MO; 
//                XI_LANH_DAY_BONG_RA;
//            }

//            if (CB_TANG_BONG == 1) { 
//                // Khi kh�ng c� b�ng, thuc hien:
//								// nha ra
//								XI_LANH_KEP_MO; 
//                XI_LANH_DAY_BONG_RA;
//            }
//            // Ki?m tra l?i tr?ng th�i n�t L1, n?u kh�ng nh?n n?a, tho�t v�ng l?p
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
	

//*********************** �UA B�NG V�O PHAN BAN ***************************
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
	 if (L1 && SQUARE)													  XI_LANH = speed, XI_LANH_ON;
	 else if (L1 && O) 	                          XI_LANH = speed, XI_LANH_OFF;
	 else	                                        XI_LANH = 2;
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
//		if(Cam > 101)					XI_LANH = 10, XI_LANH_ON;
//		else if(Cam < 99)		  XI_LANH = 10, XI_LANH_OFF;
//		else									XI_LANH = 2;
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

//void nang_ha_nong_ban(void)
//{
//	if(R1 && TRIANGLE)				state_nang = 1, state_ha = 0, taget_BT_Nong_Ban = 605, lock_nang = 0;

//	if(R1 && X)
//	{		
//		taget_BT_Nong_Ban = 54 , lock_nang = 0;
//	}   
//	else if (taget_BT_Nong_Ban <=54  && state_ha == 0 && BienTroNongBanValue < 60 ){
//	state_nang = 0;
//	state_ha = 1;
//	}
//}
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

	if (abs(BienTroNongBanValue - taget_BT_Nong_Ban) > 5 )
	{
		if (BienTroNongBanValue > taget_BT_Nong_Ban)
			Nong_Ban_Down;
		else
			Nong_Ban_Up;

		speed_temp = abs(BienTroNongBanValue - taget_BT_Nong_Ban)*15;
		if (speed_temp > 250) // 250
			speed_temp = 250;
		if (speed_temp < 10)  // 200
			speed_temp = 10;

		Nong_Ban = speed_temp;
	}
	else  Nong_Ban = 0 ;
}

void Xoay_Nong_Ban()
{
	if (target_BT_Xoay < Min_BT_Xoay )
		target_BT_Xoay = Min_BT_Xoay;
	if (target_BT_Xoay > Max_BT_Xoay)
		target_BT_Xoay = Max_BT_Xoay;

	if (abs(BienTroXoayValue - target_BT_Xoay) )
	{
		if (BienTroXoayValue > target_BT_Xoay)
			XI_LANH_OFF;
		else
			XI_LANH_ON;

		speed_temp = abs(BienTroXoayValue - target_BT_Xoay);
		if (speed_temp > 8) // 50
			speed_temp = 8;
		if (speed_temp < 6 ) 							
			speed_temp = 6;
		XI_LANH = speed_temp;
	}
	else
		XI_LANH = 0;
}

void test_nang_ha_nong_ban(void)
{
	if (R1 && X && (taget_BT_Nong_Ban < Max_BT_Nong_Ban))
		taget_BT_Nong_Ban++, vTaskDelay(300);
	else if (R1 && TRIANGLE && (taget_BT_Nong_Ban > Min_BT_Nong_Ban))
		taget_BT_Nong_Ban--, vTaskDelay(300);
}

//***************************** xoay nong ban bang tay **************************************
//void Xoay_nong_ban(vu8 speed)
//{
//	if(R1 && SQUARE)					XI_LANH = speed, XI_LANH_ON;
//	else	if(R1 && O)					XI_LANH = speed, XI_LANH_OFF;
//	else											XI_LANH = 2;
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

void Kich_van(vu8 speed)
	{
		if(state_xl_on == 1)
		{	
			XI_LANH = speed, XI_LANH_ON;
		}
		else if (state_xl_off == 1)
		{
		  XI_LANH = speed,	XI_LANH_OFF;
		}
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
		XI_LANH = speed, XI_LANH_ON;
	}
	else if (R1 && SQUARE)
	{
		XI_LANH = speed, XI_LANH_OFF;
	}
	else XI_LANH = 0;
}



//=======================Nap Bong=====================================================
 void nap_bong(void)
 {			
		int i; 		
		Ban_1 = 20 , Ban_2 = 20,  Ban_3 = 20;
		Ban_1_back, Ban_2_back, Ban_3_back;
//		XI_LANH_NONG_BAN_ON;
//		taget_BT_Nong_Ban = 975;
//		state_nang = 1, state_ha = 0,lock_nang = 0;
		//taget_BT_Nong_Ban = 1000;
		//state_nang = 1, state_ha = 0;
		//taget_BT_Nong_Ban = 1000;
		//while(BienTroNongBanValue > 1001 )		 {if(wantExit()) break; vTaskDelay(1);}
		vTaskDelay(1500);
		for(i=0;i<100;i++)	while( CB_NHAN_BONG_BO_BAN == 1 )  {if(wantExit()) break; vTaskDelay(1);}	
		Ban_1 = 0, Ban_2 = 0, Ban_3 = 0;
		Ban_1_back, Ban_2_back, Ban_3_back;
		
		
}

void reset_ham()
{
	if(L2 &&  CB_NHAN_BONG_BO_BAN == 1)
	{
		Ban_1 = 0, Ban_2 = 0, Ban_3 = 0;
		Ban_1_back, Ban_2_back, Ban_3_back;
		XI_LANH_NONG_BAN_OFF;
		taget_BT_Nong_Ban = 35;
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
		Ban_1 = Ban_2 =  Ban_3 = force;
		Ban_1_next, Ban_2_next, Ban_3_next;
		vTaskDelay(13000);
		XI_LANH_BAN_BONG_ON;
		vTaskDelay(10000);
		Ban_1 = 0 ,   Ban_2 = 0 ,  Ban_3 = 0;
		Ban_1_next, Ban_2_next, Ban_3_next;
//		vTaskDelay(5000);
//		taget_BT_Nong_Ban = 55;
//		state_ha = 1;
//		state_nang = 0;
//		lock_nang = 0;
//  	target_BT_Xoay = 766;
	}
}

void CHUYENBANH(void)
{
										if(CB_NHAN_BONG_BO_BAN == 0)
            				Ban_1 = Ban_2 = Ban_3 =luc_now;//luc_now , 100
										Ban_1_next, Ban_2_next, Ban_3_next;
										vTaskDelay(10000);
										XI_LANH_OFF;
										XI_LANH = 254;
										vTaskDelay(10000);
										Ban_1 = 0, Ban_2 = 0, Ban_3 = 0;
										Ban_1_back, Ban_2_back, Ban_3_back;
										XI_LANH = 0;
}
void TatLaze()
{
	if (L2 && CB_NHAN_BONG_BO_BAN ==1 )	XI_LANH = 0;
		
}
float tocdoXoaytrack = 0.2;	
void xoaytam(float received_offset)
{			
	
	if (R2){
    if (received_offset >= 98 && received_offset <= 102) {
        robotStop(10);
    } else if (received_offset < 98) {
        robotRotateFree(-tocdoXoaytrack, 0); // Xoay thu?n
    } else if (received_offset > 102) {
        robotRotateFree(tocdoXoaytrack, 0); // Xoay ngu?c l?i
    }
	}
}
	
void nap_banh(void)
 {			
		int i; 		
		Ban_1 = Ban_2 = Ban_3 = 35;
		Ban_1_back, Ban_2_back, Ban_3_back;
		vTaskDelay(5000);
		for(i=0;i<100;i++)	while( CB_NHAN_BONG_BO_BAN == 1 )  {if(wantExit()) break; vTaskDelay(1);}	
		Ban_1 = 0, Ban_2 = 0, Ban_3 = 0;
		Ban_1_back, Ban_2_back, Ban_3_back;
		XI_LANH = 254, XI_LANH_ON;
		//degree_F = taget_BT_Nong_Ban;
}
 
float tinhLucChuyen(){
	int mang_khoang_cach_co_dinh[7] = {150, 200, 250, 300, 350, 400,450};
	int mang_luc_co_dinh[7] = 						{88, 98, 106, 105, 112, 116,125}; // cho khoang cach 150,200,250,300,350,400,450
	float luc_temp = 0;
	float goc_temp;
	float UWB_sub_150 = 0;
	int he_so_goc = 0;
	int khoang_cach_thay_goc = 50; 
	int so_goc_mot_lan_doi = 10;
	
	if((UWBValue - 500) > 5 || (150 - UWBValue) > 5 ) return 0;
	
	UWB_sub_150 = UWBValue - 150;
	he_so_goc = (int) (UWB_sub_150/khoang_cach_thay_goc);
	if (he_so_goc == 0) {
		goc_temp = Min_BT_Nong_Ban;  
	}
	else{
		goc_temp = Min_BT_Nong_Ban + he_so_goc*so_goc_mot_lan_doi;
	}
	luc_temp =  mang_luc_co_dinh[he_so_goc] + (UWBValue - mang_khoang_cach_co_dinh[he_so_goc])/10*2;
	
	taget_BT_Nong_Ban = goc_temp;
	luc_now = luc_temp;
	return luc_temp;
	
	
	
	
//	//chinh nong ban
//	if (abs(UWBValue - 360) > 15){
//		if(UWBValue  < 360){
//			taget_BT_Nong_Ban = 260;
//			luc_temp = luc_ban_uwb_250 + (UWBValue - 250)/10*2;
//		}
//		else{
//			taget_BT_Nong_Ban = 280;
//			luc_temp = luc_ban_uwb_360 + (UWBValue - 360)/10*2;
//		}
//	}
//	else {
//		taget_BT_Nong_Ban = 280;
//		luc_temp = luc_ban_uwb_360;
//	}
//	luc_now = luc_temp;
	

}
 
			

void RobotAutoRun (int UWB,int TocDoChay)
{
		if(UWB >= 300 )
		{
			robotRun(0,TocDoChay);
		}
		 else
		{
			robotStop(0);
		}
}