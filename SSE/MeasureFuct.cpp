void MeasureFuct(long long* SpinSystem,double* BondNOsystem,long long* Hoperator\
          ,long long &HNO,long long &Size,long long &SpinNO,long long &BondNO,long long &HoperatorNO\
          ,double &AFM,double &AFM1,double &AFM2,double &AFM4,double &AFM6,double &AX1,double &Measure\
          ,double &WiddingX,double &WiddingY,double &WiddingZ)
{
    long long LoopNumA,LoopNumB,LoopNumC;
    //double Measure;
    double SingleAFM,SingleAFM1,SingleAFM2,SingleAFM4,SingleAFM6,SingleAX1,SingleMeasure,Msz,*Widding;
    SingleAFM=0;
    SingleAFM1=0;
    SingleAFM2=0;
    SingleAFM4=0;
    SingleAFM6=0;
    SingleAX1=0;
    SingleMeasure=0;
    Msz=0;
    Widding=(double *)malloc((long long)(BondNO/SpinNO*sizeof(double*)));
    for(LoopNumA=0;LoopNumA<BondNO/SpinNO;LoopNumA+=1)
    {
        Widding[LoopNumA]=0.0;
    }
    for(LoopNumA=0;LoopNumA<SpinNO*3;LoopNumA+=3)
    {

        SingleAFM+=(double)((double)SpinSystem[LoopNumA+1]*(double)SpinSystem[LoopNumA]);
        //SingleAFM+=(double)((double)SpinSystem[LoopNumA+1]*(double)pow(-1.0,(long long)(SpinSystem[LoopNumA])%Size+(long long)(SpinSystem[LoopNumA])/Size));
        //Msz=Msz+(double)((double)SpinSystem[LoopNumA+1]*(double)pow(-1.0,(long long)(SpinSystem[LoopNumA])%Size+(long long)(SpinSystem[LoopNumA])/Size));;
        //printf("%d  , %d , %f, \n",SpinSystem[LoopNumA],SpinSystem[LoopNumA+1],\
        //(double)SpinSystem[LoopNumA+1]*pow(-1.0,(long long)(SpinSystem[LoopNumA])%Size+(long long)(SpinSystem[LoopNumA])/Size));
       // printf("%d,%d,%d,%d,%f \n",SpinSystem[LoopNumA],SpinSystem[LoopNumA]%Size,\
        (SpinSystem[LoopNumA])/Size,SpinSystem[LoopNumA+1],\
        (double)SpinSystem[LoopNumA+1]*pow(-1.0,(long long)(SpinSystem[LoopNumA])%Size+(long long)(SpinSystem[LoopNumA])/Size));
    }
    SingleAFM/=2.0;
    for(LoopNumA=0;LoopNumA<HoperatorNO*3;LoopNumA+=3)
    {
        if(Hoperator[LoopNumA]==-1)
        {
            continue;
        }
        else if(Hoperator[LoopNumA]%2==1)
        {
            SpinSystem[Hoperator[LoopNumA+1]*3+1]*=-1;
            SpinSystem[Hoperator[LoopNumA+2]*3+1]*=-1;
            SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+1]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+1]*3]);
            //SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+1]*3+1]*(double)pow( -1.0 , (long long)Hoperator[LoopNumA+1]%Size+(long long)Hoperator[LoopNumA+1]/Size ) );
            Widding[((Hoperator[LoopNumA]-1)/2)/SpinNO]+=(double)SpinSystem[Hoperator[LoopNumA+2]*3+1];

        }
        /*
        SingleAX1+=(double)SingleAFM;
        SingleAFM1+=(double)fabs(SingleAFM);
        SingleAFM2+=(double)pow(SingleAFM,2);
        SingleAFM4+=(double)pow(SingleAFM,4);
        SingleAFM6+=(double)pow(SingleAFM,6);
        */
        SingleAX1+=(double)SingleAFM;
        SingleAFM1+=(double)fabs(SingleAFM);
        SingleAFM2+=(double)(SingleAFM*SingleAFM);
        SingleAFM4+=(double)(SingleAFM*SingleAFM*SingleAFM*SingleAFM);
        SingleAFM6+=(double)(SingleAFM*SingleAFM*SingleAFM*SingleAFM*SingleAFM*SingleAFM);

    }

    if(HNO!=0)
    {

        //SingleAX1=(double)(pow(SingleAX1,2)+SingleAFM2)/(double)(HNO*(HNO+1));
        SingleAX1=(double)((double)((double)(SingleAX1*SingleAX1)+(double)SingleAFM2)/(double)(HNO*(HNO+1)));
        SingleAFM1/=(double)HNO;
        SingleAFM2/=(double)HNO;
        SingleAFM4/=(double)HNO;
        SingleAFM6/=(double)HNO;

    }
    else
    {
        /*
        SingleAFM1=(double)fabs(SingleAFM);
        SingleAFM2=(double)pow(SingleAFM,2);
        SingleAFM4=(double)pow(SingleAFM,4);
        SingleAFM6=(double)pow(SingleAFM,6);
        SingleAX1=(double)SingleAFM2;
        */
        SingleAFM1=(double)fabs(SingleAFM);
        SingleAFM2=(SingleAFM*SingleAFM);
        SingleAFM4=(SingleAFM*SingleAFM*SingleAFM*SingleAFM);
        SingleAFM6=(SingleAFM*SingleAFM*SingleAFM*SingleAFM*SingleAFM*SingleAFM);
        SingleAX1=(double)SingleAFM2;
    }
    for(LoopNumA=0;LoopNumA<SpinNO*3;LoopNumA+=3)
    {
        SingleMeasure+=SpinSystem[LoopNumA+1];
    }

    SingleMeasure*=SingleMeasure;
    SingleMeasure*=0.25;
    AFM1+=SingleAFM1;
    AFM2+=SingleAFM2;
    AFM4+=SingleAFM4;
    AFM6+=SingleAFM6;
    AX1+=(double)SingleAX1;
    Measure+=SingleMeasure;
    //printf("%4,%f",Widding[0],Widding[1]);

    //WiddingX+=pow(Widding[0],2);
    //WiddingY+=pow(Widding[1],2);
    WiddingX+=(double)(Widding[0]*Widding[0]);
    WiddingY+=(double)(Widding[1]*Widding[1]);
    free(Widding);
    //printf("%f",Widding[0]*Widding[0]);
}

