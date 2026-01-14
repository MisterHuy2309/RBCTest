u8 flag_xuong=0,flag_len=0;
u8 bien_da_hoan_thanh_leo = 0, flag_ha=0, flag_nang=0;

int Endtask_1 = 0 ,robot_start = 0,CB_Truoc = 0;
int state_nang_3 = 0;
int test_bit = 0;
float Kp=0.7,Kd=0.7,Ki=0.7 , Tang_GiamCB =0;
vs32 laze_can_chay=800, sai_so_laze;
vu16 khoan_cach_nang_200 = 15300;
vu16 khoan_cach_nang_400 = 30200;

vu16 timer_cho_on_dinh = 0 ;
vu16 timer_chay_tiep   = 0;
vu16 timer_run =0 ;
// Ch? cho phép d?c c?m bi?n khi c?n
uint8_t allow_read_cam_bien_truoc = 0;
uint8_t allow_read_cam_bien_sau   = 0;

vu16 laser_truoc; 
int Press_Tam_Giac = 0 , Press_X = 0;
int FlagCB_DEMO_PRESS_O = 0;

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

#define N_CAL 36

// ---------------------------------------------------------
// Hàm gi?i h?n
// ---------------------------------------------------------
static inline vs32 clamp_vs32(vs32 v, vs32 lo, vs32 hi) {
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}


// ---------------------------------------------------------
// Hàm nâng chân mu?t
// ---------------------------------------------------------
vs32 nang_chan_tu_tu(vs32 target, vs32 current, float speed, vs32 cham_cap_2, float ty_le_giam_toc) 
{
    if (speed < 0.0f) speed = -speed;
    if (ty_le_giam_toc <= 0.0f) ty_le_giam_toc = 0.05f;
    if (ty_le_giam_toc > 1.0f) ty_le_giam_toc = 1.0f;

    vs32 khoang_cach = abs(target - current);
    if (khoang_cach == 0) return clamp_vs32(current, 0, 30200);

    float t = 1.0f;
    if (khoang_cach < cham_cap_2) {
        t = (float)khoang_cach / (float)cham_cap_2;
    }

    float delta_f = speed * (ty_le_giam_toc + (1.0f - ty_le_giam_toc) * t);
    if (delta_f > speed) delta_f = speed;

    vs32 delta = (vs32)ceilf(delta_f);
    if (delta < 1) delta = 1;

    if (khoang_cach <= delta) current = target;
    else if (current < target) current += delta;
    else current -= delta;

    return clamp_vs32(current, 0, 30200);
}

/////////////////

vs32 Nang_tay_tu_tu (vs32 target, vs32 current, float speed, vs32 cham_cap_2, float ty_le_giam_toc) 
{
    if (speed < 0.0f) speed = -speed;
    if (ty_le_giam_toc <= 0.0f) ty_le_giam_toc = 0.05f;
    if (ty_le_giam_toc > 1.0f) ty_le_giam_toc = 1.0f;

    vs32 khoang_cach = abs(target - current);
    if (khoang_cach == 0) return clamp_vs32(current, 0, 30100);

    float t = 1.0f;
    if (khoang_cach < cham_cap_2) {
        t = (float)khoang_cach / (float)cham_cap_2;
    }

    float delta_f = speed * (ty_le_giam_toc + (1.0f - ty_le_giam_toc) * t);
    if (delta_f > speed) delta_f = speed;

    vs32 delta = (vs32)ceilf(delta_f);
    if (delta < 1) delta = 1;

    if (khoang_cach <= delta) current = target;
    else if (current < target) current += delta;
    else current -= delta;

    return clamp_vs32(current, 0, 30100);
}


