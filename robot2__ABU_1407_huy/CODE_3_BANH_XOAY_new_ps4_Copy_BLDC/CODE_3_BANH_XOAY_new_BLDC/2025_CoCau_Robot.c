  
//================= Function: co cau thu banh ===================================================================
void Co_Cau_Thu() {				
		if (gp_get_mode_uart() == 13) {					
				//------------- Nhan TOUCHPAD de bat / tat laze -------------------------
				//if (CB_Ban_NhanBong == 1) {xilanh_ban_kep; Laser_off;}			
				if (TOUCHPAD == 128 && prev_TOUCHPAD != 128) {touchpad_flag++;}				
				prev_TOUCHPAD = TOUCHPAD;
				if (touchpad_flag == 1) {Laser_on;} else {Laser_off; touchpad_flag = 0;}
					
				//------------- Nhan O de chuyen bong -------------------------					
				if (O == 8) {xilanh_ban_nha;} else {xilanh_ban_kep;}	
				
				//------------- Nhan TAM GIAC de nang co cau thu -------------------------	
				if (TAM_GIAC == 32) {xilanh_thu_nha;} else {xilanh_thu_kep;}
				
		} else {
				Laser_off; touchpad_flag = 0; xilanh_ban_kep; xilanh_thu_kep;
		}
}

//=========== Function: Co Cau Nang  ====================

