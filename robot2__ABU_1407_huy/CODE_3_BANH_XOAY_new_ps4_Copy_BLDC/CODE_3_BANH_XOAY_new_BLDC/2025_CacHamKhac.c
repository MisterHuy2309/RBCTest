#include <stdlib.h>
#include <math.h>
vu16 laser_truoc, laser_trai , laser_phai , Laser_Lap_Vu_Khi_Duoi; 
vs32 NanghaR2;



#define N_CAL 36


static const int mm_vals[] = {
      5,  10,  15,  20,  25,  30,  35,  40,  45,  50,
     55,  60,  65,  70,  75,  80,  85,  90,  95, 100,
    105, 110, 115, 120, 125, 130, 135, 140, 145, 150,
    155, 160, 165, 170, 175, 180
};

static const int adc_vals[] = {
     646,  732,  797,  856,  928,  992, 1052, 1123, 1185, 1246,
    1305, 1365, 1423, 1492, 1538, 1597, 1656, 1690, 1746, 1795,
    1842, 1880, 1924, 1954, 1998, 2036, 2072, 2101, 2132, 2152,
    2183, 2210, 2234, 2255, 2277, 2318
};

int adc_to_mm(int adc_raw)
{
		int i;
    // Gi?i h?n ngoài b?ng
    if(adc_raw <= adc_vals[0]) return mm_vals[0];
    if(adc_raw >= adc_vals[N_CAL-1]) return mm_vals[N_CAL-1];

    // N?i suy tuy?n tính
    for(i = 0; i < N_CAL-1; i++)
    {
        if(adc_raw >= adc_vals[i] && adc_raw <= adc_vals[i+1])
        {
            float t = (float)(adc_raw - adc_vals[i]) /
                      (float)(adc_vals[i+1] - adc_vals[i]);

            return mm_vals[i] + (int)(t * (mm_vals[i+1] - mm_vals[i]) + 0.5f);
        }
    }

    return mm_vals[0]; // fallback
}

/// ------------ Ham Quy Doi Tham So Laser ra cm --------------- ////
void update_laser_truoc(void)
{
    int raw = _ADC1_Filtered[10];
    laser_truoc = adc_to_mm(raw);
}
void update_laser_phai(void)
{
	int Larse_Phai = _ADC1_Filtered[11];
	laser_phai = adc_to_mm(Larse_Phai);
}
void update_laser_trai(void)
{
	int Larse_Trai = _ADC1_Filtered[12];
	laser_trai = adc_to_mm(Larse_Trai);
}
void update_laser_lap_vu_khi(void)
{
	int Larse_Vu_Khi_Duoi = _ADC1_Filtered[13];
	Laser_Lap_Vu_Khi_Duoi = adc_to_mm(Larse_Vu_Khi_Duoi);
}

void All_ADC_Laser_Value(void)
{
	update_laser_truoc();
	update_laser_phai();
	update_laser_trai();
}
//================= Function: CHUYEN DOI CAC CHE DO VA RESET TAT CA TRANG THAI ===================================================================
void Chon_Che_Do() {
		if (gp_get_mode_uart() == 13) {
				if (HOME == 4 && PREV_HOME != 4) {HOME_FLAG ++;}
				PREV_HOME = HOME;
				if (HOME_FLAG >= 2) {HOME_FLAG = 0;}
		} else {HOME_FLAG = 0;}
}

void RESET_ALL_TRANGTHAI() {
		static bool home_pressed_flag = false;
		if (HOME == 4) {
				if (home_pressed_flag == false) {
						touchpad_flag = 0; prev_TOUCHPAD = 0;
					
						CONTROL_TOC_DO(0, 3, 0); xilanh_ban_kep; xilanh_thu_kep; vi_tri = 0;
						cho_phep_chay = false;				
										
						home_pressed_flag = true; 				
				}
		} else {home_pressed_flag = false;}
		
		if (gp_get_mode_uart() == 0) {
				touchpad_flag = 0; prev_TOUCHPAD = 0;	
			
				CONTROL_TOC_DO(0, 3, 0); xilanh_ban_kep; xilanh_thu_kep; Laser_off; vi_tri = 0; 
				cho_phep_chay = false;			
		}
}

/////////////////////////////////////////////////////////////////////////////////////////////

///

static vs32 clamp_vs32(vs32 v, vs32 lo, vs32 hi) {
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}