void MeasureFuctJQ2(long long* SpinSystem,double* BondNOsystem,long long* Hoperator\
          ,long long &HNO,long long &Size,long long &SpinNO,long long &BondNO,long long &HoperatorNO\
          ,double &AFM,double &AFM1,double &AFM2,double &AFM4,double &AFM6,double &AX1,double &Measure\
          ,double &WiddingX,double &WiddingY,double &WiddingZ)
{
    long long LoopNumA,LoopNumB,LoopNumC;
    //double Measure;
    double SingleAFM,SingleAFM1,SingleAFM2,SingleAFM4,SingleAFM6,SingleAX1,SingleMeasure,Msz,*Widding;
    SingleAFM=0;
    SingleAFM1=0;
    SingleAFM2=0;
    SingleAFM4=0;
    SingleAFM6=0;
    SingleAX1=0;
    SingleMeasure=0;
    Msz=0;
    Widding=(double *)malloc((long long)(BondNO/SpinNO*sizeof(double*)));
    for(LoopNumA=0;LoopNumA<BondNO/SpinNO;LoopNumA+=1)
    {
        Widding[LoopNumA]=0.0;
    }
    for(LoopNumA=0;LoopNumA<SpinNO*3;LoopNumA+=3)
    {

        SingleAFM+=(double)((double)SpinSystem[LoopNumA+1]*(double)SpinSystem[LoopNumA]);
        //SingleAFM+=(double)((double)SpinSystem[LoopNumA+1]*(double)pow(-1.0,(long long)(SpinSystem[LoopNumA])%Size+(long long)(SpinSystem[LoopNumA])/Size));
        //Msz=Msz+(double)((double)SpinSystem[LoopNumA+1]*(double)pow(-1.0,(long long)(SpinSystem[LoopNumA])%Size+(long long)(SpinSystem[LoopNumA])/Size));;
        //printf("%d  , %d , %f, \n",SpinSystem[LoopNumA],SpinSystem[LoopNumA+1],\
        //(double)SpinSystem[LoopNumA+1]*pow(-1.0,(long long)(SpinSystem[LoopNumA])%Size+(long long)(SpinSystem[LoopNumA])/Size));
       // printf("%d,%d,%d,%d,%f \n",SpinSystem[LoopNumA],SpinSystem[LoopNumA]%Size,\
        (SpinSystem[LoopNumA])/Size,SpinSystem[LoopNumA+1],\
        (double)SpinSystem[LoopNumA+1]*pow(-1.0,(long long)(SpinSystem[LoopNumA])%Size+(long long)(SpinSystem[LoopNumA])/Size));
    }
    SingleAFM/=2.0;
    for(LoopNumA=0;LoopNumA<HoperatorNO*5;LoopNumA+=5)
    {

        if(Hoperator[LoopNumA]==-1)
        {
            continue;
        }
        else
        {
            switch(Hoperator[LoopNumA]%10)
            {
                case 1:
                    SpinSystem[Hoperator[LoopNumA+1]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+2]*3+1]*=-1;
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+1]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+1]*3]);
                    Widding[((Hoperator[LoopNumA]-1)/10)/SpinNO]+=(double)SpinSystem[Hoperator[LoopNumA+2]*3+1];
                    break;
                case 5:
                    SpinSystem[Hoperator[LoopNumA+1]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+2]*3+1]*=-1;
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+1]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+1]*3]);
                    Widding[((Hoperator[LoopNumA]-5)/10)/SpinNO]+=(double)SpinSystem[Hoperator[LoopNumA+2]*3+1];
                    break;
                case 6:
                    SpinSystem[Hoperator[LoopNumA+3]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+4]*3+1]*=-1;
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+3]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+3]*3]);
                    Widding[((Hoperator[LoopNumA]-6)/10)/SpinNO]+=(double)SpinSystem[Hoperator[LoopNumA+4]*3+1];
                    break;

                case 9:
                    SpinSystem[Hoperator[LoopNumA+1]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+2]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+3]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+4]*3+1]*=-1;
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+1]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+1]*3]);
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+3]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+3]*3]);
                    Widding[((Hoperator[LoopNumA]-9)/10)/SpinNO]+=(double)SpinSystem[Hoperator[LoopNumA+2]*3+1];
                    Widding[((Hoperator[LoopNumA]-9)/10)/SpinNO]+=(double)SpinSystem[Hoperator[LoopNumA+4]*3+1];
                    break;
            }
        }
        /*
        SingleAX1+=(double)SingleAFM;
        SingleAFM1+=(double)fabs(SingleAFM);
        SingleAFM2+=(double)pow(SingleAFM,2);
        SingleAFM4+=(double)pow(SingleAFM,4);
        SingleAFM6+=(double)pow(SingleAFM,6);
        */
        SingleAX1+=(double)SingleAFM;
        SingleAFM1+=(double)fabs(SingleAFM);
        SingleAFM2+=(double)(SingleAFM*SingleAFM);
        SingleAFM4+=(double)(SingleAFM*SingleAFM*SingleAFM*SingleAFM);
        SingleAFM6+=(double)(SingleAFM*SingleAFM*SingleAFM*SingleAFM*SingleAFM*SingleAFM);

    }

    if(HNO!=0)
    {

        //SingleAX1=(double)(pow(SingleAX1,2)+SingleAFM2)/(double)(HNO*(HNO+1));
        SingleAX1=(double)((double)((double)(SingleAX1*SingleAX1)+(double)SingleAFM2)/(double)(HNO*(HNO+1)));
        SingleAFM1/=(double)HNO;
        SingleAFM2/=(double)HNO;
        SingleAFM4/=(double)HNO;
        SingleAFM6/=(double)HNO;

    }
    else
    {
        /*
        SingleAFM1=(double)fabs(SingleAFM);
        SingleAFM2=(double)pow(SingleAFM,2);
        SingleAFM4=(double)pow(SingleAFM,4);
        SingleAFM6=(double)pow(SingleAFM,6);
        SingleAX1=(double)SingleAFM2;
        */
        SingleAFM1=(double)fabs(SingleAFM);
        SingleAFM2=(SingleAFM*SingleAFM);
        SingleAFM4=(SingleAFM*SingleAFM*SingleAFM*SingleAFM);
        SingleAFM6=(SingleAFM*SingleAFM*SingleAFM*SingleAFM*SingleAFM*SingleAFM);
        SingleAX1=(double)SingleAFM2;
    }
    for(LoopNumA=0;LoopNumA<SpinNO*3;LoopNumA+=3)
    {
        SingleMeasure+=SpinSystem[LoopNumA+1];
    }

    SingleMeasure*=SingleMeasure;
    SingleMeasure*=0.25;
    AFM1+=SingleAFM1;
    AFM2+=SingleAFM2;
    AFM4+=SingleAFM4;
    AFM6+=SingleAFM6;
    AX1+=(double)SingleAX1;
    Measure+=SingleMeasure;
    //printf("%4,%f",Widding[0],Widding[1]);

    //WiddingX+=pow(Widding[0],2);
    //WiddingY+=pow(Widding[1],2);
    WiddingX+=(double)(Widding[0]*Widding[0]);
    WiddingY+=(double)(Widding[1]*Widding[1]);
    free(Widding);
    //printf("%f",Widding[0]*Widding[0]);
}


void MeasureFuctJQ3(long long* SpinSystem,double* BondNOsystem,long long* Hoperator\
          ,long long &HNO,long long &Size,long long &SpinNO,long long &BondNO,long long &HoperatorNO\
          ,double &AFM,double &AFM1,double &AFM2,double &AFM4,double &AFM6,double &AX1,double &Measure\
          ,double &WiddingX,double &WiddingY,double &WiddingZ,double &HNOMeasure ,long long * BondNORecord)
{
    long long LoopNumA,LoopNumB,LoopNumC,WiddingNO;
    //double Measure;
    double SingleAFM,SingleAFM1,SingleAFM2,SingleAFM4,SingleAFM6,SingleAX1,SingleMeasure,Msz,*Widding,WiddingXTemp,WiddingYTemp;
    SingleAFM=0;
    SingleAFM1=0;
    SingleAFM2=0;
    SingleAFM4=0;
    SingleAFM6=0;
    SingleAX1=0;
    SingleMeasure=0;
    Msz=0;
    WiddingXTemp=0;
    WiddingYTemp=0;
    WiddingNO=(long long)(BondNO/SpinNO);
    Widding=(double *)malloc(WiddingNO*sizeof(double*));
    for(LoopNumA=0;LoopNumA<WiddingNO;LoopNumA+=1)
    {
        Widding[LoopNumA]=0.0;
    }
    for(LoopNumA=0;LoopNumA<SpinNO*3;LoopNumA+=3)
    {

        SingleAFM+=(double)((double)SpinSystem[LoopNumA+1]*(double)SpinSystem[LoopNumA]);
        //SingleAFM+=(double)((double)SpinSystem[LoopNumA+1]*(double)pow(-1.0,(long long)(SpinSystem[LoopNumA])%Size+(long long)(SpinSystem[LoopNumA])/Size));
        //Msz=Msz+(double)((double)SpinSystem[LoopNumA+1]*(double)pow(-1.0,(long long)(SpinSystem[LoopNumA])%Size+(long long)(SpinSystem[LoopNumA])/Size));;
        //printf("%d  , %d , %f, \n",SpinSystem[LoopNumA],SpinSystem[LoopNumA+1],\
        //(double)SpinSystem[LoopNumA+1]*pow(-1.0,(long long)(SpinSystem[LoopNumA])%Size+(long long)(SpinSystem[LoopNumA])/Size));
       // printf("%d,%d,%d,%d,%f \n",SpinSystem[LoopNumA],SpinSystem[LoopNumA]%Size,\
        (SpinSystem[LoopNumA])/Size,SpinSystem[LoopNumA+1],\
        (double)SpinSystem[LoopNumA+1]*pow(-1.0,(long long)(SpinSystem[LoopNumA])%Size+(long long)(SpinSystem[LoopNumA])/Size));
    }
    SingleAFM/=2.0;
    //printf("test MeasureFuct-a \n");
    for(LoopNumA=0;LoopNumA<HoperatorNO*7;LoopNumA+=7)
    {
        //printf("%d %d %d \n",LoopNumA,Hoperator[LoopNumA],Hoperator[LoopNumA+1]);
        if(Hoperator[LoopNumA]==-1)
        {
            continue;
        }
        else
        {
            switch(Hoperator[LoopNumA]&15)
            {
                case 1:
                    SpinSystem[Hoperator[LoopNumA+1]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+2]*3+1]*=-1;
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+1]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+1]*3]);
                    Widding[((long long)((Hoperator[LoopNumA]-1)>>4)/SpinNO)]+=(double)SpinSystem[Hoperator[LoopNumA+2]*3+1];
                    /*
                    if(SpinSystem[Hoperator[LoopNumA+1]*3+1]==SpinSystem[Hoperator[LoopNumA+2]*3+1])
                    {
                        printf("%d  %f  %f  \n",BondNORecord[((long long)(Hoperator[LoopNumA]>>4))*7],SpinSystem[Hoperator[LoopNumA+1]*3+1],SpinSystem[Hoperator[LoopNumA+2]*3+1]);

                    }
                    */
                    break;
                case 5:
                    SpinSystem[Hoperator[LoopNumA+1]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+2]*3+1]*=-1;
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+1]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+1]*3]);
                    Widding[(long long)(((Hoperator[LoopNumA]-5)>>4)/SpinNO)]+=(double)SpinSystem[Hoperator[LoopNumA+2]*3+1];
                    break;
                case 6:
                    SpinSystem[Hoperator[LoopNumA+3]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+4]*3+1]*=-1;
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+3]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+3]*3]);
                    Widding[(long long)(((Hoperator[LoopNumA]-6)>>4)/SpinNO)]+=(double)SpinSystem[Hoperator[LoopNumA+4]*3+1];
                    break;
                case 7:
                    SpinSystem[Hoperator[LoopNumA+5]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+6]*3+1]*=-1;
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+5]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+5]*3]);
                    Widding[(long long)(((Hoperator[LoopNumA]-7)>>4)/SpinNO)]+=(double)SpinSystem[Hoperator[LoopNumA+6]*3+1];
                    break;
                case 9:
                    SpinSystem[Hoperator[LoopNumA+1]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+2]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+3]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+4]*3+1]*=-1;
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+1]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+1]*3]);
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+3]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+3]*3]);
                    Widding[(long long)(((Hoperator[LoopNumA]-9)>>4)/SpinNO)]+=(double)SpinSystem[Hoperator[LoopNumA+2]*3+1];
                    Widding[(long long)(((Hoperator[LoopNumA]-9)>>4)/SpinNO)]+=(double)SpinSystem[Hoperator[LoopNumA+4]*3+1];
                    break;
                case 10:
                    SpinSystem[Hoperator[LoopNumA+1]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+2]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+5]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+6]*3+1]*=-1;
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+1]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+1]*3]);
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+5]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+5]*3]);
                    Widding[(long long)(((Hoperator[LoopNumA]-10)>>4)/SpinNO)]+=(double)SpinSystem[Hoperator[LoopNumA+2]*3+1];
                    Widding[(long long)(((Hoperator[LoopNumA]-10)>>4)/SpinNO)]+=(double)SpinSystem[Hoperator[LoopNumA+6]*3+1];
                    break;
                case 11:
                    SpinSystem[Hoperator[LoopNumA+3]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+4]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+5]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+6]*3+1]*=-1;
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+5]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+5]*3]);
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+3]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+3]*3]);
                    Widding[(long long)(((Hoperator[LoopNumA]-11)>>4)/SpinNO)]+=(double)SpinSystem[Hoperator[LoopNumA+6]*3+1];
                    Widding[(long long)(((Hoperator[LoopNumA]-11)>>4)/SpinNO)]+=(double)SpinSystem[Hoperator[LoopNumA+4]*3+1];
                    break;
                case 14:
                    SpinSystem[Hoperator[LoopNumA+1]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+2]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+3]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+4]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+5]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+6]*3+1]*=-1;
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+1]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+1]*3]);
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+5]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+5]*3]);
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+3]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+3]*3]);
                    Widding[(long long)(((Hoperator[LoopNumA]-14)>>4)/SpinNO)]+=(double)SpinSystem[Hoperator[LoopNumA+2]*3+1];
                    Widding[(long long)(((Hoperator[LoopNumA]-14)>>4)/SpinNO)]+=(double)SpinSystem[Hoperator[LoopNumA+6]*3+1];
                    Widding[(long long)(((Hoperator[LoopNumA]-14)>>4)/SpinNO)]+=(double)SpinSystem[Hoperator[LoopNumA+4]*3+1];
                    break;
                //default:
                    //system("pause");
            }
        }

        /*
        SingleAX1+=(double)SingleAFM;
        SingleAFM1+=(double)fabs(SingleAFM);
        SingleAFM2+=(double)pow(SingleAFM,2);
        SingleAFM4+=(double)pow(SingleAFM,4);
        SingleAFM6+=(double)pow(SingleAFM,6);
        */
        SingleAX1+=(double)SingleAFM;
        SingleAFM1+=(double)fabs(SingleAFM);
        SingleAFM2+=(double)(SingleAFM*SingleAFM);
        SingleAFM4+=(double)(SingleAFM*SingleAFM*SingleAFM*SingleAFM);
        SingleAFM6+=(double)(SingleAFM*SingleAFM*SingleAFM*SingleAFM*SingleAFM*SingleAFM);

    }
    //printf("test MeasureFuct-b \n");
    if(HNO!=0)
    {

        //SingleAX1=(double)(pow(SingleAX1,2)+SingleAFM2)/(double)(HNO*(HNO+1));
        SingleAX1=(double)((double)((double)(SingleAX1*SingleAX1)+(double)SingleAFM2)/(double)(HNO*(HNO+1)));
        SingleAFM1/=(double)HNO;
        SingleAFM2/=(double)HNO;
        SingleAFM4/=(double)HNO;
        SingleAFM6/=(double)HNO;

    }
    else
    {
        /*
        SingleAFM1=(double)fabs(SingleAFM);
        SingleAFM2=(double)pow(SingleAFM,2);
        SingleAFM4=(double)pow(SingleAFM,4);
        SingleAFM6=(double)pow(SingleAFM,6);
        SingleAX1=(double)SingleAFM2;
        */
        SingleAFM1=(double)fabs(SingleAFM);
        SingleAFM2=(SingleAFM*SingleAFM);
        SingleAFM4=(SingleAFM*SingleAFM*SingleAFM*SingleAFM);
        SingleAFM6=(SingleAFM*SingleAFM*SingleAFM*SingleAFM*SingleAFM*SingleAFM);
        SingleAX1=(double)SingleAFM2;
    }
    //printf("test MeasureFuct-c \n");
    for(LoopNumA=0;LoopNumA<SpinNO*3;LoopNumA+=3)
    {
        SingleMeasure+=SpinSystem[LoopNumA+1];
    }

    SingleMeasure*=SingleMeasure;
    SingleMeasure*=0.25;
    AFM1+=SingleAFM1;
    AFM2+=SingleAFM2;
    AFM4+=SingleAFM4;
    AFM6+=SingleAFM6;
    AX1+=(double)SingleAX1;
    Measure+=SingleMeasure;
    //printf("%4,%f",Widding[0],Widding[1]);

    //WiddingX+=pow(Widding[0],2);
    //WiddingY+=pow(Widding[1],2);
   // printf("test MeasureFuct-d \n");
    for(LoopNumA = 0 ; LoopNumA<(long long)(BondNO/SpinNO) ; LoopNumA+=2 )
    {
        WiddingXTemp+=Widding[LoopNumA];
        WiddingYTemp+=Widding[LoopNumA+1];
    }
    WiddingX+=WiddingXTemp*WiddingXTemp;
    WiddingY+=WiddingYTemp*WiddingYTemp;

    //printf("test MeasureFuct-e \n");
    free(Widding);
    //printf("%f",Widding[0]*Widding[0]);
    //printf("test MeasureFuct-f \n");
}

