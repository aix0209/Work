void MakeLattice(long long &Type,long long* SpinSystem,double* BondNOsystem,long long* Hoperator\
          ,long long &Size,long long &SpinNO,long long &BondNO,long long &HoperatorNO\
          ,double &J,double &StrongJ,double &Q,double &StrongQ,double &Probability,long long* BondNORecord,long long &XSize,long long &YSize)
{
    long long LoopNumA,LoopNumB,LoopNumC,BondNOtemp,BondNOIndex;
    double RdSpin,Multiple;
    long long *SpinSave,Bond1,Bond2,Bond3;

    FILE *File=NULL;
    /*
     *0.Normal
     *1.Herring
     *2.Plaquette
     *3.Disorder Herring
     *10.JQ2 model Normal
     *20.JQ3 model 平行
     *21.JQ3 model 斜向
     *22.JQ3-Spin1 model 平行
     *30.honeycomb clean
     *31.JQ3-honeycomb Spin1/2
    */
   //兩格一組，BondNO第一格編號、第二格紀錄Bond強度J
    //Probability=0.5;//for 2. Plaquette
    Multiple=0.5;//for 2. Plaquette 1+Multiple and 1-Multiple

    /*
    依照model 設定及記錄不同Bond對應的Spin編號


    */
    if(Type<10)
    {
        SpinSave=(long long *)malloc((2+1)*sizeof(long long*));
        memset(SpinSave,-1,2*sizeof(long long*));
        for(LoopNumA=0;LoopNumA < BondNO;LoopNumA+=1)
        {
           Bond2Spin2D(LoopNumA,Size,SpinNO,SpinSave[0],SpinSave[1]);
           for(LoopNumB=0;LoopNumB < 2;LoopNumB+=1)
           {
                BondNORecord[LoopNumA*2+LoopNumB]= SpinSave[LoopNumB];
           }

        }
        for(LoopNumA=0;LoopNumA < HoperatorNO*3;LoopNumA=LoopNumA+3)
        {
           for(LoopNumB=0;LoopNumB < 3 ; LoopNumB+=1 )
           {
                Hoperator[LoopNumA+LoopNumB]=-1 ;
           }

        }


    }
    else if(Type<20)
    {
        SpinSave=(long long *)malloc((4+1)*sizeof(long long*));
        memset(SpinSave,-1,4*sizeof(long long*));
        for(LoopNumA=0;LoopNumA < SpinNO*2 ;LoopNumA+=1)
        {

           Bond2Spin2D(LoopNumA,Size,SpinNO,SpinSave[0],SpinSave[1]);
           for(LoopNumB=0;LoopNumB < 2;LoopNumB+=1)
           {
                BondNORecord[LoopNumA*4+LoopNumB]= SpinSave[LoopNumB];
           }

        }
        for(LoopNumA=SpinNO*2;LoopNumA < BondNO ;LoopNumA+=1)
        {
           BondNOtemp = LoopNumA-2*SpinNO;
           Q2Bond2Bond2D(BondNOtemp ,Size,SpinNO,Bond1,Bond2);
           Bond2Spin2D(Bond1,Size,SpinNO,SpinSave[0],SpinSave[1]);
           Bond2Spin2D(Bond2,Size,SpinNO,SpinSave[2],SpinSave[3]);
           for(LoopNumB=0;LoopNumB < 4;LoopNumB+=1)
           {
                BondNORecord[LoopNumA*4+LoopNumB]= SpinSave[LoopNumB];
           }

        }

        for(LoopNumA=0;LoopNumA < HoperatorNO*5;LoopNumA=LoopNumA+5)
        {
           for(LoopNumB=0;LoopNumB < 5 ; LoopNumB+=1 )
           {
                Hoperator[LoopNumA+LoopNumB]=-1;
           }

        }


    }
    else if(Type<30)
    {
        SpinSave=(long long *)malloc((6+1)*sizeof(long long*));
        memset(SpinSave,-1,(6+1)*sizeof(long long*));
        switch(Type)
        {
            case 20:

                for(LoopNumA=0;LoopNumA < SpinNO*2 ;LoopNumA+=1)
                {

                   Bond2Spin2D(LoopNumA,Size,SpinNO,SpinSave[0],SpinSave[1]);
                   for(LoopNumB=0;LoopNumB < 2;LoopNumB+=1)
                   {
                        BondNORecord[LoopNumA*6+LoopNumB]= SpinSave[LoopNumB];
                   }
                }
                for(LoopNumA=SpinNO*2;LoopNumA < BondNO ;LoopNumA+=1)
                {
                   BondNOtemp = LoopNumA-2*SpinNO;
                   Q3Bond2Bond2D(BondNOtemp,Size,SpinNO,Bond1,Bond2,Bond3);
                   Bond2Spin2D(Bond1,Size,SpinNO,SpinSave[0],SpinSave[1]);
                   Bond2Spin2D(Bond2,Size,SpinNO,SpinSave[2],SpinSave[3]);
                   Bond2Spin2D(Bond3,Size,SpinNO,SpinSave[4],SpinSave[5]);
                   for(LoopNumB=0;LoopNumB < 6;LoopNumB+=1)
                   {
                        BondNORecord[LoopNumA*6+LoopNumB]= SpinSave[LoopNumB];
                   }


                }
                break;
            case 21:
                for(LoopNumA=0;LoopNumA < SpinNO*2 ;LoopNumA+=1)
                {

                   Bond2Spin2D(LoopNumA,Size,SpinNO,SpinSave[0],SpinSave[1]);
                   for(LoopNumB=0;LoopNumB < 2;LoopNumB+=1)
                   {
                        BondNORecord[LoopNumA*6+LoopNumB]= SpinSave[LoopNumB];
                   }
                }
                for(LoopNumA=SpinNO*2;LoopNumA < BondNO ;LoopNumA+=1)
                {
                   BondNOtemp = LoopNumA-2*SpinNO;
                   Q3Bond2Bond2D_1(BondNOtemp,Size,SpinNO,Bond1,Bond2,Bond3);
                   Bond2Spin2D(Bond1,Size,SpinNO,SpinSave[0],SpinSave[1]);
                   Bond2Spin2D(Bond2,Size,SpinNO,SpinSave[2],SpinSave[3]);
                   Bond2Spin2D(Bond3,Size,SpinNO,SpinSave[4],SpinSave[5]);
                   for(LoopNumB=0;LoopNumB < 6;LoopNumB+=1)
                   {
                        BondNORecord[LoopNumA*6+LoopNumB]= SpinSave[LoopNumB];
                   }


                }
                break;
            case 22:
                SpinSave=(long long *)malloc((6+1)*sizeof(long long*));
                memset(SpinSave,-1,(6+1)*sizeof(long long*));
                for(LoopNumA=0;LoopNumA < SpinNO ;LoopNumA+=1)
                {

                   Bond2Spin2D(LoopNumA,Size,SpinNO,SpinSave[0],SpinSave[1]);
                   if (LoopNumA%SpinNO==SpinNO-2 or LoopNumA%SpinNO==SpinNO-1)
                   {
                        BondNORecord[LoopNumA*7]= 0;

                   }

                   for(LoopNumB=0;LoopNumB < 2;LoopNumB+=1)
                   {
                        BondNORecord[LoopNumA*7+LoopNumB+1]= SpinSave[LoopNumB];
                   }
                }
                for(LoopNumA=SpinNO;LoopNumA < SpinNO*2 ;LoopNumA+=1)
                {

                   Bond2Spin2D(LoopNumA,Size,SpinNO,SpinSave[0],SpinSave[1]);
                   if (LoopNumA%SpinNO==SpinNO-1-Size or LoopNumA%SpinNO==SpinNO-1)
                   {
                        BondNORecord[LoopNumA*7]= 0;

                   }

                   for(LoopNumB=0;LoopNumB < 2;LoopNumB+=1)
                   {
                        BondNORecord[LoopNumA*7+LoopNumB+1]= SpinSave[LoopNumB];
                   }
                }
                for(LoopNumA=SpinNO*2;LoopNumA < BondNO ;LoopNumA+=1)
                {
                   BondNOtemp = LoopNumA-2*SpinNO;
                   Q3Bond2Bond2D(BondNOtemp,Size,SpinNO,Bond1,Bond2,Bond3);
                   Bond2Spin2D(Bond1,Size,SpinNO,SpinSave[0],SpinSave[1]);
                   Bond2Spin2D(Bond2,Size,SpinNO,SpinSave[2],SpinSave[3]);
                   Bond2Spin2D(Bond3,Size,SpinNO,SpinSave[4],SpinSave[5]);
                   if(Bond1%Size>=Size-2 and Bond1%SpinNO>=SpinNO-Size*3 and Bond1<SpinNO)
                   {
                        BondNORecord[LoopNumA*7] = Size-(long long)(Bond1/Size);
                   }
                   else if(Bond1%Size>=Size-3 and Bond1%SpinNO>=SpinNO-Size*2 and Bond1>=SpinNO)
                   {
                        BondNORecord[LoopNumA*7] = Size-(long long)(Bond1%Size);

                   }
                   for(LoopNumB=0;LoopNumB < 6;LoopNumB+=1)
                   {
                        BondNORecord[LoopNumA*7+LoopNumB+1]= SpinSave[LoopNumB];
                   }


                }
                break;

        }

        for(LoopNumA=0;LoopNumA < HoperatorNO*7;LoopNumA=LoopNumA+7)
        {
           for(LoopNumB=0;LoopNumB < 7 ; LoopNumB+=1 )
           {
                Hoperator[LoopNumA+LoopNumB]=-1 ;
           }

        }

    }




    switch(Type)
    {
        case 0://
            for(LoopNumA=0;LoopNumA < SpinNO*3;LoopNumA=LoopNumA+3)
            {
               SpinSystem[LoopNumA]=(long long)pow(-1.0,(long long)(LoopNumA/3)%Size+(long long)(LoopNumA/3)/Size);
               SpinSystem[LoopNumA+2]=0;
               RdSpin=genrand64_real2();
                if(RdSpin>0.5)
                {
                   SpinSystem[LoopNumA+1]=1;
                }
                else
                {
                   SpinSystem[LoopNumA+1]=-1;
                }

            }
            for(LoopNumA=0;LoopNumA < BondNO*2;LoopNumA=LoopNumA+2)
            {
               BondNOsystem[LoopNumA]=(double)LoopNumA/2;;
               BondNOsystem[LoopNumA+1]=J;
            }
            break;


        case 1:
            for(LoopNumA=0;LoopNumA < SpinNO*3;LoopNumA=LoopNumA+3)
            {

               //SpinSystem[LoopNumA]=LoopNumA/3;
               SpinSystem[LoopNumA]=(long long)pow(-1.0,(long long)(LoopNumA/3)%Size+(long long)(LoopNumA/3)/Size);
               //printf("%d ,%f \n",LoopNumA,SpinSystem[LoopNumA]);
               SpinSystem[LoopNumA+2]=0;
               RdSpin=genrand64_real2();
                if(RdSpin<0.5)
                {
                   SpinSystem[LoopNumA+1]=1;
                }
                else
                {
                   SpinSystem[LoopNumA+1]=-1;
                }

            }

            //Bond初始化

            for(LoopNumA=0;LoopNumA < BondNO*2;LoopNumA=LoopNumA+2)
            {
               BondNOsystem[LoopNumA]=(double)LoopNumA/2;
               //BondNOsystem[LoopNumA+1]=J;
                if(BondNOsystem[LoopNumA]<BondNO/3)
               {
                    if ((long long)BondNOsystem[LoopNumA]%4==(long long)((long long)BondNOsystem[LoopNumA]/(long long)Size)%4)
                   {
                        BondNOsystem[LoopNumA+1]=StrongJ;
                   }
                   else
                   {
                        BondNOsystem[LoopNumA+1]=J;
                   }
               }
               else if(BondNOsystem[LoopNumA]<2*BondNO/3)
               {
                    if ((long long)(BondNOsystem[LoopNumA]-3)%4==(long long)((long long)BondNOsystem[LoopNumA]/(long long)Size)%4)
                   {
                        BondNOsystem[LoopNumA+1]=StrongJ;
                   }
                   else
                   {
                        BondNOsystem[LoopNumA+1]=J;
                   }
               }
               else
               {
                   BondNOsystem[LoopNumA]=(double)LoopNumA/2;
                   BondNOsystem[LoopNumA+1]=(double)1.0;
               }
            }
            break;
   //2.Plaquette
        case 2:

            for(LoopNumA=0;LoopNumA < SpinNO*3;LoopNumA=LoopNumA+3)
            {
               SpinSystem[LoopNumA]=(long long)pow(-1.0,(long long)(LoopNumA/3)%Size+(long long)(LoopNumA/3)/Size);
               SpinSystem[LoopNumA+2]=0;
               RdSpin=genrand64_real2();
                if(RdSpin>0.5)
                {
                   SpinSystem[LoopNumA+1]=1;
                }
                else
                {
                   SpinSystem[LoopNumA+1]=-1;
                }

            }
            //Bond初始化

            for(LoopNumA=0;LoopNumA < BondNO*2;LoopNumA=LoopNumA+2)
            {
               BondNOsystem[LoopNumA]=(double)LoopNumA/2;
               //BondNOsystem[LoopNumA+1]=J;
                if(BondNOsystem[LoopNumA]<BondNO/2)
               {
                    if ((long long)BondNOsystem[LoopNumA]%2==0)
                   {
                        RdSpin=genrand64_real2();
                        if(RdSpin<=Probability)
                        {
                           BondNOsystem[LoopNumA+1]=(double)StrongJ*(1+Multiple);
                        }
                        else
                        {
                           BondNOsystem[LoopNumA+1]=(double)StrongJ*(1-Multiple);
                        }
                   }
                   else
                   {
                        BondNOsystem[LoopNumA+1]=J;
                   }
               }
               else
               {
                    if ((long long)BondNOsystem[LoopNumA]%2==0 and ((long long)BondNOsystem[LoopNumA]/Size)%2==0 )
                   {
                        RdSpin=genrand64_real2();
                        if(RdSpin<=Probability)
                        {
                           BondNOsystem[LoopNumA+1]=(double)StrongJ*(1+Multiple);
                        }
                        else
                        {
                           BondNOsystem[LoopNumA+1]=(double)StrongJ*(1-Multiple);
                        }
                   }
                   else if((long long)BondNOsystem[LoopNumA]%2==1 and ((long long)BondNOsystem[LoopNumA]/Size)%2==0)
                   {
                        RdSpin=genrand64_real2();
                        if(RdSpin<=Probability)
                        {
                           BondNOsystem[LoopNumA+1]=(double)StrongJ*(1+Multiple);
                        }
                        else
                        {
                           BondNOsystem[LoopNumA+1]=(double)StrongJ*(1-Multiple);
                        }

                   }
                   else
                   {
                        BondNOsystem[LoopNumA+1]=J;
                   }
               }
            }
            break;
        case 3:
             for(LoopNumA=0;LoopNumA < SpinNO*3;LoopNumA=LoopNumA+3)
            {

               SpinSystem[LoopNumA]=(long long)pow(-1.0,(long long)(LoopNumA/3)%Size+(long long)(LoopNumA/3)/Size);
               SpinSystem[LoopNumA+2]=0;
               RdSpin=genrand64_real2();
                if(RdSpin<=0.5)
                {
                   SpinSystem[LoopNumA+1]=1;
                }
                else
                {
                   SpinSystem[LoopNumA+1]=-1;
                }

            }
            //Bond初始化

            for(LoopNumA=0;LoopNumA < BondNO*2;LoopNumA=LoopNumA+2)
            {
               BondNOsystem[LoopNumA]=(double)LoopNumA/2;

                if(BondNOsystem[LoopNumA]<BondNO/2)
               {
                    if ((long long)BondNOsystem[LoopNumA]%4==(long long)((long long)BondNOsystem[LoopNumA]/(long long)Size)%4)
                   {
                       RdSpin=genrand64_real2();
                        if(RdSpin<=Probability)
                        {
                           BondNOsystem[LoopNumA+1]=(double)StrongJ*(1+Multiple);
                        }
                        else
                        {
                           BondNOsystem[LoopNumA+1]=(double)StrongJ*(1-Multiple);
                        }
                   }
                   else
                   {
                        BondNOsystem[LoopNumA+1]=J;
                   }
               }
               else
               {
                    if ((long long)(BondNOsystem[LoopNumA]-3)%4==(long long)((long long)BondNOsystem[LoopNumA]/(long long)Size)%4)
                   {
                        RdSpin=genrand64_real2();
                        if(RdSpin<=Probability)
                        {
                           BondNOsystem[LoopNumA+1]=(double)StrongJ*(1+Multiple);
                        }
                        else
                        {
                           BondNOsystem[LoopNumA+1]=(double)StrongJ*(1-Multiple);
                        }
                    }
                   else
                   {
                        BondNOsystem[LoopNumA+1]=J;
                   }
               }
            }
            break;


        case 10:
            for(LoopNumA=0;LoopNumA < SpinNO*3;LoopNumA=LoopNumA+3)
            {
               SpinSystem[LoopNumA]=(long long)pow(-1.0,(long long)(LoopNumA/3)%Size+(long long)(LoopNumA/3)/Size);
               SpinSystem[LoopNumA+2]=0;
               RdSpin=genrand64_real2();
                if(RdSpin>0.5)
                {
                   SpinSystem[LoopNumA+1]=1;
                }
                else
                {
                   SpinSystem[LoopNumA+1]=-1;
                }

            }
           for(LoopNumA=0;LoopNumA < BondNO;LoopNumA=LoopNumA+2)
           {
               BondNOsystem[LoopNumA]=(double)(LoopNumA/2);
               BondNOsystem[LoopNumA+1]=J;
           }

           for(LoopNumA=BondNO;LoopNumA <BondNO*2;LoopNumA=LoopNumA+2)
           {
               //printf("%f ,%f \n",(double)(LoopNumA/2),Q);
               BondNOsystem[LoopNumA]=(double)(LoopNumA/2);
               BondNOsystem[LoopNumA+1]=Q;
           }
           break;
        case 20:
            for(LoopNumA=0;LoopNumA < SpinNO*3;LoopNumA=LoopNumA+3)
            {
               SpinSystem[LoopNumA]=(long long)pow(-1.0,(long long)(LoopNumA/3)%Size+(long long)(LoopNumA/3)/Size);
               SpinSystem[LoopNumA+2]=0;
               RdSpin=genrand64_real2();
                if(RdSpin>0.5)
                {
                   SpinSystem[LoopNumA+1]=1;
                }
                else
                {
                   SpinSystem[LoopNumA+1]=-1;
                }

            }
           for(LoopNumA=0;LoopNumA < BondNO;LoopNumA=LoopNumA+2)
           {
               BondNOsystem[LoopNumA]=(double)(LoopNumA/2);
               BondNOsystem[LoopNumA+1]=J;
           }

           for(LoopNumA=BondNO;LoopNumA <BondNO*2;LoopNumA=LoopNumA+2)
           {
               //printf("%f ,%f \n",(double)(LoopNumA/2),Q);
               BondNOsystem[LoopNumA]=(double)(LoopNumA/2);
               BondNOsystem[LoopNumA+1]=Q;
           }
           break;
        case 21:
            for(LoopNumA=0;LoopNumA < SpinNO*3;LoopNumA=LoopNumA+3)
            {
               SpinSystem[LoopNumA]=(long long)pow(-1.0,(long long)(LoopNumA/3)%Size+(long long)(LoopNumA/3)/Size);
               SpinSystem[LoopNumA+2]=0;
               RdSpin=genrand64_real2();
                if(RdSpin>0.5)
                {
                   SpinSystem[LoopNumA+1]=1;
                }
                else
                {
                   SpinSystem[LoopNumA+1]=-1;
                }

            }
            break;
           for(LoopNumA=0;LoopNumA < SpinNO*2*2;LoopNumA=LoopNumA+2)
           {
               BondNOsystem[LoopNumA]=(double)(LoopNumA/2);
               BondNOsystem[LoopNumA+1]=J;
           }

           for(LoopNumA=SpinNO*2*2;LoopNumA <BondNO*2;LoopNumA=LoopNumA+2)
           {
               //printf("%f ,%f \n",(double)(LoopNumA/2),Q);
               BondNOsystem[LoopNumA]=(double)(LoopNumA/2);
               BondNOsystem[LoopNumA+1]=Q;
           }
            break;
        case 22:
            for(LoopNumA=0;LoopNumA < SpinNO*3;LoopNumA=LoopNumA+3)
            {
               SpinSystem[LoopNumA]=(long long)pow(-1.0,(long long)(LoopNumA/3)%Size+(long long)(LoopNumA/3)/Size);
               SpinSystem[LoopNumA+2]=0;
               //RdSpin=genrand64_real2();
                if(genrand64_real2()>0.5)
                {
                   SpinSystem[LoopNumA+1]=1;
                }
                else
                {
                   SpinSystem[LoopNumA+1]=-1;
                }

            }
           for(LoopNumA=0;LoopNumA < BondNO;LoopNumA=LoopNumA+2)
           {
               BondNOsystem[LoopNumA]=(double)(LoopNumA/2);
               BondNOsystem[LoopNumA+1]=J;
           }

           for(LoopNumA=BondNO;LoopNumA <BondNO*2;LoopNumA=LoopNumA+2)
           {
               //printf("%f ,%f \n",(double)(LoopNumA/2),Q);
               BondNOsystem[LoopNumA]=(double)(LoopNumA/2);
               BondNOsystem[LoopNumA+1]=Q;
           }
           break;
        case 30:
            for(LoopNumA=0;LoopNumA < SpinNO*3;LoopNumA=LoopNumA+3)
            {
               SpinSystem[LoopNumA]=(long long)pow(-1.0,(long long)(LoopNumA/3)%Size+(long long)(LoopNumA/3)/Size);
               SpinSystem[LoopNumA+2]=0;
               //RdSpin=genrand64_real2();
                if(genrand64_real2()>0.5)
                {
                   SpinSystem[LoopNumA+1]=1;
                }
                else
                {
                   SpinSystem[LoopNumA+1]=-1;
                }

            }
           for(LoopNumA=0;LoopNumA < BondNO;LoopNumA=LoopNumA+2)
           {
               BondNOsystem[LoopNumA]=(double)(LoopNumA/2);
               BondNOsystem[LoopNumA+1]=J;
           }

           for(LoopNumA=BondNO;LoopNumA <BondNO*2;LoopNumA=LoopNumA+2)
           {
               //printf("%f ,%f \n",(double)(LoopNumA/2),Q);
               BondNOsystem[LoopNumA]=(double)(LoopNumA/2);
               BondNOsystem[LoopNumA+1]=Q;
           }
           break;
        case 31:
            for(LoopNumA=0;LoopNumA < SpinNO*3;LoopNumA=LoopNumA+3)
            {
               SpinSystem[LoopNumA]=(long long)pow(-1.0,(long long)(LoopNumA/3)%Size+(long long)(LoopNumA/3)/Size);
               SpinSystem[LoopNumA+2]=0;
               //RdSpin=genrand64_real2();
                if(genrand64_real2()>0.5)
                {
                   SpinSystem[LoopNumA+1]=1;
                }
                else
                {
                   SpinSystem[LoopNumA+1]=-1;
                }

            }
           for(LoopNumA=0;LoopNumA < SpinNO+(long long)(XSize/2)*YSize;LoopNumA=LoopNumA+1)
           {
               BondNOsystem[LoopNumA*2]=(double)(LoopNumA);
               BondNOsystem[LoopNumA*2+1]=J;
           }

           for(LoopNumA=SpinNO+(long long)(XSize/2)*YSize;LoopNumA <BondNO;LoopNumA=LoopNumA)
           {
               //printf("%f ,%f \n",(double)(LoopNumA/2),Q);
               BondNOsystem[LoopNumA*2]=(double)(LoopNumA);
               BondNOsystem[LoopNumA*2+1]=Q;
           }
           break;
    }


    File=fopen("ModelPlot-1.txt", "w");
    for(LoopNumA=0;LoopNumA < BondNO*2;LoopNumA=LoopNumA+2)
    {
        fprintf(File,"%lf  %2.16lf  \n",BondNOsystem[LoopNumA],BondNOsystem[LoopNumA+1]);
    }
    fclose(File);
    free(SpinSave);
}