// ---------------------------------------------------------
// Nang Ha R1 
// ---------------------------------------------------------
vs32 ConTroll_Speed (vs32 target, vs32 current, float speed, vs32 cham_cap_2, float ty_le_giam_toc)
{
   
    vs32  khoang_cach;
    vs32  delta;
    float t;
    float delta_f;

    if (speed < 0.0f) speed = -speed;
    if (ty_le_giam_toc <= 0.0f) ty_le_giam_toc = 0.05f;
    if (ty_le_giam_toc > 1.0f)  ty_le_giam_toc = 1.0f;

    khoang_cach = abs(target - current);
    if (khoang_cach == 0)
    return clamp_vs32(current, 0, 30200);

    t = 1.0f;
    if (khoang_cach < cham_cap_2)
        t = (float)khoang_cach / (float)cham_cap_2;

    delta_f = speed * (ty_le_giam_toc +
              (1.0f - ty_le_giam_toc) * t);

    if (delta_f > speed) delta_f = speed;

    delta = (vs32)ceilf(delta_f);
    if (delta < 1) delta = 1;

    if (khoang_cach <= delta)
        current = target;
    else if (current < target)
        current += delta;
    else
        current -= delta;

    return clamp_vs32(current, 0, 30200); /// Gioi han nang ha R1
}


//void Nang_Ha_R2(void)
//{
//    if (TAM_GIAC) 
//    {
//        NanghaR2 = ConTroll_Speed(30200,NanghaR2,10.0f,4200,0.1f);
//        DC_Nang_Ha_R2(NanghaR2);
//    }
//    else if (X)     
//    {
//        NanghaR2 = ConTroll_Speed(0,NanghaR2,10.0f,4200,0.1f);
//        DC_Nang_Ha_R2(NanghaR2);			
//    }
//}

//void Bam_Thanh_Laze_Phai_Truoc(vs32 LazeCapThanh)
//{
//	float Fix_Angle;
//	Fix_Angle = 
//	//MAIN_CONTROL(vs32 _mat_robot,vs32 _huong_chay,vs32 _toc_do,float _gia_toc,float _chay_va_xoay)
//	MAIN_CONTROL(0,900,10,2,0);
//}

//// Chuong Trinh Con Test 

void Cap_Thanh_Lap_Vu_Khi_Trai(vs32 num_Laze_trai , vs32 Tham_So_Cap_Thanh_Trai)
{
	int Fix_Cap_Thanh_Trai;
	Fix_Cap_Thanh_Trai = abs(laser_trai - num_Laze_trai)*5;
	
	if(laser_trai - num_Laze_trai > Tham_So_Cap_Thanh_Trai)
	{
		MAIN_CONTROL(0+Fix_Cap_Thanh_Trai , 0 , 10, 2 , 0 );
	}
	else if(laser_trai - num_Laze_trai < Tham_So_Cap_Thanh_Trai)
	{
		MAIN_CONTROL(0-Fix_Cap_Thanh_Trai , 0 , 10, 2 , 0 );
	}
	else 
		MAIN_CONTROL(0 , 0 , 10, 2 , 0 );
}

void Lap_Mui_Giao()
{
	//Nang_Co_Cau_Len 8000 xung;
	Cap_Thanh_Lap_Vu_Khi_Trai(10 , 20);
}


//#define	DIA_CHI_START13						DATA_SPEED[48]=255 // -- OK
//#define	ID13											DATA_SPEED[49]=13
//#define DC_Xoay_Trai				 			DATA_SPEED[50]=0
//#define DC_Xoay_Phai							DATA_SPEED[50]=1
//#define	DC_Xoay										DATA_SPEED[51]

int Max_BT_Xoay = 500;
int Min_BT_Xoay = 50;
int Vi_Tri_BT_Xoay = 100;
int speed_temp = 0;

	
void Controll_BT_Tay()
{
	if (Vi_Tri_BT_Xoay < Min_BT_Xoay)
		Vi_Tri_BT_Xoay = Min_BT_Xoay;
	if (Vi_Tri_BT_Xoay > Max_BT_Xoay)
		Vi_Tri_BT_Xoay = Max_BT_Xoay;

	if (abs(_ADC1_Filtered[13] - Vi_Tri_BT_Xoay) > 2 )
	{
		if (_ADC1_Filtered[13] > Vi_Tri_BT_Xoay)
			DC_Xoay_Trai;
		else
			DC_Xoay_Phai;

		speed_temp = abs(_ADC1_Filtered[13] - Vi_Tri_BT_Xoay)*15;
		if (speed_temp > 250) // 250
			speed_temp = 250;
		if (speed_temp < 10)  // 200
			speed_temp = 10;

		DC_Xoay = speed_temp;
	}
	else  DC_Xoay = 8 ;
}
