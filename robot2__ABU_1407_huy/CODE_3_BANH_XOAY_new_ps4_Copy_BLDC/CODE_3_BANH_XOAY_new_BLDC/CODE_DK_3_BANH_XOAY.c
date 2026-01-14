#include <stdlib.h>
#include <math.h>



/////////3 banh///////////////
extern float CHAY_VA_XOAY,GIA_TOC,TOC_DO,HUONG,MAT_ROBOT; 
float luong_giac_trai,luong_giac_phai,luong_giac_sau,XOAY;
const  float radian= 3.141592653589793238462643/180;
vs32 GOC_XOAY_TRON,_TOC_DO_BT,_TOC_DO_BP,_TOC_DO_BS,goc_banh_trai,goc_banh_phai,goc_banh_sau,_huong,GIA_TOC_XOAY_MAT=1,GIA_TOC_XOAY_HUONG=1;
int TOC_DO_XOAY,BIT_XOAY,GOC_LECH;
int MOTOR_LOCK,CHAY_GIA_TOC=0,Tam_Xoay=0; 
int ROBOT_STOP,_toc_do_chay,bit_dao_chieu_dong_co=1;
extern vu8 DATA_SPEED[60];
extern vs32 goc_banh_trai,goc_banh_phai,goc_banh_sau,chieu_trai,chieu_phai,chieu_sau,goc_banh_trai_cu,goc_banh_phai_cu,goc_banh_sau_cu;
extern vs32 _TOC_DO_BT,_TOC_DO_BP,_TOC_DO_BS;
extern vs32 _GOC_TRAI_CX,_GOC_PHAI_CX,_GOC_SAU_CX,_GOC_LECH_ROBO,TOC_DO_DAT;
extern vs16 IMU,HUONG_LG;

extern vs32 Dc_Trai_Xoay_Trai =1500, Dc_Phai_Xoay_Trai =300, Dc_Sau_Xoay_Trai =-900; //ham cua IMU>0     
extern vs32 Dc_Trai_Xoay_Phai =-300	, Dc_Phai_Xoay_Phai =-1500, Dc_Sau_Xoay_Phai =900; //ham cua IMU<0

vs32 bit_dao_chieu_trai=0,bit_dao_chieu_phai=0,bit_dao_chieu_sau=0,HUONG_BAN_DAU,IMU_BAN_DAU;
vs32 goc_trai_hien_tai,goc_phai_hien_tai,goc_sau_hien_tai;
 vs16 _MOTOR_LOCK,kt;

//////////////////////xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx//////////////////////////
///

void MAIN_CONTROL(vs32 _mat_robot,vs32 _huong_chay,vs32 _toc_do,float _gia_toc,float _chay_va_xoay)
{

            HUONG		      =  _huong_chay;
            HUONG_BAN_DAU  =  _huong_chay;
						GIA_TOC	      =	_gia_toc;
						//MOTOR_LOCK	   =	0;	
						TOC_DO_DAT 	   =  _toc_do;		
						MAT_ROBOT	   =  _mat_robot;	
						CHAY_VA_XOAY   =  _chay_va_xoay;						
					//	CHAY_VA_XOAY   =  0;
            XOAY           =  0;
            IMU_BAN_DAU    =  IMU;
	// moi them de xoay mat không delay do pid				
	kt   =  _chay_va_xoay;
					if (kt>10){_MOTOR_LOCK=10;}
					else _MOTOR_LOCK=2000;
					
 // khoa mat robot = 0 de chay tu dong khi bi pha song	
	if (San_Do && gp_get_mode_uart() == 13) {MAT_ROBOT	= 0;}			
													 
}
void CONTROL_TOC_DO(vs32 _toc_do,float _gia_toc,float _chay_va_xoay)
{
						GIA_TOC	      =	_gia_toc;		
						TOC_DO_DAT 	   =  _toc_do;		
						CHAY_VA_XOAY   =  _chay_va_xoay;							 
}
///////////////////////
////xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx	

/// Dieu khien va tinh toan gia toc 

