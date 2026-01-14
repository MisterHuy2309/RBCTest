


////   u8 flag_xuong=0,flag_len=0, bien_cam_bien_truoc_1=0,bien_cam_bien_sau_1=0 ,flag_400=0,flag_200=0 ,bien_da_hoan_thanh_leo=0 ;  
////		
////		vu16 khoan_cach_nang_200=15300, khoan_cach_nang_400=30200;








////static inline vs32 clamp_vs32(vs32 v, vs32 lo, vs32 hi) {
////    if (v < lo) return lo;
////    if (v > hi) return hi;
////    return v;
////}


////vs32 nang_chan_tu_tu(vs32 target, vs32 current, float speed, vs32 cham_cap_2, float ty_le_giam_toc) {
////  
////    if (speed < 0.0f) speed = -speed;
////    if (ty_le_giam_toc <= 0.0f) ty_le_giam_toc = 0.05f;
////    if (ty_le_giam_toc > 1.0f) ty_le_giam_toc = 1.0f;

////    vs32 khoang_cach = (current < target) ? (target - current) : (current - target);


////    if (khoang_cach == 0) {

////        return clamp_vs32(current, 0, 30200);
////    }


////    float delta_f;
////    if (khoang_cach >= cham_cap_2 || cham_cap_2 <= 0) {
////        delta_f = speed;
////    } else {
////   
////        float t = (float)khoang_cach / (float)cham_cap_2; 

////        delta_f = speed * (ty_le_giam_toc + (1.0f - ty_le_giam_toc) * t);

////        if (delta_f > speed) delta_f = speed;
////    }


////    vs32 delta = (vs32)ceilf(delta_f);
////    if (delta < 1) delta = 1;


////    if (khoang_cach <= (vs32)delta) {
////        current = target;
////    } else {
////        if (current < target) {
////            current += delta;
////        } else {
////            current -= delta;
////        }
////    }

//// 
////    current = clamp_vs32(current, 0, 30200);

////    return current;
////}



////void robot_leo_bac_200() {

////    if (flag_len == 1) {
////        nang_chan_phai = nang_chan_tu_tu(15300, nang_chan_phai, 10.0f, 50, 0.1f);
////        nang_chan_trai  = nang_chan_tu_tu(15300, nang_chan_trai,  10.0f, 50, 0.1f);
////        nang_chan_sau   = nang_chan_tu_tu(15300, nang_chan_sau,   10.0f, 50, 0.1f);
////    }

////    if (bien_cam_bien_truoc_1 == 1) {

////        flag_len = 2;
////        nang_chan_phai = nang_chan_tu_tu(0, nang_chan_phai, 10.0f, 50, 0.1f);
////        nang_chan_trai  = nang_chan_tu_tu(0, nang_chan_trai,  10.0f, 50, 0.1f);
////        nang_chan_sau   = nang_chan_tu_tu(15300, nang_chan_sau, 10.0f,50, 0.1f);

////    }

////    if (bien_cam_bien_sau_1 == 1) {

////        bien_cam_bien_truoc_1 = 0;
////        nang_chan_phai = nang_chan_tu_tu(0, nang_chan_phai, 10.0f, 2200, 0.1f);
////        nang_chan_trai  = nang_chan_tu_tu(0, nang_chan_trai,  10.0f, 2200, 0.1f);
////        nang_chan_sau   = nang_chan_tu_tu(0, nang_chan_sau,   10.0f, 2200, 0.1f);


////    }


////    DC_nang_sau(nang_chan_sau);
////    DC_nang_trai(nang_chan_trai);
////    DC_nang_phai(nang_chan_phai);
////}

////void robot_xuong_bac_200() {
////    if (TAM_GIAC) bien_cam_bien_truoc_1 = 1;
////    if (X)      bien_cam_bien_sau_1   = 1;

////    if (flag_xuong == 1) {
////        nang_chan_phai = nang_chan_tu_tu(0, nang_chan_phai, 10.0f, 2200, 0.1f);
////        nang_chan_trai  = nang_chan_tu_tu(0, nang_chan_trai,  10.0f, 2200, 0.1f);
////        nang_chan_sau   = nang_chan_tu_tu(0, nang_chan_sau,   10.0f, 2200, 0.1f);
////    }

////    if (bien_cam_bien_truoc_1 == 1) {
////        flag_xuong = 2;
////        nang_chan_phai = nang_chan_tu_tu(15300, nang_chan_phai, 10.0f, 2200, 0.1f);
////        nang_chan_trai  = nang_chan_tu_tu(15300, nang_chan_trai, 10.0f, 2200, 0.1f);
////        nang_chan_sau   = nang_chan_tu_tu(0, nang_chan_sau,    10.0f, 2200, 0.1f);
////    }

