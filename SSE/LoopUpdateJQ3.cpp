void LoopUpdateJQ3(long long* SpinSystem,double* BondNOsystem,\
                    long long* Hoperator,long long &HNO,\
                    long long &SpinNO,long long &BondNO,long long &HoperatorNO,\
                    double &TempW,long long* BondNORecord)
{
    long long LoopNumA,LoopNumB,LoopNumC,LoopNumD;
    long long LeftSpin,RightSpin,LeftSpin2,RightSpin2,LeftSpin3,RightSpin3;
    long long *SpinRecord= NULL,*FirstSpin= NULL,*LastSpin= NULL;
    long long StartSpin,HSpin,HopNO,SwitchNO;
    long long CurrentSpin,footSpin,Check,Hop,HLeft,HRight,HLeft2,HRight2,HLeft3,HRight3,SpinNumber,SpinNumber2,SpinNumber3,SingleFoot,SingleCurrent;
    double Chance,Goal,SumSpin;
    //srand(time(NULL)*rand());
    SpinRecord=(long long *)malloc((HoperatorNO*12+1)*sizeof(long long*));
    FirstSpin=(long long *)malloc((SpinNO+1)*sizeof(long long*));
    LastSpin=(long long *)malloc((SpinNO+1)*sizeof(long long*));
    memset(SpinRecord,-1,(HoperatorNO*12)*sizeof(long long*));
    memset(FirstSpin,-1,SpinNO*sizeof(long long*));
    memset(LastSpin,-1,SpinNO*sizeof(long long*));
    SpinRecord[HoperatorNO*12]=-999;
    FirstSpin[SpinNO]=-999;
    LastSpin[SpinNO]=-999;
    Chance=0.50;
    //建構vertex operator的腳
    //printf("vertex \n");
    for (LoopNumA=0;LoopNumA<HoperatorNO*7;LoopNumA+=7)
    {
        //printf("HoperatorNO=%d,LoopNumA=%d \n",HoperatorNO,LoopNumA);
        //printf("Hop=%d,HLeft=%d,HRight=%d,HLeft2=%d,HRight2=%d \n",Hoperator[LoopNumA],Hoperator[LoopNumA+1],Hoperator[LoopNumA+2],Hoperator[LoopNumA+3],Hoperator[LoopNumA+4]);
        Hop=Hoperator[LoopNumA];
        HLeft=Hoperator[LoopNumA+1];
        HRight=Hoperator[LoopNumA+2];
        HLeft2=Hoperator[LoopNumA+3];
        HRight2=Hoperator[LoopNumA+4];
        HLeft3=Hoperator[LoopNumA+5];
        HRight3=Hoperator[LoopNumA+6];
        SpinNumber=(long long)(LoopNumA/7)*12;
        SpinNumber2=(long long)(LoopNumA/7)*12+4;
        SpinNumber3=(long long)(LoopNumA/7)*12+8;
        //Q3 0-3第一個pair 4-7 第二個pair 8-11第三個pair  
        if(Hop!=-1)
        {
            //printf("%d , %d\n",Hop,Hop%10); 
            if((Hop&15)<2)
            {
                //printf("%d , %d\n",Hop,Hop%10);
                LeftSpin=LastSpin[HLeft];
                RightSpin=LastSpin[HRight];
                if(LeftSpin!=-1)
                {
                    SpinRecord[SpinNumber]=LeftSpin;
                    SpinRecord[LeftSpin]=SpinNumber;
                }
                else
                {
                    FirstSpin[HLeft]=SpinNumber;
                }
                if(RightSpin!=-1)
                {
                    SpinRecord[SpinNumber+1]=RightSpin;
                    SpinRecord[RightSpin]=SpinNumber+1;
                }
                else
                {
                    FirstSpin[HRight]=SpinNumber+1;
                }
                LastSpin[HLeft]=SpinNumber+2;
                LastSpin[HRight]=SpinNumber+3;                
            }
            else//JQBond
            {
                           
                LeftSpin=LastSpin[HLeft];
                RightSpin=LastSpin[HRight];
                LeftSpin2=LastSpin[HLeft2];
                RightSpin2=LastSpin[HRight2];
                LeftSpin3=LastSpin[HLeft3];
                RightSpin3=LastSpin[HRight3];
                if(LeftSpin!=-1)
                {
                    
                    SpinRecord[SpinNumber]=LeftSpin;
                    SpinRecord[LeftSpin]=SpinNumber;
    
                }
                else
                {
                    FirstSpin[HLeft]=SpinNumber;
                }
                if(RightSpin!=-1)
                {
                    SpinRecord[SpinNumber+1]=RightSpin;
                    SpinRecord[RightSpin]=SpinNumber+1;
                }
                else
                {
                    FirstSpin[HRight]=SpinNumber+1;
                }
                //QBond~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                
                if(LeftSpin2!=-1)
                {
                    SpinRecord[SpinNumber2]=LeftSpin2;
                    SpinRecord[LeftSpin2]=SpinNumber2;
                }
                else
                {
                    FirstSpin[HLeft2]=SpinNumber2;
                }
                if(RightSpin2!=-1)
                {
                    SpinRecord[SpinNumber2+1]=RightSpin2;
                    SpinRecord[RightSpin2]=SpinNumber2+1;
                }
                else
                {
                    FirstSpin[HRight2]=SpinNumber2+1;
                }
                           
                if(LeftSpin3!=-1)
                {
                    SpinRecord[SpinNumber3]=LeftSpin3;
                    SpinRecord[LeftSpin3]=SpinNumber3;
                }
                else
                {
                    FirstSpin[HLeft3]=SpinNumber3;
                }
                if(RightSpin3!=-1)
                {
                    SpinRecord[SpinNumber3+1]=RightSpin3;
                    SpinRecord[RightSpin3]=SpinNumber3+1;
                }
                else
                {
                    FirstSpin[HRight3]=SpinNumber3+1;
                }                  
                LastSpin[HLeft]=SpinNumber+2;
                LastSpin[HRight]=SpinNumber+3;
                LastSpin[HLeft2]=SpinNumber2+2;
                LastSpin[HRight2]=SpinNumber2+3;
                LastSpin[HLeft3]=SpinNumber3+2;
                LastSpin[HRight3]=SpinNumber3+3;  
                
            }
 
        }
        else
        {
            for(LoopNumB=0;LoopNumB<12;LoopNumB+=1)
            {

                SpinRecord[SpinNumber+LoopNumB]=-1;
            }
        }
    }
    //printf("vertex-1 \n");
    for(LoopNumA=0;LoopNumA<SpinNO;LoopNumA+=1)
    {
        if(FirstSpin[LoopNumA]!=-1)
        {
            SpinRecord[FirstSpin[LoopNumA]]=LastSpin[LoopNumA];
            SpinRecord[LastSpin[LoopNumA]]=FirstSpin[LoopNumA];
        }
        
    }
    /*
    for(LoopNumA=0;LoopNumA <HoperatorNO*12;LoopNumA=LoopNumA+12)
    {
        //printf("%2d ,H=%3d  ,L=%3d  ,R=%3d \n",LoopNumA/3, Hoperator[LoopNumA], Hoperator[LoopNumA+1], Hoperator[LoopNumA+2]);
        printf("%2d ,%4d[%4d]  ,%4d[%4d]  ,%4d[%4d] ,%4d[%4d] ,%4d[%4d] ,%4d[%4d]  ,%4d[%4d]  ,%4d[%4d] ,%4d[%4d] ,%4d[%4d]  ,%4d[%4d]  ,%4d[%4d] \n", \
        LoopNumA/12,LoopNumA,SpinRecord[LoopNumA],LoopNumA+1,SpinRecord[LoopNumA+1],LoopNumA+2, SpinRecord[LoopNumA+2],LoopNumA+3, SpinRecord[LoopNumA+3], \
        LoopNumA+4,SpinRecord[LoopNumA+4],LoopNumA+5,SpinRecord[LoopNumA+5],LoopNumA+6,SpinRecord[LoopNumA+6],LoopNumA+7,SpinRecord[LoopNumA+7], \
        LoopNumA+8,SpinRecord[LoopNumA+8],LoopNumA+9,SpinRecord[LoopNumA+9],LoopNumA+10,SpinRecord[LoopNumA+10],LoopNumA+11,SpinRecord[LoopNumA+11]);
    }
    */
    /*
    for(LoopNumA=0;LoopNumA <HoperatorNO*12;LoopNumA=LoopNumA+12)
    {
        //printf("%2d ,H=%3d  ,L=%3d  ,R=%3d \n",LoopNumA/3, Hoperator[LoopNumA], Hoperator[LoopNumA+1], Hoperator[LoopNumA+2]);
        
        if(Hoperator[(long long)LoopNumA/12*7]!=-1)
        {
            printf("%2d  ",LoopNumA/12) ;
            for(LoopNumB=0;LoopNumB <12;LoopNumB+=1)
            {
                printf("%5d[%5d]",LoopNumA+LoopNumB,SpinRecord[LoopNumA+LoopNumB]);
          
            }
            printf("\n ") ;
        }
        
    }
    */
    //system("pause");
    //printf("Loop \n");
    for(LoopNumA=0;LoopNumA<HoperatorNO*12;LoopNumA+=4)//4為一個operator幾個腳，在這邊Q會4*3，半邊半邊算
    {
        if(SpinRecord[LoopNumA]>-1)
        { 
            StartSpin=LoopNumA;
            CurrentSpin=LoopNumA;
            Check=1;
            if(genrand64_real2()<Chance)
            {
                SumSpin=0; 
                while (Check==1)
                {
                    footSpin=CurrentSpin^1;
                    /*
                    if(CurrentSpin%2==0)
                    {
                        footSpin=CurrentSpin+1;                     
                    }
                    else
                    {
                        footSpin=CurrentSpin-1; 
                    }
                    */
                    HopNO = (((long long)(CurrentSpin/12))*7);
                    SwitchNO = (long long)((CurrentSpin%12)/4);
                    //printf("test %d %d\n",(long long)(CurrentSpin%12/4),(long long )((long long)(CurrentSpin%12/4)));
                    switch((Hoperator[HopNO]&15))//1091002 修正
                    {
                        case 0:
                           Hoperator[HopNO]+=1;
                           break;
                        case 1:
                           Hoperator[HopNO]-=1;
                           break;
                        case 2:
              
                            switch(SwitchNO)
                            {
                                case 0:
                                    Hoperator[HopNO]+=3;
                                    break;
                                case 1:
                                    Hoperator[HopNO]+=4;
                                    break;
                                case 2:
                                    Hoperator[HopNO]+=5;
                                    break;
                                                      
                            }
                            break;
                        case 5:
                            switch(SwitchNO)
                            {
                                case 0:
                                    Hoperator[HopNO]-=3;
                                    break;
                                case 1:
                                    Hoperator[HopNO]+=4;
                                    break;
                                case 2:
                                    Hoperator[HopNO]+=5;
                                    break;
                            }
                            break;
                        case 6:
                            switch(SwitchNO)
                            {
                                case 0:
                                    Hoperator[HopNO]+=3;
                                    break;
                                case 1:
                                    Hoperator[HopNO]-=4;
                                    break;
                                case 2:
                                    Hoperator[HopNO]+=5;
                                    break;
                            }
                            break;        
                        case 7:
                            switch(SwitchNO)
                            {
                                case 0:
                                    Hoperator[HopNO]+=3;
                                    break;
                                case 1:
                                    Hoperator[HopNO]+=4;
                                    break;
                                case 2:
                                    Hoperator[HopNO]-=5;
                                    break;
                            }
                            break;
                        case 9:
                            switch(SwitchNO)
                            {
                                case 0:
                                    Hoperator[HopNO]-=3;
                                    break;
                                case 1:
                                    Hoperator[HopNO]-=4;
                                    break;
                                case 2:
                                    Hoperator[HopNO]+=5;
                                    break;
                            }
                            break;
                        case 10:
                            switch(SwitchNO)
                            {
                                case 0:
                                    Hoperator[HopNO]-=3;
                                    break;
                                case 1:
                                    Hoperator[HopNO]+=4;
                                    break;
                                case 2:
                                    Hoperator[HopNO]-=5;
                                    break;
                            }
                            break;
                        case 11:
                            switch(SwitchNO)
                            {
                                case 0:
                                    Hoperator[HopNO]+=3;
                                    break;
                                case 1:
                                    Hoperator[HopNO]-=4;
                                    break;
                                case 2:
                                    Hoperator[HopNO]-=5;
                                    break;
                            }
                            break;
                        case 14:
                            switch(SwitchNO)
                            {
                                case 0:
                                    Hoperator[HopNO]-=3;
                                    break;
                                case 1:
                                    Hoperator[HopNO]-=4;
                                    break;
                                case 2:
                                    Hoperator[HopNO]-=5;
                                    break;  
                            }
                            break;                           
                    }
                    SpinRecord[CurrentSpin]=-3;
                    //SpinRecord[CurrentSpin]=-1;
                    CurrentSpin=SpinRecord[footSpin];
                    SpinRecord[footSpin]=-3;
                    /*
                    SingleFoot=footSpin%12;
                    HSpin=Hoperator[(long long)(footSpin/12*7)+2*(long long)(SingleFoot/4)+SingleFoot%2+1];//請Hoperator內Spin的index

                    if(footSpin%4<2)
                    {
                        //printf("%f \n",SpinSystem[HSpin*3+1]);
                        if(FirstSpin[HSpin]==footSpin)
                        {
                           SumSpin+=SpinSystem[HSpin*3+1];
                           //printf("%f \n",SpinSystem[Hoperator[footSpin/8*5+2*SingleFoot/4+SingleFoot%2+1]*3+1]);
                           //SumSpin+=SpinSystem[Hoperator[CurrentSpin/8*5+SingleCurrent/4+SingleCurrent%2]*3+1]
                            
                        }
                    }
                    else
                    {
                        if(LastSpin[HSpin]==footSpin)
                        {
                           SumSpin+=SpinSystem[HSpin*3+1];
                           //SumSpin+=SpinSystem[Hoperator[CurrentSpin/8*5+SingleCurrent/4+SingleCurrent%2]*3+1]
                            
                        }
                        
                    }
                    */
                    if(CurrentSpin==StartSpin)
                    {
                        Check=0;
                    }
                    //printf("loop x1 CurrentSpin %d footSpin %d\n",CurrentSpin,footSpin);
                }
                //TempW+=SumSpin*SumSpin*0.25;
            }
            else
            {
                SumSpin=0;
                while(Check==1)
                {
                    if(CurrentSpin%2==0)
                    {
                        footSpin=CurrentSpin+1;                     
                    }
                    else
                    {
                        footSpin=CurrentSpin-1; 
                    }
                    SpinRecord[CurrentSpin]=-2;
                    CurrentSpin=SpinRecord[footSpin];
                    SpinRecord[footSpin]=-2;
                    /*SingleFoot=footSpin%12;
                    HSpin=Hoperator[(long long)(footSpin/12*7)+2*(long long)(SingleFoot/4)+SingleFoot%2+1];

                    //printf("%d \n",HSpin);
                    if(footSpin%4<2)
                    {
                        if(FirstSpin[HSpin]==footSpin)
                        {
                           SumSpin+=SpinSystem[HSpin*3+1];
                           //SumSpin+=SpinSystem[Hoperator[CurrentSpin/8*5+SingleCurrent/4+SingleCurrent%2]*3+1]
                            
                        }
                    }
                    else
                    {
                        if(LastSpin[HSpin]==footSpin)
                        {
                           SumSpin+=SpinSystem[HSpin*3+1];
                           //SumSpin+=SpinSystem[Hoperator[CurrentSpin/8*5+SingleCurrent/4+SingleCurrent%2]*3+1]
                            
                        }
                        
                    }
                    */
                    if(CurrentSpin==StartSpin)
                    {
                        Check=0;
                    }
                    //printf("loop x-1 CurrentSpin %d footSpin %d\n",CurrentSpin,footSpin);      
                }
                //TempW+=SumSpin*SumSpin*0.25;
          
            }
        }
        
    }
    /*
    for(LoopNumA=0;LoopNumA <HoperatorNO;LoopNumA=LoopNumA+1)
    {
        //printf("%2d ,H=%3d  ,L=%3d  ,R=%3d \n",LoopNumA/3, Hoperator[LoopNumA], Hoperator[LoopNumA+1], Hoperator[LoopNumA+2]);
        for(LoopNumB=0;LoopNumB <12;LoopNumB+=1)
        {
            if(SpinRecord[LoopNumA*12+LoopNumB]>-1 )
            {
            //printf("%d  %d  ",LoopNumA,SpinRecord[LoopNumA]) ;

                printf("%4d[%4d]%d ",LoopNumA+LoopNumB,SpinRecord[LoopNumA+LoopNumB+1],SpinRecord[LoopNumA+LoopNumB]);
                printf("\n");
            }
            
        }
        
    }
    */
    //printf("%f \n",TempW);
    //printf("loop 1 \n");   
    for(LoopNumA=0;LoopNumA<SpinNO;LoopNumA+=1)
    {
        SpinNumber=LoopNumA*3;
        if(FirstSpin[LoopNumA]!=-1)
        {
            if(SpinRecord[FirstSpin[LoopNumA]]==-3)
            {
                SpinSystem[SpinNumber+1]*=-1;
            }
        }
        else
        {
            //Goal=genrand64_real2();
            if(genrand64_real2()<Chance)
            {
                SpinSystem[SpinNumber+1]*=-1; 
            }
            //TempW+=SpinSystem[SpinNumber+1]*SpinSystem[SpinNumber+1]*0.25;
        }
    }
    //printf("loop end \n");
    free(SpinRecord);
    free(FirstSpin);
    free(LastSpin);
    SpinRecord=NULL;
    FirstSpin=NULL;
    LastSpin=NULL;
}


