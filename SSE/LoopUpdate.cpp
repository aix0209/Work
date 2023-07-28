void LoopUpdate(double* SpinSystem,double* BondNOsystem,long long* Hoperator,long long &HNO,long long &SpinNO,long long &BondNO,long long &HoperatorNO)
{
    long long LoopNumA,LoopNumB,LoopNumC,LoopNumD;
    long long LeftSpin,RightSpin;
    long long *SpinRecord= NULL,*FirstSpin= NULL,*LastSpin= NULL;
    long long StartSpin;
    long long CurrentSpin,footSpin,Check,Hop,HLeft,HRight,SpinNumber;
    double Chance,Goal;
    //srand(time(NULL)*rand());
    SpinRecord=(long long *)malloc((HoperatorNO*4+1)*sizeof(long long*));
    FirstSpin=(long long *)malloc((SpinNO+1)*sizeof(long long*));
    LastSpin=(long long *)malloc((SpinNO+1)*sizeof(long long*));
    memset(SpinRecord,-1,(HoperatorNO*4)*sizeof(long long*));
    
    memset(FirstSpin,-1,SpinNO*sizeof(long long*));
    memset(LastSpin,-1,SpinNO*sizeof(long long*));
    SpinRecord[HoperatorNO*4]=-999;
    FirstSpin[SpinNO]=-999;
    LastSpin[SpinNO]=-999;
    Chance=0.50;
    //建構vertex operator的腳
    for (LoopNumA=0;LoopNumA<HoperatorNO*3;LoopNumA+=3)
    {
        Hop=Hoperator[LoopNumA];
        HLeft=Hoperator[LoopNumA+1];
        HRight=Hoperator[LoopNumA+2];
        SpinNumber=LoopNumA/3*4;
        if(Hop!=-1)
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
        else
        {
            for(LoopNumB=0;LoopNumB<4;LoopNumB+=1)
            {
                SpinRecord[SpinNumber+LoopNumB]=-1;
            }
        }
    }
    for(LoopNumA=0;LoopNumA<SpinNO;LoopNumA+=1)
    {
        if(FirstSpin[LoopNumA]!=-1)
        {
            SpinRecord[FirstSpin[LoopNumA]]=LastSpin[LoopNumA];
            SpinRecord[LastSpin[LoopNumA]]=FirstSpin[LoopNumA];
        }
        
    }
    for(LoopNumA=0;LoopNumA<HoperatorNO*4;LoopNumA+=4)
    {
        
        if(SpinRecord[LoopNumA]>-1)
        { 
            
            //Goal=genrand64_real2();
            StartSpin=LoopNumA;
            CurrentSpin=LoopNumA;
            Check=1;
            if(genrand64_real2()<Chance)
            {
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
                    
                   // printf("%d \n",Hoperator[CurrentSpin/4*3]);
                    if(Hoperator[CurrentSpin/4*3]%2==0) 
                    {
                        Hoperator[CurrentSpin/4*3]+=1;
                    }
                    else
                    {
                        Hoperator[CurrentSpin/4*3]-=1;
                    }
                    SpinRecord[CurrentSpin]=-1;
                    CurrentSpin=SpinRecord[footSpin];
                    SpinRecord[footSpin]=-1;
                    if(CurrentSpin==StartSpin)
                    {
                        Check=0;
                    }
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
                }
          
            }
        }
    }
       
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
    free(SpinRecord);
    free(FirstSpin);
    free(LastSpin);
    SpinRecord=NULL;
    FirstSpin=NULL;
    LastSpin=NULL;
}


