void LoopUpdateJQ2(double* SpinSystem,double* BondNOsystem,\
    long long* Hoperator,long long &HNO,\
    long long &SpinNO,long long &BondNO,long long &HoperatorNO,\
    double &TempW)
{
    long long LoopNumA,LoopNumB,LoopNumC,LoopNumD;
    long long LeftSpin,RightSpin,LeftSpin2,RightSpin2;
    long long *SpinRecord= NULL,*FirstSpin= NULL,*LastSpin= NULL;
    long long StartSpin,SumSpin;
    long long CurrentSpin,footSpin,Check,Hop,HLeft,HRight,HLeft2,HRight2,SpinNumber,SpinNumber2,SingleFoot,SingleCurrent;
    double Chance,Goal;
    //srand(time(NULL)*rand());
    SpinRecord=(long long *)malloc((HoperatorNO*8+1)*sizeof(long long*));
    FirstSpin=(long long *)malloc((SpinNO+1)*sizeof(long long*));
    LastSpin=(long long *)malloc((SpinNO+1)*sizeof(long long*));
    memset(SpinRecord,-1,(HoperatorNO*8)*sizeof(long long*));
    memset(FirstSpin,-1,SpinNO*sizeof(long long*));
    memset(LastSpin,-1,SpinNO*sizeof(long long*));
    SpinRecord[HoperatorNO*8]=-999;
    FirstSpin[SpinNO]=-999;
    LastSpin[SpinNO]=-999;
    Chance=0.50;
    //建構vertex operator的腳
    //printf("vertex \n");
    for (LoopNumA=0;LoopNumA<HoperatorNO*5;LoopNumA+=5)
    {
        //printf("HoperatorNO=%d,LoopNumA=%d \n",HoperatorNO,LoopNumA);
        //printf("Hop=%d,HLeft=%d,HRight=%d,HLeft2=%d,HRight2=%d \n",Hoperator[LoopNumA],Hoperator[LoopNumA+1],Hoperator[LoopNumA+2],Hoperator[LoopNumA+3],Hoperator[LoopNumA+4]);
        Hop=Hoperator[LoopNumA];
        HLeft=Hoperator[LoopNumA+1];
        HRight=Hoperator[LoopNumA+2];
        HLeft2=Hoperator[LoopNumA+3];
        HRight2=Hoperator[LoopNumA+4];
        SpinNumber=(long long)(LoopNumA/5)*8;
        SpinNumber2=(long long)(LoopNumA/5)*8+4;

        if(Hop!=-1)
        {
            if(Hop%10<2)
            {
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
                
                LastSpin[HLeft]=SpinNumber+2;
                LastSpin[HRight]=SpinNumber+3;
                LastSpin[HLeft2]=SpinNumber2+2;
                LastSpin[HRight2]=SpinNumber2+3;   
                
            }
 
        }
        else
        {
            for(LoopNumB=0;LoopNumB<8;LoopNumB+=1)
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
    /*for(LoopNumA=0;LoopNumA <HoperatorNO*8;LoopNumA=LoopNumA+8)
    {
        //printf("%2d ,H=%3d  ,L=%3d  ,R=%3d \n",LoopNumA/3, Hoperator[LoopNumA], Hoperator[LoopNumA+1], Hoperator[LoopNumA+2]);
        printf("%2d ,%4d[%4d]  ,%4d[%4d]  ,%4d[%4d] ,%4d[%4d] ,%4d[%4d] ,%4d[%4d]  ,%4d[%4d]  ,%4d[%4d] \n",LoopNumA/8,LoopNumA,SpinRecord[LoopNumA],LoopNumA+1,SpinRecord[LoopNumA+1],LoopNumA+2, SpinRecord[LoopNumA+2],LoopNumA+3, SpinRecord[LoopNumA+3], \
        LoopNumA+4,SpinRecord[LoopNumA+4],LoopNumA+5,SpinRecord[LoopNumA+5],LoopNumA+6,SpinRecord[LoopNumA+6],LoopNumA+7,SpinRecord[LoopNumA+7]);
    }*/
    //printf("loop \n");
    for(LoopNumA=0;LoopNumA<HoperatorNO*8;LoopNumA+=4)//4為一個operator幾個腳，在這邊Q會4*2，半邊半邊算
    {
        //printf("LoopNumA=%d ,SpinRecord[LoopNumA]=%d \n",LoopNumA,SpinRecord[LoopNumA]);
        if(SpinRecord[LoopNumA]>-1)
        { 
           
            //Goal=genrand64_real2();
            StartSpin=LoopNumA;
            CurrentSpin=LoopNumA;
            Check=1;
            if(genrand64_real2()<Chance)
            {
                SumSpin=0; 
                while (Check==1)
                {
                    if(CurrentSpin%2==0)
                    {
                        footSpin=CurrentSpin+1;                     
                    }
                    else
                    {
                        footSpin=CurrentSpin-1; 
                    }
                    
                    switch(Hoperator[CurrentSpin/8*5]%10)
                    {
                        case 0:
                           Hoperator[CurrentSpin/8*5]+=1;
                           break;
                        case 1:
                           Hoperator[CurrentSpin/8*5]-=1;
                            break;
                        case 2:
                            if(CurrentSpin%8<4)
                            {
                                Hoperator[CurrentSpin/8*5]+=3;
                            }
                            else
                            {
                                Hoperator[CurrentSpin/8*5]+=4;
                            }
                            break;
                        case 5:
                            if(CurrentSpin%8<4)
                            {
                                Hoperator[CurrentSpin/8*5]-=3;
                            }
                            else
                            {
                                Hoperator[CurrentSpin/8*5]+=4;
                            }
                            break;
                        case 6:
                            if(CurrentSpin%8<4)
                            {
                                Hoperator[CurrentSpin/8*5]+=3;
                            }
                            else
                            {
                                Hoperator[CurrentSpin/8*5]-=4;
                            }
                            break;
                        case 9:
                            if(CurrentSpin%8<4)
                            {
                                Hoperator[CurrentSpin/8*5]-=3;
                            }
                            else
                            {
                                Hoperator[CurrentSpin/8*5]-=4;
                            }
                            break;                       
                    }
                    SpinRecord[CurrentSpin]=-1;
                    CurrentSpin=SpinRecord[footSpin];
                    SpinRecord[footSpin]=-1;

                    
                    if(CurrentSpin==StartSpin)
                    {
                        Check=0;
                    }
                    //printf("loop x1 CurrentSpin %d footSpin %d\n",CurrentSpin,footSpin);
                }
            }
            else
            {
                
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
 
                    
                    if(CurrentSpin==StartSpin)
                    {
                        Check=0;
                    }
                    //printf("loop x-1 CurrentSpin %d footSpin %d\n",CurrentSpin,footSpin);      
                }
          
            }
        }
        
    }
    //printf("loop 1 \n");   
    for(LoopNumA=0;LoopNumA<SpinNO;LoopNumA+=1)
    {
        SpinNumber=LoopNumA*3;
        if(FirstSpin[LoopNumA]!=-1)
        {
            if(SpinRecord[FirstSpin[LoopNumA]]==-1)
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


void LoopUpdateJQ2_TempW(double* SpinSystem,double* BondNOsystem,\
                    long long* Hoperator,long long &HNO,\
                    long long &SpinNO,long long &BondNO,long long &HoperatorNO,\
                    double &TempW)
{
    long long LoopNumA,LoopNumB,LoopNumC,LoopNumD;
    long long LeftSpin,RightSpin,LeftSpin2,RightSpin2;
    long long *SpinRecord= NULL,*FirstSpin= NULL,*LastSpin= NULL;
    long long StartSpin,HSpin;
    long long CurrentSpin,footSpin,Check,Hop,HLeft,HRight,HLeft2,HRight2,SpinNumber,SpinNumber2,SingleFoot,SingleCurrent;
    double Chance,Goal,SumSpin;
    //srand(time(NULL)*rand());
    SpinRecord=(long long *)malloc((HoperatorNO*8+1)*sizeof(long long*));
    FirstSpin=(long long *)malloc((SpinNO+1)*sizeof(long long*));
    LastSpin=(long long *)malloc((SpinNO+1)*sizeof(long long*));
    memset(SpinRecord,-1,(HoperatorNO*8)*sizeof(long long*));
    memset(FirstSpin,-1,SpinNO*sizeof(long long*));
    memset(LastSpin,-1,SpinNO*sizeof(long long*));
    SpinRecord[HoperatorNO*8]=-999;
    FirstSpin[SpinNO]=-999;
    LastSpin[SpinNO]=-999;
    Chance=0.50;
    //建構vertex operator的腳
    //printf("vertex \n");
    for (LoopNumA=0;LoopNumA<HoperatorNO*5;LoopNumA+=5)
    {
        //printf("HoperatorNO=%d,LoopNumA=%d \n",HoperatorNO,LoopNumA);
        //printf("Hop=%d,HLeft=%d,HRight=%d,HLeft2=%d,HRight2=%d \n",Hoperator[LoopNumA],Hoperator[LoopNumA+1],Hoperator[LoopNumA+2],Hoperator[LoopNumA+3],Hoperator[LoopNumA+4]);
        Hop=Hoperator[LoopNumA];
        HLeft=Hoperator[LoopNumA+1];
        HRight=Hoperator[LoopNumA+2];
        HLeft2=Hoperator[LoopNumA+3];
        HRight2=Hoperator[LoopNumA+4];
        SpinNumber=(long long)(LoopNumA/5)*8;
        SpinNumber2=(long long)(LoopNumA/5)*8+4;

        if(Hop!=-1)
        {
            //printf("%d , %d\n",Hop,Hop%10); 
            if(Hop%10<2)
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
                
                LastSpin[HLeft]=SpinNumber+2;
                LastSpin[HRight]=SpinNumber+3;
                LastSpin[HLeft2]=SpinNumber2+2;
                LastSpin[HRight2]=SpinNumber2+3;   
                
            }
 
        }
        else
        {
            for(LoopNumB=0;LoopNumB<8;LoopNumB+=1)
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
    /*for(LoopNumA=0;LoopNumA <HoperatorNO*8;LoopNumA=LoopNumA+8)
    {
        //printf("%2d ,H=%3d  ,L=%3d  ,R=%3d \n",LoopNumA/3, Hoperator[LoopNumA], Hoperator[LoopNumA+1], Hoperator[LoopNumA+2]);
        printf("%2d ,%4d[%4d]  ,%4d[%4d]  ,%4d[%4d] ,%4d[%4d] ,%4d[%4d] ,%4d[%4d]  ,%4d[%4d]  ,%4d[%4d] \n",LoopNumA/8,LoopNumA,SpinRecord[LoopNumA],LoopNumA+1,SpinRecord[LoopNumA+1],LoopNumA+2, SpinRecord[LoopNumA+2],LoopNumA+3, SpinRecord[LoopNumA+3], \
        LoopNumA+4,SpinRecord[LoopNumA+4],LoopNumA+5,SpinRecord[LoopNumA+5],LoopNumA+6,SpinRecord[LoopNumA+6],LoopNumA+7,SpinRecord[LoopNumA+7]);
    }*/
    //printf("loop \n");
    for(LoopNumA=0;LoopNumA<HoperatorNO*8;LoopNumA+=4)//4為一個operator幾個腳，在這邊Q會4*2，半邊半邊算
    {
        //printf("LoopNumA=%d ,SpinRecord[LoopNumA]=%d \n",LoopNumA,SpinRecord[LoopNumA]);
        if(SpinRecord[LoopNumA]>-1)
        { 
           
            //Goal=genrand64_real2();
            StartSpin=LoopNumA;
            CurrentSpin=LoopNumA;
            Check=1;
            if(genrand64_real2()<Chance)
            {
                SumSpin=0; 
                while (Check==1)
                {
                    if(CurrentSpin%2==0)
                    {
                        footSpin=CurrentSpin+1;                     
                    }
                    else
                    {
                        footSpin=CurrentSpin-1; 
                    }
                    
                    switch(Hoperator[CurrentSpin/8*5]%10)
                    {
                        case 0:
                           Hoperator[CurrentSpin/8*5]+=1;
                           break;
                        case 1:
                           Hoperator[CurrentSpin/8*5]-=1;
                            break;
                        case 2:
                            if(CurrentSpin%8<4)
                            {
                                Hoperator[CurrentSpin/8*5]+=3;
                            }
                            else
                            {
                                Hoperator[CurrentSpin/8*5]+=4;
                            }
                            break;
                        case 5:
                            if(CurrentSpin%8<4)
                            {
                                Hoperator[CurrentSpin/8*5]-=3;
                            }
                            else
                            {
                                Hoperator[CurrentSpin/8*5]+=4;
                            }
                            break;
                        case 6:
                            if(CurrentSpin%8<4)
                            {
                                Hoperator[CurrentSpin/8*5]+=3;
                            }
                            else
                            {
                                Hoperator[CurrentSpin/8*5]-=4;
                            }
                            break;
                        case 9:
                            if(CurrentSpin%8<4)
                            {
                                Hoperator[CurrentSpin/8*5]-=3;
                            }
                            else
                            {
                                Hoperator[CurrentSpin/8*5]-=4;
                            }
                            break;                       
                    }
                    SpinRecord[CurrentSpin]=-1;
                    CurrentSpin=SpinRecord[footSpin];
                    SpinRecord[footSpin]=-1;
                    SingleFoot=footSpin%8;
                    HSpin=Hoperator[(long long)(footSpin/8*5)+2*(long long)(SingleFoot/4)+SingleFoot%2+1];
                    
                    /*if(HSpin>64)
                    {
                        printf("footSpin=%d SingleFoot=%d footSpin/8=%d  SingleFoot/4=%d SingleFoot%2=%d \n",footSpin,SingleFoot,footSpin/8,SingleFoot/4,SingleFoot%2);
                        printf("%2d ,H=%3d  ,L=%3d  ,R=%3d ,L2=%3d  ,R2=%3d\n",footSpin/8*5, Hoperator[footSpin/8*5], Hoperator[footSpin/8*5+1], Hoperator[footSpin/8*5+2], Hoperator[footSpin/8*5+3], Hoperator[footSpin/8*5+4]);
                        system("pause");
                    }*/
                    //printf("footSpin=%d SingleFoot=%d footSpin/8=%d  SingleFoot/4=%d SingleFoot%2=%d \n",footSpin,SingleFoot,footSpin/8,SingleFoot/4,SingleFoot%2);
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
                    SingleFoot=footSpin%8;
                    HSpin=Hoperator[(long long)(footSpin/8*5)+2*(long long)(SingleFoot/4)+SingleFoot%2+1];

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
            if(SpinRecord[FirstSpin[LoopNumA]]==-1)
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