void MeasureFuctJQ3_3D(long long* SpinSystem,double* BondNOsystem,long long* Hoperator\
          ,long long &HNO,long long &Size,long long &SpinNO,long long &SingleSpinNO,long long &BondNO,long long &HoperatorNO\
          ,double &AFM,double &AFM1,double &AFM2,double &AFM4,double &AFM6,double &AX1,double &AFM1abs,double &Measure\
          ,double &WiddingX,double &WiddingY,double &WiddingZ,double &HNOMeasure ,long long* BondNORecord\
          ,long long &XSize,long long &YSize,long long &ZSize,double &VBSDx,double &VBSDy,double &VBSD)
{
    long long LoopNumA,LoopNumB,LoopNumC,WiddingNO,WiddingTemp,Factor,Index;
    //double Measure;
    double SingleAFM,SingleAFM1,SingleAFM2,SingleAFM4,SingleAFM6,SingleAX1,SingleMeasure,Msz,*Widding,WiddingXTemp,WiddingYTemp,WiddingZTemp,\
    SingleVBSDx,SingleVBSDy,SingleVBSD;
    SingleAFM=0;
    SingleAFM1=0;
    SingleAFM2=0;
    SingleAFM4=0;
    SingleAFM6=0;
    SingleAX1=0;
    SingleMeasure=0;
    Msz=0;
    WiddingXTemp=0;
    WiddingYTemp=0;
    WiddingZTemp=0;
    WiddingNO= 3 ;
    SingleVBSDx=0;
    SingleVBSDy=0;
    SingleVBSD=0;
    Widding=(double *)malloc(WiddingNO*sizeof(double*));
    for(LoopNumA=0;LoopNumA<WiddingNO;LoopNumA+=1)
    {
        Widding[LoopNumA]=0.0;
    }
    for(LoopNumA=0;LoopNumA<SpinNO*3;LoopNumA+=3)
    {

        SingleAFM+=(double)((double)SpinSystem[LoopNumA+1]*(double)SpinSystem[LoopNumA]);
        //SingleAFM+=(double)((double)SpinSystem[LoopNumA+1]*(double)pow(-1.0,(long long)(SpinSystem[LoopNumA])%Size+(long long)(SpinSystem[LoopNumA])/Size));
        //Msz=Msz+(double)((double)SpinSystem[LoopNumA+1]*(double)pow(-1.0,(long long)(SpinSystem[LoopNumA])%Size+(long long)(SpinSystem[LoopNumA])/Size));;
        //printf("%d  , %d , %f, \n",SpinSystem[LoopNumA],SpinSystem[LoopNumA+1],\
        //(double)SpinSystem[LoopNumA+1]*pow(-1.0,(long long)(SpinSystem[LoopNumA])%Size+(long long)(SpinSystem[LoopNumA])/Size));
       // printf("%d,%d,%d,%d,%f \n",SpinSystem[LoopNumA],SpinSystem[LoopNumA]%Size,\
        (SpinSystem[LoopNumA])/Size,SpinSystem[LoopNumA+1],\
        (double)SpinSystem[LoopNumA+1]*pow(-1.0,(long long)(SpinSystem[LoopNumA])%Size+(long long)(SpinSystem[LoopNumA])/Size));
    }
    SingleAFM/=2.0;
    //printf("test MeasureFuct-a \n");
    for(LoopNumA=0;LoopNumA<HoperatorNO*7;LoopNumA+=7)
    {
        //printf("%d %d %d \n",LoopNumA,Hoperator[LoopNumA],Hoperator[LoopNumA+1]);
        if(Hoperator[LoopNumA]==-1)
        {
            continue;
        }
        else
        {
            switch(Hoperator[LoopNumA]&15)
            {
                case 1:
                    SpinSystem[Hoperator[LoopNumA+1]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+2]*3+1]*=-1;
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+1]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+1]*3]);
                    if((Hoperator[LoopNumA]-1)>>4<ZSize*SingleSpinNO*2)
                    {
                        Widding[(long long)((((Hoperator[LoopNumA]-1)>>4)/SingleSpinNO)%2)]+=(double)SpinSystem[Hoperator[LoopNumA+2]*3+1];

                    }
                    else
                    {
                        Widding[2]+=(double)SpinSystem[Hoperator[LoopNumA+2]*3+1];

                    }

                    /*
                    if(SpinSystem[Hoperator[LoopNumA+1]*3+1]==SpinSystem[Hoperator[LoopNumA+2]*3+1])
                    {
                        printf("%d  %f  %f  \n",BondNORecord[((long long)(Hoperator[LoopNumA]>>4))*7],SpinSystem[Hoperator[LoopNumA+1]*3+1],SpinSystem[Hoperator[LoopNumA+2]*3+1]);

                    }
                    */
                    break;
                case 5:
                    WiddingTemp=(long long)(((long long)((Hoperator[LoopNumA]-5)>>4)-SingleSpinNO*3*ZSize)/SingleSpinNO)%2;
                    SpinSystem[Hoperator[LoopNumA+1]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+2]*3+1]*=-1;
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+1]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+1]*3]);
                    Widding[WiddingTemp]+=(double)SpinSystem[Hoperator[LoopNumA+2]*3+1];
                    break;
                   //(long long)(((long long)((Hoperator[LoopNumA]-5)>>4)-SingleSpinNO*3*ZSize)/SingleSpinNO)%2
                case 6:
                    WiddingTemp=(long long)(((long long)((Hoperator[LoopNumA]-6)>>4)-SingleSpinNO*3*ZSize)/SingleSpinNO)%2;
                    SpinSystem[Hoperator[LoopNumA+3]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+4]*3+1]*=-1;
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+3]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+3]*3]);
                    Widding[WiddingTemp]+=(double)SpinSystem[Hoperator[LoopNumA+4]*3+1];
                    break;
                case 7:
                    WiddingTemp=(long long)(((long long)((Hoperator[LoopNumA]-7)>>4)-SingleSpinNO*3*ZSize)/SingleSpinNO)%2;
                    SpinSystem[Hoperator[LoopNumA+5]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+6]*3+1]*=-1;
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+5]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+5]*3]);
                    Widding[WiddingTemp]+=(double)SpinSystem[Hoperator[LoopNumA+6]*3+1];
                    break;
                case 9:
                    WiddingTemp=(long long)(((long long)((Hoperator[LoopNumA]-9)>>4)-SingleSpinNO*3*ZSize)/SingleSpinNO)%2;
                    SpinSystem[Hoperator[LoopNumA+1]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+2]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+3]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+4]*3+1]*=-1;
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+1]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+1]*3]);
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+3]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+3]*3]);
                    Widding[WiddingTemp]+=(double)SpinSystem[Hoperator[LoopNumA+2]*3+1];
                    Widding[WiddingTemp]+=(double)SpinSystem[Hoperator[LoopNumA+4]*3+1];
                    break;
                case 10:
                    WiddingTemp=(long long)(((long long)((Hoperator[LoopNumA]-10)>>4)-SingleSpinNO*3*ZSize)/SingleSpinNO)%2;
                    SpinSystem[Hoperator[LoopNumA+1]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+2]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+5]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+6]*3+1]*=-1;
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+1]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+1]*3]);
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+5]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+5]*3]);
                    Widding[WiddingTemp]+=(double)SpinSystem[Hoperator[LoopNumA+2]*3+1];
                    Widding[WiddingTemp]+=(double)SpinSystem[Hoperator[LoopNumA+6]*3+1];
                    break;
                case 11:
                    WiddingTemp=(long long)(((long long)((Hoperator[LoopNumA]-11)>>4)-SingleSpinNO*3*ZSize)/SingleSpinNO)%2;
                    SpinSystem[Hoperator[LoopNumA+3]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+4]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+5]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+6]*3+1]*=-1;
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+5]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+5]*3]);
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+3]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+3]*3]);
                    Widding[WiddingTemp]+=(double)SpinSystem[Hoperator[LoopNumA+6]*3+1];
                    Widding[WiddingTemp]+=(double)SpinSystem[Hoperator[LoopNumA+4]*3+1];
                    break;
                case 14:
                    WiddingTemp=(long long)(((long long)((Hoperator[LoopNumA]-14)>>4)-SingleSpinNO*3*ZSize)/SingleSpinNO)%2;
                    SpinSystem[Hoperator[LoopNumA+1]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+2]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+3]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+4]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+5]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+6]*3+1]*=-1;
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+1]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+1]*3]);
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+5]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+5]*3]);
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+3]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+3]*3]);
                    Widding[WiddingTemp]+=(double)SpinSystem[Hoperator[LoopNumA+2]*3+1];
                    Widding[WiddingTemp]+=(double)SpinSystem[Hoperator[LoopNumA+6]*3+1];
                    Widding[WiddingTemp]+=(double)SpinSystem[Hoperator[LoopNumA+4]*3+1];
                    break;
                //default:
                    //system("pause");
            }
        }

        /*
        SingleAX1+=(double)SingleAFM;
        SingleAFM1+=(double)fabs(SingleAFM);
        SingleAFM2+=(double)pow(SingleAFM,2);
        SingleAFM4+=(double)pow(SingleAFM,4);
        SingleAFM6+=(double)pow(SingleAFM,6);
        */
        SingleAX1+=(double)SingleAFM;
        SingleAFM1+=(double)fabs(SingleAFM);
        SingleAFM2+=(double)(SingleAFM*SingleAFM);
        SingleAFM4+=(double)(SingleAFM*SingleAFM*SingleAFM*SingleAFM);
        SingleAFM6+=(double)(SingleAFM*SingleAFM*SingleAFM*SingleAFM*SingleAFM*SingleAFM);

    }
    //printf("test MeasureFuct-b \n");
    if(HNO!=0)
    {

        //SingleAX1=(double)(pow(SingleAX1,2)+SingleAFM2)/(double)(HNO*(HNO+1));
        SingleAX1=(double)((double)((double)(SingleAX1*SingleAX1)+(double)SingleAFM2)/(double)(HNO*(HNO+1)));
        SingleAFM1/=(double)HNO;
        SingleAFM2/=(double)HNO;
        SingleAFM4/=(double)HNO;
        SingleAFM6/=(double)HNO;

    }
    else
    {
        /*
        SingleAFM1=(double)fabs(SingleAFM);
        SingleAFM2=(double)pow(SingleAFM,2);
        SingleAFM4=(double)pow(SingleAFM,4);
        SingleAFM6=(double)pow(SingleAFM,6);
        SingleAX1=(double)SingleAFM2;
        */
        SingleAFM1=(double)fabs(SingleAFM);
        SingleAFM2=(SingleAFM*SingleAFM);
        SingleAFM4=(SingleAFM*SingleAFM*SingleAFM*SingleAFM);
        SingleAFM6=(SingleAFM*SingleAFM*SingleAFM*SingleAFM*SingleAFM*SingleAFM);
        SingleAX1=(double)SingleAFM2;
    }
    //printf("test MeasureFuct-c \n");
    for(LoopNumA=0;LoopNumA<SpinNO*3;LoopNumA+=3)
    {
        SingleMeasure+=(double)SpinSystem[LoopNumA+1];
    }

    for(LoopNumA=0;LoopNumA<ZSize;LoopNumA+=1)
    {
        //Factor=-1;
        for(LoopNumB=0;LoopNumB<YSize;LoopNumB+=1)
        {
           Factor=-1;
           for(LoopNumC=0;LoopNumC<XSize;LoopNumC+=1)
           {
            Index = (LoopNumA*SingleSpinNO*2+LoopNumB*XSize+LoopNumC)*6;
            SingleVBSDx += (double)(Factor*SpinSystem[BondNORecord[Index]*3+1]*SpinSystem[BondNORecord[Index+1]*3+1]);
            Factor*=-1;

           }
        }
    }
    for(LoopNumA=0;LoopNumA<ZSize;LoopNumA+=1)
    {
        Factor=-1;
        for(LoopNumB=0;LoopNumB<YSize;LoopNumB+=1)
        {
           for(LoopNumC=0;LoopNumC<XSize;LoopNumC+=1)
           {
            Index = (LoopNumA*SingleSpinNO*2+LoopNumB*XSize+LoopNumC+SingleSpinNO)*6;
            SingleVBSDy += (double)(Factor*SpinSystem[BondNORecord[Index]*3+1]*SpinSystem[BondNORecord[Index+1]*3+1]);
           }
           Factor*=-1;
        }

    }
    SingleVBSD=SingleVBSDx*SingleVBSDx + SingleVBSDy*SingleVBSDy;

    //BondNORecord
    SingleMeasure*=SingleMeasure;
    SingleMeasure*=0.25;
    AFM1+=SingleAFM1;
    AFM2+=SingleAFM2;
    AFM4+=SingleAFM4;
    AFM6+=SingleAFM6;
    AX1+=(double)SingleAX1;
    Measure+=SingleMeasure;
    HNOMeasure+=(double)HNO;
    VBSDx+=SingleVBSDx*0.25;
    VBSDy+=SingleVBSDy*0.25;
    VBSD+=SingleVBSD*0.0625;
    //printf("%4,%f",Widding[0],Widding[1]);

    //WiddingX+=pow(Widding[0],2);
    //WiddingY+=pow(Widding[1],2);
   // printf("test MeasureFuct-d \n");
    /*
    for(LoopNumA = 0 ; LoopNumA<(long long)(BondNO/SpinNO) ; LoopNumA+=2 )
    {
        WiddingXTemp+=Widding[LoopNumA];
        WiddingYTemp+=Widding[LoopNumA+1];
        WiddingZTemp+=Widding[LoopNumA+2]
    }
    */
    WiddingX+=Widding[0]*Widding[0];
    WiddingY+=Widding[1]*Widding[1];
    WiddingZ+=Widding[2]*Widding[2];
    //printf("test MeasureFuct-e \n");
    free(Widding);
    //printf("%f",Widding[0]*Widding[0]);
    //printf("test MeasureFuct-f \n");
}