////    if (bien_cam_bien_sau_1 == 1) {
////        bien_cam_bien_truoc_1 = 0;
////        nang_chan_phai = nang_chan_tu_tu(15300, nang_chan_phai, 10.0f, 2200, 0.1f);
////        nang_chan_trai  = nang_chan_tu_tu(15300, nang_chan_trai, 10.0f, 2200, 0.1f);
////        nang_chan_sau   = nang_chan_tu_tu(15300, nang_chan_sau, 10.0f, 2200, 0.1f);
////    }

////    DC_nang_sau(nang_chan_sau);
////    DC_nang_trai(nang_chan_trai);
////    DC_nang_phai(nang_chan_phai);
////}


////void robot_leo_bac_400() {
////    if (flag_len == 1) {
////        nang_chan_phai = nang_chan_tu_tu(30200, nang_chan_phai, 10.0f, 4200, 0.1f);
////        nang_chan_trai  = nang_chan_tu_tu(30200, nang_chan_trai,  10.0f, 4200, 0.1f);
////        nang_chan_sau   = nang_chan_tu_tu(30290, nang_chan_sau,   10.0f, 4200, 0.1f);
////    }

////    if (bien_cam_bien_truoc_1 == 1) {
////        flag_len = 2;
////        nang_chan_phai = nang_chan_tu_tu(0, nang_chan_phai, 10.0f, 4200, 0.1f);
////        nang_chan_trai  = nang_chan_tu_tu(0, nang_chan_trai,  10.0f, 4200, 0.1f);
////        nang_chan_sau   = nang_chan_tu_tu(30290, nang_chan_sau, 10.0f,4200,0.1f);
////    }

////    if (bien_cam_bien_sau_1 == 1) {
////        bien_cam_bien_truoc_1 = 0;
////        nang_chan_phai = nang_chan_tu_tu(0, nang_chan_phai, 10.0f, 4200, 0.1f);
////        nang_chan_trai  = nang_chan_tu_tu(0, nang_chan_trai,  10.0f, 4200, 0.1f);
////        nang_chan_sau   = nang_chan_tu_tu(0, nang_chan_sau,   10.0f, 4200, 0.1f);
////    }

////    DC_nang_sau(nang_chan_sau);
////    DC_nang_trai(nang_chan_trai);
////    DC_nang_phai(nang_chan_phai);
////}

////void robot_xuong_bac_400() {
////    if (TAM_GIAC) bien_cam_bien_truoc_1 = 1;
////    if (X)      bien_cam_bien_sau_1   = 1;

////    if (flag_xuong == 1) {
////        nang_chan_phai = nang_chan_tu_tu(0, nang_chan_phai, 10.0f, 4200, 0.1f);
////        nang_chan_trai  = nang_chan_tu_tu(0, nang_chan_trai,  10.0f, 4200, 0.1f);
////        nang_chan_sau   = nang_chan_tu_tu(0, nang_chan_sau,   10.0f, 4200, 0.1f);
////    }

////    if (bien_cam_bien_truoc_1 == 1) {
////        flag_xuong = 2;
////        nang_chan_phai = nang_chan_tu_tu(30200, nang_chan_phai, 10.0f, 4200, 0.1f);
////        nang_chan_trai  = nang_chan_tu_tu(30200, nang_chan_trai, 10.0f, 4200, 0.1f);
////        nang_chan_sau   = nang_chan_tu_tu(0, nang_chan_sau,    10.0f, 4200, 0.1f);
////    }

////    if (bien_cam_bien_sau_1 == 1) {
////        bien_cam_bien_truoc_1 = 0;
////        nang_chan_phai = nang_chan_tu_tu(30200, nang_chan_phai, 10.0f, 4200, 0.1f);
////        nang_chan_trai  = nang_chan_tu_tu(30200, nang_chan_trai, 10.0f, 4200, 0.1f);
////        nang_chan_sau   = nang_chan_tu_tu(30290, nang_chan_sau, 10.0f, 4200, 0.1f);
////    }

////    DC_nang_sau(nang_chan_sau);
////    DC_nang_trai(nang_chan_trai);
////    DC_nang_phai(nang_chan_phai);
////}

//#include <stdlib.h>
//#include <math.h>



//// --- Ð?NH NGHIA HU?NG CH?Y (Tùy ch?nh theo la bàn robot c?a b?n) ---
//#define HUONG_LEN    0       // Góc 0 d?
//#define HUONG_PHAI   900     // Góc 90 d?
//#define HUONG_XUONG  1800    // Góc 180 d?
//#define HUONG_TRAI   -900    // Góc -90 d?

//// --- THÔNG S? CH?Y ---
//#define TOC_DO_AUTO  300     // T?c d? ch?y t? d?ng
//#define GIA_TOC_AUTO 1.0     // Gia t?c
//#define QUANG_DUONG_1_O 1000 // Encoder tuong ?ng v?i 1 ô (User cung c?p 1000)

////// --- BI?N TOÀN C?C ---
////extern vs32 ENCODER_TIMER2;
////extern vu8 RX_USART6[60];

