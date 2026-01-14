
u8 flag_xuong=0,flag_len=0;
u8 bien_da_hoan_thanh_leo = 0, flag_ha=0, flag_nang=0;

float Kp=0.7,Kd=0.7,Ki=0.7 ;
vs32 laze_can_chay=800, sai_so_laze;
vu16 khoan_cach_nang_200 = 15300;
vu16 khoan_cach_nang_400 = 30200;

vu16 timer_cho_on_dinh = 0 ;
vu16 timer_chay_tiep   = 0;
vu16 timer_run =0 ;

uint8_t allow_read_cam_bien_truoc = 0;
uint8_t allow_read_cam_bien_sau   = 0;

uint16_t bien_nang=0;
static int8_t lock_ra = 0;
static int8_t lock_vo = 0;



uint8_t flag_R1=0, flag_R2=0 ,flag_X=0,flag_O=0,flag_VUONG=0,flag_TAM_GIAC=0 ,flag_L1=0,flag_L2=0,flag_HOME=0,cam_bien_da_nhan=0;
vu16 laser_truoc,laser_2, laser_3, laser_4, laser_5;; 
// gia tri nay duoc do de so sanh voi gia tri ADC laser
static const int cm_vals[] = {
      5,  10,  15,  20,  25,  30,  35,  40,  45,  50,
     55,  60,  65,  70,  75,  80,  85,  90,  95, 100,
    105, 110, 115, 120, 125, 130, 135, 140, 145, 150,
    155, 160, 165, 170, 175, 180
};

// gia tri nay duoc lay tu ADC cua laser ve 
static const int adc_vals[] = {
     646,  732,  797,  856,  928,  992, 1052, 1123, 1185, 1246,
    1305, 1365, 1423, 1492, 1538, 1597, 1656, 1690, 1746, 1795,
    1842, 1880, 1924, 1954, 1998, 2036, 2072, 2101, 2132, 2152,
    2183, 2210, 2234, 2255, 2277, 2318
};

#define N_CAL 36

// ---------------------------------------------------------

// ---------------------------------------------------------
// _______________________________________ham do laser______________________________________________
int adc_to_cm(int adc_raw)
{
    if(adc_raw <= adc_vals[0]) return cm_vals[0];
    if(adc_raw >= adc_vals[N_CAL-1]) return cm_vals[N_CAL-1];

    for(int i = 0; i < N_CAL-1; i++)
    {
        if(adc_raw >= adc_vals[i] && adc_raw <= adc_vals[i+1])
        {
            float t = (float)(adc_raw - adc_vals[i]) /
                      (float)(adc_vals[i+1] - adc_vals[i]);

            return cm_vals[i] + (int)(t * (cm_vals[i+1] - cm_vals[i]) + 0.5f);
        }
    }

    return cm_vals[0];
}
void update_all_lasers(void)
{
    laser_truoc = adc_to_cm(_ADC1_Filtered[10]);
    laser_2 = adc_to_cm(_ADC1_Filtered[11]);
    laser_3 = adc_to_cm(_ADC1_Filtered[12]);
    laser_4 = adc_to_cm(_ADC1_Filtered[13]);
    laser_5 = adc_to_cm(_ADC1_Filtered[14]);
}

#define vitri_200 15300
#define vitri_400 30200

//----------------------------------- ham nang ha chan tu tu ---------------------------------------------

static inline vs32 clamp_vs32(vs32 v, vs32 lo, vs32 hi) {
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}


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
//------------------------------- end ----------------------------------------------------

//---------------------------- HAM DIEU KHIEN PID TAY KEP KFS ---------------------------------------
void HAM_DK_TAY_MOVE(int32_t target,
                     uint8_t speed_max,
                     int32_t linear_zone)
{
    static int32_t hold_encoder = 0;
    static int32_t last_abs_error = 0;
    static uint8_t impulse_cnt = 0;

    int32_t error, abs_error, delta_error;
    uint8_t pwm;

    /* =====================================================
       HOLD MODE – CH?M C?M BI?N (COI NHU Ð?T TARGET)
       ===================================================== */
    if ((CB_TAY_NGOAI == 0 && target > ENCODER_TAY_KEP) ||
        (CB_TAY_TRONG == 0 && target < ENCODER_TAY_KEP))
    {
        DC_TAY = 0;

        /* set di?m gi? 1 l?n */
        if (impulse_cnt == 0)
        {
            hold_encoder   = ENCODER_TAY_KEP;
            last_abs_error = 0;
        }

        error = hold_encoder - ENCODER_TAY_KEP;
        abs_error = (error >= 0) ? error : -error;

        /* deadzone */
        if (abs_error < 50)
            return;

        /* ch? d?y khi encoder TRÔI THÊM */
        delta_error = abs_error - last_abs_error;
        if (delta_error < 30)
            return;

        last_abs_error = abs_error;

        /* ch? cho kéo NGU?C chi?u CB */
        if (CB_TAY_NGOAI == 0)
            DC_TAY_VO;
        else
            DC_TAY_RA;

        /* PWM gi? tuy?n tính 10 ? 40 */
        pwm = 10 + (abs_error * 30) / 1000;
        if (pwm > 40) pwm = 40;
        if (pwm < 10) pwm = 10;

        DC_TAY = pwm;

        impulse_cnt++;
        if (impulse_cnt >= 2)
        {
            DC_TAY = 0;
            impulse_cnt = 0;
        }
        return;
    }

    /* =====================================================
       MOVE MODE – ÐI?U KHI?N THEO ENCODER
       ===================================================== */
    impulse_cnt = 0;

    error = target - ENCODER_TAY_KEP;
    abs_error = (error >= 0) ? error : -error;

    /* t?i v? trí */
    if (abs_error <= 3)
    {
        DC_TAY = 0;
        return;
    }

    /* ch?n chi?u */
    if (error > 0)
        DC_TAY_RA;
    else
        DC_TAY_VO;

    /* tang t?c tuy?n tính */
    if (abs_error > linear_zone)
        pwm = speed_max;
    else
        pwm = (abs_error * speed_max) / linear_zone;

    if (pwm < 5) pwm = 5;
    DC_TAY = pwm;
}

