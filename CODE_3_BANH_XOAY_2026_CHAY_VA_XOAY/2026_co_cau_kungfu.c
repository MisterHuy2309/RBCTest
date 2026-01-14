


//   u8 flag_xuong=0,flag_len=0, bien_cam_bien_truoc_1=0,bien_cam_bien_sau_1=0 ,flag_400=0,flag_200=0 ,bien_da_hoan_thanh_leo=0 ;  
//		
//		vu16 khoan_cach_nang_200=15300, khoan_cach_nang_400=30200;








//static inline vs32 clamp_vs32(vs32 v, vs32 lo, vs32 hi) {
//    if (v < lo) return lo;
//    if (v > hi) return hi;
//    return v;
//}


//vs32 nang_chan_tu_tu(vs32 target, vs32 current, float speed, vs32 cham_cap_2, float ty_le_giam_toc) {
//  
//    if (speed < 0.0f) speed = -speed;
//    if (ty_le_giam_toc <= 0.0f) ty_le_giam_toc = 0.05f;
//    if (ty_le_giam_toc > 1.0f) ty_le_giam_toc = 1.0f;

//    vs32 khoang_cach = (current < target) ? (target - current) : (current - target);


//    if (khoang_cach == 0) {

//        return clamp_vs32(current, 0, 30200);
//    }


//    float delta_f;
//    if (khoang_cach >= cham_cap_2 || cham_cap_2 <= 0) {
//        delta_f = speed;
//    } else {
//   
//        float t = (float)khoang_cach / (float)cham_cap_2; 

//        delta_f = speed * (ty_le_giam_toc + (1.0f - ty_le_giam_toc) * t);

//        if (delta_f > speed) delta_f = speed;
//    }


//    vs32 delta = (vs32)ceilf(delta_f);
//    if (delta < 1) delta = 1;


//    if (khoang_cach <= (vs32)delta) {
//        current = target;
//    } else {
//        if (current < target) {
//            current += delta;
//        } else {
//            current -= delta;
//        }
//    }

// 
//    current = clamp_vs32(current, 0, 30200);

//    return current;
//}



//void robot_leo_bac_200() {

//    if (flag_len == 1) {
//        nang_chan_phai = nang_chan_tu_tu(15300, nang_chan_phai, 10.0f, 50, 0.1f);
//        nang_chan_trai  = nang_chan_tu_tu(15300, nang_chan_trai,  10.0f, 50, 0.1f);
//        nang_chan_sau   = nang_chan_tu_tu(15300, nang_chan_sau,   10.0f, 50, 0.1f);
//    }

//    if (bien_cam_bien_truoc_1 == 1) {

//        flag_len = 2;
//        nang_chan_phai = nang_chan_tu_tu(0, nang_chan_phai, 10.0f, 50, 0.1f);
//        nang_chan_trai  = nang_chan_tu_tu(0, nang_chan_trai,  10.0f, 50, 0.1f);
//        nang_chan_sau   = nang_chan_tu_tu(15300, nang_chan_sau, 10.0f,50, 0.1f);

//    }

//    if (bien_cam_bien_sau_1 == 1) {

//        bien_cam_bien_truoc_1 = 0;
//        nang_chan_phai = nang_chan_tu_tu(0, nang_chan_phai, 10.0f, 2200, 0.1f);
//        nang_chan_trai  = nang_chan_tu_tu(0, nang_chan_trai,  10.0f, 2200, 0.1f);
//        nang_chan_sau   = nang_chan_tu_tu(0, nang_chan_sau,   10.0f, 2200, 0.1f);


//    }


//    DC_nang_sau(nang_chan_sau);
//    DC_nang_trai(nang_chan_trai);
//    DC_nang_phai(nang_chan_phai);
//}

//void robot_xuong_bac_200() {
//    if (TAM_GIAC) bien_cam_bien_truoc_1 = 1;
//    if (X)      bien_cam_bien_sau_1   = 1;

//    if (flag_xuong == 1) {
//        nang_chan_phai = nang_chan_tu_tu(0, nang_chan_phai, 10.0f, 2200, 0.1f);
//        nang_chan_trai  = nang_chan_tu_tu(0, nang_chan_trai,  10.0f, 2200, 0.1f);
//        nang_chan_sau   = nang_chan_tu_tu(0, nang_chan_sau,   10.0f, 2200, 0.1f);
//    }

