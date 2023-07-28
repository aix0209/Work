void DiaUpdate_Spin1(long long* SpinSystem,double* BondNOsystem,long long* Hoperator\
          ,double &Beta,long long &HNO,long long &Size,long long &SpinNO,long long &BondNO,long long &HoperatorNO,long long* BondNORecord\
          ,long long &XSize,long long &YSize,double &ConstC)
{
//最後一Spin為Ferromagnetic
   long long LoopNumA,LoopNumB,LoopNumC;
   long long RdNO;
   long long BondNumber,BondNumbertemp,BondNumberIndex;
   long long LeftSpin,RightSpin,LeftSpin2,RightSpin2,LeftSpin3,RightSpin3,LeftBond,RightBond,Bond1,Bond2,Bond3;
   long long SpinSystemSize,BondNOsystemSize,SwitchNO,Check,TempSA,TempSB;
   double Chance,Goal,Weight;
   FILE *File=NULL;
   Weight=ConstC;
   for(LoopNumA=0;LoopNumA <HoperatorNO*3;LoopNumA+=3)
    {
        //printf("LoopNumA=%d HoperatorNO=%d \n",LoopNumA,HoperatorNO*7);
        //printf("%d test DiaUpdateJQ3-a\n",LoopNumA);
        if(Hoperator[LoopNumA]==-1)//該Hoperator 為空
        {
           printf("H -1 \n");
           BondNumber=(long long)(BondNO*genrand64_real2());
           BondNumberIndex=BondNumber*2;


            //printf("%d test DiaUpdateJQ3-a %d \n",LoopNumA,BondNumber);
                //printf("HoperatorNO-HNO=%d  %f\n",HoperatorNO-HNO, (double)((BondNO)*(BondNOsystem[BondNumber*2+1]*Beta*0.5)));
                //printf("%d test DiaUpdateJQ3-a-1 J Bond %d \n",LoopNumA,BondNumber);
                //if(genrand64_real2()*(double)(HoperatorNO-HNO)*2<(double)((BondNO)*(BondNOsystem[BondNumber*2+1]*Beta)))
                //{
                   //Bond2Spin2D(BondNumber,Size,SpinNO,LeftSpin,RightSpin);
           if((long long)SpinSystem[BondNORecord[BondNumberIndex+1]*3+1]*(long long)SpinSystem[BondNORecord[BondNumberIndex+0]*3+1]==0)
           {

               if(genrand64_real2()*(double)(HoperatorNO-HNO)<(double)((BondNO)*(BondNOsystem[BondNumber*2+1]*Beta))*(Weight+1))
               {
                   if((long long)SpinSystem[BondNORecord[BondNumberIndex+1]*3+1]==(long long)SpinSystem[BondNORecord[BondNumberIndex+0]*3+1])
                   {

                           Hoperator[LoopNumA]=BondNumber*2;
                           Hoperator[LoopNumA+1]=BondNORecord[BondNumberIndex];
                           Hoperator[LoopNumA+2]=BondNORecord[BondNumberIndex+1];
                           HNO+=1;

                    }
                    else
                    {

                           Hoperator[LoopNumA]=BondNumber*2;
                           Hoperator[LoopNumA+1]=BondNORecord[BondNumberIndex];
                           Hoperator[LoopNumA+2]=BondNORecord[BondNumberIndex+1];
                           HNO+=1;


                    }

               }

           }
           else if ((long long)SpinSystem[BondNORecord[BondNumberIndex+1]*3+1]*(long long)SpinSystem[BondNORecord[BondNumberIndex]*3+1]==1)
           {
               //continue;

               if(genrand64_real2()*(double)(HoperatorNO-HNO)<(double)((BondNO)*(BondNOsystem[BondNumber*2+1]*Beta))*(Weight+0))
               {
                    Hoperator[LoopNumA]=BondNumber*2;
                    Hoperator[LoopNumA+1]=BondNORecord[BondNumberIndex];
                    Hoperator[LoopNumA+2]=BondNORecord[BondNumberIndex+1];
                    HNO+=1;


               }


           }
           else
           {
                if(genrand64_real2()*(double)(HoperatorNO-HNO)<(double)((BondNO)*(BondNOsystem[BondNumber*2+1]*Beta))*(Weight+2))
                {

                   Hoperator[LoopNumA]=BondNumber*2;
                   Hoperator[LoopNumA+1]=BondNORecord[BondNumberIndex];
                   Hoperator[LoopNumA+2]=BondNORecord[BondNumberIndex+1];
                   HNO+=1;

                }

           }


        }
        else//該Hoperator非空
        {

           if((Hoperator[LoopNumA]&1)==0)
           {
               printf("H  0 \n");
               if((long long)SpinSystem[BondNORecord[BondNumberIndex+1]*3+1]*(long long)SpinSystem[BondNORecord[BondNumberIndex+0]*3+1]==0)
               {
                   printf("H  0 SS=0 \n");
                   if(genrand64_real2()*((double)((BondNO)*(BondNOsystem[(long long)Hoperator[LoopNumA]]*Beta)*(Weight+1)))<(double)(HoperatorNO-HNO+1))
                   {

                       Hoperator[LoopNumA]=-1;
                       Hoperator[LoopNumA+1]=-1;
                       Hoperator[LoopNumA+2]=-1;
                       HNO-=1;


                   }

               }
               else if ((long long)SpinSystem[BondNORecord[BondNumberIndex+1]*3+1]*(long long)SpinSystem[BondNORecord[BondNumberIndex]*3+1]==1)
               {
                   //continue;
                  printf("H  0 SS=10 \n");
                   if(genrand64_real2()*((double)((BondNO)*(BondNOsystem[(long long)Hoperator[LoopNumA]]*Beta))*(Weight+1))<(double)(HoperatorNO-HNO+1))
                   {
                        Hoperator[LoopNumA]=-1;
                        Hoperator[LoopNumA+1]=-1;
                        Hoperator[LoopNumA+2]=-1;
                        HNO-=1;


                   }


               }
               else
               {
                    printf("H  0 SS=-10 \n");
                    if(genrand64_real2()*((double)((BondNO)*(BondNOsystem[(long long)Hoperator[LoopNumA]]*Beta))*(Weight+2))<(double)(HoperatorNO-HNO+1))
                    {

                       Hoperator[LoopNumA]=-1;
                       Hoperator[LoopNumA+1]=-1;
                       Hoperator[LoopNumA+2]=-1;
                       HNO-=1;

                    }

               }
            }
            else
            {
               printf("H  1 \n");
               if((long long)SpinSystem[BondNORecord[BondNumberIndex+1]*3+1]*(long long)SpinSystem[BondNORecord[BondNumberIndex+0]]==0)
               {

                   if((long long)SpinSystem[BondNORecord[BondNumberIndex+1]*3+1]==(long long)SpinSystem[BondNORecord[BondNumberIndex+0]*3+1])
                   {

                        if(genrand64_real2()<0.5)
                        {
                            SpinSystem[Hoperator[LoopNumA+1]*3+1]+=1;
                            SpinSystem[Hoperator[LoopNumA+2]*3+1]-=1;
                        }
                        else
                        {
                            SpinSystem[Hoperator[LoopNumA+1]*3+1]-=1;
                            SpinSystem[Hoperator[LoopNumA+2]*3+1]+=1;

                        }


                    }
                    else
                    {
                        if(SpinSystem[Hoperator[LoopNumA+1]*3+1]!=0)
                        {
                            if(SpinSystem[Hoperator[LoopNumA+1]*3+1]<0)
                            {
                                SpinSystem[Hoperator[LoopNumA+1]*3+1]+=1;
                                SpinSystem[Hoperator[LoopNumA+2]*3+1]-=1;

                            }
                            else
                            {
                                SpinSystem[Hoperator[LoopNumA+1]*3+1]-=1;
                                SpinSystem[Hoperator[LoopNumA+2]*3+1]+=1;

                            }
                        }
                        else
                        {
                            if(SpinSystem[Hoperator[LoopNumA+2]*3+1]<0)
                            {
                                SpinSystem[Hoperator[LoopNumA+1]*3+1]-=1;
                                SpinSystem[Hoperator[LoopNumA+2]*3+1]+=1;

                            }
                            else
                            {
                                SpinSystem[Hoperator[LoopNumA+1]*3+1]+=1;
                                SpinSystem[Hoperator[LoopNumA+2]*3+1]-=1;

                            }

                        }



                    }


               }
               else if ((long long)SpinSystem[BondNORecord[BondNumberIndex+1]*3+1]*(long long)SpinSystem[BondNORecord[BondNumberIndex]*3+1]==1)
               {
                   printf("Error Dia ±1,±1 off \n");
                   //continue;
                   /*
                   if(genrand64_real2()*(double)(HoperatorNO-HNO)<(double)((BondNO)*(BondNOsystem[BondNumber*2+1]*Beta))*(Weight+0))
                   {
                        Hoperator[LoopNumA]=BondNumber*2;
                        Hoperator[LoopNumA+1]=BondNORecord[BondNumberIndex];
                        Hoperator[LoopNumA+2]=BondNORecord[BondNumberIndex+1];
                        HNO+=1;


                   }
                   **/


               }
               else
               {
                    if(SpinSystem[Hoperator[LoopNumA+1]*3+1]>SpinSystem[Hoperator[LoopNumA+2]*3+1])
                    {
                        SpinSystem[Hoperator[LoopNumA+1]*3+1]-=1;
                        SpinSystem[Hoperator[LoopNumA+2]*3+1]+=1;
                    }
                    else
                    {
                        SpinSystem[Hoperator[LoopNumA+1]*3+1]+=1;
                        SpinSystem[Hoperator[LoopNumA+2]*3+1]-=1;
                    }


               }


            }
        }
    }










            //SwitchNO = Hoperator[LoopNumA]&15;
            //printf("diagnonal-update %d \n",SwitchNO);
            /*
            switch((Hoperator[LoopNumA]&7))
            {
                case 0://00
                    if(genrand64_real2()*((double)((BondNO)*(BondNOsystem[(long long)(Hoperator[LoopNumA]/8)*2+1]*Beta)*(Weight+1)))<(double)(HoperatorNO-HNO+1))
                    {
                        Hoperator[LoopNumA]=-1;
                        Hoperator[LoopNumA+1]=-1;
                        Hoperator[LoopNumA+2]=-1;
                        HNO-=1;
                    }
                    break;
                case 1://0 0 , - +

                        SpinSystem[Hoperator[LoopNumA+1]*3+1]+=1;
                        SpinSystem[Hoperator[LoopNumA+2]*3+1]-=1;
                        Hoperator[LoopNumA]-=1;
                        Hoperator[LoopNumA]+=6;
                        break;

                case 2://0 0, -+
                        SpinSystem[Hoperator[LoopNumA+1]*3+1]-=1;
                        SpinSystem[Hoperator[LoopNumA+2]*3+1]+=1;
                        Hoperator[LoopNumA]-=1;
                        Hoperator[LoopNumA]+=6;
                        break;
                case 3://0 0 ,±1
                    if(genrand64_real2()*((double)((BondNO)*(BondNOsystem[(long long)((Hoperator[LoopNumA]-3)/8)*2+1]*Beta))*(Weight+1))<(double)(HoperatorNO-HNO+1))
                    {
                        Hoperator[LoopNumA]=-1;
                        Hoperator[LoopNumA+1]=-1;
                        Hoperator[LoopNumA+2]=-1;
                        HNO-=1;
                    }
                    break;
                case 4://0,±1
                    TempSA=SpinSystem[Hoperator[LoopNumA+1]*3+1];
                    SpinSystem[Hoperator[LoopNumA+1]*3+1]=SpinSystem[Hoperator[LoopNumA+2]*3+1];
                    SpinSystem[Hoperator[LoopNumA+2]*3+1]=TempSA;
                    break;

                case 5:// +1/-1,+1/-1

                    if(genrand64_real2()*((double)((BondNO)*(BondNOsystem[(long long)((Hoperator[LoopNumA]-5)/8)*2+1]*Beta))*(Weight+1))<(double)(HoperatorNO-HNO+1))
                    {
                        Hoperator[LoopNumA]=-1;
                        Hoperator[LoopNumA+1]=-1;
                        Hoperator[LoopNumA+2]=-1;
                        HNO-=1;
                    }
                    break;
                case 6:
                    if(pinSystem[Hoperator[LoopNumA+1]*3+1]>SpinSystem[Hoperator[LoopNumA+2]*3+1])
                    {
                        Hoperator[LoopNumA]+=1;
                        Hoperator[LoopNumA]-=6;
                    }
                    else
                    {
                        Hoperator[LoopNumA]+=2;
                        Hoperator[LoopNumA]-=6;
                    }

                    SpinSystem[Hoperator[LoopNumA+1]*3+1]=0;
                    SpinSystem[Hoperator[LoopNumA+2]*3+1]=0;
                    break;
                case 7:
                    if(genrand64_real2()*((double)((BondNO)*(BondNOsystem[(long long)((Hoperator[LoopNumA]-7)/8)*2+1]*Beta))*(Weight+0))<(double)(HoperatorNO-HNO+1))
                    {
                        Hoperator[LoopNumA]=-1;
                        Hoperator[LoopNumA+1]=-1;
                        Hoperator[LoopNumA+2]=-1;
                        HNO-=1;
                    }
                    break
                case 8:
                    printf("Error,H = 8 \n ");

                default:
                    printf("Diagonal-Update %d  %d \n",Hoperator[LoopNumA],Hoperator[LoopNumA]&3);
                    system("pause");

            */

        //printf("%d test DiaUpdateJQ3-b %d \n",LoopNumA,BondNumber);





    /*
    File=fopen("Dia.txt", "w");
    for(LoopNumB=0;LoopNumB <HoperatorNO*3;LoopNumB=LoopNumB+3)
    {
        //printf("%2d ,H=%3d  ,L=%3d  ,R=%3d \n",LoopNumA/3, Hoperator[LoopNumA], Hoperator[LoopNumA+1], Hoperator[LoopNumA+2]);
        //printf("%4d ,H=%4d(%4d)  ,L=%4d  ,R=%4d \n",LoopNumB, Hoperator[LoopNumB],(Hoperator[LoopNumB]&7), Hoperator[LoopNumB+1], Hoperator[LoopNumB+2]);
        fprintf(File,"%4d ,H=%4d(%4d)  ,L=%4d  ,R=%4d \n",LoopNumB, Hoperator[LoopNumB],(Hoperator[LoopNumB]&7), Hoperator[LoopNumB+1], Hoperator[LoopNumB+2]);
    }
    fclose(File);
    */
    //printf("%d test DiaUpdateJQ3-c %d \n",LoopNumA,BondNumber);
}