//----------------------------------- END ------------------------------------------------------------

//__________________________________________________________________________________________________

void ham_dieu_khien_tay()
{
	
//		if(X==4&&!L1)
//			{
//		nang_vitme = nang_chan_tu_tu(15000, nang_vitme, 7.0f, 1000, 0.1f);	
//		}
//			else if (TAM_GIAC==32&&!L1)		nang_vitme = nang_chan_tu_tu(0, nang_vitme, 7.0f, 1000, 0.1f);
//	DC_vitme (nang_vitme);
//		
//		
//				if(VUONG==16)
//			{
//xilanh_kep_kfs;
//		}
//			else if (O==8)	xilanh_nha_kfs;

//		
		
			
			
//z				if(R1==2)
//		{
//    flag_R1=1;
//		flag_R2=0;
//		}
//			else if (R2>=100)	{		
//		flag_R1=0;
//     flag_R2=1;

//			}	
//			
//		if(flag_R1==1)
//		{
//HAM_DK_TAY_MOVE(40000, 50, 3000);


//		}
//		else if (flag_R2==1)	{
//				
//HAM_DK_TAY_MOVE(-40000, 50, 800);



//			}
			
			
			
			
		
}


void DK_3chan()
{
			if(TAM_GIAC==32&&L1==1)
			{
		    nang_chan_phai = nang_chan_tu_tu(20000, nang_chan_phai, 10.0f, 19000, 0.1f);
        nang_chan_trai = nang_chan_tu_tu(20000, nang_chan_trai, 10.0f, 19000, 0.1f);
        nang_chan_sau  = nang_chan_tu_tu(20000, nang_chan_sau , 10.0f, 19000, 0.1f);	
		}
			else if (X==4&&L1)
			{
				nang_chan_phai = nang_chan_tu_tu(0, nang_chan_phai, 10.0f, 4200, 0.1f);
        nang_chan_trai = nang_chan_tu_tu(0, nang_chan_trai, 10.0f, 4200, 0.1f);
        nang_chan_sau  = nang_chan_tu_tu(0, nang_chan_sau , 10.0f, 4200, 0.1f);
			}
		
			   DC_nang_phai(nang_chan_phai);
        DC_nang_trai(nang_chan_trai);
        DC_nang_sau (nang_chan_sau);
		
}











//----------------------------------------------------------------
void dk_kep_kfs()
{
		if(flag_TAM_GIAC==1)
			{
				xilanh_nha_kfs_truoc;
//			  nang_chan_phai = nang_chan_tu_tu(15400, nang_chan_phai, 10.0f, 19000, 0.1f);
//        nang_chan_trai = nang_chan_tu_tu(15400, nang_chan_trai, 10.0f, 19000, 0.1f);
//        nang_chan_sau  = nang_chan_tu_tu(15400, nang_chan_sau , 10.0f, 19000, 0.1f);
				HAM_DK_TAY_MOVE(90000, 55, 600);
       xilanh_nha_kfs_truoc;
				
				if(CB_HT_ngoai==0&&CB_kep_KFS==1)
				{
						bien_nang=30000;
					

				}
				else if(CB_kep_KFS==0&&flag_X==0&&cam_bien_da_nhan==1)
				{
					xilanh_kep_kfs;
			bien_nang=11000;
	   HAM_DK_TAY_MOVE(-85000, 40, 600);
					
				}				
		}
			
 else if(flag_X==1)
{

	xilanh_nha_kfs;
	bien_nang=10;
	xilanh_giu_kfs_truoc;
	
}


//if(flag_VUONG==1)
//{
//	xilanh_day_kfs_ra
//	if(CB_xilanh_day_kfs==1)
//	{
//			xilanh_day_kfs_vo
//		xilanh_giu_kfs_sau
//		 vTaskDelay(1000);
//		flag_VUONG=0;
//		
//	}	
	
//}






		

//			   DC_nang_phai(nang_chan_phai);
//        DC_nang_trai(nang_chan_trai);
//        DC_nang_sau (nang_chan_sau);
//			
			nang_vitme = nang_chan_tu_tu(bien_nang, nang_vitme, 8.0f, 1000, 1.0f);
			DC_vitme (nang_vitme);
			

}






//void gap_KFS()
//{
//			if(VUONG==16)
//		{
//    flag_VUONG=flag_VUONG+=1;
//		flag_O=0;
//						flag_HOME=0;
//		}
//			else if (O==8)	{		
//		flag_VUONG=0;
//     flag_O=1;
//				flag_HOME=0;

//			}
//			else if (HOME==4)	{		
//		flag_VUONG=0;
//     flag_O=0;
//				flag_HOME=1;

//			}

//			
//			
//		if(flag_VUONG==1)
//		{
//xilanh_xuong;
//vTaskDelay(5000);
//xilanh_kep;
//		}			
//else if(flag_HOME==1)			
//{
//	xilanh_len
//	xilanh_kep;
//	
//}
//		
//	else if(flag_O==1)		
//			
//			{
//					xilanh_nha;
//				
//			}
//			
//}






void kiem_tra_cam_bien()

{
						if(CB_kep_KFS==0)
					{
						vTaskDelay(300);
						cam_bien_da_nhan=1;					
					}
	
	
}


