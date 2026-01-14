//*****************************8 bien toan cuc *************************************
#include <math.h>
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
int static_ban = 0; 
int lazeTraiValue_Ban = 0;
int layMauBT = 0;
int GT_LAZE_BAN = 0;
int lay_mau_bt_1,lay_mau_bt_2,lay_mau_laser_1,lay_mau_laser_2;
double NuaChuvi , ChieucaoAH , Khoangcachtam , radians_goc , CosGoc , GocLech;
char lock_nang = 0;
int mau_bien_tro,gtrilaze;
int state_nap_bong =1;
int da_lay_mau=0;
int donvixoay;
int giam_luc = 1;
int xl_kepbong_state = 0;
int xl_nangkep_state = 0;
int ban_bong_state=0 ;	
int CanhBang = 180;
int xoay_mam =0, savelaze_1 = 0 , savelaze_2 = 0 , Laze_1 = 0 , Laze_2 = 0;
int thulaze = 100;
int Luu_luc = 0;
int sta_nap =0;
int ERR;//extern vu8 update;
extern speed_temp;
extern vu8	Cam;
extern float	JTL;
int tocDoNongBan = 0;
void robotLineRunLeft(vu8 speed);
void robotLineRunRight(vu8 speed);
int angleJoy = 0;
int speedJoy = 0;
extern float power;
int Lucbanbandau = 0;
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void TinhToanLucBan()
{
	float shot = 0;
	float LucMin = 94;
	float KhoangCachMin = 437  ;
	float KhoangCachLuc = 4;
	float UpdateLuc = 1; 
    shot = LucMin + ((float)(GT_LAZE_BAN - KhoangCachMin) / KhoangCachLuc)*UpdateLuc ;	 
	   
		 if (GT_LAZE_BAN >= 490) {
				shot =(int) shot;
        shot += 6 ;
    }
//		 if (GT_LAZE_BAN >= 500) {
//				shot =(int) shot;
//        shot += 4 ;
//    }
//		  if (lazeTraiValue_Ban >= 560) {
//				shot =(int) shot;
//        shot += 4 ;
//    }
		power_shot = shot;
}

int calculate(int K) {
    int A[] = {445, 460, 465, 480, 485, 490, 495, 520, 525, 545, 550, 565, 570, 590, 650};
    int B[] = {86, 89, 90, 97, 98, 101, 103, 116, 118, 124, 126, 136, 140, 150, 180};
		int i;
    for (i = 0; i < 14; i++) {
        if (K >= A[i] && K <= A[i+1]) {
						//if(K >= 460 && K <= 465) return (B[i] + (K - A[i]) * (B[i+1] - B[i]) / (A[i+1] - A[i])) + 2;
            //else return B[i] + (K - A[i]) * (B[i+1] - B[i]) / (A[i+1] - A[i]);
					return B[i] + (K - A[i]) * (B[i+1] - B[i]) / (A[i+1] - A[i]);
        }
    }
    return 99;
	}

//int xoay_mam =0, savelaze_1 = 0 , savelaze_2 = 0 , Laze_1 = 0 , Laze_2 = 0;

void XoayNongLayGTLaze()
{
	if (R2 && xoay_mam ==0 && (target_BT_Xoay < Max_BT_Xoay) && lazeTraiValue >= 600)
	{
		target_BT_Xoay++, vTaskDelay(1000);
		savelaze_1 = 1;
	}
	if (lazeTraiValue <=600 && savelaze_1 == 1)
	{
		lazeTraiValue = Laze_1;
		vTaskDelay(1);
		xoay_mam = 1;
	}
	if ( R2 && xoay_mam == 1 && (target_BT_Xoay > Max_BT_Xoay ) && lazeTraiValue >= 600 )
	{
		target_BT_Xoay--, vTaskDelay(1000);
		savelaze_2 = 1;
	}
	if (lazeTraiValue <=600 && savelaze_2 == 1)
	{
		lazeTraiValue = Laze_2;
		vTaskDelay(1);
		xoay_mam = 2;
	}
	if (R2 && xoay_mam == 1 && xoay_mam == 2 )
	{
		target_BT_Xoay = 296;
		xoay_mam = 0;
	}
}

void Timkhoangcachgiuabang()
{
	
	Khoangcachtam = (2*(Laze_1*Laze_1 + Laze_2*Laze_2)- (CanhBang * CanhBang))/4;
}


