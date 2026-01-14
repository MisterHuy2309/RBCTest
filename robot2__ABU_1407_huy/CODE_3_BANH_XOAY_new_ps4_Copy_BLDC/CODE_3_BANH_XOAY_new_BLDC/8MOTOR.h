/// THU VIEN 8 MOTOR
float cao_chan_phai_truoc,cao_chan_trai_truoc,cao_chan_phai_sau,cao_chan_trai_sau,diem_giua_chan_phai_truoc,
	diem_giua_chan_trai_truoc,diem_giua_chan_phai_sau,diem_giua_chan_trai_sau;
vs32 _chan_phai_sau_A,_chan_phai_sau_B,_chan_trai_sau_A,_chan_trai_sau_B,_chan_phai_truoc_A,
	_chan_phai_truoc_B,_chan_trai_truoc_A,_chan_trai_truoc_B;

vs32 bu_trai,bu_phai,lech_imu,imu;

float _diem_giua_chan_trai_sau,_diem_giua_chan_phai_sau,_diem_giua_chan_trai_truoc,_diem_giua_chan_phai_truoc,
	_cao_chan_trai_sau,_cao_chan_trai_truoc,_cao_chan_phai_sau,_cao_chan_phai_truoc,he_so_bu;




void retry_xanh_1(void);


void bu_do_cao(vs32 cao_phai_truoc,vs32 cao_trai_truoc,vs32 cao_phai_sau,vs32 cao_trai_sau,float gia_toc){

_cao_chan_phai_truoc=cao_phai_truoc;
_cao_chan_trai_truoc=cao_trai_truoc;
_cao_chan_phai_sau=cao_phai_sau;
_cao_chan_trai_sau=cao_trai_sau;	
he_so_bu=gia_toc;
}

void thay_doi_diem_giua(vs32 giua_chan_phai_truoc,vs32 giua_chan_trai_truoc,vs32 giua_chan_phai_sau,vs32 giua_chan_trai_sau,float gia_toc){

_diem_giua_chan_phai_truoc=giua_chan_phai_truoc;
_diem_giua_chan_trai_truoc=giua_chan_trai_truoc;
_diem_giua_chan_phai_sau=giua_chan_phai_sau;
_diem_giua_chan_trai_sau=giua_chan_trai_sau;	
he_so_bu=gia_toc;
}