void MeasureFuctJQ3_Honeycomb(long long* SpinSystem,double* BondNOsystem,long long* Hoperator\
          ,long long &HNO,long long &Size,long long &SpinNO,long long &BondNO,long long &HoperatorNO\
          ,double &AFM,double &AFM1,double &AFM2,double &AFM4,double &AFM6,double &AX1,double &AFM1abs,double &Measure\
          ,double &WiddingX,double &WiddingY,double &WiddingZ,double &HNOMeasure ,long long * BondNORecord)
{
    long long LoopNumA,LoopNumB,LoopNumC,WiddingNO;
    //double Measure;
    double SingleAFM,SingleAFM1,SingleAFM2,SingleAFM4,SingleAFM6,SingleAX1,SingleMeasure,Msz,*Widding,WiddingXTemp,WiddingYTemp,SingleAFMabs;
    SingleAFM=0;
    SingleAFM1=0;
    SingleAFM2=0;
    SingleAFM4=0;
    SingleAFM6=0;
    SingleAX1=0;
    SingleAFMabs=0;
    SingleMeasure=0;
    Msz=0;
    WiddingXTemp=0;
    WiddingYTemp=0;
    WiddingNO= 2 ;//X,y 2 Direction
    Widding=(double *)malloc(WiddingNO*sizeof(double*));
    for(LoopNumA=0;LoopNumA<WiddingNO;LoopNumA+=1)
    {
        Widding[LoopNumA]=0.0;
    }
    for(LoopNumA=0;LoopNumA<SpinNO*3;LoopNumA+=3)
    {

        SingleAFM+=(double)((double)SpinSystem[LoopNumA+1]*(double)SpinSystem[LoopNumA]);
        //SingleAFM+=(double)((double)SpinSystem[LoopNumA+1]*(double)pow(-1.0,(long long)(SpinSystem[LoopNumA])%Size+(long long)(SpinSystem[LoopNumA])/Size));
        //Msz=Msz+(double)((double)SpinSystem[LoopNumA+1]*(double)pow(-1.0,(long long)(SpinSystem[LoopNumA])%Size+(long long)(SpinSystem[LoopNumA])/Size));;
        //printf("%d  , %d , %f, \n",SpinSystem[LoopNumA],SpinSystem[LoopNumA+1],\
        //(double)SpinSystem[LoopNumA+1]*pow(-1.0,(long long)(SpinSystem[LoopNumA])%Size+(long long)(SpinSystem[LoopNumA])/Size));
       // printf("%d,%d,%d,%d,%f \n",SpinSystem[LoopNumA],SpinSystem[LoopNumA]%Size,\
        (SpinSystem[LoopNumA])/Size,SpinSystem[LoopNumA+1],\
        (double)SpinSystem[LoopNumA+1]*pow(-1.0,(long long)(SpinSystem[LoopNumA])%Size+(long long)(SpinSystem[LoopNumA])/Size));
    }
    SingleAFM/=2.0;
    SingleAFMabs=(double)fabs(SingleAFM);
    //printf("test MeasureFuct-a \n");
    for(LoopNumA=0;LoopNumA<HoperatorNO*7;LoopNumA+=7)
    {
        //printf("%d %d %d \n",LoopNumA,Hoperator[LoopNumA],Hoperator[LoopNumA+1]);
        if(Hoperator[LoopNumA]==-1)
        {
            continue;
        }
        else
        {
            switch(Hoperator[LoopNumA]&15)
            {
                case 1:
                    SpinSystem[Hoperator[LoopNumA+1]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+2]*3+1]*=-1;
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+1]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+1]*3]);
                    if(((long long)((Hoperator[LoopNumA]-1)>>4))< SpinNO)
                    {
                        Widding[0]+=(double)SpinSystem[Hoperator[LoopNumA+2]*3+1];
                    }
                    else
                    {
                        Widding[1]+=(double)SpinSystem[Hoperator[LoopNumA+2]*3+1];
                    }

                    /*
                    if(SpinSystem[Hoperator[LoopNumA+1]*3+1]==SpinSystem[Hoperator[LoopNumA+2]*3+1])
                    {
                        printf("%d  %f  %f  \n",BondNORecord[((long long)(Hoperator[LoopNumA]>>4))*7],SpinSystem[Hoperator[LoopNumA+1]*3+1],SpinSystem[Hoperator[LoopNumA+2]*3+1]);

                    }
                    */
                    break;
                case 5://2+3
                    SpinSystem[Hoperator[LoopNumA+1]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+2]*3+1]*=-1;
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+1]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+1]*3]);
                    Widding[1]+=(double)SpinSystem[Hoperator[LoopNumA+2]*3+1];
                    break;
                case 6://2+4
                    SpinSystem[Hoperator[LoopNumA+3]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+4]*3+1]*=-1;
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+3]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+3]*3]);
                    Widding[0]+=(double)SpinSystem[Hoperator[LoopNumA+4]*3+1];
                    break;
                case 7://2+5
                    SpinSystem[Hoperator[LoopNumA+5]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+6]*3+1]*=-1;
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+5]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+5]*3]);
                    Widding[0]+=(double)SpinSystem[Hoperator[LoopNumA+6]*3+1];
                    break;
                case 9://2+3+4
                    SpinSystem[Hoperator[LoopNumA+1]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+2]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+3]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+4]*3+1]*=-1;
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+1]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+1]*3]);
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+3]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+3]*3]);
                    Widding[1]+=(double)SpinSystem[Hoperator[LoopNumA+2]*3+1];
                    Widding[0]+=(double)SpinSystem[Hoperator[LoopNumA+4]*3+1];
                    break;
                case 10://2+3+5
                    SpinSystem[Hoperator[LoopNumA+1]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+2]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+5]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+6]*3+1]*=-1;
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+1]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+1]*3]);
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+5]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+5]*3]);
                    Widding[1]+=(double)SpinSystem[Hoperator[LoopNumA+2]*3+1];
                    Widding[0]+=(double)SpinSystem[Hoperator[LoopNumA+6]*3+1];
                    break;
                case 11://2+4+5
                    SpinSystem[Hoperator[LoopNumA+3]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+4]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+5]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+6]*3+1]*=-1;
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+5]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+5]*3]);
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+3]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+3]*3]);
                    Widding[0]+=(double)SpinSystem[Hoperator[LoopNumA+6]*3+1];
                    Widding[0]+=(double)SpinSystem[Hoperator[LoopNumA+4]*3+1];
                    break;
                case 14:
                    SpinSystem[Hoperator[LoopNumA+1]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+2]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+3]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+4]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+5]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+6]*3+1]*=-1;
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+1]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+1]*3]);
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+5]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+5]*3]);
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+3]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+3]*3]);
                    Widding[1]+=(double)SpinSystem[Hoperator[LoopNumA+2]*3+1];
                    Widding[0]+=(double)SpinSystem[Hoperator[LoopNumA+6]*3+1];
                    Widding[0]+=(double)SpinSystem[Hoperator[LoopNumA+4]*3+1];
                    break;
                //default:
                    //system("pause");
            }
        }

        /*
        SingleAX1+=(double)SingleAFM;
        SingleAFM1+=(double)fabs(SingleAFM);
        SingleAFM2+=(double)pow(SingleAFM,2);
        SingleAFM4+=(double)pow(SingleAFM,4);
        SingleAFM6+=(double)pow(SingleAFM,6);
        */
        SingleAX1+=(double)SingleAFM;
        SingleAFM1+=(double)fabs(SingleAFM);
        SingleAFM2+=(double)(SingleAFM*SingleAFM);
        SingleAFM4+=(double)(SingleAFM*SingleAFM*SingleAFM*SingleAFM);
        SingleAFM6+=(double)(SingleAFM*SingleAFM*SingleAFM*SingleAFM*SingleAFM*SingleAFM);

    }
    //printf("test MeasureFuct-b \n");
    if(HNO!=0)
    {

        //SingleAX1=(double)(pow(SingleAX1,2)+SingleAFM2)/(double)(HNO*(HNO+1));
        SingleAX1=(double)((double)((double)(SingleAX1*SingleAX1)+(double)SingleAFM2)/(double)(HNO*(HNO+1)));
        SingleAFM1/=(double)HNO;
        SingleAFM2/=(double)HNO;
        SingleAFM4/=(double)HNO;
        SingleAFM6/=(double)HNO;

    }
    else
    {
        /*
        SingleAFM1=(double)fabs(SingleAFM);
        SingleAFM2=(double)pow(SingleAFM,2);
        SingleAFM4=(double)pow(SingleAFM,4);
        SingleAFM6=(double)pow(SingleAFM,6);
        SingleAX1=(double)SingleAFM2;
        */
        SingleAFM1=(double)fabs(SingleAFM);
        SingleAFM2=(SingleAFM*SingleAFM);
        SingleAFM4=(SingleAFM*SingleAFM*SingleAFM*SingleAFM);
        SingleAFM6=(SingleAFM*SingleAFM*SingleAFM*SingleAFM*SingleAFM*SingleAFM);
        SingleAX1=(double)SingleAFM2;
    }
    //printf("test MeasureFuct-c \n");
    for(LoopNumA=0;LoopNumA<SpinNO*3;LoopNumA+=3)
    {
        SingleMeasure+=SpinSystem[LoopNumA+1];
    }

    SingleMeasure*=SingleMeasure;
    SingleMeasure*=0.25;
    AFM1+=SingleAFM1;
    AFM2+=SingleAFM2;
    AFM4+=SingleAFM4;
    AFM6+=SingleAFM6;
    AX1+=(double)SingleAX1;
    AFM1abs+=SingleAFMabs;
    //printf("%f \n",AFM1abs);
    Measure+=SingleMeasure;
    HNOMeasure+=(double)HNO;
    //printf("%4,%f",Widding[0],Widding[1]);

    //WiddingX+=pow(Widding[0],2);
    //WiddingY+=pow(Widding[1],2);
   // printf("test MeasureFuct-d \n");
    /*
    for(LoopNumA = 0 ; LoopNumA<(long long)(BondNO/SpinNO) ; LoopNumA+=2 )
    {
        WiddingXTemp+=Widding[LoopNumA];
        WiddingYTemp+=Widding[LoopNumA+1];
    }
    */
    WiddingX+=Widding[0]*Widding[0];
    WiddingY+=Widding[1]*Widding[1];
    //printf("%f %f \n", Widding[1],WiddingY);
    //printf("test MeasureFuct-e \n");
    free(Widding);

    //printf("test MeasureFuct-f \n");
}