//    if (bien_cam_bien_truoc_1 == 1) {
//        flag_xuong = 2;
//        nang_chan_phai = nang_chan_tu_tu(15300, nang_chan_phai, 10.0f, 2200, 0.1f);
//        nang_chan_trai  = nang_chan_tu_tu(15300, nang_chan_trai, 10.0f, 2200, 0.1f);
//        nang_chan_sau   = nang_chan_tu_tu(0, nang_chan_sau,    10.0f, 2200, 0.1f);
//    }

//    if (bien_cam_bien_sau_1 == 1) {
//        bien_cam_bien_truoc_1 = 0;
//        nang_chan_phai = nang_chan_tu_tu(15300, nang_chan_phai, 10.0f, 2200, 0.1f);
//        nang_chan_trai  = nang_chan_tu_tu(15300, nang_chan_trai, 10.0f, 2200, 0.1f);
//        nang_chan_sau   = nang_chan_tu_tu(15300, nang_chan_sau, 10.0f, 2200, 0.1f);
//    }

//    DC_nang_sau(nang_chan_sau);
//    DC_nang_trai(nang_chan_trai);
//    DC_nang_phai(nang_chan_phai);
//}


//void robot_leo_bac_400() {
//    if (flag_len == 1) {
//        nang_chan_phai = nang_chan_tu_tu(30200, nang_chan_phai, 10.0f, 4200, 0.1f);
//        nang_chan_trai  = nang_chan_tu_tu(30200, nang_chan_trai,  10.0f, 4200, 0.1f);
//        nang_chan_sau   = nang_chan_tu_tu(30290, nang_chan_sau,   10.0f, 4200, 0.1f);
//    }

//    if (bien_cam_bien_truoc_1 == 1) {
//        flag_len = 2;
//        nang_chan_phai = nang_chan_tu_tu(0, nang_chan_phai, 10.0f, 4200, 0.1f);
//        nang_chan_trai  = nang_chan_tu_tu(0, nang_chan_trai,  10.0f, 4200, 0.1f);
//        nang_chan_sau   = nang_chan_tu_tu(30290, nang_chan_sau, 10.0f,4200,0.1f);
//    }

//    if (bien_cam_bien_sau_1 == 1) {
//        bien_cam_bien_truoc_1 = 0;
//        nang_chan_phai = nang_chan_tu_tu(0, nang_chan_phai, 10.0f, 4200, 0.1f);
//        nang_chan_trai  = nang_chan_tu_tu(0, nang_chan_trai,  10.0f, 4200, 0.1f);
//        nang_chan_sau   = nang_chan_tu_tu(0, nang_chan_sau,   10.0f, 4200, 0.1f);
//    }

//    DC_nang_sau(nang_chan_sau);
//    DC_nang_trai(nang_chan_trai);
//    DC_nang_phai(nang_chan_phai);
//}

//void robot_xuong_bac_400() {
//    if (TAM_GIAC) bien_cam_bien_truoc_1 = 1;
//    if (X)      bien_cam_bien_sau_1   = 1;

//    if (flag_xuong == 1) {
//        nang_chan_phai = nang_chan_tu_tu(0, nang_chan_phai, 10.0f, 4200, 0.1f);
//        nang_chan_trai  = nang_chan_tu_tu(0, nang_chan_trai,  10.0f, 4200, 0.1f);
//        nang_chan_sau   = nang_chan_tu_tu(0, nang_chan_sau,   10.0f, 4200, 0.1f);
//    }

//    if (bien_cam_bien_truoc_1 == 1) {
//        flag_xuong = 2;
//        nang_chan_phai = nang_chan_tu_tu(30200, nang_chan_phai, 10.0f, 4200, 0.1f);
//        nang_chan_trai  = nang_chan_tu_tu(30200, nang_chan_trai, 10.0f, 4200, 0.1f);
//        nang_chan_sau   = nang_chan_tu_tu(0, nang_chan_sau,    10.0f, 4200, 0.1f);
//    }

