


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