//// Khai báo l?i hàm c?a b?n d? trình biên d?ch không báo l?i
////void MAIN_CONTROL(vs32 _mat_robot, vs32 _huong_chay, vs32 _toc_do, float _gia_toc, float _chay_va_xoay);

////// --- HÀM Ð?C ENCODER C?A B?N ---
////s32 READ_ENCODER_2(void)
////{
////    vs32 enNew, enOld = ENCODER_TIMER2;
////    int i = 0;
////    while( i < 2)
////    {
////        enNew = ENCODER_TIMER2;
////        if(abs(enNew) - abs(enOld) < 50000) i++;
////        enOld = enNew;
////        if(i > 65000) break;
////    }
////    return enNew;
////}

//// --- HÀM TÍNH HU?NG T? Ô A SANG Ô B ---
//// Tr? v? góc c?n ch?y d? di t? start_cell d?n end_cell
//vs32 TINH_HUONG_DI_CHUYEN(u8 start_cell, u8 end_cell) {
//    if (start_cell == 0 || end_cell == 0) return 0;

//    // Tính t?a d? (Hàng, C?t)
//    // -1 vì ô b?t d?u t? 1, t?a d? tính t? 0
//    int r1 = (start_cell - 1) / 3; 
//    int c1 = (start_cell - 1) % 3;
//    
//    int r2 = (end_cell - 1) / 3;
//    int c2 = (end_cell - 1) % 3;

//    int delta_row = r2 - r1;
//    int delta_col = c2 - c1;

//    // Logic xác d?nh hu?ng
//    if (delta_row > 0) return HUONG_LEN;    // Ði lên (ví d?: 1 -> 4)
//    if (delta_row < 0) return HUONG_XUONG;  // Ði xu?ng (ví d?: 4 -> 1)
//    if (delta_col > 0) return HUONG_PHAI;   // Ði ph?i (ví d?: 1 -> 2)
//    if (delta_col < 0) return HUONG_TRAI;   // Ði trái (ví d?: 2 -> 1)

//    return 0; // Ð?ng yên n?u trùng ô
//}

//// --- HÀM CH?Y T? Ð?NG THEO CHU?I ---
//void RUN_AUTO_PATH(void) {
//    // 1. Luu chu?i du?ng di vào m?ng d? d? x? lý
//    u8 path[8] = {BYTE1, BYTE2, BYTE3, BYTE4, BYTE5, BYTE6, BYTE7, BYTE8};
//    
//    // Bi?n luu v? trí encoder lúc b?t d?u m?i do?n
//    s32 start_encoder_val = 0;
//    s32 current_encoder_val = 0;
//    vs32 huong_can_chay = 0;

//    // 2. Vòng l?p duy?t qua t?ng di?m trong l? trình
//    // Ch?y t? di?m i d?n di?m i+1 (ví d?: path[0] -> path[1])
//    for (int i = 0; i < 7; i++) {
//        
//        u8 diem_hien_tai = path[i];
//        u8 diem_tiep_theo = path[i+1];

//        // N?u g?p s? 0 ho?c h?t du?ng thì d?ng l?i
//        if (diem_tiep_theo == 0) break;

//        // 3. Tính toán hu?ng c?n ch?y
//        huong_can_chay = TINH_HUONG_DI_CHUYEN(diem_hien_tai, diem_tiep_theo);

//        // 4. Reset m?c Encoder (L?y giá tr? hi?n t?i làm m?c 0)
//        start_encoder_val = READ_ENCODER_2();

//        // 5. Vòng l?p di chuy?n (BLOCKING - Ch?n chuong trình cho d?n khi d?n noi)
//        while (1) {
//            // G?i hàm di?u khi?n: Ch?y th?ng theo hu?ng dã tính
//            // _mat_robot = 0 (gi? hu?ng m?t), _gia_toc = GIA_TOC_AUTO, _chay_va_xoay = 0 (không xoay)
//            MAIN_CONTROL(0, huong_can_chay, TOC_DO_AUTO, GIA_TOC_AUTO, 0);

//            // Ki?m tra quãng du?ng
//            current_encoder_val = READ_ENCODER_2();
//            
//            // Tính kho?ng cách tuy?t d?i dã di du?c so v?i m?c b?t d?u
//            if (abs(current_encoder_val - start_encoder_val) >= QUANG_DUONG_1_O) {
//                break; // Ðã di d? quãng du?ng 1 ô -> Thoát vòng l?p di chuy?n
//            }
//        }
//        
//        // (Tùy ch?n) D?ng ng?n gi?a các ô d? ?n d?nh quán tính n?u c?n
//        // MAIN_CONTROL(0, huong_can_chay, 0, 5.0, 0); 
//        // delay_ms(100);
//    }

//    // 6. K?t thúc hành trình: D?ng Robot
//    MAIN_CONTROL(0, 0, 0, 5.0, 0);
//}

