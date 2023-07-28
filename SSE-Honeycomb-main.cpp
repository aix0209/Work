#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "SSE\mt19937-64.c"
#include "SSE\AddHoperatorJQ3.cpp"
#include "SSE\Bond2Spin.cpp"
#include "SSE\DiaUpdateJQ3_Honeycomb.cpp"
#include "SSE\LoopUpdateJQ3.cpp"
#include "SSE\MakeLattice.cpp"
#include "SSE\MeasureFuct.cpp"
#include <ctime>

int main(int argc, char *argv[])
{
    long long LoopNumA,LoopNumB,LoopNumC,AddHStatus,Type;
    long long Size,XSize,YSize,SpinNO,BondNO,HoperatorNO,T,MeasureT,HNO,MeasureStep;
    long long SpinSystemSize,BondNOsystemSize,HoperatorSize,SpinSize,BondSize,HSize,SeedNum;
    double *SpinSystem,*BondNOsystem,RdSpin;
    double LoopJ,LoopBeta,Beta,J,StrongJ,Probability,Q,StrongQ;
    long long *Hoperator,*BondNORecord;
    //測量變數
    double AFM,AFM1,AFM2,AFM4,AFM6,AX1,Measure,MeansMeasure,Means,STD,STDD,WiddingX,WiddingY,WiddingZ,TempW;
    double *UsuscMent,*AFMMent,*AFM1Ment,*AFM2Ment,*AFM4Ment,*AFM6Ment,*AX1Ment,\
    *WindingXMent,*WindingYMent,*WindingZMent,*TempWMent;//,*Widding;
    char FileName[80],BetaChar,FileNameDetail[80],FileNameTime[80];
    double JMeans,JSTD,JErr,UsuscMeans,UsuscSTD,UsuscErr,AFM1Means,AFM1STD,AFM1Err,AFM2Means,AFM2STD,AFM2Err,\
    AFM4Means,AFM4STD,AFM4Err,AFM6Means,AFM6STD,AFM6Err,AX1Means,AX1STD,AX1Err,\
    WindingXMeans,WindingXSTD,WindingXErr,\
    WindingYMeans,WindingYSTD,WindingYErr,\
    TempWMeans,TempWSTD,TempWErr;
    double BetaReadAll,JMeansAll,JSTDAll,JErrAll,UsuscMeansAll,UsuscSTDAll,UsuscErrAll,AFM1MeansAll,AFM1STDAll,AFM1ErrAll,AFM2MeansAll,AFM2STDAll,AFM2ErrAll,\
    AFM4MeansAll,AFM4STDAll,AFM4ErrAll,AFM6MeansAll,AFM6STDAll,AFM6ErrAll,AX1MeansAll,AX1STDAll,AX1ErrAll,\
    WindingXMeansAll,WindingXSTDAll,WindingXErrAll,\
    TempWMeansAll,TempWSTDAll,TempWErrAll,\
    WindingYMeansAll,WindingYSTDAll,WindingYErrAll,JReadAll,StrongJReadAlls,\
    Q1MeansAll,Q1STDAll,Q1ErrAll,Q2MeansAll,Q2STDAll,Q2ErrAll;   
    int err,nproc,myid;
    clock_t StartTime, EndTime;
    FILE *File=NULL,*FileDetail=NULL,*FileTime=NULL;
    //unsigned long long long long init[4]={0x12345ULL, 0x23456ULL, 0x34567ULL, 0x45678ULL}, length=4;
    //init_by_array64(init, length);

    init_genrand64(atoi(argv[12])+(long long)getpid());

    if (genrand64_real2()>0.5)
    {
        SeedNum=(long long)(time(NULL)+atoi(argv[12])-10000*atoi(argv[12])*genrand64_real2()+10000*(long long)getpid());        
    }
    else
    {
        SeedNum=(long long)(time(NULL)-atoi(argv[12])+10000*atoi(argv[12])*genrand64_real2()-10000*(long long)getpid());       
    }
    init_genrand64(SeedNum);
    XSize=atoi(argv[1]);
    YSize=atoi(argv[2]);
    //YSize = XSize;
    Beta=(double)(atof(argv[3])/10000.0);
    J=(double)(atoi(argv[4])/10000.0);
    StrongJ=(double)(atoi(argv[5])/10000.0);
    Q=(double)(atoi(argv[6])/10000.0);
    StrongQ=(double)(atoi(argv[7])/10000.0);
    Type=31;
    Probability=0.5;
    T=atoi(argv[8]);
    MeasureT=atoi(argv[9]);
    MeasureStep=atoi(argv[10]);
    //InitialParameter(XSize,YSize,HoperatorNO,HNO,Beta,J,T,MeasureT,MeasureStep,StrongJ);
    //InitialParameter((YSize,HoperatorNO,HNO,Beta,J,T,MeasureT,MeasureStep);
    HoperatorNO=20;//#Operator初始數量(M個)
    HNO=0;
    Size=XSize;//晶格大小，單邊
    SpinNO=XSize*YSize;
    SpinSystemSize=SpinNO*3;
    //printf("Initial\n");
    
    if(Type<10)
    {
        BondNO=SpinNO*2;
        BondNORecord=(long long *)malloc((BondNO*2+1)*sizeof(long long*));
        memset(BondNORecord,-1,(BondNO*2+1)*sizeof(long long*)); 
    }
    else if(Type<20)
    {
        BondNO=SpinNO*4;
        BondNORecord=(long long *)malloc((BondNO*4+1)*sizeof(long long*));
        memset(BondNORecord,-1,(BondNO*4+1)*sizeof(long long*)); 
    }
    else if(Type<30)
    {
        switch(Type)
        {
            case 20:
                BondNO=SpinNO*4;
                BondNORecord=(long long *)malloc((BondNO*6+1)*sizeof(long long*));
                memset(BondNORecord,-1,(BondNO*6+1)*sizeof(long long*)); 
                break;
            case 201:
                BondNO=SpinNO*4;
                BondNORecord=(long long *)malloc((BondNO*7+1)*sizeof(long long*));
                memset(BondNORecord,-1,(BondNO*7+1)*sizeof(long long*)); 
                break;
            case 21:
                //printf("memset\n");
                BondNO=SpinNO*6;
                BondNORecord=(long long *)malloc((BondNO*6+1)*sizeof(long long*));
                memset(BondNORecord,-1,(BondNO*6+1)*sizeof(long long*));
                break;
        }
    }
    else
    {
        switch(Type)
        {
            case 30:
                BondNO=SpinNO+(long long)(XSize/2)*YSize;
                BondNORecord=(long long *)malloc((BondNO*6+1)*sizeof(long long*));
                memset(BondNORecord,-1,(BondNO*6+1)*sizeof(long long*)); 
                break;
            case 31:
                BondNO=SpinNO+((long long)(XSize/2)*YSize)*3;
                BondNORecord=(long long *)malloc((BondNO*6+1)*sizeof(long long*));
                memset(BondNORecord,-1,(BondNO*6+1)*sizeof(long long*)); 
                break;
            case 32:
                BondNO=SpinNO+((long long)(XSize/2)*YSize)*3-8;
                BondNORecord=(long long *)malloc((BondNO*6+1)*sizeof(long long*));
                memset(BondNORecord,-1,(BondNO*6+1)*sizeof(long long*)); 
                break;           
            
        }     

      
        
    }
    //BondNO=SpinNO*4;
    BondNOsystemSize=BondNO*2;
    //printf("test X=%d Y=%d SpinNO=%d BondNO=%d\n",XSize,YSize,SpinNO,BondNO);
    HoperatorSize=HoperatorNO*7;//*3 J modle *5 JQ2 modle *7 JQ3 modle
    LoopBeta=1.0;
    LoopJ=1.0;
    Measure=0;
    MeansMeasure=0;
    Means=0;
    STD=0;
    WiddingX=0;
    WiddingY=0;
    WiddingZ=0;
    TempW=0.0;
    StartTime=clock();
    
    //printf("Initial\n");
    //printf("test");
    AFMMent=(double *)malloc((MeasureT/MeasureStep+1)*sizeof(double*));
    AFM1Ment=(double *)malloc((MeasureT/MeasureStep+1)*sizeof(double*));
    AFM2Ment=(double *)malloc((MeasureT/MeasureStep+1)*sizeof(double*));
    AFM4Ment=(double *)malloc((MeasureT/MeasureStep+1)*sizeof(double*));
    AFM6Ment=(double *)malloc((MeasureT/MeasureStep+1)*sizeof(double*));
    AX1Ment=(double *)malloc((MeasureT/MeasureStep+1)*sizeof(double*));
    WindingXMent=(double *)malloc((MeasureT/MeasureStep+1)*sizeof(double*));
    WindingYMent=(double *)malloc((MeasureT/MeasureStep+1)*sizeof(double*));
    WindingZMent=(double *)malloc((MeasureT/MeasureStep+1)*sizeof(double*));
    TempWMent=(double *)malloc((MeasureT/MeasureStep+1)*sizeof(double*));
    UsuscMent=(double *)malloc((MeasureT/MeasureStep+1)*sizeof(double*));
    Hoperator=(long long *)malloc((HoperatorSize+1)*sizeof(long long*));
    memset(Hoperator,-1,(HoperatorSize+1)*sizeof(long long*));
    Hoperator[HoperatorSize]=-999;
    SpinSystem=(double *)malloc((SpinSystemSize+1)*sizeof(double*));
    SpinSystem[SpinSystemSize]=-999;  
    BondNOsystem=(double *)malloc((BondNOsystemSize+1)*sizeof(double*));
    BondNOsystem[BondNOsystemSize]=-999;
    //memset(BondNORecord,-1,(BondNO+1)*sizeof(long long*));
    
    //兩格一組，BondNO第一格編號、第二格紀錄Bond強度J
    //printf("test \n");

    /*
     * 三格一組，Hoperator第一格記H是dia N%2=0 or 0ff-dia N%2=1 、第二格紀錄左邊的spin編號、第三格紀錄右邊spin編號
    */

    /*
     * 第一格記Spin的編號、第二格紀錄Spin的方向 1/-1、第三格紀錄是否有operator作用
     * 
     */ 
    
    ///MakeLattice(Type,SpinSystem,BondNOsystem,Hoperator,Size,SpinNO,BondNO,HoperatorNO,J,StrongJ,Probability);
    //printf("MakeLattice\n");
    
    MakeLattice_Honeycomb_JQ3_Clean(Type,SpinSystem,BondNOsystem,Hoperator,Size,SpinNO,BondNO,HoperatorNO,J,StrongJ,Q,StrongQ,Probability,BondNORecord,XSize,YSize);
    /*
    for(LoopNumA=0;LoopNumA < BondNO;LoopNumA=LoopNumA+1)
    {
        for (LoopNumB=0;LoopNumB<7;LoopNumB+=1)
        {
            printf("  %d  ",BondNORecord[LoopNumA*7+LoopNumB]); 
        }
        printf("\n"); 
    
    }
    system("pause");
    */
    /*
     *1.Herring
     *2.Plaquette 
     * 
     * 
    */
    /*確認Bond
    for(LoopNumA=0;LoopNumA < BondNO*2;LoopNumA=LoopNumA+2)
    {
        printf("%3.2f ,J=%.3lf\n",BondNOsystem[LoopNumA], BondNOsystem[LoopNumA+1]);
    }
    system("pause");
    */
    //printf("%d \n",BondNO);
    //printf("L=%d Beta=%.3f J=%.3f Q=%.3f \n",XSize,Beta,J,Q );
    
    for(LoopNumA=0;LoopNumA<T;LoopNumA++)
    {   
        //printf("Diagonal-update Begain %d test0\n",LoopNumA);
        DiaUpdateJQ3_Honeycomb(SpinSystem,BondNOsystem,Hoperator,Beta,HNO,Size,SpinNO,BondNO,HoperatorNO,BondNORecord,XSize,YSize);
        /*
        for(LoopNumB=0;LoopNumB <HoperatorNO*7;LoopNumB=LoopNumB+7)
        {   
            
            //printf("%2d ,H=%3d  ,L=%3d  ,R=%3d \n",LoopNumB/3, Hoperator[LoopNumB], Hoperator[LoopNumB+1], Hoperator[LoopNumB+2]);
            printf("   %6d ,H=   %3d   (%3d)  ,L=%3d  ,R=%3d ,L2=%3d  ,R2=%3d ,L3=%3d  ,R3=%3d\n",(long long)LoopNumB/7, Hoperator[LoopNumB],(long long)(Hoperator[LoopNumB]/15)\
             , Hoperator[LoopNumB+1], Hoperator[LoopNumB+2], Hoperator[LoopNumB+3], Hoperator[LoopNumB+4], Hoperator[LoopNumB+5], Hoperator[LoopNumB+6]);
            

            //system("pause");
        }
        */
        
      
        /*
        for(LoopNumA=0;LoopNumA <HoperatorNO*7;LoopNumA=LoopNumA+7)
        {
            //printf("%2d ,H=%3d  ,L=%3d  ,R=%3d \n",LoopNumA/3, Hoperator[LoopNumA], Hoperator[LoopNumA+1], Hoperator[LoopNumA+2]);
            printf("%2d ,H=%3d(%3d)  Dia=%3d  ,L=%3d(%2d)  ,R=%3d(%2d) ,L2=%3d(%2d)  ,R2=%3d(%2d) ,L3=%3d(%2d)  ,R3=%3d(%2d)\n",(long long )LoopNumA/7, Hoperator[LoopNumA],(long long)(Hoperator[LoopNumA]/15), Hoperator[LoopNumA]%15,\
            Hoperator[LoopNumA+1],(long long)SpinSystem[Hoperator[LoopNumA+1]*3+1], Hoperator[LoopNumA+2],(long long)SpinSystem[Hoperator[LoopNumA+2]*3+1],\
            Hoperator[LoopNumA+3],(long long)SpinSystem[Hoperator[LoopNumA+3]*3+1], Hoperator[LoopNumA+4],(long long)SpinSystem[Hoperator[LoopNumA+4]*3+1],\
            Hoperator[LoopNumA+5],(long long)SpinSystem[Hoperator[LoopNumA+5]*3+1], Hoperator[LoopNumA+6],(long long)SpinSystem[Hoperator[LoopNumA+6]*3+1]);
        }
        */
        //system("pause");
        
        //printf("Loop-update Begain %d test1\n",LoopNumA);
        LoopUpdateJQ3(SpinSystem,BondNOsystem,Hoperator,HNO,SpinNO,BondNO,HoperatorNO,TempW,BondNORecord);
      
        //printf("AddHoperatorJQ3 Begain %d test2\n",LoopNumA);
        AddHStatus=AddHoperatorJQ3(&Hoperator,HNO,HoperatorNO,LoopNumA);
        //printf("%d test3\n",LoopNumA);
    }
    
    //printf("%d %f \n",HoperatorNO-HNO,(double)((BondNO)*(BondNOsystem[600*2+1]*Beta*0.125)));
    /*確認Hoperator
    for(LoopNumA=0;LoopNumA <HoperatorNO*5;LoopNumA=LoopNumA+5)
    {
        //printf("%2d ,H=%3d  ,L=%3d  ,R=%3d \n",LoopNumA/3, Hoperator[LoopNumA], Hoperator[LoopNumA+1], Hoperator[LoopNumA+2]);
        printf("%2d ,H=%3d  ,L=%3d  ,R=%3d ,L2=%3d  ,R2=%3d\n",LoopNumA/3, Hoperator[LoopNumA], Hoperator[LoopNumA+1], Hoperator[LoopNumA+2], Hoperator[LoopNumA+3], Hoperator[LoopNumA+4]);
    }
    
    for(LoopNumA=0;LoopNumA <MeasureT/MeasureStep+1;LoopNumA=LoopNumA+1)
    {
        UsuscMent[LoopNumA]=-999;

    }
    * */
    /*
    for(LoopNumA=0;LoopNumA <HoperatorNO*7;LoopNumA=LoopNumA+7)
    {
        //printf("%2d ,H=%3d  ,L=%3d  ,R=%3d \n",LoopNumA/3, Hoperator[LoopNumA], Hoperator[LoopNumA+1], Hoperator[LoopNumA+2]);
        printf("%2d ,H=%3d  %3d,L=%3d  ,R=%3d ,L2=%3d  ,R2=%3d ,L3=%3d  ,R3=%3d\n",LoopNumA/7, Hoperator[LoopNumA], Hoperator[LoopNumA]%15, Hoperator[LoopNumA+1], Hoperator[LoopNumA+2], Hoperator[LoopNumA+3], Hoperator[LoopNumA+4], Hoperator[LoopNumA+5], Hoperator[LoopNumA+6]);
    }
    */
    EndTime=clock();
    printf("%f sec.\n",(double)(EndTime-StartTime)/CLOCKS_PER_SEC);
    //system("pause");
    //sprintf(FileName,"Size%dx%d Beta%.2lf J%.2lf SJ%.2lf.txt",XSize,YSize,Beta,J,StrongJ);
    //sprintf(FileName,"SSE-Beta%.4lf-SJ%.4lf.txt",Beta,StrongJ);//MeasnsData
    sprintf(FileNameDetail,"SSE-L%d-Beta%.2lf-Q%.4lf-Seed%ld-Detail-%d.txt",XSize,Beta,Q,SeedNum,atoi(argv[11]));//FileNameDetailData
    
    //File=fopen("SSE-Beta1.0-J1.15.txt", "w+");
    //File=fopen(FileName, "a+");
    for(LoopNumA=0;LoopNumA<(long long)(MeasureT/MeasureStep);LoopNumA++)
    {
        
        for(LoopNumB=0;LoopNumB<(long long)MeasureStep;LoopNumB++)
        {
            //printf("%d test4\n",LoopNumA);
            DiaUpdateJQ3_Honeycomb(SpinSystem,BondNOsystem,Hoperator,Beta,HNO,Size,SpinNO,BondNO,HoperatorNO,BondNORecord,XSize,YSize);
            //printf("%d test5\n",LoopNumA);
            LoopUpdateJQ3_TempW(SpinSystem,BondNOsystem,Hoperator,HNO,SpinNO,BondNO,HoperatorNO,TempW,BondNORecord);
            //printf("%d test6\n",LoopNumA);
            MeasureFuctJQ3_Honeycomb(SpinSystem, BondNOsystem, Hoperator,HNO,Size,SpinNO,BondNO,HoperatorNO\
                        ,AFM,AFM1,AFM2,AFM4,AFM6,AX1,Measure,WiddingX,WiddingY,WiddingZ,BondNORecord);
            //AddHStatus=AddHoperator(&Hoperator,HNO,HoperatorNO,LoopNumA);
            AddHStatus=AddHoperatorJQ3(&Hoperator,HNO,HoperatorNO,LoopNumA);
            //printf("%d test7\n",LoopNumA);          
        }
        //printf("%d \n",LoopNumA);
        MeasureMeans(AFM,AFM1,AFM2,AFM4,AFM6,AX1,Measure,WiddingX,WiddingY,WiddingZ,TempW,XSize,YSize,Beta,MeasureStep,SpinNO\
        ,UsuscMent[LoopNumA],AFM1Ment[LoopNumA],AFM2Ment[LoopNumA],AFM4Ment[LoopNumA]\
        ,AFM6Ment[LoopNumA],AX1Ment[LoopNumA],WindingXMent[LoopNumA],WindingYMent[LoopNumA],TempWMent[LoopNumA]);
        //printf("aaa%f \n",TempW); 
        FileDetail=fopen(FileNameDetail, "a+");
        fprintf(FileDetail,"%2d   %2d   %2.16lf    %2.16lf   %2.16lf   %d    ",XSize,YSize,Beta,J,Q,HNO);
        fprintf(FileDetail,"%2.16lf    %2.16lf    %2.16lf    %2.16lf    %2.16lf    %2.16lf    %2.16lf    %2.16lf     %2.16lf\n",\
        UsuscMent[LoopNumA],\
        AFM1Ment[LoopNumA], \
        AFM2Ment[LoopNumA], \
        AFM4Ment[LoopNumA],  \
        AFM6Ment[LoopNumA], \
        AX1Ment[LoopNumA], \
        WindingXMent[LoopNumA],\
        WindingYMent[LoopNumA],\
        TempWMent[LoopNumA]);       
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
        FileDetail=fopen(FileNameDetail, "a+");
        fprintf(FileDetail,"%2d   %2.16lf  %2.16lf   %2.16lf ",XSize,Beta,J,StrongJ);
        //fprintf(FileDetail,"%1d  ",TimesLoop);
        //fprintf(FileDetail,"%4d  ",BetaLoop);
        MeansSTD(JMent,JMeansAll,JSTDAll,JErrAll,T);
        fprintf(FileDetail,"%21.16lf  %21.16lf ",JMeansAll,JErrAll);
        MeansSTD(UsuscMent,UsuscMeansAll,UsuscSTDAll,UsuscErrAll,T);
        fprintf(FileDetail,"%21.16lf  %21.16lf ",UsuscMeansAll,UsuscErrAll);
        MeansSTD(AFM1Ment,AFM1MeansAll,AFM1STDAll,AFM1ErrAll,T);
        fprintf(FileDetail,"%21.16lf  %21.16lf ",AFM1MeansAll,AFM1ErrAll);
        MeansSTD(AFM2Ment,AFM2MeansAll,AFM2STDAll,AFM2ErrAll,T);
        fprintf(FileDetail,"%21.16lf  %21.16lf ",AFM2MeansAll,AFM2ErrAll);
        MeansSTD(AFM4Ment,AFM4MeansAll,AFM4STDAll,AFM4ErrAll,T);
        fprintf(FileDetail,"%21.16lf  %21.16lf ",AFM4MeansAll,AFM4ErrAll);
        MeansSTD(AFM6Ment,AFM6MeansAll,AFM6STDAll,AFM6ErrAll,T);
        fprintf(FileDetail,"%21.16lf  %21.16lf ",AFM6MeansAll,AFM6ErrAll);
        MeansSTD(AX1Ment,AX1MeansAll,AX1STDAll,AX1ErrAll,T);
        fprintf(FileDetail,"%21.16lf  %21.16lf \n",AX1MeansAll,AX1ErrAll);*/
        /*MeansSTD(WindingXMent,WindingXMeansAll,WindingXSTDAll,WindingXErrAll,T);
        fprintf(FileDetail,"%21.16lf  %21.16lf ",WindingXMeansAll,WindingXErrAll);
        MeansSTD(WindingYMent,WindingYMeansAll,WindingYSTDAll,WindingYErrAll,T);
        fprintf(FileDetail,"%21.16lf  %21.16lf \n",WindingYMeansAll,WindingYErrAll);*/
        fclose(FileDetail);
    }

    
    
    EndTime=clock();
    printf("%f sec.\n",(double)(EndTime-StartTime)/CLOCKS_PER_SEC);
    FileTime=fopen("Time.txt", "a+");
    //sprintf(FileNameDetail,"SSE-Beta%.4lf-SJ%.4lf-Seed%ld-Detail.txt",Beta,StrongJ,SeedNum);
    fprintf(FileTime,"%ld  %lf sec.\n",SeedNum,(double)(EndTime-StartTime)/CLOCKS_PER_SEC);
    fclose(FileTime);
    /*

    
    free(SpinSystem);
    free(Hoperator);
    free(BondNOsystem);
    free(MeasureMent);
    */
    //SpinSystem=NULL;
    //Hoperator=NULL;
    //BondNOsystem=NULL;
   // MeasureMent=NULL;
    
    printf("End %f sec.\n",(double)(EndTime-StartTime)/CLOCKS_PER_SEC);
    return 0;

}
//exmain