// _______________________________________ham do laser______________________________________________
int adc_to_mm(int adc_raw)
{
    // Gi?i h?n ngoài b?ng
    if(adc_raw <= adc_vals[0]) return mm_vals[0];
    if(adc_raw >= adc_vals[N_CAL-1]) return mm_vals[N_CAL-1];

    // N?i suy tuy?n tính
    for(int i = 0; i < N_CAL-1; i++)
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
void update_laser_truoc(void)
{
    int raw = _ADC1_Filtered[10];
    laser_truoc = adc_to_mm(raw);
}

// ====================================================================


void test_cb(void)
{
	
	update_laser_truoc();
	
    if (laser_truoc >= 70 && laser_truoc <= 130)   

    {
			flag_nang=1;
			flag_ha=0; 
    }
		else if (laser_truoc < 70 && laser_truoc > 130) 
		{

			flag_ha=1; 
			flag_nang=0;
		}
		
		if(flag_nang==1)
		{
		    nang_chan_phai = nang_chan_tu_tu(20000, nang_chan_phai, 10.0f, 4200, 0.1f);
        nang_chan_trai = nang_chan_tu_tu(20000, nang_chan_trai, 10.0f, 4200, 0.1f);
        nang_chan_sau  = nang_chan_tu_tu(20000, nang_chan_sau , 10.0f, 4200, 0.1f);
		
		}
		else if(flag_ha==1)
		{
			
				nang_chan_phai = nang_chan_tu_tu(0, nang_chan_phai, 10.0f, 4200, 0.1f);
        nang_chan_trai = nang_chan_tu_tu(0, nang_chan_trai, 10.0f, 4200, 0.1f);
        nang_chan_sau  = nang_chan_tu_tu(0, nang_chan_sau , 10.0f, 4200, 0.1f);
		}
		
		


// dk dc
		   if (laser_truoc >=55) MAIN_CONTROL(0,0,30,2,0);
		
		else if(laser_truoc <55) MAIN_CONTROL(0,0,1,2,0);
		
								
		    DC_nang_phai(nang_chan_phai);
        DC_nang_trai(nang_chan_trai);
        DC_nang_sau (nang_chan_sau);
		
		
}





//// hàm leo rung phai 
//void robot_leo_rung_phai()
//{
//    static uint8_t state = 0;

//    switch (state)
//    {
//        // =====================================================
//        case 0: // NÂNG 3 CHÂN (30200)
//        // =====================================================
//            nang_chan_phai = nang_chan_tu_tu(30200, nang_chan_phai, 10, 50, 0.1f);
//            nang_chan_trai = nang_chan_tu_tu(30200, nang_chan_trai, 10, 50, 0.1f);
//            nang_chan_sau  = nang_chan_tu_tu(30200, nang_chan_sau , 10, 50, 0.1f);

//            if (nang_chan_phai == 30200 &&
//                nang_chan_trai == 30200 &&
//                nang_chan_sau  == 30200)
//            {
//                allow_read_cam_bien_truoc = 1; 
//                state = 1;
//            }
//            break;

//        // =====================================================
//        case 1: // CH? C?M BI?N TRU?C 1 == 0
//        // =====================================================
//         MAIN_CONTROL(0,0,25,2,0);

//            if (allow_read_cam_bien_truoc && CB_BANH_TRUOC_1 == 0)
//            {
//                MAIN_CONTROL(0,0,0,2,0);
//                allow_read_cam_bien_truoc = 0;
//                state = 2;
//            }
//            break;

//        // =====================================================
//        case 2: // KÉO 2 CHÂN TRU?C V? 0
//        // =====================================================
//            nang_chan_phai = nang_chan_tu_tu(0, nang_chan_phai, 10, 2200, 0.1f);
//            nang_chan_trai = nang_chan_tu_tu(0, nang_chan_trai, 10, 2200, 0.1f);

//            if (nang_chan_phai == 0 && nang_chan_trai == 0)
//            {
//                allow_read_cam_bien_sau = 1;
//                state = 3;
//            }
//            break;

//        // =====================================================
//        case 3: // CH?Y T?I – CH? C?M BI?N SAU 1 == 0
//        // =====================================================
//           MAIN_CONTROL(0,0,25,2,0);

//            if (allow_read_cam_bien_sau && CB_BANH_SAU_1 == 0)
//            {
//                MAIN_CONTROL(0,0,0,2,0);
//                allow_read_cam_bien_sau = 0;
//                state = 4;
//            }
//            break;

//        // =====================================================
//        case 4: // KÉO CHÂN SAU V? 0
//        // =====================================================
//            nang_chan_sau = nang_chan_tu_tu(0, nang_chan_sau, 10, 2200, 0.1f);

//            if (nang_chan_sau == 0)
//            {
//                allow_read_cam_bien_truoc = 1; 
//                state = 5;
//            }
//            break;

//        // =====================================================
//        case 5: // CH?Y T?I – CH? C?M BI?N TRU?C 2 == 1 (KHÔNG NH?N)
//        // =====================================================
//         MAIN_CONTROL(0,0,25,2,0);

//            if (allow_read_cam_bien_truoc && CB_BANH_TRUOC_2 == 1)
//            {
//                MAIN_CONTROL(0,0,0,2,0);
//                allow_read_cam_bien_truoc = 0;
//                state = 6;
//            }
//            break;

//        // =====================================================
//        case 6: // H? 2 CHÂN TRU?C XU?NG 15300
//        // =====================================================
//            nang_chan_phai = nang_chan_tu_tu(15300, nang_chan_phai, 10, 200, 0.1f);
//            nang_chan_trai = nang_chan_tu_tu(15300, nang_chan_trai, 10, 200, 0.1f);

//            if (nang_chan_phai == 15300 && nang_chan_trai == 15300)
//            {
//                allow_read_cam_bien_sau = 1;
//                state = 7;
//            }
//            break;

//        // =====================================================
//        case 7: // CH?Y T?I – CH? C?M BI?N SAU 2 == 1 (KHÔNG NH?N)
//        // =====================================================
//       MAIN_CONTROL(0,0,25,2,0);

//            if (allow_read_cam_bien_sau && CB_BANH_SAU_2 == 1)
//            {
//                MAIN_CONTROL(0,0,0,2,0);
//                allow_read_cam_bien_sau = 0;
//                state = 8;
//            }
//            break;

//        // =====================================================
// case 8: // H? CHÂN SAU XU?NG 15300 (k?t thúc chu trình cu)
//    nang_chan_sau = nang_chan_tu_tu(15300, nang_chan_sau, 10, 200, 0.1f);

//    if (nang_chan_sau == 15300)
//    {
//        // B?T Ð?U QUY TRÌNH M?I B?N V?A MÔ T?
//        allow_read_cam_bien_truoc = 1;  
//        state = 9;
//    }
//    break;

//// =====================================================
//// STATE 9 – CH?Y T?I ? CH? CB_TRUOC_1 == 0
//// =====================================================
//case 9:
// MAIN_CONTROL(0,0,25,2,0);

//    if (allow_read_cam_bien_truoc && CB_BANH_TRUOC_1 == 0)
//    {
//        MAIN_CONTROL(0,0,0,2,0);
//        allow_read_cam_bien_truoc = 0;
//        state = 10;
//    }
//    break;

//// =====================================================
//// STATE 10 – KÉO 2 CHÂN TRU?C LÊN 0
//// =====================================================
//case 10:
//    nang_chan_phai = nang_chan_tu_tu(0, nang_chan_phai, 10, 2000, 0.1f);
//    nang_chan_trai = nang_chan_tu_tu(0, nang_chan_trai, 10, 2000, 0.1f);

//    if (nang_chan_phai == 0 && nang_chan_trai == 0)
//    {
//        allow_read_cam_bien_sau = 1;
//        state = 11;
//    }
//    break;

//// =====================================================
//// STATE 11 – CH?Y T?I ? CH? CB_SAU_1 == 0
//// =====================================================
//case 11:
// MAIN_CONTROL(0,0,25,2,0);
//    if (allow_read_cam_bien_sau && CB_BANH_SAU_1 == 0)
//    {
//        MAIN_CONTROL(0,0,0,2,0);
//        allow_read_cam_bien_sau = 0;
//        state = 12;
//    }
//    break;

//// =====================================================
//// STATE 12 – KÉO CHÂN SAU LÊN 0
//// =====================================================
//case 12:
//    nang_chan_sau = nang_chan_tu_tu(0, nang_chan_sau, 10, 2000, 0.1f);

//    if (nang_chan_sau == 0)
//    {
//        // Ti?p t?c quy trình phía sau…
//        state = 13;
//    }
//    break;
//		// =====================================================
//// STATE 13 – CH?Y T?I, CH? CB_TRUOC_2 NG?NG NH?N (==1)
//// =====================================================
//case 13:
//  MAIN_CONTROL(0,0,25,2,0);

//    if (CB_BANH_TRUOC_2 == 1)  // c?m bi?n TRU?C 2 NG?NG nh?n
//    {
//        MAIN_CONTROL(0,0,0,2,0);  // d?ng
//        state = 14;
//    }
//    break;


//// =====================================================
//// STATE 14 – H? 2 CHÂN TRU?C XU?NG 15300
//// =====================================================
//case 14:
//    nang_chan_phai = nang_chan_tu_tu(15300, nang_chan_phai, 10, 300, 0.1f);
//    nang_chan_trai = nang_chan_tu_tu(15300, nang_chan_trai, 10, 300, 0.1f);

//    if (nang_chan_phai == 15300 && nang_chan_trai == 15300)
//    {
//        state = 15;
//    }
//    break;


//// =====================================================
//// STATE 15 – CH?Y T?I, CH? CB_SAU_2 NG?NG NH?N (==1)
//// =====================================================
//case 15:
// MAIN_CONTROL(0,0,25,2,0);

//    if (CB_BANH_SAU_2 == 1)    // c?m bi?n SAU 2 NG?NG nh?n
//    {
//        MAIN_CONTROL(0,0,0,2,0);
//        state = 16;
//    }
//    break;


//// =====================================================
//// STATE 16 – H? CHÂN SAU XU?NG 15300
//// =====================================================
//case 16:
//    nang_chan_sau = nang_chan_tu_tu(15300, nang_chan_sau, 10, 300, 0.1f);

//    if (nang_chan_sau == 15300)
//    {
//        // N?u b?n mu?n k?t thúc chu trình ? dây:
//        bien_da_hoan_thanh_leo = 1;

//        // Ho?c b?n mu?n ti?p t?c quy trình khác -> state = 17;
//        state = 17;
//    }
//    break;

//// =====================================================
//// STATE 17 – CH?Y T?I ~2 GIÂY R?I H? T?T C? CHÂN V? 0
//// =====================================================
//case 17:
//{
//    static uint16_t run_delay_17 = 0;

//    // bu?c 1: ch?y t?i
//    if (run_delay_17 < 2000)   // 200 l?n ˜ 2 giây (task 10ms)
//    {
// MAIN_CONTROL(0,0,25,2,0);
//        run_delay_17++;
//    }
//    else
//    {
//        // bu?c 2: d?ng và b?t d?u h? chân
//        MAIN_CONTROL(0,0,0,2,0);

//        nang_chan_phai = nang_chan_tu_tu(0, nang_chan_phai, 10, 400, 0.1f);
//        nang_chan_trai = nang_chan_tu_tu(0, nang_chan_trai, 10, 400, 0.1f);
//        nang_chan_sau  = nang_chan_tu_tu(0, nang_chan_sau , 10, 400, 0.1f);

//        if (nang_chan_phai == 0 &&
//            nang_chan_trai == 0 &&
//            nang_chan_sau  == 0)
//        {
//            run_delay_17 = 0;     // reset l?i d? dùng cho l?n sau
//            state = 18;
//        }
//    }
//}
//break;


//// =====================================================
//// STATE 18 – CH?Y T?I CH? CB_TRUOC_2 NG?NG NH?N
//// =====================================================
//case 18:
// MAIN_CONTROL(0,0,25,2,0);

//    if (CB_BANH_TRUOC_2 == 1)
//    {
//        MAIN_CONTROL(0,0,0,2,0);
//        state = 19;
//    }
//    break;


//// =====================================================
//// STATE 19 – H? 2 CHÂN TRU?C XU?NG 15300
//// =====================================================
//case 19:
//    nang_chan_phai = nang_chan_tu_tu(15300, nang_chan_phai, 10, 250, 0.1f);
//    nang_chan_trai = nang_chan_tu_tu(15300, nang_chan_trai, 10, 250, 0.1f);

//    if (nang_chan_phai == 15300 && nang_chan_trai == 15300)
//    {
//        state = 20;
//    }
//    break;


//// =====================================================
//// STATE 20 – CH?Y T?I CH? CB_SAU_2 NG?NG NH?N
//// =====================================================
//case 20:
//   MAIN_CONTROL(0,0,25,2,0);
//    if (CB_BANH_SAU_2 == 1)
//    {
//        MAIN_CONTROL(0,0,0,2,0);
//        state = 21;
//    }
//    break;


//// =====================================================
//// STATE 21 – H? CHÂN SAU XU?NG 15300
//// =====================================================
//case 21:
//    nang_chan_sau = nang_chan_tu_tu(15300, nang_chan_sau, 10, 250, 0.1f);

//    if (nang_chan_sau == 15300)
//    {
//        state = 22;
//    }
//    break;


//// =====================================================
//// STATE 22 – CH?Y T?I ~2 GIÂY TRU?C KHI H? H?T CHÂN (CASE 23)
//// =====================================================
//case 22:
//{
//    static uint16_t run_delay_22 = 0;

//    // ch?y t?i
//    if (run_delay_22 < 2100)     // 200 l?n = ~2 giây
//    {
// MAIN_CONTROL(0,0,25,2,0);
//        run_delay_22++;
//    }
//    else
//    {
//        MAIN_CONTROL(0,0,0,2,0);
//        run_delay_22 = 0;
//        state = 23;
//    }
//}
//break;


//// =====================================================
//// STATE 23 – H? T?T C? CHÂN V? 0 (K?T THÚC CU?I)
//// =====================================================
//case 23:
//    nang_chan_phai = nang_chan_tu_tu(0, nang_chan_phai, 10, 400, 0.1f);
//    nang_chan_trai = nang_chan_tu_tu(0, nang_chan_trai, 10, 400, 0.1f);
//    nang_chan_sau  = nang_chan_tu_tu(0, nang_chan_sau , 10, 400, 0.1f);

//    if (nang_chan_phai == 0 &&
//        nang_chan_trai == 0 &&
//        nang_chan_sau  == 0)
//    {
//        bien_da_hoan_thanh_leo = 1;
//        state = 24;
//    }
//    break;


//// =====================================================
//// STATE 24 – DONE
//// =====================================================
//case 24:
//    break;


//	}


//    // luôn c?p nh?t motor
//    DC_nang_sau(nang_chan_sau);
//    DC_nang_trai(nang_chan_trai);
//    DC_nang_phai(nang_chan_phai);
//}


//// ham leo bac vung giua 

//void robot_leo_rung_giua()
//{
//    static uint8_t state = 0;
//    static uint16_t run_delay = 0;

//    switch(state)
//    {
//        //====================================================
//        // STATE 0: NÂNG 3 CHÂN LÊN 15300
//        //====================================================
//        case 0:
//            nang_chan_phai = nang_chan_tu_tu(15300, nang_chan_phai, 10, 200, 0.1f);
//            nang_chan_trai = nang_chan_tu_tu(15300, nang_chan_trai, 10, 200, 0.1f);
//            nang_chan_sau  = nang_chan_tu_tu(15300, nang_chan_sau , 10, 200, 0.1f);

//            if (nang_chan_phai == 15300 &&
//                nang_chan_trai == 15300 &&
//                nang_chan_sau  == 15300)
//            {
//                state = 1;
//            }
//            break;

//        //====================================================
//        // STATE 1: CH?Y T?I & CH? CB TRU?C 1 NH?N
//        //====================================================
//        case 1:
//        MAIN_CONTROL(0,0,25,2,0);

//            if (CB_BANH_TRUOC_1 == 0)   // NG?NG NH?N
//            {
//                MAIN_CONTROL(0,0,0,2,0);
//                state = 2;
//            }
//            break;

//        //====================================================
//        // STATE 2: NÂNG 2 CHÂN TRU?C LÊN 0
//        //====================================================
//        case 2:
//            nang_chan_phai = nang_chan_tu_tu(0, nang_chan_phai, 10, 2000, 0.1f);
//            nang_chan_trai = nang_chan_tu_tu(0, nang_chan_trai, 10, 2000, 0.1f);

//            if (nang_chan_phai == 0 && nang_chan_trai == 0)
//            {
//                state = 3;
//            }
//            break;

//        //====================================================
//        // STATE 3: CH?Y T?I & CH? CB SAU 1 NH?N
//        //====================================================
//        case 3:
//   MAIN_CONTROL(0,0,25,2,0);

//            if (CB_BANH_SAU_1 == 0)
//            {
//                MAIN_CONTROL(0,0,0,2,0);
//                state = 4;
//            }
//            break;

//        //====================================================
//        // STATE 4: NÂNG CHÂN SAU LÊN 0
//        //====================================================
//        case 4:
//            nang_chan_sau = nang_chan_tu_tu(0, nang_chan_sau, 10, 2000, 0.1f);

//            if (nang_chan_sau == 0)
//            {
//                run_delay = 0;
//                state = 5;
//            }
//            break;

//        //====================================================
//        // STATE 5: CH?Y T?I 2S
//        //====================================================
//        case 5:
//          MAIN_CONTROL(0,0,25,2,0);

//            if (run_delay < 1500)   // 200 × 10ms = 2 giây
//            {
//                run_delay++;
//            }
//            else
//            {
//                MAIN_CONTROL(0,0,0,2,0);
//                state = 6;
//            }
//            break;

//        //====================================================
//        // STATE 6: NÂNG L?I 3 CHÂN LÊN 15300
//        //====================================================
//        case 6:
//            nang_chan_phai = nang_chan_tu_tu(15300, nang_chan_phai, 10, 200, 0.1f);
//            nang_chan_trai = nang_chan_tu_tu(15300, nang_chan_trai, 10, 200, 0.1f);
//            nang_chan_sau  = nang_chan_tu_tu(15300, nang_chan_sau , 10, 200, 0.1f);

//            if (nang_chan_phai == 15300 &&
//                nang_chan_trai == 15300 &&
//                nang_chan_sau  == 15300)
//            {
//                state = 7;
//            }
//            break;

//        //====================================================
//        // STATE 7: CH?Y T?I & CH? CB TRU?C 1
//        //====================================================
//        case 7:
//         MAIN_CONTROL(0,0,25,2,0);

//            if (CB_BANH_TRUOC_1 == 0)
//            {
//                MAIN_CONTROL(0,0,0,2,0);
//                state = 8;
//            }
//            break;

//        //====================================================
//        // STATE 8: NÂNG 2 CHÂN TRU?C LÊN 0
//        //====================================================
//        case 8:
//            nang_chan_phai = nang_chan_tu_tu(0, nang_chan_phai, 10, 2000, 0.1f);
//            nang_chan_trai = nang_chan_tu_tu(0, nang_chan_trai, 10, 2000, 0.1f);

//            if (nang_chan_phai == 0 && nang_chan_trai == 0)
//            {
//                state = 9;
//            }
//            break;

//        //====================================================
//        // STATE 9: CH?Y T?I & CH? CB SAU 1
//        //====================================================
//        case 9:
//        MAIN_CONTROL(0,0,25,2,0);

//            if (CB_BANH_SAU_1 == 0)
//            {
//                MAIN_CONTROL(0,0,0,2,0);
//                state = 10;
//            }
//            break;

//        //====================================================
//        // STATE 10: NÂNG CHÂN SAU LÊN 0 ? DONE
//        //====================================================
//        case 10:
//            nang_chan_sau = nang_chan_tu_tu(0, nang_chan_sau, 10, 2000, 0.1f);

//            if (nang_chan_sau == 0)
//            {
//                bien_da_hoan_thanh_leo = 1;
//                state = 12;
//            }
//            break;

////====================================================
//// STATE 12 – CH?Y T?I 2S
////====================================================
//case 12:
// MAIN_CONTROL(0,0,25,2,0);

//    if (run_delay < 2500)   // 200 × 10ms = 2s
//        run_delay++;
//    else
//    {
//        MAIN_CONTROL(0,0,0,2,0);
//        state = 13;
//    }
//    break;

////====================================================
//// STATE 13 – NÂNG T?T C? CHÂN LÊN 15300
////====================================================
//case 13:
//    nang_chan_phai = nang_chan_tu_tu(15300, nang_chan_phai, 10, 200, 0.1f);
//    nang_chan_trai = nang_chan_tu_tu(15300, nang_chan_trai, 10, 200, 0.1f);
//    nang_chan_sau  = nang_chan_tu_tu(15300, nang_chan_sau , 10, 200, 0.1f);

//    if (nang_chan_phai == 15300 &&
//        nang_chan_trai == 15300 &&
//        nang_chan_sau  == 15300)
//    {
//        state = 14;
//    }
//    break;

////====================================================
//// STATE 14 – ÐI T?I, Ð?I CB TRU?C 1 NH?N
////====================================================
//case 14:
//   MAIN_CONTROL(0,0,25,2,0);

//    if (CB_BANH_TRUOC_1 == 0)
//    {
//        MAIN_CONTROL(0,0,0,2,0);
//        state = 15;
//    }
//    break;

////====================================================
//// STATE 15 – NÂNG 2 CHÂN TRU?C LÊN 0
////====================================================
//case 15:
//    nang_chan_phai = nang_chan_tu_tu(0, nang_chan_phai, 10, 2000, 0.1f);
//    nang_chan_trai = nang_chan_tu_tu(0, nang_chan_trai, 10, 2000, 0.1f);

//    if (nang_chan_phai == 0 && nang_chan_trai == 0)
//        state = 16;
//    break;

////====================================================
//// STATE 16 – CH?Y T?I & Ð?I CB SAU 1 NH?N
////====================================================
//case 16:
// MAIN_CONTROL(0,0,25,2,0);

//    if (CB_BANH_SAU_1 == 0)
//    {
//        MAIN_CONTROL(0,0,0,2,0);
//        state = 17;
//    }
//    break;

////====================================================
//// STATE 17 – NÂNG CHÂN SAU LÊN 0
////====================================================
//case 17:
//    nang_chan_sau = nang_chan_tu_tu(0, nang_chan_sau, 10, 2000, 0.1f);

//    if (nang_chan_sau == 0)
//        state = 18;
//    break;

////====================================================
//// STATE 18 – ÐI T?I & Ð?I CB TRU?C 2 NG?NG NH?N
////====================================================
//case 18:
// MAIN_CONTROL(0,0,25,2,0);

//    if (CB_BANH_TRUOC_2 == 1)   // NG?NG NH?N = 1
//    {
//        MAIN_CONTROL(0,0,0,2,0);
//        state = 19;
//    }
//    break;

////====================================================
//// STATE 19 – H? 2 CHÂN TRU?C XU?NG 15300
////====================================================
//case 19:
//    nang_chan_phai = nang_chan_tu_tu(15300, nang_chan_phai, 10, 200, 0.1f);
//    nang_chan_trai = nang_chan_tu_tu(15300, nang_chan_trai, 10, 200, 0.1f);

//    if (nang_chan_phai == 15300 && nang_chan_trai == 15300)
//        state = 20;
//    break;

////====================================================
//// STATE 20 – ÐI T?I & Ð?I CB SAU 2 NG?NG NH?N
////====================================================
//case 20:
//    MAIN_CONTROL(0,0,25,2,0);

//    if (CB_BANH_SAU_2 == 1)
//    {
//        MAIN_CONTROL(0,0,0,2,0);
//        state = 21;
//    }
//    break;

////====================================================
//// STATE 21 – H? CHÂN SAU XU?NG 15300
////====================================================
//case 21:
//    nang_chan_sau = nang_chan_tu_tu(15300, nang_chan_sau, 10, 200, 0.1f);

//    if (nang_chan_sau == 15300)
//    {
//        run_delay = 0;
//        state = 22;
//    }
//    break;

////====================================================
//// STATE 22 – CH?Y T?I 2S
////====================================================
//case 22:
// MAIN_CONTROL(0,0,25,2,0);

//    if (run_delay < 1500)
//        run_delay++;
//    else
//    {
//        MAIN_CONTROL(0,0,0,2,0);
//        state = 23;
//    }
//    break;

////====================================================
//// STATE 23 – H? T?T C? CHÂN XU?NG 0
////====================================================
//case 23:
//    nang_chan_phai = nang_chan_tu_tu(0, nang_chan_phai, 10, 2000, 0.1f);
//    nang_chan_trai = nang_chan_tu_tu(0, nang_chan_trai, 10, 2000, 0.1f);
//    nang_chan_sau  = nang_chan_tu_tu(0, nang_chan_sau , 10, 2000, 0.1f);

//    if (nang_chan_phai == 0 &&
//        nang_chan_trai == 0 &&
//        nang_chan_sau  == 0)
//    {
//        state = 24;
//    }
//    break;

////====================================================
//// STATE 24 – ÐI T?I & Ð?I CB TRU?C 2 NG?NG NH?N
////====================================================
//case 24:
// MAIN_CONTROL(0,0,25,2,0);

//    if (CB_BANH_TRUOC_2 == 1)
//    {
//        MAIN_CONTROL(0,0,0,2,0);
//        state = 25;
//    }
//    break;

////====================================================
//// STATE 25 – H? 2 CHÂN TRU?C XU?NG 30200
////====================================================
//case 25:
//    nang_chan_phai = nang_chan_tu_tu(30200, nang_chan_phai, 10, 200, 0.1f);
//    nang_chan_trai = nang_chan_tu_tu(30200, nang_chan_trai, 10, 200, 0.1f);

//    if (nang_chan_phai == 30200 && nang_chan_trai == 30200)
//        state = 26;
//    break;

////====================================================
//// STATE 26 – ÐI T?I & Ð?I CB SAU 2 NG?NG NH?N
////====================================================
//case 26:
// MAIN_CONTROL(0,0,25,2,0);

//    if (CB_BANH_SAU_2 == 1)
//    {
//        MAIN_CONTROL(0,0,0,2,0);
//        state = 27;
//    }
//    break;

////====================================================
//// STATE 27 – H? CHÂN SAU XU?NG 30200
////====================================================
//case 27:
//    nang_chan_sau = nang_chan_tu_tu(30200, nang_chan_sau, 10, 200, 0.1f);

//    if (nang_chan_sau == 30200)
//    {
//        run_delay = 0;
//        state = 28;
//    }
//    break;

////====================================================
//// STATE 28 – ÐI T?I 2S
////====================================================
//case 28:
//     MAIN_CONTROL(0,0,25,2,0);

//    if (run_delay < 1500)
//        run_delay++;
//    else
//    {
//        MAIN_CONTROL(0,0,0,2,0);
//        state = 29;
//    }
//    break;

////====================================================
//// STATE 29 – CHO T?T C? CHÂN V? 0 (K?T THÚC)
////====================================================
//case 29:
//    nang_chan_phai = nang_chan_tu_tu(0, nang_chan_phai, 10, 2000, 0.1f);
//    nang_chan_trai = nang_chan_tu_tu(0, nang_chan_trai, 10, 2000, 0.1f);
//    nang_chan_sau  = nang_chan_tu_tu(0, nang_chan_sau , 10, 2000, 0.1f);

//    if (nang_chan_phai == 0 &&
//        nang_chan_trai == 0 &&
//        nang_chan_sau  == 0)
//    {
//        bien_da_hoan_thanh_leo = 1; // DONE!
//        state = 30;
//    }
//    break;

//				
//				
//				
//				
//				
//    }
//		

//    // Luôn c?p nh?t motor
//    DC_nang_sau(nang_chan_sau);
//    DC_nang_trai(nang_chan_trai);
//    DC_nang_phai(nang_chan_phai);
//}

//void robot_leo_rung_trai()
//{
//    static uint8_t state = 0;
//    static uint16_t run_delay = 0;

//    switch(state)
//    {

//    //===========================================
//    // STATE 0 – NÂNG 3 CHÂN LÊN 30200
//    //===========================================
//    case 0:
//        nang_chan_phai = nang_chan_tu_tu(30200, nang_chan_phai, 10, 200, 0.1f);
//        nang_chan_trai = nang_chan_tu_tu(30200, nang_chan_trai, 10, 200, 0.1f);
//        nang_chan_sau  = nang_chan_tu_tu(30200, nang_chan_sau , 10, 200, 0.1f);

//        if (nang_chan_phai == 30200 &&
//            nang_chan_trai == 30200 &&
//            nang_chan_sau  == 30200)
//        {
//            state = 1;
//        }
//        break;

//    //===========================================
//    // STATE 1 – ÐI T?I, Ð?I CB TRU?C 1 NH?N
//    //===========================================
//    case 1:
//     MAIN_CONTROL(0,0,25,2,0);

//        if (CB_BANH_TRUOC_1 == 0)
//        {
//            MAIN_CONTROL(0,0,0,2,0);
//            state = 2;
//        }
//        break;

//    //===========================================
//    // STATE 2 – KÉO 2 CHÂN TRU?C V? 0
//    //===========================================
//    case 2:
//        nang_chan_phai = nang_chan_tu_tu(0, nang_chan_phai, 10, 2000, 0.1f);
//        nang_chan_trai = nang_chan_tu_tu(0, nang_chan_trai, 10, 2000, 0.1f);

//        if (nang_chan_phai == 0 && nang_chan_trai == 0)
//            state = 3;
//        break;

//    //===========================================
//    // STATE 3 – ÐI T?I, Ð?I CB SAU 1 NH?N
//    //===========================================
//    case 3:
// MAIN_CONTROL(0,0,25,2,0);

//        if (CB_BANH_SAU_1 == 0)
//        {
//            MAIN_CONTROL(0,0,0,2,0);
//            state = 4;
//        }
//        break;

//    //===========================================
//    // STATE 4 – KÉO CHÂN SAU V? 0
//    //===========================================
//    case 4:
//        nang_chan_sau = nang_chan_tu_tu(0, nang_chan_sau, 10, 2000, 0.1f);

//        if (nang_chan_sau == 0)
//        {
//            run_delay = 0;
//            state = 5;
//        }
//        break;

//    //===========================================
//    // STATE 5 – ÐI T?I 2S
//    //===========================================
//    case 5:
//    MAIN_CONTROL(0,0,25,2,0);

//        if (run_delay < 1500) run_delay++;
//        else {
//            MAIN_CONTROL(0,0,0,2,0);
//            state = 6;
//        }
//        break;

//    //===========================================
//    // STATE 6 – NÂNG 3 CHÂN LÊN 15300
//    //===========================================
//    case 6:
//        nang_chan_phai = nang_chan_tu_tu(15300, nang_chan_phai, 10, 300, 0.1f);
//        nang_chan_trai = nang_chan_tu_tu(15300, nang_chan_trai, 10, 300, 0.1f);
//        nang_chan_sau  = nang_chan_tu_tu(15300, nang_chan_sau , 10, 300, 0.1f);

//        if (nang_chan_phai == 15300 &&
//            nang_chan_trai == 15300 &&
//            nang_chan_sau  == 15300)
//            state = 7;
//        break;

//    //===========================================
//    // STATE 7 – ÐI T?I, CH? CB TRU?C 1 NH?N
//    //===========================================
//    case 7:
//     MAIN_CONTROL(0,0,25,2,0);

//        if (CB_BANH_TRUOC_1 == 0)
//        {
//            MAIN_CONTROL(0,0,0,2,0);
//            state = 8;
//        }
//        break;

//    //===========================================
//    // STATE 8 – NÂNG 2 CHÂN TRU?C LÊN 0
//    //===========================================
//    case 8:
//        nang_chan_phai = nang_chan_tu_tu(0, nang_chan_phai, 10, 2000, 0.1f);
//        nang_chan_trai = nang_chan_tu_tu(0, nang_chan_trai, 10, 2000, 0.1f);

//        if (nang_chan_phai == 0 && nang_chan_trai == 0)
//            state = 9;
//        break;

//    //===========================================
//    // STATE 9 – ÐI T?I, CH? CB SAU 1 NH?N
//    //===========================================
//    case 9:
//       MAIN_CONTROL(0,0,25,2,0);

//        if (CB_BANH_SAU_1 == 0)
//        {
//            MAIN_CONTROL(0,0,0,2,0);
//            state = 10;
//        }
//        break;

//    //===========================================
//    // STATE 10 – NÂNG CHÂN SAU LÊN 0
//    //===========================================
//    case 10:
//        nang_chan_sau = nang_chan_tu_tu(0, nang_chan_sau, 10, 2000, 0.1f);

//        if (nang_chan_sau == 0)
//            state = 11;
//        break;

//    //===========================================
//    // STATE 11 – ÐI T?I, Ð?I CB TRU?C 2 NG?NG NH?N
//    //===========================================
//    case 11:
//      MAIN_CONTROL(0,0,25,2,0);

//        if (CB_BANH_TRUOC_2 == 1)
//        {
//            MAIN_CONTROL(0,0,0,2,0);
//            state = 12;
//        }
//        break;

//    //===========================================
//    // STATE 12 – H? 2 CHÂN TRU?C XU?NG 15300
//    //===========================================
//    case 12:
//        nang_chan_phai = nang_chan_tu_tu(15300, nang_chan_phai, 10, 200, 0.1f);
//        nang_chan_trai = nang_chan_tu_tu(15300, nang_chan_trai, 10, 200, 0.1f);

//        if (nang_chan_phai == 15300 && nang_chan_trai == 15300)
//            state = 13;
//        break;

//    //===========================================
//    // STATE 13 – ÐI T?I, Ð?I CB SAU 2 NG?NG NH?N
//    //===========================================
//    case 13:
//        MAIN_CONTROL(0,0,25,2,0);

//        if (CB_BANH_SAU_2 == 1)
//        {
//            MAIN_CONTROL(0,0,0,2,0);
//            state = 14;
//        }
//        break;

//    //===========================================
//    // STATE 14 – H? CHÂN SAU XU?NG 15300
//    //===========================================
//    case 14:
//        nang_chan_sau = nang_chan_tu_tu(15300, nang_chan_sau, 10, 200, 0.1f);

//        if (nang_chan_sau == 15300)
//        {
//            run_delay = 0;
//            state = 15;
//        }
//        break;

//    //===========================================
//    // STATE 15 – ÐI T?I 2S
//    //===========================================
//    case 15:
//       MAIN_CONTROL(0,0,25,2,0);

//        if (run_delay < 1500) run_delay++;
//        else {
//            MAIN_CONTROL(0,0,0,2,0);
//            state = 16;
//        }
//        break;

//    //===========================================
//    // STATE 16 – H? T?T C? CHÂN V? 0
//    //===========================================
//    case 16:
//        nang_chan_phai = nang_chan_tu_tu(0, nang_chan_phai, 10, 2000, 0.1f);
//        nang_chan_trai = nang_chan_tu_tu(0, nang_chan_trai, 10, 2000, 0.1f);
//        nang_chan_sau  = nang_chan_tu_tu(0, nang_chan_sau , 10, 2000, 0.1f);

//        if (nang_chan_phai == 0 &&
//            nang_chan_trai == 0 &&
//            nang_chan_sau  == 0)
//            state = 17;
//        break;

//    //===========================================
//    // STATE 17 – ÐI T?I, Ð?I CB TRU?C 2 NG?NG NH?N
//    //===========================================
//    case 17:
//     MAIN_CONTROL(0,0,25,2,0);

//        if (CB_BANH_TRUOC_2 == 1)
//        {
//            MAIN_CONTROL(0,0,0,2,0);
//            state = 18;
//        }
//        break;

//    //===========================================
//    // STATE 18 – H? 2 CHÂN TRU?C XU?NG 15300
//    //===========================================
//    case 18:
//        nang_chan_phai = nang_chan_tu_tu(15300, nang_chan_phai, 10, 200, 0.1f);
//        nang_chan_trai = nang_chan_tu_tu(15300, nang_chan_trai, 10, 200, 0.1f);

//        if (nang_chan_phai == 15300 && nang_chan_trai == 15300)
//            state = 19;
//        break;

//    //===========================================
//    // STATE 19 – ÐI T?I, Ð?I CB SAU 2 NG?NG NH?N
//    //===========================================
//    case 19:
//        MAIN_CONTROL(0,0,25,2,0);

//        if (CB_BANH_SAU_2 == 1)
//        {
//            MAIN_CONTROL(0,0,0,2,0);
//            state = 20;
//        }
//        break;

//    //===========================================
//    // STATE 20 – H? CHÂN SAU XU?NG 15300
//    //===========================================
//    case 20:
//        nang_chan_sau = nang_chan_tu_tu(15300, nang_chan_sau, 10, 200, 0.1f);

//        if (nang_chan_sau == 15300)
//        {
//            run_delay = 0;
//            state = 21;
//        }
//        break;

//    //===========================================
//    // STATE 21 – ÐI T?I 2S
//    //===========================================
//    case 21:
//        MAIN_CONTROL(0,0,25,2,0);

//        if (run_delay < 1500) run_delay++;
//        else {
//            MAIN_CONTROL(0,0,0,2,0);
//            state = 22;
//        }
//        break;

//    //===========================================
//    // STATE 22 – H? T?T C? CHÂN XU?NG 0
//    //===========================================
//    case 22:
//        nang_chan_phai = nang_chan_tu_tu(0, nang_chan_phai, 10, 2000, 0.1f);
//        nang_chan_trai = nang_chan_tu_tu(0, nang_chan_trai, 10, 2000, 0.1f);
//        nang_chan_sau  = nang_chan_tu_tu(0, nang_chan_sau , 10, 2000, 0.1f);

//        if (nang_chan_phai == 0 &&
//            nang_chan_trai == 0 &&
//            nang_chan_sau  == 0)
//            state = 23;
//        break;

//    //===========================================
//    // STATE 23 – ÐI T?I, CH? CB TRU?C 2 NG?NG NH?N
//    //===========================================
//    case 23:
//     MAIN_CONTROL(0,0,25,2,0);

//        if (CB_BANH_TRUOC_2 == 1)
//        {
//            MAIN_CONTROL(0,0,0,2,0);
//            state = 24;
//        }
//        break;

//    //===========================================
//    // STATE 24 – H? 2 CHÂN TRU?C XU?NG 15300
//    //===========================================
//    case 24:
//        nang_chan_phai = nang_chan_tu_tu(15300, nang_chan_phai, 10, 200, 0.1f);
//        nang_chan_trai = nang_chan_tu_tu(15300, nang_chan_trai, 10, 200, 0.1f);

//        if (nang_chan_phai == 15300 && nang_chan_trai == 15300)
//            state = 25;
//        break;

//    //===========================================
//    // STATE 25 – ÐI T?I, CH? CB SAU 2 NG?NG NH?N
//    //===========================================
//    case 25:
//        MAIN_CONTROL(0,0,25,2,0);

//        if (CB_BANH_SAU_2 == 1)
//        {
//            MAIN_CONTROL(0,0,0,2,0);
//            state = 26;
//        }
//        break;

//    //===========================================
//    // STATE 26 – H? CHÂN SAU XU?NG 0
//    //===========================================
//    case 26:
//        nang_chan_sau = nang_chan_tu_tu(15300, nang_chan_sau, 10, 200, 0.1f);

//        if (nang_chan_sau == 0)
//        {
//            run_delay = 0;
//            state = 27;
//        }
//        break;

//    //===========================================
//    // STATE 27 – CH?Y T?I 2S
//    //===========================================
//    case 27:
//        MAIN_CONTROL(0,0,25,2,0);

//        if (run_delay < 1500) run_delay++;
//        else {
//            MAIN_CONTROL(0,0,0,2,0);
//            state = 28;
//        }
//        break;

//    //===========================================
//    // STATE 28 – H? T?T C? CHÂN XU?NG 0 – K?T THÚC
//    //===========================================
//    case 28:
//        nang_chan_phai = nang_chan_tu_tu(0, nang_chan_phai, 10, 2000, 0.1f);
//        nang_chan_trai = nang_chan_tu_tu(0, nang_chan_trai, 10, 2000, 0.1f);
//        nang_chan_sau  = nang_chan_tu_tu(0, nang_chan_sau , 10, 2000, 0.1f);

//        if (nang_chan_phai == 0 &&
//            nang_chan_trai == 0 &&
//            nang_chan_sau  == 0)
//        {
//            bien_da_hoan_thanh_leo = 1;
//            state = 29;
//        }
//        break;

//    case 29:
//        break;
//    }

//    // c?p nh?t motor luôn
//    DC_nang_sau(nang_chan_sau);
//    DC_nang_trai(nang_chan_trai);
//    DC_nang_phai(nang_chan_phai);
//}
//___________________________________________________________________________

void ham_test()  {


	}
//	else if(TOUCHPAD)
//	{
//		
//		
//		
//		
//			  nang_chan_phai = nang_chan_tu_tu(0, nang_chan_phai, 10, 2000, 0.1f);
//        nang_chan_trai = nang_chan_tu_tu(0, nang_chan_trai, 10, 2000, 0.1f);
//        nang_chan_sau  = nang_chan_tu_tu(0, nang_chan_sau , 10, 2000, 0.1f);
//		
//	}
	
	
	
//	
//		DC_nang_sau(nang_chan_sau);
//    DC_nang_trai(nang_chan_trai);
//    DC_nang_phai(nang_chan_phai);
//	
//}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



void Test_Nang_Chan()
{
	 nang_chan_phai = nang_chan_tu_tu(15300, nang_chan_phai, 10, 200, 0.1f);
   nang_chan_trai = nang_chan_tu_tu(15300, nang_chan_trai, 10, 200, 0.1f);
	 nang_chan_sau = nang_chan_tu_tu(15300, nang_chan_sau, 10, 200, 0.1f);
	DC_nang_sau(nang_chan_sau);
  DC_nang_trai(nang_chan_trai);
  DC_nang_phai(nang_chan_phai);
}



void Robot_Start()
{
	nang_chan_phai = nang_chan_tu_tu(0, nang_chan_phai, 10.0f, 2200, 0.1f);
  nang_chan_trai  = nang_chan_tu_tu(0, nang_chan_trai,  10.0f, 2200, 0.1f);
  nang_chan_sau   = nang_chan_tu_tu(0, nang_chan_sau,   10.0f, 2200, 0.1f);

  DC_nang_sau(nang_chan_sau);
  DC_nang_trai(nang_chan_trai);
  DC_nang_phai(nang_chan_phai);
	
	if(nang_chan_phai < 2 && nang_chan_trai < 2 && nang_chan_sau < 2)
	{
		robot_start =0;
	}
}


//void Run_Cell_2()
//{
//	if(RX_USART6[2] == 2 && RX_USART6[3] == 0)
//	{
//		Endtask_1 = 1;
//	}
//	else if(RX_USART6[2] == 2 && RX_USART6[3] == 1 && laser_truoc >= 15 && laser_truoc <= 40 )
//	{
//		CONTROL_TOC_DO(0,3,0);
//		if(RX_USART6[2] == 2 && RX_USART6[3] == 1 && laser_truoc > 100)
//		{
//			Endtask_1 = 1;
//		}
//	}
//	else if (RX_USART6[2] == 2 && RX_USART6[3] == 2 && laser_truoc >= 50 && laser_truoc <= 90  )
//	{
//		{
//			Endtask_1 = 1;
//		}
//	}
//	if (Endtask_1 == 1) return;
//}

int state_run = 0;



void UP_All_LEG()
{
		nang_chan_phai = nang_chan_tu_tu(20000, nang_chan_phai, 10.0f, 4200, 0.1f);
		nang_chan_trai = nang_chan_tu_tu(20000, nang_chan_trai, 10.0f, 4200, 0.1f);
		nang_chan_sau  = nang_chan_tu_tu(20000, nang_chan_sau , 10.0f, 4200, 0.1f);
		DC_nang_phai(nang_chan_phai);
		DC_nang_trai(nang_chan_trai);
		DC_nang_sau (nang_chan_sau);

}

void Check_VT1()
{
	if(CELL_1 == 0)
	{
		PICK_LANE = 2;
	}
	else if (CELL_1 == 1)
	{
		if(laser_truoc >=50 ) {PICK_LANE = 0;}
		else if (laser_truoc <=50) { while(laser_truoc >= 60) {if(BreakHam()) break; vTaskDelay(1); PICK_LANE = 2; }  } 
	}
}


uint8_t robot_state = 0; 



void Test_Run_auto_noleg()
{
	int i;		
		MAIN_CONTROL(0,0,30,2,0);
		//RESET_ENCODER(2);
		for(i=0;i<100;i++)while(laser_truoc > 50) {if(BreakHam()) break; vTaskDelay(1);state_nang_3 = 1;} //Chay ra Ô 1
		CONTROL_TOC_DO(0,3,0);
}

void Kiem_Tra_Va_Di_Chuyen(uint8_t trang_thai_cell)
{
    if (trang_thai_cell == 11 || trang_thai_cell == 2 || trang_thai_cell == 3)
    {
        CONTROL_TOC_DO(0, 3, 0); 
        vTaskDelay(5000);         
        Test_Run_auto_noleg();        
    }
    else if (trang_thai_cell == 1)
    {
        CONTROL_TOC_DO(0, 3, 0); 
        
        while (laser_truoc <= 50)
        {
            if (BreakHam()) return; 
            vTaskDelay(1);
        }
        
        Test_Run_auto_noleg(); 
    }
    
    
    else 
    {
        Test_Run_auto_noleg();
    }
}

void Xu_Ly_Cell_Cuoi(uint8_t trang_thai_cell)
{
    if (trang_thai_cell == 11 || trang_thai_cell == 2 || trang_thai_cell == 3)
    {
        CONTROL_TOC_DO(0, 3, 0); 
        vTaskDelay(5000);          
    }
    else if (trang_thai_cell == 1)
    {
        CONTROL_TOC_DO(0, 3, 0); 
        while (laser_truoc <= 50) { if (BreakHam()) return; vTaskDelay(1); }
    }
    
    Test_Run_auto_noleg(); 
    
    CONTROL_TOC_DO(0, 3, 0); 
}


void Start_Auto_Lane_Logic()
{
    if (PICK_LANE == 1 || PICK_LANE == 2 || PICK_LANE == 3)
    {
        Kiem_Tra_Va_Di_Chuyen(CELL_1); // Ch?y ô 1
        Kiem_Tra_Va_Di_Chuyen(CELL_2); // Ch?y ô 2
        Kiem_Tra_Va_Di_Chuyen(CELL_3); // Ch?y ô 3
        Xu_Ly_Cell_Cuoi(CELL_4); // Ch?y ô 4
        
        CONTROL_TOC_DO(0, 3, 0);       
    }
}

//void Start_auto_Cell_2()	
//{
//	
//		int i;
//		MAIN_CONTROL(0,0,30,2,0);
//		for(i=0;i<100;i++)while(READ_ENCODER_2() < 400) {if(BreakHam()) break; vTaskDelay(1);state_nang_3 = 1;} //Chay ra Ô 1
//		if(state_nang_3 ==1 )UP_All_LEG();
//		CONTROL_TOC_DO(0,3,0);
//		if(nang_chan_trai >= 20000 && nang_chan_phai >= 20000 && nang_chan_sau >= 20000) 
//		//{PICK_LANE = 0;}
//	{
//		
//		if (laser_truoc <= 30)
//		{
//			if (CELL_1 == 1)
//			{
//				CONTROL_TOC_DO(0,3,0);
//				RESET_ENCODER(2);
//				for(i=0;i<100;i++)while(laser_truoc <= 50) {if(BreakHam()) break; vTaskDelay(1);} //Chay ra Ô 1
//				MAIN_CONTROL(0,0,30,2,0);
//				for(i=0;i<100;i++)while(READ_ENCODER_2() <= 100) {if(BreakHam()) break; vTaskDelay(1);} //Chay ra Ô 1
//				if(READ_ENCODER_2() <= 100){PICK_LANE = 0; test_bit = 1;} 
//				
//			}   
//			else if (CELL_1 == 0)
//			{
//				RESET_ENCODER(2);
//				MAIN_CONTROL(0,0,30,2,0);
//				for(i=0;i<100;i++)while(READ_ENCODER_2() < 400) {if(BreakHam()) break; vTaskDelay(1);} //Chay ra Ô 1
//				if(READ_ENCODER_2() < 400){PICK_LANE = 0;}
//			}
//							
//		}
//		else if (CELL_1 == 0 && laser_truoc >= 30)
//		{
//				
//				RESET_ENCODER(2);
//				MAIN_CONTROL(0,0,30,2,0);
//				for(i=0;i<100;i++)while(READ_ENCODER_2() < 400) {if(BreakHam()) break; vTaskDelay(1);} //Chay ra Ô 1
//				if(READ_ENCODER_2() < 400){PICK_LANE = 0; CONTROL_TOC_DO(0,3,0);}
//		}
//	}
//	
//}

		
//void Start_auto_Cell_2()	
//{
////		int i;
////		MAIN_CONTROL(0,0,30,2,0);
////		for(i=0;i<100;i++)while(READ_ENCODER_2() < 400) {if(BreakHam()) break; vTaskDelay(1);} //Chay ra Ô 1
////		UP_All_LEG();
////		for(i=0;i<100;i++)while(READ_ENCODER_2() < 450) {if(BreakHam()) break; vTaskDelay(1);} //Chay ra Ô 1
////		CONTROL_TOC_DO(0,3,0);
////		//RESET_ENCODER(2);
////		//for(i=0;i<100;i++)while(DC_nang_phai >=20000 && DC_nang_trai >=20000 && DC_nang_sau >=20000) {if(BreakHam()) break; vTaskDelay(1);}
////		Run_Cell_2();
////		MAIN_CONTROL(0,0,30,2,0);
////		for(i=0;i<100;i++)while(READ_ENCODER_2() < 1000) {if(BreakHam()) break; vTaskDelay(1);} //Chay ra Ô 1	
////		CONTROL_TOC_DO(0,3,0);
////		//RESET_ENCODER(2);
//}

void Test_CB_Bang_tay(void)
{
	if(O) {Tang_GiamCB +=80 , vTaskDelay(2000); }
	else if(VUONG)  {Tang_GiamCB -=80 , vTaskDelay(2000); }
}



void Chay_Lane_1(void)
{
	Test_CB_Bang_tay();
	int i;		
	RESET_ENCODER(2);
	MAIN_CONTROL(0,0,30,2,0);
	for(i=0;i<50;i++)while(READ_ENCODER_2() < 500) {if(BreakHam()) break; vTaskDelay(1);} //Chay ra Ô 1
	for(i=0;i<50;i++)while(laser_truoc <= Tang_GiamCB) 
	{
		if(CELL_1 == 1 && laser_truoc <= Tang_GiamCB ) 
		{
			CONTROL_TOC_DO(0,3,0);
			Test_CB_Bang_tay();
			 while(laser_truoc >= Tang_GiamCB)
			 {
				 Test_CB_Bang_tay();
				 return ; 
			 }				 
		}
		else if (CELL_1 == 0 && laser_truoc <= Tang_GiamCB)
		{
			CONTROL_TOC_DO(0,3,0);
			vTaskDelay(10000);
			return ;
		}
		if(BreakHam()) break;
		vTaskDelay(1);
	}
	//Chay ra Ô 1	
	MAIN_CONTROL(0,0,40,2,0);
	for(i=0;i<100;i++)while(READ_ENCODER_2() < 1000) {if(BreakHam()) test_bit = 5; break; vTaskDelay(1);} //Chay ra Ô 1
	CONTROL_TOC_DO(0,3,0); 
	PICK_LANE = 0;
	test_bit = 1;
	//RESET_ENCODER(2);
	
}

//#define  DONG_CO_len 	  			DATA_SPEED[32]=1
//#define  DONG_CO_xuong 	    	DATA_SPEED[32]=0
//#define	DONG_CO_nang   				DATA_SPEED[33]


void Bit_tay_ra_vao()
{
	if(TAM_GIAC) Press_Tam_Giac = 1;
	if(X) Press_X = 1;
}	

void Co_Cau_Tay()
{
	if(OPTIONS)
	{
		DC_TAY_KEP = 0;
		Press_Tam_Giac = 0;
		Press_X = 0;
	}
	
	if( Press_Tam_Giac == 1 && CB_HANH_TRINH_TAY_KEP_RA == 1 )
	{
		Press_X = 0;
		DC_TAY_KEP_RA , DC_TAY_KEP = 40;
	}
	
	else if (Press_X == 1 && CB_HANH_TRINH_TAY_KEP_VAO == 1)
	{
		Press_Tam_Giac = 0;
		DC_TAY_KEP_VAO , DC_TAY_KEP = 25;
	}
	if(CB_HANH_TRINH_TAY_KEP_VAO == 0 && Press_X == 1)
	{
		//Press_Tam_Giac = 0;
		Press_X = 0;
		DC_TAY_KEP = 8;
	}	
	if (CB_HANH_TRINH_TAY_KEP_RA == 0 && Press_Tam_Giac == 1 )
	{
		DC_TAY_KEP = 0;
		Press_Tam_Giac = 0;
	}
}

void Nang_Ha_Tay_Kep()
{
	if(O) 
	{	//				nang_chan_phai = nang_chan_tu_tu(0, nang_chan_phai, 10.0f, 4200, 0.1f);
		testxung =  Nang_tay_tu_tu(0, testxung, 10.0f, 4200, 0.1f);
	}
	else if (VUONG)
	{
		testxung =  Nang_tay_tu_tu(25000, testxung, 10.0f, 4200, 0.1f);
	}
	DC_NANG_HA_TAY_KEP (testxung);
}


void TestDC_RA_VAO(vu8 tocdo)
{
	if(!R1 && TAM_GIAC) 							DC_TAY_KEP_RA , DC_TAY_KEP = tocdo;
	else if (!R1 && X) 								DC_TAY_KEP_VAO , DC_TAY_KEP = tocdo;
	else 															DC_TAY_KEP = 0;
}

void Test_Tay_Kep()
{
	if(R1) 
	{
		XI_LANH_KEP_ON;
	}
	else if (R2)
	{
		XI_LANH_KEP_OFF;
	}	
}

int Bit_OPTIONS = 0;
void Test_Day_KFS(void)
{
	XI_LANH_DAY_KFS_RA;
	XI_LANH_GIU_KFS_SAU_OFF;
	//Bit_OPTIONS = 0;
	
}

void TuDongCanGiua(vu8 KC_Trai , vu8 KC_Phai) // 98 , 102
{
	
	if (Camera_uart4 >= KC_Trai && Camera_uart4 <= KC_Phai)
	{
			CONTROL_TOC_DO(0,3,0);
	}
	if (Camera_uart4 < KC_Trai)  
	{
		MAIN_CONTROL(5400,0,10,2,20); // xoay trai
	}
	if (Camera_uart4 > KC_Phai) 
	{
		MAIN_CONTROL(-5400,0,10,2,20); //xoay phai
	}
}
//

void Tu_Dong_KFS(void)
{
	int i;
	DC_TAY_KEP_RA , DC_TAY_KEP = 40;
	for(i=0;i<100;i++)while(CB_HANH_TRINH_TAY_KEP_RA == 1) {if(BreakHam()) test_bit = 5; break; vTaskDelay(1);} //Chay ra Ô 1
//	if(CB_HANH_TRINH_TAY_KEP_RA == 0) DC_TAY_KEP = 0;
//	DC_TAY_KEP = 0;
}

void Test_Lay_VK(void)
{
	if(CB_TAY_KEP_VU_KHI  == 0 )
	{
		XI_LANH_KEP_VU_KHI_ON;
		vTaskDelay(800);	
		XI_LANH_VU_KHI_UP;
	}
	
	
	 if (TOUCHPAD)
	{
		XI_LANH_KEP_VU_KHI_OFF;
		XI_LANH_VU_KHI_DOWN;
	}
	
	
}




