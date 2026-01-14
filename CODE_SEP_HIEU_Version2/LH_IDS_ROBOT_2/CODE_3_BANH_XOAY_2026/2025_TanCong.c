//================= Function: Tinh toan khoang cach va huong di chuyen ===================================================================
#define M_PI 3.141592653589793238462643383279
#define DUONG_KINH_BANH_XE 70.0 //90.0
#define XUNG_MOI_VONG 26000 //22000
//#define M_PI 3.141592653589793238462643383279
//#define DUONG_KINH_BANH_XE 80.0 //90.0
//#define XUNG_MOI_VONG 23000 //22000
   u8 flag_xuong=0,flag_len=0, bien_cam_bien_truoc_1=0,bien_cam_bien_sau_1=0 ,flag_400=0,flag_200=0 ,bien_da_hoan_thanh_leo=0 ;  
		
		vu16 khoan_cach_nang_200=15000, khoan_cach_nang_400=30000;
		
		
		
//		
//float tinh_khoang_cach(float x1, float y1, float x2, float y2) {
//    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
//}

//vs32 tinh_huong(float x1, float y1, float x2, float y2) {
//    float dx = x2 - x1;
//    float dy = y2 - y1;
//    float angleRad = atan2(dx, dy); // Tinh goc radian
//    float angleDeg = angleRad * (180.0 / M_PI); // Doi goc radian sang do
//    vs32 pulses = (vs32)(angleDeg * 10); // Nhan 10 de trung voi MAIN CONTROL 
//    return -pulses;
//}

//void chay_toi_diem(float x1, float y1, float x2, float y2, vs32 toc_do_toi_da, float he_so_xung) {
//		vs32 huong_chay = tinh_huong(x1, y1, x2, y2);	
//		float khoang_cach = tinh_khoang_cach(x1, y1, x2, y2);
//		float chu_vi_banh_xe = M_PI * DUONG_KINH_BANH_XE; // Chu vi bánh xe (mm)
//	  float gt_qduong;	
//		vs32 toc_do = toc_do_toi_da;
//		s32 encoder_max = 0;
//	
//		#define NGUONG_ENCODER 1000000 // Nguong xung encoder cho phep 
//		#define DO_LECH_TOI_DA 50000  // Xung encoder cho phep lech giua 3 banh
//		
//		// Loai bo encoder bi vuot nguong xung cho phep
////		s32 e1 = (ENCODER_TRAI < NGUONG_ENCODER) ? ENCODER_TRAI : 0;
////		s32 e2 = (ENCODER_PHAI < NGUONG_ENCODER) ? ENCODER_PHAI : 0;
////		s32 e3 = (ENCODER_SAU  < NGUONG_ENCODER) ? ENCODER_SAU  : 0;

//		// Loai bo encoder bi lech qua nhieu so voi 2 encoder con lai
//		if (abs(e1 - e2) > DO_LECH_TOI_DA && abs(e1 - e3) > DO_LECH_TOI_DA)
//				e1 = 0;  // e1 lech qua nhieu
//		if (abs(e2 - e1) > DO_LECH_TOI_DA && abs(e2 - e3) > DO_LECH_TOI_DA)
//				e2 = 0;  // e2 lech qua nhieu
//		if (abs(e3 - e1) > DO_LECH_TOI_DA && abs(e3 - e2) > DO_LECH_TOI_DA)
//				e3 = 0;  // e3 lech qua nhieu

//		// Tim encoder lon nhat trong so encoder hop le
//		if (e1 > encoder_max) encoder_max = e1;
//		if (e2 > encoder_max) encoder_max = e2;
//		if (e3 > encoder_max) encoder_max = e3;
//		
//		// Tinh muc tieu xung va xung con lai 
//		muc_tieu_xung = (s32)(((khoang_cach * 1000.0f) / chu_vi_banh_xe * XUNG_MOI_VONG) * he_so_xung); 
//		xung_con_lai = muc_tieu_xung - encoder_max;
//	
//	
//		if (cho_phep_chay == true) {
//				if (xung_con_lai > 0) {
//						// === Giam toc do tuyen tinh khi con 1/3 quang duong ===						
//						if (xung_con_lai <= muc_tieu_xung * 0.35) {
//								toc_do = (vs32)(toc_do_toi_da * ((float)xung_con_lai / ((float)muc_tieu_xung / 3.0f)));
//						}						
//						
//            // === Dieu chinh toc do theo quang duong ===						
//						if (xung_con_lai <= muc_tieu_xung * 0.1 || khoang_cach <= 1.0) {toc_do = 120;} // Khi gan dung
//						else if (toc_do < 150) {toc_do = 150;} // Gioi han toc do thap						
//						else if (toc_do > toc_do_toi_da) {toc_do = toc_do_toi_da;} // Gioi han toc do cao
//						toc_do_test = toc_do;					
//						
//            // === Dieu chinh gia toc theo quang duong ===
//            if (xung_con_lai <= muc_tieu_xung * 0.2) {gt_qduong = 0.7;} // Khi gan dung
//            else if (xung_con_lai <= muc_tieu_xung * 0.8) {gt_qduong = 0.3; touchpad_flag = 1;} // Khi chay on dinh
//            else {gt_qduong = 0.5;} // Khi khoi dong
//						
//						MAIN_CONTROL(0, huong_chay, toc_do, gt_qduong, 0);