/////////////////////////////////
void TIMER_8_CHAN(void)
{
		if(bit_dieu_khien_PT==0){
	/////////////////////////chan_phai_truoc

				if(GOC_A_HIEN_TAI_PT>GOC_A_PT)GOC_A_HIEN_TAI_PT=GOC_A_HIEN_TAI_PT-GIA_TOC_A_PT;
				else if(GOC_A_HIEN_TAI_PT<GOC_A_PT)GOC_A_HIEN_TAI_PT=GOC_A_HIEN_TAI_PT+GIA_TOC_A_PT;
				else GOC_A_HIEN_TAI_PT=GOC_A_PT;
			
				if(GOC_B_HIEN_TAI_PT>GOC_B_PT)GOC_B_HIEN_TAI_PT=GOC_B_HIEN_TAI_PT-GIA_TOC_B_PT;
				else if(GOC_B_HIEN_TAI_PT<GOC_B_PT)GOC_B_HIEN_TAI_PT=GOC_B_HIEN_TAI_PT+GIA_TOC_B_PT;
				else GOC_B_HIEN_TAI_PT=GOC_B_PT;

		}
		else {
				/////////////////////////chan_phai_truoc
				GOC_A_HIEN_TAI_PT=GOC_A_PT;
				GOC_B_HIEN_TAI_PT=GOC_B_PT;

			}
		
		////////////////////////////////////////////CHAN TRAI TRUOC
			
		if(bit_dieu_khien_TT==0){
	/////////////////////////chan_phai_truoc

				if(GOC_A_HIEN_TAI_TT>GOC_A_TT)GOC_A_HIEN_TAI_TT=GOC_A_HIEN_TAI_TT-GIA_TOC_A_TT;
				else if(GOC_A_HIEN_TAI_TT<GOC_A_TT)GOC_A_HIEN_TAI_TT=GOC_A_HIEN_TAI_TT+GIA_TOC_A_TT;
				else GOC_A_HIEN_TAI_TT=GOC_A_TT;
			
				if(GOC_B_HIEN_TAI_TT>GOC_B_TT)GOC_B_HIEN_TAI_TT=GOC_B_HIEN_TAI_TT-GIA_TOC_B_TT;
				else if(GOC_B_HIEN_TAI_TT<GOC_B_TT)GOC_B_HIEN_TAI_TT=GOC_B_HIEN_TAI_TT+GIA_TOC_B_TT;
				else GOC_B_HIEN_TAI_TT=GOC_B_TT;

		}
		else {
				/////////////////////////chan_phai_truoc
				GOC_A_HIEN_TAI_TT=GOC_A_TT;
				GOC_B_HIEN_TAI_TT=GOC_B_TT;

			}			
			
//////////------------------NUA SAU-------------------------///////////////////////////////////////			
			if(bit_dieu_khien_PS==0){
	/////////////////////////chan_phai_truoc

				if(GOC_A_HIEN_TAI_PS>GOC_A_PS)GOC_A_HIEN_TAI_PS=GOC_A_HIEN_TAI_PS-GIA_TOC_A_PS;
				else if(GOC_A_HIEN_TAI_PS<GOC_A_PS)GOC_A_HIEN_TAI_PS=GOC_A_HIEN_TAI_PS+GIA_TOC_A_PS;
				else GOC_A_HIEN_TAI_PS=GOC_A_PS;
			
				if(GOC_B_HIEN_TAI_PS>GOC_B_PS)GOC_B_HIEN_TAI_PS=GOC_B_HIEN_TAI_PS-GIA_TOC_B_PS;
				else if(GOC_B_HIEN_TAI_PS<GOC_B_PS)GOC_B_HIEN_TAI_PS=GOC_B_HIEN_TAI_PS+GIA_TOC_B_PS;
				else GOC_B_HIEN_TAI_PS=GOC_B_PS;

		}
		else {
				/////////////////////////chan_phai_truoc
				GOC_A_HIEN_TAI_PS=GOC_A_PS;
				GOC_B_HIEN_TAI_PS=GOC_B_PS;

			}
		
		////////////////////////////////////////////CHAN TRAI TRUOC
			
		if(bit_dieu_khien_TS==0){
	/////////////////////////chan_phai_truoc

				if(GOC_A_HIEN_TAI_TS>GOC_A_TS)GOC_A_HIEN_TAI_TS=GOC_A_HIEN_TAI_TS-GIA_TOC_A_TS;
				else if(GOC_A_HIEN_TAI_TS<GOC_A_TS)GOC_A_HIEN_TAI_TS=GOC_A_HIEN_TAI_TS+GIA_TOC_A_TS;
				else GOC_A_HIEN_TAI_TS=GOC_A_TS;
			
				if(GOC_B_HIEN_TAI_TS>GOC_B_TS)GOC_B_HIEN_TAI_TS=GOC_B_HIEN_TAI_TS-GIA_TOC_B_TS;
				else if(GOC_B_HIEN_TAI_TS<GOC_B_TS)GOC_B_HIEN_TAI_TS=GOC_B_HIEN_TAI_TS+GIA_TOC_B_TS;
				else GOC_B_HIEN_TAI_TS=GOC_B_TS;

		}
		else {
				/////////////////////////chan_phai_truoc
				GOC_A_HIEN_TAI_TS=GOC_A_TS;
				GOC_B_HIEN_TAI_TS=GOC_B_TS;

			}				
			
//////////////////xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx//////////////////////			
		if(cao_chan_phai_truoc<_cao_chan_phai_truoc)cao_chan_phai_truoc=cao_chan_phai_truoc+he_so_bu;
		else if(cao_chan_phai_truoc>_cao_chan_phai_truoc)cao_chan_phai_truoc=cao_chan_phai_truoc-he_so_bu;
		else cao_chan_phai_truoc=_cao_chan_phai_truoc;
//			cao_chan_phai_truoc=_cao_chan_phai_truoc;
		if(diem_giua_chan_phai_truoc<_diem_giua_chan_phai_truoc)diem_giua_chan_phai_truoc=diem_giua_chan_phai_truoc+he_so_bu;
		else if(diem_giua_chan_phai_truoc>_diem_giua_chan_phai_truoc)diem_giua_chan_phai_truoc=diem_giua_chan_phai_truoc-he_so_bu;
		else diem_giua_chan_phai_truoc=_diem_giua_chan_phai_truoc;
//diem_giua_chan_phai_truoc=_diem_giua_chan_phai_truoc;				
		////
		if(cao_chan_trai_truoc<_cao_chan_trai_truoc)cao_chan_trai_truoc=cao_chan_trai_truoc+he_so_bu;
		else if(cao_chan_trai_truoc>_cao_chan_trai_truoc)cao_chan_trai_truoc=cao_chan_trai_truoc-he_so_bu;
		else cao_chan_trai_truoc=_cao_chan_trai_truoc;
//			cao_chan_trai_truoc=_cao_chan_trai_truoc;
		if(diem_giua_chan_trai_truoc<_diem_giua_chan_trai_truoc)diem_giua_chan_trai_truoc=diem_giua_chan_trai_truoc+he_so_bu;
		else if(diem_giua_chan_trai_truoc>_diem_giua_chan_trai_truoc)diem_giua_chan_trai_truoc=diem_giua_chan_trai_truoc-he_so_bu;
		else diem_giua_chan_trai_truoc=_diem_giua_chan_trai_truoc;	
	//		diem_giua_chan_trai_truoc=_diem_giua_chan_trai_truoc;	
		////
		if(cao_chan_phai_sau<_cao_chan_phai_sau)cao_chan_phai_sau=cao_chan_phai_sau+he_so_bu;
		else if(cao_chan_phai_sau>_cao_chan_phai_sau)cao_chan_phai_sau=cao_chan_phai_sau-he_so_bu;
		else cao_chan_phai_sau=_cao_chan_phai_sau;
//cao_chan_phai_sau=_cao_chan_phai_sau;
		if(diem_giua_chan_phai_sau<_diem_giua_chan_phai_sau)diem_giua_chan_phai_sau=diem_giua_chan_phai_sau+he_so_bu;
		else if(diem_giua_chan_phai_sau>_diem_giua_chan_phai_sau)diem_giua_chan_phai_sau=diem_giua_chan_phai_sau-he_so_bu;
		else diem_giua_chan_phai_sau=_diem_giua_chan_phai_sau;
//diem_giua_chan_phai_sau=_diem_giua_chan_phai_sau;
		////
		if(cao_chan_trai_sau<_cao_chan_trai_sau)cao_chan_trai_sau=cao_chan_trai_sau+he_so_bu;
		else if(cao_chan_trai_sau>_cao_chan_trai_sau)cao_chan_trai_sau=cao_chan_trai_sau-he_so_bu;
		else cao_chan_trai_sau=_cao_chan_trai_sau;
//cao_chan_trai_sau=_cao_chan_trai_sau;
		if(diem_giua_chan_trai_sau<_diem_giua_chan_trai_sau)diem_giua_chan_trai_sau=diem_giua_chan_trai_sau+he_so_bu;
		else if(diem_giua_chan_trai_sau>_diem_giua_chan_trai_sau)diem_giua_chan_trai_sau=diem_giua_chan_trai_sau-he_so_bu;
		else diem_giua_chan_trai_sau=_diem_giua_chan_trai_sau;	
//diem_giua_chan_trai_sau=_diem_giua_chan_trai_sau;
			
/////////////////////xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx///////////////////////////			
			
			
		///////////gan toc do vao dong co////////////////////////
			
		_chan_phai_truoc_A=abs(GOC_A_HIEN_TAI_PT)+cao_chan_phai_truoc-diem_giua_chan_phai_truoc-10;	
		_chan_phai_truoc_B=abs(GOC_B_HIEN_TAI_PT)+cao_chan_phai_truoc+diem_giua_chan_phai_truoc+5;
			
		_chan_trai_truoc_A=abs(GOC_A_HIEN_TAI_TT)+cao_chan_trai_truoc-diem_giua_chan_trai_truoc-10;	
		_chan_trai_truoc_B=abs(GOC_B_HIEN_TAI_TT)+cao_chan_trai_truoc+diem_giua_chan_trai_truoc;	
			
		_chan_phai_sau_A=abs(GOC_A_HIEN_TAI_PS)+cao_chan_phai_sau-diem_giua_chan_phai_sau;	
		_chan_phai_sau_B=abs(GOC_B_HIEN_TAI_PS)+cao_chan_phai_sau+diem_giua_chan_phai_sau+5;
			
		_chan_trai_sau_A=abs(GOC_A_HIEN_TAI_TS)+cao_chan_trai_sau-diem_giua_chan_trai_sau+10;	
		_chan_trai_sau_B=abs(GOC_B_HIEN_TAI_TS)+cao_chan_trai_sau+diem_giua_chan_trai_sau+10;		
		
		///truoc
		if(_chan_phai_truoc_A>cuc_dai)_chan_phai_truoc_A=chan_phai_truoc_A=cuc_dai;
		else if(_chan_phai_truoc_A<cuc_tieu)_chan_phai_truoc_A=chan_phai_truoc_A=cuc_tieu;
		else 	chan_phai_truoc_A=_chan_phai_truoc_A;
			
    if(_chan_phai_truoc_B>cuc_dai)_chan_phai_truoc_B=chan_phai_truoc_B=cuc_dai;
		else if(_chan_phai_truoc_B<cuc_tieu)_chan_phai_truoc_B=chan_phai_truoc_B=cuc_tieu;
		else 	chan_phai_truoc_B=_chan_phai_truoc_B;
		
		if(_chan_trai_truoc_A>cuc_dai)_chan_trai_truoc_A=chan_trai_truoc_A=cuc_dai;
		else if(_chan_trai_truoc_A<cuc_tieu)_chan_trai_truoc_A=chan_trai_truoc_A=cuc_tieu;
		else 	chan_trai_truoc_A=_chan_trai_truoc_A;
		
		if(_chan_trai_truoc_B>cuc_dai)_chan_trai_truoc_B=chan_trai_truoc_B=cuc_dai;
		else if(_chan_trai_truoc_B<cuc_tieu)_chan_trai_truoc_B=chan_trai_truoc_B=cuc_tieu;
		else 	chan_trai_truoc_B=_chan_trai_truoc_B;
		////////sau
		
		if(_chan_phai_sau_A>cuc_dai)_chan_phai_sau_A=chan_phai_sau_A=cuc_dai;
		else if(_chan_phai_sau_A<cuc_tieu)_chan_phai_sau_A=chan_phai_sau_A=cuc_tieu;
		else 	chan_phai_sau_A=_chan_phai_sau_A;
			
    if(_chan_phai_sau_B>cuc_dai)_chan_phai_sau_B=chan_phai_sau_B=cuc_dai;
		else if(_chan_phai_sau_B<cuc_tieu)_chan_phai_sau_B=chan_phai_sau_B=cuc_tieu;
		else 	chan_phai_sau_B=_chan_phai_sau_B;
		
		if(_chan_trai_sau_A>cuc_dai)_chan_trai_sau_A=chan_trai_sau_A=cuc_dai;
		else if(_chan_trai_sau_A<cuc_tieu)_chan_trai_sau_A=chan_trai_sau_A=cuc_tieu;
		else 	chan_trai_sau_A=_chan_trai_sau_A;
		
		if(_chan_trai_sau_B>cuc_dai)_chan_trai_sau_B=chan_trai_sau_B=cuc_dai;
		else if(_chan_trai_sau_B<cuc_tieu)_chan_trai_sau_B=chan_trai_sau_B=cuc_tieu;
		else 	chan_trai_sau_B=_chan_trai_sau_B;
		
		
}