float apply_s_curve_shaping(float toc_do, float toc_do_dat, float gia_toc) {
    float input_shaped_toc_do = toc_do;
    float delta = toc_do_dat - toc_do;

    float t_norm = fabs(delta) / (toc_do_dat != 0 ? toc_do_dat : 1);    /// tinh chuan hoa sai lech 


    float s_factor = 2 * (1 - exp(-5 * t_norm));  // Sigmoid tao S-Curve /// Tao He so

    if (delta > 0) {
        
        if (fabs(delta) > 20) {
            input_shaped_toc_do = toc_do + gia_toc * 2;  // Tang toc  " tang manh dan "   
        } else {
            input_shaped_toc_do = toc_do + gia_toc * (1 + 0.5 * s_factor);  // Tang toc (cách <20)  "Muot khi gan ket thuc"
        }
        
        if (input_shaped_toc_do > toc_do_dat) {
            input_shaped_toc_do = toc_do_dat;  // "Khong vuot qua toc do mong muon toc do set "
        }
    } else if (delta < 0) {
      
        if (fabs(delta) > 20) {
            input_shaped_toc_do = toc_do - gia_toc * 2;  // giamtoc
        } else {
            input_shaped_toc_do = toc_do - gia_toc * (1 + 0.3 * s_factor);  // Giam toc (cách <20)
        }

        if (input_shaped_toc_do < toc_do_dat) {
            input_shaped_toc_do = toc_do_dat;
        }
    }

    return input_shaped_toc_do;
}
//// -------------HAM XOAY GOC TU TU	 ---------------------------

//float tinh_goc_theo_gia_toc(float goc_muc_tieu, float goc_hien_tai, float GIA_TOC) {
//    float buoc = GIA_TOC*2.8;

//    if (goc_hien_tai < goc_muc_tieu) {
//        goc_hien_tai += buoc;
//        if (goc_hien_tai > goc_muc_tieu) goc_hien_tai = goc_muc_tieu;
//    } else if (goc_hien_tai > goc_muc_tieu) {
//        goc_hien_tai -= buoc;
//        if (goc_hien_tai < goc_muc_tieu) goc_hien_tai = goc_muc_tieu;
//    }

//    return goc_hien_tai;
//}
//------------------------------------------

///XXXXXXXXXXXXXXXXXXXXX
////////////////////////////////
void RUN_XOAY()
	{	//int bien_xoay;				
      XOAY++;
      if(CHAY_VA_XOAY>0) {
         if(XOAY>CHAY_VA_XOAY){
                  MAT_ROBOT	=	  MAT_ROBOT   + TOC_DO/4;
                  HUONG			=	  HUONG_BAN_DAU-IMU+IMU_BAN_DAU-TOC_DO/4;	
                  XOAY=0;
         }
      }
      else if(CHAY_VA_XOAY<0){
         if(XOAY>abs(CHAY_VA_XOAY)){
                        MAT_ROBOT	=	  MAT_ROBOT  -TOC_DO/4;
                        HUONG			=	 HUONG_BAN_DAU+IMU-IMU_BAN_DAU+TOC_DO/4;	
                        XOAY=0;
         }
      }
      else{
         GIA_TOC_XOAY_MAT  =1;
         GIA_TOC_XOAY_HUONG=1;
         
      }
      
    //  IMU-MAT_ROBOT
      
      
	}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx	