//				} else {CONTROL_TOC_DO(0, 0.8, 0); cho_phep_chay = false;}	
//	  }
//}







////================= Function: Chay 3 vi tri: Trai, giua, phai khi nhan bong ===================================================================
//void Chay_Vi_Tri() {
//		if (HOME_FLAG == 1) {
//				if (VUONG == 16) {vi_tri = 1;} else if (TAM_GIAC == 32) {vi_tri = 2;} else if (O == 8) {vi_tri = 3;}
//				if (vi_tri != 0 && O != 8 && TAM_GIAC != 32 && VUONG != 16) {HOME_FLAG = 0;}
//		} else if (HOME_FLAG == 0) {		
//				if (vi_tri == 1) {chay_toi_diem(2.5, 0.0, 2.0, 5.4, 400, 1.0f);} // Chay trai
//				else if (vi_tri == 2 || vi_tri == 0) {chay_toi_diem(2.5, 0.0, 4.0, 5.4, 400, 1.0f);} // Chay giua					
//				else if (vi_tri == 3) {chay_toi_diem(2.5, 0.0, 6.5, 5.4, 400, 1.0f);} // Chay phai			
//	  }			
//}

//+++++++++++++++ robot leo va xuong bac   +++++++++++++++++++++++++++++++++++++++++++++++++=








////+++++++++++++++++++++++++++++++++++++++

//vs32 nang_chan_tu_tu(vs32 target, vs32 current, float speed, vs32 cham_cap_2, float ty_le_giam_toc) {
//    vs32 delta;
//    vs32 khoang_cach = (current < target) ? (target - current) : (current - target);
//    
//    // N?u kho?ng cách còn l?i nh? hon ngu?ng ch?m c?p 2, gi?m t?c d?
//    if (khoang_cach <= cham_cap_2) {
//        delta = (vs32)(speed * ty_le_giam_toc);  // Gi?m t?c d? theo t? l?
//        if (delta < 1) delta = 1;                 // Ð?m b?o v?n di chuy?n
//    } else {
//        delta = (vs32)(speed * 1.0f);
//    }
//    
//    if (current < target) {
//        current += delta;
//        if (current > target) current = target;
//    } else if (current > target) {
//        current -= delta;
//        if (current < target) current = target;
//    }
//   
//    // Gi?i h?n giá tr?
//    if (current < 0)     current = 0;
//    if (current > 28000) current = 28000;
//    
//    return current;
//}









////_____________________________________leo_______200__________________________________
//void robot_leo_bac_200(){
//	

//			
//			if(flag_len==1)				
//			{				
//					nang_chan_phai = nang_chan_tu_tu(15300, nang_chan_phai, 10.0f, 50, 0.1f);
//					nang_chan_trai = nang_chan_tu_tu(15300, nang_chan_trai, 10.0f, 50, 0.1f);
//					nang_chan_sau = nang_chan_tu_tu(15300, nang_chan_sau, 10.0f, 50, 0.1f);

//			}
//		
//						
//      if(bien_cam_bien_truoc_1==1)
//				{
//				flag_len=2;
//					nang_chan_phai = nang_chan_tu_tu(0, nang_chan_phai, 10.0f, 50, 0.1f);
//					nang_chan_trai = nang_chan_tu_tu(0, nang_chan_trai, 10.0f, 50, 0.1f);
//          nang_chan_sau = nang_chan_tu_tu(15300, nang_chan_sau, 10.0f, 50, 0.1f);