void MeasureFuctJQ3_Honeycomb_SpinHalf(long long* SpinSystem,double* BondNOsystem,long long* Hoperator\
          ,long long &HNO,long long &Size,long long &SpinNO,long long &BondNO,long long &HoperatorNO\
          ,double &AFM,double &AFM1,double &AFM2,double &AFM4,double &AFM6,double &AX1,double &AFM1abs,double &Measure\
          ,double &WiddingX,double &WiddingY,double &WiddingZ,double &HNOMeasure ,long long * BondNORecord)
{
    long long LoopNumA,LoopNumB,LoopNumC,WiddingNO;
    //double Measure;
    double SingleAFM,SingleAFM1,SingleAFM2,SingleAFM4,SingleAFM6,SingleAX1,SingleMeasure,Msz,*Widding,WiddingXTemp,WiddingYTemp,SingleAFMabs;
    SingleAFM=0;
    SingleAFM1=0;
    SingleAFM2=0;
    SingleAFM4=0;
    SingleAFM6=0;
    SingleAX1=0;
    SingleAFMabs=0;
    SingleMeasure=0;
    Msz=0;
    WiddingXTemp=0;
    WiddingYTemp=0;
    WiddingNO= 2 ;//X,y 2 Direction
    Widding=(double *)malloc(WiddingNO*sizeof(double*));
    for(LoopNumA=0;LoopNumA<WiddingNO;LoopNumA+=1)
    {
        Widding[LoopNumA]=0.0;
    }
    for(LoopNumA=0;LoopNumA<SpinNO*3;LoopNumA+=3)
    {

        SingleAFM+=(double)((double)SpinSystem[LoopNumA+1]*(double)SpinSystem[LoopNumA]);
        //SingleAFM+=(double)((double)SpinSystem[LoopNumA+1]*(double)pow(-1.0,(long long)(SpinSystem[LoopNumA])%Size+(long long)(SpinSystem[LoopNumA])/Size));
        //Msz=Msz+(double)((double)SpinSystem[LoopNumA+1]*(double)pow(-1.0,(long long)(SpinSystem[LoopNumA])%Size+(long long)(SpinSystem[LoopNumA])/Size));;
        //printf("%d  , %d , %f, \n",SpinSystem[LoopNumA],SpinSystem[LoopNumA+1],\
        //(double)SpinSystem[LoopNumA+1]*pow(-1.0,(long long)(SpinSystem[LoopNumA])%Size+(long long)(SpinSystem[LoopNumA])/Size));
       // printf("%d,%d,%d,%d,%f \n",SpinSystem[LoopNumA],SpinSystem[LoopNumA]%Size,\
        (SpinSystem[LoopNumA])/Size,SpinSystem[LoopNumA+1],\
        (double)SpinSystem[LoopNumA+1]*pow(-1.0,(long long)(SpinSystem[LoopNumA])%Size+(long long)(SpinSystem[LoopNumA])/Size));
    }
    SingleAFM/=2.0;
    SingleAFMabs=(double)fabs(SingleAFM);
    //printf("test MeasureFuct-a \n");
    for(LoopNumA=0;LoopNumA<HoperatorNO*7;LoopNumA+=7)
    {
        //printf("%d %d %d \n",LoopNumA,Hoperator[LoopNumA],Hoperator[LoopNumA+1]);
        if(Hoperator[LoopNumA]==-1)
        {
            continue;
        }
        else
        {
            switch(Hoperator[LoopNumA]&15)
            {
                case 1:
                    SpinSystem[Hoperator[LoopNumA+1]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+2]*3+1]*=-1;
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+1]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+1]*3]);
                    if(((long long)((Hoperator[LoopNumA]-1)>>4))< SpinNO-1)
                    {
                        Widding[0]+=(double)SpinSystem[Hoperator[LoopNumA+2]*3+1];
                    }
                    else
                    {
                        Widding[1]+=(double)SpinSystem[Hoperator[LoopNumA+2]*3+1];
                    }

                    /*
                    if(SpinSystem[Hoperator[LoopNumA+1]*3+1]==SpinSystem[Hoperator[LoopNumA+2]*3+1])
                    {
                        printf("%d  %f  %f  \n",BondNORecord[((long long)(Hoperator[LoopNumA]>>4))*7],SpinSystem[Hoperator[LoopNumA+1]*3+1],SpinSystem[Hoperator[LoopNumA+2]*3+1]);

                    }
                    */
                    break;
                case 5://2+3
                    SpinSystem[Hoperator[LoopNumA+1]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+2]*3+1]*=-1;
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+1]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+1]*3]);
                    Widding[1]+=(double)SpinSystem[Hoperator[LoopNumA+2]*3+1];
                    break;
                case 6://2+4
                    SpinSystem[Hoperator[LoopNumA+3]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+4]*3+1]*=-1;
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+3]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+3]*3]);
                    Widding[0]+=(double)SpinSystem[Hoperator[LoopNumA+4]*3+1];
                    break;
                case 7://2+5
                    SpinSystem[Hoperator[LoopNumA+5]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+6]*3+1]*=-1;
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+5]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+5]*3]);
                    Widding[0]+=(double)SpinSystem[Hoperator[LoopNumA+6]*3+1];
                    break;
                case 9://2+3+4
                    SpinSystem[Hoperator[LoopNumA+1]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+2]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+3]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+4]*3+1]*=-1;
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+1]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+1]*3]);
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+3]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+3]*3]);
                    Widding[1]+=(double)SpinSystem[Hoperator[LoopNumA+2]*3+1];
                    Widding[0]+=(double)SpinSystem[Hoperator[LoopNumA+4]*3+1];
                    break;
                case 10://2+3+5
                    SpinSystem[Hoperator[LoopNumA+1]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+2]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+5]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+6]*3+1]*=-1;
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+1]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+1]*3]);
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+5]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+5]*3]);
                    Widding[1]+=(double)SpinSystem[Hoperator[LoopNumA+2]*3+1];
                    Widding[0]+=(double)SpinSystem[Hoperator[LoopNumA+6]*3+1];
                    break;
                case 11://2+4+5
                    SpinSystem[Hoperator[LoopNumA+3]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+4]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+5]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+6]*3+1]*=-1;
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+5]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+5]*3]);
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+3]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+3]*3]);
                    Widding[0]+=(double)SpinSystem[Hoperator[LoopNumA+6]*3+1];
                    Widding[0]+=(double)SpinSystem[Hoperator[LoopNumA+4]*3+1];
                    break;
                case 14:
                    SpinSystem[Hoperator[LoopNumA+1]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+2]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+3]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+4]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+5]*3+1]*=-1;
                    SpinSystem[Hoperator[LoopNumA+6]*3+1]*=-1;
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+1]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+1]*3]);
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+5]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+5]*3]);
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+3]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+3]*3]);
                    Widding[1]+=(double)SpinSystem[Hoperator[LoopNumA+2]*3+1];
                    Widding[0]+=(double)SpinSystem[Hoperator[LoopNumA+6]*3+1];
                    Widding[0]+=(double)SpinSystem[Hoperator[LoopNumA+4]*3+1];
                    break;
                //default:
                    //system("pause");
            }
        }

        /*
        SingleAX1+=(double)SingleAFM;
        SingleAFM1+=(double)fabs(SingleAFM);
        SingleAFM2+=(double)pow(SingleAFM,2);
        SingleAFM4+=(double)pow(SingleAFM,4);
        SingleAFM6+=(double)pow(SingleAFM,6);
        */
        SingleAX1+=(double)SingleAFM;
        SingleAFM1+=(double)fabs(SingleAFM);
        SingleAFM2+=(double)(SingleAFM*SingleAFM);
        SingleAFM4+=(double)(SingleAFM*SingleAFM*SingleAFM*SingleAFM);
        SingleAFM6+=(double)(SingleAFM*SingleAFM*SingleAFM*SingleAFM*SingleAFM*SingleAFM);

    }
    //printf("test MeasureFuct-b \n");
    if(HNO!=0)
    {

        //SingleAX1=(double)(pow(SingleAX1,2)+SingleAFM2)/(double)(HNO*(HNO+1));
        SingleAX1=(double)((double)((double)(SingleAX1*SingleAX1)+(double)SingleAFM2)/(double)(HNO*(HNO+1)));
        SingleAFM1/=(double)HNO;
        SingleAFM2/=(double)HNO;
        SingleAFM4/=(double)HNO;
        SingleAFM6/=(double)HNO;

    }
    else
    {
        /*
        SingleAFM1=(double)fabs(SingleAFM);
        SingleAFM2=(double)pow(SingleAFM,2);
        SingleAFM4=(double)pow(SingleAFM,4);
        SingleAFM6=(double)pow(SingleAFM,6);
        SingleAX1=(double)SingleAFM2;
        */
        SingleAFM1=(double)fabs(SingleAFM);
        SingleAFM2=(SingleAFM*SingleAFM);
        SingleAFM4=(SingleAFM*SingleAFM*SingleAFM*SingleAFM);
        SingleAFM6=(SingleAFM*SingleAFM*SingleAFM*SingleAFM*SingleAFM*SingleAFM);
        SingleAX1=(double)SingleAFM2;
    }
    //printf("test MeasureFuct-c \n");
    for(LoopNumA=0;LoopNumA<SpinNO*3;LoopNumA+=3)
    {
        SingleMeasure+=(double)SpinSystem[LoopNumA+1];
    }

    SingleMeasure*=SingleMeasure;
    SingleMeasure*=0.25;
    AFM1+=SingleAFM1;
    AFM2+=SingleAFM2;
    AFM4+=SingleAFM4;
    AFM6+=SingleAFM6;
    AFM1abs+=SingleAFMabs;
    AX1+=(double)SingleAX1;
    Measure+=SingleMeasure;
    HNOMeasure+=(double)HNO;
    //printf("%4,%f",Widding[0],Widding[1]);

    //WiddingX+=pow(Widding[0],2);
    //WiddingY+=pow(Widding[1],2);
   // printf("test MeasureFuct-d \n");
    /*
    for(LoopNumA = 0 ; LoopNumA<(long long)(BondNO/SpinNO) ; LoopNumA+=2 )
    {
        WiddingXTemp+=Widding[LoopNumA];
        WiddingYTemp+=Widding[LoopNumA+1];
    }
    */
    WiddingX+=Widding[0]*Widding[0];
    WiddingY+=Widding[1]*Widding[1];

    //printf("test MeasureFuct-e \n");
    free(Widding);
    //printf("%f",Widding[0]*Widding[0]);
    //printf("test MeasureFuct-f \n");
}

