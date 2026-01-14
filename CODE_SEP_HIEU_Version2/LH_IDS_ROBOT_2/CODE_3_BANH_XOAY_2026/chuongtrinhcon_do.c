void dovitri_do()
{
	int dem=0;
	while(1)
	{
			if(!cb_quang_trai&&cb_quang_phai)  {MAIN_CONTROL(0,-900,20,1,0);}
				else if(cb_quang_trai&&!cb_quang_phai){MAIN_CONTROL(0,900,20,1,0);}
					else if(cb_trai&&cb_phai)	{MAIN_CONTROL(0,0,30,1,0);}
					else	dem++;
					if(dem > 12) break;
					if(!X) break;
	}
}
void tryball_1_do()
{
		while(abs(READ_ENCODER(3))<300)  {if(!X) break;MAIN_CONTROL(0,-950-CHAY_TU_DONG_THEO_LAZE_X(1,28,3),50,5,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<500)  {if(!X) break;MAIN_CONTROL(0,-950-CHAY_TU_DONG_THEO_LAZE_X(1,28,3),100,5,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<1000) {if(!X) break;MAIN_CONTROL(0,-950-CHAY_TU_DONG_THEO_LAZE_X(1,28,3),150,5,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<1500) {if(!X) break;MAIN_CONTROL(0,-950-CHAY_TU_DONG_THEO_LAZE_X(1,28,3),200,5,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<3000) {if(!X) break;MAIN_CONTROL(0,-950-CHAY_TU_DONG_THEO_LAZE_X(1,28,3),250,5,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<5000) {if(!X) break;MAIN_CONTROL(0,-950-CHAY_TU_DONG_THEO_LAZE_X(1,28,3),300,5,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<16000){if(!X) break;MAIN_CONTROL(0,-950-CHAY_TU_DONG_THEO_LAZE_X(1,28,3),330,5,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<25000){if(!X) break;MAIN_CONTROL(0,-930-CHAY_TU_DONG_THEO_LAZE_X(1,28,5),300,15,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<28000){if(!X) break;MAIN_CONTROL(0,-930-CHAY_TU_DONG_THEO_LAZE_X(1,28,5),250,15,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<32000){if(!X) break;MAIN_CONTROL(0,-930-CHAY_TU_DONG_THEO_LAZE_X(1,28,5),200,15,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<36000){if(!X) break;MAIN_CONTROL(0,-930-CHAY_TU_DONG_THEO_LAZE_X(1,28,5),150,15,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<39000){if(!X) break;MAIN_CONTROL(0,-930-CHAY_TU_DONG_THEO_LAZE_X(1,28,5),100,15,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<41000){if(!X) break;MAIN_CONTROL(0,-930-CHAY_TU_DONG_THEO_LAZE_X(1,28,5),50,15,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<41500){if(!X) break;MAIN_CONTROL(0,-930-CHAY_TU_DONG_THEO_LAZE_X(1,28,5),20,7,0);vTaskDelay(1);}	
		while(laze_sau!=28){
		while(laze_sau<28) {if(!X) break;MAIN_CONTROL(0,0,15,0.2,0);}
		while(laze_sau>28) {if(!X) break;MAIN_CONTROL(0,1800,15,0.2,0);}	
		if(!X) break;}
//		e2 41600 E1 7900 laze_trai 64 laze_sau 27
		Robot_Stop_Now(5);vTaskDelay(100);//(laze_phai>4&&laze_phai<12)|| 
		while(_stop||!X){if(!O) break;vTaskDelay(1);}
		RESET_ENCODER(3);
		RESET_ENCODER(2);
		vTaskDelay(1);
	}
void test_tryball_1_do()
{
		while(abs(READ_ENCODER(3))<50)  {if(!X) break;MAIN_CONTROL(0,-880-CHAY_TU_DONG_THEO_LAZE_E1_E2(1,24,2),20,3,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<150)  {if(!X) break;MAIN_CONTROL(0,-880-CHAY_TU_DONG_THEO_LAZE_E1_E2(1,24,2),50,3,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<500)  {if(!X) break;MAIN_CONTROL(0,-880-CHAY_TU_DONG_THEO_LAZE_E1_E2(1,24,2),100,3,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<1000)  {if(!X) break;MAIN_CONTROL(0,-880-CHAY_TU_DONG_THEO_LAZE_E1_E2(1,24,2),150,3,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<1500) {if(!X) break;MAIN_CONTROL(0,-880-CHAY_TU_DONG_THEO_LAZE_E1_E2(1,24,2),200,1,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<2500) {if(!X) break;MAIN_CONTROL(0,-880-CHAY_TU_DONG_THEO_LAZE_E1_E2(1,24,2),250,1,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<5000) {if(!X) break;MAIN_CONTROL(0,-880-CHAY_TU_DONG_THEO_LAZE_E1_E2(1,24,2),300,1,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<16000){if(!X) break;MAIN_CONTROL(0,-900-CHAY_TU_DONG_THEO_LAZE_E1_E2(1,24,2),300,1,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<23000){if(!X) break;MAIN_CONTROL(0,-900-CHAY_TU_DONG_THEO_LAZE_E1_E2(1,24,2),300,2,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<28000){if(!X) break;MAIN_CONTROL(0,-900-CHAY_TU_DONG_THEO_LAZE_X(1,24,3),250,2,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<32000){if(!X) break;MAIN_CONTROL(0,-900-CHAY_TU_DONG_THEO_LAZE_X(1,24,3),200,2,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<36000){if((laze_phai>68&&laze_phai<98)||!X) break;MAIN_CONTROL(0,-900-CHAY_TU_DONG_THEO_LAZE_X(1,24,3),150,2,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<39000){if((laze_phai>44&&laze_phai<62)||!X) break;MAIN_CONTROL(0,-900-CHAY_TU_DONG_THEO_LAZE_X(1,24,3),100,2,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<40000){if((laze_phai>36&&laze_phai<38)||!X) break;MAIN_CONTROL(0,-900-CHAY_TU_DONG_THEO_LAZE_X(1,24,3),50,2,0);vTaskDelay(1);}
		while(laze_phai>36&&laze_phai<100){if(!X) break;MAIN_CONTROL(0,-900-CHAY_TU_DONG_THEO_LAZE_X(1,24,3),20,2,0);vTaskDelay(1);}
		while(laze_sau!=24){
		while(laze_sau<24) {if(!X) break;MAIN_CONTROL(0,0,15,0.2,0);}
		while(laze_sau>24) {if(!X) break;MAIN_CONTROL(0,1800,15,0.2,0);}	
		if(!X) break;}
//		e2 41600 E1 7900 laze_trai 64 laze_sau 24
		while(_stop||!X){if(!O) break;vTaskDelay(1);}
		Robot_Stop_Now(5);vTaskDelay(100);//(laze_phai>4&&laze_phai<12) 
		RESET_ENCODER(3);
		RESET_ENCODER(2);
		vTaskDelay(1);
}
void dat_tryball_1_do()//vi tri 3
{
		Robot_Stop_Now(0);
		MAIN_CONTROL(0,490,50,1,0); while(abs(READ_ENCODER(2))<500)  {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,490,100,1,0);while(abs(READ_ENCODER(2))<1000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,490,150,1,0);while(abs(READ_ENCODER(2))<2000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,490,200,1,0);while(abs(READ_ENCODER(2))<3000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,490,250,1,0);while(abs(READ_ENCODER(2))<5000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,490,250,1,0);while(abs(READ_ENCODER(2))<15000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,490,200,1,0);while(abs(READ_ENCODER(2))<23000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,490,150,2,0);while(abs(READ_ENCODER(2))<30000) {if((laze_sau>5&&laze_sau<40)||(laze_phai>150&&laze_phai<170)||!X) break;	vTaskDelay(1);}
		xilanh_tryball_1;xilanh_tay_dat_1;
		MAIN_CONTROL(0,240,150,2,0);while(abs(READ_ENCODER(2))<35000) {if(!X) break;	vTaskDelay(1);}
		_bien_cho_dat_tryball=1;
		MAIN_CONTROL(0,240,150,2,0);while(abs(READ_ENCODER(2))<38000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,240,100,2,0);while(abs(READ_ENCODER(2))<42000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,240,50,2,0);while(abs(READ_ENCODER(2))<43000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,240-CHAY_TU_DONG_THEO_LAZE_Y(-1,270,10),50,2,0); while(abs(READ_ENCODER(2))<45500) {if((!cb_trai||!cb_phai)||!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,240-CHAY_TU_DONG_THEO_LAZE_Y(-1,270,10),20,2,0); while(abs(READ_ENCODER(2))<47000) {if((!cb_quang_trai||!cb_quang_phai)||!X) break;	vTaskDelay(1);}
		dovitri_do();
		while(_stop||!X){if(!O) break;vTaskDelay(1);}
		if(X) _bien_dat_tryball=1;
		MAIN_CONTROL(0,0,30,1,0);vTaskDelay(500);
		Robot_Stop_Now(5);vTaskDelay(100);
		RESET_ENCODER(3);
		RESET_ENCODER(2);
		RESET_IMU();
		vTaskDelay(1);
}
void tryball_2_do()
{
		Robot_Stop_Now(0);
		MAIN_CONTROL(0,-1390,50,4,0); while(abs(READ_ENCODER(2))<300)  {if(!X) break;vTaskDelay(1);}
		MAIN_CONTROL(0,-1390,100,4,0);while(abs(READ_ENCODER(2))<700) 	{if(!X) break;vTaskDelay(1);}
		MAIN_CONTROL(0,-1390,150,4,0);while(abs(READ_ENCODER(2))<1300) {if(!X) break;vTaskDelay(1);}
		MAIN_CONTROL(0,-1390,200,4,0);while(abs(READ_ENCODER(2))<2300) {if(!X) break;vTaskDelay(1);}
		xilanh_tay_dat_0;
		MAIN_CONTROL(0,-1390,250,4,0);while(abs(READ_ENCODER(2))<3500) {if(!X) break;vTaskDelay(1);}
		MAIN_CONTROL(0,-1390,250,4,0);while(abs(READ_ENCODER(2))<17000){if(!X) break;vTaskDelay(1);}
		MAIN_CONTROL(0,-1390,250,4,0);while(abs(READ_ENCODER(2))<27000){if(!X) break;vTaskDelay(1);}
		MAIN_CONTROL(0,-1390,200,4,0);while(abs(READ_ENCODER(2))<34000){if(!X) break;vTaskDelay(1);}
		MAIN_CONTROL(0,-1390,150,4,0);while(abs(READ_ENCODER(2))<39000){if(!X) break;vTaskDelay(1);}
		while(laze_sau>40&&laze_sau<150){if(!X) break;MAIN_CONTROL(0,-1390,100,4,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<22000){if((laze_phai>35&&laze_phai<39)||!X) break;MAIN_CONTROL(0,-900-CHAY_TU_DONG_THEO_LAZE_X(-1,28,2),100,10,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<23000){if((laze_phai>25&&laze_phai<29)||!X) break;MAIN_CONTROL(0,-900-CHAY_TU_DONG_THEO_LAZE_X(-1,28,2),50,10,0);vTaskDelay(1);}
		while(laze_phai>22&&laze_phai<50){if(!X) break;MAIN_CONTROL(0,-900-CHAY_TU_DONG_THEO_LAZE_X(-1,28,2),20,10,0);vTaskDelay(1);}
		while(laze_phai!=21){
		while(laze_phai<21) {if(!X) break;MAIN_CONTROL(0,900,20,1,0);}
		while(laze_phai>21) {if(!X) break;MAIN_CONTROL(0,-900,20,1,0);}
		if(!X) break;}
		while(laze_sau!=24){
		while(laze_sau<24) {if(!X) break;MAIN_CONTROL(0,0,20,1,0);}
		while(laze_sau>24) {if(!X) break;MAIN_CONTROL(0,1800,20,1,0);}
		if(!X) break;}
		Robot_Stop_Now(5);vTaskDelay(100);
		RESET_ENCODER(3);
		RESET_ENCODER(2);
		vTaskDelay(1);
}
void dat_tryball_2_do() //vi tri 2
{
		Robot_Stop_Now(0);
		MAIN_CONTROL(0,530,50,1,0); while(abs(READ_ENCODER(2))<500)  {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,530,100,1,0);while(abs(READ_ENCODER(2))<1000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,530,150,1,0);while(abs(READ_ENCODER(2))<2000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,530,200,1,0);while(abs(READ_ENCODER(2))<3000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,530,250,1,0);while(abs(READ_ENCODER(2))<5000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,530,200,1,0);while(abs(READ_ENCODER(2))<15000) {if((laze_sau>90&&laze_sau<100)||!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,-20,200,1,0);while(abs(READ_ENCODER(2))<23000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,-20,200,2,0);while(abs(READ_ENCODER(2))<30000) {if(!X) break;	vTaskDelay(1);}
		xilanh_tryball_1;xilanh_tay_dat_1;
		MAIN_CONTROL(0,-20,150,2,0);while(abs(READ_ENCODER(2))<35000) {if(!X) break;	vTaskDelay(1);}
		_bien_cho_dat_tryball=1;
		MAIN_CONTROL(0,-20,150,2,0);while(abs(READ_ENCODER(2))<38000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,-20,100,2,0);while(abs(READ_ENCODER(2))<42000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,-20,50,2,0); while(abs(READ_ENCODER(2))<45000) {if((!cb_trai||!cb_phai)||!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,-20,20,2,0); while(abs(READ_ENCODER(2))<47000) {if((!cb_quang_trai||!cb_quang_phai)||!X) break;	vTaskDelay(1);}
		dovitri_do();
		while(_stop||!X){if(!O) break;vTaskDelay(1);}
		if(X) _bien_dat_tryball=1;
		MAIN_CONTROL(0,0,30,4,0);vTaskDelay(500);
		Robot_Stop_Now(5);vTaskDelay(100);
		RESET_ENCODER(2);
		RESET_ENCODER(3);
		RESET_IMU();
		vTaskDelay(1);
}
void tryball_3_do()
{
		Robot_Stop_Now(0);
		while(abs(READ_ENCODER(2))<500)  {if(!X) break;MAIN_CONTROL(0,-1550,50,1,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<1000)  {if(!X) break;MAIN_CONTROL(0,-1550,100,1,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<3000) {if(!X) break;MAIN_CONTROL(0,-1550,150,1,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<7000) {if(!X) break;MAIN_CONTROL(0,-1550,200,1,0);vTaskDelay(1);}
//		while(abs(READ_ENCODER(2))<7000) {if(!X) break;MAIN_CONTROL(0,-1600,250,1,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<15000) {if(!X) break;MAIN_CONTROL(0,-1550,250,1,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<20000){if((laze_phai>125&&laze_phai<200)||!X) break;MAIN_CONTROL(0,-1550,250,2,0);vTaskDelay(1);}
		xilanh_tay_dat_0;
		while(abs(READ_ENCODER(2))<30000){MAIN_CONTROL(0,1800-CHAY_TU_DONG_THEO_LAZE_Y_P(-1,123,7),200,2,0);if(!X) break;vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<36000){if(!X) break;MAIN_CONTROL(0,1800-CHAY_TU_DONG_THEO_LAZE_Y_P(-1,123,7),150,2,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<41000){if((laze_sau>50&&laze_sau<67)||!X) break;MAIN_CONTROL(0,1800-CHAY_TU_DONG_THEO_LAZE_Y_P(-1,123,7),150,2,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<46000){if((laze_sau>20&&laze_sau<30)||!X) break;MAIN_CONTROL(0,1800-CHAY_TU_DONG_THEO_LAZE_Y_P(-1,123,7),100,2,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<49000){if((laze_sau>12&&laze_sau<15)||!X) break;MAIN_CONTROL(0,1800-CHAY_TU_DONG_THEO_LAZE_Y_P(-1,123,7),50,2,0);vTaskDelay(1);}
		while(laze_sau>10&&laze_sau<100){if((laze_sau>3&&laze_sau<8)||!X) break;MAIN_CONTROL(0,1800-CHAY_TU_DONG_THEO_LAZE_Y_P(-1,123,7),20,2,0);vTaskDelay(1);}
		while(_stop||!X){if(!O) break;vTaskDelay(1);}
		Robot_Stop_Now(5);vTaskDelay(100);
		RESET_ENCODER(3);
		RESET_ENCODER(2);
		vTaskDelay(1);
}
void dat_tryball_3_do() //vi tri 1
{
		Robot_Stop_Now(0);
		while(abs(READ_ENCODER(2))<500)  {if(!X) break;MAIN_CONTROL(0,50-CHAY_TU_DONG_THEO_LAZE_Y_P(1,137,4),50,1,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<2000) {if(!X) break;MAIN_CONTROL(0,50-CHAY_TU_DONG_THEO_LAZE_Y_P(1,137,4),100,1,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<6000) {if(!X) break;MAIN_CONTROL(0,50-CHAY_TU_DONG_THEO_LAZE_Y_P(1,137,4),150,1,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<12000){if(!X) break;MAIN_CONTROL(0,50-CHAY_TU_DONG_THEO_LAZE_Y_P(1,137,4),200,1,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<21000){if(!X) break;MAIN_CONTROL(0,50-CHAY_TU_DONG_THEO_LAZE_Y_P(1,137,4),250,1,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<22000){if(!X) break;MAIN_CONTROL(0,50-CHAY_TU_DONG_THEO_LAZE_Y_P(1,137,4),250,1,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<23000){if(!X) break;MAIN_CONTROL(0,-220,250,1,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<30000){if(!X) break;MAIN_CONTROL(0,-250,200,2,0);vTaskDelay(1);}
		xilanh_tryball_1;xilanh_tay_dat_1;
		while(abs(READ_ENCODER(2))<35000){if(!X) break;MAIN_CONTROL(0,-250,150,2,0);vTaskDelay(1);}
		_bien_cho_dat_tryball=1;
		MAIN_CONTROL(0,-250,150,2,0);while(abs(READ_ENCODER(2))<38000) {if(!X) break;	vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<46000){if(!X) break;MAIN_CONTROL(0,-300,100,2,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<49000){if((!cb_trai||!cb_phai)||!X) break;MAIN_CONTROL(0,-300,50,2,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<50000){if((!cb_quang_trai||!cb_quang_phai)||!X) break;MAIN_CONTROL(0,-300,20,2,0);vTaskDelay(1);}
		dovitri_do();
		while(_stop||!X){if(!O) break;vTaskDelay(1);}
		if(X) _bien_dat_tryball=1;
		MAIN_CONTROL(0,0,30,4,0);vTaskDelay(500);
		Robot_Stop_Now(5);vTaskDelay(100);
		RESET_ENCODER(3);
		RESET_ENCODER(2);
		RESET_IMU();
		vTaskDelay(1);
}
void tryball_4_do()//vi tri 1
{
		Robot_Stop_Now(0);
		while(abs(READ_ENCODER(2))<500)  {if(!X) break;MAIN_CONTROL(0,1400,50,1,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<2000)  {if(!X) break;MAIN_CONTROL(0,1400,100,1,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<7000) {if(!X) break;MAIN_CONTROL(0,1400,150,1,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<15000) {if(!X) break;MAIN_CONTROL(0,-1550,200,1,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<20000) {if(!X) break;MAIN_CONTROL(0,-1550,250,1,0);vTaskDelay(1);}
//		while(abs(READ_ENCODER(2))<19000) {if(!X) break;MAIN_CONTROL(0,-1600,300,1,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<30000){if((laze_phai>115&&laze_phai<130)||!X) break;MAIN_CONTROL(0,-1650,200,2,0);vTaskDelay(1);}
		xilanh_tay_dat_0;
		while(abs(READ_ENCODER(2))<36000){if(!X) break;MAIN_CONTROL(0,1800-CHAY_TU_DONG_THEO_LAZE_Y_P(-1,123,7),150,2,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<41000){if((laze_sau>50&&laze_sau<67)||!X) break;MAIN_CONTROL(0,1800-CHAY_TU_DONG_THEO_LAZE_Y_P(-1,123,7),150,2,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<46000){if((laze_sau>20&&laze_sau<30)||!X) break;MAIN_CONTROL(0,1800-CHAY_TU_DONG_THEO_LAZE_Y_P(-1,123,7),100,2,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<49000){if((laze_sau>12&&laze_sau<15)||!X) break;MAIN_CONTROL(0,1800-CHAY_TU_DONG_THEO_LAZE_Y_P(-1,123,7),50,2,0);vTaskDelay(1);}
		while(laze_sau>10&&laze_sau<100){if(!X) break;MAIN_CONTROL(0,1800-CHAY_TU_DONG_THEO_LAZE_Y_P(-1,123,7),20,2,0);vTaskDelay(1);}
		while(_stop||!X){if(!O) break;vTaskDelay(1);}
		Robot_Stop_Now(5);vTaskDelay(100);
		RESET_ENCODER(3);
		RESET_ENCODER(2);
		vTaskDelay(1);
}
void dat_tryball_4_do()//vi tri 5
{
		Robot_Stop_Now(0);
		MAIN_CONTROL(0,530,50,1,0); while(abs(READ_ENCODER(2))<500)  {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,530,100,1,0);while(abs(READ_ENCODER(2))<1000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,530,150,1,0);while(abs(READ_ENCODER(2))<2000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,530,200,2,0);while(abs(READ_ENCODER(2))<1000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,530,200,2,0);while(abs(READ_ENCODER(2))<5000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,530,250,2,0);while(abs(READ_ENCODER(2))<17000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,50,300,4,0);while(abs(READ_ENCODER(2))<24000) {if((laze_sau>108&&laze_sau<140)||!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,50,250,4,0);while(abs(READ_ENCODER(2))<27000) {if(!X) break;	vTaskDelay(1);}//(laze_sau>130&&laze_sau<150)||
		MAIN_CONTROL(0,300,200,4,0);while(abs(READ_ENCODER(2))<33000) {if(!X) break;	vTaskDelay(1);}
		xilanh_tryball_1;xilanh_tay_dat_1;
		MAIN_CONTROL(0,300,150,4,0);while(abs(READ_ENCODER(2))<36000) {if(!X) break;	vTaskDelay(1);}
		_bien_cho_dat_tryball=1;
		MAIN_CONTROL(0,300,150,4,0);while(abs(READ_ENCODER(2))<43000) {if(!X) break;	vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<46000) {if(!X) break;MAIN_CONTROL(0,300-CHAY_TU_DONG_THEO_LAZE_Y(1,90,1),100,4,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<48000) {if((!cb_trai||!cb_phai)||!X) break;MAIN_CONTROL(0,300-CHAY_TU_DONG_THEO_LAZE_Y(1,90,1),50,4,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(2))<50000) {if((!cb_quang_trai||!cb_quang_phai)||!X) break;MAIN_CONTROL(0,300-CHAY_TU_DONG_THEO_LAZE_Y(1,90,1),20,4,0);vTaskDelay(1);}
		dovitri_do();
		while(_stop||!X){if(!O) break;vTaskDelay(1);}
		if(X) _bien_dat_tryball=1;
		MAIN_CONTROL(0,0,20,4,0);vTaskDelay(500);
		Robot_Stop_Now(5);vTaskDelay(100);
		RESET_ENCODER(3);
		RESET_ENCODER(2);
		RESET_IMU();
		vTaskDelay(1);
}
void tryball_5_do()//vi tri 5
{
		Robot_Stop_Now(0);
		MAIN_CONTROL(0,-1400,50,1,0); while(abs(READ_ENCODER(2))<500)  {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,-1400,100,1,0);while(abs(READ_ENCODER(2))<1000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,-1400,150,1,0);while(abs(READ_ENCODER(2))<2000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,-1400,200,1,0);while(abs(READ_ENCODER(2))<3000) {if(!X) break;	vTaskDelay(1);}
		xilanh_tay_dat_0;
		MAIN_CONTROL(0,-1400,250,1,0);while(abs(READ_ENCODER(2))<5000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,-1400,270,1,0);while(abs(READ_ENCODER(2))<17000){if(!X) break;vTaskDelay(1);}
		MAIN_CONTROL(0,-1400,250,2,0);while(abs(READ_ENCODER(2))<27000){if(!X) break;vTaskDelay(1);}
		MAIN_CONTROL(0,-1400,200,2,0);while(abs(READ_ENCODER(2))<33000){if(!X) break;vTaskDelay(1);}
		MAIN_CONTROL(0,-1400,150,2,0);while(abs(READ_ENCODER(2))<40000){if(!X) break;vTaskDelay(1);}
		while(laze_sau>20&&laze_sau<100){if(!X) break;MAIN_CONTROL(0,-1400,100,2,0);vTaskDelay(1);}
//		while(abs(READ_ENCODER(3))<22000){if((laze_phai>140&&laze_phai<150)||!X) break;MAIN_CONTROL(0,-900-CHAY_TU_DONG_THEO_LAZE_X(-1,12,4),150,10,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<22000){if((laze_phai>132&&laze_phai<148)||!X) break;MAIN_CONTROL(0,-900-CHAY_TU_DONG_THEO_LAZE_X(1,9,3),100,10,0);vTaskDelay(1);}
		while(abs(READ_ENCODER(3))<24000){if((laze_phai>124&&laze_phai<132)||!X) break;MAIN_CONTROL(0,-900-CHAY_TU_DONG_THEO_LAZE_X(1,9,3),50,10,0);vTaskDelay(1);}
		while(laze_phai>124&&laze_phai<300){if(!X) break;MAIN_CONTROL(0,-900-CHAY_TU_DONG_THEO_LAZE_X(1,9,3),20,10,0);vTaskDelay(1);}
		while(laze_sau!=9){
		while(laze_sau<9) {if(!X) break;MAIN_CONTROL(0,0,15,0.2,0);}
		while(laze_sau>9) {if(!X) break;MAIN_CONTROL(0,1800,15,0.2,0);}	
		if(!X) break;}
		while(laze_phai!=123){
		while(laze_phai<123) {if(!X) break;MAIN_CONTROL(0,900,15,0.2,0);}
		while(laze_phai>123) {if(!X) break;MAIN_CONTROL(0,-900,15,0.2,0);}	
		if(!X) break;}
		while(_stop||!X){if(!O) break;vTaskDelay(1);}
		Robot_Stop_Now(5);vTaskDelay(100);
		RESET_ENCODER(3);
		RESET_ENCODER(2);
		vTaskDelay(1);
}
void dat_tryball_5_do() //vi tri 5
{
		Robot_Stop_Now(0);
		MAIN_CONTROL(0,540,50,1,0); while(abs(READ_ENCODER(2))<500)  {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,540,100,1,0);while(abs(READ_ENCODER(2))<1000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,540,150,1,0);while(abs(READ_ENCODER(2))<2000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,540,200,2,0);while(abs(READ_ENCODER(2))<1000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,540,200,2,0);while(abs(READ_ENCODER(2))<5000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,540,250,2,0);while(abs(READ_ENCODER(2))<17000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,-300,250,4,0);while(abs(READ_ENCODER(2))<24000) {if((laze_sau>112&&laze_sau<140)||!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,-300,250,4,0);while(abs(READ_ENCODER(2))<27000) {if(!X) break;	vTaskDelay(1);}//(laze_sau>130&&laze_sau<150)||
		MAIN_CONTROL(0,-90,200,4,0);while(abs(READ_ENCODER(2))<33000) {if(!X) break;	vTaskDelay(1);}
		xilanh_tryball_1;xilanh_tay_dat_1;
		MAIN_CONTROL(0,-90,150,4,0);while(abs(READ_ENCODER(2))<41000) {if(!X) break;	vTaskDelay(1);}
		_bien_cho_dat_tryball=1;
		MAIN_CONTROL(0,-90,100,4,0);while(abs(READ_ENCODER(2))<46000) {if(!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,-90,50,4,0); while(abs(READ_ENCODER(2))<48000) {if((!cb_trai||!cb_phai)||!X) break;	vTaskDelay(1);}
		MAIN_CONTROL(0,-90,20,4,0); while(abs(READ_ENCODER(2))<50000) {if((!cb_quang_trai||!cb_quang_phai)||!X) break;	vTaskDelay(1);}
		dovitri_do();
		while(TAM_GIAC)vTaskDelay(1);	
		if(X) _bien_dat_tryball=1;
		MAIN_CONTROL(0,0,20,4,0);vTaskDelay(500);
		Robot_Stop_Now(5);vTaskDelay(100);
		RESET_ENCODER(3);
		RESET_ENCODER(2);
		RESET_IMU();
		vTaskDelay(1);
}