///////////////////////////////////////////////////
void RUN_SW(){

/////////////////                  
         if(abs(CHAY_VA_XOAY)>0)RUN_XOAY();
//////////////////////////////   
	
	//xxxxxxxxxxxxxx
	
	 //  S-Curve Profiling
	
		TOC_DO = apply_s_curve_shaping(TOC_DO, TOC_DO_DAT, GIA_TOC);

	
   ////////////////////////////////////////
   
	//xxxxxxxxxxxxxxxxxx
	
//      if(TOC_DO>TOC_DO_DAT){
//                  TOC_DO=TOC_DO-(GIA_TOC+(float)(GIA_TOC*TOC_DO)/100);
//                 if(TOC_DO<TOC_DO_DAT)TOC_DO=TOC_DO_DAT; 				
//               }
//         else if(TOC_DO<TOC_DO_DAT){														
//                  TOC_DO=TOC_DO+(GIA_TOC+(float)(GIA_TOC*TOC_DO)/100);
//                  if(TOC_DO>TOC_DO_DAT)TOC_DO=TOC_DO_DAT; 
//               }
//         else TOC_DO=TOC_DO_DAT;
			 

////////////////////////////////////////////////
///////////////////////////////								
								
//////////tinh goc lech		
              
if (San_Do && gp_get_mode_uart() == 13) 
	{
			if(abs(CHAY_VA_XOAY)>0)
					{
            _GOC_LECH_ROBO   = (IMU-MAT_ROBOT )*5;  //*5
            if  	 (_GOC_LECH_ROBO>1800)_GOC_LECH_ROBO=1800;
            else if(_GOC_LECH_ROBO<-1800)_GOC_LECH_ROBO=-1800;
            
					}

         else
					 {
            _GOC_LECH_ROBO   = (IMU-MAT_ROBOT )*5 ;  
            if(_GOC_LECH_ROBO>3600)_GOC_LECH_ROBO=3600;
            else if(_GOC_LECH_ROBO<-3600)_GOC_LECH_ROBO=-3600;
               
					}

	}
////////
	else {               
			if(abs(CHAY_VA_XOAY)>0)
					{
            _GOC_LECH_ROBO   = (IMU-MAT_ROBOT )*3;  //*5
            if     (_GOC_LECH_ROBO>1800)_GOC_LECH_ROBO=1800;
            else if(_GOC_LECH_ROBO<-1800)_GOC_LECH_ROBO=-1800;
            
					}

         else {
            _GOC_LECH_ROBO   = (IMU-MAT_ROBOT )*3 ;  
            if(_GOC_LECH_ROBO>3600)_GOC_LECH_ROBO=3600;
            else if(_GOC_LECH_ROBO<-3600)_GOC_LECH_ROBO=-3600;
               
						}
			}			 
/////////doi ve goc 0 khi robot xoay 360 do
         
			HUONG_LG=HUONG-(3600*(int)(HUONG/3600) ) ; /// Giu gtri goc tu 0 den 3600  
  
			if(_GOC_LECH_ROBO>0)
				{ ////////bi xoay qua trai
                          
									_GOC_TRAI_CX=	Dc_Trai_Xoay_Phai	-	HUONG_LG;
									_GOC_PHAI_CX=	Dc_Phai_Xoay_Phai	-	HUONG_LG;
									_GOC_SAU_CX =	Dc_Sau_Xoay_Phai	-	HUONG_LG;
            
              
				}
			else if(_GOC_LECH_ROBO<0){
									_GOC_TRAI_CX=	Dc_Trai_Xoay_Trai	-	HUONG_LG;
									_GOC_PHAI_CX=	Dc_Phai_Xoay_Trai	-	HUONG_LG;
									_GOC_SAU_CX=	Dc_Sau_Xoay_Trai	-	HUONG_LG;	
                                      

				}
			else {
		
/////////////////////////////////////////////////// gó£ ech theo huong
                     
								_TOC_DO_BS	=TOC_DO;
								_TOC_DO_BP	=TOC_DO;
								_TOC_DO_BT	=TOC_DO; 
		
				}
				
				
////////////////////////////////
         if(_GOC_TRAI_CX>1800)_GOC_TRAI_CX=(_GOC_TRAI_CX-3600);                          
         else if(_GOC_TRAI_CX<-1800) _GOC_TRAI_CX=(_GOC_TRAI_CX+3600);             

/////////////////////////////////////////
         
         if(_GOC_PHAI_CX>1800)_GOC_PHAI_CX=(_GOC_PHAI_CX-3600);
         else if(_GOC_PHAI_CX<-1800)_GOC_PHAI_CX=(_GOC_PHAI_CX+3600);
      
//////////////////////////////////////// 
         if(_GOC_SAU_CX>1800) _GOC_SAU_CX=(_GOC_SAU_CX-3600);
         else if(_GOC_SAU_CX<-1800)_GOC_SAU_CX=(_GOC_SAU_CX+3600);

//////////////////tinh toan goc xoay 
				
				
				if(abs(_GOC_LECH_ROBO)>1800){ // --- khi xoay tron 
							 
									goc_banh_trai =(HUONG_LG +(_GOC_TRAI_CX/3600.000)*abs(_GOC_LECH_ROBO));        
									goc_banh_phai =(HUONG_LG+ (_GOC_PHAI_CX/3600.000)*abs(_GOC_LECH_ROBO));
									goc_banh_sau  =(HUONG_LG+ (_GOC_SAU_CX /3600.000)*abs(_GOC_LECH_ROBO));	
					
						////////////////////////////////tim goc gan nhat
           if((goc_banh_trai_cu- goc_banh_trai)>2700)goc_banh_trai=3600+goc_banh_trai;
           else if((goc_banh_trai_cu- goc_banh_trai)<-2700)  goc_banh_trai=goc_banh_trai-3600;
            if((goc_banh_trai_cu- goc_banh_trai)>900)goc_banh_trai=1800+goc_banh_trai;
           else if((goc_banh_trai_cu- goc_banh_trai)<-900)  goc_banh_trai=goc_banh_trai-1800;
            
          //////////////////////////////// 
           if((goc_banh_phai_cu- goc_banh_phai)>2700) goc_banh_phai=3600+goc_banh_phai;
           else if((goc_banh_phai_cu- goc_banh_phai)<-2700)  goc_banh_phai=goc_banh_phai-3600;
           if((goc_banh_phai_cu- goc_banh_phai)>900) goc_banh_phai=1800+goc_banh_phai;
           else if((goc_banh_phai_cu- goc_banh_phai)<-900)  goc_banh_phai=goc_banh_phai-1800;
           
					/////////////////////     
           if((goc_banh_sau_cu- goc_banh_sau)>2700)goc_banh_sau=3600+goc_banh_sau;
           else if((goc_banh_sau_cu- goc_banh_sau)<-2700)  goc_banh_sau=goc_banh_sau-3600;
           if((goc_banh_sau_cu- goc_banh_sau)>900)goc_banh_sau=1800+goc_banh_sau;
           else if((goc_banh_sau_cu- goc_banh_sau)<-900)  goc_banh_sau=goc_banh_sau-1800;	 
					 ////////////////////////////////    
						 goc_banh_trai_cu= goc_banh_trai; 
						 goc_banh_phai_cu= goc_banh_phai; 
						 goc_banh_sau_cu= goc_banh_sau; 

							
						 }
						 
				else{	 
							goc_banh_trai =HUONG_LG;     
							goc_banh_phai =HUONG_LG;
							goc_banh_sau  =HUONG_LG; 
							
						//----tim goc gan nhat
							 
           if((goc_banh_trai_cu- goc_banh_trai)>2700)goc_banh_trai=3600+goc_banh_trai;
           else if((goc_banh_trai_cu- goc_banh_trai)<-2700)  goc_banh_trai=goc_banh_trai-3600;
            if((goc_banh_trai_cu- goc_banh_trai)>1350)goc_banh_trai=1800+goc_banh_trai;
           else if((goc_banh_trai_cu- goc_banh_trai)<-1350)  goc_banh_trai=goc_banh_trai-1800;
            
          //////////////////////////////// 
           if((goc_banh_phai_cu- goc_banh_phai)>2700) goc_banh_phai=3600+goc_banh_phai;
           else if((goc_banh_phai_cu- goc_banh_phai)<-2700)  goc_banh_phai=goc_banh_phai-3600;
           if((goc_banh_phai_cu- goc_banh_phai)>1350) goc_banh_phai=1800+goc_banh_phai;
           else if((goc_banh_phai_cu- goc_banh_phai)<-1350)  goc_banh_phai=goc_banh_phai-1800;
           
					/////////////////////     
           if((goc_banh_sau_cu- goc_banh_sau)>2700)goc_banh_sau=3600+goc_banh_sau;
           else if((goc_banh_sau_cu- goc_banh_sau)<-2700)  goc_banh_sau=goc_banh_sau-3600;
           if((goc_banh_sau_cu- goc_banh_sau)>1350)goc_banh_sau=1800+goc_banh_sau;
           else if((goc_banh_sau_cu- goc_banh_sau)<-1350)  goc_banh_sau=goc_banh_sau-1800;
					 
					 //so sánh goc cu
					 goc_banh_trai_cu= goc_banh_trai; 					 
           goc_banh_phai_cu= goc_banh_phai; 					 
           goc_banh_sau_cu= goc_banh_sau; 

						//-cong them goc lech laban
						goc_banh_trai += (_GOC_TRAI_CX/3600.000)*abs(_GOC_LECH_ROBO);        
						goc_banh_phai += (_GOC_PHAI_CX/3600.000)*abs(_GOC_LECH_ROBO);
						goc_banh_sau  += (_GOC_SAU_CX /3600.000)*abs(_GOC_LECH_ROBO);	
						
				}
						
	
//				if (cho_phep_chay == false) {
//			goc_trai_hien_tai = tinh_goc_theo_gia_toc(goc_banh_trai, goc_trai_hien_tai, GIA_TOC);
//			goc_phai_hien_tai = tinh_goc_theo_gia_toc(goc_banh_phai, goc_phai_hien_tai, GIA_TOC);
//			goc_sau_hien_tai  = tinh_goc_theo_gia_toc(goc_banh_sau,  goc_sau_hien_tai,  GIA_TOC);

//			dong_co_xoay_trai(goc_trai_hien_tai);
//			dong_co_xoay_phai(goc_phai_hien_tai);
//			dong_co_xoay_sau(goc_sau_hien_tai);

//				}
////**************************cap nhat góc tu tu--------------------------
//       
//else{
//	
//					 dong_co_xoay_trai(goc_banh_trai);
//           dong_co_xoay_phai(goc_banh_phai);
//           dong_co_xoay_sau(goc_banh_sau);
//}
			
					 dong_co_xoay_trai(goc_banh_trai);
           dong_co_xoay_phai(goc_banh_phai);
           dong_co_xoay_sau(goc_banh_sau);
					 
					 
//////////////////////////////////////// toc do 
            
            if (abs(_GOC_LECH_ROBO)>1800){
               if(_GOC_LECH_ROBO>0){
                  
                  _TOC_DO_BS	=	((cos(((goc_banh_sau    -	Dc_Sau_Xoay_Phai)	/10)*radian))*TOC_DO);
                  _TOC_DO_BP	=	((cos(((goc_banh_phai	-	Dc_Phai_Xoay_Phai)/10)*radian))*TOC_DO);
                  _TOC_DO_BT	=	((cos(((goc_banh_trai	-	Dc_Trai_Xoay_Phai)/10)*radian))*TOC_DO); 
               }
               else   if(_GOC_LECH_ROBO<0){
                  _TOC_DO_BS	=	((cos(((goc_banh_sau    -	Dc_Sau_Xoay_Trai)	/10)*radian))*TOC_DO);
                  _TOC_DO_BP	=	((cos(((goc_banh_phai	-	Dc_Phai_Xoay_Trai)/10)*radian))*TOC_DO);
                  _TOC_DO_BT	=	((cos(((goc_banh_trai	-	Dc_Trai_Xoay_Trai)/10)*radian))*TOC_DO); 

               }
            }
            else{
            _TOC_DO_BS	=	((cos(((goc_banh_sau    -	HUONG_LG)		/10)*radian))*TOC_DO);
            _TOC_DO_BP	=	((cos(((goc_banh_phai	-	HUONG_LG)		/10)*radian))*TOC_DO);
            _TOC_DO_BT	=	((cos(((goc_banh_trai	-	HUONG_LG)		/10)*radian))*TOC_DO);  
							
            }


			
			if (cho_phep_chay == false) {
	
				if (TOC_DO<=1.0){
         if(MOTOR_LOCK<=0)  {MOTOR_LOCK=0;TOC_DO=0;}
         else {MOTOR_LOCK--;TOC_DO=1;_TOC_DO_BS=_TOC_DO_BP=_TOC_DO_BT=1;}
         //else {MOTOR_LOCK--;} 
         if(MOTOR_LOCK<500&&((abs(goc_banh_trai_cu)>1800)||(abs(goc_banh_phai_cu)>1800)||(abs(goc_banh_sau_cu)>1800))){
           goc_banh_trai_cu= goc_banh_trai=0; 
           goc_banh_phai_cu= goc_banh_phai=0; 
           goc_banh_sau_cu= goc_banh_sau=0;            
						}            
					}
					else { MOTOR_LOCK=_MOTOR_LOCK;}
					
						banh_trai(_TOC_DO_BT);
            banh_phai(_TOC_DO_BP);	
            banh_sau (_TOC_DO_BS);	
					 
			}
			
			else {
						
				 		banh_trai(_TOC_DO_BT);
            banh_phai(_TOC_DO_BP);	
            banh_sau (_TOC_DO_BS);
					
				}

////						// Gioi han -254 den 254
////					
//						_TOC_DO_BS = (_TOC_DO_BS > 700) ? 700 : (_TOC_DO_BS < -700 ? -700 : _TOC_DO_BS);
//						_TOC_DO_BP = (_TOC_DO_BP > 700) ? 700 : (_TOC_DO_BP < -700 ? -700 : _TOC_DO_BP);
//						_TOC_DO_BT = (_TOC_DO_BT > 700) ? 700 : (_TOC_DO_BT < -700 ? -700 : _TOC_DO_BT);
					
//            banh_trai(_TOC_DO_BT);
//            banh_phai(_TOC_DO_BP);	
//            banh_sau (_TOC_DO_BS);	

					
//            banh_trai(1300);
//            banh_phai(1300);	
//            banh_sau (1300);	
//                        


}
				

///////////////////////////////////////////