void chan_phai_truoc(vs32 goc_A,vs32 goc_B,float toc_do_phai_truoc,vs32 cach_dieu_khien){
	
	float TI_SO_LECH_AB;
	vs32 GOC_LECH_A,GOC_LECH_B;
	
							if(cach_dieu_khien==0){	
								GOC_LECH_A = abs(goc_A-GOC_A_HIEN_TAI_PT);
								GOC_LECH_B = abs(goc_B-GOC_B_HIEN_TAI_PT);
							}
							else{
								GOC_LECH_A=GOC_LECH_B=0;
								
							}
								
								
												if(GOC_LECH_A>GOC_LECH_B){
													
													TI_SO_LECH_AB=GOC_LECH_A/GOC_LECH_B;
															if(TI_SO_LECH_AB==0)TI_SO_LECH_AB=1;
													GIA_TOC_A_PT = TI_SO_LECH_AB*toc_do_phai_truoc;
													GIA_TOC_B_PT = toc_do_phai_truoc;
													
													}
												else if(GOC_LECH_A<GOC_LECH_B){
													
													TI_SO_LECH_AB=GOC_LECH_B/GOC_LECH_A;
														if(TI_SO_LECH_AB==0)TI_SO_LECH_AB=1;
													GIA_TOC_A_PT = toc_do_phai_truoc;
													GIA_TOC_B_PT = TI_SO_LECH_AB*toc_do_phai_truoc;
														
													}
												else{
													
															
													GIA_TOC_A_PT = toc_do_phai_truoc;
													GIA_TOC_B_PT = toc_do_phai_truoc;
													
													
													}
												
									GOC_A_PT=goc_A;
									GOC_B_PT=goc_B;				
									bit_dieu_khien_PT=0;				
								

	}
//////////////////////////////////////////////////////////////
void chan_trai_truoc(vs32 goc_A,vs32 goc_B,float toc_do_trai_truoc,vs32 cach_dieu_khien){
	
	float TI_SO_LECH_AB;
	vs32 GOC_LECH_A,GOC_LECH_B;
	
	

							if(cach_dieu_khien==0){	
								GOC_LECH_A = abs(goc_A-GOC_A_HIEN_TAI_TT);
								GOC_LECH_B = abs(goc_B-GOC_B_HIEN_TAI_TT);
							}
							else{
								GOC_LECH_A=GOC_LECH_B=0;
								
							}
										

										
										
														if(GOC_LECH_A>GOC_LECH_B){
															
															TI_SO_LECH_AB=GOC_LECH_A/GOC_LECH_B;
																if(TI_SO_LECH_AB==0)TI_SO_LECH_AB=1;
															GIA_TOC_A_TT = TI_SO_LECH_AB*toc_do_trai_truoc;
															GIA_TOC_B_TT = toc_do_trai_truoc;
															
															}
														else if(GOC_LECH_A<GOC_LECH_B){
															
															TI_SO_LECH_AB=GOC_LECH_B/GOC_LECH_A;
																if(TI_SO_LECH_AB==0)TI_SO_LECH_AB=1;
															GIA_TOC_A_TT = toc_do_trai_truoc;
															GIA_TOC_B_TT = TI_SO_LECH_AB*toc_do_trai_truoc;
																
															}
														else{
															
																	
															GIA_TOC_A_TT = toc_do_trai_truoc;
															GIA_TOC_B_TT = toc_do_trai_truoc;
															
															
															}
														
											GOC_A_TT=goc_A;
											GOC_B_TT=goc_B;				
											bit_dieu_khien_TT=0;				
						

	}
/////////////////////////////--------------------------------------///////////////////////////////	

void chan_phai_sau(vs32 goc_A,vs32 goc_B,float toc_do_phai_sau,vs32 cach_dieu_khien){
	
	float TI_SO_LECH_AB;
	vs32 GOC_LECH_A,GOC_LECH_B;
	
								
								
							if(cach_dieu_khien==0){	
								GOC_LECH_A = abs(goc_A-GOC_A_HIEN_TAI_PS);
								GOC_LECH_B = abs(goc_B-GOC_B_HIEN_TAI_PS);
							}
							else{
								GOC_LECH_A=GOC_LECH_B=0;
								
							}
								
								
												if(GOC_LECH_A>GOC_LECH_B){
													
													TI_SO_LECH_AB=GOC_LECH_A/GOC_LECH_B;
															if(TI_SO_LECH_AB==0)TI_SO_LECH_AB=1;
													GIA_TOC_A_PS = TI_SO_LECH_AB*toc_do_phai_sau;
													GIA_TOC_B_PS = toc_do_phai_sau;
													
													}
												else if(GOC_LECH_A<GOC_LECH_B){
													
													TI_SO_LECH_AB=GOC_LECH_B/GOC_LECH_A;
														if(TI_SO_LECH_AB==0)TI_SO_LECH_AB=1;
													GIA_TOC_A_PS = toc_do_phai_sau;
													GIA_TOC_B_PS = TI_SO_LECH_AB*toc_do_phai_sau;
														
													}
												else{
													
															
													GIA_TOC_A_PS = toc_do_phai_sau;
													GIA_TOC_B_PS = toc_do_phai_sau;
													
													
													}
												
									GOC_A_PS=goc_A;
									GOC_B_PS=goc_B;				
									bit_dieu_khien_PS=0;				
				

	}
//////////////////////////////////////////////////////////////
void chan_trai_sau(vs32 goc_A,vs32 goc_B,float toc_do_trai_sau,vs32 cach_dieu_khien){
	
	float TI_SO_LECH_AB;
	vs32 GOC_LECH_A,GOC_LECH_B;
							
							
							if(cach_dieu_khien==0){	
								GOC_LECH_A = abs(goc_A-GOC_A_HIEN_TAI_TS);
								GOC_LECH_B = abs(goc_B-GOC_B_HIEN_TAI_TS);
							}
							else{
								GOC_LECH_A=GOC_LECH_B=0;
								
							}
							
							
											if(GOC_LECH_A>GOC_LECH_B){
												
												TI_SO_LECH_AB=GOC_LECH_A/GOC_LECH_B;
													if(TI_SO_LECH_AB==0)TI_SO_LECH_AB=1;
												GIA_TOC_A_TS = TI_SO_LECH_AB*toc_do_trai_sau;
												GIA_TOC_B_TS = toc_do_trai_sau;
												
												}
											else if(GOC_LECH_A<GOC_LECH_B){
												
												TI_SO_LECH_AB=GOC_LECH_B/GOC_LECH_A;
													if(TI_SO_LECH_AB==0)TI_SO_LECH_AB=1;
												GIA_TOC_A_TS = toc_do_trai_sau;
												GIA_TOC_B_TS = TI_SO_LECH_AB*toc_do_trai_sau;
													
												}
											else{
												
														
												GIA_TOC_A_TS = toc_do_trai_sau;
												GIA_TOC_B_TS = toc_do_trai_sau;
												
												
												}
											
								GOC_A_TS=goc_A;
								GOC_B_TS=goc_B;				
								bit_dieu_khien_TS=0;				
					

	}
////////////////////////////