void MeasureFuct_1(long long* SpinSystem,double* BondNOsystem,long long* Hoperator\
          ,long long &HNO,long long &Size,long long &SpinNO,long long &BondNO,long long &HoperatorNO\
          ,double &AFM,double &AFM1,double &AFM2,double &AFM4,double &AFM6,double &AX1,double &Measure\
          ,double &WiddingX,double &WiddingY,double &WiddingZ)
{
    long long LoopNumA,LoopNumB,LoopNumC;
    //double Measure;
    double SingleAFM,SingleAFM1,SingleAFM2,SingleAFM4,SingleAFM6,SingleAX1,SingleMeasure,Msz,*Widding;
    SingleAFM=0;
    SingleAFM1=0;
    SingleAFM2=0;
    SingleAFM4=0;
    SingleAFM6=0;
    SingleAX1=0;
    SingleMeasure=0;
    Msz=0;
    for(LoopNumA=0;LoopNumA<SpinNO*3;LoopNumA+=3)
    {
        SingleAFM+=(double)((double)SpinSystem[LoopNumA+1]*SpinSystem[LoopNumA]);
        //SingleAFM+=(double)((double)SpinSystem[LoopNumA+1]*(double)pow(-1.0,(long long)(SpinSystem[LoopNumA])%Size+(long long)(SpinSystem[LoopNumA])/Size));

    }
    SingleAFM/=2.0;
    for(LoopNumA=0;LoopNumA<SpinNO*3;LoopNumA+=3)
    {
        SingleMeasure+=SpinSystem[LoopNumA+1];
    }
    //SingleAFM=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+1]*3+1]*(double)pow(-1.0,(long long)Hoperator[LoopNumA+1]%Size+(long long)Hoperator[LoopNumA+1]/Size));
    SingleAFM1=(double)fabs(SingleAFM);
    //SingleAFM2=(double)pow(SingleAFM,2);
    //SingleAFM4=(double)pow(SingleAFM,4);
    //SingleAFM6=(double)pow(SingleAFM,6);
    SingleAFM2=SingleAFM*SingleAFM;
    SingleAFM4=SingleAFM*SingleAFM*SingleAFM*SingleAFM;
    SingleAFM6=SingleAFM*SingleAFM*SingleAFM*SingleAFM*SingleAFM*SingleAFM;
    SingleAX1=(double)SingleAFM2;
    SingleMeasure*=SingleMeasure;
    SingleMeasure*=0.25;
    AFM1+=SingleAFM1;
    AFM2+=SingleAFM2;
    AFM4+=SingleAFM4;
    AFM6+=SingleAFM6;
    AX1+=SingleAX1;
    Measure+=SingleMeasure;
    //printf("%4,%f",Widding[0],Widding[1]);

    //WiddingX+=pow(Widding[0],2);
    //WiddingY+=pow(Widding[1],2);
    //free(Widding);
}