void LoopUpdate_TempW(double* SpinSystem,double* BondNOsystem,long long* Hoperator,long long &HNO,\
                    long long &SpinNO,long long &BondNO,long long &HoperatorNO,double &TempW)
    {
    long long LoopNumA,LoopNumB,LoopNumC,LoopNumD;
    long long LeftSpin,RightSpin;
    long long *SpinRecord= NULL,*FirstSpin= NULL,*LastSpin= NULL;
    long long StartSpin,HSpin;
    long long CurrentSpin,footSpin,Check,Hop,HLeft,HRight,SpinNumber,SingleFoot,SingleCurrent;
    double Chance,Goal,SumSpin;
    //srand(time(NULL)*rand());
    SpinRecord=(long long *)malloc((HoperatorNO*4+1)*sizeof(long long*));
    FirstSpin=(long long *)malloc((SpinNO+1)*sizeof(long long*));
    LastSpin=(long long *)malloc((SpinNO+1)*sizeof(long long*));
    memset(SpinRecord,-1,(HoperatorNO*4)*sizeof(long long*));
    
    memset(FirstSpin,-1,SpinNO*sizeof(long long*));
    memset(LastSpin,-1,SpinNO*sizeof(long long*));
    SpinRecord[HoperatorNO*4]=-999;
    FirstSpin[SpinNO]=-999;
    LastSpin[SpinNO]=-999;
    Chance=0.50;
    //建構vertex operator的腳
    for (LoopNumA=0;LoopNumA<HoperatorNO*3;LoopNumA+=3)
    {
        Hop=Hoperator[LoopNumA];
        HLeft=Hoperator[LoopNumA+1];
        HRight=Hoperator[LoopNumA+2];
        SpinNumber=LoopNumA/3*4;
        if(Hop!=-1)
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
        else
        {
            for(LoopNumB=0;LoopNumB<4;LoopNumB+=1)
            {
                SpinRecord[SpinNumber+LoopNumB]=-1;
            }
        }
    }
    for(LoopNumA=0;LoopNumA<SpinNO;LoopNumA+=1)
    {
        if(FirstSpin[LoopNumA]!=-1)
        {
            SpinRecord[FirstSpin[LoopNumA]]=LastSpin[LoopNumA];
            SpinRecord[LastSpin[LoopNumA]]=FirstSpin[LoopNumA];
        }
        
    }
    for(LoopNumA=0;LoopNumA<HoperatorNO*4;LoopNumA+=4)
    {
        
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
                    
                   // printf("%d \n",Hoperator[CurrentSpin/4*3]);
                    if(Hoperator[CurrentSpin/4*3]%2==0) 
                    {
                        Hoperator[CurrentSpin/4*3]+=1;
                    }
                    else
                    {
                        Hoperator[CurrentSpin/4*3]-=1;
                    }
                    SpinRecord[CurrentSpin]=-1;
                    CurrentSpin=SpinRecord[footSpin];
                    SpinRecord[footSpin]=-1;
                    SingleFoot=footSpin%4;
                    HSpin=Hoperator[(long long)(footSpin/4*3)+SingleFoot%2+1];
                    if(footSpin%4<2)
                    {

                        if(FirstSpin[HSpin]==footSpin)
                        {
                           SumSpin+=SpinSystem[HSpin*3+1];

                        }
                    }
                    else
                    {
                        if(LastSpin[HSpin]==footSpin)
                        {
                           SumSpin+=SpinSystem[HSpin*3+1];

                            
                        }
                        
                    }
                    if(CurrentSpin==StartSpin)
                    {
                        Check=0;
                    }
                }
                TempW+=SumSpin*SumSpin*0.25;
            }
            else
            {
                while(Check==1)
                {
                    SumSpin=0;
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
                    SingleFoot=footSpin%4;
                    HSpin=Hoperator[(long long)(footSpin/4*3)+SingleFoot%2+1];
                    if(footSpin%4<2)
                    {

                        if(FirstSpin[HSpin]==footSpin)
                        {
                           SumSpin+=SpinSystem[HSpin*3+1];

                        }
                    }
                    else
                    {
                        if(LastSpin[HSpin]==footSpin)
                        {
                           SumSpin+=SpinSystem[HSpin*3+1];

                            
                        }
                        
                    }
                    if(CurrentSpin==StartSpin)
                    {
                        Check=0;
                    }      
                }
                TempW+=SumSpin*SumSpin*0.25;
          
            }
        }
    }
       
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
        TempW+=SpinSystem[SpinNumber+1]*SpinSystem[SpinNumber+1]*0.25;
    }
    free(SpinRecord);
    free(FirstSpin);
    free(LastSpin);
    SpinRecord=NULL;
    FirstSpin=NULL;
    LastSpin=NULL;
}