void ham_xoay(vs32 so_buoc,vs32 bien_do,vs32 diem_giua,vs32 toc_do,vs32 di_toi_lui){

		diem_tren=diem_giua+bien_do;
		diem_duoi=diem_giua-bien_do;
						for(buoc=0;buoc<so_buoc;buoc++){
										chan_phai_sau(diem_tren,diem_tren,1,1);
										chan_trai_truoc(diem_tren,diem_tren,1,1);
										chan_phai_truoc(diem_duoi-di_toi_lui,diem_duoi+di_toi_lui,1,1);
										chan_trai_sau(diem_duoi+di_toi_lui,diem_duoi-di_toi_lui,1,1);
									
										vTaskDelay(toc_do);
				
										chan_phai_truoc(diem_tren,diem_tren,1,1);
										chan_trai_sau(diem_tren,diem_tren,1,1);		
										chan_phai_sau(diem_duoi-di_toi_lui,diem_duoi+di_toi_lui,1,1);
										chan_trai_truoc(diem_duoi+di_toi_lui,diem_duoi-di_toi_lui,1,1);
							
										vTaskDelay(toc_do);
							
										chan_phai_truoc(diem_giua,diem_giua,1,1);
										chan_trai_sau(diem_giua,diem_giua,1,1);
							
										chan_phai_sau(diem_giua,diem_giua,1,1);
										chan_trai_truoc(diem_giua,diem_giua,1,1);
										bu_do_cao(0,0,0,0,1);
	}
	
}
////////////********************************************?????????????
//	
void ham_chay_nhanh(vs32 so_buoc,vs32 bien_do,vs32 diem_giua,vs32 toc_do,float gia_toc,vs32 di_toi_lui,vs32 _imu){
	vs32 he_so_day_chan_tt,he_so_day_chan_pt,he_so_day_chan_ps,he_so_day_chan_ts,k;
	vs32 can_phai=-5,can_trai=0;	
		imu=_imu;
		diem_tren=diem_giua+bien_do;
		diem_duoi=diem_giua-bien_do;
												
									if(buoc_le==0){
																									chan_phai_truoc(diem_duoi,diem_duoi,gia_toc*2,1);
																									chan_trai_sau(diem_duoi,diem_duoi,gia_toc*2,1);
																						
																									chan_phai_sau(diem_tren,diem_tren,gia_toc*2,1);
																									chan_trai_truoc(diem_tren,diem_tren,gia_toc*2,1);
																		
																									vTaskDelay(toc_do/2);
									}
									else if (buoc_chan==0){
																											
																									chan_phai_truoc(diem_tren,diem_tren,gia_toc*2,1);
																									chan_trai_sau(diem_tren,diem_tren,gia_toc*2,1);
																						
																									chan_phai_sau(diem_duoi,diem_duoi,gia_toc*2,1);
																									chan_trai_truoc(diem_duoi,diem_duoi,gia_toc*2,1);
																		
																									vTaskDelay(toc_do/2);
									}
									
		
	for(buoc=0;buoc<so_buoc;buoc++){
		
	bu_do_cao(bu_trai/4+can_trai,bu_phai/4+can_phai,0+can_trai,0+can_phai,1);
		

		
		
		
		
		
										if(buoc_le==0){buoc_le=1;buoc_chan=0;
																	
																		chan_phai_truoc(diem_tren,diem_tren,gia_toc*2,1);
																		chan_trai_sau(diem_tren,diem_tren,gia_toc*2,1);
															
																		chan_phai_sau(diem_duoi,diem_duoi,gia_toc*2,1);
																		chan_trai_truoc(diem_duoi,diem_duoi,gia_toc*2,1);
											
																		vTaskDelay(toc_do/2);
											
																		chan_phai_truoc(diem_tren,diem_tren,gia_toc,1);
																		chan_trai_sau(diem_tren,diem_tren,gia_toc,1);
															
																		chan_phai_sau(diem_duoi-di_toi_lui+bu_trai-bu_phai,diem_duoi+(di_toi_lui/7),gia_toc,1);
																		chan_trai_truoc(diem_duoi-di_toi_lui-bu_trai+bu_phai,diem_duoi+(di_toi_lui/7),gia_toc,1);

																		
																		vTaskDelay(toc_do);


																}
										else {buoc_le=0;buoc_chan=1;

																
																		chan_phai_sau(diem_tren,diem_tren,gia_toc*2,1);
																		chan_trai_truoc(diem_tren,diem_tren,gia_toc*2,1);

																		chan_phai_truoc(diem_giua,diem_duoi,gia_toc*2,1);
																		chan_trai_sau(diem_duoi,diem_duoi,gia_toc*2,1);
																		vTaskDelay(toc_do/2);		
											
																
																		chan_phai_sau(diem_tren,diem_tren,gia_toc,1);
																		chan_trai_truoc(diem_tren,diem_tren,gia_toc,1);

																		chan_phai_truoc(diem_duoi-di_toi_lui-bu_phai+bu_trai,diem_duoi+(di_toi_lui/7),gia_toc,1);
																		chan_trai_sau(diem_duoi-di_toi_lui+bu_phai-bu_trai,diem_duoi+(di_toi_lui/7),gia_toc,1);
																		vTaskDelay(toc_do);		
																				

															

															}


							
				}
																		bu_do_cao(0,0,0,0,1);
																		chan_phai_truoc(diem_giua,diem_giua,gia_toc*2,1);
																		chan_trai_sau(diem_giua,diem_giua,gia_toc*2,1);
															
																		chan_phai_sau(diem_giua,diem_giua,gia_toc*2,1);
																		chan_trai_truoc(diem_giua,diem_giua,gia_toc*2,1);	
	
}
///////////////////////////////
	
void ham_di_len_doc(vs32 so_buoc,vs32 bien_do,vs32 diem_giua,vs32 toc_do,float gia_toc,vs32 di_toi_lui,vs32 _imu){
	vs32 he_so_day_chan_tt,he_so_day_chan_pt,he_so_day_chan_ps,he_so_day_chan_ts;
		
		imu=_imu;
		diem_tren=diem_giua+bien_do;
		diem_duoi=diem_giua-bien_do;

	
	for(buoc=0;buoc<so_buoc;buoc++){
		
							if(imu==30000){	

								bu_trai=1;
								bu_phai=1;
								}


								
		if(buoc_le==0){buoc_le=1;buoc_chan=0;
			
			
										chan_phai_sau(diem_tren,diem_tren,gia_toc,1);
										chan_trai_truoc(diem_tren,diem_tren,gia_toc,1);

										chan_phai_truoc(diem_duoi-bu_phai-di_toi_lui+bu_trai,diem_tren,gia_toc,0);
										chan_trai_sau(diem_duoi-di_toi_lui,diem_tren,gia_toc,0);
										vTaskDelay(toc_do);


								}
		else {buoc_le=0;buoc_chan=1;


										chan_phai_truoc(diem_tren,diem_tren,gia_toc,1);
										chan_trai_sau(diem_tren,diem_tren,gia_toc,1);
										
										chan_phai_sau(diem_duoi-di_toi_lui,diem_tren,gia_toc,0);
										chan_trai_truoc(diem_duoi-bu_trai-di_toi_lui+bu_phai,diem_tren,gia_toc,0);
										vTaskDelay(toc_do);

							}
//						
	GOC_A_PT=GOC_B_PT=GOC_A_PS=GOC_B_PS=diem_giua;
	GOC_A_TT=GOC_B_TT=GOC_A_TS=GOC_B_TS=diem_giua;
vTaskDelay(5);
							
				}
	
	
}

//////////////////////////////////////////
	
void ham_di_test(vs32 so_buoc,vs32 bien_do,vs32 diem_giua,vs32 toc_do,float gia_toc,vs32 di_toi_lui,vs32 _imu){
		vs32 he_so_day_chan_tt,he_so_day_chan_pt,he_so_day_chan_ps,he_so_day_chan_ts;
			vs32 can_phai=10,can_trai=0;	
		imu=_imu;
		diem_tren=diem_giua+bien_do;
		diem_duoi=diem_giua-bien_do;

	
	for(buoc=0;buoc<so_buoc;buoc++){
				
		if(buoc_le==0){buoc_le=1;buoc_chan=0;
			


		
	bu_do_cao(bu_trai/4+can_trai,bu_phai/4+can_phai,0+can_trai,0+can_phai,1);
										
										chan_phai_sau(diem_tren,diem_tren,gia_toc,1);
										chan_trai_truoc(diem_tren,diem_tren,gia_toc,1);

										chan_phai_truoc(diem_duoi-bu_phai*2-di_toi_lui+bu_trai*2,diem_duoi,gia_toc,1);
										chan_trai_sau(diem_duoi-di_toi_lui,diem_duoi,gia_toc,1);
			
			
										vTaskDelay(toc_do);


								}
		else {buoc_le=0;buoc_chan=1;


								
			
										chan_phai_truoc(diem_tren,diem_tren,gia_toc,1);
										chan_trai_sau(diem_tren,diem_tren,gia_toc,1);
										
										chan_phai_sau(diem_duoi-di_toi_lui,diem_duoi,gia_toc,1);
										chan_trai_truoc(diem_duoi-bu_trai*2-di_toi_lui+bu_phai*2,diem_duoi,gia_toc,1);
										vTaskDelay(toc_do);

							}
//						
	GOC_A_PT=GOC_B_PT=GOC_A_PS=GOC_B_PS=diem_giua;
	GOC_A_TT=GOC_B_TT=GOC_A_TS=GOC_B_TS=diem_giua;
vTaskDelay(toc_do/5);
							
				}
	
	
}
	
	
//////////////////////////////////////////////////////////////////	
void ham_dung(vs32 diem_giua,float gia_toc){

										chan_phai_truoc(diem_giua,diem_giua,gia_toc,0);
										chan_trai_sau(diem_giua,diem_giua,gia_toc,0);
									
										chan_phai_sau(diem_giua,diem_giua,gia_toc,0);
										chan_trai_truoc(diem_giua,diem_giua,gia_toc,0);
	
	}