//					
//					
//					
//					
//				
//			}
//					
//						if(bien_cam_bien_sau_1==1)
//							{
//					bien_cam_bien_truoc_1=0;
//					nang_chan_phai = nang_chan_tu_tu(0, nang_chan_phai, 10.0f, 2200, 0.1f);
//					nang_chan_trai = nang_chan_tu_tu(0, nang_chan_trai, 10.0f, 2200, 0.1f);				
//					nang_chan_sau = nang_chan_tu_tu(0, nang_chan_sau, 10.0f, 2200, 0.1f);
//          		
//			}
//			
//					DC_nang_sau(nang_chan_sau);
//			    DC_nang_trai(nang_chan_trai);
//				  DC_nang_phai(nang_chan_phai);

//}


////_______________xuong_______200_________________

//void robot_xuong_bac_200()
//	{

//			if(TAM_GIAC) bien_cam_bien_truoc_1=1   ;
//			if(X)bien_cam_bien_sau_1 =1;
//			if(flag_xuong==1)				
//			{				
//					nang_chan_phai = nang_chan_tu_tu(0, nang_chan_phai, 10.0f, 2200, 0.1f);
//					nang_chan_trai = nang_chan_tu_tu(0, nang_chan_trai, 10.0f, 2200, 0.1f);
//					nang_chan_sau = nang_chan_tu_tu(0, nang_chan_sau, 10.0f, 2200, 0.1f);

//			}
//						
//      if(bien_cam_bien_truoc_1==1)
//				{
//				flag_xuong=2;
//					nang_chan_phai = nang_chan_tu_tu(15300, nang_chan_phai, 10.0f, 2200, 0.1f);
//					nang_chan_trai = nang_chan_tu_tu(15300, nang_chan_trai,10.0f, 2200, 0.1f);
//          nang_chan_sau = nang_chan_tu_tu(0, nang_chan_sau, 10.0f, 2200, 0.1f);
//				
//			}
//					
//						if(bien_cam_bien_sau_1==1)
//							{
//         bien_cam_bien_truoc_1=0;
//					nang_chan_phai = nang_chan_tu_tu(15300, nang_chan_phai,10.0f, 2200, 0.1f);
//					nang_chan_trai = nang_chan_tu_tu(15300, nang_chan_trai, 10.0f, 2200, 0.1f);				
//					nang_chan_sau = nang_chan_tu_tu(15300, nang_chan_sau, 10.0f, 2200, 0.1f);
//          		
//			}
//			
//					DC_nang_sau(nang_chan_sau);
//			    DC_nang_trai(nang_chan_trai);
//				  DC_nang_phai(nang_chan_phai);
//		
//}


////++++++++++++leo 400++++++++++++++++++++++++++++++
//void robot_leo_bac_400(){
//	

//			
//			if(flag_len==1)				
//			{				
//					nang_chan_phai = nang_chan_tu_tu(28000, nang_chan_phai, 10.0f, 4200, 0.1f);
//					nang_chan_trai = nang_chan_tu_tu(28000, nang_chan_trai, 10.0f, 4200, 0.1f);
//					nang_chan_sau = nang_chan_tu_tu(28000, nang_chan_sau, 10.0f, 4200, 0.1f);

//			}
//						
//      if(bien_cam_bien_truoc_1==1)
//				{
//				flag_len=2;
//					nang_chan_phai = nang_chan_tu_tu(0, nang_chan_phai, 10.0f, 4200, 0.1f);
//					nang_chan_trai = nang_chan_tu_tu(0, nang_chan_trai, 10.0f, 4200, 0.1f);
//          nang_chan_sau = nang_chan_tu_tu(28000, nang_chan_sau, 10.0f, 4200, 0.1f);
//				
//			}
//					
//						if(bien_cam_bien_sau_1==1)
//							{
//         bien_cam_bien_truoc_1=0;
//					nang_chan_phai = nang_chan_tu_tu(0, nang_chan_phai, 10.0f, 4200, 0.1f);
//					nang_chan_trai = nang_chan_tu_tu(0, nang_chan_trai, 10.0f, 4200, 0.1f);				
//					nang_chan_sau = nang_chan_tu_tu(0, nang_chan_sau, 10.0f, 4200, 0.1f);
//          		
//			}
//			
//					DC_nang_sau(nang_chan_sau);
//			    DC_nang_trai(nang_chan_trai);
//				  DC_nang_phai(nang_chan_phai);
//		
//}
////+++++++++++++++++++++++++++++++++++++++