void Tinhgoclech() //
{
		NuaChuvi = (Laze_1 + Laze_2 + CanhBang) / 2;
		ChieucaoAH =  (2*sqrt(NuaChuvi * (NuaChuvi - Laze_1) * (NuaChuvi - Laze_2 ) * (NuaChuvi - CanhBang ))) /  CanhBang;
		
		 CosGoc = ChieucaoAH / Khoangcachtam;

    // Bu?c 2: Tính góc (theo radian)
     radians_goc = acos(CosGoc);

    // Bu?c 3: Ðoi radian sang do
		GocLech = radians_goc * 180.0 / M_PI;

}




//void Xoay_nong (void)
//{
//	if (R1 && O && (target_BT_Xoay < Max_BT_Xoay))
//		target_BT_Xoay++, vTaskDelay(1000);
//	else if (R1 && SQUARE && (target_BT_Xoay > Min_BT_Xoay))
//		target_BT_Xoay--, vTaskDelay(1000);
//}



//void TinhToanLucBan(int lazeTraiValue)
//{
//	float shot = 0;
//	float LucMin = 58;
//	float KhoangCachMin = 390 ;
//	float KhoangCachLuc = 5;
//	float UpdateLuc = 1; 
//    shot = LucMin + ((float)(lazeTraiValue - KhoangCachMin) / KhoangCachLuc)*UpdateLuc ;	 
//    if (lazeTraiValue >= 500) {
//				shot =(int) shot;
//        shot += 3;
//    } else if (lazeTraiValue >= 450) {
//				shot =(int) shot;
//        shot += 1;
//    }

//		power_shot = shot;
//}







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
	 if (TRIANGLE)													XI_LANH = speed, XI_LANH_OFF;
	 else if (X && CB_HOME_NANG_HA == 1) 		XI_LANH = speed, XI_LANH_ON;
	 else																		XI_LANH = 2;
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
///
void nang_ha_nong_ban(void) // min 40 max 930  /// min 83 max 982
{
	if(R1 && TRIANGLE)	{
//		target_BT_Xoay = 392;
//		while (abs(BienTroXoayValue - target_BT_Xoay) > 5) {vTaskDelay(1);};
		state_nang = 1, state_ha = 0, taget_BT_Nong_Ban = 300 + Troi_Bientro , lock_nang = 0 , XI_LANH = 254, XI_LANH_ON;
	}
	else if(R1 && X){
	target_BT_Xoay = 392;
	while (abs(BienTroXoayValue - target_BT_Xoay) > 2) {if(wantExit()) break; vTaskDelay(1);};
	taget_BT_Nong_Ban = 922 + Troi_Bientro , lock_nang = 0, XI_LANH = 0, XI_LANH_OFF;
	}
	else if (taget_BT_Nong_Ban >=920  && state_ha == 0 && BienTroNongBanValue > 915 ){
	state_nang = 0;  
	state_ha = 1;
	}
}

///





//void nang_ha_nong_ban(void)
//{
//	if(R1 && TRIANGLE)
//{	
//	//sta_nap = 1;
//	target_BT_Xoay = 296;
//	while (abs(BienTroXoayValue - target_BT_Xoay) > 1) {vTaskDelay(1);};
//   state_nang = 1, state_ha = 0, taget_BT_Nong_Ban = 955 + Troi_Bientro , lock_nang = 0 , XI_LANH = 254, XI_LANH_ON;
//}
//	else if( R1 && X){
//	
//	target_BT_Xoay = 296;		
//	while (abs(BienTroXoayValue - target_BT_Xoay) > 1) {vTaskDelay(1);};
//	taget_BT_Nong_Ban = 50 + Troi_Bientro , lock_nang = 0, XI_LANH = 0, XI_LANH_OFF;
//}	