//////////////////////////////////////////////////////////////		

	
void qua_buc(vs32 _delay)	
{
	int so_buoc;	
	
	vTaskDelay(_delay);
					thay_doi_diem_giua(0,0,0,0,0.5);
					bu_do_cao(-30,-30,0,0,0.5);		
vTaskDelay(_delay*2);
	
					thay_doi_diem_giua(0,0,0,0,1);
					bu_do_cao(-30,50,0,0,1);		
	
vTaskDelay(_delay);
					thay_doi_diem_giua(0,-50,0,0,1);
					bu_do_cao(-30,0,0,0,1);		
		
vTaskDelay(_delay);
	
					thay_doi_diem_giua(0,-50,0,0,1);
					bu_do_cao(-30,-30,0,0,1);
vTaskDelay(_delay);
	
	
	
					thay_doi_diem_giua(0,-50,0,0,1);
					bu_do_cao(50,-30,0,0,1);	
	vTaskDelay(_delay);
						thay_doi_diem_giua(-50,-50,0,0,1);
					bu_do_cao(0,-30,0,0,1);	
	vTaskDelay(_delay);
					thay_doi_diem_giua(-50,-50,0,0,1);
					bu_do_cao(-30,-30,0,0,1);	
	vTaskDelay(_delay);
	
					thay_doi_diem_giua(-30,-30,30,30,1);
					bu_do_cao(20,20,0,0,1);	
	vTaskDelay(2000);
									
									ham_di_len_doc(8,5,140,500,0.5,50,tham_so_imu);
		vTaskDelay(1000);				
		thay_doi_diem_giua(0,0,20,20,1);
		bu_do_cao(20,20,-40,-40,1);	
/////////////////////////////////////////chan sau
								
			vTaskDelay(_delay);						
		thay_doi_diem_giua(0,0,100,20,1);
		bu_do_cao(20,20,70,-40,1);							
			vTaskDelay(_delay);

		thay_doi_diem_giua(0,0,0,20,1);
		bu_do_cao(20,20,70,-40,1);							
			vTaskDelay(_delay);
								
		thay_doi_diem_giua(0,0,0,20,1);
		bu_do_cao(20,20,20,-40,1);							
		vTaskDelay(_delay);		
				//////////	
				
	//	while(1){};
								
		thay_doi_diem_giua(10,10,0,100,1);
		bu_do_cao(20,20,20,80,1);							
		vTaskDelay(_delay);	

			thay_doi_diem_giua(10,10,-10,-10,1);
		bu_do_cao(20,20,20,60,1);							
		vTaskDelay(_delay);	
	
		///////////////
				
		thay_doi_diem_giua(10,10,-10,-10,1);
		bu_do_cao(20,20,60,60,1);							
		vTaskDelay(_delay*2);	
		

									ham_di_len_doc(2,10,140,800,0.5,40,tham_so_imu);
									thay_doi_diem_giua(0,0,0,0,1);
									bu_do_cao(20,20,40,40,1);
									ham_di_len_doc(3,10,140,800,0.5,40,tham_so_imu);
									
							
	vTaskDelay(_delay);	
	bu_do_cao(0,0,0,0,0.5);		
	thay_doi_diem_giua(0,0,0,0,0.5)	;
		

		
}		
	/////////////////////////////////////lap trinh lam nhiem vu////////////////////////////////////////	




void nhay_qua_buc(vs32 so_lan_nhay,vs32 timer_nhay)
	{
	int nhay=0,k;
	float gt=2;
		for(nhay=0;nhay<so_lan_nhay;nhay++){
			///xoay tam 
					thay_doi_diem_giua(50,50,60,60,0.5);
					bu_do_cao(50,50,50,50,0.5);
					vTaskDelay(1000);
			///bung len 
					thay_doi_diem_giua(50,50,70,70,gt);
					bu_do_cao(-250,-250,-200,-200,gt);
					vTaskDelay(1000);
			////thu chan tren khong
				thay_doi_diem_giua(70,70,70,70,gt);
				bu_do_cao(50,50,50,50,gt);
					vTaskDelay(1000);
			//xoay tam
				thay_doi_diem_giua(-100,-100,0,0,gt);
				bu_do_cao(0,0,-50,-50,gt);
				//vTaskDelay(1000);
			//dua chan ra de tiep dat
				k=0;
			while(1){	
				k++;
				if(k>1500)break;
				if(k>500){
						if(CB_DAM_CHAN==0)break;		
				}
				vTaskDelay(1);
			}
//				thay_doi_diem_giua(-100,-100,0,0,gt);
//				bu_do_cao(0,0,-60,-60,gt);
//				vTaskDelay(1000);
			//xoay tam luc tiep dat
//				thay_doi_diem_giua(-20,-20,0,0,gt);
//				bu_do_cao(0,0,0,0,gt);
				//vTaskDelay(1000);
			// ve trang thai ban dau
						thay_doi_diem_giua(0,0,0,0,gt);
				bu_do_cao(0,0,-30,-30,gt);
				vTaskDelay(1000);
		//////////////////////////////////////////////////////////
					thay_doi_diem_giua(50,50,60,60,1);
					bu_do_cao(50,50,50,50,1);
					vTaskDelay(1000);
			///bung len 
					thay_doi_diem_giua(50,50,70,70,gt);
					bu_do_cao(-250,-250,-200,-200,gt);
					vTaskDelay(1000);
			////thu chan tren khong
				thay_doi_diem_giua(70,70,70,70,gt);
				bu_do_cao(150,150,150,150,gt);
					vTaskDelay(1000);
			//xoay tam
				thay_doi_diem_giua(-50,-50,-50,-50,gt);
				bu_do_cao(0,0,0,0,gt);
				vTaskDelay(1000);
			//dua chan ra de tiep dat
				thay_doi_diem_giua(-30,-30,-50,-50,gt);
				bu_do_cao(0,0,-60,-60,gt);
				//vTaskDelay(2000);
			k=0;
			while(1){	
				k++;
				if(k>1500)break;
				if(k>500){
						if(CB_DAM_CHAN==0)break;		
				}
				vTaskDelay(1);
			}
			//xoay tam luc tiep dat
				thay_doi_diem_giua(0,0,0,0,gt);
				bu_do_cao(0,0,0,0,gt);
				vTaskDelay(1000);
			// ve trang thai ban dau
						thay_doi_diem_giua(0,0,0,0,gt);
				bu_do_cao(0,0,0,0,gt);
				vTaskDelay(1000);		


		
		}
		
		

	}