void MakeLattice_Honeycomb_Clean(long long &Type,long long* SpinSystem,double* BondNOsystem,long long* Hoperator\
          ,long long &Size,long long &SpinNO,long long &BondNO,long long &HoperatorNO\
          ,double &J,double &StrongJ,double &Q,double &StrongQ,double &Probability,long long* BondNORecord,long long &XSize,long long &YSize)
{
    long long LoopNumA,LoopNumB,LoopNumC,BondNOtemp,BondNOIndex;
    double RdSpin,Multiple;
    long long *SpinSave,Bond1,Bond2,Bond3;

    SpinSave=(long long *)malloc((2+1)*sizeof(long long*));
    memset(SpinSave,-1,2*sizeof(long long*));
    BondNOIndex=0;
    for(LoopNumA=0;LoopNumA < SpinNO-1;LoopNumA+=1)
    {
       Bond2Spin2D(LoopNumA,Size,SpinNO,SpinSave[0],SpinSave[1]);
       for(LoopNumB=0;LoopNumB < 2;LoopNumB+=1)
       {
            BondNORecord[LoopNumA*2+LoopNumB]= SpinSave[LoopNumB];
       }
       BondNOIndex+=1;

    }
    BondNOIndex = SpinNO-1 ;
    for(LoopNumA=SpinNO;LoopNumA <SpinNO*2-1;LoopNumA+=1)
    {
        if(/**/ ((long long )(LoopNumA/XSize))%2 == 0 and LoopNumA%2 == 0 )
        {
           Bond2Spin2D(LoopNumA,Size,SpinNO,SpinSave[0],SpinSave[1]);
           for(LoopNumB=0;LoopNumB < 2;LoopNumB+=1)
           {
                BondNORecord[BondNOIndex*2+LoopNumB]= SpinSave[LoopNumB];
           }
           BondNOIndex+=1;

        }
        else if(/**/ ((long long )(LoopNumA/XSize))%2 == 1 and LoopNumA%2 == 1 )
        {
           Bond2Spin2D(LoopNumA,Size,SpinNO,SpinSave[0],SpinSave[1]);
           for(LoopNumB=0;LoopNumB < 2;LoopNumB+=1)
           {
                BondNORecord[BondNOIndex*2+LoopNumB]= SpinSave[LoopNumB];
           }
           BondNOIndex+=1;

        }
        else
        {
            continue;
        }

    }
    if(BondNOIndex!=BondNO)
    {
        printf("Error!!!! BondNO=%d  BondNOIndex=%d  \n",BondNO,BondNOIndex);

    }
    for(LoopNumA=0;LoopNumA < HoperatorNO*3;LoopNumA=LoopNumA+3)
    {
       for(LoopNumB=0;LoopNumB < 3 ; LoopNumB+=1 )
       {
            Hoperator[LoopNumA+LoopNumB]=-1 ;
       }

    }
    for(LoopNumA=0;LoopNumA < SpinNO*3;LoopNumA=LoopNumA+3)
    {
       SpinSystem[LoopNumA]=(long long)pow(-1.0,(long long)(LoopNumA/3)%XSize+(long long)(LoopNumA/3)/XSize);
       SpinSystem[LoopNumA+2]=0;
       //RdSpin=genrand64_real2();
        if(genrand64_real2()>0.5)
        {
           SpinSystem[LoopNumA+1]=1;
        }
        else
        {
           SpinSystem[LoopNumA+1]=-1;
        }

    }
   for(LoopNumA=0;LoopNumA < SpinNO;LoopNumA+=1)
   {
       BondNOsystem[LoopNumA*2]=(double)(LoopNumA);
       BondNOsystem[LoopNumA*2+1]=J;
   }

   for(LoopNumA=SpinNO;LoopNumA <BondNO;LoopNumA+=1)
   {
       //printf("%f ,%f \n",(double)(LoopNumA/2),Q);
       BondNOsystem[LoopNumA*2]=(double)(LoopNumA);
       BondNOsystem[LoopNumA*2+1]=Q;
   }


}


