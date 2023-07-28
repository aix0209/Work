long long AddHoperator(long long** Hoperator,long long &HNO,long long &HoperatorNO,long long &CurrentT)
{
    long long OldLenth,LoopNumA,LoopNumB,Check,NewLenth,*Temp=NULL,*Temp1;
    double c,multiple;
    FILE *File=NULL;
    //if((double)HNO/(double)(len(*Hoperator)/3)>=0.8)
    //{
    //printf("d \n");
    multiple=1.33333;
    //printf("%d \n",HoperatorNO);
    OldLenth=HoperatorNO*3;
    NewLenth=(long long)(HNO*multiple)*3;
    //NewLenth*=3;
    if(NewLenth<=OldLenth)
    {
        return 0;
    }
    else
    {
        HoperatorNO=(long long )(NewLenth/3);
        printf("CurrentT=%5d ,HoperatorNO=%5d \n",CurrentT,HoperatorNO);
        Temp=*Hoperator;
        //printf("Bulid New Hoperator \n",CurrentT,HoperatorNO);
        *Hoperator=(long long*)malloc((NewLenth+1)*sizeof(long long*));
        memset((*Hoperator),-1,(NewLenth+1)*sizeof(long long*));
        //printf("Restore New Hoperator \n",CurrentT,HoperatorNO);

        for(LoopNumA=0;LoopNumA< OldLenth;LoopNumA++)
        {
            (*Hoperator)[LoopNumA]=Temp[LoopNumA];
        }
        /*
        File=fopen("Dia-2.txt", "w");
        for(LoopNumB=0;LoopNumB <HoperatorNO*3;LoopNumB=LoopNumB+3)
        {
            //printf("%2d ,H=%3d  ,L=%3d  ,R=%3d \n",LoopNumA/3, Hoperator[LoopNumA], Hoperator[LoopNumA+1], Hoperator[LoopNumA+2]);
            //printf("%4d ,H=%4d(%4d)  ,L=%4d  ,R=%4d \n",LoopNumB, Hoperator[LoopNumB],(Hoperator[LoopNumB]&7), Hoperator[LoopNumB+1], Hoperator[LoopNumB+2]);
            fprintf(File,"%4d ,H=%4d(%4d)  ,L=%4d  ,R=%4d \n",LoopNumB, *Hoperator[LoopNumB],*Hoperator[LoopNumB]&7, *Hoperator[LoopNumB+1], *Hoperator[LoopNumB+2]);
        }
        fclose(File);
        */
        /*for(LoopNumA=OldLenth;LoopNumA< NewLenth;LoopNumA++)
        {
            (*Hoperator)[LoopNumA]=-1;
        }*/
        //(*Hoperator)[NewLenth]=-999;
        //printf("Done1 \n",CurrentT,HoperatorNO);
        free(Temp);
        //printf("Done2 \n",CurrentT,HoperatorNO);
        Temp=NULL;
        return 0;
    }
    //printf("%d \n",len(*Hoperator));
   // }
    
}
