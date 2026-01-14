void robotGamePadControl(void)
{
int tocdo;

float	tocdoXoay = 0.3;
    int rJoy_LR  = (RJOY_LR >= 5 && RJOY_LR <= 250)? 1 : 0; 
    int lJoy_LR  = (LJOY_LR >= 5 && LJOY_LR <= 250)? 1 : 0;

    if(UP && DOWN && RIGHT && LEFT && rJoy_LR && lJoy_LR)
		{ // Khong dieu khien
        robotStop(10); //truot banh
        return;
    }                
/*____________________________//__________________________*/

/********************** TOC DO ****************************/
/*___________________________//__________________________*/
     if(!L1) tocdo = 40, tocdoXoay = 0.5;
		 else tocdo = 20, tocdoXoay = 0.3;
		

		
		
//		tocdo = 10, tocdoXoay = 0.3;
  
    //--------- chay cac huong -----------
    if		(!UP && DOWN && RIGHT && LEFT )   robotRun(0,tocdo);
    else if(UP && !DOWN && RIGHT && LEFT  )   robotRun(1800,tocdo);
    else if(UP && DOWN && !RIGHT && LEFT  )   robotRunAngle(900,tocdo, 0);
    else if(UP && DOWN && RIGHT && !LEFT  )   robotRunAngle(-900,tocdo, 0);
    
    else if(!UP && DOWN && !RIGHT && LEFT  )  robotRunAngle(450,tocdo, 0);
    else if(!UP && DOWN && RIGHT && !LEFT  )  robotRunAngle(-450,tocdo, 0);
    else if(UP && !DOWN && !RIGHT && LEFT )  	robotRunAngle(1350,tocdo, 0);
    else if(UP && !DOWN && RIGHT && !LEFT  )  robotRunAngle(-1350,tocdo, 0);
//    //-------------- Dang chay va Khong chay nua, chi xoay ----------------
    if(UP && DOWN && RIGHT && LEFT && !rJoy_LR && lJoy_LR  && robotIsRun()) robotStop(0);   

    //-------------- Xoay ----------------
    if(rJoy_LR) robotRotateStop();
    else if((RJOY_LR < 5) && L2)
    {
        if(robotIsRun()) robotRotateFree(-0.7,1);
        else robotRotateFree(-tocdoXoay,0);
    }
    else if((RJOY_LR > 250) && L2)
    {
        if(robotIsRun()) robotRotateFree(0.7,1);
        else robotRotateFree(tocdoXoay,0);
    }

    else robotRotateStop();
	}
//######################################################################################################