//    if (bien_cam_bien_sau_1 == 1) {
//        bien_cam_bien_truoc_1 = 0;
//        nang_chan_phai = nang_chan_tu_tu(30200, nang_chan_phai, 10.0f, 4200, 0.1f);
//        nang_chan_trai  = nang_chan_tu_tu(30200, nang_chan_trai, 10.0f, 4200, 0.1f);
//        nang_chan_sau   = nang_chan_tu_tu(30290, nang_chan_sau, 10.0f, 4200, 0.1f);
//    }

//    DC_nang_sau(nang_chan_sau);
//    DC_nang_trai(nang_chan_trai);
//    DC_nang_phai(nang_chan_phai);
//}

float PWM_Down_Up = 100;

extern int testbit;

void Testtudong()
{
	int i;
	MAIN_CONTROL(IMU+4000,0, 10, 2, 0);
//	for(i = 0; i<100; i++) while(abs(IMU-(IMU + 900)) > 10)
	//nho_IMU=IMU-chay_xoay*36;huong_chay=0; MAIN_CONTROL(nho_IMU,huong_chay,10,gt*2,20);nho_IMU=IMU;BIT_NHO_CHAY=10;nho_IMU=IMU;
	for(i = 0; i<100; i++) while(READ_ENCODER_2() < 1000 ) {if(BreakHam()) break; vTaskDelay(1);}
	RESET_ENCODER(2);
	MAIN_CONTROL(0,0,20,1,20);
	for(i = 0; i<100; i++) while(READ_ENCODER_2() < 1000 ) {if(BreakHam()) break; vTaskDelay(1);}
	CONTROL_TOC_DO(0,4,0);
	testbit = 0;
}


void Robot_Task1()
{
	int i;
	MAIN_CONTROL(0,900,10, 2, 0);  //Mat_RB , Huong chay , toc_do, gia toc , chay va xoay
	for(i=0;i<100;i++)while(READ_ENCODER_2() < 1000) {if(BreakHam()) break; vTaskDelay(1);} //Lay mui giao
	CONTROL_TOC_DO(0,3,0);
  //MAIN_CONTROL(0,0,0,1,0);
	vTaskDelay(50000);
	//// Code Co cau lay giao//
	//......../// Khoi dong co cau kep Ket hop voi cam bien
	///Lay giao xong
	RESET_ENCODER(2);
	
	MAIN_CONTROL(IMU+4000,0,10, 2, 0); // xoay va chay tam 3s ve huong R2 de lap mui giao
	//Khoi dong xi lanh ngua 
	for(i=0;i<100;i++)while(READ_ENCODER_2() < 1000) {if(BreakHam()) break; vTaskDelay(1);} //chay len 1 xiu de lap mui giao
	// Kich hoat Co cau lap Mui giao	
	RESET_ENCODER(2);
}

void START_CELL_1()
{
	int i;
	RESET_ENCODER(2);
	MAIN_CONTROL(0,0,40,2,0); // chay ra Cell 1
	for(i=0;i<100;i++)while(READ_ENCODER_2() < PWM_Down_Up) {if(BreakHam()) break; vTaskDelay(1);} //Chay ra Ô 1
	CONTROL_TOC_DO(0,3,0);
	//Khoi dong co cau lay R1 
	RESET_ENCODER(2);

}

void START_CELL_2()
{
	int i;
	RESET_ENCODER(2);
	MAIN_CONTROL(IMU+90000,0,50,1,50); // chay ra Cell 2
	for(i=0;i<100;i++)while(READ_ENCODER_2() < 1000) {if(BreakHam()) break; vTaskDelay(1);} //Chay ra Ô 1
	CONTROL_TOC_DO(0,3,0);
	//Khoi dong co cau lay R1 
	RESET_ENCODER(2);

}

void START_CELL_3()
{
	int i;
	RESET_ENCODER(2);
	MAIN_CONTROL(IMU+90000,0,60,1,60); // chay ra Cell 3
	for(i=0;i<100;i++)while(READ_ENCODER_2() < 1000) {if(BreakHam()) break; vTaskDelay(1);} //Chay ra Ô 1
	CONTROL_TOC_DO(0,3,0);
	//Khoi dong co cau lay R1 
	RESET_ENCODER(2);
}

void Reset_ALL(void)
{
	CONTROL_TOC_DO(0,3,0);
}

