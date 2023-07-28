void LoopUpdateJQ3_Spin1_TempW(double* SpinSystem,double* BondNOsystem,\
                    long long* Hoperator,long long &HNO,\
                    long long &SpinNO,long long &BondNO,long long &HoperatorNO,\
                    double &TempW,long long* BondNORecord)
{
    long long LoopNumA,LoopNumB,LoopNumC,LoopNumD;
    long long LeftSpin,RightSpin,LeftSpin2,RightSpin2,LeftSpin3,RightSpin3;
    long long *SpinRecord= NULL,*FirstSpin= NULL,*LastSpin= NULL,*HSpinLR = NULL, *SpinNumber=NULL, *FootTemp=NULL;
    long long StartSpin,HopNO,HSpin,SwitchNO,SpinNumber_NO;
    long long CurrentSpin,footSpin,Check,Hop,HLeft,HRight,HLeft2,HRight2,HLeft3,HRight3,SingleFoot,SingleCurrent;
    double Chance,Goal,SumSpin;
    //srand(time(NULL)*rand());
    SpinRecord=(long long *)malloc((HoperatorNO*2*12+1)*sizeof(long long*));
    FirstSpin=(long long *)malloc((SpinNO+1)*sizeof(long long*));
    LastSpin=(long long *)malloc((SpinNO+1)*sizeof(long long*));
    HSpinLR=(long long *)malloc((6*2+1)*sizeof(long long*));//每個Spin都記是否為Ferromagnetic
    SpinNumber=(long long *)malloc((3+1)*sizeof(long long*));
    FootTemp=(long long *)malloc((4+1)*sizeof(long long*));
    memset(SpinRecord,-1,(HoperatorNO*2*12)*sizeof(long long*));
    memset(FirstSpin,-1,SpinNO*sizeof(long long*));
    memset(LastSpin,-1,SpinNO*sizeof(long long*));
    memset(HSpinLR,-1,(6*2+1)*sizeof(long long*));
    memset(SpinNumber,-1,(3+1)*sizeof(long long*));
    memset(FootTemp,-1,(4+1)*sizeof(long long*));
    FootTemp[0]=3;
    FootTemp[1]=1;
    FootTemp[2]=-1;
    FootTemp[3]=-3;
    
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
       memset(HSpinLR,-1,(6*2)*sizeof(long long*));
        //printf("HoperatorNO=%d,LoopNumA=%d \n",HoperatorNO,LoopNumA);
        //printf("Hop=%d,HLeft=%d,HRight=%d,HLeft2=%d,HRight2=%d \n",Hoperator[LoopNumA],Hoperator[LoopNumA+1],Hoperator[LoopNumA+2],Hoperator[LoopNumA+3],Hoperator[LoopNumA+4]);
        //printf("Check Loop-1\n");
        Hop=Hoperator[LoopNumA];
        if (BondNORecord[((long long)(Hop/15))*7]>-1)
        {
            if(BondNORecord[((long long)(Hop/15))*7]==0)
            {
                HSpinLR[0] = BondNORecord[((long long)(Hop/15))*7];
                HSpinLR[2] = BondNORecord[((long long)(Hop/15))*7];  
                //printf("%d %d \n",HSpinLR[0],HSpinLR[2]);  
            }
            else
            {
                HSpinLR[(BondNORecord[((long long)(Hop/15))*7]-1)*4]= BondNORecord[((long long)(Hop/15))*7];
                HSpinLR[(BondNORecord[((long long)(Hop/15))*7]-1)*4+2]= BondNORecord[((long long)(Hop/15))*7];
            }
              
        }
        for(LoopNumB=0;LoopNumB<6;LoopNumB+=1)
        {
          

          HSpinLR[LoopNumB*2+1] = Hoperator[LoopNumA+LoopNumB+1];

        }       
        /*
        HLeft=Hoperator[LoopNumA+1];
        HRight=Hoperator[LoopNumA+2];
        HLeft2=Hoperator[LoopNumA+3];
        HRight2=Hoperator[LoopNumA+4];
        HLeft3=Hoperator[LoopNumA+5];
        HRight3=Hoperator[LoopNumA+6];
        */
        for(LoopNumB = 0 ; LoopNumB < 3 ; LoopNumB+=1)
        {
            SpinNumber[LoopNumB] = (long long)(LoopNumA/7)*12+4*LoopNumB;
        }
        /*
        SpinNumber=(long long)(LoopNumA/7)*12;
        SpinNumber2=(long long)(LoopNumA/7)*12+4;
        SpinNumber3=(long long)(LoopNumA/7)*12+8;
        */
        
        //Q3 0-3第一個pair 4-7 第二個pair 8-11第三個pair  
        if(Hop!=-1)
        {
            //printf("%d , %d\n",Hop,Hop%10); 
            if(Hop%15<2)
            {
                //printf("%d , %d\n",Hop,Hop%10);
                //LeftSpin=LastSpin[HLeft];
                //RightSpin=LastSpin[HRight];
                if(HSpinLR[0] >-1)
                {
                    for(LoopNumB=0 ; LoopNumB < 2 ; LoopNumB+=1)
                    {
                        SpinRecord[(SpinNumber[0]+LoopNumB)*2]=HSpinLR[LoopNumB*2];
                        SpinRecord[(SpinNumber[0]+LoopNumB+2)*2]=HSpinLR[LoopNumB*2]; 
                    }
                        
                                        
                } 
                
                
                for(LoopNumB=0 ; LoopNumB < 2 ; LoopNumB+=1)
                {
                    if(LastSpin[HSpinLR[LoopNumB*2+1]]!=-1)
                    {
                        SpinRecord[(SpinNumber[0]+LoopNumB)*2+1]=LastSpin[HSpinLR[LoopNumB*2+1]];
                        SpinRecord[LastSpin[HSpinLR[LoopNumB*2+1]]*2+1]=SpinNumber[0]+LoopNumB;
                        //printf("%3d %3d \n",SpinRecord[(SpinNumber[0]+LoopNumB)*2+1], SpinRecord[LastSpin[HSpinLR[LoopNumB*2+1]]*2+1]);
                        /*
                        if(HSpinLR[LoopNumB*2] !=-1)
                        {
                           //printf("Spin1");
                           SpinRecord[(SpinNumber[0]+LoopNumB)*2]=HSpinLR[LoopNumB*2];
                           ///SpinRecord[LastSpin[HSpinLR[LoopNumB*2+1]]*2]=HSpinLR[LoopNumB*2];
                        }
                        */
                        
                    }
                    else
                    {
                        FirstSpin[HSpinLR[LoopNumB*2+1]]=SpinNumber[0]+LoopNumB ;
                        /*
                        if(HSpinLR[LoopNumB*2] >-1)
                        {
                           //printf("Spin1");
                           SpinRecord[(SpinNumber[0]+LoopNumB)*2]=HSpinLR[LoopNumB*2];
                           SpinRecord[(SpinNumber[0]+LoopNumB+2)*2]=HSpinLR[LoopNumB*2];
                        }
                        */                        
                    }
                    LastSpin[HSpinLR[LoopNumB*2+1]]=SpinNumber[0]+2+LoopNumB;
                }
                /*
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
                */               
            }
            else//JQBond
            {
                for(LoopNumC=0 ; LoopNumC < 3 ; LoopNumC+=1)
                {    
                    if(HSpinLR[LoopNumC*4] >-1)
                    {
                        for(LoopNumB=0 ; LoopNumB < 2 ; LoopNumB+=1)
                        {
                            SpinRecord[(SpinNumber[LoopNumC]+LoopNumB)*2]=HSpinLR[LoopNumC*4];
                            SpinRecord[(SpinNumber[LoopNumC]+LoopNumB+2)*2]=HSpinLR[LoopNumC*4];  
                        }
                    }
                } 
                
                
                for(LoopNumC=0 ; LoopNumC < 3 ; LoopNumC+=1)
                {
                    for(LoopNumB=0 ; LoopNumB < 2 ; LoopNumB+=1)
                    {
                        if(LastSpin[HSpinLR[LoopNumB*2+LoopNumC*4+1]]!=-1)
                        {
                            SpinRecord[(SpinNumber[LoopNumC]+LoopNumB)*2+1]=LastSpin[HSpinLR[LoopNumB*2+LoopNumC*4+1]];
                            SpinRecord[LastSpin[HSpinLR[LoopNumB*2+LoopNumC*4+1]]*2+1]=SpinNumber[LoopNumC]+LoopNumB;
                            //printf("%3d %3d \n",SpinRecord[(SpinNumber[LoopNumC]+LoopNumB)*2+1],SpinRecord[LastSpin[HSpinLR[LoopNumB*2+LoopNumC*4+1]]*2+1]);
                            /*
                            if(HSpinLR[LoopNumB*2+LoopNumC*4]!=-1)
                            {
                               //printf("Spin1");
                               SpinRecord[(SpinNumber[LoopNumC]+LoopNumB)*2]=HSpinLR[LoopNumB*2+LoopNumC*4];
                               //SpinRecord[LastSpin[HSpinLR[LoopNumB*2+LoopNumC*4+1]]*2]=HSpinLR[LoopNumB*2+LoopNumC*4];
                            }
                            * */
                        }
                        else
                        {
                            FirstSpin[HSpinLR[LoopNumB*2+LoopNumC*4+1]]=SpinNumber[LoopNumC]+LoopNumB ;
                            /*
                            if(HSpinLR[LoopNumB*2+LoopNumC*4]>-1)
                            {
                               //printf("Spin1");
                               SpinRecord[(SpinNumber[LoopNumC]+LoopNumB)*2]=HSpinLR[LoopNumB*2+LoopNumC*4];
                               SpinRecord[(SpinNumber[LoopNumC]+LoopNumB+2)*2]=HSpinLR[LoopNumB*2+LoopNumC*4];
                            }
                            */                            
                        }
                        LastSpin[HSpinLR[LoopNumB*2+LoopNumC*4+1]]=SpinNumber[LoopNumC]+2+LoopNumB;
                    }                    
                }
                /*           
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
                */
            }
 
        }
        else
        {
            //continue;
            
            for(LoopNumB=0;LoopNumB<12;LoopNumB+=1)
            {

                SpinRecord[(SpinNumber[0]+LoopNumB)*2]=-1;
            }
            
        }
    }
    //printf("vertex-1 \n");
    for(LoopNumA=0;LoopNumA<SpinNO;LoopNumA+=1)
    {
        if(FirstSpin[LoopNumA]!=-1)
        {
            SpinRecord[FirstSpin[LoopNumA]*2+1]=LastSpin[LoopNumA];
            SpinRecord[LastSpin[LoopNumA]*2+1]=FirstSpin[LoopNumA];
        }
        
    }
    /*    
    for(LoopNumA=0;LoopNumA<SpinNO;LoopNumA+=1)
    {
        if(FirstSpin[LoopNumA]!=-1)
        {
            SpinRecord[FirstSpin[LoopNumA]]=LastSpin[LoopNumA];
            SpinRecord[LastSpin[LoopNumA]]=FirstSpin[LoopNumA];
        }
        
    }
    */
 
    for(LoopNumA=0;LoopNumA<HoperatorNO*12;LoopNumA+=2)//4為一個operator幾個腳，在這邊Q會4*3，半邊半邊算
    {
        if(SpinRecord[LoopNumA*2+1]>-1)
        { 
            StartSpin=LoopNumA;
            CurrentSpin=LoopNumA;
            Check=1;
            if(genrand64_real2()<0.5)
            {
                
                SumSpin=0; 
                while (Check==1)
                {
                    if(SpinRecord[CurrentSpin*2]<0)
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
                    }
                    else
                    {
                        footSpin=CurrentSpin+FootTemp[CurrentSpin%4];
                       
                    }
        /*
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
                    if(CurrentSpin%2==0)
                    {
                        footSpin=CurrentSpin+1;                     
                    }
                    else
                    {
                        footSpin=CurrentSpin-1; 
                    }
        */            
                    HopNO = ((long long)(CurrentSpin/12)*7);
                    SwitchNO = (long long)((CurrentSpin%12)/4);
                    //printf("%d %d %d\n",Hoperator[(long long)(CurrentSpin/12)*7]%15,CurrentSpin%12,(long long)(CurrentSpin%12/4));
                    
                    switch(Hoperator[HopNO]%15)//1091002 修正
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
//**********************************測試code************************************************//
                    /*
                    switch(Hoperator[(long long)(CurrentSpin/12)*7]%15)//1091002 修正
                    {
                        case 0:
                           Hoperator[(long long)(CurrentSpin/12)*7]+=1;
                           break;
                        case 1:
                           Hoperator[(long long)(CurrentSpin/12)*7]-=1;
                           break;
                        case 2:
              
                            switch((long long )((long long)(CurrentSpin%12/4)))
                            {
                                case 0:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=3;
                                    break;
                                case 1:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=4;
                                    break;
                                case 2:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=5;
                                    break;
                                                      
                            }
                            break;
                        case 5:
                            switch((long long )((long long)(CurrentSpin%12/4)))
                            {
                                case 0:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=3;
                                    break;
                                case 1:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=4;
                                    break;
                                case 2:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=5;
                                    break;
                            }
                            break;
                        case 6:
                            switch((long long )((long long)(CurrentSpin%12/4)))
                            {
                                case 0:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=3;
                                    break;
                                case 1:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=4;
                                    break;
                                case 2:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=5;
                                    break;
                            }
                            break;        
                        case 7:
                            switch((long long )((long long)(CurrentSpin%12/4)))
                            {
                                case 0:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=3;
                                    break;
                                case 1:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=4;
                                    break;
                                case 2:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=5;
                                    break;
                            }
                            break;
                        case 9:
                            switch((long long )((long long)(CurrentSpin%12/4)))
                            {
                                case 0:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=3;
                                    break;
                                case 1:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=4;
                                    break;
                                case 2:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=5;
                                    break;
                            }
                            break;
                        case 10:
                            switch((long long )((long long)(CurrentSpin%12/4)))
                            {
                                case 0:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=3;
                                    break;
                                case 1:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=4;
                                    break;
                                case 2:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=5;
                                    break;
                            }
                            break;
                        case 11:
                            switch((long long )((long long)(CurrentSpin%12/4)))
                            {
                                case 0:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=3;
                                    break;
                                case 1:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=4;
                                    break;
                                case 2:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=5;
                                    break;
                            }
                            break;
                        case 14:
                            switch((long long )((long long)(CurrentSpin%12/4)))
                            {
                                case 0:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=3;
                                    break;
                                case 1:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=4;
                                    break;
                                case 2:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=5;
                                    break;  
                            }
                            break;                           
                    }*/                    
//**********************************↑測試code↑************************************************//
                    SpinRecord[CurrentSpin*2]=-3;
                    SpinRecord[CurrentSpin*2+1]=-3;
                    CurrentSpin=SpinRecord[footSpin*2+1];
                    SpinRecord[footSpin*2]=-3;
                    SpinRecord[footSpin*2+1]=-3;
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
                    if(SpinRecord[CurrentSpin*2]<0)
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
                    }
                    else
                    {
                        footSpin=CurrentSpin+FootTemp[CurrentSpin%4];
                       
                    }                    
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
                    SpinRecord[CurrentSpin*2+1]=-2;
                    CurrentSpin=SpinRecord[footSpin*2+1];
                    SpinRecord[footSpin*2+1]=-2;
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
        SpinNumber_NO=LoopNumA*3;
        if(FirstSpin[LoopNumA]!=-1)
        {
            if(SpinRecord[FirstSpin[LoopNumA]*2+1]==-3)
            {
                SpinSystem[SpinNumber_NO+1]*=-1;
            }
        }
        else
        {
            //Goal=genrand64_real2();
            if(genrand64_real2()<0.5)
            {
                SpinSystem[SpinNumber_NO+1]*=-1; 
            }
            TempW+=SpinSystem[SpinNumber_NO+1]*SpinSystem[SpinNumber_NO+1]*0.25;
        }
    }
    //printf("loop end \n");
    //*SpinRecord= NULL,*FirstSpin= NULL,*LastSpin= NULL,*HSpinLR = NULL, *SpinNumber=NULL, *FootTemp=NULL;
    free(SpinRecord);
    free(FirstSpin);
    free(LastSpin);
    free(HSpinLR);
    free(SpinNumber);
    free(FootTemp);
    SpinRecord=NULL;
    FirstSpin=NULL;
    LastSpin=NULL;
    HSpinLR=NULL;
    SpinNumber=NULL;
    FootTemp=NULL;
    
}
void LoopUpdateJQ3_Spin1(double* SpinSystem,double* BondNOsystem,\
                    long long* Hoperator,long long &HNO,\
                    long long &SpinNO,long long &BondNO,long long &HoperatorNO,\
                    double &TempW,long long* BondNORecord)
{
    long long LoopNumA,LoopNumB,LoopNumC,LoopNumD;
    long long LeftSpin,RightSpin,LeftSpin2,RightSpin2,LeftSpin3,RightSpin3;
    long long *SpinRecord= NULL,*FirstSpin= NULL,*LastSpin= NULL,*HSpinLR = NULL, *SpinNumber=NULL, *FootTemp=NULL;
    long long StartSpin,HopNO,HSpin,SwitchNO,SpinNumber_NO;
    long long CurrentSpin,footSpin,Check,Hop,HLeft,HRight,HLeft2,HRight2,HLeft3,HRight3,SingleFoot,SingleCurrent;
    double Chance,Goal,SumSpin;
    //printf("test LoopUpdate-memset start");
    SpinRecord=(long long *)malloc((HoperatorNO*2*12+1)*sizeof(long long*));
    FirstSpin=(long long *)malloc((SpinNO+1)*sizeof(long long*));
    LastSpin=(long long *)malloc((SpinNO+1)*sizeof(long long*));
    HSpinLR=(long long *)malloc((6*2+1)*sizeof(long long*));//每個Spin都記是否為Ferromagnetic
    SpinNumber=(long long *)malloc((3+1)*sizeof(long long*));
    FootTemp=(long long *)malloc((4+1)*sizeof(long long*));
    memset(SpinRecord,-1,(HoperatorNO*2*12)*sizeof(long long*));
    memset(FirstSpin,-1,SpinNO*sizeof(long long*));
    memset(LastSpin,-1,SpinNO*sizeof(long long*));
    memset(SpinNumber,-1,3*sizeof(long long*));
    memset(FootTemp,-1,(4+1)*sizeof(long long*));
    FootTemp[0]=3;
    FootTemp[1]=1;
    FootTemp[2]=-1;
    FootTemp[3]=-3;
    //printf("test LoopUpdate-memset end");
    //SpinRecord[HoperatorNO*12+1]=-999;
    //FirstSpin[SpinNO]=-999;
    //LastSpin[SpinNO]=-999;
    Chance=0.50;
    //建構vertex operator的腳
    //printf("vertex \n");
    //printf("Check Loop-0\n");
     for (LoopNumA=0;LoopNumA<HoperatorNO*7;LoopNumA+=7)
    {
        memset(HSpinLR,-1,(6*2)*sizeof(long long*));
        //printf("HoperatorNO=%d,LoopNumA=%d \n",HoperatorNO,LoopNumA);
        //printf("Hop=%d,HLeft=%d,HRight=%d,HLeft2=%d,HRight2=%d \n",Hoperator[LoopNumA],Hoperator[LoopNumA+1],Hoperator[LoopNumA+2],Hoperator[LoopNumA+3],Hoperator[LoopNumA+4]);
        //printf("Check Loop-1\n");
        Hop=Hoperator[LoopNumA];
        if (BondNORecord[((long long)(Hop/15))*7]>-1)
        {
            if(BondNORecord[((long long)(Hop/15))*7]==0)
            {
                HSpinLR[0] = BondNORecord[((long long)(Hop/15))*7];
                HSpinLR[2] = BondNORecord[((long long)(Hop/15))*7];  
                //printf("Jbond %d %d \n",HSpinLR[0],HSpinLR[2]);  
            }
            else
            {
                //((long long)(Hop/15))*7]-1) Ferromagnetic Bond的位置
                HSpinLR[(BondNORecord[((long long)(Hop/15))*7]-1)*4]= BondNORecord[((long long)(Hop/15))*7];
                HSpinLR[(BondNORecord[((long long)(Hop/15))*7]-1)*4+2]= BondNORecord[((long long)(Hop/15))*7];
                //printf("Q Bond %d , %d \n", HSpinLR[(BondNORecord[((long long)(Hop/15))*7]-1)*2],HSpinLR[(BondNORecord[((long long)(Hop/15))*7]-1)*2+2]);
            }
              
        }
        for(LoopNumB=0;LoopNumB<6;LoopNumB+=1)
        {
          

          HSpinLR[LoopNumB*2+1] = Hoperator[LoopNumA+LoopNumB+1];

        }        
        
        //printf("Check Loop-2\n");
        /*
        HLeft=Hoperator[LoopNumA+1];
        HRight=Hoperator[LoopNumA+2];
        HLeft2=Hoperator[LoopNumA+3];
        HRight2=Hoperator[LoopNumA+4];
        HLeft3=Hoperator[LoopNumA+5];
        HRight3=Hoperator[LoopNumA+6];
        */
        for(LoopNumB = 0 ; LoopNumB < 3 ; LoopNumB+=1)
        {
            SpinNumber[LoopNumB] = ((long long)(LoopNumA/7))*12+4*LoopNumB;
        }
        /*
        SpinNumber=(long long)(LoopNumA/7)*12;
        SpinNumber2=(long long)(LoopNumA/7)*12+4;
        SpinNumber3=(long long)(LoopNumA/7)*12+8;
        */
        
        //Q3 0-3第一個pair 4-7 第二個pair 8-11第三個pair  
        if(Hop!=-1)
        {
            //printf("Check Loop-3\n");
            //printf("%d , %d\n",Hop,Hop%10); 
            if(Hop%15<2)
            {
                //printf("Check Loop-4-1\n");
                //printf("%d , %d\n",Hop,Hop%10);
                //LeftSpin=LastSpin[HLeft];
                //RightSpin=LastSpin[HRight];
                if(HSpinLR[0] >-1)
                {
                    for(LoopNumB=0 ; LoopNumB < 2 ; LoopNumB+=1)
                    {
                        SpinRecord[(SpinNumber[0]+LoopNumB)*2]=HSpinLR[LoopNumB*2];
                        SpinRecord[(SpinNumber[0]+LoopNumB+2)*2]=HSpinLR[LoopNumB*2]; 
                    }
                } 
                //printf("Check Loop-4-2\n");
                
                for(LoopNumB=0 ; LoopNumB < 2 ; LoopNumB+=1)
                {
                    if(LastSpin[HSpinLR[LoopNumB*2+1]]>-1)
                    {
                        //printf("Check Loop-4-2-1\n");
                        SpinRecord[(SpinNumber[0]+LoopNumB)*2+1]=LastSpin[HSpinLR[LoopNumB*2+1]];
                        SpinRecord[LastSpin[HSpinLR[LoopNumB*2+1]]*2+1]=SpinNumber[0]+LoopNumB;
                        //printf("%3d %3d \n",SpinRecord[(SpinNumber[0]+LoopNumB)*2+1], SpinRecord[LastSpin[HSpinLR[LoopNumB*2+1]]*2+1]);
                        /*
                        if(HSpinLR[LoopNumB*2] !=-1)
                        {
                           //printf("Spin1");
                           SpinRecord[(SpinNumber[0]+LoopNumB)*2]=HSpinLR[LoopNumB*2];
                           ///SpinRecord[LastSpin[HSpinLR[LoopNumB*2+1]]*2]=HSpinLR[LoopNumB*2];
                        }
                        */
                        //printf("Check Loop-4-2-2\n");
                        
                    }
                    else
                    {
                        FirstSpin[HSpinLR[LoopNumB*2+1]]=SpinNumber[0]+LoopNumB ;
                        /*
                        if(HSpinLR[LoopNumB*2] >-1)
                        {
                           //printf("Spin1");
                           SpinRecord[(SpinNumber[0]+LoopNumB)*2]=HSpinLR[LoopNumB*2];
                           SpinRecord[(SpinNumber[0]+LoopNumB+2)*2]=HSpinLR[LoopNumB*2];
                        }
                        */                        
                    }
                    LastSpin[HSpinLR[LoopNumB*2+1]]=SpinNumber[0]+2+LoopNumB;
                }
                /*
                for(LoopNumA=0;LoopNumA<16;LoopNumA+=1)
                {
                    if(FirstSpin[LoopNumA]>-1)
                    {
                        SpinRecord[(SpinNumber[0]+8+LoopNumB)]=-1;
                        
                    }
                    
                }
                */
                //printf("Check Loop-4-3\n");
                /*
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
                */               
            }
            else//JQBond
            {
                //printf("Check Loop-5-1\n");
                for(LoopNumC=0 ; LoopNumC < 3 ; LoopNumC+=1)
                {    
                    if(HSpinLR[LoopNumC*4] >-1)
                    {
                        for(LoopNumB=0 ; LoopNumB < 2 ; LoopNumB+=1)
                        {
                            SpinRecord[(SpinNumber[LoopNumC]+LoopNumB)*2]=HSpinLR[LoopNumC*4];
                            SpinRecord[(SpinNumber[LoopNumC]+LoopNumB+2)*2]=HSpinLR[LoopNumC*4];  
                        }
                    }
                }   
                
                //printf("Check Loop-5-2\n");
                for(LoopNumC=0 ; LoopNumC < 3 ; LoopNumC+=1)
                {
                    for(LoopNumB=0 ; LoopNumB < 2 ; LoopNumB+=1)
                    {
                        if(LastSpin[HSpinLR[LoopNumB*2+LoopNumC*4+1]]>-1)
                        {
                            SpinRecord[(SpinNumber[LoopNumC]+LoopNumB)*2+1]=LastSpin[HSpinLR[LoopNumB*2+LoopNumC*4+1]];
                            SpinRecord[LastSpin[HSpinLR[LoopNumB*2+LoopNumC*4+1]]*2+1]=SpinNumber[LoopNumC]+LoopNumB;
                            //printf("%3d %3d \n",SpinRecord[(SpinNumber[LoopNumC]+LoopNumB)*2+1],SpinRecord[LastSpin[HSpinLR[LoopNumB*2+LoopNumC*4+1]]*2+1]);
                            /*
                            if(HSpinLR[LoopNumB*2+LoopNumC*4]!=-1)
                            {
                               //printf("Spin1");
                               SpinRecord[(SpinNumber[LoopNumC]+LoopNumB)*2]=HSpinLR[LoopNumB*2+LoopNumC*4];
                               //SpinRecord[LastSpin[HSpinLR[LoopNumB*2+LoopNumC*4+1]]*2]=HSpinLR[LoopNumB*2+LoopNumC*4];
                            }
                            * */
                        }
                        else
                        {
                            FirstSpin[HSpinLR[LoopNumB*2+LoopNumC*4+1]]=SpinNumber[LoopNumC]+LoopNumB ;
                            /*
                            if(HSpinLR[LoopNumB*2+LoopNumC*4]>-1)
                            {
                               //printf("Spin1");
                               SpinRecord[(SpinNumber[LoopNumC]+LoopNumB)*2]=HSpinLR[LoopNumB*2+LoopNumC*4];
                               SpinRecord[(SpinNumber[LoopNumC]+LoopNumB+2)*2]=HSpinLR[LoopNumB*2+LoopNumC*4];
                            }
                            */                            
                        }
                        LastSpin[HSpinLR[LoopNumB*2+LoopNumC*4+1]]=SpinNumber[LoopNumC]+2+LoopNumB;
                    }                    
                    
                }
                //printf("Check Loop-5-3\n");

                /*           
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
                */
            }
 
        }
        else
        {
            //continue;
            
            for(LoopNumB=0;LoopNumB<12;LoopNumB+=1)
            {

                SpinRecord[(SpinNumber[0]+LoopNumB)*2]=-1;
                SpinRecord[(SpinNumber[0]+LoopNumB)*2+1]=-1;
                
            }
            
            
        }
    }

    for(LoopNumA=0;LoopNumA<SpinNO;LoopNumA+=1)
    {
        if(FirstSpin[LoopNumA]>-1)
        {
            SpinRecord[LastSpin[LoopNumA]*2+1]=FirstSpin[LoopNumA];
            SpinRecord[FirstSpin[LoopNumA]*2+1]=LastSpin[LoopNumA];
            
        }
        
    }
    /*
    for(LoopNumA=0;LoopNumA <HoperatorNO*12;LoopNumA=LoopNumA+12)
    {
        //printf("%2d ,H=%3d  ,L=%3d  ,R=%3d \n",LoopNumA/3, Hoperator[LoopNumA], Hoperator[LoopNumA+1], Hoperator[LoopNumA+2]);
        
        //if(Hoperator[(long long)LoopNumA/12*7]!=-1)
        //{
            printf("%2d  ",LoopNumA/12) ;
            for(LoopNumB=0;LoopNumB <12;LoopNumB+=1)
            {
                printf("%5d[%5d]%2d ",LoopNumA+LoopNumB,SpinRecord[LoopNumA*2+LoopNumB*2+1],SpinRecord[LoopNumA*2+LoopNumB*2]);
          
            }
        //}
        printf("\n ") ;
    }
    system("pause");
    */
    /*    
    for(LoopNumA=0;LoopNumA<SpinNO;LoopNumA+=1)
    {
        if(FirstSpin[LoopNumA]!=-1)
        {
            SpinRecord[FirstSpin[LoopNumA]]=LastSpin[LoopNumA];
            SpinRecord[LastSpin[LoopNumA]]=FirstSpin[LoopNumA];
        }
        
    }
    */
    //printf("Check Loop-6\n");
    for(LoopNumA=0;LoopNumA<HoperatorNO*12;LoopNumA+=4)//4為一個operator幾個腳，在這邊Q會4*3，半邊半邊算
    {
        //printf("%d \n",LoopNumA);
        if(SpinRecord[LoopNumA*2+1]>-1)
        { 
            
            StartSpin=LoopNumA;
            CurrentSpin=LoopNumA;
            Check=1;
            if(genrand64_real2()<0.5)
            {
                //printf("Check Loop-6-1\n");
                //printf("*****  chance  ******\n");
                SumSpin=0; 
                while (Check==1)
                {
                    
                    //printf("Check Loop-6-1\n");
                    //printf("SpinType %2d CurrentSpin=%3d \n",SpinRecord[CurrentSpin*2],CurrentSpin);
                    if(SpinRecord[CurrentSpin*2]<0)
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
                    }
                    else
                    {
                        //printf("SpinType %2d CurrentSpin=%3d \n",SpinRecord[CurrentSpin*2],CurrentSpin);
                        footSpin=CurrentSpin+FootTemp[CurrentSpin%4];
                        //printf("SpinType %2d footSpin=%3d \n",SpinRecord[footSpin*2],footSpin);
                    }
                    ///printf("SpinType %2d footSpin=%3d \n",SpinRecord[footSpin*2],footSpin);
                    //printf("  %3d   %3d   ",CurrentSpin,footSpin);
        /*
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
                    SwitchNO = ((long long)((CurrentSpin%12)/4));
                    //printf("%d %d %d\n",HopNO,Hoperator[HopNO]%15,SwitchNO);
                    
                    switch(Hoperator[HopNO]%15)//1091002 修正
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
                           // printf("+++++++ %d %d %d\n",HopNO,Hoperator[HopNO]%15,SwitchNO);
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
                        default:
                            system("pause");                        
                    }
                    
                    SpinRecord[CurrentSpin*2]=-3;
                    SpinRecord[CurrentSpin*2+1]=-3;
                    
                    CurrentSpin=SpinRecord[footSpin*2+1];
                    SpinRecord[footSpin*2]=-3;
                    SpinRecord[footSpin*2+1]=-3;
                    //printf("SpinType %2d CurrentSpin=%3d \n",SpinRecord[CurrentSpin*2],CurrentSpin);
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
                //printf("\n");
                //printf("\n");
            }
            else
            {
                //printf("Check Loop-6-2\n");
                SumSpin=0;
                //printf("*****  no chance  ****** \n");
                while(Check==1)
                {
                    //printf("Check Loop-6-2\n");
                    //printf("SpinType %2d CurrentSpin=%3d \n",SpinRecord[CurrentSpin*2],CurrentSpin);
                    if(SpinRecord[CurrentSpin*2]<0)
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
                    }
                    else
                    {
                        footSpin=CurrentSpin+FootTemp[CurrentSpin%4];
                       
                    }
                    //printf("  %3d   %3d   ",CurrentSpin,footSpin);
                    //printf("Check Loop-6-2-1\n");
                    //printf("SpinType %2d footSpin=%3d \n",SpinRecord[footSpin*2],footSpin);                    
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
                    SpinRecord[CurrentSpin*2]=-2;
                    SpinRecord[CurrentSpin*2+1]=-2;
                    
                    CurrentSpin=SpinRecord[footSpin*2+1];
                    SpinRecord[footSpin*2]=-2;
                    SpinRecord[footSpin*2+1]=-2;
                   /// printf("Check Loop-6-2-2\n");
                    /*
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
                    */
                    if(CurrentSpin==StartSpin)
                    {
                        Check=0;
                    }
                    
                    //printf("loop x-1 CurrentSpin %d footSpin %d\n",CurrentSpin,footSpin);      
                }
                //printf("\n");
                //printf("\n");
                //TempW+=SumSpin*SumSpin*0.25;
          
            }
        }
        
    }
    /*
    printf("***************************************************************************************\n");
    for(LoopNumA=0;LoopNumA <HoperatorNO*12;LoopNumA=LoopNumA+12)
    {
        //printf("%2d ,H=%3d  ,L=%3d  ,R=%3d \n",LoopNumA/3, Hoperator[LoopNumA], Hoperator[LoopNumA+1], Hoperator[LoopNumA+2]);
        
        //if(Hoperator[(long long)LoopNumA/12*7]!=-1)
        //{
            printf("%2d  ",LoopNumA/12) ;
            for(LoopNumB=0;LoopNumB <12;LoopNumB+=1)
            {
                printf("%5d[%5d]%2d ",LoopNumA+LoopNumB,SpinRecord[LoopNumA*2+LoopNumB*2+1],SpinRecord[LoopNumA*2+LoopNumB*2]);
          
            }
        //}
        printf("\n ") ;
    }
    */   
    /*
    for(LoopNumA=0;LoopNumA <HoperatorNO;LoopNumA=LoopNumA+1)
    {
        //printf("%2d ,H=%3d  ,L=%3d  ,R=%3d \n",LoopNumA/3, Hoperator[LoopNumA], Hoperator[LoopNumA+1], Hoperator[LoopNumA+2]);
        for(LoopNumB=0;LoopNumB <12;LoopNumB+=1)
        {
            if(SpinRecord[LoopNumA*12+LoopNumB*2+1]>-1 )
            {
            //printf("%d  %d  ",LoopNumA,SpinRecord[LoopNumA]) ;

                printf("%4d[%4d]%d \n",LoopNumA+LoopNumB,SpinRecord[LoopNumA*12+LoopNumB*2+1],SpinRecord[LoopNumA*12+LoopNumB*2]);
          
            }
            
        }
        
    }
    */
    //printf("\n");
    //printf("\n");
    /*
    for(LoopNumA=0;LoopNumA <SpinNO;LoopNumA=LoopNumA+1)
    {
        //printf("%2d ,H=%3d  ,L=%3d  ,R=%3d \n",LoopNumA/3, Hoperator[LoopNumA], Hoperator[LoopNumA+1], Hoperator[LoopNumA+2]);
        
       
            //printf("Spin=%d  FirstSpin=%d  ",LoopNumA,FirstSpin[LoopNumA]) ;
             /*for(LoopNumB=0;LoopNumB <12;LoopNumB+=1)
            {
                printf("%4d[%4d]%d ",LoopNumA+LoopNumB,SpinRecord[LoopNumA*2+LoopNumB*2+1],SpinRecord[LoopNumA*2+LoopNumB*2]);
          
            }

        //printf("\n ") ;
    }
    */
    /*
    for(LoopNumA=0;LoopNumA <SpinNO;LoopNumA=LoopNumA+1)
    {
        //printf("%2d ,H=%3d  ,L=%3d  ,R=%3d \n",LoopNumA/3, Hoperator[LoopNumA], Hoperator[LoopNumA+1], Hoperator[LoopNumA+2]);

        printf("Spin=%4d  %4d  \n",LoopNumA,FirstSpin[LoopNumA]);

        //printf("\n ") ;
    }
    */
    //printf("\n");
    //printf("\n");
    ///printf("Check Loop-7\n");
    //printf("%f \n",TempW);
    //printf("loop 1 \n");   
    for(LoopNumA=0;LoopNumA<SpinNO;LoopNumA+=1)
    {
        SpinNumber_NO=LoopNumA*3;
        if(FirstSpin[LoopNumA]!=-1)
        {
            if(SpinRecord[FirstSpin[LoopNumA]*2+1]==-3)
            {
                SpinSystem[SpinNumber_NO+1]*=(-1);
            }
        }
        else
        {
            //Goal=genrand64_real2();
            if(genrand64_real2()<0.5)
            {
                SpinSystem[SpinNumber_NO+1]*=-1; 
            }
            //TempW+=SpinSystem[SpinNumber_NO+1]*SpinSystem[SpinNumber_NO+1]*0.25;
        }
    }
    //printf("loop end \n");
    //*SpinRecord= NULL,*FirstSpin= NULL,*LastSpin= NULL,*HSpinLR = NULL, *SpinNumber=NULL, *FootTemp=NULL;
    free(SpinRecord);
    free(FirstSpin);
    free(LastSpin);
    free(HSpinLR);
    free(SpinNumber);
    free(FootTemp);
    SpinRecord=NULL;
    FirstSpin=NULL;
    LastSpin=NULL;
    HSpinLR=NULL;
    SpinNumber=NULL;
    FootTemp=NULL;
    
}