//////////////////////////////////////////////////	
void nhay_qua_day(vs32 so_lan_nhay,vs32 timer_nhay)
	{
	int nhay=0,k;
	float gt=2;
		for(nhay=0;nhay<so_lan_nhay;nhay++){
			///xoay tam 
					thay_doi_diem_giua(60,60,60,60,0.5);
					bu_do_cao(50,50,50,50,0.5);
					vTaskDelay(1000);
			///bung len 
					thay_doi_diem_giua(60,60,60,60,gt);
					bu_do_cao(-250,-250,-100,-100,gt);
					vTaskDelay(1300);
			////thu chan tren khong
				thay_doi_diem_giua(50,50,30,30,gt);
				bu_do_cao(150,150,150,150,gt);
					vTaskDelay(1000);
			//xoay tam
				thay_doi_diem_giua(-70,-70,-50,-50,gt);
				bu_do_cao(50,50,50,50,gt);
				vTaskDelay(1000);
			//dua chan ra de tiep dat
				thay_doi_diem_giua(-70,-70,-50,-50,gt);
				bu_do_cao(0,0,-40,-40,gt);
				//vTaskDelay(1000);
				k=0;
			while(1){	
				k++;
				if(k>2000)break;
				if(k>500){
						if(CB_DAM_CHAN==0)break;		
				}
				vTaskDelay(1);
			}
			
			
			//xoay tam luc tiep dat
				thay_doi_diem_giua(-20,-20,20,20,gt);
				bu_do_cao(0,0,0,0,gt);
				vTaskDelay(1000);
			// ve trang thai ban dau
						thay_doi_diem_giua(-10,-10,20,20,1);
				bu_do_cao(0,0,0,0,gt);
				vTaskDelay(1000);
						thay_doi_diem_giua(0,0,0,0,gt);
				bu_do_cao(0,0,0,0,gt);
				vTaskDelay(1000);

		
		}
		
		
		
}	
///////////////////////////
void nhay_qua_day_ngan(vs32 so_lan_nhay,vs32 timer_nhay)
	{	int nhay=0;
	float gt=2;
		for(nhay=0;nhay<so_lan_nhay;nhay++){
			///xoay tam 
					thay_doi_diem_giua(50,50,70,70,0.1);
					bu_do_cao(50,50,50,50,0.1);
					vTaskDelay(3000);
			///bung len 
					thay_doi_diem_giua(50,50,70,70,gt);
					bu_do_cao(-250,-250,-200,-200,gt);
					vTaskDelay(1100);
			////thu chan tren khong
				thay_doi_diem_giua(70,70,70,70,gt);
				bu_do_cao(150,150,150,150,gt);
					vTaskDelay(1000);
			//xoay tam
				thay_doi_diem_giua(-100,-100,-100,-100,gt);
				bu_do_cao(50,50,50,50,gt);
				vTaskDelay(1000);
			//dua chan ra de tiep dat
				thay_doi_diem_giua(-100,-100,-30,-30,gt);
				bu_do_cao(0,0,-40,-40,gt);
				vTaskDelay(1000);
			//xoay tam luc tiep dat
				thay_doi_diem_giua(0,0,0,0,gt);
				bu_do_cao(0,0,0,0,gt);
				vTaskDelay(1000);
			// ve trang thai ban dau
						thay_doi_diem_giua(0,0,0,0,0.05);
				bu_do_cao(0,0,0,0,gt);
				vTaskDelay(1000);
						thay_doi_diem_giua(0,0,0,0,gt);
				bu_do_cao(0,0,0,0,gt);
				vTaskDelay(1000);	
				}
}	
	
///////////////////////////////////////////////////////////////	
void qua_day(vs32 _delay)	
{

	
bu_do_cao(-50,-50,0,0,0.1);		
thay_doi_diem_giua(0,0,0,0,0.5)	;
vTaskDelay(_delay*2);	
	
	bu_do_cao(0,-50,0,0,0.5);		
			chan_phai_truoc(100,240,0.1,0);
	
	vTaskDelay(_delay);	
				chan_phai_truoc(240,240,1,0);

	vTaskDelay(_delay*1.5);	
				chan_phai_truoc(240,100,1,0);
	
	vTaskDelay(_delay);	
				  chan_phai_truoc(100,100,1,0);

//////////////////////////////////////
	vTaskDelay(_delay*2);	
	bu_do_cao(0,0,0,0,0.5);		
			//chan_phai_truoc(150,240,0.1,0);

				chan_trai_truoc(100,240,1,0);
	
	vTaskDelay(_delay);	
				//chan_phai_truoc(240,240,0.1,0);

				chan_trai_truoc(240,240,1,0);
	vTaskDelay(_delay*1.5);	
				//chan_phai_truoc(240,100,0.1,0);

				chan_trai_truoc(240,100,1,0);		
	vTaskDelay(_delay);	
				//chan_phai_truoc(100,100,0.1,0);

		    chan_trai_truoc(100,100,1,0);	
///////////////////////////////////////////////////////
		vTaskDelay(_delay*2);	
	bu_do_cao(0,0,0,0,0.5);		
	thay_doi_diem_giua(0,0,0,0,0.5)	;
	vTaskDelay(_delay*2);	
	
	ham_di_len_doc(7,10,140,700,0.5,30,tham_so_imu);
	ham_di_len_doc(1,10,140,500,0.5,0,tham_so_imu);
/////////////////////////////////////////////////////*****************/////////////////////////////////////////////////
vTaskDelay(_delay);	
bu_do_cao(0,0,-50,-50,0.1);		
thay_doi_diem_giua(0,0,0,0,0.1)	;
vTaskDelay(_delay*2);	
	
	bu_do_cao(0,0,0,-50,0.5);		
			chan_phai_sau(100,240,1,0);
	vTaskDelay(_delay);	
				chan_phai_sau(240,240,1,0);
	vTaskDelay(_delay);	
				chan_phai_sau(240,100,1,0);
	vTaskDelay(_delay);	
				  chan_phai_sau(100,100,1,0);
//////////////////////////////////////
	vTaskDelay(_delay*2);	
	bu_do_cao(0,0,0,0,0.5);		
				chan_trai_sau(100,240,1,0);
	vTaskDelay(_delay);	
				chan_trai_sau(240,240,1,0);
	vTaskDelay(_delay);	
				chan_trai_sau(240,100,1,0);		
	vTaskDelay(_delay);	
		    chan_trai_sau(100,100,1,0);	
///////////////////////////////////////////////////////
		vTaskDelay(_delay*2);	
	bu_do_cao(0,0,0,0,1);		
	thay_doi_diem_giua(0,0,0,0,1)	;
	vTaskDelay(_delay*2);	
	ham_di_len_doc(7,10,140,700,0.5,30,tham_so_imu);
	ham_di_len_doc(1,10,140,500,0.5,0,tham_so_imu);
	vTaskDelay(_delay);	
		
	
}
///////////////////
void len_doc_do(){
	
	int so_buoc;
	
//																thay_doi_diem_giua(10,10,10,10,1);
//																bu_do_cao(20,20,0,0,1);
//																ham_dung(150,0.1);
//																while(CB_DUOI==0){	vTaskDelay(1);}
////																
//																run_read_gyro_uart1();	
//																ham_di_len_doc(4,25,150,1000,1,40,0);
//																ham_di_len_doc(8,20,150,1000,1,40,0);
//																ham_di_len_doc(4,20,150,500,0.5,20,0);
//																so_buoc=0;
//																BIT_CB_CHAN_PHAI_XA=1;
//																			while((CB_CHAN_PHAI==1)&&(so_buoc<20)){
//																					so_buoc++;
//																					ham_di_len_doc(1,20,150,500,0.5,20,0);	
//																					vTaskDelay(1);
//																					if(BIT_CB_CHAN_PHAI_XA==0)break;
//																			}
//																			
//																			
////																								while(NUT_LEN_DOC==1){	vTaskDelay(1);}
//							XL_DO_THE_ON;									
//							thay_doi_diem_giua(0,0,0,0,0.5);
//							bu_do_cao(-50,-50,0,0,1);
//							vTaskDelay(500);
//							thay_doi_diem_giua(0,0,0,0,0.5);
//							bu_do_cao(-50,-50,-20,-20,1);
//							vTaskDelay(500);	
//							while(1){};
				
	}
