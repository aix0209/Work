long long AddHoperatorJQ2(long long** Hoperator,long long &HNO,long long &HoperatorNO,long long &CurrentT)
{
    long long OldLenth,LoopNumA,Check,NewLenth,*Temp,*Temp1;
    double c,multiple;
    //if((double)HNO/(double)(len(*Hoperator)/3)>=0.8)
    //{
    //printf("d \n");
    multiple=1.33333;
    //printf("%d \n",HoperatorNO);
    OldLenth=HoperatorNO*5;
    NewLenth=(long long)(HNO*multiple);
    NewLenth*=5;
    if(NewLenth<=HoperatorNO*5)
    {
        return 0;
    }
    else
    {
        HoperatorNO=NewLenth/5;
        printf("CurrentT=%5d ,HoperatorNO=%5d \n",CurrentT,HoperatorNO);
        Temp=*Hoperator;
        *Hoperator=(long long*)malloc((NewLenth+1)*sizeof(long long*));
        memset((*Hoperator),-1,(NewLenth+1)*sizeof(long long*));
        for(LoopNumA=0;LoopNumA< OldLenth;LoopNumA++)
        {
            (*Hoperator)[LoopNumA]=Temp[LoopNumA];
        }
        /*for(LoopNumA=OldLenth;LoopNumA< NewLenth;LoopNumA++)
        {
            (*Hoperator)[LoopNumA]=-1;
        }*/
        (*Hoperator)[NewLenth]=-999;
        free(Temp);
        return 0;
    }
    //printf("%d \n",len(*Hoperator));
   // }
    
}