//	else if (taget_BT_Nong_Ban <= 50   && state_ha == 0 && BienTroNongBanValue < 60 ){
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
static char p = 0;

	if (taget_BT_Nong_Ban < Min_BT_Nong_Ban)
		taget_BT_Nong_Ban = Min_BT_Nong_Ban;
	if (taget_BT_Nong_Ban > Max_BT_Nong_Ban)
		taget_BT_Nong_Ban = Max_BT_Nong_Ban;

	if (abs(BienTroNongBanValue - taget_BT_Nong_Ban) > 5 && lock_nang == 0)
	{
		speed_temp = (abs(BienTroNongBanValue - taget_BT_Nong_Ban))*3;
		if (BienTroNongBanValue > taget_BT_Nong_Ban)
		{
			Nong_Ban_Up;
				
			if (BienTroNongBanValue >= 500){
				// anh vu code 
				if(tocDoNongBan < 180) {
					if(p++ %8 == 0) {
						tocDoNongBan++;
						if(tocDoNongBan >= 180) tocDoNongBan = 180;
					}
				}
				speed_temp = tocDoNongBan;
			}
			else
			{
				tocDoNongBan = 0;
				if (speed_temp > 200)  // 160 
					speed_temp = 200; 	
				if (speed_temp < 80)  
						speed_temp = 80;
			}
			
		}
		else 
		{
			Nong_Ban_Down;
			if (speed_temp > 80)   // 80
				speed_temp = 80;		// 80
			if (speed_temp < 10)  
				speed_temp = 10;
		}
		Nong_Ban = speed_temp; 
	}
	else  
	{
		Nong_Ban = 5;
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

	if (abs(BienTroXoayValue - target_BT_Xoay) > 4)
	{
		if (BienTroXoayValue > target_BT_Xoay)
			Mor_CamRotate_back;
		else
			Mor_CamRotate_next;
		speed_temp = abs(BienTroXoayValue - target_BT_Xoay)*8;
		if (speed_temp > 250) // 50
			speed_temp = 250;
		if (speed_temp < 50 ) 							
			speed_temp = 50;
		Mor_CamRotate = speed_temp;
	}
	else
		Mor_CamRotate = 2;
	//if(toc_do_xoay_sau_ban == 1) {}
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
	if (R1 && O && (target_BT_Xoay < Max_BT_Xoay)){
		bit_xoayTay = 1; 
		if(L1) Mor_CamRotate = 70;
		else Mor_CamRotate = 20;
		Mor_CamRotate_next;
		target_BT_Xoay = BienTroXoayValue;
	}
	else if (R1 && SQUARE && (target_BT_Xoay > Min_BT_Xoay)){
		bit_xoayTay = 1;
		if(L1) Mor_CamRotate = 70;
		else Mor_CamRotate = 20;
		Mor_CamRotate_back;
		target_BT_Xoay = BienTroXoayValue;
	}
	else bit_xoayTay = 0;
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
int gongluc = 0;
void Lay_Mau_GT_Laze()
{
	if(!R1 && SQUARE) {
		//gongluc = 1;
		lazeTraiValue_Ban =	lazeTraiValue;
		layMauBT = BienTroXoayValue;
	}
}



void bu_luc()
{
	if (da_lay_mau == 1)
	{
		donvixoay = abs(BienTroXoayValue - mau_bien_tro);
		if( donvixoay > 3 )
		{
			//lazeTraiValue_Ban -= 1;
			power_shot -=1;
		}
	}
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

void nap_bong_2()
{
		//Lay_Mau_GT_Laze();
		//for(i=0;i<100;i++)	while( CB_NHAN_BONG_BO_BAN == 0 )  {Xoay_nong();if(wantExit()) break; vTaskDelay(1);}	
		Ban_1 = Ban_2 = Ban_3 = 13;
		Ban_1_back, Ban_2_back, Ban_3_back;
		
		for(i=0;i<100;i++)	while( CB_NHAN_BONG_BO_BAN == 1 )  {Xoay_nong();if(wantExit()) break; vTaskDelay(1);}
		vTaskDelay(10000);
		Ban_1 = 0, Ban_2 = 0, Ban_3 = 0;
		Ban_1_back, Ban_2_back, Ban_3_back;
		XI_LANH = 254, XI_LANH_ON;
		sta_nap = 1;
		//Lay_Mau_GT_Laze();
}



//=======================Nap Bong=====================================================
 void nap_bong(void)
 {			
		
		int i; 	
	//	state_nang = 1, state_ha = 0, taget_BT_Nong_Ban = 613, lock_nang = 0;
	//	vTaskDelay(5000);
		
		//for(i=0;i<100;i++)	while( CB_NHAN_BONG_BO_BAN == 1 )  {Xoay_nong();if(wantExit()) break; vTaskDelay(1);}	
		Ban_1 = Ban_2 = Ban_3 = 13;
		Ban_1_back, Ban_2_back, Ban_3_back;
		vTaskDelay(9000);
		for(i=0;i<100;i++)	while( CB_NHAN_BONG_BO_BAN == 0 )  {Xoay_nong();if(wantExit()) break; vTaskDelay(1);}	
		Ban_1 = 0, Ban_2 = 0, Ban_3 = 0;
		Ban_1_back, Ban_2_back, Ban_3_back;
		XI_LANH = 254, XI_LANH_ON;
		Lay_Mau_GT_Laze();
		
}
	

 void nap_bongtest(void)
 {			
	 if(!R1 && OPTIONS)
	 {
		Ban_1 = Ban_2 = Ban_3 = 10;
		Ban_1_back, Ban_2_back, Ban_3_back;
	 }
	 else{
	 		Ban_1 = Ban_2 = Ban_3 = 0;
	 }
		
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

void testlaze()
{
	if(TOUCHPAD)
	{
		XI_LANH = 254;
	}
 else{ XI_LANH = 0;}
}


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

 void Ban_Bong_Can_Luc()
{
		if(CB_NHAN_BONG_BO_BAN == 0 ) 
		{
		Ban_1 = power , Ban_2 = power ,  Ban_3 = power; //force , power ,power_shot
		Ban_1_next, Ban_2_next, Ban_3_next;
		vTaskDelay(15000);
		//XI_LANH_BAN_BONG_ON;
		XI_LANH_OFF;
		XI_LANH = 254;
		vTaskDelay(10000);
		Ban_1 = 0 ,   Ban_2 = 0 ,  Ban_3 = 0;
		Ban_1_next, Ban_2_next, Ban_3_next;
		//XI_LANH_BAN_BONG_OFF;
		XI_LANH = 0  ;
		//vTaskDelay(16000);
		//target_BT_Xoay = 520;
		//XI_LANH = 0;
		}
//		taget_BT_Nong_Ban = 52 , lock_nang = 0;
//		if (taget_BT_Nong_Ban <=55   && state_ha == 0 && BienTroNongBanValue < 65 )
//	{
//		state_nang = 0;  
//		state_ha = 1;
//		lock_nang = 0;
//	}
	}

	void Bu_Tru_Luc()
	{
		if(!R1 && O) {power += 1;vTaskDelay(2000);}
		if(!R1 && X) {power -= 1;vTaskDelay(2000);}
	}
	void nap_bong_backup()
	{
		if(RJOY)
		{
			Ban_1 = Ban_2 = Ban_3 = 13;
			Ban_1_back, Ban_2_back, Ban_3_back;
			
			//XI_LANH = 254, XI_LANH_ON;
		}
		
	}

  void BanBong1(void)
{
	//tg ban goc giua san 
						
						
							//Lay_Mau_GT_Laze();
							//lazeTraiValue_Ban = lazeTraiValue;
							GT_LAZE_BAN = lazeTraiValue_Ban - 5   ;  //-2
							TinhToanLucBan();
							//Bu_Tru_Luc();
							Ban_1 = Ban_2 = Ban_3 = power_shot + power; //sang: 22  /trua: 20  / chieu: 10  /toi:    
							Ban_1_next, Ban_2_next, Ban_3_next;
							
						
}

void BanBong2(void)
{
				//sq
						if(CB_NHAN_BONG_BO_BAN == 0 )
						{	
							//Lay_Mau_GT_Laze();
							//lazeTraiValue_Ban = lazeTraiValue+11;
							//lazeTraiValue_Ban = lazeTraiValue_Ban + 1;
							//GT_LAZE_BAN = lazeTraiValue_Ban - 5;
							TinhToanLucBan();
							Ban_1 = Ban_2 = Ban_3 = calculate(lazeTraiValue_Ban + erLayMauBT - 30); // power_shot , testluc , power
							Ban_1_next, Ban_2_next, Ban_3_next;
						}
}

void BanBong3(void)
{
						//X
						if(CB_NHAN_BONG_BO_BAN == 0 )
						{	
							//Lay_Mau_GT_Laze();
							//lazeTraiValue_Ban = lazeTraiValue + 2;
							//lazeTraiValue_Ban = lazeTraiValue_Ban - 1;
							GT_LAZE_BAN = lazeTraiValue_Ban; // -15
							TinhToanLucBan();
							Ban_1 = Ban_2 = Ban_3 = calculate(GT_LAZE_BAN); // power_shot , testluc
							Ban_1_next, Ban_2_next, Ban_3_next;
						}
}

void BanBong4(void)
{
						//O
						if(CB_NHAN_BONG_BO_BAN == 0 )
						{	
							//Lay_Mau_GT_Laze();
							//bu_luc();
							//lazeTraiValue_Ban = lazeTraiValue + 8;
							//lazeTraiValue_Ban = lazeTraiValue_Ban + 8;
							GT_LAZE_BAN = lazeTraiValue_Ban; // -20
							TinhToanLucBan();
							Ban_1 = Ban_2 = Ban_3 = calculate(GT_LAZE_BAN); // power_shot , testluc
							Ban_1_next, Ban_2_next, Ban_3_next;
						}
}

void Reset_Ham()
{
	if (OPTIONS)
	{
		//XI_LANH = 0;
		Ban_1 = Ban_2 = Ban_3 = 0;
		da_lay_mau = 0;
		gongluc = 0;
		GT_LAZE_BAN = 0;
		//lazeTraiValue_Ban = 0;
	// static_ban = 0;  
	}
		
}
	
void Ban_Bong_test()
{
	if(!R1 && SQUARE )
	{
		Ban_1 = power , Ban_2 = power ,  Ban_3 = power; //force , power ,power_shot
		Ban_1_next, Ban_2_next, Ban_3_next;
	}
	else{
		Ban_1 = 0 ,   Ban_2 = 0 ,  Ban_3 = 0;
		Ban_1_next, Ban_2_next, Ban_3_next;
	}
}
void laze_test()
{
	if(!R1 && OPTIONS)
	{
		XI_LANH = 254 , XI_LANH_ON;
	}
	else
		XI_LANH = 0 , XI_LANH_OFF;
}
void Xoay_nong_tu_chinh(vu8 speed)
{
	if(R1 + O)                  Mor_CamRotate = speed, Mor_CamRotate_next;
	else if (R1 + SQUARE)				Mor_CamRotate = speed, Mor_CamRotate_next;
	else												Mor_CamRotate = 2;
}


void Nang_haNong_test(vu8 speed)
{
	if(TRIANGLE) 						Nong_Ban = speed , Nong_Ban_Up;
	else if (X) 						Nong_Ban = speed , Nong_Ban_Down;
	else 										Nong_Ban = 7;
}


///############################# CACULATOR POWER SHOT ################################################################
//void TinhToanLucBan(int lazeTraiValue)
//{
//	float shot = 0;
//	float LucMin = 58;
//	float KhoangCachMin = 390 ;
//	float KhoangCachLuc = 5;
//	float UpdateLuc = 1; 
//    shot = LucMin + ((float)(lazeTraiValue - KhoangCachMin) / KhoangCachLuc)*UpdateLuc ;	 
//    if (lazeTraiValue >= 500) {
//				shot =(int) shot;
//        shot += 3;
//    } else if (lazeTraiValue >= 450) {
//				shot =(int) shot;
//        shot += 1;
//    }

//		power_shot = shot;
//}
//############################# DATA POWER FROM EXCEL   #########################################################
void All_Data_Power(int lazeTraiValue) {
    int range = 0;
	
    if 			(lazeTraiValue >= 395 && lazeTraiValue <= 398) { range = 1; power_shot = 60; }
    else if (lazeTraiValue >= 399 && lazeTraiValue <= 402) { range = 2; power_shot = 60; }
    else if (lazeTraiValue >= 403 && lazeTraiValue <= 406) { range = 3; power_shot = 61; }
    else if (lazeTraiValue >= 407 && lazeTraiValue <= 410) { range = 4; power_shot = 61; }
    else if (lazeTraiValue >= 411 && lazeTraiValue <= 414) { range = 5; power_shot = 62; } //////
    else if (lazeTraiValue >= 415 && lazeTraiValue <= 418) { range = 6; power_shot = 63; }
    else if (lazeTraiValue >= 419 && lazeTraiValue <= 422) { range = 7; power_shot = 63; }
    else if (lazeTraiValue >= 423 && lazeTraiValue <= 426) { range = 8; power_shot = 63; }
    else if (lazeTraiValue >= 427 && lazeTraiValue <= 430) { range = 9; power_shot = 63; }
    else if (lazeTraiValue >= 431 && lazeTraiValue <= 434) { range = 10; power_shot	= 63; }
    else if (lazeTraiValue >= 435 && lazeTraiValue <= 438) { range = 11; power_shot = 64; }
    else if (lazeTraiValue >= 439 && lazeTraiValue <= 442) { range = 12; power_shot = 64; }
    else if (lazeTraiValue >= 443 && lazeTraiValue <= 446) { range = 13; power_shot = 84; }
    else if (lazeTraiValue >= 447 && lazeTraiValue <= 450) { range = 14; power_shot = 86; }
    else if (lazeTraiValue >= 451 && lazeTraiValue <= 454) { range = 15; power_shot = 87; }
    else if (lazeTraiValue >= 455 && lazeTraiValue <= 458) { range = 16; power_shot = 88; }
    else if (lazeTraiValue >= 459 && lazeTraiValue <= 462) { range = 17; power_shot = 89; }
    else if (lazeTraiValue >= 463 && lazeTraiValue <= 466) { range = 18; power_shot = 89; }
    else if (lazeTraiValue >= 467 && lazeTraiValue <= 470) { range = 19; power_shot = 89; }
    else if (lazeTraiValue >= 471 && lazeTraiValue <= 474) { range = 20; power_shot = 88; }
    else if (lazeTraiValue >= 475 && lazeTraiValue <= 478) { range = 21; power_shot = 90; }
		else if (lazeTraiValue >= 526 && lazeTraiValue <= 530) { range = 22; power_shot = 90; }
		else if (lazeTraiValue >= 531 && lazeTraiValue <= 535) { range = 23; power_shot = 92; }
    else {
        TinhToanLucBan(lazeTraiValue); 
        return;
    }
}

void BanBongDangCap()
{
    if(SQUARE)
    {
        if(static_ban == 0 && CB_NHAN_BONG_BO_BAN == 0)
        {
            Ban_1 = Ban_2 = Ban_3 = power; 
            Ban_1_next, Ban_2_next, Ban_3_next;
//            vTaskDelay(15000); 
            static_ban = 1; 
        }
        else if(static_ban == 1)
        {
            XI_LANH_OFF;
						XI_LANH = 254;
            vTaskDelay(10000); 
            Ban_1 = Ban_2 = Ban_3 = 0;
						XI_LANH = 0;
            static_ban = 0; 
        }
        while(SQUARE) {if(wantExit()) break; vTaskDelay(1);}
    }
}

//void ban_bong_tc()
//{
//	
////if(TOUCHPAD)
////{
////	            Ban_1 = Ban_2 = Ban_3 = power; 
////            Ban_1_next, Ban_2_next, Ban_3_next;

////}

//if(TOUCHPAD){
//	vTaskDelay(10);
//	while(TOUCHPAD)
//		{vTaskDelay(100);
//	e++;}
//}
//}

void kichxilanhbanbong()
{
	if (TOUCHPAD)
	{
//		XI_LANH = 254 , XI_LANH_ON ;
		XI_LANH = 254,XI_LANH_OFF ;
		vTaskDelay(7000);
		XI_LANH = 0 ;
		Ban_1_next, Ban_2_next, Ban_3_next;
      Ban_1 = 0;
			Ban_2 = 0;
			Ban_3 = 0;
			da_lay_mau = 0;
			mau_bien_tro = 0;
		sta_nap = 0;
			ERR = erLayMauBT;
			//Luu_luc = calculate(lazeTraiValue_Ban + erLayMauBT + 10 + power);
		gongluc = 0;
		Luu_luc = power_shot + power;	
		Lucbanbandau = power_shot;
		//lazeTraiValue_Ban = 0;
		//GT_LAZE_BAN = 0;
//		XI_LANH = 0 ;
	}
}

//void Xoay_nong (void)
//{
//	if (R1 && O && (target_BT_Xoay < Max_BT_Xoay))
//		target_BT_Xoay++, vTaskDelay(1000);
//	else if (R1 && SQUARE && (target_BT_Xoay > Min_BT_Xoay))
//		target_BT_Xoay--, vTaskDelay(1000);
//}
//void xoay_tu_dong_hieu()
//{
//	if(R2&&   "dang tren cao"){
//	if(SQUARE){
//		da_lay_mau=1;
//lay_mau_bt_1=BienTroXoayValue;
//lay_mau_laser_1 =lazeTraiValue;
//		vTaskDelay(1);
//		da_lay_mau=2;
//	}
//	if(da_lay_mau ==2){
//		Mor_CamRotate_next;
//		Mor_CamRotate=10;
//		//target_BT_Xoay++;
//	if(lazeTraiValue<lay_mau_laser_1)
//	{
//		
//		
//		
//	}
//	}
//}

//}
//void gia_tri_bien_tro()
//{
//	if(TRIAGLE){		
//	mau_bien_tro=	BienTroXoayValue;		
//	}
//	
//	
//}

