
// ====================================================================


//void test_cb(void)
//{

//	
//	
//update_all_lasers();

//	


//    if (laser_truoc >= 70 && laser_truoc <= 130)   

//    {
//			flag_nang=1;
//			flag_ha=0; 
//    }
//		else if (laser_truoc < 70 && laser_truoc > 130) 
//		{

//			flag_ha=1; 
//			flag_nang=0;
//		}
//		
//		if(flag_nang==1)
//		{
//		    nang_chan_phai = nang_chan_tu_tu(20000, nang_chan_phai, 10.0f, 4200, 0.1f);
//        nang_chan_trai = nang_chan_tu_tu(20000, nang_chan_trai, 10.0f, 4200, 0.1f);
//        nang_chan_sau  = nang_chan_tu_tu(20000, nang_chan_sau , 10.0f, 4200, 0.1f);
//		
//		}
//		else if(flag_ha==1)
//		{
//			
//				nang_chan_phai = nang_chan_tu_tu(0, nang_chan_phai, 10.0f, 4200, 0.1f);
//        nang_chan_trai = nang_chan_tu_tu(0, nang_chan_trai, 10.0f, 4200, 0.1f);
//        nang_chan_sau  = nang_chan_tu_tu(0, nang_chan_sau , 10.0f, 4200, 0.1f);
//		}
//		
//		


//// dk dc
//		   if (laser_truoc >=55) MAIN_CONTROL(0,0,30,2,0);
//		
//		else if(laser_truoc <55) MAIN_CONTROL(0,0,1,2,0);
//		
//		
//		
//		
//		
//		
//		    DC_nang_phai(nang_chan_phai);
//        DC_nang_trai(nang_chan_trai);
//        DC_nang_sau (nang_chan_sau);
//		
//		
//}















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
void ham_leo_rung_trai()
{
	
	
	
	
	
	
	
	
}
	
	
	