//void robot_xuong_bac_400(){
//		
//			if(TAM_GIAC) bien_cam_bien_truoc_1=1   ;
//			if(X)bien_cam_bien_sau_1 =1;
//	
//			if(flag_xuong==1)				
//			{				
//					nang_chan_phai = nang_chan_tu_tu(0, nang_chan_phai, 10.0f, 4200, 0.1f);
//					nang_chan_trai = nang_chan_tu_tu(0, nang_chan_trai, 10.0f, 4200, 0.1f);
//					nang_chan_sau = nang_chan_tu_tu(0, nang_chan_sau, 10.0f, 4200, 0.1f);

//			}
//						
//      if(bien_cam_bien_truoc_1==1)
//				{
//				flag_xuong=2;
//					nang_chan_phai = nang_chan_tu_tu(28000, nang_chan_phai, 10.0f, 4200, 0.1f);
//					nang_chan_trai = nang_chan_tu_tu(28000, nang_chan_trai, 10.0f, 4200, 0.1f);
//          nang_chan_sau = nang_chan_tu_tu(0, nang_chan_sau, 10.0f, 4200, 0.1f);
//				
//			}
//					
//						if(bien_cam_bien_sau_1==1)
//							{
//         bien_cam_bien_truoc_1=0;
//					nang_chan_phai = nang_chan_tu_tu(28000, nang_chan_phai, 10.0f, 4200, 0.1f);
//					nang_chan_trai = nang_chan_tu_tu(28000, nang_chan_trai, 10.0f, 4200, 0.1f);				
//					nang_chan_sau = nang_chan_tu_tu(28000, nang_chan_sau, 10.0f, 4200, 0.1f);
//          		
//			}
//			
//					DC_nang_sau(nang_chan_sau);
//			    DC_nang_trai(nang_chan_trai);
//				  DC_nang_phai(nang_chan_phai);
//		
//}
//static inline vs32 clamp_vs32(vs32 v, vs32 lo, vs32 hi) {
//    if (v < lo) return lo;
//    if (v > hi) return hi;
//    return v;
//}


//vs32 nang_chan_tu_tu(vs32 target, vs32 current, float speed, vs32 cham_cap_2, float ty_le_giam_toc) {
//    // an toàn: d?m b?o speed >= 0, ty_le_giam_toc trong (0,1]
//    if (speed < 0.0f) speed = -speed;
//    if (ty_le_giam_toc <= 0.0f) ty_le_giam_toc = 0.05f;
//    if (ty_le_giam_toc > 1.0f) ty_le_giam_toc = 1.0f;

//    vs32 khoang_cach = (current < target) ? (target - current) : (current - target);

//    // N?u dã t?i ho?c b?ng target thì tr? v? ngay
//    if (khoang_cach == 0) {
//        // v?n clamp d? an toàn
//        return clamp_vs32(current, 0, 28000);
//    }

//    // Tính delta (s? don v? di chuy?n l?n này)
//    // Ý tu?ng: khi xa target dùng full speed,
//    // khi trong vùng cham_cap_2 gi?m tuy?n tính xu?ng t?i speed * ty_le_giam_toc
//    float delta_f;
//    if (khoang_cach >= cham_cap_2 || cham_cap_2 <= 0) {
//        delta_f = speed;
//    } else {
//        // t: t? l? kho?ng cách trong vùng gi?m t?c (0..1)
//        float t = (float)khoang_cach / (float)cham_cap_2; // t = 0 (trùng) .. 1 (v?a ch?m ngu?ng)
//        // gi?m tuy?n tính: delta = speed * (ty_le_giam_toc + (1 - ty_le_giam_toc) * t)
//        delta_f = speed * (ty_le_giam_toc + (1.0f - ty_le_giam_toc) * t);
//        // d?m b?o không l?n hon speed
//        if (delta_f > speed) delta_f = speed;
//    }

//    // chuy?n sang vs32, dùng ceil d? không b? stuck khi delta_f < 1
//    vs32 delta = (vs32)ceilf(delta_f);
//    if (delta < 1) delta = 1;

//    // Không overshoot: n?u còn cách nh? hon delta thì d?t tr?c ti?p t?i target
//    if (khoang_cach <= (vs32)delta) {
//        current = target;
//    } else {
//        if (current < target) {
//            current += delta;
//        } else {
//            current -= delta;
//        }
//    }

//    // Clamp giá tr? theo gi?i h?n h? th?ng
//    current = clamp_vs32(current, 0, 28000);

//    return current;
//}

//// ---------------- Các hàm robot (leo/xu?ng) ----------------
//// Tôi gi? c?u trúc nhung có logic rõ ràng: khi m?t c?m bi?n hoàn thành
//// thì ta ch? set flag x? lý 1 l?n (clear trong hàm x? lý n?u c?n).