void MakeLattice_Honeycomb_JQ3_Clean(long long &Type,long long* SpinSystem,double* BondNOsystem,long long* Hoperator\
          ,long long &Size,long long &SpinNO,long long &BondNO,long long &HoperatorNO\
          ,double &J,double &StrongJ,double &Q,double &StrongQ,double &Probability,long long* BondNORecord,long long &XSize,long long &YSize)
{
    long long LoopNumA,LoopNumB,LoopNumC,BondNOtemp,BondNOIndex;
    double RdSpin,Multiple;
    long long *SpinSave,Bond1,Bond2,Bond3;
    FILE *File=NULL;

    SpinSave=(long long *)malloc((6+1)*sizeof(long long*));
    memset(SpinSave,-1,6*sizeof(long long*));
    //橫JBond
    BondNOIndex=0;
    for(LoopNumA=0;LoopNumA < SpinNO ; LoopNumA+=1)
    {
       Bond2Spin2D_HoneyComb(LoopNumA,XSize,YSize,SpinNO,SpinSave[0],SpinSave[1]);
       for(LoopNumB=0;LoopNumB < 2;LoopNumB+=1)
       {
            BondNORecord[LoopNumA*6+LoopNumB]= SpinSave[LoopNumB];
       }
       //BondNOIndex+=1;

    }
    //直JBond
    for(LoopNumA = SpinNO ;LoopNumA < (long long)(SpinNO*1.5);LoopNumA+=1)
    {
       BondNOtemp = LoopNumA-SpinNO;
       BondNOtemp = BondNOtemp*2+(long long)(BondNOtemp*2/XSize)%2+SpinNO;
       Bond2Spin2D_HoneyComb(BondNOtemp,XSize,YSize,SpinNO,SpinSave[0],SpinSave[1]);
       for(LoopNumB=0;LoopNumB < 2;LoopNumB+=1)
       {
            BondNORecord[LoopNumA*6+LoopNumB]= SpinSave[LoopNumB];
       }
       //BondNOIndex+=1;
    }


    //向右QBond
    //printf("MakeLattice QBond to Right \n");
    for(LoopNumA = (long long)(SpinNO*1.5) ;LoopNumA < SpinNO*2;LoopNumA+=1)
    {
       BondNOtemp = (long long)(LoopNumA-SpinNO*1.5);
       BondNOtemp = BondNOtemp*2+(long long)(BondNOtemp*2/XSize)%2;
       Q3Bond2Bond2D_HoneyComb(BondNOtemp,XSize,YSize,SpinNO,Bond1,Bond2,Bond3);
       Bond2Spin2D_HoneyComb(Bond1,XSize,YSize,SpinNO,SpinSave[0],SpinSave[1]);
       Bond2Spin2D_HoneyComb(Bond2,XSize,YSize,SpinNO,SpinSave[2],SpinSave[3]);
       Bond2Spin2D_HoneyComb(Bond3,XSize,YSize,SpinNO,SpinSave[4],SpinSave[5]);
       for(LoopNumB=0;LoopNumB < 6;LoopNumB+=1)
       {
            BondNORecord[LoopNumA*6+LoopNumB]= SpinSave[LoopNumB];
       }
       //BondNOIndex+=1;
    }
    for(LoopNumA = SpinNO*2 ;LoopNumA < BondNO;LoopNumA+=1)
    {
       BondNOtemp = (long long)LoopNumA-SpinNO*2;
       BondNOtemp = BondNOtemp*2+(long long)(BondNOtemp*2/XSize)%2+SpinNO;
       Q3Bond2Bond2D_HoneyComb(BondNOtemp,XSize,YSize,SpinNO,Bond1,Bond2,Bond3);
       Bond2Spin2D_HoneyComb(Bond1,XSize,YSize,SpinNO,SpinSave[0],SpinSave[1]);
       Bond2Spin2D_HoneyComb(Bond2,XSize,YSize,SpinNO,SpinSave[2],SpinSave[3]);
       Bond2Spin2D_HoneyComb(Bond3,XSize,YSize,SpinNO,SpinSave[4],SpinSave[5]);
       for(LoopNumB=0;LoopNumB < 6;LoopNumB+=1)
       {
            BondNORecord[LoopNumA*6+LoopNumB]= SpinSave[LoopNumB];
       }
       //BondNOIndex+=1;
    }
    /*
    if(BondNOIndex!=BondNO)
    {
        printf("Error!!!! BondNO=%d  BondNOIndex=%d  \n",BondNO,BondNOIndex);
        //exit();
        system("pause");
    }
    */
    /*
    for(LoopNumA=0;LoopNumA < BondNO;LoopNumA=LoopNumA+1)
    {
        printf(" %4d  ",LoopNumA);
        for (LoopNumB=0;LoopNumB<6;LoopNumB+=1)
        {
            printf(" %4d  ",BondNORecord[LoopNumA*6+LoopNumB]);
        }
        printf("\n");

    }
    system("pause");
    */
    for(LoopNumA=0;LoopNumA < HoperatorNO*7;LoopNumA+=7)
    {
       for(LoopNumB=0;LoopNumB < 7 ; LoopNumB+=1 )
       {
            Hoperator[LoopNumA+LoopNumB]=-1 ;
       }

    }


    for(LoopNumA=0;LoopNumA < SpinNO;LoopNumA+=1)
    {
       SpinSystem[LoopNumA*3]=(long long )pow(-1.0,(long long)(LoopNumA)%XSize+(long long)(LoopNumA/XSize));
       SpinSystem[LoopNumA*3+2]=0;
       //RdSpin=genrand64_real2();
        if(genrand64_real2()>0.5)
        {
           SpinSystem[LoopNumA*3+1]=1;
        }
        else
        {
           SpinSystem[LoopNumA*3+1]=-1;
        }

    }
    for(LoopNumA=0;LoopNumA < (long long)SpinNO*1.5;LoopNumA+=1)
    {
       BondNOsystem[LoopNumA*2]=(double)(LoopNumA);
       BondNOsystem[LoopNumA*2+1]=J;
    }

    for(LoopNumA=(long long)(SpinNO*1.5);LoopNumA <BondNO;LoopNumA+=1)
    {
       //printf("%f ,%f \n",(double)(LoopNumA/2),Q);
       BondNOsystem[LoopNumA*2]=(double)(LoopNumA);
       BondNOsystem[LoopNumA*2+1]=Q;
    }
    File=fopen("ModelPlot-1.txt", "w");
    for(LoopNumA=0;LoopNumA < BondNO;LoopNumA=LoopNumA+1)
    {
        fprintf(File,"%lf  %2.4lf  ",BondNOsystem[LoopNumA*2],BondNOsystem[LoopNumA*2+1]);
        for (LoopNumB=0;LoopNumB<6;LoopNumB+=1)
        {
            fprintf(File," %4d  ",BondNORecord[LoopNumA*6+LoopNumB]);
        }
        fprintf(File,"\n");
    }
    fclose(File);
    free(SpinSave);

}

