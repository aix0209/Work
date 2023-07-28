void DiaUpdate(double* SpinSystem,double* BondNOsystem,long long* Hoperator\
          ,double &Beta,long long &HNO,long long &Size,long long &SpinNO,long long &BondNO,long long &HoperatorNO,long long* BondNORecord)
{
   long long LoopNumA,LoopNumB,LoopNumC;
   long long RdNO;
   long long BondNumber,BondNumberIndex;
   long long LeftSpin,RightSpin;
   long long SpinSystemSize,BondNOsystemSize;
   double Chance,Goal;
   
   SpinSystemSize=SpinNO;
   //BondNO=len64(BondNOsystem)/2;
   //HoperatorNO=len(Hoperator)/3;
   //srand(time(NULL));
   //printf("%d",BondNO);
   //printf("%f \n",BondNOsystem[BondNumber*2+1]);
   for(LoopNumA=0;LoopNumA <HoperatorNO*3;LoopNumA=LoopNumA+3)
    {
        

        if(Hoperator[LoopNumA]==-1)//該Hoperator 為空
        {
            
            BondNumber=(long long)(BondNO*genrand64_real2());
            BondNumberIndex=BondNumber*2;
            //BondNumber=(long long)(BondNO*_rand());
            //Goal=genrand64_real2()*(double)(HoperatorNO-HNO);
            //Chance=(double)((BondNO)*(BondNOsystem[BondNumber*2+1]*Beta*0.5));
            //if(Goal<Chance )
            if(genrand64_real2()*(double)(HoperatorNO-HNO)<=(double)((BondNO)*(BondNOsystem[BondNumber*2+1]*Beta*0.5)))
            {
               //Bond2Spin2D(BondNumber,Size,SpinNO,LeftSpin,RightSpin);
               
               if(SpinSystem[BondNORecord[BondNumberIndex]*3+1]==SpinSystem[BondNORecord[BondNumberIndex+1]*3+1]*(-1))
               {
                   Hoperator[LoopNumA]=BondNumber*2;
                   Hoperator[LoopNumA+1]=BondNORecord[BondNumberIndex];
                   Hoperator[LoopNumA+2]=BondNORecord[BondNumberIndex+1];
                   HNO+=1;
                }
            }
        }
        else if (Hoperator[LoopNumA]%2==0)//該Hoperator 為dia
        {
            //Goal=genrand64_real2()*((double)((BondNO)*(BondNOsystem[Hoperator[LoopNumA]+1]*Beta*0.5)));
            //Chance=(double)(HoperatorNO-HNO+1);
            //if(Goal<Chance)
            if(genrand64_real2()*((double)((BondNO)*(BondNOsystem[Hoperator[LoopNumA]+1]*Beta*0.5)))<(double)(HoperatorNO-HNO+1))
            {
            //BondNOsystem[Hoperator[LoopNumA]+1]，Hoperator[LoopNumA]=Hoperator[LoopNumA]/2*2
                   Hoperator[LoopNumA]=-1;
                   Hoperator[LoopNumA+1]=-1;
                   Hoperator[LoopNumA+2]=-1;
                   HNO-=1;
            }
        }
        else//該Hoperator 為off-dia
        {
           SpinSystem[Hoperator[LoopNumA+1]*3+1]*=(-1);
           SpinSystem[Hoperator[LoopNumA+2]*3+1]*=(-1);
        }
    }
}
