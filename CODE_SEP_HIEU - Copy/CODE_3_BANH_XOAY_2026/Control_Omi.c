#include <stdlib.h>
#include <math.h>



float GIA_TOC,TOC_DO=2,CHAY_VA_XOAY,HUONG,MAT_ROBOT; 
float luong_giac_trai_truoc,luong_giac_phai_truoc,luong_giac_trai_sau,luong_giac_phai_sau;
const  float radian= 3.141592653589793238462643/180;
vs32 chuyen_che_do;
int TOC_DO_XOAY,BIT_XOAY,GOC_LECH;
int MOTOR_LOCK,CHAY_GIA_TOC=0,Tam_Xoay=0; 
int trai_truoc,phai_truoc,trai_sau,phai_sau,TOC_DO_DAT,ROBOT_STOP;
void RUN_XOAY_TRON(vs32 _toc_do,float _gia_toc);
float trai_truoc_1,phai_truoc_1,trai_sau_1,phai_sau_1;
float trai_float,phai_float,sau_float;   //gia_toc_dieu_xung=0.07;
//////////////////////xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx//////////////////////////

	
void MAIN_CONTROL(vs32 _mat_robot,vs32 _huong,vs32 _toc_do_chay,float _gia_toc,float _chay_va_xoay)		
		{		
			
			  chuyen_che_do=0;
				if(abs(_huong)==40000){HUONG =	_huong;RUN_XOAY_TRON(_toc_do_chay,_gia_toc);}
		
				else{
						BIT_XOAY		=	0;
						HUONG				=	_huong;
						GIA_TOC			=	_gia_toc;
						ROBOT_STOP	=	0;
						MOTOR_LOCK	=	30000;	
						CHAY_GIA_TOC=	10;
						TOC_DO_DAT 	= _toc_do_chay;		
						MAT_ROBOT	 	= _mat_robot;	
						CHAY_VA_XOAY=	_chay_va_xoay;			
						if(TOC_DO==0)TOC_DO=	4;
						

					
						luong_giac_trai_truoc=(float)(sin(((450 	-HUONG)/10)*radian));
						luong_giac_phai_truoc=(float)(sin(((-450 	-HUONG)/10)*radian));
						luong_giac_trai_sau=(float)(sin(((1350 		-HUONG)/10)*radian));
						luong_giac_phai_sau=(float)(sin(((-1350 	-HUONG)/10)*radian));
					
					}
}	
		
////xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx	
void robotResetIMU(void)
{
	RESET_IMU();
}
////xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx	
void RUN_XOAY()
	{					
						MAT_ROBOT	=	MAT_ROBOT	-	CHAY_VA_XOAY;
						HUONG			=	HUONG	+	CHAY_VA_XOAY;	
						luong_giac_trai_truoc=(float)(sin(((450 	-HUONG)/10)*radian));
						luong_giac_phai_truoc=(float)(sin(((-450 	-HUONG)/10)*radian));
						luong_giac_trai_sau=(float)(sin(((1350 		-HUONG)/10)*radian));
						luong_giac_phai_sau=(float)(sin(((-1350 	-HUONG)/10)*radian));

	}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx	
