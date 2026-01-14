void dat_tryball_tay()
{
	if(!R2){
		xilanh_tryball_1;xilanh_tay_dat_1;
		vTaskDelay(6000);
		while(1) {if(bien_tro<180||!X)break;chan_da_kich_ball_toi;chan_da_kich_ball=50;vTaskDelay(1);}
		while(1) {if(bien_tro<140||!X)break;chan_da_kich_ball_toi;chan_da_kich_ball=20;vTaskDelay(1);}
		chan_da_kich_ball=2;vTaskDelay(1);
		while(R2)vTaskDelay(1);
		while(1) {if(bien_tro<100||!X)break;chan_da_kich_ball_toi;chan_da_kich_ball=100;vTaskDelay(1);}
		chan_da_kich_ball=0;vTaskDelay(1);
		xilanh_tryball_0;vTaskDelay(2000);
		chan_da_kich_ball=0;vTaskDelay(500);
		while(1) {if(bien_tro>220||!X)break;chan_da_kich_ball_lui;chan_da_kich_ball=100;vTaskDelay(1);}
		chan_da_kich_ball=0;xilanh_tryball_0;
		vTaskDelay(6000);
		xilanh_tay_dat_0;
		}
}
void stop()
{
	if(!L2||!X){_stop=1;Robot_Stop_Now(0);MAIN_CONTROL(0,0,0,2,0);}
	if(!VUONG){_stop=1;Robot_Stop_Now(0);}
	if(!O){_stop=0;RESET_ENCODER(1);RESET_ENCODER(2);RESET_IMU();}
}
void dovitri()
{
	int dem=0;
	while(1)
	{
			if(!cb_quang_trai&&cb_quang_phai)  {MAIN_CONTROL(0,-900,30,4,0);}
				else if(cb_quang_trai&&!cb_quang_phai){MAIN_CONTROL(0,900,30,4,0);}
					else if(cb_trai&&cb_phai)	{MAIN_CONTROL(0,0,30,2,0);}
					else	dem++;
					if(dem > 5) break;
					if(!X) break;
	}
	
}
void tryball_1()
{
		while(abs(READ_ENCODER(3))<300)  {if(!X) break;MAIN_CONTROL(0,1020-CHAY_TU_DONG_THEO_LAZE_X(-1,28,1),50,5,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<500)  {if(!X) break;MAIN_CONTROL(0,1020-CHAY_TU_DONG_THEO_LAZE_X(-1,28,1),100,5,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<1000) {if(!X) break;MAIN_CONTROL(0,1020-CHAY_TU_DONG_THEO_LAZE_X(-1,28,1),150,5,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<1500) {if(!X) break;MAIN_CONTROL(0,1020-CHAY_TU_DONG_THEO_LAZE_X(-1,28,1),200,5,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<3000) {if(!X) break;MAIN_CONTROL(0,1020-CHAY_TU_DONG_THEO_LAZE_X(-1,28,1),250,5,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<5000) {if(!X) break;MAIN_CONTROL(0,1020-CHAY_TU_DONG_THEO_LAZE_X(-1,28,1),300,5,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<15000){if(!X) break;MAIN_CONTROL(0,1020-CHAY_TU_DONG_THEO_LAZE_X(-1,28,1),300,5,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<22000){if(!X) break;MAIN_CONTROL(0,1020-CHAY_TU_DONG_THEO_LAZE_X(-1,28,7),300,15,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<28000){if(!X) break;MAIN_CONTROL(0,920-CHAY_TU_DONG_THEO_LAZE_X(-1,28,7),250,15,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<32000){if(!X) break;MAIN_CONTROL(0,920-CHAY_TU_DONG_THEO_LAZE_X(-1,28,7),200,15,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<36000){if(!X) break;MAIN_CONTROL(0,920-CHAY_TU_DONG_THEO_LAZE_X(-1,28,7),150,15,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<39000){if(!X) break;MAIN_CONTROL(0,920-CHAY_TU_DONG_THEO_LAZE_X(-1,28,7),100,15,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<40000){if(!X) break;MAIN_CONTROL(0,920-CHAY_TU_DONG_THEO_LAZE_X(-1,28,7),50,15,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<41000){if(!X) break;MAIN_CONTROL(0,920-CHAY_TU_DONG_THEO_LAZE_X(-1,28,7),20,7,0);vTaskDelay(1);}	
		while(laze_sau!=28){
		while(laze_sau<28) {if(!X) break;MAIN_CONTROL(0,0-CHAY_TU_DONG_THEO_LAZE_Y(1,70,2),15,0.2,0);}
		while(laze_sau>28) {if(!X) break;MAIN_CONTROL(0,1800-CHAY_TU_DONG_THEO_LAZE_Y(1,70,2),15,0.2,0);}	
		if(!X) break;}
//		e2 41600 E1 7900 laze_trai 64 laze_sau 27
		Robot_Stop_Now(5);vTaskDelay(100);//(laze_phai>4&&laze_phai<12)|| 
		while(_stop||!X){if(!O) break;vTaskDelay(1);}
		RESET_ENCODER(3);vTaskDelay(1);
		RESET_ENCODER(2);vTaskDelay(1);
	}
void test_tryball_1()
{
		while(abs(READ_ENCODER(3))<300)  {if(!X) break;MAIN_CONTROL(0,950-CHAY_TU_DONG_THEO_LAZE_E1_E2(-1,23,2),50,1,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<500)  {if(!X) break;MAIN_CONTROL(0,950-CHAY_TU_DONG_THEO_LAZE_E1_E2(-1,23,2),150,1,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<1500) {if(!X) break;MAIN_CONTROL(0,950-CHAY_TU_DONG_THEO_LAZE_E1_E2(-1,23,2),200,1,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<2000) {if(!X) break;MAIN_CONTROL(0,950-CHAY_TU_DONG_THEO_LAZE_E1_E2(-1,23,2),250,1,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<5000) {if(!X) break;MAIN_CONTROL(0,950-CHAY_TU_DONG_THEO_LAZE_E1_E2(-1,23,2),300,1,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<16000){if(!X) break;MAIN_CONTROL(0,950-CHAY_TU_DONG_THEO_LAZE_E1_E2(-1,23,2),300,1,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<23000){if(!X) break;MAIN_CONTROL(0,950-CHAY_TU_DONG_THEO_LAZE_E1_E2(-1,23,2),300,2,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<26000){if(!X) break;MAIN_CONTROL(0,908-CHAY_TU_DONG_THEO_LAZE_X(-1,24,7),250,15,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<32000){if((laze_trai>200&&laze_trai<213)||!X) break;MAIN_CONTROL(0,908-CHAY_TU_DONG_THEO_LAZE_X(-1,24,7),200,2,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<37000){if((laze_trai>150&&laze_trai<155)||!X) break;MAIN_CONTROL(0,908-CHAY_TU_DONG_THEO_LAZE_X(-1,24,7),150,2,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<39000){if((laze_trai>115&&laze_trai<123)||!X) break;MAIN_CONTROL(0,908-CHAY_TU_DONG_THEO_LAZE_X(-1,24,7),100,2,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<40000){if((laze_trai>75&&laze_trai<88)||!X) break;MAIN_CONTROL(0,908-CHAY_TU_DONG_THEO_LAZE_X(-1,24,7),50,2,0);vTaskDelay(1);}
		while(laze_trai>70&&laze_trai<100){if(!X) break;MAIN_CONTROL(0,908-CHAY_TU_DONG_THEO_LAZE_X(-1,24,7),20,2,0);vTaskDelay(1);}
		while(laze_sau!=24){
		while(laze_sau<24) {if(!X) break;MAIN_CONTROL(0,0-CHAY_TU_DONG_THEO_LAZE_Y(1,70,2),15,0.2,0);}
		while(laze_sau>24) {if(!X) break;MAIN_CONTROL(0,1800-CHAY_TU_DONG_THEO_LAZE_Y(1,70,2),15,0.2,0);}	
		if(!X) break;}
//		e2 41600 E1 7900 laze_trai 64 laze_sau 27
		while(_stop||!X){if(!O) break;vTaskDelay(1);}
		Robot_Stop_Now(5);vTaskDelay(100);//(laze_phai>4&&laze_phai<12) 
		RESET_ENCODER(3);
		RESET_ENCODER(2);
		vTaskDelay(1);
}
void dat_tryball_1()//vi tri 3
{
		Robot_Stop_Now(0);
		MAIN_CONTROL(0,-480,50,1,0); while(abs(READ_ENCODER(2))<500)  {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,-480,100,1,0);while(abs(READ_ENCODER(2))<1000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,-480,150,1,0);while(abs(READ_ENCODER(2))<2000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,-480,200,1,0);while(abs(READ_ENCODER(2))<3000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,-480,250,1,0);while(abs(READ_ENCODER(2))<5000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,-480,250,1,0);while(abs(READ_ENCODER(2))<15000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,-480,200,1,0);while(abs(READ_ENCODER(2))<23000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,-480,150,2,0);while(abs(READ_ENCODER(2))<30000) {if((laze_sau>10&&laze_sau<40)||(laze_phai>150&&laze_phai<170)||!X) break;	vTaskDelay(1);}
		xilanh_tryball_1;
		xilanh_tay_dat_1;
		MAIN_CONTROL(0,-320,150,2,0);while(abs(READ_ENCODER(2))<36000) {if(!X) break;	vTaskDelay(1);}
		_bien_cho_dat_tryball=1;
		MAIN_CONTROL(0,-320,100,2,0);while(abs(READ_ENCODER(2))<39000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,-320,50,2,0); while(abs(READ_ENCODER(2))<42000) {if((!cb_trai||!cb_phai)||!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,-320,20,2,0); while(abs(READ_ENCODER(2))<46000) {if((!cb_trai||!cb_phai)||(!cb_quang_trai||!cb_quang_phai)||!X) break;	vTaskDelay(1);}
		dovitri();
		while(_stop||!X){if(!O) break;vTaskDelay(1);}
		if(X) _bien_dat_tryball=1;
		MAIN_CONTROL(0,0,30,1,0);vTaskDelay(500);
		Robot_Stop_Now(5);vTaskDelay(100);
		RESET_ENCODER(3);
		RESET_ENCODER(2);
		RESET_IMU();
		vTaskDelay(1);
	}
void tryball_2()
{
		Robot_Stop_Now(0);
		MAIN_CONTROL(0,1390,50,4,0); while(abs(READ_ENCODER(2))<500)  {if(!X) break;vTaskDelay(1);}
		MAIN_CONTROL(0,1390,100,4,0);while(abs(READ_ENCODER(2))<1000) 	{if(!X) break;vTaskDelay(1);}
		MAIN_CONTROL(0,1390,150,4,0);while(abs(READ_ENCODER(2))<1500) {if(!X) break;vTaskDelay(1);}
		MAIN_CONTROL(0,1390,200,4,0);while(abs(READ_ENCODER(2))<3000) {if(!X) break;vTaskDelay(1);}
		xilanh_tay_dat_0;
		MAIN_CONTROL(0,1390,220,4,0);while(abs(READ_ENCODER(2))<5000) {if(!X) break;vTaskDelay(1);}
		MAIN_CONTROL(0,1390,220,4,0);while(abs(READ_ENCODER(2))<17000){if(!X) break;vTaskDelay(1);}
		MAIN_CONTROL(0,1390,220,4,0);while(abs(READ_ENCODER(2))<26000){if(!X) break;vTaskDelay(1);}
		MAIN_CONTROL(0,1390,200,4,0);while(abs(READ_ENCODER(2))<32000){if(!X) break;vTaskDelay(1);}
		MAIN_CONTROL(0,1390,150,4,0);while(abs(READ_ENCODER(2))<37000){if(!X) break;vTaskDelay(1);}
		MAIN_CONTROL(0,1390,100,4,0);while(laze_sau>37&&laze_sau<100){if(!X) break;vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<22000){if((laze_trai>48&&laze_trai<60)||!X) break;MAIN_CONTROL(0,900-CHAY_TU_DONG_THEO_LAZE_X(-1,23,2),100,10,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<23000){if((laze_trai>36&&laze_trai<48)||!X) break;MAIN_CONTROL(0,900-CHAY_TU_DONG_THEO_LAZE_X(-1,23,2),50,10,0);vTaskDelay(1);}
		while(laze_trai>48&&laze_trai<100){if(!X) break;MAIN_CONTROL(0,900-CHAY_TU_DONG_THEO_LAZE_X(-1,23,2),20,10,0);vTaskDelay(1);}
		while(laze_trai!=47){
		while(laze_trai<47) {if(!X) break;MAIN_CONTROL(0,-900,20,1,0);}
		while(laze_trai>47) {if(!X) break;MAIN_CONTROL(0,900,20,1,0);}
		if(!X) break;}
		while(laze_sau!=23){
		while(laze_sau<23) {if(!X) break;MAIN_CONTROL(0,0,20,1,0);}
		while(laze_sau>23) {if(!X) break;MAIN_CONTROL(0,1800,20,1,0);}
		if(!X) break;}
		Robot_Stop_Now(5);vTaskDelay(100);
		RESET_ENCODER(3);
		RESET_ENCODER(2);
		vTaskDelay(1);
}
void dat_tryball_2() //vi tri 2
{
		Robot_Stop_Now(0);
		MAIN_CONTROL(0,-540,50,1,0); while(abs(READ_ENCODER(2))<500)  {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,-540,100,1,0);while(abs(READ_ENCODER(2))<1000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,-540,150,1,0);while(abs(READ_ENCODER(2))<2000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,-540,200,1,0);while(abs(READ_ENCODER(2))<3000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,-540,250,1,0);while(abs(READ_ENCODER(2))<7000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,-540,200,1,0);while(abs(READ_ENCODER(2))<15000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,-540,150,1,0);while(abs(READ_ENCODER(2))<23000) {if((laze_trai>220&&laze_trai<300)||!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,0,150,2,0);while(abs(READ_ENCODER(2))<30000) {if(!X) break;	vTaskDelay(1);}
		xilanh_tryball_1;
		xilanh_tay_dat_1;
		MAIN_CONTROL(0,0,150,2,0);while(abs(READ_ENCODER(2))<36000) {if(!X) break;	vTaskDelay(1);}
		_bien_cho_dat_tryball=1;
		MAIN_CONTROL(0,0,100,2,0);while(abs(READ_ENCODER(2))<39000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,0,50,2,0); while(abs(READ_ENCODER(2))<42000) {if((!cb_trai||!cb_phai)||!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,0,20,2,0); while(abs(READ_ENCODER(2))<46000) {if((!cb_trai||!cb_phai)||(!cb_quang_trai||!cb_quang_phai)||!X) break;	vTaskDelay(1);}
		dovitri();
		while(_stop||!X){if(!O) break;vTaskDelay(1);}
		if(X) _bien_dat_tryball=1;
		MAIN_CONTROL(0,0,30,4,0);vTaskDelay(500);
		Robot_Stop_Now(5);vTaskDelay(100);
		RESET_ENCODER(2);
		RESET_ENCODER(3);
		RESET_IMU();
		vTaskDelay(1);
}
void tryball_3()
{
		Robot_Stop_Now(0);
		while(abs(READ_ENCODER(2))<500)  {if(!X) break;MAIN_CONTROL(0,1560,50,1,0);vTaskDelay(1);}//lon len thi qua trai
		while(abs(READ_ENCODER(2))<1000)  {if(!X) break;MAIN_CONTROL(0,1560,100,1,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<3000) {if(!X) break;MAIN_CONTROL(0,1560,150,1,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<7000) {if(!X) break;MAIN_CONTROL(0,1560,200,1,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<15000) {if(!X) break;MAIN_CONTROL(0,1560,150,1,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<18000){if((laze_trai>150&&laze_trai<255)||!X) break;MAIN_CONTROL(0,1560,150,2,0);vTaskDelay(1);}
		xilanh_tay_dat_0;
		while(abs(READ_ENCODER(2))<28000){if((laze_trai>150&&laze_trai<245)||!X) break;MAIN_CONTROL(0,1560,150,2,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<34000){if(!X) break;MAIN_CONTROL(0,1800-CHAY_TU_DONG_THEO_LAZE_Y(1,235,10),150,2,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<38000){if((laze_sau>50&&laze_sau<67)||!X) break;MAIN_CONTROL(0,1800-CHAY_TU_DONG_THEO_LAZE_Y(1,235,10),150,2,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<45000){if((laze_sau>15&&laze_sau<30)||!X) break;MAIN_CONTROL(0,1800-CHAY_TU_DONG_THEO_LAZE_Y(1,235,10),100,2,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<46000){if((laze_sau>12&&laze_sau<15)||!X) break;MAIN_CONTROL(0,1800-CHAY_TU_DONG_THEO_LAZE_Y(1,235,10),50,2,0);vTaskDelay(1);}
		while(laze_sau>12&&laze_sau<200){if(!X) break;MAIN_CONTROL(0,1800-CHAY_TU_DONG_THEO_LAZE_Y(1,235,10),20,2,0);vTaskDelay(1);}
		while(laze_sau!=12){
		while(laze_sau<12) {if(!X) break;MAIN_CONTROL(0,0,20,0.5,0);}
		while(laze_sau>12) {if(!X) break;MAIN_CONTROL(0,1800,20,0.5,0);}
		if(!X) break;}
		Robot_Stop_Now(5);vTaskDelay(100);
		RESET_ENCODER(3);
		RESET_ENCODER(2);vTaskDelay(1);
}
void dat_tryball_3()//vi tri 1
{
		Robot_Stop_Now(0);
		while(abs(READ_ENCODER(2))<500)  {if(!X) break;MAIN_CONTROL(0,-50-CHAY_TU_DONG_THEO_LAZE_Y(-1,250,8),50,1,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<2000) {if(!X) break;MAIN_CONTROL(0,-50-CHAY_TU_DONG_THEO_LAZE_Y(-1,250,8),100,1,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<6000) {if(!X) break;MAIN_CONTROL(0,-50-CHAY_TU_DONG_THEO_LAZE_Y(-1,250,8),150,1,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<12000){if(!X) break;MAIN_CONTROL(0,-50-CHAY_TU_DONG_THEO_LAZE_Y(-1,250,8),200,1,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<21000){if(!X) break;MAIN_CONTROL(0,-50-CHAY_TU_DONG_THEO_LAZE_Y(-1,250,8),200,1,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<22000){if(!X) break;MAIN_CONTROL(0,-50-CHAY_TU_DONG_THEO_LAZE_Y(-1,250,8),150,1,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<23000){if(!X) break;MAIN_CONTROL(0,170,150,1,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<28000){if(!X) break;MAIN_CONTROL(0,170,200,2,0);vTaskDelay(1);}
		xilanh_tryball_1;
		xilanh_tay_dat_1;
		while(abs(READ_ENCODER(2))<37000){if(!X) break;MAIN_CONTROL(0,170,150,2,0);vTaskDelay(1);}
		_bien_cho_dat_tryball=1;
		while(abs(READ_ENCODER(2))<46000){if(!X) break;MAIN_CONTROL(0,170,100,2,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<48000){if((!cb_trai||!cb_phai)||!X) break;MAIN_CONTROL(0,170,50,2,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<49000){if((!cb_trai||!cb_phai)||(!cb_quang_trai||!cb_quang_phai)||!X) break;MAIN_CONTROL(0,170,20,2,0);vTaskDelay(1);}
		dovitri();
		while(_stop||!X){if(!O) break;vTaskDelay(1);}
		if(X) _bien_dat_tryball=1;
		MAIN_CONTROL(0,0,30,4,0);vTaskDelay(500);
		Robot_Stop_Now(5);vTaskDelay(100);
		RESET_ENCODER(3);
		RESET_ENCODER(2);
		RESET_IMU();
		vTaskDelay(1);
}
void tryball_4()
{
		Robot_Stop_Now(0);
		while(abs(READ_ENCODER(2))<500)  {if(!X) break;MAIN_CONTROL(0,-1400,50,1,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<2000)  {if(!X) break;MAIN_CONTROL(0,-1400,100,1,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<6000) {if(!X) break;MAIN_CONTROL(0,-1400,150,1,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<12000) {if(!X) break;MAIN_CONTROL(0,1600,200,1,0);vTaskDelay(1);}//lin thi len phai
		while(abs(READ_ENCODER(2))<18000) {if(!X) break;MAIN_CONTROL(0,1600,200,1,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<19000) {if(!X) break;MAIN_CONTROL(0,1600,150,1,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<28000){if((laze_trai>240&&laze_trai<400)||!X) break;MAIN_CONTROL(0,1600,150,2,0);vTaskDelay(1);}
		xilanh_tay_dat_0;
		while(abs(READ_ENCODER(2))<34000){if(!X) break;MAIN_CONTROL(0,1800-CHAY_TU_DONG_THEO_LAZE_Y(1,240,10),200,2,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<38000){if((laze_sau>50&&laze_sau<67)||!X) break;MAIN_CONTROL(0,1800-CHAY_TU_DONG_THEO_LAZE_Y(1,240,10),150,2,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<44000){if((laze_sau>20&&laze_sau<26)||!X) break;MAIN_CONTROL(0,1800-CHAY_TU_DONG_THEO_LAZE_Y(1,240,10),100,2,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<46000){if((laze_sau>12&&laze_sau<14)||!X) break;MAIN_CONTROL(0,1800-CHAY_TU_DONG_THEO_LAZE_Y(1,240,10),50,2,0);vTaskDelay(1);}
		while(laze_sau>12&&laze_sau<200){if(!X) break;MAIN_CONTROL(0,1800-CHAY_TU_DONG_THEO_LAZE_Y(1,240,10),20,2,0);vTaskDelay(1);}
		while(laze_sau!=12){
		while(laze_sau<12) {if(!X) break;MAIN_CONTROL(0,0,20,0.5,0);}
		while(laze_sau>12) {if(!X) break;MAIN_CONTROL(0,1800,20,0.5,0);}
		if(!X) break;}
		Robot_Stop_Now(5);vTaskDelay(100);
		RESET_ENCODER(3);
		RESET_ENCODER(2);
		vTaskDelay(1);
}
void dat_tryball_4() //vi tri 5
{
		Robot_Stop_Now(0);
		MAIN_CONTROL(0,-540,50,1,0); while(abs(READ_ENCODER(2))<500)  {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,-540,100,1,0);while(abs(READ_ENCODER(2))<1000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,-540,150,1,0);while(abs(READ_ENCODER(2))<2000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,-540,200,2,0);while(abs(READ_ENCODER(2))<1000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,-540,200,2,0);while(abs(READ_ENCODER(2))<5000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,-540,200,2,0);while(abs(READ_ENCODER(2))<17000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,-370,150,4,0);while(abs(READ_ENCODER(2))<24000) {if((laze_sau>112&&laze_sau<140)||!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,-370,150,4,0);while(abs(READ_ENCODER(2))<27000) {if(!X) break;	vTaskDelay(1);}//(laze_sau>130&&laze_sau<150)||
		MAIN_CONTROL(0,-370,150,4,0);while(abs(READ_ENCODER(2))<33000) {if(!X) break;	vTaskDelay(1);}
		xilanh_tryball_1;
		xilanh_tay_dat_1;
		MAIN_CONTROL(0,-370,150,4,0);while(abs(READ_ENCODER(2))<39000) {if(!X) break;	vTaskDelay(1);}
		_bien_cho_dat_tryball=1;
		while(abs(READ_ENCODER(2))<44000) {if(!X) break;MAIN_CONTROL(0,-370-CHAY_TU_DONG_THEO_LAZE_Y_P(-1,46,5),100,4,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<46000) {if((!cb_trai||!cb_phai)||!X) break;MAIN_CONTROL(0,-370-CHAY_TU_DONG_THEO_LAZE_Y_P(-1,46,5),50,4,0); vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<48000) {if((!cb_trai||!cb_phai)||(!cb_quang_trai||!cb_quang_phai)||!X) break;MAIN_CONTROL(0,-370-CHAY_TU_DONG_THEO_LAZE_Y_P(-1,46,5),20,4,0); vTaskDelay(1);}
		dovitri();
		while(_stop||!X){if(!O) break;vTaskDelay(1);}
		if(X) _bien_dat_tryball=1;
		MAIN_CONTROL(0,0,20,4,0);vTaskDelay(500);
		Robot_Stop_Now(5);vTaskDelay(100);
		RESET_ENCODER(3);
		RESET_ENCODER(2);
		RESET_IMU();
		vTaskDelay(1);
}
void tryball_5()
{
		Robot_Stop_Now(0);
		MAIN_CONTROL(0,1390,50,1,0); while(abs(READ_ENCODER(2))<500)  {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,1390,100,1,0);while(abs(READ_ENCODER(2))<1000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,1390,150,1,0);while(abs(READ_ENCODER(2))<2000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,1390,200,1,0);while(abs(READ_ENCODER(2))<3000) {if(!X) break;	vTaskDelay(1);}
		xilanh_tay_dat_0;
		MAIN_CONTROL(0,1390,250,1,0);while(abs(READ_ENCODER(2))<5000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,1390,270,1,0);while(abs(READ_ENCODER(2))<17000){if(!X) break;vTaskDelay(1);}
		MAIN_CONTROL(0,1390,250,2,0);while(abs(READ_ENCODER(2))<27000){if(!X) break;vTaskDelay(1);}
		MAIN_CONTROL(0,1390,200,2,0);while(abs(READ_ENCODER(2))<33000){if(!X) break;vTaskDelay(1);}
		MAIN_CONTROL(0,1390,150,2,0);while(abs(READ_ENCODER(2))<40000){if(!X) break;vTaskDelay(1);}
		while(laze_sau>25&&laze_sau<100){if(!X) break;MAIN_CONTROL(0,1400,100,2,0);vTaskDelay(1);}
//		while(abs(READ_ENCODER(3))<22000){if((laze_phai>140&&laze_phai<150)||!X) break;MAIN_CONTROL(0,-900-CHAY_TU_DONG_THEO_LAZE_X(-1,12,4),150,10,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<23000){if((laze_trai>250&&laze_trai<260)||!X) break;MAIN_CONTROL(0,900-CHAY_TU_DONG_THEO_LAZE_X(1,12,2),100,10,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<24000){if((laze_trai>240&&laze_trai<250)||!X) break;MAIN_CONTROL(0,900-CHAY_TU_DONG_THEO_LAZE_X(1,12,2),50,10,0);vTaskDelay(1);}
		while(laze_trai>235&&laze_trai<500){if(!X) break;MAIN_CONTROL(0,900-CHAY_TU_DONG_THEO_LAZE_X(1,12,2),20,10,0);vTaskDelay(1);}
		while(laze_trai!=235){
		while(laze_trai<235) {if(!X) break;MAIN_CONTROL(0,0,20,0.5,0);}
		while(laze_trai>235) {if(!X) break;MAIN_CONTROL(0,1800,20,0.5,0);}
		if(!X) break;}
		while(laze_sau!=12){
		while(laze_sau<12) {if(!X) break;MAIN_CONTROL(0,0,20,0.5,0);}
		while(laze_sau>12) {if(!X) break;MAIN_CONTROL(0,1800,20,0.5,0);}
		if(!X) break;}
		Robot_Stop_Now(5);vTaskDelay(100);
		RESET_ENCODER(3);
		RESET_ENCODER(2);
		vTaskDelay(1);
} 
void dat_tryball_5() //vi tri 4
{
		Robot_Stop_Now(0);
		MAIN_CONTROL(0,-530,50,1,0); while(abs(READ_ENCODER(2))<500)  {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,-530,100,1,0);while(abs(READ_ENCODER(2))<1000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,-530,150,1,0);while(abs(READ_ENCODER(2))<2000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,-530,200,2,0);while(abs(READ_ENCODER(2))<1000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,-530,200,2,0);while(abs(READ_ENCODER(2))<5000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,-530,200,2,0);while(abs(READ_ENCODER(2))<17000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,-530,150,4,0);while(abs(READ_ENCODER(2))<24000) {if((laze_sau>112&&laze_sau<140)||!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,0,150,4,0);while(abs(READ_ENCODER(2))<27000) {if(!X) break;	vTaskDelay(1);}//(laze_sau>130&&laze_sau<150)||
		MAIN_CONTROL(0,0,150,4,0);while(abs(READ_ENCODER(2))<33000) {if(!X) break;	vTaskDelay(1);}
		xilanh_tryball_1;
		xilanh_tay_dat_1;
		MAIN_CONTROL(0,0,150,4,0);while(abs(READ_ENCODER(2))<39000) {if(!X) break;	vTaskDelay(1);}
		_bien_cho_dat_tryball=1;
		while(abs(READ_ENCODER(2))<44000) {if(!X) break;MAIN_CONTROL(0,0-CHAY_TU_DONG_THEO_LAZE_Y_P(-1,104,5),100,4,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<46000) {if((!cb_trai||!cb_phai)||!X) break;MAIN_CONTROL(0,0-CHAY_TU_DONG_THEO_LAZE_Y_P(-1,46,5),50,4,0); vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<48000) {if((!cb_trai||!cb_phai)||(!cb_quang_trai||!cb_quang_phai)||!X) break;MAIN_CONTROL(0,0-CHAY_TU_DONG_THEO_LAZE_Y_P(-1,46,5),20,4,0); vTaskDelay(1);}
		dovitri();
		Robot_Stop_Now(5);vTaskDelay(100);	
		while(TAM_GIAC)vTaskDelay(1);
		if(X) _bien_dat_tryball=1;
		MAIN_CONTROL(0,0,20,4,0);vTaskDelay(500);
		RESET_ENCODER(3);
		RESET_ENCODER(2);
		RESET_IMU();
		vTaskDelay(1);
}