void MakeLattice_Honeycomb_JQ3_SpinHalf(long long &Type,long long* SpinSystem,double* BondNOsystem,long long* Hoperator\
          ,long long &Size,long long &SpinNO,long long &BondNO,long long &HoperatorNO\
          ,double &J,double &StrongJ,double &Q,double &StrongQ,double &Probability,long long* BondNORecord,long long &XSize,long long &YSize)
{
    long long LoopNumA,LoopNumB,LoopNumC,BondNOtemp,BondNOIndex,SpinNOTemp;
    double RdSpin,Multiple;
    long long *SpinSave,Bond1,Bond2,Bond3;
    FILE *File=NULL;
    SpinNOTemp=SpinNO+1;
    SpinSave=(long long *)malloc((6+1)*sizeof(long long*));
    memset(SpinSave,-1,6*sizeof(long long*));
    //橫JBond
    BondNOIndex=0;
    for(LoopNumA=0;LoopNumA < SpinNOTemp ; LoopNumA+=1)
    {
       Bond2Spin2D_HoneyComb(LoopNumA,XSize,YSize,SpinNOTemp,SpinSave[0],SpinSave[1]);
       for(LoopNumB=0;LoopNumB < 2;LoopNumB+=1)
       {
            BondNORecord[LoopNumA*6+LoopNumB]= SpinSave[LoopNumB];
       }
       //BondNOIndex+=1;

    }
    //直JBond
    for(LoopNumA = SpinNOTemp-2 ;LoopNumA < (long long)(SpinNOTemp*1.5)-3;LoopNumA+=1)
    {
       BondNOtemp = LoopNumA-SpinNOTemp+2;
       BondNOtemp = BondNOtemp*2+(long long)(BondNOtemp*2/XSize)%2+SpinNOTemp;
       Bond2Spin2D_HoneyComb(BondNOtemp,XSize,YSize,SpinNOTemp,SpinSave[0],SpinSave[1]);
       for(LoopNumB=0;LoopNumB < 2;LoopNumB+=1)
       {
            BondNORecord[LoopNumA*6+LoopNumB]= SpinSave[LoopNumB];
       }
       //BondNOIndex+=1;
    }


    //向右QBond
    //printf("MakeLattice QBond to Right \n");
    for(LoopNumA = (long long)(SpinNOTemp*1.5)-3 ;LoopNumA < SpinNOTemp*2;LoopNumA+=1)//JBond共少3Bond，故Bond號少3碼
    {
        BondNOtemp = (long long)(LoopNumA-SpinNOTemp*1.5+3);
        BondNOtemp = BondNOtemp*2+(long long)(BondNOtemp*2/XSize)%2;
        Q3Bond2Bond2D_HoneyComb(BondNOtemp,XSize,YSize,SpinNOTemp,Bond1,Bond2,Bond3);
        Bond2Spin2D_HoneyComb(Bond1,XSize,YSize,SpinNOTemp,SpinSave[0],SpinSave[1]);
        Bond2Spin2D_HoneyComb(Bond2,XSize,YSize,SpinNOTemp,SpinSave[2],SpinSave[3]);
        Bond2Spin2D_HoneyComb(Bond3,XSize,YSize,SpinNOTemp,SpinSave[4],SpinSave[5]);
       if(Bond1 < SpinNOTemp+XSize*(YSize-1)-2)// XSize*(YSize-1)-2 第一個碰到最上角的Bond
       {

           for(LoopNumB=0;LoopNumB < 6;LoopNumB+=1)
           {
                BondNORecord[LoopNumA*6+LoopNumB]= SpinSave[LoopNumB];
           }
        }
        else if( Bond1 > SpinNOTemp+XSize*(YSize-1)-2 and Bond1 < SpinNOTemp+XSize*YSize-2) // XSize*(YSize-1)-2 第二個碰到最上角的Bond
        {
           for(LoopNumB=0;LoopNumB < 6;LoopNumB+=1)
           {
                BondNORecord[(LoopNumA-1)*6+LoopNumB]= SpinSave[LoopNumB];
           }

        }
        else
        {
            continue;
        }
      //BondNOIndex+=1;
    }

    for(LoopNumA = SpinNOTemp*2-6 ;LoopNumA < SpinNOTemp*2.5 ;LoopNumA+=1)//向右QBond少兩個，加上JBond少3個，共少5個
    {
        BondNOtemp = LoopNumA-SpinNOTemp*2+6;
        BondNOtemp = BondNOtemp*2+(long long)(BondNOtemp*2/XSize)%2+SpinNOTemp;
        Q3Bond2Bond2D_HoneyComb(BondNOtemp,XSize,YSize,SpinNOTemp,Bond1,Bond2,Bond3);
        Bond2Spin2D_HoneyComb(Bond1,XSize,YSize,SpinNOTemp,SpinSave[0],SpinSave[1]);
        Bond2Spin2D_HoneyComb(Bond2,XSize,YSize,SpinNOTemp,SpinSave[2],SpinSave[3]);
        Bond2Spin2D_HoneyComb(Bond3,XSize,YSize,SpinNOTemp,SpinSave[4],SpinSave[5]);

        if(Bond1 < SpinNOTemp+XSize*(YSize-2))
        {

           for(LoopNumB=0;LoopNumB < 6;LoopNumB+=1)
           {
                BondNORecord[LoopNumA*6+LoopNumB]= SpinSave[LoopNumB];
           }

        }
        else if( Bond1 > SpinNOTemp+XSize*(YSize-2) and Bond1 < SpinNOTemp+XSize*(YSize-1)+1)
        {

           for(LoopNumB=0;LoopNumB < 6;LoopNumB+=1)
           {
                BondNORecord[(LoopNumA-1)*6+LoopNumB]= SpinSave[LoopNumB];
           }

        }
        else if( Bond1 > SpinNOTemp+XSize*(YSize-1)+1 and Bond1 < SpinNOTemp+XSize*YSize-1)
        {

           for(LoopNumB=0;LoopNumB < 6;LoopNumB+=1)
           {
                BondNORecord[(LoopNumA-2)*6+LoopNumB]= SpinSave[LoopNumB];
           }

        }
        else
        {
            continue;
        }

       //BondNOIndex+=1;
    }
    /*
    if(BondNOIndex!=BondNO)
    {
        printf("Error!!!! BondNO=%d  BondNOIndex=%d  \n",BondNO,BondNOIndex);
        //exit();
        system("pause");
    }
    */
    /*
    for(LoopNumA=0;LoopNumA < BondNO;LoopNumA=LoopNumA+1)
    {
        printf(" %4d  ",LoopNumA);
        for (LoopNumB=0;LoopNumB<6;LoopNumB+=1)
        {
            printf(" %4d  ",BondNORecord[LoopNumA*6+LoopNumB]);
        }
        printf("\n");

    }
    system("pause");
    */
    for(LoopNumA=0;LoopNumA < HoperatorNO*7;LoopNumA+=7)
    {
       for(LoopNumB=0;LoopNumB < 7 ; LoopNumB+=1 )
       {
            Hoperator[LoopNumA+LoopNumB]=-1 ;
       }

    }


    for(LoopNumA=0;LoopNumA < SpinNO;LoopNumA+=1)
    {
       SpinSystem[LoopNumA*3]=(long long)pow(-1.0,(long long)(LoopNumA)%XSize+(long long)(LoopNumA/XSize));
       //printf("%d %d \n",LoopNumA,SpinSystem[LoopNumA*3]);
       //SpinSystem[LoopNumA*3]=(double)pow(-1.0,(long long)(LoopNumA)%XSize+(long long)(LoopNumA/XSize));
       SpinSystem[LoopNumA*3+2]=0;
       //RdSpin=genrand64_real2();
        if(genrand64_real2()>0.5)
        {
           SpinSystem[LoopNumA*3+1]=1;
        }
        else
        {
           SpinSystem[LoopNumA*3+1]=-1;
        }

    }
    for(LoopNumA=0;LoopNumA < (long long)(SpinNO+1)*1.5-3;LoopNumA+=1)
    {
       BondNOsystem[LoopNumA*2]=(double)(LoopNumA);
       BondNOsystem[LoopNumA*2+1]=J;
    }

    for(LoopNumA=(long long)((SpinNO+1)*1.5-3);LoopNumA <BondNO;LoopNumA+=1)
    {
       //printf("%f ,%f \n",(double)(LoopNumA/2),Q);
       BondNOsystem[LoopNumA*2]=(double)(LoopNumA);
       BondNOsystem[LoopNumA*2+1]=Q;
    }
    File=fopen("ModelPlot-1.txt", "w");
    for(LoopNumA=0;LoopNumA < BondNO;LoopNumA=LoopNumA+1)
    {
        fprintf(File,"%lf  %2.4lf  ",BondNOsystem[LoopNumA*2],BondNOsystem[LoopNumA*2+1]);
        for (LoopNumB=0;LoopNumB<6;LoopNumB+=1)
        {
            fprintf(File," %4d  ",BondNORecord[LoopNumA*6+LoopNumB]);
        }
        fprintf(File,"\n");
    }
    fclose(File);
    free(SpinSave);
}

