vs32 tang_toc_giam_toc,quet_nut,mat,gtoc,nho_IMU=4,analog,chay_xoay=150;//2000
vs32 huong_chay,BIT_NHO_CHAY,QUAT,toc_p;
float gt;
int p;
//================= Function: quet tay game ===================================================================
void quet_tay_game() {	
		
//khong co banh	
		if (!L1 && R1 && L2>25 ) { tang_toc_giam_toc=1*1; gt=1.2;	toc_p=tang_toc_giam_toc+21;}
		else if (L1 && !R1 ) 		 { tang_toc_giam_toc=30; 	gt=2;			toc_p=tang_toc_giam_toc+21;}
		else if (!L1 && R1 )     { tang_toc_giam_toc=20; gt=0.65;	toc_p=tang_toc_giam_toc+21;}	
		else 										 { tang_toc_giam_toc=25; gt=0.65;	  toc_p=tang_toc_giam_toc+21;}
		


////-----------------------------------------------------------------------------------------------		
		// khi co banh
		
//		if (gp_get_mode_uart() == GP_MODE_ANALOGUE_RED_LED ) {
				
			///////////////////////-----xoay tron
		
		
      
      
				 
		if (gp_get_mode_uart() == GP_MODE_ANALOGUE_RED_LED ) {
				
			///////////////////////-----xoay tron
				if(!TOI&&!TRAI&&!PHAI&&!LUI&&(NUM_PHAI_CHIEU_TRAI_PHAI>200)&&HUONG_GAME_CT<50 ){nho_IMU=IMU-chay_xoay*36;huong_chay=0; MAIN_CONTROL(nho_IMU,huong_chay,toc_p/5,gt*2,20);nho_IMU=IMU;BIT_NHO_CHAY=10;nho_IMU=IMU;}
				else if(!TOI&&!TRAI&&!PHAI&&!LUI&&(NUM_PHAI_CHIEU_TRAI_PHAI<50 )&&HUONG_GAME_CT<50 ){nho_IMU=IMU+chay_xoay*36;huong_chay=0;  MAIN_CONTROL(nho_IMU,huong_chay,toc_p/5,gt*2,20);nho_IMU=IMU;BIT_NHO_CHAY=10;nho_IMU=IMU;}
				
					/////////////////////////------------chay xoay		
				else if(TOI&&!TRAI&&!PHAI&&!LUI&&(NUM_PHAI_CHIEU_TRAI_PHAI>200)&&HUONG_GAME_CT<50 ){nho_IMU=IMU-chay_xoay;huong_chay=0;MAIN_CONTROL(nho_IMU,huong_chay,toc_p,gt,0);BIT_NHO_CHAY=10;nho_IMU=IMU;}
				else if(TOI&&!TRAI&&!PHAI&&!LUI&&(NUM_PHAI_CHIEU_TRAI_PHAI<50)&&HUONG_GAME_CT<50 ){nho_IMU=IMU+chay_xoay;huong_chay=0;MAIN_CONTROL(nho_IMU,huong_chay,toc_p,gt,0);BIT_NHO_CHAY=10;nho_IMU=IMU;}
				
				else if(!TOI&&TRAI&&!PHAI&&!LUI&&(NUM_PHAI_CHIEU_TRAI_PHAI>200)&&HUONG_GAME_CT<50 ){nho_IMU=IMU-chay_xoay;huong_chay=900;MAIN_CONTROL(nho_IMU,huong_chay,toc_p,gt,0);BIT_NHO_CHAY=10;nho_IMU=IMU;}
				else if(!TOI&&TRAI&&!PHAI&&!LUI&&(NUM_PHAI_CHIEU_TRAI_PHAI<50)&&HUONG_GAME_CT<50 ){nho_IMU=IMU+chay_xoay;huong_chay=900;MAIN_CONTROL(nho_IMU,huong_chay,toc_p,gt,0);BIT_NHO_CHAY=10;nho_IMU=IMU;}
				
				else if(!TOI&&!TRAI&&PHAI&&!LUI&&(NUM_PHAI_CHIEU_TRAI_PHAI>200)&&HUONG_GAME_CT<50 ){nho_IMU=IMU-chay_xoay;huong_chay=-900;MAIN_CONTROL(nho_IMU,huong_chay,toc_p,gt,0);BIT_NHO_CHAY=10;nho_IMU=IMU;}
				else if(!TOI&&!TRAI&&PHAI&&!LUI&&(NUM_PHAI_CHIEU_TRAI_PHAI<50)&&HUONG_GAME_CT<50 ){nho_IMU=IMU+chay_xoay;huong_chay=-900;MAIN_CONTROL(nho_IMU,huong_chay,toc_p,gt,0);BIT_NHO_CHAY=10;nho_IMU=IMU;}
				
				else if(!TOI&&!TRAI&&!PHAI&&LUI&&(NUM_PHAI_CHIEU_TRAI_PHAI>200)&&HUONG_GAME_CT<50 ){nho_IMU=IMU-chay_xoay;huong_chay=1800;MAIN_CONTROL(nho_IMU,huong_chay,toc_p,gt,0);BIT_NHO_CHAY=10;nho_IMU=IMU;}
				else if(!TOI&&!TRAI&&!PHAI&&LUI&&(NUM_PHAI_CHIEU_TRAI_PHAI<50)&&HUONG_GAME_CT<50 ){nho_IMU=IMU+chay_xoay;huong_chay=1800;MAIN_CONTROL(nho_IMU,huong_chay,toc_p,gt,0);BIT_NHO_CHAY=10;nho_IMU=IMU;}
				
				else if(TOI&&TRAI&&!PHAI&&!LUI&&(NUM_PHAI_CHIEU_TRAI_PHAI>200)&&HUONG_GAME_CT<50 ){nho_IMU=IMU-chay_xoay;huong_chay=450;MAIN_CONTROL(nho_IMU,huong_chay,toc_p,gt,0);BIT_NHO_CHAY=10;nho_IMU=IMU;}
				else if(TOI&&TRAI&&!PHAI&&!LUI&&(NUM_PHAI_CHIEU_TRAI_PHAI<50)&&HUONG_GAME_CT<50 ){nho_IMU=IMU+chay_xoay;huong_chay=450;MAIN_CONTROL(nho_IMU,huong_chay,toc_p,gt,0);BIT_NHO_CHAY=10;nho_IMU=IMU;}
					
				else if(TOI&&!TRAI&&PHAI&&!LUI&&(NUM_PHAI_CHIEU_TRAI_PHAI>200)&&HUONG_GAME_CT<50 ){nho_IMU=IMU-chay_xoay;huong_chay=-450;MAIN_CONTROL(nho_IMU,huong_chay,toc_p,gt,0);BIT_NHO_CHAY=10;nho_IMU=IMU;}
				else if(TOI&&!TRAI&&PHAI&&!LUI&&(NUM_PHAI_CHIEU_TRAI_PHAI<50)&&HUONG_GAME_CT<50 ){nho_IMU=IMU+chay_xoay;huong_chay=-450;MAIN_CONTROL(nho_IMU,huong_chay,toc_p,gt,0);BIT_NHO_CHAY=10;nho_IMU=IMU;}
				
				else if(!TOI&&TRAI&&!PHAI&&LUI&&(NUM_PHAI_CHIEU_TRAI_PHAI>200)&&HUONG_GAME_CT<50 ){nho_IMU=IMU-chay_xoay;huong_chay=1350;MAIN_CONTROL(nho_IMU,huong_chay,toc_p,gt,0);BIT_NHO_CHAY=10;nho_IMU=IMU;}
				else if(!TOI&&TRAI&&!PHAI&&LUI&&(NUM_PHAI_CHIEU_TRAI_PHAI<50)&&HUONG_GAME_CT<50 ){nho_IMU=IMU+chay_xoay;huong_chay=1350;MAIN_CONTROL(nho_IMU,huong_chay,toc_p,gt,0);BIT_NHO_CHAY=10;nho_IMU=IMU;}
				
				else if(!TOI&&!TRAI&&PHAI&&LUI&&(NUM_PHAI_CHIEU_TRAI_PHAI>200)&&HUONG_GAME_CT<50 ){nho_IMU=IMU-chay_xoay;huong_chay=-1350;MAIN_CONTROL(nho_IMU,huong_chay,toc_p,gt,0);BIT_NHO_CHAY=10;nho_IMU=IMU;}
				else if(!TOI&&!TRAI&&PHAI&&LUI&&(NUM_PHAI_CHIEU_TRAI_PHAI<50)&&HUONG_GAME_CT<50 ){nho_IMU=IMU+chay_xoay;huong_chay=-1350;MAIN_CONTROL(nho_IMU,huong_chay,toc_p,gt,0);BIT_NHO_CHAY=10;nho_IMU=IMU;}
				
					// toi lui trai phai
					
				else if(TOI&&!TRAI&&!PHAI&&!LUI){huong_chay=0;MAIN_CONTROL(nho_IMU,huong_chay,tang_toc_giam_toc,gt,0);BIT_NHO_CHAY=10;}
				else if(!TOI&&!TRAI&&!PHAI&&LUI){huong_chay=1800;MAIN_CONTROL(nho_IMU,huong_chay,tang_toc_giam_toc,gt,0);BIT_NHO_CHAY=10;}
				else if(!TOI&&TRAI&&!PHAI&&!LUI){huong_chay=900;MAIN_CONTROL(nho_IMU,huong_chay,tang_toc_giam_toc,gt,0);BIT_NHO_CHAY=10;}
				else if(!TOI&&!TRAI&&PHAI&&!LUI){huong_chay=-900;MAIN_CONTROL(nho_IMU,huong_chay,tang_toc_giam_toc,gt,0);BIT_NHO_CHAY=10;}
				else if(TOI&&TRAI&&!PHAI&&!LUI){huong_chay=450;MAIN_CONTROL(nho_IMU,huong_chay,tang_toc_giam_toc,gt,0);BIT_NHO_CHAY=10;}
				else if(TOI&&!TRAI&&PHAI&&!LUI){huong_chay=-450;MAIN_CONTROL(nho_IMU,huong_chay,tang_toc_giam_toc,gt,0);BIT_NHO_CHAY=10;}
				else if(!TOI&&TRAI&&!PHAI&&LUI){huong_chay=1350;MAIN_CONTROL(nho_IMU,huong_chay,tang_toc_giam_toc,gt,0);BIT_NHO_CHAY=10;}
				else if(!TOI&&!TRAI&&PHAI&&LUI){huong_chay=-1350;MAIN_CONTROL(nho_IMU,huong_chay,tang_toc_giam_toc,gt,0);BIT_NHO_CHAY=10;}
				
				
            else if(!TOI&&!TRAI&&!PHAI&&!LUI&&(NUM_PHAI_CHIEU_LEN_XUONG<50)){	//NUM_PHAI_CHIEU_LEN_XUONG>200
                                    nho_IMU=IMU;huong_chay=1800;MAIN_CONTROL(nho_IMU,huong_chay,10,1,1);
                                //     GIA_TOC_XOAY(1,1);//DOI MAT NHANH HON DOI HUONG
                                        while(NUM_PHAI_CHIEU_LEN_XUONG<50){vTaskDelay(10);
                                                      if(L2){
                                                         CONTROL_TOC_DO(100,0.05,2);
                                                      }
                                                      else { 
                                                         CONTROL_TOC_DO(20,0.5,20);

                                                      }
                                        }
                                        nho_IMU=IMU;BIT_NHO_CHAY=10;MAIN_CONTROL(nho_IMU,huong_chay,2,1,0);
                        }
				else if(!TOI&&!TRAI&&!PHAI&&!LUI&&(NUM_PHAI_CHIEU_LEN_XUONG>200 )){//NUM_PHAI_CHIEU_LEN_XUONG<50 
                                    nho_IMU=IMU;huong_chay=0;MAIN_CONTROL(nho_IMU,huong_chay,10,1,1);

                                    while(NUM_PHAI_CHIEU_LEN_XUONG>200){vTaskDelay(10);
                                                      if(L2){
                                                         CONTROL_TOC_DO(200,1,2);
                                                      }
                                                      else { 
                                                         CONTROL_TOC_DO(20,0.5,5);

                                                      }
                                    
                                    }
                                    nho_IMU=IMU;BIT_NHO_CHAY=10;MAIN_CONTROL(nho_IMU,huong_chay,2,1,0);
                        }
        ///di?u khien                
             else if(!TOI&&!TRAI&&!PHAI&&!LUI&&HUONG_GAME_CT>10 ){
                                 MAIN_CONTROL(nho_IMU,HUONG_GAME,tang_toc_giam_toc,gt,0);BIT_NHO_CHAY=10;//nho_IMU=IMU;
                               while(NUM_PHAI_CHIEU_TRAI_PHAI<50){vTaskDelay(10);
                                                      if(L2){
                                                         CONTROL_TOC_DO(50,1,2);
                                                      }
                                                      else { 
                                                         CONTROL_TOC_DO(20,0.5,5);

                                                      }
                                    
                                    }  
                               while(NUM_PHAI_CHIEU_TRAI_PHAI>200){vTaskDelay(10);
                                                      if(L2){
                                                         CONTROL_TOC_DO(50,1,-2);
                                                      }
                                                      else { 
                                                         CONTROL_TOC_DO(20,0.5,-5);

                                                      }
                                    
                                    } 
														//	 nho_IMU=IMU;
                              }     
				
				
				/////////////////////  num trai diêu khi?n huong bang num annalog trai
				else if (!TOI&&!TRAI&&!PHAI&&!LUI&&HUONG_GAME_CT>50) {
////
						if (NUM_PHAI_CHIEU_TRAI_PHAI>200) {nho_IMU=IMU-chay_xoay;MAIN_CONTROL(nho_IMU,HUONG_GAME,toc_p,gt,0);BIT_NHO_CHAY=10;nho_IMU=IMU;}
						else if (NUM_PHAI_CHIEU_TRAI_PHAI<50) {nho_IMU=IMU+chay_xoay;MAIN_CONTROL(nho_IMU,HUONG_GAME,toc_p,gt,0);BIT_NHO_CHAY=10;nho_IMU=IMU;}
						else {MAIN_CONTROL(nho_IMU,HUONG_GAME,tang_toc_giam_toc,gt,0); BIT_NHO_CHAY=10;}
						
				} 
				else {nho_IMU=IMU; MAIN_CONTROL(nho_IMU,0,0,gt,0);}
				
				
				//CONTROL_TOC_DO(0,3.5,0);}
	
		}
 else {CONTROL_TOC_DO(0,4,0);}
//				 
}