double MeasureMeans(double &AFM,double &AFM1,double &AFM2,double &AFM4,double &AFM6\
        ,double &AX1,double AFM1abs,double &Ususc,double &WiddingX,double &WiddingY,double &WiddingZ,double &HNOMeasure,double &TempW\
        ,long long &XSize,long long &YSize,double &Beta,long long &MeasureStep,long long &SpinNO\
        ,double &UsuscMent,double &AFM1Ment,double &AFM2Ment,double &AFM4Ment\
        ,double &AFM6Ment,double &AX1Ment,double &WindingXMent,double &WindingYMent,double &HNOMent,double &TempWMent)//每個測量的平均
{
    double Vol;
    Vol=(double)(SpinNO);
    UsuscMent=Ususc/(double)MeasureStep;
    //UsuscMent/=MeasureStep*Beta/SpinNO;
    AFM1Ment=AFM1/(double)MeasureStep;
    AFM1Ment/=Vol;

    AFM2Ment=AFM2/(double)MeasureStep;
    AFM2Ment/=(Vol*Vol);

    AFM4Ment=AFM4/(double)MeasureStep;
    AFM4Ment/=(Vol*Vol*Vol*Vol);

    AFM6Ment=AFM6/(double)MeasureStep;
    AFM6Ment/=(Vol*Vol*Vol*Vol*Vol*Vol);

    AX1Ment=(double)((double)AX1/(double)MeasureStep);
    AX1Ment/=(double)(Vol);
    AX1Ment*=(double)Beta;

    WindingXMent=(double)((double)WiddingX/(double)MeasureStep);
    WindingXMent/=(double)(XSize*XSize);

    WindingYMent=(double)((double)WiddingY/(double)MeasureStep);
    WindingYMent/=(double)(YSize*YSize);

    HNOMent=HNOMeasure/(double)MeasureStep;

    TempWMent=TempW/(double)MeasureStep;

    Ususc=0.0;
    AFM1=0.0;
    AFM2=0.0;
    AFM4=0.0;
    AFM6=0.0;
    AX1=0.0;
    WiddingX=0.0;
    WiddingY=0.0;
    TempW=0.0;

    //double Means;
    //Means=Data/(double)MeasureStep;
    //Means/=(double)XSize*YSize;
    /*
    UsuscMent[LoopNumA]=(double)(MeasureMeans(Measure,MeasureStep,XSize,YSize,0));
    UsuscMent[LoopNumA]=(double)(MeasureMeans(Measure,MeasureStep,XSize,YSize,0)*Beta/SpinNO);
    AFM1Ment[LoopNumA]=MeasureMeans(AFM1,MeasureStep,XSize,YSize,1);
    AFM2Ment[LoopNumA]=MeasureMeans(AFM2,MeasureStep,XSize,YSize,2);
    AFM4Ment[LoopNumA]=MeasureMeans(AFM4,MeasureStep,XSize,YSize,4);
    AFM6Ment[LoopNumA]=MeasureMeans(AFM6,MeasureStep,XSize,YSize,6);
    AX1Ment[LoopNumA]=Beta*MeasureMeans(AX1,MeasureStep,XSize,YSize,1);
    WindingXMent[LoopNumA]=MeasureMeans(WiddingX,MeasureStep,XSize,YSize,0);
    WindingXMent[LoopNumA]/=(double)(pow(XSize,2)/Beta);
    WindingYMent[LoopNumA]=MeasureMeans(WiddingY,MeasureStep,XSize,YSize,0);
    WindingYMent[LoopNumA]/=(double)(pow(YSize,2)/Beta);

    if(Choice!=0)
    {
      Means/=(double)pow(((double)XSize*(double)YSize),(double)Choice);
      //printf("%f \n",(double)pow((double)XSize*(double)YSize,Choice));
    }

    Data=0.0;
    */
    return 0;
}