void MakeLattice_3DSqure_Clean(long long &Type,long long* SpinSystem,double* BondNOsystem,long long* Hoperator\
          ,long long &Size,long long &SpinNO,long long &BondNO,long long &HoperatorNO\
          ,double &J,double &StrongJ,double &Q,double &StrongQ,double &Probability,long long* BondNORecord,long long &XSize,long long &YSize,long long &ZSize)
{
    long long LoopNumA,LoopNumB,LoopNumC,BondNOtemp,BondNOIndex,SingleSpinNO;
    double RdSpin,Multiple;
    long long *SpinSave,Bond1,Bond2,Bond3;

    SpinSave=(long long *)malloc((2+1)*sizeof(long long*));
    memset(SpinSave,-1,2*sizeof(long long*));
    BondNOIndex=0;
    SingleSpinNO=XSize*YSize;
    for(LoopNumA=0;LoopNumA < BondNO-ZSize*SingleSpinNO;LoopNumA+=1)
    {
       Bond2Spin2DXY(LoopNumA,XSize,YSize,ZSize,SpinNO,SingleSpinNO,SpinSave[0],SpinSave[1]);
       for(LoopNumB=0;LoopNumB < 2;LoopNumB+=1)
       {
            BondNORecord[LoopNumA*2+LoopNumB]= SpinSave[LoopNumB];
       }
       //BondNOIndex+=1;

    }
    for(LoopNumA =BondNO-ZSize*SingleSpinNO;LoopNumA <BondNO;LoopNumA+=1)
    {

        Bond2Spin2DZ(LoopNumA,XSize,YSize,ZSize,SpinNO,SingleSpinNO,SpinSave[0],SpinSave[1]);
        for(LoopNumB=0;LoopNumB < 2;LoopNumB+=1)
        {
            BondNORecord[LoopNumA*2+LoopNumB]= SpinSave[LoopNumB];
        }
    }
    /*
    if(BondNOIndex!=BondNO)
    {
        printf("Error!!!! BondNO=%d  BondNOIndex=%d  \n",BondNO,BondNOIndex);

    }
    */
    for(LoopNumA=0;LoopNumA < HoperatorNO*3;LoopNumA=LoopNumA+3)
    {
       for(LoopNumB=0;LoopNumB < 3 ; LoopNumB+=1 )
       {
            Hoperator[LoopNumA+LoopNumB]=-1 ;
       }

    }
    for(LoopNumA=0;LoopNumA < SpinNO*3;LoopNumA=LoopNumA+3)
    {
       SpinSystem[LoopNumA]=(long long)pow(-1.0,(long long)(LoopNumA/3)%XSize+(long long)(LoopNumA/3)/XSize+(long long)(LoopNumA/SingleSpinNO));
       SpinSystem[LoopNumA+2]=0;
       //RdSpin=genrand64_real2();
        if(genrand64_real2()>0.5)
        {
           SpinSystem[LoopNumA+1]=1;
        }
        else
        {
           SpinSystem[LoopNumA+1]=-1;
        }

    }
   for(LoopNumA=0;LoopNumA < SpinNO;LoopNumA+=1)
   {
       BondNOsystem[LoopNumA*2]=(double)(LoopNumA);
       BondNOsystem[LoopNumA*2+1]=J;
   }

   for(LoopNumA=SpinNO;LoopNumA <BondNO;LoopNumA+=1)
   {
       //printf("%f ,%f \n",(double)(LoopNumA/2),Q);
       BondNOsystem[LoopNumA*2]=(double)(LoopNumA);
       BondNOsystem[LoopNumA*2+1]=Q;
   }


}