void len_doc_xanh(){
int so_buoc;
																XL_DO_THE_OFF;	
																thay_doi_diem_giua(10,10,30,30,1);
																bu_do_cao(0,0,-30,-30,1);
																ham_dung(180,0.1);
																vTaskDelay(1000);
																while(CB_DUOI==1){	vTaskDelay(1);}
																run_read_gyro_uart1();	
														
																ham_di_test(5,10,180,900,2,80,0);	
																
																	thay_doi_diem_giua(20,20,30,30,1);
																	bu_do_cao(0,0,-30,-30,1);
																
																ham_di_test(10,10,180,800,2,120,0);
																
																thay_doi_diem_giua(10,10,20,20,1);
																bu_do_cao(0,0,-30,-30,1);
																bit_bat_laze=0;
																while(LAZE>25){
																if( bit_bat_laze==1)break;
																			ham_di_test(1,15,180,500,2,60,0);
																			//	ham_chay_nhanh(1,20,180,600,1,50,0);			
																			vTaskDelay(1);		
																	}		
																	thay_doi_diem_giua(10,10,10,10,1);
																	bu_do_cao(0,0,-20,-20,1);
																	bit_bat_laze=0;
																		while(LAZE>15){
																			if( bit_bat_laze==1)break;
																	//ham_chay_nhanh(1,20,180,600,1,50,0);			
																			ham_di_test(1,10,180,500,2,50,0);
																			
																			vTaskDelay(1);		
																	}		
																			
								//		while(1);									
//																								while(NUT_LEN_DOC==1){	vTaskDelay(1);}
							XL_DO_THE_ON;			
												thay_doi_diem_giua(0,0,-20,-20,0.1);
												bu_do_cao(-10,-10,0,0,0.1);
												ham_dung(180,0.1);																	
							//vTaskDelay(1000);		
																
//							thay_doi_diem_giua(0,0,0,0,0.5);
//							bu_do_cao(-50,-50,0,0,1);
//							vTaskDelay(500);
//							thay_doi_diem_giua(0,0,0,0,0.5);
//							bu_do_cao(-50,-50,-20,-20,1);
//							vTaskDelay(500);																				
								vTaskDelay(50000);											
							//while(1){};
				
	}

	
	void test_nhay_day(){
	int k;
					nhay_qua_day(1,0);
				k=0;
				while(IMU>80){
						k++;
						if(k>5)break;
						//ham_chay_nhanh(1,10,180,500,1,20,-150);
						ham_xoay(1,20,180,500,-30);
				}
				
				k=0;
				while(IMU<-80){
						k++;
						if(k>5)break;
					//ham_chay_nhanh(1,10,180,500,1,20,150);
						ham_xoay(1,20,180,300,30);
					
				}
				nhay_qua_day(1,0);
				
				k=0;
				while(IMU>80){
						k++;
						if(k>5)break;
						//ham_chay_nhanh(1,10,180,500,1,20,-150);
								ham_xoay(1,20,180,300,-30);
				}
				k=0;
				while(IMU<-80){
					k++;
					if(k>5)break;
					//ham_chay_nhanh(1,10,180,500,1,20,150);
						ham_xoay(1,20,180,300,30);
				}
				nhay_qua_day(1,0);
	
	
	
	}
	
	void test_nhay_day_2(){
	int k;
					nhay_qua_day(1,0);

				

				BIT_CB_CHAN=0;
				k=0;
//				while(1){
//					k++;
//					if(k>6)break;
//					if(BIT_CB_CHAN==1)break;
//					ham_chay_nhanh(1,10,180,500,1,80,0);
//					
//				}
				ham_chay_nhanh(5,10,180,500,1,80,0);		
				nhay_qua_day(1,0);
				

	
	
	
	}	
		
///////////////////////////////////////************************>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	
void xuat_phat_xanh(void)	{
	int k;
			ham_chay_nhanh(2,10,180,700,1,50,-50);	
			ham_chay_nhanh(13,10,180,700,1,150,-100);	
				k=0;
			while(LAZE>15){
						k++;
						if(k>10)break;
							ham_chay_nhanh(1,10,180,350,1,100,-100);	
							
						vTaskDelay(1);
			}		
						k=0;
				while(CB_CHAN_PHAI==1){
						k++;
						if(k>10)break;
						ham_chay_nhanh(1,10,180,350,1,50,0);	
				}	
				k=0;
				while(CB_CHAN_TRAI==1){
						k++;
						if(k>10)break;
						ham_chay_nhanh(1,10,180,350,1,50,-300);	
				}	

					ham_chay_nhanh(4,10,180,500,1,10,-350);	
				
				
				 vTaskDelay(1000);
	////////////////////////////////////nhay////////////////////////////////////////////////////////////////////	
				nhay_qua_buc(1,0);
	///////////////////////////////////////////////////////////////////////////////			
				
				
				ham_chay_nhanh(5,10,180,400,1,0,-600);
					
				ham_chay_nhanh(4,10,180,600,1,100,-500);
			
				ham_chay_nhanh(4,10,180,600,1,100,-250);
				ham_chay_nhanh(3,10,180,500,1,60,-100);
	
				k=0;		
				while(IMU<-100){
						k++;
						if(k>10)break;
					ham_chay_nhanh(1,15,180,500,1,10,100);
					vTaskDelay(1);
					
					}
				k=0;
				while(IMU>0){
				k++;
				if(k>10)break;
					ham_chay_nhanh(1,15,180,500,1,10,-100);
					vTaskDelay(1);
					
				}
				BIT_CB_CHAN=0;
				k=0;
				while(1){
					k++;
					if(k>4)break;
					if(BIT_CB_CHAN==1)break;
					ham_chay_nhanh(1,10,180,500,1,50,0);
					
				}
					ham_chay_nhanh(2,10,180,400,1,50,0);
				
				test_nhay_day();
				
				ham_chay_nhanh(2,10,180,800,1,100,0);

				while(IMU<750){
			
						ham_xoay(1,20,180,500,30);
					vTaskDelay(1);
					
				}
				
		////////////////////////////////////////
				
		len_doc_xanh();
				
				
	

	}

/////////////////////////////////////////////////////////...............................	
	
void xuat_phat_do(void)	{
	int k;
			ham_chay_nhanh(3,10,180,700,1,50,50);	
			ham_chay_nhanh(13,10,180,700,1,150,150);	
				k=0;
			while(LAZE>15){
						k++;
						if(k>10)break;
							ham_chay_nhanh(1,10,180,350,1,100,100);	
							
						vTaskDelay(1);
			}		
						k=0;
				while(CB_CHAN_TRAI==1){
						k++;
						if(k>10)break;
						ham_chay_nhanh(1,10,180,350,1,50,0);	
				}	
				k=0;
				while(CB_CHAN_PHAI==1){
						k++;
						if(k>10)break;
						ham_chay_nhanh(1,10,180,350,1,50,300);	
				}	

					ham_chay_nhanh(4,10,180,500,1,10,350);	
				
				
				 vTaskDelay(1000);
	////////////////////////////////////nhay////////////////////////////////////////////////////////////////////	
				nhay_qua_buc(1,0);
	///////////////////////////////////////////////////////////////////////////////			
				
				
				ham_chay_nhanh(5,10,180,400,1,0,600);
					
				ham_chay_nhanh(5,10,180,600,1,100,500);
			
				ham_chay_nhanh(4,10,180,600,1,100,250);
				ham_chay_nhanh(3,10,180,500,1,60,100);
	
				k=0;		
				while(IMU>100){
						k++;
						if(k>10)break;
					ham_chay_nhanh(1,15,180,500,1,10,-100);
					vTaskDelay(1);
					
					}
				k=0;
				while(IMU<0){
				k++;
				if(k>10)break;
					ham_chay_nhanh(1,15,180,500,1,10,100);
					vTaskDelay(1);
					
				}
				BIT_CB_CHAN=0;
				k=0;
				while(1){
					k++;
					if(k>4)break;
					if(BIT_CB_CHAN==1)break;
					ham_chay_nhanh(1,10,180,500,1,50,0);
					
				}
					ham_chay_nhanh(2,10,180,400,1,50,0);
				
				test_nhay_day();
				
				ham_chay_nhanh(2,10,180,800,1,100,0);

				while(IMU>-750){
			
						ham_xoay(1,20,180,500,-30);
					vTaskDelay(1);
					
				}
				
		////////////////////////////////////////
				
		len_doc_xanh();
				
	

	}

////////////////////////////////////////////////////////////////////////
void retry_do_1(void){
		int k;

				ham_chay_nhanh(5,10,180,500,1,50,100);
					k=0;
			while(LAZE>15){
						k++;
						if(k>10)break;
							ham_chay_nhanh(1,10,180,350,1,100,100);	
							
						vTaskDelay(1);
			}		
						k=0;
				while(CB_CHAN_TRAI==1){
						k++;
						if(k>10)break;
						ham_chay_nhanh(1,10,180,350,1,50,0);	
				}	
				k=0;
				while(CB_CHAN_PHAI==1){
						k++;
						if(k>10)break;
						ham_chay_nhanh(1,10,180,350,1,50,300);	
				}	

					ham_chay_nhanh(4,10,180,500,1,10,350);	
				
				
				 vTaskDelay(1000);
	////////////////////////////////////nhay////////////////////////////////////////////////////////////////////	
				nhay_qua_buc(1,0);
	///////////////////////////////////////////////////////////////////////////////			
				
				
				ham_chay_nhanh(5,10,180,400,1,0,600);
					
				ham_chay_nhanh(4,10,180,600,1,100,500);
			
				ham_chay_nhanh(4,10,180,600,1,100,250);
				ham_chay_nhanh(3,10,180,500,1,60,100);
	
				k=0;		
				while(IMU>100){
						k++;
						if(k>10)break;
					ham_chay_nhanh(1,15,180,500,1,10,-100);
					vTaskDelay(1);
					
					}
				k=0;
				while(IMU<0){
				k++;
				if(k>10)break;
					ham_chay_nhanh(1,15,180,500,1,10,100);
					vTaskDelay(1);
					
				}
				BIT_CB_CHAN=0;
				k=0;
				while(1){
					k++;
					if(k>4)break;
					if(BIT_CB_CHAN==1)break;
					ham_chay_nhanh(1,10,180,500,1,50,0);
					
				}
					ham_chay_nhanh(2,10,180,400,1,50,0);
				
				test_nhay_day();
				
				ham_chay_nhanh(2,10,180,800,1,100,0);

				while(IMU>-750){
			
						ham_xoay(1,20,180,500,-30);
					vTaskDelay(1);
					
				}
				
		////////////////////////////////////////
				
		len_doc_xanh();
		////////////////////////////////////////
				
		len_doc_xanh();
				
				}