void STOP_ROBOT(void)		
{						
						TOC_DO_DAT 	= 0;	
						TOC_DO_XOAY	=	0;
						BIT_XOAY		=	0;
					//	CHAY_GIA_TOC=	0;
						TOC_DO			=	0;
}		
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx	
void RUN_XOAY_TRON(vs32 _toc_do,float _gia_toc)		
		{				BIT_XOAY		=	10;
						GIA_TOC			=	_gia_toc;	
							if(_toc_do>254)TOC_DO_DAT=254;
						  else TOC_DO_DAT 	= _toc_do;	
						
						CHAY_VA_XOAY=	0;
						//TOC_DO			=	2;
			                   
			            
						if(HUONG>0){chieu_trai_truoc_lui;chieu_phai_truoc_toi;chieu_trai_sau_lui;chieu_phai_sau_toi;}
						else if(HUONG<0){chieu_trai_truoc_toi;chieu_phai_truoc_lui;chieu_trai_sau_toi;chieu_phai_sau_lui;}
}	                 //       
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx	
void TINH_GOC_LECH()		
{				
						
							GOC_LECH=(IMU-MAT_ROBOT)/2; // do dap ung
	
						trai_truoc 	=	(int)(luong_giac_trai_truoc	*TOC_DO  + GOC_LECH);
						phai_truoc 	=	(int)(luong_giac_phai_truoc	*TOC_DO  + GOC_LECH);	
						trai_sau  	=	(int)(luong_giac_trai_sau		*TOC_DO  + GOC_LECH);	
						phai_sau  	=	(int)(luong_giac_phai_sau		*TOC_DO  + GOC_LECH);
	
							if(trai_truoc<0){ chieu_trai_truoc_lui;}
							else {chieu_trai_truoc_toi;} 
							
							if(phai_truoc<0){ chieu_phai_truoc_toi;}
							else {chieu_phai_truoc_lui;} 

							if(trai_sau>0){ chieu_trai_sau_toi;}
							else {chieu_trai_sau_lui;} 
							
							if(phai_sau>0){ chieu_phai_sau_lui;}
							else {chieu_phai_sau_toi;} 		

							

								
							if ( abs(trai_truoc) < 3)trai_truoc_1=2;
							else if(abs(trai_truoc)>254)trai_truoc_1=254;
							else trai_truoc_1=abs(trai_truoc);									
							
							if ( abs(phai_truoc) < 3)phai_truoc_1=2;
							else if(abs(phai_truoc)>254)phai_truoc_1=254;
							else phai_truoc_1=abs(phai_truoc);	
						
							if ( abs(trai_sau) < 3)trai_sau_1=2;
							else if(abs(trai_sau)>254)trai_sau_1=254;
							else trai_sau_1=abs(trai_sau);									
							
							if ( abs(phai_sau) < 3)phai_sau_1=2;
							else if(abs(phai_sau)>254)phai_sau_1=254;
							else phai_sau_1=abs(phai_sau);			
//////////////////////////////////////HÀM GIA TÔC//////////////////					
}
///////////////////////////////////////////////////
void RUN_OMI(){

/////////////////
	
	
						if(TOC_DO>TOC_DO_DAT){
									TOC_DO=TOC_DO-GIA_TOC;
									if(TOC_DO<TOC_DO_DAT)TOC_DO=TOC_DO_DAT; 				
								}
						else if(TOC_DO<TOC_DO_DAT){														
									TOC_DO=TOC_DO+GIA_TOC;
									if(TOC_DO>TOC_DO_DAT)TOC_DO=TOC_DO_DAT; 
								}

						else {
									if(TOC_DO<=3)STOP_ROBOT();
									else {TOC_DO=TOC_DO_DAT;}				
								}		

	


////////////////
	
	
	if(BIT_XOAY==10)
		{
			
											if(TOC_DO>abs(TOC_DO_DAT))
												  {
														TOC_DO=TOC_DO-GIA_TOC;
														if(TOC_DO<abs(TOC_DO_DAT))TOC_DO=abs(TOC_DO_DAT); 				
													}
											else if(TOC_DO<abs(TOC_DO_DAT))
												  {														
														TOC_DO=(float)TOC_DO+GIA_TOC;
														if(TOC_DO>abs(TOC_DO_DAT))TOC_DO=abs(TOC_DO_DAT); 
													}
											else 
												  {
														if(TOC_DO<=3)STOP_ROBOT();
														else{TOC_DO=TOC_DO_DAT;}
													}
							MOTOR_LOCK=0;trai_truoc_1=phai_truoc_1=trai_sau_1=phai_sau_1=TOC_DO;
				}	
		
////////////////////////////////////////////////////		
				
		else{
				if(TOC_DO_DAT>2&&CHAY_GIA_TOC==10)
					{ 
						MOTOR_LOCK=0;
						if(CHAY_VA_XOAY!=0){RUN_XOAY();} 
						TINH_GOC_LECH();	
					}
			  else
						{	
							if(MOTOR_LOCK<=0){MOTOR_LOCK=0;TOC_DO=2;trai_truoc_1=phai_truoc_1=trai_sau_1=phai_sau_1=0;	STOP_ROBOT();}
							else{																					
								if(TOC_DO<=2)
									{
									  banh_trai_truoc=banh_phai_truoc=banh_trai_sau=banh_phai_sau=TOC_DO=2;
										
									  trai_truoc=phai_truoc=trai_sau=phai_sau=0;
									  trai_truoc_1=phai_truoc_1=trai_sau_1=phai_sau_1=2;
									 // trai_float=phai_float=sau_float=0;
									  MOTOR_LOCK--;
									
								  }
								else {

									if (HUONG==40000){
										TOC_DO=TOC_DO-GIA_TOC;
										trai_truoc_1=phai_truoc_1=trai_sau_1=phai_sau_1=TOC_DO;
									}
									else {TINH_GOC_LECH();}	
													
								}
							
							}		
					}			
				}
		

	if(Tam_Xoay==0)
	{
			banh_trai_truoc=trai_truoc_1;
			banh_phai_truoc=phai_truoc_1;
			banh_trai_sau=trai_sau_1;
			banh_phai_sau=phai_sau_1;
	}
	else if(Tam_Xoay==1)
		 {
			banh_trai_truoc=2;
			banh_phai_truoc=phai_truoc_1;
			banh_trai_sau=trai_sau_1;
			banh_phai_sau=phai_sau_1;
		}	
	 else if(Tam_Xoay==2){
			banh_trai_truoc=trai_truoc_1;
			banh_phai_truoc=2;
			banh_trai_sau=trai_sau_1;
			banh_phai_sau=phai_sau_1;
		}		 
	 	 else if(Tam_Xoay==3){
			banh_trai_truoc=trai_truoc_1;
			banh_phai_truoc=phai_truoc_1;
			banh_trai_sau=2;
			banh_phai_sau=phai_sau_1;
		}	
		else if(Tam_Xoay==4){
			banh_trai_truoc=trai_truoc_1;
			banh_phai_truoc=phai_truoc_1;
			banh_trai_sau=trai_sau_1;
			banh_phai_sau=2;
		}	
		else{
			banh_trai_truoc=trai_truoc_1=2;
			banh_phai_truoc=phai_truoc_1=2;
			banh_trai_sau=trai_sau_1=2;
			banh_phai_sau=phai_sau_1=2;	
			TOC_DO=TOC_DO_DAT=2;
			TOC_DO_DAT 	= 0;	
			TOC_DO_XOAY	=	0;
			BIT_XOAY		=	0;			
			TOC_DO			=	0;
		}			 

				
}	


///////////////////////////////////////////
void Robot_Stop_Now(vs32 _Tam_Xoay)
{
	Tam_Xoay=_Tam_Xoay;		 
	
}