void MakeLattice_3DSquare_JQ3_ladder(long long &Type,long long* SpinSystem,double* BondNOsystem,long long* Hoperator\
          ,long long &Size,long long &SpinNO,long long &BondNO,long long &HoperatorNO\
          ,double &J,double &StrongJ,double &Q,double &StrongQ,double &Probability,long long* BondNORecord,long long &XSize,long long &YSize,long long &ZSize)
{
    long long LoopNumA,LoopNumB,LoopNumC,BondNOtemp,BondNOIndex,SingleSpinNO;
    double RdSpin,Multiple;
    long long *SpinSave,Bond1,Bond2,Bond3;
    FILE *File=NULL;
    SpinSave=(long long *)malloc((6+1)*sizeof(long long*));
    memset(SpinSave,-1,6*sizeof(long long*));
    BondNOIndex=0;
    SingleSpinNO=XSize*YSize;
    //printf("xy Bond \n");
    for(LoopNumA=0;LoopNumA < ZSize*SingleSpinNO*2;LoopNumA+=1)//xy平面Bond
    {
       //BondNOtemp = LoopNumA;
       Bond2Spin2DXY(LoopNumA,XSize,YSize,ZSize,SpinNO,SingleSpinNO,SpinSave[0],SpinSave[1]);
       for(LoopNumB=0;LoopNumB < 2;LoopNumB+=1)
       {
            BondNORecord[LoopNumA*6+LoopNumB]= SpinSave[LoopNumB];
       }
       //BondNOIndex+=1;

    }
    //printf("Z Bond \n");
    for(LoopNumA =ZSize*SingleSpinNO*2;LoopNumA < ZSize*SingleSpinNO*3;LoopNumA+=1)//Z方向Bond
    {
        //printf("Z Bond %d\n",LoopNumA);
        BondNOtemp = LoopNumA-ZSize*SingleSpinNO*2;
        Bond2Spin2DZ(BondNOtemp,XSize,YSize,ZSize,SpinNO,SingleSpinNO,SpinSave[0],SpinSave[1]);
        for(LoopNumB=0;LoopNumB < 2;LoopNumB+=1)
        {
            BondNORecord[LoopNumA*6+LoopNumB]= SpinSave[LoopNumB];
        }
    }
    //printf("xy JQ3 Bond \n");
    for(LoopNumA=ZSize*SingleSpinNO*3;LoopNumA < BondNO ;LoopNumA+=1)//xy平面JQ3 Bond
    {
       BondNOtemp = LoopNumA-ZSize*SingleSpinNO*3;
       Q3Bond2Bond2DXY_Ladder(BondNOtemp,XSize,YSize,ZSize,SpinNO,SingleSpinNO,Bond1,Bond2,Bond3);
       Bond2Spin2DXY(Bond1,XSize,YSize,ZSize,SpinNO,SingleSpinNO,SpinSave[0],SpinSave[1]);
       Bond2Spin2DXY(Bond2,XSize,YSize,ZSize,SpinNO,SingleSpinNO,SpinSave[2],SpinSave[3]);
       Bond2Spin2DXY(Bond3,XSize,YSize,ZSize,SpinNO,SingleSpinNO,SpinSave[4],SpinSave[5]);
       for(LoopNumB=0;LoopNumB < 6;LoopNumB+=1)
       {
            BondNORecord[LoopNumA*6+LoopNumB]= SpinSave[LoopNumB];
       }


    }
    /*
    if(BondNOIndex!=BondNO)
    {
        printf("Error!!!! BondNO=%d  BondNOIndex=%d  \n",BondNO,BondNOIndex);

    }
    */
   // printf("Hoperator \n");
    for(LoopNumA=0;LoopNumA < HoperatorNO*7;LoopNumA=LoopNumA+7)
    {
       for(LoopNumB=0;LoopNumB < 7 ; LoopNumB+=1 )
       {
            Hoperator[LoopNumA+LoopNumB]=-1 ;
       }

    }
    //printf("SpinSystem \n");
    for(LoopNumA=0;LoopNumA < SpinNO*3;LoopNumA=LoopNumA+3)
    {
       SpinSystem[LoopNumA]=(long long)pow(-1.0,(long long)(LoopNumA/3)%XSize+(long long)(LoopNumA/3)/XSize+(long long)(LoopNumA/3)/SingleSpinNO);
       SpinSystem[LoopNumA+2]=0;
       //printf("%d %d\n",(long long)LoopNumA/3,SpinSystem[LoopNumA]);
       //RdSpin=genrand64_real2();
        if(genrand64_real2()>0.5)
        {
           SpinSystem[LoopNumA+1]=1;
        }
        else
        {
           SpinSystem[LoopNumA+1]=-1;
        }

    }
    //printf("BondNOsystem \n");
   for(LoopNumA=0;LoopNumA < SingleSpinNO*3*ZSize;LoopNumA+=1)
   {
       BondNOsystem[LoopNumA*2]=(double)(LoopNumA);
       BondNOsystem[LoopNumA*2+1]=J;
   }

   for(LoopNumA=SingleSpinNO*3*ZSize;LoopNumA <BondNO;LoopNumA+=1)
   {
       //printf("%f ,%f \n",(double)(LoopNumA/2),Q);
       BondNOsystem[LoopNumA*2]=(double)(LoopNumA);
       BondNOsystem[LoopNumA*2+1]=Q;
   }
    File=fopen("ModelPlot-1.txt", "w");
    for(LoopNumA=0;LoopNumA < BondNO;LoopNumA=LoopNumA+1)
    {
        fprintf(File,"%lf  %2.4lf  ",BondNOsystem[LoopNumA*2],BondNOsystem[LoopNumA*2+1]);
        for (LoopNumB=0;LoopNumB<6;LoopNumB+=1)
        {
            fprintf(File," %4d  ",BondNORecord[LoopNumA*6+LoopNumB]);
        }
        fprintf(File,"\n");
    }
    fclose(File);
    free(SpinSave);
}