//void robot_leo_bac_200() {
//    // Ví d? các target/layout b?n dùng tru?c: 0 ho?c 15300 cho 200
//    if (flag_len == 1) {
//        nang_chan_phai = nang_chan_tu_tu(15300, nang_chan_phai, 10.0f, 50, 0.1f);
//        nang_chan_trai  = nang_chan_tu_tu(15300, nang_chan_trai,  10.0f, 50, 0.1f);
//        nang_chan_sau   = nang_chan_tu_tu(15300, nang_chan_sau,   10.0f, 50, 0.1f);
//    }

//    if (bien_cam_bien_truoc_1 == 1) {
//        // chuy?n tr?ng thái: dã ch?m tru?c nên chu?n b? d?t chân sau
//        flag_len = 2;
//        nang_chan_phai = nang_chan_tu_tu(0, nang_chan_phai, 10.0f, 50, 0.1f);
//        nang_chan_trai  = nang_chan_tu_tu(0, nang_chan_trai,  10.0f, 50, 0.1f);
//        nang_chan_sau   = nang_chan_tu_tu(15300, nang_chan_sau, 10.0f,50, 0.1f);
//        // Không t? reset bien_cam_bien_truoc_1 ? dây; d? c?m bi?n/h? th?ng khác quy?t d?nh
//    }

//    if (bien_cam_bien_sau_1 == 1) {
//        // Khi c?m bi?n sau kích ho?t -> hoàn thành bu?c leo
//        // Tùy m?c dích, có th? reset bien_cam_bien_truoc_1 d? b?t d?u chu trình ti?p theo
//        bien_cam_bien_truoc_1 = 0;
//        nang_chan_phai = nang_chan_tu_tu(0, nang_chan_phai, 10.0f, 2200, 0.1f);
//        nang_chan_trai  = nang_chan_tu_tu(0, nang_chan_trai,  10.0f, 2200, 0.1f);
//        nang_chan_sau   = nang_chan_tu_tu(0, nang_chan_sau,   10.0f, 2200, 0.1f);

//        // Sau khi hoàn thành, b?n có th? reset bien_cam_bien_sau_1 = 0 n?u c?m bi?n không auto reset
//        // bien_cam_bien_sau_1 = 0;
//    }

//    // Xu?t ra driver PWM / DC
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

//// ---- phiên b?n 400 (tuong t?) ----
//void robot_leo_bac_400() {
//    if (flag_len == 1) {
//        nang_chan_phai = nang_chan_tu_tu(28000, nang_chan_phai, 10.0f, 4200, 0.1f);
//        nang_chan_trai  = nang_chan_tu_tu(28000, nang_chan_trai,  10.0f, 4200, 0.1f);
//        nang_chan_sau   = nang_chan_tu_tu(28000, nang_chan_sau,   10.0f, 4200, 0.1f);
//    }

//    if (bien_cam_bien_truoc_1 == 1) {
//        flag_len = 2;
//        nang_chan_phai = nang_chan_tu_tu(0, nang_chan_phai, 10.0f, 4200, 0.1f);
//        nang_chan_trai  = nang_chan_tu_tu(0, nang_chan_trai,  10.0f, 4200, 0.1f);
//        nang_chan_sau   = nang_chan_tu_tu(28000, nang_chan_sau, 10.0f,4200,0.1f);
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
//        nang_chan_phai = nang_chan_tu_tu(28000, nang_chan_phai, 10.0f, 4200, 0.1f);
//        nang_chan_trai  = nang_chan_tu_tu(28000, nang_chan_trai, 10.0f, 4200, 0.1f);
//        nang_chan_sau   = nang_chan_tu_tu(0, nang_chan_sau,    10.0f, 4200, 0.1f);
//    }

//    if (bien_cam_bien_sau_1 == 1) {
//        bien_cam_bien_truoc_1 = 0;
//        nang_chan_phai = nang_chan_tu_tu(28000, nang_chan_phai, 10.0f, 4200, 0.1f);
//        nang_chan_trai  = nang_chan_tu_tu(28000, nang_chan_trai, 10.0f, 4200, 0.1f);
//        nang_chan_sau   = nang_chan_tu_tu(28000, nang_chan_sau, 10.0f, 4200, 0.1f);
//    }

//    DC_nang_sau(nang_chan_sau);
//    DC_nang_trai(nang_chan_trai);
//    DC_nang_phai(nang_chan_phai);
//}


