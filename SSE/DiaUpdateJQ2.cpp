void DiaUpdateJQ2(double* SpinSystem,double* BondNOsystem,long long* Hoperator\
          ,double &Beta,long long &HNO,long long &Size,long long &SpinNO,long long &BondNO,long long &HoperatorNO,long long* BondNORecord)
{
   long long LoopNumA,LoopNumB,LoopNumC;
   long long RdNO;
   long long BondNumber,BondNumbertemp,BondNumberIndex;
   long long LeftSpin,RightSpin,LeftSpin2,RightSpin2,LeftBond,RightBond;
   long long SpinSystemSize,BondNOsystemSize;
   double Chance,Goal;
   
   SpinSystemSize=SpinNO;
   //BondNO=len64(BondNOsystem)/2;
   //HoperatorNO=len(Hoperator)/3;
   //srand(time(NULL));
   //printf("%d",BondNO);
   //printf("%f \n",BondNOsystem[BondNumber*2+1]);
   for(LoopNumA=0;LoopNumA <HoperatorNO*5;LoopNumA=LoopNumA+5)
    {
        

        if(Hoperator[LoopNumA]==-1)//該Hoperator 為空
        {
            
            BondNumber=(long long)(BondNO*genrand64_real2());
            BondNumberIndex=BondNumber*4;
            //BondNumber=(long long)(BondNO*_rand());
            //Goal=genrand64_real2()*(double)(HoperatorNO-HNO);
            //Chance=(double)((BondNO)*(BondNOsystem[BondNumber*2+1]*Beta*0.5));
            //if(Goal<Chance )
            if (BondNumber<(long long)(BondNO*0.5))//J Bond
            {
                if(genrand64_real2()*(double)(HoperatorNO-HNO)<(double)((BondNO)*(BondNOsystem[BondNumber*2+1]*Beta*0.5)))
                {
                   //Bond2Spin2D(BondNumber,Size,SpinNO,LeftSpin,RightSpin);
                   
                   if(SpinSystem[BondNORecord[BondNumberIndex]*3+1]==SpinSystem[BondNORecord[BondNumberIndex+1]*3+1]*(-1))
                   {
                       Hoperator[LoopNumA]=BondNumber*10;
                       Hoperator[LoopNumA+1]=BondNORecord[BondNumberIndex];
                       Hoperator[LoopNumA+2]=BondNORecord[BondNumberIndex+1];
                       HNO+=1;
                    }
                }
                
            }
            else//Q Bond
            {
                //printf("HoperatorNO-HNO=%d  %f\n",HoperatorNO-HNO, (double)(BondNO)*(BondNOsystem[BondNumber*2+1]*Beta*0.25));
                if(genrand64_real2()*(double)(HoperatorNO-HNO)<(double)((BondNO)*(BondNOsystem[BondNumber*2+1]*Beta*0.25)))
                {
                   
                   //BondNumbertemp=BondNumber-(long long)(BondNO*0.5);
                   //Q2Bond2Bond2D(BondNumbertemp,Size,SpinNO,LeftBond,RightBond);
                   //printf("LeftBond=%d RightBond=%d \n",LeftBond,RightBond);
                   //Bond2Spin2D(LeftBond,Size,SpinNO,LeftSpin,RightSpin);             
                   //Bond2Spin2D(RightBond,Size,SpinNO,LeftSpin2,RightSpin2);
                   //printf("LeftSpin=%d RightSpin=%d LeftSpin2=%d RightSpin2=%d \n",LeftSpin,RightSpin,LeftSpin2,RightSpin2);
                   if(SpinSystem[BondNORecord[BondNumberIndex]*3+1]==SpinSystem[BondNORecord[BondNumberIndex+1]*3+1]*(-1) and \
                   SpinSystem[BondNORecord[BondNumberIndex+2]*3+1]==SpinSystem[BondNORecord[BondNumberIndex+3]*3+1]*(-1))
                   {
                       Hoperator[LoopNumA]=BondNumber*10+2;
                       Hoperator[LoopNumA+1]=BondNORecord[BondNumberIndex];
                       Hoperator[LoopNumA+2]=BondNORecord[BondNumberIndex+1];
                       Hoperator[LoopNumA+3]=BondNORecord[BondNumberIndex+2];
                       Hoperator[LoopNumA+4]=BondNORecord[BondNumberIndex+3];
                       HNO+=1;
                    }
                }                
                
            }

        }
        else//該Hoperator非空
        {
            switch(Hoperator[LoopNumA]%10)
            {
                case 0:
                    if(genrand64_real2()*((double)((BondNO)*(BondNOsystem[(long long)(Hoperator[LoopNumA]*0.2)+1]*Beta*0.5)))<(double)(HoperatorNO-HNO+1))
                    {
                       Hoperator[LoopNumA]=-1;
                       Hoperator[LoopNumA+1]=-1;
                       Hoperator[LoopNumA+2]=-1;
                       Hoperator[LoopNumA+3]=-1;
                       Hoperator[LoopNumA+4]=-1;
                       HNO-=1;
                    }
                    break;
                case 1:
                    SpinSystem[Hoperator[LoopNumA+1]*3+1]*=(-1);
                    SpinSystem[Hoperator[LoopNumA+2]*3+1]*=(-1);
                    break;
                case 2:
                    if(genrand64_real2()*((double)((BondNO)*(BondNOsystem[(long long)(Hoperator[LoopNumA]*0.2)+1]*Beta*0.25)))<(double)(HoperatorNO-HNO+1))
                    {
                       Hoperator[LoopNumA]=-1;
                       Hoperator[LoopNumA+1]=-1;
                       Hoperator[LoopNumA+2]=-1;
                       Hoperator[LoopNumA+3]=-1;
                       Hoperator[LoopNumA+4]=-1;
                       HNO-=1;
                    }
                    break;
                case 5:
                    SpinSystem[Hoperator[LoopNumA+1]*3+1]*=(-1);
                    SpinSystem[Hoperator[LoopNumA+2]*3+1]*=(-1);
                    break;
                case 6:
                    SpinSystem[Hoperator[LoopNumA+3]*3+1]*=(-1);
                    SpinSystem[Hoperator[LoopNumA+4]*3+1]*=(-1);
                    break;
                case 9:
                    SpinSystem[Hoperator[LoopNumA+1]*3+1]*=(-1);
                    SpinSystem[Hoperator[LoopNumA+2]*3+1]*=(-1);
                    SpinSystem[Hoperator[LoopNumA+3]*3+1]*=(-1);
                    SpinSystem[Hoperator[LoopNumA+4]*3+1]*=(-1);
                    break; 
            }
        }
    }
}