double MeasureMeans_3D(double &AFM,double &AFM1,double &AFM2,double &AFM4,double &AFM6\
        ,double &AX1,double &AFM1abs,double &Ususc,double &WiddingX,double &WiddingY,double &WiddingZ,double &HNOMeasure,double &TempW\
        ,long long &XSize,long long &YSize,long long ZSize,double &Beta,long long &MeasureStep,long long &SpinNO,long long &SingleSpinNO\
        ,double &UsuscMent,double &AFM1Ment,double &AFM2Ment,double &AFM4Ment\
        ,double &AFM6Ment,double &AX1Ment,double &AFM1absMent,double &WindingXMent,double &WindingYMent,double &WindingZMent,double &HNOMent,double &TempWMent\
        ,double &VBSDx,double &VBSDy,double &VBSD,double &VBSDxMent,double &VBSDyMent, double &VBSDMent)//每個測量的平均
{
    double Vol;
    Vol=(double)(SpinNO);
    UsuscMent=Ususc/(double)MeasureStep;
    //UsuscMent/=MeasureStep*Beta/SpinNO;
    AFM1Ment=AFM1/(double)MeasureStep;
    AFM1Ment/=Vol;

    AFM2Ment=AFM2/(double)MeasureStep;
    AFM2Ment/=(Vol*Vol);

    AFM4Ment=AFM4/(double)MeasureStep;
    AFM4Ment/=(Vol*Vol*Vol*Vol);

    AFM6Ment=AFM6/(double)MeasureStep;
    AFM6Ment/=(Vol*Vol*Vol*Vol*Vol*Vol);

    AX1Ment=(double)((double)AX1/(double)MeasureStep);
    AX1Ment/=(double)(Vol);
    AX1Ment*=(double)Beta;

    WindingXMent=(double)((double)WiddingX/(double)MeasureStep);
    WindingXMent/=(double)(XSize*XSize);

    WindingYMent=(double)((double)WiddingY/(double)MeasureStep);
    WindingYMent/=(double)(YSize*YSize);

    WindingZMent=(double)((double)WiddingZ/(double)MeasureStep);
    WindingZMent/=(double)(ZSize*ZSize);

    HNOMent=HNOMeasure/(double)MeasureStep;

    TempWMent=TempW/(double)MeasureStep;

    VBSDxMent=VBSDx/(double)SpinNO/(double)MeasureStep;
    VBSDyMent=VBSDy/(double)SpinNO/(double)MeasureStep;
    VBSDMent=VBSD/(double)(SpinNO*SpinNO)/(double)MeasureStep;

    Ususc=0.0;
    AFM1=0.0;
    AFM2=0.0;
    AFM4=0.0;
    AFM6=0.0;
    AX1=0.0;
    WiddingX=0.0;
    WiddingY=0.0;
    WiddingZ=0.0;
    TempW=0.0;
    HNOMeasure=0.0;
    VBSDx=0.0;
    VBSDy=0.0;
    VBSD=0.0;

    //double Means;
    //Means=Data/(double)MeasureStep;
    //Means/=(double)XSize*YSize;
    /*
    UsuscMent[LoopNumA]=(double)(MeasureMeans(Measure,MeasureStep,XSize,YSize,0));
    UsuscMent[LoopNumA]=(double)(MeasureMeans(Measure,MeasureStep,XSize,YSize,0)*Beta/SpinNO);
    AFM1Ment[LoopNumA]=MeasureMeans(AFM1,MeasureStep,XSize,YSize,1);
    AFM2Ment[LoopNumA]=MeasureMeans(AFM2,MeasureStep,XSize,YSize,2);
    AFM4Ment[LoopNumA]=MeasureMeans(AFM4,MeasureStep,XSize,YSize,4);
    AFM6Ment[LoopNumA]=MeasureMeans(AFM6,MeasureStep,XSize,YSize,6);
    AX1Ment[LoopNumA]=Beta*MeasureMeans(AX1,MeasureStep,XSize,YSize,1);
    WindingXMent[LoopNumA]=MeasureMeans(WiddingX,MeasureStep,XSize,YSize,0);
    WindingXMent[LoopNumA]/=(double)(pow(XSize,2)/Beta);
    WindingYMent[LoopNumA]=MeasureMeans(WiddingY,MeasureStep,XSize,YSize,0);
    WindingYMent[LoopNumA]/=(double)(pow(YSize,2)/Beta);

    if(Choice!=0)
    {
      Means/=(double)pow(((double)XSize*(double)YSize),(double)Choice);
      //printf("%f \n",(double)pow((double)XSize*(double)YSize,Choice));
    }

    Data=0.0;
    */
    return 0;
}
double MeasureMeans_Honeycomb(double &AFM,double &AFM1,double &AFM2,double &AFM4,double &AFM6\
        ,double &AX1,double &AFM1abs, double &Ususc,double &WiddingX,double &WiddingY,double &WiddingZ,double &HNOMeasure,double &TempW\
        ,long long &XSize,long long &YSize,double &Beta,long long &MeasureStep,long long &SpinNO\
        ,double &UsuscMent,double &AFM1Ment,double &AFM2Ment,double &AFM4Ment\
        ,double &AFM6Ment,double &AX1Ment,double &AFM1absMent,double &WindingXMent,double &WindingYMent,double &HNOMent,double &TempWMent)//每個測量的平均
{
    double Vol;
    Vol=(double)(SpinNO);
    UsuscMent=Ususc/(double)MeasureStep;
    //UsuscMent/=MeasureStep*Beta/SpinNO;
    AFM1Ment=AFM1/(double)MeasureStep;
    AFM1Ment/=Vol;

    AFM1absMent=AFM1abs/(double)MeasureStep;
    AFM1absMent/=Vol;

    AFM2Ment=AFM2/(double)MeasureStep;
    AFM2Ment/=(Vol*Vol);

    AFM4Ment=AFM4/(double)MeasureStep;
    AFM4Ment/=(Vol*Vol*Vol*Vol);

    AFM6Ment=AFM6/(double)MeasureStep;
    AFM6Ment/=(Vol*Vol*Vol*Vol*Vol*Vol);

    AX1Ment=(double)((double)AX1/(double)MeasureStep);
    AX1Ment/=(double)(Vol);
    AX1Ment*=(double)Beta;

    WindingXMent=(double)((double)WiddingX/(double)MeasureStep);
    WindingXMent/=(double)(XSize*XSize);

    WindingYMent=(double)((double)WiddingY/(double)MeasureStep);
    WindingYMent/=(double)(YSize*YSize);

    HNOMent=HNOMeasure/(double)MeasureStep;

    TempWMent=TempW/(double)MeasureStep;

    Ususc=0.0;
    AFM1=0.0;
    AFM2=0.0;
    AFM4=0.0;
    AFM6=0.0;
    AX1=0.0;
    AFM1abs=0.0;
    WiddingX=0.0;
    WiddingY=0.0;
    TempW=0.0;
    HNOMeasure=0.0;

    //double Means;
    //Means=Data/(double)MeasureStep;
    //Means/=(double)XSize*YSize;
    /*
    UsuscMent[LoopNumA]=(double)(MeasureMeans(Measure,MeasureStep,XSize,YSize,0));
    UsuscMent[LoopNumA]=(double)(MeasureMeans(Measure,MeasureStep,XSize,YSize,0)*Beta/SpinNO);
    AFM1Ment[LoopNumA]=MeasureMeans(AFM1,MeasureStep,XSize,YSize,1);
    AFM2Ment[LoopNumA]=MeasureMeans(AFM2,MeasureStep,XSize,YSize,2);
    AFM4Ment[LoopNumA]=MeasureMeans(AFM4,MeasureStep,XSize,YSize,4);
    AFM6Ment[LoopNumA]=MeasureMeans(AFM6,MeasureStep,XSize,YSize,6);
    AX1Ment[LoopNumA]=Beta*MeasureMeans(AX1,MeasureStep,XSize,YSize,1);
    WindingXMent[LoopNumA]=MeasureMeans(WiddingX,MeasureStep,XSize,YSize,0);
    WindingXMent[LoopNumA]/=(double)(pow(XSize,2)/Beta);
    WindingYMent[LoopNumA]=MeasureMeans(WiddingY,MeasureStep,XSize,YSize,0);
    WindingYMent[LoopNumA]/=(double)(pow(YSize,2)/Beta);

    if(Choice!=0)
    {
      Means/=(double)pow(((double)XSize*(double)YSize),(double)Choice);
      //printf("%f \n",(double)pow((double)XSize*(double)YSize,Choice));
    }

    Data=0.0;
    */
    return 0;
}


void MeansSTD(double* MeasureMent,double &Means,double &STD,double &STDD,long long MeasureT)
{
    long long LoopNumA,LoopNumB,LoopNumC,RealT;
    double Total,TotalSqrt;//,Means,STD;
    Total=0;
    TotalSqrt=0;
    LoopNumA=0;
    RealT=0;
    //RealT=len64(MeasureMent);
    while(LoopNumA<MeasureT)
    {
        if(MeasureMent[LoopNumA]==-999)
        {
            //printf("%d,%d \n",MeasureT,LoopNumA+1);
            break;
        }
        else
        {
            Total+=(double)MeasureMent[LoopNumA];
            //TotalSqrt+=(double)pow(MeasureMent[LoopNumA],2.0);
            TotalSqrt+=MeasureMent[LoopNumA]*MeasureMent[LoopNumA];
            LoopNumA+=1;
       }

    }
    /*for(LoopNumA=0;LoopNumA<RealT;LoopNumA+=1)
    {
        Total+=(double)MeasureMent[LoopNumA];
        TotalSqrt+=(double)pow(MeasureMent[LoopNumA],2.0);
    }*/
    RealT=LoopNumA;
    Means=(double)Total/(double)(RealT);
    TotalSqrt/=(double)(RealT);
    STD=(double)TotalSqrt-sqrt(Means);
    //STD=(double)TotalSqrt-(double)pow(Means,2.0);
    STD=sqrt(STD);
    //STD=(double)pow(STD,0.5);
    STDD=STD/sqrt(RealT);
    //STDD=STD/pow((double)RealT,0.5);
}