void MakeLattice_Honeycomb_JQ3_Spin1(long long &Type,long long* SpinSystem,double* BondNOsystem,long long* Hoperator\
          ,long long &Size,long long &SpinNO,long long &BondNO,long long &HoperatorNO\
          ,double &J,double &StrongJ,double &Q,double &StrongQ,double &Probability,long long* BondNORecord,long long &XSize,long long &YSize)
{
    long long LoopNumA,LoopNumB,LoopNumC,BondNOtemp,BondNOIndex;
    double RdSpin,Multiple;
    long long *SpinSave,Bond1,Bond2,Bond3,SpinNOTemp;

    FILE *File=NULL;
    /*
     *0.Normal
     *1.Herring
     *2.Plaquette
     *3.Disorder Herring
     *10.JQ2 model Normal
     *20.JQ3 model 平行
     *21.JQ3 model 斜向
     *22.JQ3-Spin1 model 平行
     *30.honeycomb clean
     *31.JQ3-honeycomb Spin1/2
    */
   //兩格一組，BondNO第一格編號、第二格紀錄Bond強度J
    //Probability=0.5;//for 2. Plaquette
    SpinNOTemp=SpinNO;
    SpinSave=(long long *)malloc((6+1)*sizeof(long long*));
    memset(SpinSave,-1,6*sizeof(long long*));
    for(LoopNumA=0;LoopNumA < SpinNO ;LoopNumA+=1)//橫J Bond
    {
       Bond2Spin2D_HoneyComb(LoopNumA,XSize,YSize,SpinNO,SpinSave[0],SpinSave[1]);
       if (LoopNumA%SpinNO==SpinNO-2 or LoopNumA%SpinNO==SpinNO-1)
       {
            BondNORecord[LoopNumA*7]= 0;

       }

       for(LoopNumB=0;LoopNumB < 2;LoopNumB+=1)
       {
            BondNORecord[LoopNumA*7+LoopNumB+1]= SpinSave[LoopNumB];
       }
    }
    for(LoopNumA=SpinNO;LoopNumA < SpinNO*1.5;LoopNumA+=1)//直J Bond
    {
       BondNOtemp = LoopNumA-SpinNO;
       BondNOtemp = BondNOtemp*2+(long long)(BondNOtemp*2/XSize)%2+SpinNO;
       Bond2Spin2D_HoneyComb(BondNOtemp,XSize,YSize,SpinNO,SpinSave[0],SpinSave[1]);
       if (LoopNumA == SpinNO*1.5-1)//
       {
            BondNORecord[LoopNumA*7]= 0;

       }

       for(LoopNumB=0;LoopNumB < 2;LoopNumB+=1)
       {
            BondNORecord[LoopNumA*7+LoopNumB+1]= SpinSave[LoopNumB];
       }
    }

    for(LoopNumA=(long long)(SpinNO*1.5);LoopNumA < BondNO ;LoopNumA+=1)//Q Bond
    {
        BondNOtemp = (long long)(LoopNumA-SpinNO*1.5);
        BondNOtemp = BondNOtemp*2+(long long)(BondNOtemp*2/XSize)%2;
        Q3Bond2Bond2D_HoneyComb(BondNOtemp,XSize,YSize,SpinNO,Bond1,Bond2,Bond3);
        Bond2Spin2D_HoneyComb(Bond1,XSize,YSize,SpinNO,SpinSave[0],SpinSave[1]);
        Bond2Spin2D_HoneyComb(Bond2,XSize,YSize,SpinNO,SpinSave[2],SpinSave[3]);
        Bond2Spin2D_HoneyComb(Bond3,XSize,YSize,SpinNO,SpinSave[4],SpinSave[5]);
       if(SpinSave[0] == SpinNO-1 )
       {
            BondNORecord[LoopNumA*7] = 1 ;
       }
       else if(SpinSave[2] == SpinNO-1 or SpinSave[3] == SpinNO-1)
       {
            BondNORecord[LoopNumA*7] = 2 ;

       }
       else if(SpinSave[4] == SpinNO-1 or SpinSave[5] == SpinNO-1)
       {
            BondNORecord[LoopNumA*7] = 3 ;

       }
       for(LoopNumB=0;LoopNumB < 6;LoopNumB+=1)
       {
            BondNORecord[LoopNumA*7+LoopNumB+1]= SpinSave[LoopNumB];
       }


    }
    for(LoopNumA=0;LoopNumA < HoperatorNO*7;LoopNumA=LoopNumA+7)
    {
       for(LoopNumB=0;LoopNumB < 7 ; LoopNumB+=1 )
       {
            Hoperator[LoopNumA+LoopNumB]=-1 ;
       }

    }
    for(LoopNumA=0;LoopNumA < SpinNO*3;LoopNumA=LoopNumA+3)
    {
       SpinSystem[LoopNumA]=(long long)pow(-1.0,(long long)(LoopNumA/3)%Size+(long long)(LoopNumA/3)/Size);
       SpinSystem[LoopNumA+2]=0;
       //RdSpin=genrand64_real2();
        if(genrand64_real2()>0.5)
        {
           SpinSystem[LoopNumA+1]=1;
        }
        else
        {
           SpinSystem[LoopNumA+1]=-1;
        }

    }
   for(LoopNumA=0;LoopNumA < SpinNO*1.5;LoopNumA+=1)
   {
       BondNOsystem[LoopNumA*2]=(double)(LoopNumA);
       BondNOsystem[LoopNumA*2+1]=J;
   }

   for(LoopNumA=(long long)(SpinNO*1.5);LoopNumA <BondNO;LoopNumA+=1)
   {
       //printf("%f ,%f \n",(double)(LoopNumA/2),Q);
       BondNOsystem[LoopNumA*2]=(double)(LoopNumA);
       BondNOsystem[LoopNumA*2+1]=Q;
   }
    File=fopen("ModelPlot-1.txt", "w");
    for(LoopNumA=0;LoopNumA < BondNO;LoopNumA=LoopNumA+1)
    {
        fprintf(File,"%lf  %2.4lf  ",BondNOsystem[LoopNumA*2],BondNOsystem[LoopNumA*2+1]);
        for (LoopNumB=0;LoopNumB<7;LoopNumB+=1)
        {
            fprintf(File," %4d  ",BondNORecord[LoopNumA*7+LoopNumB]);
        }
        fprintf(File,"\n");
    }
    fclose(File);
    free(SpinSave);
}