void LoopUpdateJQ3_TempW(long long* SpinSystem,double* BondNOsystem,\
                    long long* Hoperator,long long &HNO,\
                    long long &SpinNO,long long &BondNO,long long &HoperatorNO,\
                    double &TempW,long long* BondNORecord)
{
    long long LoopNumA,LoopNumB,LoopNumC,LoopNumD;
    long long LeftSpin,RightSpin,LeftSpin2,RightSpin2,LeftSpin3,RightSpin3;
    long long *SpinRecord= NULL,*FirstSpin= NULL,*LastSpin= NULL;
    long long StartSpin,HSpin,HopNO,SwitchNO;
    long long CurrentSpin,footSpin,Check,Hop,HLeft,HRight,HLeft2,HRight2,HLeft3,HRight3,SpinNumber,SpinNumber2,SpinNumber3,SingleFoot,SingleCurrent;
    double Chance,Goal,SumSpin;
    //srand(time(NULL)*rand());
    SpinRecord=(long long *)malloc((HoperatorNO*12+1)*sizeof(long long*));
    FirstSpin=(long long *)malloc((SpinNO+1)*sizeof(long long*));
    LastSpin=(long long *)malloc((SpinNO+1)*sizeof(long long*));
    memset(SpinRecord,-1,(HoperatorNO*12)*sizeof(long long*));
    memset(FirstSpin,-1,SpinNO*sizeof(long long*));
    memset(LastSpin,-1,SpinNO*sizeof(long long*));
    //SpinRecord[HoperatorNO*12+1]=-999;
    //FirstSpin[SpinNO]=-999;
    //LastSpin[SpinNO]=-999;
    Chance=0.50;
    //建構vertex operator的腳
    //printf("vertex \n");
    for (LoopNumA=0;LoopNumA<HoperatorNO*7;LoopNumA+=7)
    {
        //printf("HoperatorNO=%d,LoopNumA=%d \n",HoperatorNO,LoopNumA);
        //printf("Hop=%d,HLeft=%d,HRight=%d,HLeft2=%d,HRight2=%d \n",Hoperator[LoopNumA],Hoperator[LoopNumA+1],Hoperator[LoopNumA+2],Hoperator[LoopNumA+3],Hoperator[LoopNumA+4]);
        Hop=Hoperator[LoopNumA];
        HLeft=Hoperator[LoopNumA+1];
        HRight=Hoperator[LoopNumA+2];
        HLeft2=Hoperator[LoopNumA+3];
        HRight2=Hoperator[LoopNumA+4];
        HLeft3=Hoperator[LoopNumA+5];
        HRight3=Hoperator[LoopNumA+6];
        SpinNumber=(long long)(LoopNumA/7)*12;
        SpinNumber2=(long long)(LoopNumA/7)*12+4;
        SpinNumber3=(long long)(LoopNumA/7)*12+8;
        //Q3 0-3第一個pair 4-7 第二個pair 8-11第三個pair  
        if(Hop!=-1)
        {
            //printf("%d , %d\n",Hop,Hop%10); 
            if((Hop&15)<2)
            {
                //printf("%d , %d\n",Hop,Hop%10);
                LeftSpin=LastSpin[HLeft];
                RightSpin=LastSpin[HRight];
                if(LeftSpin!=-1)
                {
                    SpinRecord[SpinNumber]=LeftSpin;
                    SpinRecord[LeftSpin]=SpinNumber;
                }
                else
                {
                    FirstSpin[HLeft]=SpinNumber;
                }
                if(RightSpin!=-1)
                {
                    SpinRecord[SpinNumber+1]=RightSpin;
                    SpinRecord[RightSpin]=SpinNumber+1;
                }
                else
                {
                    FirstSpin[HRight]=SpinNumber+1;
                }
                LastSpin[HLeft]=SpinNumber+2;
                LastSpin[HRight]=SpinNumber+3;                
            }
            else//JQBond
            {
                           
                LeftSpin=LastSpin[HLeft];
                RightSpin=LastSpin[HRight];
                LeftSpin2=LastSpin[HLeft2];
                RightSpin2=LastSpin[HRight2];
                LeftSpin3=LastSpin[HLeft3];
                RightSpin3=LastSpin[HRight3];
                if(LeftSpin!=-1)
                {
                    
                    SpinRecord[SpinNumber]=LeftSpin;
                    SpinRecord[LeftSpin]=SpinNumber;
    
                }
                else
                {
                    FirstSpin[HLeft]=SpinNumber;
                }
                if(RightSpin!=-1)
                {
                    SpinRecord[SpinNumber+1]=RightSpin;
                    SpinRecord[RightSpin]=SpinNumber+1;
                }
                else
                {
                    FirstSpin[HRight]=SpinNumber+1;
                }
                //QBond~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                
                if(LeftSpin2!=-1)
                {
                    SpinRecord[SpinNumber2]=LeftSpin2;
                    SpinRecord[LeftSpin2]=SpinNumber2;
                }
                else
                {
                    FirstSpin[HLeft2]=SpinNumber2;
                }
                if(RightSpin2!=-1)
                {
                    SpinRecord[SpinNumber2+1]=RightSpin2;
                    SpinRecord[RightSpin2]=SpinNumber2+1;
                }
                else
                {
                    FirstSpin[HRight2]=SpinNumber2+1;
                }
                           
                if(LeftSpin3!=-1)
                {
                    SpinRecord[SpinNumber3]=LeftSpin3;
                    SpinRecord[LeftSpin3]=SpinNumber3;
                }
                else
                {
                    FirstSpin[HLeft3]=SpinNumber3;
                }
                if(RightSpin3!=-1)
                {
                    SpinRecord[SpinNumber3+1]=RightSpin3;
                    SpinRecord[RightSpin3]=SpinNumber3+1;
                }
                else
                {
                    FirstSpin[HRight3]=SpinNumber3+1;
                }                  
                LastSpin[HLeft]=SpinNumber+2;
                LastSpin[HRight]=SpinNumber+3;
                LastSpin[HLeft2]=SpinNumber2+2;
                LastSpin[HRight2]=SpinNumber2+3;
                LastSpin[HLeft3]=SpinNumber3+2;
                LastSpin[HRight3]=SpinNumber3+3;  
                
            }
 
        }
        else
        {
            for(LoopNumB=0;LoopNumB<12;LoopNumB+=1)
            {

                SpinRecord[SpinNumber+LoopNumB]=-1;
            }
        }
    }
    //printf("vertex-1 \n");
    for(LoopNumA=0;LoopNumA<SpinNO;LoopNumA+=1)
    {
        if(FirstSpin[LoopNumA]!=-1)
        {
            SpinRecord[FirstSpin[LoopNumA]]=LastSpin[LoopNumA];
            SpinRecord[LastSpin[LoopNumA]]=FirstSpin[LoopNumA];
        }
        
    }
 
    for(LoopNumA=0;LoopNumA<HoperatorNO*12;LoopNumA+=4)//4為一個operator幾個腳，在這邊Q會4*3，半邊半邊算
    {
        if(SpinRecord[LoopNumA]>-1)
        { 
            StartSpin=LoopNumA;
            CurrentSpin=LoopNumA;
            Check=1;
            if(genrand64_real2()<Chance)
            {
                SumSpin=0; 
                while (Check==1)
                {
                    footSpin=CurrentSpin^1;
                    /*
                    if(CurrentSpin%2==0)
                    {
                        footSpin=CurrentSpin+1;                     
                    }
                    else
                    {
                        footSpin=CurrentSpin-1; 
                    }
                    */
                    
                    HopNO = (((long long)(CurrentSpin/12))*7);
                    SwitchNO = (long long)((CurrentSpin%12)/4);
                    //printf("%d %d %d\n",Hoperator[(long long)(CurrentSpin/12)*7]&15,CurrentSpin%12,(long long)(CurrentSpin%12/4));
                    
                    switch((Hoperator[HopNO]&15))//1091002 修正
                    {
                        case 0:
                           Hoperator[HopNO]+=1;
                           break;
                        case 1:
                           Hoperator[HopNO]-=1;
                           break;
                        case 2:
              
                            switch(SwitchNO)
                            {
                                case 0:
                                    Hoperator[HopNO]+=3;
                                    break;
                                case 1:
                                    Hoperator[HopNO]+=4;
                                    break;
                                case 2:
                                    Hoperator[HopNO]+=5;
                                    break;
                          
                            }
                            break;

                        case 5:
                            switch(SwitchNO)
                            {
                                case 0:
                                    Hoperator[HopNO]-=3;
                                    break;
                                case 1:
                                    Hoperator[HopNO]+=4;
                                    break;
                                case 2:
                                    Hoperator[HopNO]+=5;
                                    break;
                            }
                            break;
                        case 6:
                            switch(SwitchNO)
                            {
                                case 0:
                                    Hoperator[HopNO]+=3;
                                    break;
                                case 1:
                                    Hoperator[HopNO]-=4;
                                    break;
                                case 2:
                                    Hoperator[HopNO]+=5;
                                    break;
                            }
                            break;        
                        case 7:
                            switch(SwitchNO)
                            {
                                case 0:
                                    Hoperator[HopNO]+=3;
                                    break;
                                case 1:
                                    Hoperator[HopNO]+=4;
                                    break;
                                case 2:
                                    Hoperator[HopNO]-=5;
                                    break;
                            }
                            break;
                        case 9:
                            switch(SwitchNO)
                            {
                                case 0:
                                    Hoperator[HopNO]-=3;
                                    break;
                                case 1:
                                    Hoperator[HopNO]-=4;
                                    break;
                                case 2:
                                    Hoperator[HopNO]+=5;
                                    break;
                            }
                            break;
                        case 10:
                            switch(SwitchNO)
                            {
                                case 0:
                                    Hoperator[HopNO]-=3;
                                    break;
                                case 1:
                                    Hoperator[HopNO]+=4;
                                    break;
                                case 2:
                                    Hoperator[HopNO]-=5;
                                    break;
                            }
                            break;
                        case 11:
                            switch(SwitchNO)
                            {
                                case 0:
                                    Hoperator[HopNO]+=3;
                                    break;
                                case 1:
                                    Hoperator[HopNO]-=4;
                                    break;
                                case 2:
                                    Hoperator[HopNO]-=5;
                                    break;
                            }
                            break;
                        case 14:
                            switch(SwitchNO)
                            {
                                case 0:
                                    Hoperator[HopNO]-=3;
                                    break;
                                case 1:
                                    Hoperator[HopNO]-=4;
                                    break;
                                case 2:
                                    Hoperator[HopNO]-=5;
                                    break;  
                            }
                            break;                           
                    }
                    

                    SpinRecord[CurrentSpin]=-3;
                    CurrentSpin=SpinRecord[footSpin];
                    SpinRecord[footSpin]=-3;
                    SingleFoot=footSpin%12;
                    HSpin=Hoperator[(long long)(footSpin/12*7)+2*(long long)(SingleFoot/4)+SingleFoot%2+1];//請Hoperator內Spin的index

                    if(footSpin%4<2)
                    {
                        //printf("%f \n",SpinSystem[HSpin*3+1]);
                        if(FirstSpin[HSpin]==footSpin)
                        {
                           SumSpin+=SpinSystem[HSpin*3+1];
                           //printf("%f \n",SpinSystem[Hoperator[footSpin/8*5+2*SingleFoot/4+SingleFoot%2+1]*3+1]);
                           //SumSpin+=SpinSystem[Hoperator[CurrentSpin/8*5+SingleCurrent/4+SingleCurrent%2]*3+1]
                            
                        }
                    }
                    else
                    {
                        if(LastSpin[HSpin]==footSpin)
                        {
                           SumSpin+=SpinSystem[HSpin*3+1];
                           //SumSpin+=SpinSystem[Hoperator[CurrentSpin/8*5+SingleCurrent/4+SingleCurrent%2]*3+1]
                            
                        }
                        
                    }
                    
                    if(CurrentSpin==StartSpin)
                    {
                        Check=0;
                    }
                    //printf("loop x1 CurrentSpin %d footSpin %d\n",CurrentSpin,footSpin);
                }
                TempW+=SumSpin*SumSpin*0.25;
            }
            else
            {
                SumSpin=0;
                while(Check==1)
                {
                    if(CurrentSpin%2==0)
                    {
                        footSpin=CurrentSpin+1;                     
                    }
                    else
                    {
                        footSpin=CurrentSpin-1; 
                    }
                    SpinRecord[CurrentSpin]=-2;
                    CurrentSpin=SpinRecord[footSpin];
                    SpinRecord[footSpin]=-2;
                    SingleFoot=footSpin%12;
                    HSpin=Hoperator[(long long)(footSpin/12*7)+2*(long long)(SingleFoot/4)+SingleFoot%2+1];

                    //printf("%d \n",HSpin);
                    if(footSpin%4<2)
                    {
                        if(FirstSpin[HSpin]==footSpin)
                        {
                           SumSpin+=SpinSystem[HSpin*3+1];
                           //SumSpin+=SpinSystem[Hoperator[CurrentSpin/8*5+SingleCurrent/4+SingleCurrent%2]*3+1]
                            
                        }
                    }
                    else
                    {
                        if(LastSpin[HSpin]==footSpin)
                        {
                           SumSpin+=SpinSystem[HSpin*3+1];
                           //SumSpin+=SpinSystem[Hoperator[CurrentSpin/8*5+SingleCurrent/4+SingleCurrent%2]*3+1]
                            
                        }
                        
                    }
                    
                    if(CurrentSpin==StartSpin)
                    {
                        Check=0;
                    }
                    //printf("loop x-1 CurrentSpin %d footSpin %d\n",CurrentSpin,footSpin);      
                }
                TempW+=SumSpin*SumSpin*0.25;
          
            }
        }
        
    }
    //printf("%f \n",TempW);
    //printf("loop 1 \n");   
    for(LoopNumA=0;LoopNumA<SpinNO;LoopNumA+=1)
    {
        SpinNumber=LoopNumA*3;
        if(FirstSpin[LoopNumA]!=-1)
        {
            if(SpinRecord[FirstSpin[LoopNumA]]==-3)
            {
                SpinSystem[SpinNumber+1]*=-1;
            }
        }
        else
        {
            //Goal=genrand64_real2();
            if(genrand64_real2()<Chance)
            {
                SpinSystem[SpinNumber+1]*=-1; 
            }
            TempW+=SpinSystem[SpinNumber+1]*SpinSystem[SpinNumber+1]*0.25;
        }
    }
    //printf("loop end \n");
    free(SpinRecord);
    free(FirstSpin);
    free(LastSpin);
    SpinRecord=NULL;
    FirstSpin=NULL;
    LastSpin=NULL;
}
