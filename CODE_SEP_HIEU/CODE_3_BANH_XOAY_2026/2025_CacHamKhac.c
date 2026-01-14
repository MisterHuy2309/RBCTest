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













