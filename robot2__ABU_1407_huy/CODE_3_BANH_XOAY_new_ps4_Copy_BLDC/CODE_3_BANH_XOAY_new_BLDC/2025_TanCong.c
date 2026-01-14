//================= Function: Tinh toan khoang cach va huong di chuyen ===================================================================
#define M_PI 3.141592653589793238462643383279
#define DUONG_KINH_BANH_XE 70.0 //90.0
#define XUNG_MOI_VONG 26000 //22000
//#define M_PI 3.141592653589793238462643383279
//#define DUONG_KINH_BANH_XE 80.0 //90.0
//#define XUNG_MOI_VONG 23000 //22000

float tinh_khoang_cach(float x1, float y1, float x2, float y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

vs32 tinh_huong(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float angleRad = atan2(dx, dy); // Tinh goc radian
    float angleDeg = angleRad * (180.0 / M_PI); // Doi goc radian sang do
    vs32 pulses = (vs32)(angleDeg * 10); // Nhan 10 de trung voi MAIN CONTROL 
    return -pulses;
}

void chay_toi_diem(float x1, float y1, float x2, float y2, vs32 toc_do_toi_da, float he_so_xung) {
		vs32 huong_chay = tinh_huong(x1, y1, x2, y2);	
		float khoang_cach = tinh_khoang_cach(x1, y1, x2, y2);
		float chu_vi_banh_xe = M_PI * DUONG_KINH_BANH_XE; // Chu vi bánh xe (mm)
	  float gt_qduong;	
		vs32 toc_do = toc_do_toi_da;
		s32 encoder_max = 0;
	
		#define NGUONG_ENCODER 1000000 // Nguong xung encoder cho phep 
		#define DO_LECH_TOI_DA 50000  // Xung encoder cho phep lech giua 3 banh
		
		// Loai bo encoder bi vuot nguong xung cho phep
		s32 e1 = (ENCODER_TRAI < NGUONG_ENCODER) ? ENCODER_TRAI : 0;
		s32 e2 = (ENCODER_PHAI < NGUONG_ENCODER) ? ENCODER_PHAI : 0;
		s32 e3 = (ENCODER_SAU  < NGUONG_ENCODER) ? ENCODER_SAU  : 0;

		// Loai bo encoder bi lech qua nhieu so voi 2 encoder con lai
		if (abs(e1 - e2) > DO_LECH_TOI_DA && abs(e1 - e3) > DO_LECH_TOI_DA)
				e1 = 0;  // e1 lech qua nhieu
		if (abs(e2 - e1) > DO_LECH_TOI_DA && abs(e2 - e3) > DO_LECH_TOI_DA)
				e2 = 0;  // e2 lech qua nhieu
		if (abs(e3 - e1) > DO_LECH_TOI_DA && abs(e3 - e2) > DO_LECH_TOI_DA)
				e3 = 0;  // e3 lech qua nhieu

		// Tim encoder lon nhat trong so encoder hop le
		if (e1 > encoder_max) encoder_max = e1;
		if (e2 > encoder_max) encoder_max = e2;
		if (e3 > encoder_max) encoder_max = e3;
		
		// Tinh muc tieu xung va xung con lai 
		muc_tieu_xung = (s32)(((khoang_cach * 1000.0f) / chu_vi_banh_xe * XUNG_MOI_VONG) * he_so_xung); 
		xung_con_lai = muc_tieu_xung - encoder_max;
	
	
		if (cho_phep_chay == true) {
				if (xung_con_lai > 0) {
						// === Giam toc do tuyen tinh khi con 1/3 quang duong ===						
						if (xung_con_lai <= muc_tieu_xung * 0.35) {
								toc_do = (vs32)(toc_do_toi_da * ((float)xung_con_lai / ((float)muc_tieu_xung / 3.0f)));
						}						
						
            // === Dieu chinh toc do theo quang duong ===						
						if (xung_con_lai <= muc_tieu_xung * 0.1 || khoang_cach <= 1.0) {toc_do = 120;} // Khi gan dung
						else if (toc_do < 150) {toc_do = 150;} // Gioi han toc do thap						
						else if (toc_do > toc_do_toi_da) {toc_do = toc_do_toi_da;} // Gioi han toc do cao
						toc_do_test = toc_do;					
						
            // === Dieu chinh gia toc theo quang duong ===
            if (xung_con_lai <= muc_tieu_xung * 0.2) {gt_qduong = 0.7;} // Khi gan dung
            else if (xung_con_lai <= muc_tieu_xung * 0.8) {gt_qduong = 0.3; touchpad_flag = 1;} // Khi chay on dinh
            else {gt_qduong = 0.5;} // Khi khoi dong
						
						MAIN_CONTROL(0, huong_chay, toc_do, gt_qduong, 0);

				} else {CONTROL_TOC_DO(0, 0.8, 0); cho_phep_chay = false;}	
	  }
}

//================= Function: Chay 3 vi tri: Trai, giua, phai khi nhan bong ===================================================================
void Chay_Vi_Tri() {
		if (HOME_FLAG == 1) {
				if (VUONG == 16) {vi_tri = 1;} else if (TAM_GIAC == 32) {vi_tri = 2;} else if (O == 8) {vi_tri = 3;}
				if (vi_tri != 0 && O != 8 && TAM_GIAC != 32 && VUONG != 16) {HOME_FLAG = 0;}
		} else if (HOME_FLAG == 0) {		
				if (vi_tri == 1) {chay_toi_diem(2.5, 0.0, 2.0, 5.4, 400, 1.0f);} // Chay trai
				else if (vi_tri == 2 || vi_tri == 0) {chay_toi_diem(2.5, 0.0, 4.0, 5.4, 400, 1.0f);} // Chay giua					
				else if (vi_tri == 3) {chay_toi_diem(2.5, 0.0, 6.5, 5.4, 400, 1.0f);} // Chay phai			
	  }			
}



