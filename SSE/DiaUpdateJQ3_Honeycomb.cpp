void DiaUpdateJQ3_Honeycomb(long long* SpinSystem,double* BondNOsystem,long long* Hoperator\
          ,double &Beta,long long &HNO,long long &Size,long long &SpinNO,long long &BondNO,long long &HoperatorNO,long long* BondNORecord,long long &XSize,long long &YSize)
{
   long long LoopNumA,LoopNumB,LoopNumC;
   long long RdNO;
   long long BondNumber,BondNumbertemp,BondNumberIndex;
   long long LeftSpin,RightSpin,LeftSpin2,RightSpin2,LeftSpin3,RightSpin3,LeftBond,RightBond,Bond1,Bond2,Bond3;
   long long SpinSystemSize,BondNOsystemSize;
   double Chance,Goal;
   
   //SpinSystemSize=SpinNO;
   for(LoopNumA=0;LoopNumA <HoperatorNO*7;LoopNumA=LoopNumA+7)
    {
        //printf("LoopNumA=%d HoperatorNO=%d \n",LoopNumA,HoperatorNO*7);
        //printf("%d test DiaUpdateJQ3-a\n",LoopNumA);
        if(Hoperator[LoopNumA]==-1)//該Hoperator 為空
        {
            //printf(" %d \n",BondNO);
            BondNumber=(long long)(BondNO*genrand64_real2());
            BondNumberIndex=BondNumber*6;
            //printf("%d test DiaUpdateJQ3-a %d \n",LoopNumA,BondNumber);
            if (BondNumber<(long long)(1.5*SpinNO))//J Bond
            {
                //printf("HoperatorNO-HNO=%d  %f\n",HoperatorNO-HNO, (double)((BondNO)*(BondNOsystem[BondNumber*2+1]*Beta*0.5)));
                //printf("%d test DiaUpdateJQ3-a-1 J Bond %d \n",LoopNumA,BondNumber);
                if(genrand64_real2()*(double)(HoperatorNO-HNO)*2<(double)((BondNO)*(BondNOsystem[BondNumber*2+1]*Beta)))
                {
                   //Bond2Spin2D(BondNumber,Size,SpinNO,LeftSpin,RightSpin);
                   
                   if((long long)SpinSystem[BondNORecord[BondNumberIndex]*3+1]==(long long)SpinSystem[BondNORecord[BondNumberIndex+1]*3+1]*(-1))
                   {
                       Hoperator[LoopNumA]=BondNumber*16;
                       Hoperator[LoopNumA+1]=BondNORecord[BondNumberIndex];
                       Hoperator[LoopNumA+2]=BondNORecord[BondNumberIndex+1];
                       //printf("Dia %d ,%d \n",BondNORecord[BondNumberIndex],BondNORecord[BondNumberIndex+1]);
                       //Hoperator[LoopNumA+3]=-1;
                       //Hoperator[LoopNumA+4]=-1;
                       //Hoperator[LoopNumA+5]=-1;
                       //Hoperator[LoopNumA+6]=-1; 
                       HNO+=1;
                    }
                }
                
            }
            else//Q3 Bond
            {
                //printf("HoperatorNO-HNO=%d  %f\n",HoperatorNO-HNO, (double)((BondNO)*(BondNOsystem[BondNumber*2+1]*Beta*0.125)));
                if(genrand64_real2()*(double)(HoperatorNO-HNO)*8<(double)((BondNO)*(BondNOsystem[BondNumber*2+1]*Beta)))
                {
                   //printf("Y-HoperatorNO-HNO=%d  %f\n",HoperatorNO-HNO, (double)((BondNO)*(BondNOsystem[BondNumber*2+1]*Beta*0.125)));
                   //BondNumbertemp=BondNumber-(long long)(BondNO*0.5);
                   //Q3Bond2Bond2D(BondNumbertemp,Size,SpinNO,Bond1,Bond2,Bond3);
                   //printf("LeftBond=%d RightBond=%d \n",LeftBond,RightBond);
                   //Bond2Spin2D(Bond1,Size,SpinNO,LeftSpin,RightSpin);             
                   //Bond2Spin2D(Bond2,Size,SpinNO,LeftSpin2,RightSpin2);
                   //Bond2Spin2D(Bond3,Size,SpinNO,LeftSpin3,RightSpin3);
                   //printf("LeftSpin=%d RightSpin=%d LeftSpin2=%d RightSpin2=%d \n",LeftSpin,RightSpin,LeftSpin2,RightSpin2);
                   if((long long)SpinSystem[BondNORecord[BondNumberIndex]*3+1]==(long long)SpinSystem[BondNORecord[BondNumberIndex+1]*3+1]*(-1) and \
                   (long long)SpinSystem[BondNORecord[BondNumberIndex+2]*3+1]==(long long)SpinSystem[BondNORecord[BondNumberIndex+3]*3+1]*(-1) and \
                   (long long)SpinSystem[BondNORecord[BondNumberIndex+4]*3+1]==(long long)SpinSystem[BondNORecord[BondNumberIndex+5]*3+1]*(-1))
                   {
                       Hoperator[LoopNumA]=BondNumber*16+2;//*13 bond碼編號
                       Hoperator[LoopNumA+1]=BondNORecord[BondNumberIndex];
                       Hoperator[LoopNumA+2]=BondNORecord[BondNumberIndex+1];
                       Hoperator[LoopNumA+3]=BondNORecord[BondNumberIndex+2];
                       Hoperator[LoopNumA+4]=BondNORecord[BondNumberIndex+3];
                       Hoperator[LoopNumA+5]=BondNORecord[BondNumberIndex+4];
                       Hoperator[LoopNumA+6]=BondNORecord[BondNumberIndex+5];
                       HNO+=1;
                    }
                }                
                
            }

        }
        else//該Hoperator非空
        {
            switch((Hoperator[LoopNumA]&15))
            {
                case 0:
                    if(genrand64_real2()*((double)((BondNO)*(BondNOsystem[((long long)(Hoperator[LoopNumA]>>4)*2)+1]*Beta)))<(double)(HoperatorNO-HNO+1)*2)
                    {
                        Hoperator[LoopNumA]=-1;
                        Hoperator[LoopNumA+1]=-1;
                        Hoperator[LoopNumA+2]=-1;
                        Hoperator[LoopNumA+3]=-1;
                        Hoperator[LoopNumA+4]=-1;
                        Hoperator[LoopNumA+5]=-1;
                        Hoperator[LoopNumA+6]=-1;
                        HNO-=1;
                    }
                    break;
                case 1:
                    SpinSystem[Hoperator[LoopNumA+1]*3+1]*=(-1);
                    SpinSystem[Hoperator[LoopNumA+2]*3+1]*=(-1);
                    break;
                case 2:
                    if(genrand64_real2()*((double)((BondNO)*(BondNOsystem[(((long long)((Hoperator[LoopNumA]-2)>>4))*2)+1]*Beta)))<(double)(HoperatorNO-HNO+1)*8)
                    {
                        Hoperator[LoopNumA]=-1;
                        Hoperator[LoopNumA+1]=-1;
                        Hoperator[LoopNumA+2]=-1;
                        Hoperator[LoopNumA+3]=-1;
                        Hoperator[LoopNumA+4]=-1;
                        Hoperator[LoopNumA+5]=-1;
                        Hoperator[LoopNumA+6]=-1;
                        HNO-=1;
                    }
                    break;
                case 5://Bond1 off 2+3
                    SpinSystem[Hoperator[LoopNumA+1]*3+1]*=(-1);
                    SpinSystem[Hoperator[LoopNumA+2]*3+1]*=(-1);
                    break;
                case 6://Bond2 off 2+4
                    SpinSystem[Hoperator[LoopNumA+3]*3+1]*=(-1);
                    SpinSystem[Hoperator[LoopNumA+4]*3+1]*=(-1);
                    break;
                case 7://Bond3 off 2+5
                    SpinSystem[Hoperator[LoopNumA+5]*3+1]*=(-1);
                    SpinSystem[Hoperator[LoopNumA+6]*3+1]*=(-1);               
                    break;
                case 9://Bond1 2 off 2+3+4 
                    SpinSystem[Hoperator[LoopNumA+1]*3+1]*=(-1);
                    SpinSystem[Hoperator[LoopNumA+2]*3+1]*=(-1);
                    SpinSystem[Hoperator[LoopNumA+3]*3+1]*=(-1);
                    SpinSystem[Hoperator[LoopNumA+4]*3+1]*=(-1);
                    break;
                case 10://Bond1 3 off 2+3+5
                    SpinSystem[Hoperator[LoopNumA+1]*3+1]*=(-1);
                    SpinSystem[Hoperator[LoopNumA+2]*3+1]*=(-1);
                    SpinSystem[Hoperator[LoopNumA+5]*3+1]*=(-1);
                    SpinSystem[Hoperator[LoopNumA+6]*3+1]*=(-1);
                    break;
                case 11: //Bond2 3 off 2+4+5                 
                    SpinSystem[Hoperator[LoopNumA+3]*3+1]*=(-1);
                    SpinSystem[Hoperator[LoopNumA+4]*3+1]*=(-1);
                    SpinSystem[Hoperator[LoopNumA+5]*3+1]*=(-1);
                    SpinSystem[Hoperator[LoopNumA+6]*3+1]*=(-1);
                    break;
                case 14://Bond1 2 3 off 2+3+4+5
                    SpinSystem[Hoperator[LoopNumA+1]*3+1]*=(-1);
                    SpinSystem[Hoperator[LoopNumA+2]*3+1]*=(-1);
                    SpinSystem[Hoperator[LoopNumA+3]*3+1]*=(-1);
                    SpinSystem[Hoperator[LoopNumA+4]*3+1]*=(-1);
                    SpinSystem[Hoperator[LoopNumA+5]*3+1]*=(-1);
                    SpinSystem[Hoperator[LoopNumA+6]*3+1]*=(-1);
                    break;
              
            }
        }
        //printf("%d test DiaUpdateJQ3-b %d \n",LoopNumA,BondNumber);
        /*
        for(LoopNumB=0;LoopNumB <HoperatorNO*7;LoopNumB=LoopNumB+7)
        {
            //printf("%2d ,H=%3d  ,L=%3d  ,R=%3d \n",LoopNumA/3, Hoperator[LoopNumA], Hoperator[LoopNumA+1], Hoperator[LoopNumA+2]);
            printf("%2d ,H=%3d  ,L=%3d  ,R=%3d ,L2=%3d  ,R2=%3d ,L3=%3d  ,R3=%3d\n",LoopNumB, Hoperator[LoopNumB], Hoperator[LoopNumB+1], Hoperator[LoopNumB+2], Hoperator[LoopNumB+3], Hoperator[LoopNumB+4], Hoperator[LoopNumB+5], Hoperator[LoopNumB+6]);
        }
        * */
               
    }
    //printf("%d test DiaUpdateJQ3-c %d \n",LoopNumA,BondNumber);
}
