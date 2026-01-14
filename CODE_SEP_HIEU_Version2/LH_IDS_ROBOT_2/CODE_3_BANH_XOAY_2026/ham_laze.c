
//vs32 CHAY_TU_DONG_THEO_LAZE_X_Y(vs32 chieu_chay,vs32 laze_chuan_x,vs32 laze_chuan_y,vs32 he_so_dap_ung_laze)
//{
//	float laze_lech,goc_lech;
//	laze_lech=((tanh(laze_chuan_x/laze_chuan_y) / 10)*radian)*he_so_dap_ung_laze;
//	if(laze_lech>900) laze_lech = 900;    //200
//	else if(laze_lech<-900)laze_lech =-900;		//200
//	laze_lech=laze_lech*chieu_chay;	
//	return laze_lech;
//	
//}
vs32 CHAY_TU_DONG_THEO_TOI_LUI(vs32 chieu_chay,vs32 e1_chuan,vs32 he_so_dap_ung_e1)
{
	vs32 e1_lech,goc_lech;

	e1_lech=(abs(READ_ENCODER(2)-e1_chuan)/10)*he_so_dap_ung_e1;
	if(e1_lech>200) e1_lech = 200;
	else if(e1_lech<-200)e1_lech = -200;		
	e1_lech=e1_lech*chieu_chay;	
	return e1_lech;
}	
void reset_ve_vt_dau()
{
	while(!R1)
	{
	RESET_ENCODER(1);
	RESET_ENCODER(2);
	RESET_IMU();
	Robot_Stop_Now(0);
	}
}
vs32 CHAY_TU_DONG_THEO_LAZE_E1_E2(vs32 chieu_chay,vs32 laze_chuan,vs32 he_so_dap_ung_laze)
{
	vs32 laze_lech,goc_lech,E3,hs_laze_theo_e3,bien;
	E3=sqrt(abs(READ_ENCODER(2))*abs(READ_ENCODER(2))+abs(READ_ENCODER(1))*abs(READ_ENCODER(1)));
	bien=E3/1000;
	if(bien>laze_chuan){bien=laze_chuan;}
	laze_lech=(laze_sau-bien)*he_so_dap_ung_laze;
	if(laze_lech>500) laze_lech = 500;    //200
	else if(laze_lech<-500)laze_lech =-500;		//200
	laze_lech=laze_lech*chieu_chay;	
	return laze_lech;
}	
vs32 CHAY_TU_DONG_THEO_LAZE_X(vs32 chieu_chay,vs32 laze_chuan,vs32 he_so_dap_ung_laze)
{
	vs32 laze_lech,goc_lech;

	laze_lech=(laze_sau-laze_chuan)*he_so_dap_ung_laze;
	if(laze_lech>500) laze_lech = 500;    //200
	else if(laze_lech<-500)laze_lech =-500;		//200
	laze_lech=laze_lech*chieu_chay;	
	return laze_lech;
}	
////////////////////
vs32 CHAY_TU_DONG_THEO_LAZE_Y(vs32 chieu_chay,vs32 laze_chuan,float he_so_dap_ung_laze)
{
	vs32 laze_lech,goc_lech;

	laze_lech=(laze_trai-laze_chuan)*he_so_dap_ung_laze;
	if(laze_lech>500) laze_lech = 500;
	else if(laze_lech<-500)laze_lech =-500;		
	laze_lech=laze_lech*chieu_chay;	
	return laze_lech;
}	
//void chinh_chan_da()
//{
//	if(!START)
//	{
//	chan_da_kich_ball_lui;
//	chan_da_kich_ball=20;
//	vTaskDelay(100);
//	chan_da_kich_ball=0;
//	}
//	else if(!SELECT)
//	{
//	chan_da_kich_ball_toi;
//	chan_da_kich_ball=20;
//	vTaskDelay(100);
//	chan_da_kich_ball=0;
//	}
//}
//void reset_e2()
//{
//	vs32 dem;
//	while(reset_ecoder2)
//	{
//	for(i=0;i<50;i++)
//	{
//	RESET_ENCODER(2);
//	vTaskDelay(200);
//	}
//	reset_ecoder2=0;
//	vTaskDelay(1);
//	}
//}
//void trang_thai_cho_da()
//{
//	 while(chuan_bi_da)
//	 {
//		while(1)
//		{
//		chan_da_kich_ball_lui;
//		chan_da_kich_ball=250;
//		if(!cb_cho_da||!X) break;
//		}
//		chan_da_kich_ball=0;
//		vTaskDelay(2);
//	 	chuan_bi_da=0;
//		}
//	  vTaskDelay(1);
//		
//}
void dat_tryball()
{
	 while(_bien_dat_tryball)
	 {
		while(1) {if(bien_tro<180)break;chan_da_kich_ball_toi;chan_da_kich_ball=150;vTaskDelay(1);}
		chan_da_kich_ball=0;vTaskDelay(1);
		xilanh_tryball_0;vTaskDelay(2000);
		while(1) {if(bien_tro>220)break;chan_da_kich_ball_lui;chan_da_kich_ball=100;vTaskDelay(1);bien_chay=1;}//if(bien_tro>125){bien_chay=1;}
		chan_da_kich_ball=0;
		if(bien_tro>235) break;
		vTaskDelay(1);
		}	
		bien_chay=0;
		_bien_dat_tryball=0;	 
}
void cho_dat_tryball()
{
	 while(_bien_cho_dat_tryball)
	 {
		while(1) {if(bien_tro<210)break;chan_da_kich_ball_toi;chan_da_kich_ball=150;vTaskDelay(1);}
		chan_da_kich_ball=2;vTaskDelay(1);
		if(bien_tro<230) break;
		vTaskDelay(1);
		}	
		_bien_cho_dat_tryball=0;	 
}
void ham_khoa_de()
{
	 while(bien_khoa_de)
	 {
		Robot_Stop_Now(5);
		vTaskDelay(1);
	}
}		
//void _lay_de()
//{
//		if(!nut_lay_de)
//	{
//		vTaskDelay(1000);
//		if(nut_lay_de){
//		bien_lay_de+=1;
//		if(bien_lay_de==5) bien_lay_de=0;
//		vTaskDelay(2);}
//	}
//}
void retry_()
{
	if(!nut_retry)
	{
		vTaskDelay(1000);
		if(nut_retry){
		_retry+=1;
		if(_retry==6) _retry=0;
		vTaskDelay(2);}
	}
}
////-chay-theo-laze----------------
//void chay_toi_theo_laze(vs32 mat,vs32 huong,vs32 toc_do_chay,float gia_toc,float chay_va_xoay,vs32 giam_toc,vs32 encoder,vs32 laze)
//	{
//	vs32 toc_do,dem;
//	for(dem=0;dem<10;dem++)
//	{
//		gia_toc=gia_toc/dem;
//		toc_do=toc_do_chay/dem;
//		MAIN_CONTROL(mat,huong-CHAY_TU_DONG_THEO_LAZE_Y(1,laze,5),toc_do,gia_toc,chay_va_xoay);
//		while(1){
//		if(abs(READ_ENCODER(1))>encoder/dem)break;
//		vTaskDelay(2);}
//		
//	}
//		for(dem=10;dem>0;dem--)
//	{
//		gia_toc=gia_toc/dem;
//		toc_do=toc_do_chay/dem;
//		MAIN_CONTROL(mat,huong-CHAY_TU_DONG_THEO_LAZE_Y(1,laze,5),toc_do,gia_toc,chay_va_xoay);
//		while(1){
//		if(abs(READ_ENCODER(1))>(giam_toc/(dem*10))+encoder)break;
//		vTaskDelay(2);}
//		}
//	vTaskDelay(2);
//	}
//	void chay_lui_theo_laze(vs32 encoder_2,vs32 laze)
//	{
//		while(1){
//			MAIN_CONTROL(0,1800-CHAY_TU_DONG_THEO_LAZE_Y(-1,laze,2),80,gt,0);//CHAY toi theo laze vao dung vi tri dat bong
//			if(abs(READ_ENCODER(1))>encoder_2)break;
//			vTaskDelay(1);
//			}
//	}
//	//-chay-theo-laze----------------
//void chay_phai_theo_laze(vs32 encoder_1,vs32 laze)
//	{
//		while(1){
//			MAIN_CONTROL(0,-900-CHAY_TU_DONG_THEO_LAZE_X(1,laze,2),80,gt,0);//CHAY toi theo laze vao dung vi tri dat bong
//			if(abs(READ_ENCODER(2))>encoder_1)break;
//			vTaskDelay(1);
//			}
//	}
//	void chay_trai_theo_laze(vs32 encoder_1,vs32 laze)
//	{
//		while(1){
//			MAIN_CONTROL(0,900-CHAY_TU_DONG_THEO_LAZE_X(-1,laze,2),80,gt,0);//CHAY toi theo laze vao dung vi tri dat bong
//			if(abs(READ_ENCODER(2))>encoder_1)break;
//			vTaskDelay(1);
//			}
//	}