//////////////////////////////////////////////	
	void quet_tay_game(void){
		
		if(TAM_GIAC==0){
					
nhay_qua_day_ngan(1,0);
					
				}
				else if(O==0){
			nhay_qua_buc(1,0);
				
				}
				else if(X==0){
						nhay_qua_day(1,0);

					
				
				}
				else if(VUONG==0){
				
				chan_phai_truoc(60,60,0.01,0);
				chan_trai_sau(60,60,0.01,0);
				chan_phai_sau(60,60,0.01,0);
				chan_trai_truoc(60,60,0.01,0);
				}		
				
				else if(TOI==0){

				ham_chay_nhanh(1,10,180,500,1,150,0);
					//ham_di_len_doc(15,0,180,1000,0.3,120,-100);
				}
				
				else if(LUI==0){
					
					ham_chay_nhanh(1,20,180,700,1,0,0);
				
				}
		
				else if(TRAI==0){
			
						ham_xoay(1,20,180,500,30);
				}
					
				else if(PHAI==0){
		
						ham_xoay(1,20,180,500,-30);
				}
				
				else if(SELECT==0){
					tham_so_imu=0;
			//	 	qua_buc(1000);
					vTaskDelay(2000);
				ham_chay_nhanh(1,20,180,400,1,20,-450);
				}


				
				else{

						thay_doi_diem_giua(0,0,0,0,1);
												bu_do_cao(0,0,0,0,1);
												ham_dung(180,0.1);
									//	vTaskDelay(10000);
					
					
					
						tham_so_imu=0;
						run_read_gyro_uart1();
					
					}
				
		
		
		}
	//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX	
	void quet_nut_nhan(void){
		if( GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_15)==0)	{	//xanh
			
				if(NUT_STAR==0){
							XL_CHOT_ON;
										while(CB_THE==0){	vTaskDelay(1);}
										vTaskDelay(1000);
										while(CB_THE==1){	vTaskDelay(1);}
											
												XL_CHOT_OFF;
											run_read_gyro_uart1();	

												xuat_phat_xanh();
		
				}
				else if(NUT_QUA_BUC==0){
													run_read_gyro_uart1();	

													retry_xanh_1();	
				}
				
				else if(NUT_QUA_DAY==0){
											run_read_gyro_uart1();	

													retry_xanh_1();	
				}
				
				
				else if(NUT_LEN_DOC==0){

												len_doc_xanh();
				}
								
								
			else{
			
												thay_doi_diem_giua(0,0,0,0,1);
												bu_do_cao(0,0,0,0,1);
												ham_dung(180,0.1);
			
			
			}
				
	}
		
		
///////////XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX		
else{						//do

	if(NUT_STAR==0){
						XL_CHOT_ON;
										while(CB_THE==0){	vTaskDelay(1);}
										vTaskDelay(1000);
										while(CB_THE==1){	vTaskDelay(1);}
											
												XL_CHOT_OFF;
												run_read_gyro_uart1();	
												xuat_phat_do();
		
				}
				else if(NUT_QUA_BUC==0){
															run_read_gyro_uart1();	
															retry_do_1();	
				}
				
				else if(NUT_QUA_DAY==0){
											//			run_read_gyro_uart1();	
															///////////////////////////////DI TOI DAY	
											
										test_nhay_day();
	
				}
				
				
				else if(NUT_LEN_DOC==0){
													thay_doi_diem_giua(0,0,30,30,1);
																bu_do_cao(0,0,-50,-50,1);
																ham_dung(180,0.1);
												len_doc_xanh();
								}

			else{
			
					thay_doi_diem_giua(0,0,0,0,1);
												bu_do_cao(0,0,0,0,1);
												ham_dung(180,0.1);
			
			
			}


}		
					
		
		}
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
void retry_xanh_1(void)	{			
			int k;
						

				ham_chay_nhanh(5,10,180,500,1,50,-100);
				k=0;
				while(CB_CHAN_PHAI==1){
						k++;
						if(k>10)break;
						ham_chay_nhanh(1,10,180,350,1,50,0);	
				}	
				k=0;
				while(CB_CHAN_TRAI==1){
						k++;
						if(k>10)break;
						ham_chay_nhanh(1,10,180,350,1,50,-300);	
				}	

					ham_chay_nhanh(4,10,180,500,1,10,-350);	
				
				
				 vTaskDelay(1000);
	////////////////////////////////////nhay////////////////////////////////////////////////////////////////////	
				nhay_qua_buc(1,0);
	///////////////////////////////////////////////////////////////////////////////			
				
				
				ham_chay_nhanh(5,10,180,400,1,0,-600);
					
				ham_chay_nhanh(4,10,180,600,1,100,-500);
			
				ham_chay_nhanh(4,10,180,600,1,100,-250);
				ham_chay_nhanh(3,10,180,500,1,60,-100);
	
				k=0;		
				while(IMU<-100){
						k++;
						if(k>10)break;
					ham_chay_nhanh(1,15,180,500,1,10,100);
					vTaskDelay(1);
					
					}
				k=0;
				while(IMU>0){
				k++;
				if(k>10)break;
					ham_chay_nhanh(1,15,180,500,1,10,-100);
					vTaskDelay(1);
					
				}
				BIT_CB_CHAN=0;
				k=0;
				while(1){
					k++;
					if(k>4)break;
					if(BIT_CB_CHAN==1)break;
					ham_chay_nhanh(1,10,180,500,1,50,0);
					
				}
					ham_chay_nhanh(2,10,180,400,1,50,0);
				
				test_nhay_day();
				
				ham_chay_nhanh(2,10,180,800,1,100,0);

				while(IMU<750){
			
						ham_xoay(1,20,180,500,30);
					vTaskDelay(1);
					
				}
				
		////////////////////////////////////////
				
		len_doc_xanh();
				
	}	
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
void retry_xanh_2(void)	{			


				ham_chay_nhanh(2,15,180,700,1,100,0);
				ham_chay_nhanh(2,15,180,700,1,100,150);
				ham_chay_nhanh(2,15,180,500,1,100,300);
				while(IMU>500){
				
					ham_chay_nhanh(1,15,180,500,1,50,400);
					vTaskDelay(1);
					
					}
				
				while(IMU<400){
				
					ham_chay_nhanh(1,15,180,500,1,50,500);
					vTaskDelay(1);
					
				}
				ham_chay_nhanh(2,10,180,500,1,50,450);
				ham_chay_nhanh(4,10,180,500,1,50,450);
				
				
			//	while(1);
				
				nhay_qua_day(1,0);
				// vTaskDelay(1000);
				while(IMU>500){
				
					ham_chay_nhanh(1,15,180,700,1,10,400);
					vTaskDelay(1);
					
				}
				while(IMU<400){
				
					ham_chay_nhanh(1,20,180,700,1,20,500);
					vTaskDelay(1);
					
				}
				nhay_qua_day(1,0);
				 vTaskDelay(1000);
				nhay_qua_day_ngan(1,0);
			//	while(1);	
				
				
				while(IMU<1300){
				
					ham_chay_nhanh(1,20,180,700,1,0,1500);
					vTaskDelay(1);
					
				}
				
		/////
				
									thay_doi_diem_giua(0,0,30,30,1);
																bu_do_cao(0,0,-50,-50,1);
																ham_dung(180,0.1);
												len_doc_xanh();	
	}	
///////////////////////////////////////

	