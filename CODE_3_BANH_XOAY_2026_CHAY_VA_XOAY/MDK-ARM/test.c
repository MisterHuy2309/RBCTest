
void Chay_Tay(){
                       ////////////////////LAY-LUA/////////////////  	
	  if(SELECT==0){			
									while(1){
											quet_tay_ban_banh();
											if(X==0)         {xilanh_nang_lua_2;xilanh_ha_lua_1;}
											if(TAM_GIAC==0)  {xilanh_nang_lua_1;xilanh_ha_lua_2;}																															
											if(L1==0&&R1==0) {xilanh_co_tay_gap_lua;}
											if(L1==0&&R2==0) {xilanh_duoi_tay_gap_lua;}
											if(L2==0&&R1==0) {xilanh_tay_gap_1_nha;xilanh_tay_gap_3_nha;}
											if(L2==0&&R2==0) {xilanh_tay_gap_2_nha;xilanh_tay_gap_4_nha;}
											if(O==0)         {xilanh_tay_gap_1_kep;xilanh_tay_gap_2_kep;xilanh_tay_gap_3_kep;xilanh_tay_gap_4_kep;}
											if(VUONG==0)     {xilanh_tay_gap_1_nha;xilanh_tay_gap_2_nha;xilanh_tay_gap_3_nha;xilanh_tay_gap_4_nha;}											
											if(START==0)      break;		 
												vTaskDelay(2);
								}
				   vTaskDelay(2);
	    }
///////////////////////////////////////////BAN_BANH//////////////////////////////
                  else
			                {	}
 }