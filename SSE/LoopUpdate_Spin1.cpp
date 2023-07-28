void LoopUpdate_Spin1_TempW(long long* SpinSystem,double* BondNOsystem,\
                    long long* Hoperator,long long &HNO,\
                    long long &SpinNO,long long &BondNO,long long &HoperatorNO,\
                    double &TempW,long long* BondNORecord,double* Pb)
{
    long long LoopNumA,LoopNumB,LoopNumC,LoopNumD;
    long long LeftSpin,RightSpin,LeftSpin2,RightSpin2,LeftSpin3,RightSpin3;
    long long *SpinRecord= NULL,*FirstSpin= NULL,*LastSpin= NULL,*HSpinLR = NULL, *SpinNumber=NULL, *FootTemp=NULL ,*HRecord=NULL,*SpinTemp=NULL ;
    long long StartSpin,HopNO,HSpin,SwitchNO,SpinNumber_NO,SpinTempA,SpinTempB,TempH;
    long long CurrentSpin,footSpin,Check,Hop,HLeft,HRight,HLeft2,HRight2,HLeft3,HRight3,SingleFoot,SingleCurrent,LoopCount;
    double Chance,Goal,SumSpin,PbP;
    FILE *File=NULL,*LoopFile=NULL;
    //srand(time(NULL)*rand());

    SpinRecord=(long long *)malloc((HoperatorNO*4+1)*sizeof(long long*));
    FirstSpin=(long long *)malloc((SpinNO+1)*sizeof(long long*));
    LastSpin=(long long *)malloc((SpinNO+1)*sizeof(long long*));
    HSpinLR=(long long *)malloc((2+1)*sizeof(long long*));//每個Spin都記是否為Ferromagnetic
    SpinNumber=(long long *)malloc((3+1)*sizeof(long long*));
    FootTemp=(long long *)malloc((4+1)*sizeof(long long*));
    SpinTemp=(long long *)malloc((SpinNO*3+1)*sizeof(long long*));
    //Pb=(double *)malloc((8*4)*sizeof(double*));
    HRecord=(long long *)malloc((HoperatorNO+1)*sizeof(long long*));
    memset(HRecord,-1,(HoperatorNO+1)*sizeof(long long*));
    memset(SpinRecord,-1,(HoperatorNO*4+1)*sizeof(long long*));
    memset(FirstSpin,-1,SpinNO*sizeof(long long*));
    memset(LastSpin,-1,SpinNO*sizeof(long long*));
    memset(HSpinLR,-1,(2+1)*sizeof(long long*));
    memset(SpinNumber,-1,(3+1)*sizeof(long long*));
    memset(FootTemp,-1,(4+1)*sizeof(long long*));
    memset(SpinTemp,-1,(SpinNO*3+1)*sizeof(long long*));
    for(LoopNumA=0;LoopNumA<40;LoopNumA+=1)
    {
        printf("Pb[%d] = %5f \n",LoopNumA,Pb[LoopNumA]);

    }
    /*
    // 0 0 dia
    Pb[0]=0.25;
    Pb[1]= 0.5;
    Pb[2]= 0.75;
    Pb[3]= 1.0;
    // 0 0 off
    Pb[4]=0.2;
    Pb[5]=0.4;
    Pb[6]=0.6;
    Pb[7]=1.0;
    // 1 0 dia
    Pb[8]=0.25;
    Pb[9]=0.5;
    Pb[10]=0.75;
    Pb[11]=1.0;
    // 1 0 off
    Pb[12]=0.25;
    Pb[13]=0.5;
    Pb[14]=0.75;
    Pb[15]=1.0;
    // 0 1 dia
    Pb[16]=0.2;
    Pb[17]=0.6;
    Pb[18]=0.8;
    Pb[19]=1.0;
    // 0 1 off
    Pb[20]=0.3333333;
    Pb[21]=0.6666667;
    Pb[22]=-1;
    Pb[23]=1.0;
    // 1 -1 dia
    Pb[24]=0.5;
    Pb[25]=0.75;
    Pb[26]=-1;
    Pb[27]=1.0;
    //1 -1 off
    Pb[28]=0.25;
    Pb[29]=0.5;
    Pb[30]=0.75;
    Pb[31]=1.0;
    */
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
    //printf("Build vertex \n");
    for(LoopNumA=0;LoopNumA<SpinNO;LoopNumA+=1)
    {
        SpinTemp[LoopNumA]=SpinSystem[LoopNumA];
    }

    for (LoopNumA=0;LoopNumA<HoperatorNO*3;LoopNumA+=3)
    {
        //printf("HoperatorNO=%d,LoopNumA=%d \n",HoperatorNO,LoopNumA);
        //printf("Hop=%d,HLeft=%d,HRight=%d,HLeft2=%d,HRight2=%d \n",Hoperator[LoopNumA],Hoperator[LoopNumA+1],Hoperator[LoopNumA+2],Hoperator[LoopNumA+3],Hoperator[LoopNumA+4]);

        //printf("HoperatorNO=%d,LoopNumA=%d \n",HoperatorNO,LoopNumA);
        //printf("Hop=%d,HLeft=%d,HRight=%d,HLeft2=%d,HRight2=%d \n",Hoperator[LoopNumA],Hoperator[LoopNumA+1],Hoperator[LoopNumA+2],Hoperator[LoopNumA+3],Hoperator[LoopNumA+4]);
        //printf("Check Loop-1\n");
        HRecord[(long long)(LoopNumA/3)]=Hoperator[LoopNumA];
        Hop=Hoperator[LoopNumA];

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
            SpinNumber[LoopNumB] = (long long)(LoopNumA/3)*4+LoopNumB*4;
        }
        /*
        SpinNumber=(long long)(LoopNumA/7)*12;
        SpinNumber2=(long long)(LoopNumA/7)*12+4;
        SpinNumber3=(long long)(LoopNumA/7)*12+8;
        */

        //Q3 0-3第一個pair 4-7 第二個pair 8-11第三個pair
        if(Hop!=-1)
        {
            //printf("Save HSpinLR \n");
            for(LoopNumB=0;LoopNumB<2;LoopNumB+=1)
            {

                //printf("%d \n",LoopNumA+1+LoopNumB);
                //printf("%d \n",Hoperator[LoopNumA+1+LoopNumB]);
                HSpinLR[LoopNumB] = Hoperator[LoopNumA+LoopNumB+1];

            }
            /*
            memset(HSpinLR,-1,(6*2)*sizeof(long long*));
            if(BondNORecord[((long long)(Hop>>4))*7]>-1)
            {
                if(BondNORecord[((long long)(Hop>>4))*7]==0)
                {
                    HSpinLR[0] = BondNORecord[((long long)(Hop>>4))*7];
                    HSpinLR[2] = BondNORecord[((long long)(Hop>>4))*7];
                    //printf("%d %d \n",HSpinLR[0],HSpinLR[2]);
                }
                else
                {
                    HSpinLR[(BondNORecord[((long long)(Hop>>4))*7]-1)*4]= BondNORecord[((long long)(Hop>>4))*7];
                    HSpinLR[(BondNORecord[((long long)(Hop>>4))*7]-1)*4+2]= BondNORecord[((long long)(Hop>>4))*7];
                }

            }
            for(LoopNumB=0;LoopNumB<6;LoopNumB+=1)
            {


              HSpinLR[LoopNumB*2+1] = Hoperator[LoopNumA+LoopNumB+1];

            }
            */
            //printf("%d , %d\n",Hop,Hop%10);

                //printf("%d , %d\n",Hop,Hop%10);
                //LeftSpin=LastSpin[HLeft];
                //RightSpin=LastSpin[HRight];
                /*
                if(HSpinLR[0] >-1)
                {
                    for(LoopNumB=0 ; LoopNumB < 2 ; LoopNumB+=1)
                    {
                        SpinRecord[(SpinNumber[0]+LoopNumB)*2]=HSpinLR[LoopNumB*2];
                        SpinRecord[(SpinNumber[0]+LoopNumB+2)*2]=HSpinLR[LoopNumB*2];
                    }


                }
                */
                //printf("Start Build \n");
                for(LoopNumB=0 ; LoopNumB < 2 ; LoopNumB+=1)
                {
                    if(LastSpin[HSpinLR[LoopNumB]]!=-1)
                    {
                        //printf("LastSpin \n");
                        SpinRecord[SpinNumber[0]+LoopNumB]=LastSpin[HSpinLR[LoopNumB]];
                        SpinRecord[LastSpin[HSpinLR[LoopNumB]]]=SpinNumber[0]+LoopNumB;
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
                        //printf("FirstSpin \n");
                        FirstSpin[HSpinLR[LoopNumB]]=SpinNumber[0]+LoopNumB ;
                        /*
                        if(HSpinLR[LoopNumB*2] >-1)
                        {
                           //printf("Spin1");
                           SpinRecord[(SpinNumber[0]+LoopNumB)*2]=HSpinLR[LoopNumB*2];
                           SpinRecord[(SpinNumber[0]+LoopNumB+2)*2]=HSpinLR[LoopNumB*2];
                        }
                        */
                    }
                    LastSpin[HSpinLR[LoopNumB]]=SpinNumber[0]+2+LoopNumB;
                }

        }
        else
        {
            //continue;

            for(LoopNumB=0;LoopNumB<4;LoopNumB+=1)
            {

                SpinRecord[(SpinNumber[0]+LoopNumB)]=-1;
            }

        }
    }
    //printf("Finish Build \n");
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
    for(LoopNumA=0;LoopNumA<SpinNO;LoopNumA+=1)
    {
        if(FirstSpin[LoopNumA]!=-1)
        {
            SpinRecord[FirstSpin[LoopNumA]]=LastSpin[LoopNumA];
            SpinRecord[LastSpin[LoopNumA]]=FirstSpin[LoopNumA];
        }

    }
    */
    File=fopen("VertexTable.txt","w");
    for(LoopNumA=0;LoopNumA<HoperatorNO*4;LoopNumA+=4)
    {
        fprintf(File,"%4d %4d ",(long long)LoopNumA/4,LoopNumA );
        //printf("%d ",(long long)LoopNumA/4);
        //printf("H = %6d  ",Hoperator[(long long)(LoopNumA/4)*3]);
        for(LoopNumB=0;LoopNumB<4;LoopNumB+=1)
        {
            fprintf(File,"%4d ",SpinRecord[LoopNumA+LoopNumB]);
            //printf("%4d ",SpinRecord[LoopNumA+LoopNumB]);
        }
        fprintf(File,"\n");
        //printf("\n");

    }
    fclose(File);
    //printf("Go Loop \n");
    LoopFile=fopen("LoopLog-1.txt","w");
    for(LoopNumA=0;LoopNumA<HoperatorNO*4;LoopNumA+=4)//4為一個operator幾個腳，在這邊Q會4*3，半邊半邊算
    {

        if(HRecord[(long long)(LoopNumA/4)]>-1 and SpinRecord[LoopNumA]>-1)
        {
            StartSpin=LoopNumA;
            CurrentSpin=LoopNumA;
            Check=1;
            SumSpin=0;
            //printf("************Start While %4d ************\n",LoopNumA);
            LoopCount=0;

            fprintf(LoopFile,"While Start \n");

            while (Check==1)
            {

                HRecord[(long long)(CurrentSpin/4)]=-1;
                HopNO = ((long long)(CurrentSpin/4*3));
                //HRecord[(long long)(HopNO/3)]=-1;
                PbP=genrand64_real2();
                //File=fopen("LoopLog.txt","a");
                //fprintf(File,"HopNO=%4d H=%4d (%4d,%4d) CurrentSpin=%4d PbP=%6f \n",(long long)HopNO/3,Hoperator[HopNO],Hoperator[HopNO]&7,Hoperator[HopNO]%8 ,CurrentSpin,PbP );
                TempH=Hoperator[HopNO]&7;
                SpinTempA=((CurrentSpin^1)%2);
                SpinTempB=(SpinTempA)^1;
                //printf("HopNO=%4d H=%4d (%4d,%4d) CurrentSpin=%4d PbP=%6f \n",(long long)HopNO/3,Hoperator[HopNO],SpinTempA,SpinTempB ,CurrentSpin,PbP );
                /*
                if(CurrentSpin<0 or (Hoperator[HopNO]&7)==4 or (Hoperator[HopNO]&7)==5)
                {
                printf("HopNO=%4d H=%4d (%4d,%4d) CurrentSpin=%4d PbP=%6f \n",(long long)HopNO/3,Hoperator[HopNO],Hoperator[HopNO]&7,Hoperator[HopNO]%8 ,CurrentSpin,PbP );
                }
                */
                //fclose(File);
                //switch((Hoperator[HopNO]&7))


                if((Hoperator[HopNO]&1)==0)
                {
                    if(SpinTemp[Hoperator[HopNO+1+SpinTempA]]*SpinTemp[Hoperator[HopNO+1+SpinTempB]]==0)
                    {
                        if(SpinTemp[Hoperator[HopNO+1+SpinTempA]]==SpinTemp[Hoperator[HopNO+1+SpinTempB]])
                        {//0 ,0 H=0

                            if(PbP<Pb[0])
                            {
                                footSpin=CurrentSpin;
                            }
                            else if (PbP<Pb[1])
                            {
                                //Hoperator[HopNO]+=3;
                                //************************

                                //***************************
                                if((CurrentSpin&3)<2)
                                {
                                    footSpin=CurrentSpin+2;
                                }
                                else
                                {
                                    footSpin=CurrentSpin-2;
                                }
                                if(FirstSpin[Hoperator[HopNO+1+SpinTempA]]==CurrentSpin or FirstSpin[Hoperator[HopNO+1+SpinTempA]]==footSpin)
                                {
                                    SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=1;
                                }
                                SpinTemp[Hoperator[HopNO+1+SpinTempA]*3+1]=1;


                            }
                            else if (PbP<Pb[2])
                            {
                                Hoperator[HopNO]^=1;
                                footSpin=CurrentSpin+FootTemp[(CurrentSpin&3)];
                                if(FirstSpin[Hoperator[HopNO+1+SpinTempA]]==CurrentSpin )
                                {
                                    SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=1;
                                }
                                if(FirstSpin[Hoperator[HopNO+1+SpinTempB]]==footSpin)
                                {
                                    SpinSystem[Hoperator[HopNO+1+SpinTempB]*3+1]=1;
                                }
                                SpinTemp[Hoperator[HopNO+1+SpinTempB]*3+1]=1;

                            }
                            else
                            {

                                Hoperator[HopNO]^=1;
                                footSpin=(CurrentSpin^1);
                                if(FirstSpin[Hoperator[HopNO+1+SpinTempA]]==CurrentSpin )
                                {
                                    SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=1;
                                }
                                if(FirstSpin[Hoperator[HopNO+1+SpinTempB]]==footSpin)
                                {
                                    SpinSystem[Hoperator[HopNO+1+SpinTempB]*3+1]=-1;
                                }
                                SpinTemp[Hoperator[HopNO+1+SpinTempA]*3+1]=1;
                                SpinTemp[Hoperator[HopNO+1+SpinTempB]*3+1]=-1;


                            }

                        }
                        else
                        //0,1 H=0 Pb[16-19]
                        {
                            if(SpinTemp[Hoperator[HopNO+1+SpinTempA]]!=0)
                            {
                                if(PbP<Pb[12])
                                {
                                    footSpin=CurrentSpin;
                                }
                                else if (PbP<Pb[13])
                                {
                                    //Hoperator[HopNO]+=3;
                                    //************************

                                    //***************************
                                    if((CurrentSpin&3)<2)
                                    {
                                        footSpin=CurrentSpin+2;
                                    }
                                    else
                                    {
                                        footSpin=CurrentSpin-2;
                                    }
                                    if(FirstSpin[Hoperator[HopNO+1+SpinTempA]]==CurrentSpin or FirstSpin[Hoperator[HopNO+1+SpinTempA]]==footSpin)
                                    {
                                        SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=0;
                                    }
                                    SpinTemp[Hoperator[HopNO+1+SpinTempA]*3+1]=0;


                                }
                                else if (PbP<Pb[14])
                                {
                                    Hoperator[HopNO]^=1;
                                    footSpin=CurrentSpin+FootTemp[(CurrentSpin&3)];
                                    if(FirstSpin[Hoperator[HopNO+1+SpinTempA]]==CurrentSpin )
                                    {
                                        SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=0;
                                    }
                                    if(FirstSpin[Hoperator[HopNO+1+SpinTempB]]==footSpin)
                                    {
                                        SpinSystem[Hoperator[HopNO+1+SpinTempB]*3+1]=SpinTemp[Hoperator[HopNO+1+SpinTempA]]*(-1);
                                    }
                                    //SpinTemp[Hoperator[HopNO+1+SpinTempA]*3+1]=1;
                                    SpinTemp[Hoperator[HopNO+1+SpinTempB]*3+1]=SpinTemp[Hoperator[HopNO+1+SpinTempA]]*(-1);

                                }
                                else
                                {

                                    Hoperator[HopNO]^=1;
                                    footSpin=(CurrentSpin^1);
                                    if(FirstSpin[Hoperator[HopNO+1+SpinTempA]]==CurrentSpin )
                                    {
                                        SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=0;
                                    }
                                    if(FirstSpin[Hoperator[HopNO+1+SpinTempB]]==footSpin)
                                    {
                                        SpinSystem[Hoperator[HopNO+1+SpinTempB]*3+1]=SpinTemp[Hoperator[HopNO+1+SpinTempA]];
                                    }
                                    SpinTemp[Hoperator[HopNO+1+SpinTempA]*3+1]=0;
                                    SpinTemp[Hoperator[HopNO+1+SpinTempB]*3+1]=SpinTemp[Hoperator[HopNO+1+SpinTempA]];


                                }


                            }
                            else
                            {

                                if(PbP<Pb[16])
                                {
                                    footSpin=CurrentSpin;
                                }
                                else if (PbP<Pb[17])
                                {
                                    //Hoperator[HopNO]+=3;
                                    //************************

                                    //***************************
                                    if((CurrentSpin&3)<2)
                                    {
                                        footSpin=CurrentSpin+2;
                                    }
                                    else
                                    {
                                        footSpin=CurrentSpin-2;
                                    }
                                    if(FirstSpin[Hoperator[HopNO+1+SpinTempA]]==CurrentSpin or FirstSpin[Hoperator[HopNO+1+SpinTempA]]==footSpin)
                                    {
                                        SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=SpinTemp[Hoperator[HopNO+1+SpinTempB]*3+1];
                                    }
                                    SpinTemp[Hoperator[HopNO+1+SpinTempA]*3+1]=SpinTemp[Hoperator[HopNO+1+SpinTempB]*3+1];


                                }
                                else if (PbP<Pb[18])
                                {
                                    Hoperator[HopNO]^=1;
                                    footSpin=CurrentSpin+FootTemp[(CurrentSpin&3)];
                                    if(FirstSpin[Hoperator[HopNO+1+SpinTempA]]==CurrentSpin )
                                    {
                                        SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=SpinTemp[Hoperator[HopNO+1+SpinTempB]*3+1]*(-1);
                                    }
                                    if(FirstSpin[Hoperator[HopNO+1+SpinTempB]]==footSpin)
                                    {
                                        SpinSystem[Hoperator[HopNO+1+SpinTempB]*3+1]=0;
                                    }
                                    SpinTemp[Hoperator[HopNO+1+SpinTempA]*3+1]=0;
                                    //SpinTemp[Hoperator[HopNO+1+SpinTempB]*3+1]=0;

                                }
                                else
                                {

                                    Hoperator[HopNO]^=1;
                                    footSpin=(CurrentSpin^1);
                                    if(FirstSpin[Hoperator[HopNO+1+SpinTempA]]==CurrentSpin )
                                    {
                                        SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=SpinTemp[Hoperator[HopNO+1+SpinTempB]*3+1];
                                    }
                                    if(FirstSpin[Hoperator[HopNO+1+SpinTempB]]==footSpin)
                                    {
                                        SpinSystem[Hoperator[HopNO+1+SpinTempB]*3+1]=0;
                                    }
                                    SpinTemp[Hoperator[HopNO+1+SpinTempA]*3+1]=SpinTemp[Hoperator[HopNO+1+SpinTempB]*3+1];
                                    SpinTemp[Hoperator[HopNO+1+SpinTempB]*3+1]=0;


                                }
                            }

                        }
                    }
                    else if(SpinTemp[Hoperator[HopNO+1+SpinTempA]]*SpinTemp[Hoperator[HopNO+1+SpinTempB]]<0)
                    {//±1,-1/+1 H=0 ,Pb[28-31]

                        if(PbP<Pb[28])
                        {
                            footSpin=CurrentSpin;
                        }
                        else if (PbP<Pb[29])
                        {
                            //Hoperator[HopNO]+=3;
                            //************************

                            //***************************
                            if((CurrentSpin&3)<2)
                            {
                                footSpin=CurrentSpin+2;
                            }
                            else
                            {
                                footSpin=CurrentSpin-2;
                            }
                            if(FirstSpin[Hoperator[HopNO+1+SpinTempA]]==CurrentSpin or FirstSpin[Hoperator[HopNO+1+SpinTempA]]==footSpin)
                            {
                                SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=0;
                            }
                            SpinTemp[Hoperator[HopNO+1+SpinTempA]*3+1]=0;


                        }
                        else if (PbP<Pb[30])
                        {
                            printf("Error 1/-1 P[30] Pb=%4f \n",PbP);
                            system("pause");
                            /*
                            Hoperator[HopNO]^=1;
                            footSpin=CurrentSpin+FootTemp[(CurrentSpin&3)];
                            if(FirstSpin[Hoperator[HopNO+1+SpinTempA]]==CurrentSpin )
                            {
                                SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=0;
                            }
                            if(FirstSpin[Hoperator[HopNO+1+SpinTempB]]==footSpin)
                            {
                                SpinSystem[Hoperator[HopNO+1+SpinTempB]*3+1]=SpinTemp[Hoperator[HopNO+1+SpinTempA]]*(-1);
                            }
                            //SpinTemp[Hoperator[HopNO+1+SpinTempA]*3+1]=1;
                            SpinTemp[Hoperator[HopNO+1+SpinTempB]*3+1]=SpinTemp[Hoperator[HopNO+1+SpinTempA]]*(-1);
                            */
                        }
                        else
                        {

                            Hoperator[HopNO]^=1;
                            footSpin=(CurrentSpin^1);
                            if(FirstSpin[Hoperator[HopNO+1+SpinTempA]]==CurrentSpin )
                            {
                                SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=0;
                            }
                            if(FirstSpin[Hoperator[HopNO+1+SpinTempB]]==footSpin)
                            {
                                SpinSystem[Hoperator[HopNO+1+SpinTempB]*3+1]=0;
                            }
                            SpinTemp[Hoperator[HopNO+1+SpinTempA]*3+1]=0;
                            SpinTemp[Hoperator[HopNO+1+SpinTempB]*3+1]=0;


                        }





                    }
                    else
                    {
                        //±1,±1 H=0 Pb[36-39]
                        if(PbP<Pb[36])
                        {
                            footSpin=CurrentSpin;
                        }
                        else if (PbP<Pb[37])
                        {
                            //Hoperator[HopNO]+=3;
                            //************************

                            //***************************
                            if((CurrentSpin&3)<2)
                            {
                                footSpin=CurrentSpin+2;
                            }
                            else
                            {
                                footSpin=CurrentSpin-2;
                            }
                            if(FirstSpin[Hoperator[HopNO+1+SpinTempA]]==CurrentSpin or FirstSpin[Hoperator[HopNO+1+SpinTempA]]==footSpin)
                            {
                                SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=0;
                            }
                            SpinTemp[Hoperator[HopNO+1+SpinTempA]*3+1]=0;


                        }
                        else if (PbP<Pb[38])
                        {
                            //printf("Error 1/-1 P[30] \n")

                            Hoperator[HopNO]^=1;
                            footSpin=CurrentSpin+FootTemp[(CurrentSpin&3)];
                            if(FirstSpin[Hoperator[HopNO+1+SpinTempA]]==CurrentSpin )
                            {
                                SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=0;
                            }
                            if(FirstSpin[Hoperator[HopNO+1+SpinTempB]]==footSpin)
                            {
                                SpinSystem[Hoperator[HopNO+1+SpinTempB]*3+1]=0;
                            }
                            //SpinTemp[Hoperator[HopNO+1+SpinTempA]*3+1]=1;
                            SpinTemp[Hoperator[HopNO+1+SpinTempB]*3+1]=0;

                        }
                        else
                        {
                            printf("Error 1/-1 P[39]=%4f Pb=%4f\n",Pb[39],PbP);
                            system("pause");
                            /*
                            Hoperator[HopNO]^=1;
                            footSpin=(CurrentSpin^1);
                            if(FirstSpin[Hoperator[HopNO+1+SpinTempA]]==CurrentSpin )
                            {
                                SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=0;
                            }
                            if(FirstSpin[Hoperator[HopNO+1+SpinTempB]]==footSpin)
                            {
                                SpinSystem[Hoperator[HopNO+1+SpinTempB]*3+1]=0;
                            }
                            SpinTemp[Hoperator[HopNO+1+SpinTempA]*3+1]=0;
                            SpinTemp[Hoperator[HopNO+1+SpinTempB]*3+1]=0;
                            */

                        }

                    }


                }
                else
/****************************              H=1        ***************************************************/
                {
                    if(SpinTemp[Hoperator[HopNO+1+SpinTempA]]*SpinTemp[Hoperator[HopNO+1+SpinTempB]]==0)
                    {
                        if(SpinTemp[Hoperator[HopNO+1+SpinTempA]]==SpinTemp[Hoperator[HopNO+1+SpinTempB]])
                        {
//***************** 0 ,0 H=1 Pb[4-7]
                            if(PbP<Pb[4])
                            {
                                footSpin=CurrentSpin;
                            }
                            else if (PbP<Pb[5])
                            {
                                //Hoperator[HopNO]+=3;
                                //************************

                                //***************************
                                if((CurrentSpin&3)<2)
                                {
                                    footSpin=CurrentSpin+2;
                                }
                                else
                                {
                                    footSpin=CurrentSpin-2;
                                }
                                if(FirstSpin[Hoperator[HopNO+1+SpinTempA]]==CurrentSpin )
                                {
                                    SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=-1;
                                }
                                else if(FirstSpin[Hoperator[HopNO+1+SpinTempA]]==footSpin)
                                {
                                    SpinSystem[Hoperator[HopNO+1+SpinTempB]*3+1]=0;
                                }
                                SpinTemp[Hoperator[HopNO+1+SpinTempA]*3+1]=0;
                                SpinTemp[Hoperator[HopNO+1+SpinTempB]*3+1]=-1;

                            }
                            else if (PbP<Pb[6])
                            {
                                Hoperator[HopNO]^=1;
                                footSpin=CurrentSpin+FootTemp[(CurrentSpin&3)];
                                if(FirstSpin[Hoperator[HopNO+1+SpinTempA]]==CurrentSpin )
                                {
                                    SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=1;
                                }
                                if(FirstSpin[Hoperator[HopNO+1+SpinTempB]]==footSpin)
                                {
                                    SpinSystem[Hoperator[HopNO+1+SpinTempB]*3+1]=0;
                                }
                                SpinTemp[Hoperator[HopNO+1+SpinTempA]*3+1]=1;
                                SpinTemp[Hoperator[HopNO+1+SpinTempB]*3+1]=0;

                            }
                            else
                            {

                                Hoperator[HopNO]^=1;
                                footSpin=(CurrentSpin^1);
                                if(FirstSpin[Hoperator[HopNO+1+SpinTempA]]==CurrentSpin )
                                {
                                    SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=1;
                                }
                                if(FirstSpin[Hoperator[HopNO+1+SpinTempB]]==footSpin)
                                {
                                    SpinSystem[Hoperator[HopNO+1+SpinTempB]*3+1]=-1;
                                }
                                SpinTemp[Hoperator[HopNO+1+SpinTempA]*3+1]=1;
                                SpinTemp[Hoperator[HopNO+1+SpinTempB]*3+1]=-1;


                            }

                        }
                        else

                        {
                            if(SpinTemp[Hoperator[HopNO+1+SpinTempA]]!=0)
                            {
//**********************   1,0 H=1 Pb[20-23]
                                if(PbP<Pb[20])
                                {
                                    footSpin=CurrentSpin;
                                }
                                else if (PbP<Pb[21])
                                {
                                    //Hoperator[HopNO]+=3;
                                    //************************

                                    //***************************
                                    if((CurrentSpin&3)<2)
                                    {
                                        footSpin=CurrentSpin+2;
                                    }
                                    else
                                    {
                                        footSpin=CurrentSpin-2;
                                    }
                                    if(FirstSpin[Hoperator[HopNO+1+SpinTempA]]==CurrentSpin)
                                    {
                                        SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=0;
                                    }
                                    if(FirstSpin[Hoperator[HopNO+1+SpinTempA]]==footSpin)
                                    {
                                        SpinSystem[Hoperator[HopNO+1+SpinTempB]*3+1]=SpinTemp[Hoperator[HopNO+1+SpinTempA]*3+1]*(-1);
                                    }
                                    SpinTemp[Hoperator[HopNO+1+SpinTempA]*3+1]=SpinTemp[Hoperator[HopNO+1+SpinTempA]*3+1]*(-1);
                                    SpinTemp[Hoperator[HopNO+1+SpinTempA]*3+1]=SpinTemp[Hoperator[HopNO+1+SpinTempA]*3+1]*(-1);

                                }
                                else if (PbP<Pb[22])
                                {
                                    Hoperator[HopNO]^=1;
                                    footSpin=CurrentSpin+FootTemp[(CurrentSpin&3)];
                                    if(FirstSpin[Hoperator[HopNO+1+SpinTempA]]==CurrentSpin )
                                    {
                                        SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=0;
                                    }
                                    if(FirstSpin[Hoperator[HopNO+1+SpinTempB]]==footSpin)
                                    {
                                        SpinSystem[Hoperator[HopNO+1+SpinTempB]*3+1]=0;
                                    }
                                    SpinTemp[Hoperator[HopNO+1+SpinTempA]*3+1]=0;
                                    SpinTemp[Hoperator[HopNO+1+SpinTempB]*3+1]=0;

                                }
                                else
                                {

                                    Hoperator[HopNO]^=1;
                                    footSpin=(CurrentSpin^1);
                                    if(FirstSpin[Hoperator[HopNO+1+SpinTempA]]==CurrentSpin )
                                    {
                                        SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=0;
                                    }
                                    if(FirstSpin[Hoperator[HopNO+1+SpinTempB]]==footSpin)
                                    {
                                        SpinSystem[Hoperator[HopNO+1+SpinTempB]*3+1]=SpinTemp[Hoperator[HopNO+1+SpinTempA]];
                                    }
                                    SpinTemp[Hoperator[HopNO+1+SpinTempB]*3+1]=SpinTemp[Hoperator[HopNO+1+SpinTempA]];
                                    SpinTemp[Hoperator[HopNO+1+SpinTempA]*3+1]=0;



                                }
                            }
                            else
                            {
//********************      0,1 H=1 Pb[24-27]
                                if(PbP<Pb[24])
                                {
                                    footSpin=CurrentSpin;
                                }
                                else if (PbP<Pb[25])
                                {
                                    //Hoperator[HopNO]+=3;
                                    //************************

                                    //***************************
                                    if((CurrentSpin&3)<2)
                                    {
                                        footSpin=CurrentSpin+2;
                                    }
                                    else
                                    {
                                        footSpin=CurrentSpin-2;
                                    }
                                    if(FirstSpin[Hoperator[HopNO+1+SpinTempA]]==CurrentSpin)
                                    {
                                        SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=SpinTemp[Hoperator[HopNO+1+SpinTempA]*3+1]*(-1);
                                    }
                                    if(FirstSpin[Hoperator[HopNO+1+SpinTempA]]==footSpin)
                                    {
                                        SpinSystem[Hoperator[HopNO+1+SpinTempB]*3+1]=0;
                                    }
                                    SpinTemp[Hoperator[HopNO+1+SpinTempA]*3+1]=0;
                                    SpinTemp[Hoperator[HopNO+1+SpinTempB]*3+1]=0;

                                }
                                else if (PbP<Pb[26])
                                {
                                    Hoperator[HopNO]^=1;
                                    footSpin=CurrentSpin+FootTemp[(CurrentSpin&3)];
                                    if(FirstSpin[Hoperator[HopNO+1+SpinTempA]]==CurrentSpin )
                                    {
                                        SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=SpinTemp[Hoperator[HopNO+1+SpinTempB]*3+1];
                                    }
                                    if(FirstSpin[Hoperator[HopNO+1+SpinTempB]]==footSpin)
                                    {
                                        SpinSystem[Hoperator[HopNO+1+SpinTempB]*3+1]=SpinTemp[Hoperator[HopNO+1+SpinTempB]*3+1];
                                    }
                                    SpinTemp[Hoperator[HopNO+1+SpinTempA]*3+1]=SpinTemp[Hoperator[HopNO+1+SpinTempB]*3+1];
                                    SpinTemp[Hoperator[HopNO+1+SpinTempB]*3+1]=SpinTemp[Hoperator[HopNO+1+SpinTempB]*3+1];

                                }
                                else
                                {

                                    Hoperator[HopNO]^=1;
                                    footSpin=(CurrentSpin^1);
                                    if(FirstSpin[Hoperator[HopNO+1+SpinTempA]]==CurrentSpin )
                                    {
                                        SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=SpinTemp[Hoperator[HopNO+1+SpinTempB]*3+1];
                                    }
                                    if(FirstSpin[Hoperator[HopNO+1+SpinTempB]]==footSpin)
                                    {
                                        SpinSystem[Hoperator[HopNO+1+SpinTempB]*3+1]=0;
                                    }

                                    SpinTemp[Hoperator[HopNO+1+SpinTempA]*3+1]=SpinTemp[Hoperator[HopNO+1+SpinTempB]*3+1];
                                    SpinTemp[Hoperator[HopNO+1+SpinTempB]*3+1]=0;


                                }


                            }



                        }
                    }
//**************************  ±1,-1/+1 H=1 ,Pb[32-35]
                    else if(SpinTemp[Hoperator[HopNO+1+SpinTempA]]*SpinTemp[Hoperator[HopNO+1+SpinTempB]]<0)
                    {
                        if(PbP<Pb[32])
                        {
                            footSpin=CurrentSpin;
                        }
                        else if (PbP<Pb[33])
                        {
                            //Hoperator[HopNO]+=3;
                            //************************

                            //***************************
                            if((CurrentSpin&3)<2)
                            {
                                footSpin=CurrentSpin+2;
                            }
                            else
                            {
                                footSpin=CurrentSpin-2;
                            }
                            if(FirstSpin[Hoperator[HopNO+1+SpinTempA]]==CurrentSpin)
                            {
                                SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=0;
                            }
                            else if( FirstSpin[Hoperator[HopNO+1+SpinTempA]]==footSpin)
                            {
                                SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=SpinTemp[Hoperator[HopNO+1+SpinTempA]*3+1]*(-1);
                            }
                            SpinTemp[Hoperator[HopNO+1+SpinTempA]*3+1]=SpinTemp[Hoperator[HopNO+1+SpinTempA]*3+1]*(-1);
                            SpinTemp[Hoperator[HopNO+1+SpinTempB]*3+1]=0;

                        }
                        else if (PbP<Pb[34])
                        {
                            //printf("Error 1/-1 P[30] \n")

                            Hoperator[HopNO]^=1;
                            footSpin=CurrentSpin+FootTemp[(CurrentSpin&3)];
                            if(FirstSpin[Hoperator[HopNO+1+SpinTempA]]==CurrentSpin )
                            {
                                SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=0;
                            }
                            if(FirstSpin[Hoperator[HopNO+1+SpinTempB]]==footSpin)
                            {
                                SpinSystem[Hoperator[HopNO+1+SpinTempB]*3+1]=SpinTemp[Hoperator[HopNO+1+SpinTempA]*3+1]*(-1);
                            }
                            SpinTemp[Hoperator[HopNO+1+SpinTempA]*3+1]=0;
                            SpinTemp[Hoperator[HopNO+1+SpinTempB]*3+1]=SpinTemp[Hoperator[HopNO+1+SpinTempA]*3+1]*(-1);

                        }
                        else
                        {

                            Hoperator[HopNO]^=1;
                            footSpin=(CurrentSpin^1);
                            if(FirstSpin[Hoperator[HopNO+1+SpinTempA]]==CurrentSpin )
                            {
                                SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=0;
                            }
                            if(FirstSpin[Hoperator[HopNO+1+SpinTempB]]==footSpin)
                            {
                                SpinSystem[Hoperator[HopNO+1+SpinTempB]*3+1]=0;
                            }
                            SpinTemp[Hoperator[HopNO+1+SpinTempB]*3+1]=0;
                            SpinTemp[Hoperator[HopNO+1+SpinTempA]*3+1]=0;
                            //SpinTemp[Hoperator[HopNO+1+SpinTempB]*3+1]=0;


                        }




                    }
                    else
//******************** ±1 ±1 H=1
                    {
                        //printf("±1 ±1 H=1 \n");
                        Hoperator[HopNO]^=1;
                        footSpin=CurrentSpin+FootTemp[(CurrentSpin&3)];
                        /*
                        if((CurrentSpin&3)<2)
                        {
                            footSpin=CurrentSpin+2;
                        }
                        else
                        {
                            footSpin=CurrentSpin-2;
                        }
                        */

                        if(FirstSpin[Hoperator[HopNO+1+SpinTempA]]==CurrentSpin)
                        {
                            SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=0;
                        }
                        else if( FirstSpin[Hoperator[HopNO+1+SpinTempA]]==footSpin)
                        {
                            SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=0;
                        }

                        //SpinTemp[Hoperator[HopNO+1+SpinTempA]*3+1]=SpinTemp[Hoperator[HopNO+1+SpinTempA]*3+1];
                        SpinTemp[Hoperator[HopNO+1+SpinTempB]*3+1]=0;
                    }


                }
                CurrentSpin=SpinRecord[footSpin];
                if(CurrentSpin==StartSpin)
                {
                    Check=0;
                }
/*
                switch((Hoperator[HopNO]&7))
                {



                    case 0://|00>,Pb index 0-3

                        //LoopFile=fopen("LoopLog-1.txt","a");
                        //fprintf(LoopFile,"Case 0 \n");
                        //fclose(LoopFile);
                        if(PbP<Pb[0])
                        {
                            footSpin=CurrentSpin;
                        }
                        else if (PbP<Pb[1])
                        {
                            Hoperator[HopNO]+=3;
                            //************************

                            //***************************
                            if((CurrentSpin&3)<2)
                            {
                                footSpin=CurrentSpin+2;
                            }
                            else
                            {
                                footSpin=CurrentSpin-2;
                            }
                            if(FirstSpin[Hoperator[HopNO+1+SpinTempA]]==CurrentSpin or FirstSpin[Hoperator[HopNO+1+SpinTempA]]==footSpin)
                            {
                                SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=1;
                            }


                        }
                        else if (PbP<Pb[2])
                        {
                            Hoperator[HopNO]+=4;
                            footSpin=CurrentSpin+FootTemp[(CurrentSpin&3)];
                            if(FirstSpin[Hoperator[HopNO+1+SpinTempA]]==CurrentSpin )
                            {
                                SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=1;
                            }
                            if(FirstSpin[Hoperator[HopNO+1+SpinTempB]]==footSpin)
                            {
                                SpinSystem[Hoperator[HopNO+1+SpinTempB]*3+1]=1;
                            }

                        }
                        else
                        {

                            Hoperator[HopNO]+=6;
                            footSpin=(CurrentSpin^1);
                            if(FirstSpin[Hoperator[HopNO+1+SpinTempA]]==CurrentSpin )
                            {
                                SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=1;
                            }
                            if(FirstSpin[Hoperator[HopNO+1+SpinTempB]]==footSpin)
                            {
                                SpinSystem[Hoperator[HopNO+1+SpinTempB]*3+1]=-1;
                            }


                        }
                        break;
                    Case 0 end
                    case 1:
                        //LoopFile=fopen("LoopLog-1.txt","a");
                        //fprintf(LoopFile,"Case 1 \n");
                        //fclose(LoopFile);
                        //PbP=genrand64_real2();
                        if(PbP<Pb[4])
                        {
                            footSpin=CurrentSpin;

                        }
                        else if (PbP<Pb[5])
                        {
                            Hoperator[HopNO]-=1;
                            Hoperator[HopNO]+=4;
                            if((CurrentSpin&3)<2)
                            {
                                footSpin=CurrentSpin+2;
                            }
                            else
                            {
                                footSpin=CurrentSpin-2;
                            }
                            if(SpinTempA==0)
                            {
                                if(FirstSpin[Hoperator[HopNO+1+SpinTempA]]==CurrentSpin )
                                {
                                    SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=-1;
                                }
                                if(FirstSpin[Hoperator[HopNO+1+SpinTempA]]==footSpin)
                                {
                                    SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=0;
                                }
                            }
                            else
                            {
                                if(FirstSpin[Hoperator[HopNO+1+SpinTempA]]==CurrentSpin )
                                {
                                    SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=-1;
                                }
                                if(FirstSpin[Hoperator[HopNO+1+SpinTempA]]==footSpin)
                                {
                                    SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=0;
                                }
                            }




                        }
                        else if (PbP<Pb[6])
                        {
                            Hoperator[HopNO]-=1;
                            Hoperator[HopNO]+=3;
                            footSpin=CurrentSpin+FootTemp[(CurrentSpin&3)];
                            if(FirstSpin[Hoperator[HopNO+1+SpinTempA]]==CurrentSpin )
                            {
                                SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=1;
                            }
                            if(FirstSpin[Hoperator[HopNO+1+SpinTempB]]==footSpin)
                            {
                                SpinSystem[Hoperator[HopNO+1+SpinTempB]*3+1]=0;
                            }
                        }
                        else
                        {

                            Hoperator[HopNO]-=1;
                            Hoperator[HopNO]+=5;
                            if(SpinTempA==0)
                            {
                                SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=1;
                                SpinSystem[Hoperator[HopNO+1+SpinTempB]*3+1]=-1;

                            }
                            else
                            {
                                SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=-1;
                                SpinSystem[Hoperator[HopNO+1+SpinTempB]*3+1]=1;
                            }
                            footSpin=(CurrentSpin^1);
                        }
                        break;


                    /*case 1 end
                    case 2:
                        //LoopFile=fopen("LoopLog-1.txt","a");
                        //fprintf(LoopFile,"Case 2 \n");
                        //fclose(LoopFile);
  //PbP=genrand64_real2();
                        if(PbP<Pb[8])
                        {
                            footSpin=CurrentSpin;

                        }
                        else if (PbP<Pb[9])
                        {
                            Hoperator[HopNO]-=2;
                            Hoperator[HopNO]+=4;
                            if(SpinTempA==0)
                            {
                                SpinSystem[Hoperator[HopNO+1+SpinTempB]*3+1]=1;

                            }
                            else
                            {
                                SpinSystem[Hoperator[HopNO+1+SpinTempB]*3+1]=-1;
                            }
                            if((CurrentSpin&3)<2)
                            {
                                footSpin=CurrentSpin+2;
                            }
                            else
                            {
                                footSpin=CurrentSpin-2;
                            }

                        }
                        else if (PbP<Pb[10])
                        {
                            Hoperator[HopNO]-=2;
                            Hoperator[HopNO]+=3;
                            if(SpinTempA==0)
                            {
                                SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=-1;

                            }
                            else
                            {
                                SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]= 1;
                            }

                            footSpin=CurrentSpin+FootTemp[(CurrentSpin&3)];

                        }
                        else
                        {
                            footSpin=(CurrentSpin^1);
                            Hoperator[HopNO]-=2;
                            Hoperator[HopNO]+=5;
                            if(SpinTempA==0)
                            {
                                SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=-1;

                            }
                            else
                            {
                                SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]= 1;
                            }
                        }
                        break;

                    case 3:
                        //LoopFile=fopen("LoopLog-1.txt","a");
                        //fprintf(LoopFile,"Case 3 \n");
                        //fclose(LoopFile);
                        if(SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]!=0)
                        {
                            //PbP=genrand64_real2();
                            if(PbP<Pb[12])
                            {
                                footSpin=CurrentSpin;
                                SpinSystem[Hoperator[HopNO+1+SpinTempB]*3+1]=SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1];
                                SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=0;

                            }
                            else if (PbP<Pb[13])
                            {
                                Hoperator[HopNO]-=3;
                                Hoperator[HopNO]+=1;
                                if((CurrentSpin&3)<2)
                                {
                                    footSpin=CurrentSpin+2;
                                }
                                else
                                {
                                    footSpin=CurrentSpin-2;
                                }
                                SpinTempB=(SpinTempA^1);
                                SpinSystem[Hoperator[HopNO+1+SpinTempB]*3+1]=SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1];
                                SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]*=(-1);



                            }
                            else if (PbP<Pb[14])
                            {
                                Hoperator[HopNO]-=3;
                                //Hoperator[HopNO]+=0-3;
                                footSpin=CurrentSpin+FootTemp[(CurrentSpin&3)];
                                SpinTempB=(SpinTempA^1);
                                SpinSystem[Hoperator[HopNO+1+SpinTempB]*3+1] = 0;
                                SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1] = 0;

                            }
                            else
                            {
                                Hoperator[HopNO]-=3;
                                Hoperator[HopNO]+=2;
                                footSpin=(CurrentSpin^1);

                            }
                            break;
                        }
                        else
                        {
                            //PbP=genrand64_real2();
                            if(PbP<Pb[20])
                            {
                                footSpin=CurrentSpin;

                            }
                            else if (PbP<Pb[21])
                            {
                                Hoperator[HopNO]-=3;
                                Hoperator[HopNO]+=7;
                                if((CurrentSpin&3)<2)
                                {
                                    footSpin=CurrentSpin+2;
                                }
                                else
                                {
                                    footSpin=CurrentSpin-2;
                                }
                                SpinTempA=(CurrentSpin%2);
                                SpinTempB=(SpinTempA^1);
                                SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=0;
                                SpinSystem[Hoperator[HopNO+1+SpinTempB]*3+1]=0;


                            }
                            else if (PbP<Pb[22])//C=1 不作用
                            {
                                Hoperator[HopNO]-=3;
                                Hoperator[HopNO]+=6;
                                SpinTempA=(CurrentSpin%2);
                                SpinTempB=(SpinTempA^1);
                                footSpin=CurrentSpin+FootTemp[(CurrentSpin&3)];
                                SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=SpinSystem[Hoperator[HopNO+1+SpinTempB]*3+1];


                            }
                            else
                            {

                                Hoperator[HopNO]-=3;
                                Hoperator[HopNO]+=2;
                                footSpin=(CurrentSpin^1);
                                SpinTempA=(CurrentSpin%2);
                                SpinTempB=(SpinTempA^1);
                                SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=SpinSystem[Hoperator[HopNO+1+SpinTempB]*3+1];
                                SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=0;
                            }
                            break;
                        }
                    case 4:

                        printf("Error Case 4 \n");
                        printf("HopNO=%4d H=%4d (%4d,%4d) CurrentSpin=%4d PbP=%6f \n",HopNO,Hoperator[HopNO],Hoperator[HopNO]&7,Hoperator[HopNO]%8 ,CurrentSpin,PbP );
                        printf("HopNO=%4d H=%4d  footSpin=%4d to New-CurrentSpin=%4d  \n",HopNO,Hoperator[LoopNumA]&7,footSpin,CurrentSpin );
                        system("pause");
                        break;
                    case 5:
                        printf("Error Case 5 \n");
                        printf("HopNO=%4d H=%4d (%4d,%4d) CurrentSpin=%4d PbP=%6f \n",HopNO,Hoperator[HopNO],Hoperator[HopNO]&7,Hoperator[HopNO]%8 ,CurrentSpin,PbP );
                        printf("HopNO=%4d H=%4d  footSpin=%4d to New-CurrentSpin=%4d  \n",HopNO,Hoperator[LoopNumA]&7,footSpin,CurrentSpin );
                        system("pause");
                        break;
                    case 6:
                        //LoopFile=fopen("LoopLog-1.txt","a");
                        //fprintf(LoopFile,"Case 6 \n");
                        //fclose(LoopFile);
                        //PbP=genrand64_real2();
                        if(PbP<Pb[24])
                        {
                            footSpin=CurrentSpin;
                        }
                        else if (PbP<Pb[25])
                        {
                            Hoperator[HopNO]-=6;
                            Hoperator[HopNO]+=2;

                            if((CurrentSpin&3)<2)
                            {
                                footSpin=CurrentSpin+2;
                            }
                            else
                            {
                                footSpin=CurrentSpin-2;
                            }
                            SpinTempA=(CurrentSpin%2);
                            //SpinTempB=(SpinTempA^1);
                            SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1] = 0;

                        }
                        else if (PbP<Pb[26])
                        {
                            Hoperator[HopNO]-=6;
                            Hoperator[HopNO]+=3;
                            footSpin=CurrentSpin+FootTemp[(CurrentSpin&3)];
                            SpinTempA=(CurrentSpin%2);
                            SpinTempB=(SpinTempA^1);
                            SpinSystem[Hoperator[HopNO+1+SpinTempB]*3+1]=0;

                        }
                        else
                        {
                            footSpin=(CurrentSpin^1);
                            Hoperator[HopNO]-=6;
                            Hoperator[HopNO]+=1;
                        }
                        break;
                    case 7:
                        //LoopFile=fopen("LoopLog-1.txt","a");
                        //fprintf(LoopFile,"Case 7 \n");
                        //fclose(LoopFile);
                        //PbP=genrand64_real2();
                        if(PbP<Pb[24])
                        {
                            footSpin=CurrentSpin;
                        }
                        else if (PbP<Pb[25])
                        {
                            Hoperator[HopNO]-=7;
                            Hoperator[HopNO]+=3;

                            if((CurrentSpin&3)<2)
                            {
                                footSpin=CurrentSpin+2;
                            }
                            else
                            {
                                footSpin=CurrentSpin-2;
                            }
                            SpinTempA=(CurrentSpin%2);
                            SpinTempB=(SpinTempA^1);
                            SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1] = SpinSystem[Hoperator[HopNO+1+SpinTempB]*3+1];
                            SpinSystem[Hoperator[HopNO+1+SpinTempB]*3+1]=0;

                        }
                        else if (PbP<Pb[26])
                        {
                            Hoperator[HopNO]-=7;
                            Hoperator[HopNO]+=2;
                            footSpin=CurrentSpin+FootTemp[(CurrentSpin&3)];
                            SpinTempA=(CurrentSpin%2);
                            //SpinTempB=(SpinTempA^1);
                            SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1]=0;

                        }
                        else
                        {
                            Hoperator[HopNO]-=7;
                            //Hoperator[HopNO]+=0-7;
                            footSpin=(CurrentSpin^1);
                            SpinTempA=(CurrentSpin%2);
                            SpinTempB=(SpinTempA^1);
                            SpinSystem[Hoperator[HopNO+1+SpinTempA]*3+1] = 0;
                            SpinSystem[Hoperator[HopNO+1+SpinTempB]*3+1] = 0;
                        }
                        break;
                }
*/
                //////////
/*
                //LoopFile=fopen("LoopLog-1.txt","a");
                fprintf(LoopFile,"While off \n");
                //fclose(LoopFile);

                //printf("HopNO=%4d OldH=%4d  NewH=%4d CurrentSpin=%4d footSpin=%4d to New-CurrentSpin=%4d  PbP=%5f \n",HopNO,TempH,Hoperator[LoopNumA]&7,CurrentSpin,footSpin,SpinRecord[footSpin],PbP );
                if(SpinRecord[footSpin]<0 or footSpin<0 or (Hoperator[HopNO]&7)==4 or (Hoperator[HopNO]&7)==5)
                {

                    printf("HopNO=%4d OldH=%4d  NewH=%4d CurrentSpin=%4d footSpin=%4d to New-CurrentSpin=%4d  PbP=%5f \n",HopNO,TempH,(Hoperator[HopNO]&7),CurrentSpin,footSpin,SpinRecord[footSpin],PbP );
                    //printf("%4d %4d %4d %4d %4d %4d %4d\n",SpinRecord[footSpin-3],SpinRecord[footSpin-2],SpinRecord[footSpin-1],SpinRecord[footSpin],SpinRecord[footSpin+1],SpinRecord[footSpin+2],SpinRecord[footSpin+3] );
                }

                //File=fopen("LoopLog.txt","a");
                //fprintf(File,"HopNO=%4d H=%4d  footSpin=%4d to New-CurrentSpin=%4d  \n",HopNO,Hoperator[LoopNumA]&7,footSpin,CurrentSpin );

                //fclose(File);
                LoopCount+=1;
                if(CurrentSpin==StartSpin or  LoopCount==HoperatorNO*100)
                {
                    Check=0;
                }
*/


            }


        }

    }
    //fclose(LoopFile);
                //////////
    //LoopFile=fopen("LoopLog-1.txt","a");
    //fprintf(LoopFile,"Loop End \n");
    //fclose(LoopFile);
    /*
    File=fopen("VertexTable-1.txt","w");
    for(LoopNumA=0;LoopNumA<HoperatorNO*4;LoopNumA+=4)
    {
        fprintf(File,"%4d %4d ",(long long)LoopNumA/4,LoopNumA );
        //printf("%d ",(long long)LoopNumA/4);
        //printf("H = %6d  ",Hoperator[(long long)(LoopNumA/4)*3]);
        for(LoopNumB=0;LoopNumB<4;LoopNumB+=1)
        {
            fprintf(File,"%4d ",SpinRecord[LoopNumA+LoopNumB]);
            //printf("%4d ",SpinRecord[LoopNumA+LoopNumB]);
        }
        fprintf(File,"\n");
        //printf("\n");

    }
    fclose(File);
    */
    for(LoopNumA=0;LoopNumA<SpinNO;LoopNumA+=1)
    {
        SpinNumber_NO=LoopNumA*3;
        if(FirstSpin[LoopNumA]==-1)
        {
            if(genrand64_real2()<0.5)
            {
                SpinSystem[SpinNumber_NO+1]*=-1;
            }
        }
        /*else
        {
            TempW+=SpinSystem[SpinNumber_NO+1]*SpinSystem[SpinNumber_NO+1]*0.25;
        }
        */
    }
    //LoopFile=fopen("LoopLog-1.txt","a");
    //fprintf(LoopFile,"Loop All End \n");
    //fclose(LoopFile);
    //printf("loop free and NULL \n");
    //*SpinRecord= NULL,*FirstSpin= NULL,*LastSpin= NULL,*HSpinLR = NULL, *SpinNumber=NULL, *FootTemp=NULL;
    free(HRecord);
    free(SpinRecord);
    free(FirstSpin);
    free(LastSpin);
    free(HSpinLR);
    free(SpinNumber);
    free(FootTemp);
    free(Pb);
    SpinRecord=NULL;
    FirstSpin=NULL;
    LastSpin=NULL;
    HSpinLR=NULL;
    SpinNumber=NULL;
    FootTemp=NULL;
    HRecord=NULL;
    Pb=NULL;
    //printf("loop end \n");


}
void LoopUpdate_Spin1(long long* SpinSystem,double* BondNOsystem,\
                    long long* Hoperator,long long &HNO,\
                    long long &SpinNO,long long &BondNO,long long &HoperatorNO,\
                    double &TempW,long long* BondNORecord)
{
    long long LoopNumA,LoopNumB,LoopNumC,LoopNumD;
    long long LeftSpin,RightSpin,LeftSpin2,RightSpin2,LeftSpin3,RightSpin3;
    long long *SpinRecord= NULL,*FirstSpin= NULL,*LastSpin= NULL,*HSpinLR = NULL, *SpinNumber=NULL, *FootTemp=NULL;
    long long StartSpin,HopNO,HSpin,SwitchNO,SpinNumber_NO;
    long long CurrentSpin,footSpin,Check,Hop,HLeft,HRight,HLeft2,HRight2,HLeft3,HRight3,SingleFoot,SingleCurrent;
    double Chance,Goal,SumSpin,Pb,Pb1,Pb2,Pb3;
    //srand(time(NULL)*rand());
    SpinRecord=(long long *)malloc((HoperatorNO*4+1)*sizeof(long long*));
    //FirstSpin=(long long *)malloc((SpinNO+1)*sizeof(long long*));
    //LastSpin=(long long *)malloc((SpinNO+1)*sizeof(long long*));
    //HSpinLR=(long long *)malloc((6*2+1)*sizeof(long long*));//每個Spin都記是否為Ferromagnetic
    SpinNumber=(long long *)malloc((3+1)*sizeof(long long*));
    FootTemp=(long long *)malloc((4+1)*sizeof(long long*));
    memset(SpinRecord,-1,(HoperatorNO*4)*sizeof(long long*));
    //memset(FirstSpin,-1,SpinNO*sizeof(long long*));
    //memset(LastSpin,-1,SpinNO*sizeof(long long*));
    //memset(HSpinLR,-1,(6*2+1)*sizeof(long long*));
    memset(SpinNumber,-1,(3+1)*sizeof(long long*));
    memset(FootTemp,-1,(4+1)*sizeof(long long*));
    Pb1=1/3;
    Pb2=Pb1+0.5;
    Pb3=1;

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
    for (LoopNumA=0;LoopNumA<HoperatorNO*3;LoopNumA+=3)
    {
        //printf("HoperatorNO=%d,LoopNumA=%d \n",HoperatorNO,LoopNumA);
        //printf("Hop=%d,HLeft=%d,HRight=%d,HLeft2=%d,HRight2=%d \n",Hoperator[LoopNumA],Hoperator[LoopNumA+1],Hoperator[LoopNumA+2],Hoperator[LoopNumA+3],Hoperator[LoopNumA+4]);

        //printf("HoperatorNO=%d,LoopNumA=%d \n",HoperatorNO,LoopNumA);
        //printf("Hop=%d,HLeft=%d,HRight=%d,HLeft2=%d,HRight2=%d \n",Hoperator[LoopNumA],Hoperator[LoopNumA+1],Hoperator[LoopNumA+2],Hoperator[LoopNumA+3],Hoperator[LoopNumA+4]);
        //printf("Check Loop-1\n");
        Hop=Hoperator[LoopNumA];

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
            SpinNumber[LoopNumB] = (long long)(LoopNumA/3)+LoopNumB;
        }
        /*
        SpinNumber=(long long)(LoopNumA/7)*12;
        SpinNumber2=(long long)(LoopNumA/7)*12+4;
        SpinNumber3=(long long)(LoopNumA/7)*12+8;
        */

        //Q3 0-3第一個pair 4-7 第二個pair 8-11第三個pair
        if(Hop!=-1)
        {
            for(LoopNumB=0;LoopNumB<2;LoopNumB+=1)
            {


              HSpinLR[LoopNumB] = Hoperator[LoopNumA+LoopNumB];

            }
            /*
            memset(HSpinLR,-1,(6*2)*sizeof(long long*));
            if(BondNORecord[((long long)(Hop>>4))*7]>-1)
            {
                if(BondNORecord[((long long)(Hop>>4))*7]==0)
                {
                    HSpinLR[0] = BondNORecord[((long long)(Hop>>4))*7];
                    HSpinLR[2] = BondNORecord[((long long)(Hop>>4))*7];
                    //printf("%d %d \n",HSpinLR[0],HSpinLR[2]);
                }
                else
                {
                    HSpinLR[(BondNORecord[((long long)(Hop>>4))*7]-1)*4]= BondNORecord[((long long)(Hop>>4))*7];
                    HSpinLR[(BondNORecord[((long long)(Hop>>4))*7]-1)*4+2]= BondNORecord[((long long)(Hop>>4))*7];
                }

            }
            for(LoopNumB=0;LoopNumB<6;LoopNumB+=1)
            {


              HSpinLR[LoopNumB*2+1] = Hoperator[LoopNumA+LoopNumB+1];

            }
            */
            //printf("%d , %d\n",Hop,Hop%10);

                //printf("%d , %d\n",Hop,Hop%10);
                //LeftSpin=LastSpin[HLeft];
                //RightSpin=LastSpin[HRight];
                /*
                if(HSpinLR[0] >-1)
                {
                    for(LoopNumB=0 ; LoopNumB < 2 ; LoopNumB+=1)
                    {
                        SpinRecord[(SpinNumber[0]+LoopNumB)*2]=HSpinLR[LoopNumB*2];
                        SpinRecord[(SpinNumber[0]+LoopNumB+2)*2]=HSpinLR[LoopNumB*2];
                    }


                }
                */

                for(LoopNumB=0 ; LoopNumB < 2 ; LoopNumB+=1)
                {
                    if(LastSpin[HSpinLR[LoopNumB]]!=-1)
                    {
                        SpinRecord[SpinNumber[0]+LoopNumB]=LastSpin[HSpinLR[LoopNumB]];
                        SpinRecord[LastSpin[HSpinLR[LoopNumB]]]=SpinNumber[0]+LoopNumB;
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
                        FirstSpin[HSpinLR[LoopNumB]]=SpinNumber[0]+LoopNumB ;
                        /*
                        if(HSpinLR[LoopNumB*2] >-1)
                        {
                           //printf("Spin1");
                           SpinRecord[(SpinNumber[0]+LoopNumB)*2]=HSpinLR[LoopNumB*2];
                           SpinRecord[(SpinNumber[0]+LoopNumB+2)*2]=HSpinLR[LoopNumB*2];
                        }
                        */
                    }
                    LastSpin[HSpinLR[LoopNumB]]=SpinNumber[0]+2+LoopNumB;
                }

        }
        else
        {
            //continue;

            for(LoopNumB=0;LoopNumB<4;LoopNumB+=1)
            {

                SpinRecord[(SpinNumber[0]+LoopNumB)]=-1;
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
    for(LoopNumA=0;LoopNumA<SpinNO;LoopNumA+=1)
    {
        if(FirstSpin[LoopNumA]!=-1)
        {
            SpinRecord[FirstSpin[LoopNumA]]=LastSpin[LoopNumA];
            SpinRecord[LastSpin[LoopNumA]]=FirstSpin[LoopNumA];
        }

    }
    */

    for(LoopNumA=0;LoopNumA<HoperatorNO*4;LoopNumA+=2)//4為一個operator幾個腳，在這邊Q會4*3，半邊半邊算
    {
        if(SpinRecord[LoopNumA]>-1)
        {
            StartSpin=LoopNumA;
            CurrentSpin=LoopNumA;
            Check=1;
            SumSpin=0;
            if(genrand64_real2()<Chance)
            {
                while (Check==1)
                {
                    HopNO = ((long long)(CurrentSpin>>2)*3);
                    if((Hoperator[HopNO]&3)<2)
                    {
                        Pb=genrand64_real2();
                        if(Pb<Pb1)
                        {
                            Hoperator[HopNO]=Hoperator[HopNO]^1+2;
                            footSpin=CurrentSpin+FootTemp[CurrentSpin%4];
                            SpinSystem[Hoperator[HopNO+1+footSpin>>1]]*=(-1);
                        }
                        else if(Pb<Pb2)
                        {
                            if((CurrentSpin&3)<2)
                            {
                                footSpin=CurrentSpin+2;
                            }
                            else
                            {
                                footSpin=CurrentSpin-2;
                            }

                            SpinSystem[Hoperator[HopNO+1+CurrentSpin>>1]]*=(-1);
                        }
                        else
                        {
                            footSpin=CurrentSpin;
                        }
                    }
                    else if((Hoperator[HopNO]&1)==0)
                    {
                        Pb=genrand64_real2();
                        if(Pb<Pb1)
                        {
                            Hoperator[HopNO]=Hoperator[HopNO]^1-2;
                            footSpin=(CurrentSpin^1);
                            SpinSystem[Hoperator[HopNO+1+CurrentSpin>>1]]*=(-1);
                            SpinSystem[Hoperator[HopNO+1+footSpin>>1]]*=(-1);
                        }
                        else if(Pb<Pb2)
                        {
                            footSpin=CurrentSpin;

                        }
                        else
                        {
                            if((CurrentSpin&3)<2)
                            {
                                footSpin=CurrentSpin+2;
                            }
                            else
                            {
                                footSpin=CurrentSpin-2;
                            }
                            SpinSystem[Hoperator[HopNO+1+footSpin>>1]]*=(-1) ;
                        }
                    }
                    else
                    {
                        Pb=genrand64_real2();
                        if(Pb<Pb1)
                        {
                            footSpin=CurrentSpin;
                            SpinSystem[Hoperator[HopNO+1+CurrentSpin>>1]]*=(-1);
                            SpinSystem[Hoperator[HopNO+1+footSpin>>1]]*=(-1);
                        }
                        else if(Pb<Pb2)
                        {
                            Hoperator[HopNO]=Hoperator[HopNO]^1-2;
                            footSpin=(CurrentSpin^1);
                            SpinSystem[Hoperator[HopNO+1+CurrentSpin>>1]]*=(-1);
                            SpinSystem[Hoperator[HopNO+1+footSpin>>1]]*=(-1);
                        }
                        else
                        {
                            footSpin=CurrentSpin+FootTemp[CurrentSpin%4];
                            SpinSystem[Hoperator[HopNO+1+footSpin>>1]]*=(-1);
                        }

                    }



                    CurrentSpin=SpinRecord[footSpin];


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
        SpinNumber_NO=LoopNumA*3;
        if(FirstSpin[LoopNumA]==-1)
        {
            if(genrand64_real2()<0.5)
            {
                SpinSystem[SpinNumber_NO+1]*=-1;
            }
        }
        /*else
        {
            TempW+=SpinSystem[SpinNumber_NO+1]*SpinSystem[SpinNumber_NO+1]*0.25;
        }
        */
    }
    //printf("loop end \n");
    //*SpinRecord= NULL,*FirstSpin= NULL,*LastSpin= NULL,*HSpinLR = NULL, *SpinNumber=NULL, *FootTemp=NULL;
    free(SpinRecord);
    free(FirstSpin);
    free(LastSpin);
    free(HSpinLR);
    free(SpinNumber);
    free(FootTemp);
    ///
    SpinRecord=NULL;
    FirstSpin=NULL;
    LastSpin=NULL;
    HSpinLR=NULL;
    SpinNumber=NULL;
    FootTemp=NULL;



}