void MakeLattice_Spin1_im(long long &Type,long long* SpinSystem,double* BondNOsystem,long long* Hoperator\
          ,long long &Size,long long &SpinNO,long long &BondNO,long long &HoperatorNO\
          ,double &J,double &StrongJ,double &Q,double &StrongQ,double &Probability,long long* BondNORecord,long long &XSize,long long &YSize)
{
    long long LoopNumA,LoopNumB,LoopNumC,BondNOtemp,BondNOIndex;
    double RdSpin,Multiple;
    long long *SpinSave,Bond1,Bond2,Bond3,SpinNOTemp;

    FILE *File=NULL;
    /*
     *0.Normal
     *1.Herring
     *2.Plaquette
     *3.Disorder Herring
     *10.JQ2 model Normal
     *20.JQ3 model 平行
     *21.JQ3 model 斜向
     *22.JQ3-Spin1 model 平行
     *30.honeycomb clean
     *31.JQ3-honeycomb Spin1/2
    */
   //兩格一組，BondNO第一格編號、第二格紀錄Bond強度J
    //Probability=0.5;//for 2. Plaquette
    SpinNOTemp=SpinNO;
    SpinSave=(long long *)malloc((2+1)*sizeof(long long*));
    memset(SpinSave,-1,2*sizeof(long long*));
    for(LoopNumA=0;LoopNumA < SpinNO ;LoopNumA+=1)//橫J Bond
    {
       Bond2Spin2D_HoneyComb(LoopNumA,XSize,YSize,SpinNO,SpinSave[0],SpinSave[1]);
       if (LoopNumA%SpinNO==SpinNO-2 or LoopNumA%SpinNO==SpinNO-1)
       {
            BondNORecord[LoopNumA*2]= 0;

       }

       for(LoopNumB=0;LoopNumB < 2;LoopNumB+=1)
       {
            BondNORecord[LoopNumA*7+LoopNumB+1]= SpinSave[LoopNumB];
       }
    }
    for(LoopNumA=SpinNO;LoopNumA < SpinNO*1.5;LoopNumA+=1)//直J Bond
    {
       BondNOtemp = LoopNumA-SpinNO;
       BondNOtemp = BondNOtemp*2+(long long)(BondNOtemp*2/XSize)%2+SpinNO;
       Bond2Spin2D_HoneyComb(BondNOtemp,XSize,YSize,SpinNO,SpinSave[0],SpinSave[1]);
       if (LoopNumA == SpinNO*1.5-1)//
       {
            BondNORecord[LoopNumA*7]= 0;

       }

       for(LoopNumB=0;LoopNumB < 2;LoopNumB+=1)
       {
            BondNORecord[LoopNumA*7+LoopNumB+1]= SpinSave[LoopNumB];
       }
    }

    for(LoopNumA=(long long)(SpinNO*1.5);LoopNumA < BondNO ;LoopNumA+=1)//Q Bond
    {
        BondNOtemp = (long long)(LoopNumA-SpinNO*1.5);
        BondNOtemp = BondNOtemp*2+(long long)(BondNOtemp*2/XSize)%2;
        Q3Bond2Bond2D_HoneyComb(BondNOtemp,XSize,YSize,SpinNO,Bond1,Bond2,Bond3);
        Bond2Spin2D_HoneyComb(Bond1,XSize,YSize,SpinNO,SpinSave[0],SpinSave[1]);
        Bond2Spin2D_HoneyComb(Bond2,XSize,YSize,SpinNO,SpinSave[2],SpinSave[3]);
        Bond2Spin2D_HoneyComb(Bond3,XSize,YSize,SpinNO,SpinSave[4],SpinSave[5]);
       if(SpinSave[0] == SpinNO-1 )
       {
            BondNORecord[LoopNumA*7] = 1 ;
       }
       else if(SpinSave[2] == SpinNO-1 or SpinSave[3] == SpinNO-1)
       {
            BondNORecord[LoopNumA*7] = 2 ;

       }
       else if(SpinSave[4] == SpinNO-1 or SpinSave[5] == SpinNO-1)
       {
            BondNORecord[LoopNumA*7] = 3 ;

       }
       for(LoopNumB=0;LoopNumB < 6;LoopNumB+=1)
       {
            BondNORecord[LoopNumA*7+LoopNumB+1]= SpinSave[LoopNumB];
       }


    }
    for(LoopNumA=0;LoopNumA < HoperatorNO*7;LoopNumA=LoopNumA+7)
    {
       for(LoopNumB=0;LoopNumB < 7 ; LoopNumB+=1 )
       {
            Hoperator[LoopNumA+LoopNumB]=-1 ;
       }

    }
    for(LoopNumA=0;LoopNumA < SpinNO*3;LoopNumA=LoopNumA+3)
    {
       SpinSystem[LoopNumA]=(long long)pow(-1.0,(long long)(LoopNumA/3)%Size+(long long)(LoopNumA/3)/Size);
       SpinSystem[LoopNumA+2]=0;
       //RdSpin=genrand64_real2();
        if(genrand64_real2()>0.5)
        {
           SpinSystem[LoopNumA+1]=1;
        }
        else
        {
           SpinSystem[LoopNumA+1]=-1;
        }

    }
   for(LoopNumA=0;LoopNumA < SpinNO*1.5;LoopNumA+=1)
   {
       BondNOsystem[LoopNumA*2]=(double)(LoopNumA);
       BondNOsystem[LoopNumA*2+1]=J;
   }

   for(LoopNumA=(long long)(SpinNO*1.5);LoopNumA <BondNO;LoopNumA+=1)
   {
       //printf("%f ,%f \n",(double)(LoopNumA/2),Q);
       BondNOsystem[LoopNumA*2]=(double)(LoopNumA);
       BondNOsystem[LoopNumA*2+1]=Q;
   }
    File=fopen("ModelPlot-1.txt", "w");
    for(LoopNumA=0;LoopNumA < BondNO;LoopNumA=LoopNumA+1)
    {
        fprintf(File,"%lf  %2.4lf  ",BondNOsystem[LoopNumA*2],BondNOsystem[LoopNumA*2+1]);
        for (LoopNumB=0;LoopNumB<7;LoopNumB+=1)
        {
            fprintf(File," %4d  ",BondNORecord[LoopNumA*7+LoopNumB]);
        }
        fprintf(File,"\n");
    }
    fclose(File);
    free(SpinSave);
}


void MakeLattice_Spin1(long long &Type,long long* SpinSystem,double* BondNOsystem,long long* Hoperator\
          ,long long &Size,long long &SpinNO,long long &BondNO,long long &HoperatorNO\
          ,double &J,double &StrongJ,double &Q,double &StrongQ,double &Probability,long long* BondNORecord,long long &XSize,long long &YSize)
{
    long long LoopNumA,LoopNumB,LoopNumC,BondNOtemp,BondNOIndex,SingleSpinNO;
    double RdSpin,Multiple,Pb;
    long long *SpinSave,Bond1,Bond2,Bond3;
    FILE *File=NULL;
    SpinSave=(long long *)malloc((2+1)*sizeof(long long*));
    memset(SpinSave,-1,2*sizeof(long long*));
    BondNOIndex=0;
    //SingleSpinNO=XSize*YSize;
    //void Bond2Spin2D(long long &BondNO,long long &Size,long long &SpinNO,long long &LeftSpin,long long &RightSpin)
    //printf("Build Bond \n");
    for(LoopNumA=0;LoopNumA < BondNO;LoopNumA+=1)
    {
       Bond2Spin2D(LoopNumA,XSize,SpinNO,SpinSave[0],SpinSave[1]);
       for(LoopNumB=0;LoopNumB < 2;LoopNumB+=1)
       {
            BondNORecord[LoopNumA*2+LoopNumB]= SpinSave[LoopNumB];
       }
       //BondNOIndex+=1;

    }

    /*
    if(BondNOIndex!=BondNO)
    {
        printf("Error!!!! BondNO=%d  BondNOIndex=%d  \n",BondNO,BondNOIndex);

    }
    */
    //printf("Build Hoperator \n");
    for(LoopNumA=0;LoopNumA < HoperatorNO;LoopNumA=LoopNumA+1)
    {
       for(LoopNumB=0;LoopNumB < 3 ; LoopNumB+=1 )
       {
            Hoperator[LoopNumA*3+LoopNumB]=-1 ;
       }

    }
    //printf("Build RdSpin \n");
    for(LoopNumA=0;LoopNumA < SpinNO*3;LoopNumA=LoopNumA+3)
    {
       //printf("%d-1 \n",LoopNumA);
       SpinSystem[LoopNumA]=(long long)pow(-1.0,(long long)(LoopNumA/3)%XSize+(long long)(LoopNumA/3)/XSize);
       SpinSystem[LoopNumA+2]=0;
       //RdSpin=genrand64_real2();
        RdSpin=genrand64_real2();
        if(RdSpin<0.3333333)
        {
           SpinSystem[LoopNumA+1]=1;
        }
        else if(RdSpin<0.6666667)
        {
           SpinSystem[LoopNumA+1]=-1;
        }
        else
        {
            SpinSystem[LoopNumA+1]=0;
        }

    }
    //printf("Build BondNOsystem \n");
   for(LoopNumA=0;LoopNumA < BondNO;LoopNumA+=1)
   {
       BondNOsystem[LoopNumA*2]=(double)(LoopNumA);
       BondNOsystem[LoopNumA*2+1]=J;

   }
    File=fopen("ModelPlot-1.txt", "w");
    for(LoopNumA=0;LoopNumA < BondNO;LoopNumA=LoopNumA+1)
    {
        //printf("%d \n",LoopNumA);
        fprintf(File,"%4.0lf  %2.4lf  ",BondNOsystem[LoopNumA*2],BondNOsystem[LoopNumA*2+1]);
        for (LoopNumB=0;LoopNumB<2;LoopNumB+=1)
        {
            fprintf(File," %4d  ",BondNORecord[LoopNumA*2+LoopNumB]);
        }
        for (LoopNumB=0;LoopNumB<2;LoopNumB+=1)
        {
            fprintf(File," %4d  ",SpinSystem[BondNORecord[LoopNumA*2+LoopNumB]*3+1]);
        }
        fprintf(File,"\n");
    }
    //printf("Free SpinSave \n");
    fclose(File);
    free(SpinSave);

}
