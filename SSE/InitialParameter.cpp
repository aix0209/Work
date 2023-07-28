void InitialParameter(long long &XSize,long long &YSize,long long &HoperatorNO,long long &HNO,double &Beta,\
double &J,long long &T,long long &MeasureT,long long &MeasureStep,double &StrongJ)
{
    long long LoopNumA,LoopNumB,LoopNumC,check;
    //XSize=atoi(argc[1]);
    XSize=8;
    YSize=8;
    Beta=1.0;
    J=1.0;
    StrongJ=1;
    HoperatorNO=20;//#Operator初始數量(M個)
    HNO=0;
    T=50000;
    MeasureT=1000000;
    MeasureStep=2000; 
