#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

//#include <boost/random.hpp>
#include <ctime>
//using namespace std;


//boost::mt19937 rng(static_cast<unsigned int>(time(0)+getpid()*365*3600));
//boost::uniform_01<boost::mt19937> randmt(rng);
    
#define min(x,y) ( x<y?x:y )
#define prlong(x) (printf("%d \n",x))
//#include <iostream>
/*void DiaUpdate(double*,double*,double*);
void *BuildMatrix(long dim1,long dim2)
/*
 *function傳值方法
 *function(long* a, long &b)
 *main(){
 *function(a[],b)
 *}
 *
 * 
 *
 *
 *2018/05/05 之前的錯誤問題在於當Loop回到原點時不一定是結束，而有可能有Loop繼續前進
 *解決辦法是判別，當Loop回到原點時，方向要跟一開始的相反即可
 *2018/05/08 (long*)realloc(Hoperator,(NewLenth+1)*sizeof(long)); 
 *
 * */
//void DiaUpdate(long*);
//
//long Bond2Spin2D(long*,long*,long*,long*,long*);
//void AddHoperator(long*,long*);


#define NN 312
#define MM 156
#define MATRIX_A 0xB5026F5AA96619E9ULL
#define UM 0xFFFFFFFF80000000ULL /* Most significant 33 bits */
#define LM 0x7FFFFFFFULL /* Least significant 31 bits */


/* The array for the state vector */
static unsigned long long mt[NN]; 
/* mti==NN+1 means mt[NN] is not initialized */
static long mti=NN+1; 

/* initializes mt[NN] with a seed */
void init_genrand64(unsigned long long seed)
{
    mt[0] = seed;
    for (mti=1; mti<NN; mti++) 
        mt[mti] =  (6364136223846793005ULL * (mt[mti-1] ^ (mt[mti-1] >> 62)) + mti);
}

/* initialize by an array with array-length */
/* init_key is the array for initializing keys */
/* key_length is its length */
void init_by_array64(unsigned long long init_key[],
             unsigned long long key_length)
{
    unsigned long long i, j, k;
    init_genrand64(19650218ULL);
    //init_genrand64(rand());
    i=1; j=0;
    k = (NN>key_length ? NN : key_length);
    for (; k; k--) {
        mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 62)) * 3935559000370003845ULL))
          + init_key[j] + j; /* non linear */
        i++; j++;
        if (i>=NN) { mt[0] = mt[NN-1]; i=1; }
        if (j>=key_length) j=0;
    }
    for (k=NN-1; k; k--) {
        mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 62)) * 2862933555777941757ULL))
          - i; /* non linear */
        i++;
        if (i>=NN) { mt[0] = mt[NN-1]; i=1; }
    }

    mt[0] = 1ULL << 63; /* MSB is 1; assuring non-zero initial array */ 
}

/* generates a random number on [0, 2^64-1]-longerval */
unsigned long long genrand64_long64(void)
{
    long i;
    unsigned long long x;
    static unsigned long long mag01[2]={0ULL, MATRIX_A};

    if (mti >= NN) { /* generate NN words at one time */

        /* if init_genrand64() has not been called, */
        /* a default initial seed is used     */
        if (mti == NN+1) 
            init_genrand64(5489ULL); 

        for (i=0;i<NN-MM;i++) {
            x = (mt[i]&UM)|(mt[i+1]&LM);
            mt[i] = mt[i+MM] ^ (x>>1) ^ mag01[(long)(x&1ULL)];
        }
        for (;i<NN-1;i++) {
            x = (mt[i]&UM)|(mt[i+1]&LM);
            mt[i] = mt[i+(MM-NN)] ^ (x>>1) ^ mag01[(long)(x&1ULL)];
        }
        x = (mt[NN-1]&UM)|(mt[0]&LM);
        mt[NN-1] = mt[MM-1] ^ (x>>1) ^ mag01[(long)(x&1ULL)];

        mti = 0;
    }
  
    x = mt[mti++];

    x ^= (x >> 29) & 0x5555555555555555ULL;
    x ^= (x << 17) & 0x71D67FFFEDA60000ULL;
    x ^= (x << 37) & 0xFFF7EEE000000000ULL;
    x ^= (x >> 43);

    return x;
}

/* generates a random number on [0, 2^63-1]-longerval */
long long genrand64_long63(void)
{
    return (long long)(genrand64_long64() >> 1);
}

/* generates a random number on [0,1]-real-longerval */
double genrand64_real1(void)
{
    return (genrand64_long64() >> 11) * (1.0/9007199254740991.0);
}

/* generates a random number on [0,1)-real-longerval */
double genrand64_real2(void)
{
    return (genrand64_long64() >> 11) * (1.0/9007199254740992.0);
}

/* generates a random number on (0,1)-real-longerval */
double genrand64_real3(void)
{
    return ((genrand64_long64() >> 12) + 0.5) * (1.0/4503599627370496.0);
}

long long len(long long* array)//取array的大小function
{
    long long LoopNumA,LoopNumB,LoopNumC;
    LoopNumA=0;
    while (array[LoopNumA]!=-999)
    {
        LoopNumA++;
    }
    return LoopNumA;
}

long long len64(double* array)//取array的大小function
{
    long long LoopNumA,LoopNumB,LoopNumC;
    LoopNumA=0;
    while (array[LoopNumA]!=-999)
    {
        LoopNumA++;
    }
    return LoopNumA;
}
void Bond2Spin2D(long long &BondNO,long long &Size,long long &SpinNO,long long &LeftSpin,long long &RightSpin)//Bond編號轉成Spin的編號
{
    if (BondNO<SpinNO)//左右向的Bond
    {
        if(BondNO%Size!=(Size-1))
        {
            LeftSpin=BondNO;
            RightSpin=LeftSpin+1;
        }
        else
        {
            LeftSpin=BondNO;
            RightSpin=LeftSpin-Size+1;
        }
    }
    else
    {
        if(BondNO<(2*SpinNO-Size))//上下向的Spin
        {
            LeftSpin=BondNO-SpinNO;
            RightSpin=LeftSpin+Size;
        }
        else
        {
            LeftSpin=BondNO-SpinNO;
            RightSpin=LeftSpin-SpinNO+Size;
        }
    }
    
}

void Q2Bond2Bond2D(long long &BondNO,long long &Size,long long &SpinNO,long long &LeftSpin,long long &RightSpin)//Bond編號轉成Spin的編號
{
    if (BondNO<SpinNO)//左右向的QBond
    {
        if(BondNO<(SpinNO-Size))
        {
            LeftSpin=BondNO;
            RightSpin=LeftSpin+Size;
        }
        else
        {
            LeftSpin=BondNO;
            RightSpin=LeftSpin-SpinNO+Size;
        }
    }
    else//Q上下向的Spin
    {
        if(BondNO%Size!=(Size-1))
        {
            LeftSpin=BondNO;
            RightSpin=LeftSpin+1;
        }
        else
        {
            LeftSpin=BondNO;
            RightSpin=LeftSpin-Size+1;
        }
    }
    
}
//Q3編號轉成Bond的編號
void Q3Bond2Bond2D(long long &BondNO,long long &Size,long long &SpinNO,long long &Bond1,long long &Bond2,long long &Bond3)
{
    if (BondNO<SpinNO)//左右向的QBond ≡
    {
        if(BondNO<(SpinNO-Size*2))
        {
            Bond1=BondNO;
            Bond2=Bond1+Size;
            Bond3=Bond1+Size*2; 


        }
        else
        {
            
            if(BondNO>(SpinNO-Size-1))
            {
                Bond1=BondNO;
                Bond2=Bond1+Size-SpinNO;
                Bond3=Bond1+Size*2-SpinNO;   
                
            }
            else
            {
                Bond1=BondNO;
                Bond2=Bond1+Size;
                Bond3=Bond1+Size*2-SpinNO;         
            }
        }
    }
    else//Q上下向的Spin Ⅲ Size**2*2
    {
        if(BondNO%Size<(Size-2))
        {
            Bond1=BondNO;
            Bond2=Bond1+1;
            Bond3=Bond1+2;
        }
        else
        {
            if(BondNO%Size==(Size-1))
            {
                Bond1=BondNO;
                Bond2=Bond1+1-Size;
                Bond3=Bond1+2-Size;
            }
            else
            {
                Bond1=BondNO;
                Bond2=Bond1+1;
                Bond3=Bond1+2-Size;                
                
            }
        }
    }
    
}
void Q3Bond2Bond2D_1(long long &BondNO,long long &Size,long long &SpinNO,long long &Bond1,long long &Bond2,long long &Bond3)
{//斜向Bond
    if (BondNO<SpinNO*2)
    {
        if (BondNO<SpinNO)
        {
            if(BondNO<(SpinNO-Size*2))//先定左右向的QBond ≡
            {
                Bond1=BondNO;
                Bond2=Bond1+Size;
                Bond3=Bond1+Size*2; 
                
    
    
            }
            else
            {
                
                if(BondNO>(SpinNO-Size-1))
                {
                    Bond1=BondNO;
                    Bond2=Bond1+Size-SpinNO;
                    Bond3=Bond1+Size*2-SpinNO;   
                    
                }
                else
                {
                    Bond1=BondNO;
                    Bond2=Bond1+Size;
                    Bond3=Bond1+Size*2-SpinNO;         
                }
            }
            if(BondNO%Size<(Size-2))//再向右展開
            {
                Bond1=Bond1;
                Bond2=Bond2+1;
                Bond3=Bond3+2;
            }
            else
            {
                if(BondNO%Size==(Size-1))
                {
                    Bond1=Bond1;
                    Bond2=Bond2+1-Size;
                    Bond3=Bond3+2-Size;
                }
                else
                {
                    Bond1=Bond1;
                    Bond2=Bond2+1;
                    Bond3=Bond3+2-Size;                
                    
                }
            }
        }
        else//Q上下向的Spin Ⅲ Size**2*2
        {
            if(BondNO%Size<(Size-2))//先左右展開
            {
                Bond1=BondNO;
                Bond2=Bond1+1;
                Bond3=Bond1+2;
            }
            else
            {
                if(BondNO%Size==(Size-1))
                {
                    Bond1=BondNO;
                    Bond2=Bond1+1-Size;
                    Bond3=Bond1+2-Size;
                }
                else
                {
                    Bond1=BondNO;
                    Bond2=Bond1+1;
                    Bond3=Bond1+2-Size;                
                    
                }
            }
            if(BondNO<(SpinNO*2-Size*2))//再向上展開
            {
                Bond1=Bond1;
                Bond2=Bond2+Size;
                Bond3=Bond3+Size*2; 
    
    
            }
            else
            {
                
                if(BondNO>(SpinNO*2-Size-1))
                {
                    Bond1=Bond1;
                    Bond2=Bond2+Size-SpinNO;
                    Bond3=Bond3+Size*2-SpinNO;   
                    
                }
                else
                {
                    Bond1=Bond1;
                    Bond2=Bond2+Size;
                    Bond3=Bond3+Size*2-SpinNO;         
                }
            }
            //printf("%d %d %d %d \n",BondNO,Bond1,Bond2,Bond3);
        }
    }
    else
    {
        //printf("1.%d \n" ,BondNO);
        BondNO=BondNO-SpinNO*2;
        //printf("2.%d \n" ,BondNO);
        if (BondNO<SpinNO)
        {
            if(BondNO<(SpinNO-Size*2))//先定左右向的QBond ≡
            {
                Bond1=BondNO;
                Bond2=Bond1+Size;
                Bond3=Bond1+Size*2; 
                
    
    
            }
            else
            {
                
                if(BondNO>(SpinNO-Size-1))
                {
                    Bond1=BondNO;
                    Bond2=Bond1+Size-SpinNO;
                    Bond3=Bond1+Size*2-SpinNO;   
                    
                }
                else
                {
                    Bond1=BondNO;
                    Bond2=Bond1+Size;
                    Bond3=Bond1+Size*2-SpinNO;         
                }
            }
            if(BondNO%Size>1)//再向左展開
            {
                Bond1=Bond1;
                Bond2=Bond2-1;
                Bond3=Bond3-2;
            }
            else
            {
                if(BondNO%Size==0)
                {
                    Bond1=Bond1;
                    Bond2=Bond2-1+Size;
                    Bond3=Bond3-2+Size;
                }
                else
                {
                    Bond1=Bond1;
                    Bond2=Bond2-1;
                    Bond3=Bond3-2+Size;                
                    
                }
            }
            //printf("%d %d %d \n",Bond1,Bond2,Bond3);
        }
        else//Q上下向的Spin Ⅲ Size**2*2
        {
            if(BondNO%Size>1)//先左展開
            {
                Bond1=BondNO;
                Bond2=Bond1-1;
                Bond3=Bond1-2;
            }
            else
            {
                if(BondNO%Size==0)
                {
                    Bond1=BondNO;
                    Bond2=Bond1-1+Size;
                    Bond3=Bond1-2+Size;
                }
                else
                {
                    Bond1=BondNO;
                    Bond2=Bond1-1;
                    Bond3=Bond1-2+Size;                
                    
                }
            }
            if(BondNO<(SpinNO*2-Size*2))//再向上展開
            {
                Bond1=Bond1;
                Bond2=Bond2+Size;
                Bond3=Bond3+Size*2; 
    
    
            }
            else
            {
                
                if(BondNO>(SpinNO*2-Size-1))
                {
                    Bond1=Bond1;
                    Bond2=Bond2+Size-SpinNO;
                    Bond3=Bond3+Size*2-SpinNO;   
                    
                }
                else
                {
                    Bond1=Bond1;
                    Bond2=Bond2+Size;
                    Bond3=Bond3+Size*2-SpinNO;         
                }
            }
            //printf("%d %d %d %d \n",BondNO,Bond1,Bond2,Bond3);
        }
    }
}
void Q3Bond2Bond2D_prove(long long &BondNO,long long &Size,long long &SpinNO,long long &Bond1,long long &Bond2,long long &Bond3)
{//斜向Bond
    long long QETypeR,QETypeL,QMTypeR,QMTypeL;
    //printf("In Q3Bond2Bond2D_1 BondNO=%d \n",BondNO);
    QETypeR = SpinNO;
    QMTypeR = SpinNO*2;
    QETypeL = SpinNO*3;
    QMTypeL = SpinNO*4;    
    if (BondNO<QMTypeR)//向右上展開
    {
        if (BondNO<QETypeR)
        {
            //三字左右向的QBond ≡，向上展開
            Bond1=BondNO;
            Bond2=Bond1+Size;
            Bond3=Bond1+Size*2;
            if(Bond2>=QETypeR)
            {
                Bond2=Bond2%SpinNO;
                Bond3=Bond3%SpinNO;
            }
            else if (Bond3>=SpinNO)
            {
                Bond3=Bond3%SpinNO; 
            }
            //三字左右向的QBond ≡，向右展開
            Bond2+=1;
            Bond3+=2;
            if(Bond2%Size==0)
            {
                Bond2=((long long )(Bond2/Size)-1)*Size+Bond2%Size;
                Bond3=((long long )(Bond3/Size)-1)*Size+Bond3%Size;
            }
            else if (Bond3%Size==0)
            {
                Bond3=((long long )(Bond3/Size)-1)*Size+Bond3%Size;
            }
        }
        else//Q上下向的Spin Ⅲ Size**2*2
        {
            //川字左右向的QBond |||，向上展開
            Bond1=BondNO;
            Bond2=Bond1+Size;
            Bond3=Bond1+Size*2; 
            if(Bond2>=QMTypeR)
            {
                Bond2=Bond2%SpinNO+QETypeR;
                Bond3=Bond3%SpinNO+QETypeR;
            }
            else if (Bond3>=QMTypeR)
            {
                Bond3=Bond3%SpinNO+QETypeR; 
            }
            //川字左右向的QBond ≡，向右展開
            Bond2+=1;
            Bond3+=2;
            if(Bond2%Size==0)
            {
                Bond2=((long long )(Bond2/Size)-1)*Size+Bond2%Size;
                Bond3=((long long )(Bond3/Size)-1)*Size+Bond3%Size;
            }
            else if (Bond3%Size==0)
            {
                Bond3=((long long )(Bond3/Size)-1)*Size+Bond3%Size;
            }           

            //printf("%d %d %d %d \n",BondNO,Bond1,Bond2,Bond3);
        }
    }
    else//向左上展開
    {
        //printf("1.%d \n" ,BondNO);
        //BondNO=BondNO-SpinNO*2;
        //printf("2.%d \n" ,BondNO);
        if (BondNO<QETypeL)
        {
            //三字左右向的QBond ≡，向上展開
            Bond1=BondNO-QMTypeR;
            Bond2=Bond1+Size;
            Bond3=Bond1+Size*2;
            ///printf("%d %d %d \n",Bond1,Bond2,Bond3);
            if(Bond2>=QETypeR)
            {
                Bond2=Bond2%SpinNO;
                Bond3=Bond3%SpinNO;
            }
            else if (Bond3>=QETypeR)
            {
                Bond3=Bond3%SpinNO; 
            }
            //printf("%d %d %d \n",Bond1,Bond2,Bond3);
            //三字左右向的QBond ≡，向左展開
            Bond2-=1;
            Bond3-=2;
            //printf("%d %d %d \n",Bond1,Bond2,Bond3);
            if(Bond2%Size==Size-1 or Bond2<0)
            {
                Bond2=((long long )(Bond2/Size)+1)*Size+Bond2%Size;
                Bond3=((long long )(Bond3/Size)+1)*Size+Bond3%Size;
            }
            else if (Bond3%Size==Size-1 or Bond3<0)
            {
                Bond3=((long long )(Bond3/Size)+1)*Size+Bond3%Size;
            }
            //printf("%d %d %d \n",Bond1,Bond2,Bond3);
        }
        else//Q上下向的Spin Ⅲ Size**2*2
        {
            //川字左右向的QBond 向上展開
            Bond1=BondNO-QMTypeR;
            Bond2=Bond1+Size;
            Bond3=Bond1+Size*2;
            ///printf("%d %d %d \n",Bond1,Bond2,Bond3); 
            if(Bond2>=QMTypeR)
            {
                Bond2=Bond2%SpinNO+QETypeR;
                Bond3=Bond3%SpinNO+QETypeR;
            }
            else if (Bond3>=QMTypeR)
            {
                Bond3=Bond3%SpinNO+QETypeR; 
            }
            //printf("%d %d %d \n",Bond1,Bond2,Bond3);
            //川字左右向的QBond ≡，向左展開
            Bond2-=1;
            Bond3-=2;
            ///printf("%d %d %d \n",Bond1,Bond2,Bond3);
            if(Bond2%Size==Size-1)
            {
                Bond2=((long long )(Bond2/Size)+1)*Size+Bond2%Size;
                Bond3=((long long )(Bond3/Size)+1)*Size+Bond3%Size;
            }
            else if (Bond3%Size==Size-1)
            {
                Bond3=((long long )(Bond3/Size)+1)*Size+Bond3%Size;
            }           
            //printf("%d %d %d \n",Bond1,Bond2,Bond3);
            //printf("%d %d %d %d \n",BondNO,Bond1,Bond2,Bond3);
        }        

    }
}
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
            if(genrand64_real2()*(double)(HoperatorNO-HNO)<(double)((BondNO)*(BondNOsystem[BondNumber*2+1]*Beta*0.5)))
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
void DiaUpdateJQ3_test(double* SpinSystem,double* BondNOsystem,long long* Hoperator\
          ,double &Beta,long long &HNO,long long &Size,long long &SpinNO,long long &BondNO,long long &HoperatorNO)
{
   long long LoopNumA,LoopNumB,LoopNumC;
   long long RdNO;
   long long BondNumber,BondNumbertemp;
   long long LeftSpin,RightSpin,LeftSpin2,RightSpin2,LeftSpin3,RightSpin3,LeftBond,RightBond,Bond1,Bond2,Bond3;
   long long SpinSystemSize,BondNOsystemSize;
   double Chance,Goal;
   
   SpinSystemSize=SpinNO;
   for(LoopNumA=0;LoopNumA <HoperatorNO*7;LoopNumA=LoopNumA+7)
    {
        //printf("LoopNumA=%d HoperatorNO=%d \n",LoopNumA,HoperatorNO*7);
        //printf("%d test DiaUpdateJQ3-a\n",LoopNumA);
        if(Hoperator[LoopNumA]==-1)//該Hoperator 為空
        {
            
            BondNumber=(long long)(BondNO*genrand64_real2());
            //printf("%d test DiaUpdateJQ3-a %d \n",LoopNumA,BondNumber);
            if (BondNumber<(long long)(BondNO*0.5))//J Bond
            {
                //printf("HoperatorNO-HNO=%d  %f\n",HoperatorNO-HNO, (double)((BondNO)*(BondNOsystem[BondNumber*2+1]*Beta*0.5)));
                //printf("%d test DiaUpdateJQ3-a-1 J Bond %d \n",LoopNumA,BondNumber);
                if(genrand64_real2()*(double)(HoperatorNO-HNO)<(double)((BondNO)*(BondNOsystem[BondNumber*2+1]*Beta*0.5)))
                {
                   Bond2Spin2D(BondNumber,Size,SpinNO,LeftSpin,RightSpin);
                   if(SpinSystem[LeftSpin*3+1]==SpinSystem[RightSpin*3+1]*(-1))
                   {
                       Hoperator[LoopNumA]=BondNumber*15;
                       Hoperator[LoopNumA+1]=LeftSpin;
                       Hoperator[LoopNumA+2]=RightSpin;
                       Hoperator[LoopNumA+3]=-1;
                       Hoperator[LoopNumA+4]=-1;
                       Hoperator[LoopNumA+5]=-1;
                       Hoperator[LoopNumA+6]=-1;                      
                       HNO+=1;
                    }
                }
                
            }
            else//Q3 Bond
            {
                //printf("HoperatorNO-HNO=%d  %f\n",HoperatorNO-HNO, (double)((BondNO)*(BondNOsystem[BondNumber*2+1]*Beta*0.125)));
                if(genrand64_real2()*(double)(HoperatorNO-HNO)<(double)((BondNO)*(BondNOsystem[BondNumber*2+1]*Beta*0.125)))
                {
                   //printf("Y-HoperatorNO-HNO=%d  %f\n",HoperatorNO-HNO, (double)((BondNO)*(BondNOsystem[BondNumber*2+1]*Beta*0.125)));
                   BondNumbertemp=BondNumber-(long long)(BondNO*0.5);
                   Q3Bond2Bond2D(BondNumbertemp,Size,SpinNO,Bond1,Bond2,Bond3);
                   //printf("LeftBond=%d RightBond=%d \n",LeftBond,RightBond);
                   Bond2Spin2D(Bond1,Size,SpinNO,LeftSpin,RightSpin);             
                   Bond2Spin2D(Bond2,Size,SpinNO,LeftSpin2,RightSpin2);
                   Bond2Spin2D(Bond3,Size,SpinNO,LeftSpin3,RightSpin3);
                   //printf("LeftSpin=%d RightSpin=%d LeftSpin2=%d RightSpin2=%d \n",LeftSpin,RightSpin,LeftSpin2,RightSpin2);
                   if(SpinSystem[LeftSpin*3+1]==SpinSystem[RightSpin*3+1]*(-1) and \
                   SpinSystem[LeftSpin2*3+1]==SpinSystem[RightSpin2*3+1]*(-1) and \
                   SpinSystem[LeftSpin3*3+1]==SpinSystem[RightSpin3*3+1]*(-1))
                   {
                       Hoperator[LoopNumA]=BondNumber*15+2;//*13 bond碼編號
                       Hoperator[LoopNumA+1]=LeftSpin;
                       Hoperator[LoopNumA+2]=RightSpin;
                       Hoperator[LoopNumA+3]=LeftSpin2;
                       Hoperator[LoopNumA+4]=RightSpin2;
                       Hoperator[LoopNumA+5]=LeftSpin3;
                       Hoperator[LoopNumA+6]=RightSpin3;
                       HNO+=1;
                    }
                }                
                
            }

        }
        else//該Hoperator非空
        {
            switch(Hoperator[LoopNumA]%15)
            {
                case 0:
                    if(genrand64_real2()*((double)((BondNO)*(BondNOsystem[(long long)(Hoperator[LoopNumA]/15*2)+1]*Beta*0.5)))<(double)(HoperatorNO-HNO+1))
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
                    if(genrand64_real2()*((double)((BondNO)*(BondNOsystem[(long long)((Hoperator[LoopNumA]-2)/15*2)+1]*Beta*0.125)))<(double)(HoperatorNO-HNO+1))
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
void DiaUpdateJQ3(double* SpinSystem,double* BondNOsystem,long long* Hoperator\
          ,double &Beta,long long &HNO,long long &Size,long long &SpinNO,long long &BondNO,long long &HoperatorNO,long long* BondNORecord)
{
   long long LoopNumA,LoopNumB,LoopNumC;
   long long RdNO;
   long long BondNumber,BondNumbertemp,BondNumberIndex;
   long long LeftSpin,RightSpin,LeftSpin2,RightSpin2,LeftSpin3,RightSpin3,LeftBond,RightBond,Bond1,Bond2,Bond3;
   long long SpinSystemSize,BondNOsystemSize;
   double Chance,Goal;
   
   SpinSystemSize=SpinNO;
   for(LoopNumA=0;LoopNumA <HoperatorNO*7;LoopNumA=LoopNumA+7)
    {
        //printf("LoopNumA=%d HoperatorNO=%d \n",LoopNumA,HoperatorNO*7);
        //printf("%d test DiaUpdateJQ3-a\n",LoopNumA);
        if(Hoperator[LoopNumA]==-1)//該Hoperator 為空
        {
            
            //BondNumber=(long long)(BondNO*genrand64_real2());
            
            
            BondNumber=(long long)(BondNO*genrand64_real2());
            BondNumberIndex=BondNumber*6;
            //printf("%d test DiaUpdateJQ3-a %d \n",LoopNumA,BondNumber);
            if (BondNumber<(long long)(BondNO*0.5))//J Bond
            {
                //printf("HoperatorNO-HNO=%d  %f\n",HoperatorNO-HNO, (double)((BondNO)*(BondNOsystem[BondNumber*2+1]*Beta*0.5)));
                //printf("%d test DiaUpdateJQ3-a-1 J Bond %d \n",LoopNumA,BondNumber);
                if(genrand64_real2()*(double)(HoperatorNO-HNO)<(double)((BondNO)*(BondNOsystem[BondNumber*2+1]*Beta*0.5)))
                {
                   Bond2Spin2D(BondNumber,Size,SpinNO,LeftSpin,RightSpin);
                   if(SpinSystem[LeftSpin*3+1]==SpinSystem[RightSpin*3+1]*(-1))
                   {
                       Hoperator[LoopNumA]=BondNumber*15;
                       Hoperator[LoopNumA+1]=LeftSpin;
                       Hoperator[LoopNumA+2]=RightSpin;
                       Hoperator[LoopNumA+3]=-1;
                       Hoperator[LoopNumA+4]=-1;
                       Hoperator[LoopNumA+5]=-1;
                       Hoperator[LoopNumA+6]=-1;                      
                       HNO+=1;
                    }
                }
                
            }
            else//Q3 Bond
            {
                //printf("HoperatorNO-HNO=%d  %f\n",HoperatorNO-HNO, (double)((BondNO)*(BondNOsystem[BondNumber*2+1]*Beta*0.125)));
                if(genrand64_real2()*(double)(HoperatorNO-HNO)<(double)((BondNO)*(BondNOsystem[BondNumber*2+1]*Beta*0.125)))
                {
                   //printf("Y-HoperatorNO-HNO=%d  %f\n",HoperatorNO-HNO, (double)((BondNO)*(BondNOsystem[BondNumber*2+1]*Beta*0.125)));
                   BondNumbertemp=BondNumber-(long long)(BondNO*0.5);
                   Q3Bond2Bond2D(BondNumbertemp,Size,SpinNO,Bond1,Bond2,Bond3);
                   //printf("LeftBond=%d RightBond=%d \n",LeftBond,RightBond);
                   Bond2Spin2D(Bond1,Size,SpinNO,LeftSpin,RightSpin);             
                   Bond2Spin2D(Bond2,Size,SpinNO,LeftSpin2,RightSpin2);
                   Bond2Spin2D(Bond3,Size,SpinNO,LeftSpin3,RightSpin3);
                   printf("%d  LeftSpin=%d  RightSpin=%d  LeftSpin2=%d  RightSpin2=%d LeftSpin3=%d  RightSpin3=%d  \n",BondNumber,LeftSpin,RightSpin,LeftSpin2,RightSpin2,LeftSpin3,RightSpin3);
                   printf("%d  Table LeftSpin=%d  RightSpin=%d  LeftSpin2=%d  RightSpin2=%d LeftSpin3=%d  RightSpin3=%d  \n",BondNumber,BondNORecord[BondNumberIndex],BondNORecord[BondNumberIndex+1],BondNORecord[BondNumberIndex+2],BondNORecord[BondNumberIndex+3],BondNORecord[BondNumberIndex+4],BondNORecord[BondNumberIndex+5]);
                   if(SpinSystem[LeftSpin*3+1]==SpinSystem[RightSpin*3+1]*(-1) and \
                   SpinSystem[LeftSpin2*3+1]==SpinSystem[RightSpin2*3+1]*(-1) and \
                   SpinSystem[LeftSpin3*3+1]==SpinSystem[RightSpin3*3+1]*(-1))
                   {
                       Hoperator[LoopNumA]=BondNumber*15+2;//*13 bond碼編號
                       Hoperator[LoopNumA+1]=LeftSpin;
                       Hoperator[LoopNumA+2]=RightSpin;
                       Hoperator[LoopNumA+3]=LeftSpin2;
                       Hoperator[LoopNumA+4]=RightSpin2;
                       Hoperator[LoopNumA+5]=LeftSpin3;
                       Hoperator[LoopNumA+6]=RightSpin3;
                       HNO+=1;
                    }
                }                
                
            }
            /*
            //printf("%d test DiaUpdateJQ3-a %d \n",LoopNumA,BondNumber);
            if (BondNumber<(long long)(BondNO*0.5))//J Bond
            {
                //printf("HoperatorNO-HNO=%d  %f\n",HoperatorNO-HNO, (double)((BondNO)*(BondNOsystem[BondNumber*2+1]*Beta*0.5)));
                //printf("%d test DiaUpdateJQ3-a-1 J Bond %d \n",LoopNumA,BondNumber);
                if(genrand64_real2()*(double)(HoperatorNO-HNO)<(double)((BondNO)*(BondNOsystem[BondNumber*2+1]*Beta*0.5)))
                {
                   //Bond2Spin2D(BondNumber,Size,SpinNO,LeftSpin,RightSpin);
                   
                   if(SpinSystem[BondNORecord[BondNumberIndex]*3+1]==SpinSystem[BondNORecord[BondNumberIndex+1]*3+1]*(-1))
                   {
                       Hoperator[LoopNumA]=BondNumber*15;
                       Hoperator[LoopNumA+1]=BondNORecord[BondNumberIndex];
                       Hoperator[LoopNumA+2]=BondNORecord[BondNumberIndex+1];
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
                if(genrand64_real2()*(double)(HoperatorNO-HNO)<(double)((BondNO)*(BondNOsystem[BondNumber*2+1]*Beta*0.125)))
                {
                   //printf("Y-HoperatorNO-HNO=%d  %f\n",HoperatorNO-HNO, (double)((BondNO)*(BondNOsystem[BondNumber*2+1]*Beta*0.125)));
                   //BondNumbertemp=BondNumber-(long long)(BondNO*0.5);
                   //Q3Bond2Bond2D(BondNumbertemp,Size,SpinNO,Bond1,Bond2,Bond3);
                   //printf("LeftBond=%d RightBond=%d \n",LeftBond,RightBond);
                   //Bond2Spin2D(Bond1,Size,SpinNO,LeftSpin,RightSpin);             
                   //Bond2Spin2D(Bond2,Size,SpinNO,LeftSpin2,RightSpin2);
                   //Bond2Spin2D(Bond3,Size,SpinNO,LeftSpin3,RightSpin3);
                   //printf("LeftSpin=%d RightSpin=%d LeftSpin2=%d RightSpin2=%d \n",LeftSpin,RightSpin,LeftSpin2,RightSpin2);
                   if(SpinSystem[BondNORecord[BondNumberIndex]*3+1]==SpinSystem[BondNORecord[BondNumberIndex+1]*3+1]*(-1) and \
                   SpinSystem[BondNORecord[BondNumberIndex+2]*3+1]==SpinSystem[BondNORecord[BondNumberIndex+3]*3+1]*(-1) and \
                   SpinSystem[BondNORecord[BondNumberIndex+4]*3+1]==SpinSystem[BondNORecord[BondNumberIndex+5]*3+1]*(-1))
                   {
                       Hoperator[LoopNumA]=BondNumber*15+2;//*13 bond碼編號
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
            */
            

        }
        else//該Hoperator非空
        {
            switch(Hoperator[LoopNumA]%15)
            {
                case 0:
                    if(genrand64_real2()*((double)((BondNO)*(BondNOsystem[(long long)(Hoperator[LoopNumA]/15*2)+1]*Beta*0.5)))<(double)(HoperatorNO-HNO+1))
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
                    if(genrand64_real2()*((double)((BondNO)*(BondNOsystem[(long long)((Hoperator[LoopNumA]-2)/15*2)+1]*Beta*0.125)))<(double)(HoperatorNO-HNO+1))
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
void DiaUpdateJQ3_1(double* SpinSystem,double* BondNOsystem,long long* Hoperator\
          ,double &Beta,long long &HNO,long long &Size,long long &SpinNO,long long &BondNO,long long &HoperatorNO,long long* BondNORecord)
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
            
            BondNumber=(long long)(BondNO*genrand64_real2());
            BondNumberIndex=BondNumber*6;
            //printf("BondNumber=%d LeftSpin=%d RightSpin=%d LeftSpin2=%d RightSpin2=%d LeftSpin3=%d RightSpin3=%d \n",BondNumber,BondNORecord[BondNumber*6],BondNORecord[BondNumber*6+1],BondNORecord[BondNumber*6+2],BondNORecord[BondNumber*6+3],BondNORecord[BondNumber*6+3],BondNORecord[BondNumber*6+4],BondNORecord[BondNumber*6+5]);
            //printf("%d test DiaUpdateJQ3-a %d \n",LoopNumA,BondNumber);
            if (BondNumber<(long long)(SpinNO*2))//J Bond
            {
                //printf("HoperatorNO-HNO=%d  %f\n",HoperatorNO-HNO, (double)((BondNO)*(BondNOsystem[BondNumber*2+1]*Beta*0.5)));
                //printf("%d test DiaUpdateJQ3-a-1 J Bond %d \n",LoopNumA,BondNumber);
                if(genrand64_real2()*(double)(HoperatorNO-HNO)<(double)((BondNO)*(BondNOsystem[BondNumber*2+1]*Beta*0.5)))
                {
                   //Bond2Spin2D(BondNumber,Size,SpinNO,LeftSpin,RightSpin);
                   
                   if(SpinSystem[BondNORecord[BondNumberIndex]*3+1]==SpinSystem[BondNORecord[BondNumberIndex+1]*3+1]*(-1))
                   {
                       Hoperator[LoopNumA]=BondNumber*15;
                       Hoperator[LoopNumA+1]=BondNORecord[BondNumberIndex];
                       Hoperator[LoopNumA+2]=BondNORecord[BondNumberIndex+1];
                       Hoperator[LoopNumA+3]=-1;
                       Hoperator[LoopNumA+4]=-1;
                       Hoperator[LoopNumA+5]=-1;
                       Hoperator[LoopNumA+6]=-1; 
                       HNO+=1;
                    }
                }
                
            }
            else//Q3 Bond
            {
                //printf("HoperatorNO-HNO=%d  %f\n",HoperatorNO-HNO, (double)((BondNO)*(BondNOsystem[BondNumber*2+1]*Beta*0.125)));
                if(genrand64_real2()*(double)(HoperatorNO-HNO)<(double)((BondNO)*(BondNOsystem[BondNumber*2+1]*Beta*0.125)))
                {
                   //printf("Y-HoperatorNO-HNO=%d  %f\n",HoperatorNO-HNO, (double)((BondNO)*(BondNOsystem[BondNumber*2+1]*Beta*0.125)));
                   //BondNumbertemp=BondNumber-(long long)(BondNO*0.5);
                   //Q3Bond2Bond2D(BondNumbertemp,Size,SpinNO,Bond1,Bond2,Bond3);
                   //printf("LeftBond=%d RightBond=%d \n",LeftBond,RightBond);
                   //Bond2Spin2D(Bond1,Size,SpinNO,LeftSpin,RightSpin);             
                   //Bond2Spin2D(Bond2,Size,SpinNO,LeftSpin2,RightSpin2);
                   //Bond2Spin2D(Bond3,Size,SpinNO,LeftSpin3,RightSpin3);
                   

                   if(SpinSystem[BondNORecord[BondNumberIndex]*3+1]==SpinSystem[BondNORecord[BondNumberIndex+1]*3+1]*(-1) and \
                   SpinSystem[BondNORecord[BondNumberIndex+2]*3+1]==SpinSystem[BondNORecord[BondNumberIndex+3]*3+1]*(-1) and \
                   SpinSystem[BondNORecord[BondNumberIndex+4]*3+1]==SpinSystem[BondNORecord[BondNumberIndex+5]*3+1]*(-1))
                   {
                       Hoperator[LoopNumA]=BondNumber*15+2;//*13 bond碼編號
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
            switch(Hoperator[LoopNumA]%15)
            {
                case 0:
                    if(genrand64_real2()*((double)((BondNO)*(BondNOsystem[(long long)(Hoperator[LoopNumA]/15*2)+1]*Beta*0.5)))<(double)(HoperatorNO-HNO+1))
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
                    if(genrand64_real2()*((double)((BondNO)*(BondNOsystem[(long long)((Hoperator[LoopNumA]-2)/15*2)+1]*Beta*0.125)))<(double)(HoperatorNO-HNO+1))
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

void DiaUpdateJQ3_Spin1(double* SpinSystem,double* BondNOsystem,long long* Hoperator\
          ,double &Beta,long long &HNO,long long &Size,long long &SpinNO,long long &BondNO,long long &HoperatorNO,long long* BondNORecord)
{
//最後一Spin為Ferromagnetic    
   long long LoopNumA,LoopNumB,LoopNumC;
   long long RdNO;
   long long BondNumber,BondNumbertemp,BondNumberIndex;
   long long LeftSpin,RightSpin,LeftSpin2,RightSpin2,LeftSpin3,RightSpin3,LeftBond,RightBond,Bond1,Bond2,Bond3;
   long long SpinSystemSize,BondNOsystemSize,SwitchNO,Check;
   double Chance,Goal;
   
   //SpinSystemSize=SpinNO;
   for(LoopNumA=0;LoopNumA <HoperatorNO*7;LoopNumA=LoopNumA+7)
    {
        //printf("LoopNumA=%d HoperatorNO=%d \n",LoopNumA,HoperatorNO*7);
        //printf("%d test DiaUpdateJQ3-a\n",LoopNumA);
        if(Hoperator[LoopNumA]==-1)//該Hoperator 為空
        {
            
            BondNumber=(long long)(BondNO*genrand64_real2());
            BondNumberIndex=BondNumber*7;
            //printf("BondNumber=%4d BondType=%2d LeftSpin=%3d RightSpin=%3d LeftSpin2=%3d RightSpin2=%3d LeftSpin3=%3d RightSpin3=%3d \n",BondNumber,BondNORecord[BondNumberIndex],BondNORecord[BondNumberIndex+1],BondNORecord[BondNumberIndex+2],BondNORecord[BondNumberIndex+3],BondNORecord[BondNumberIndex+4],BondNORecord[BondNumberIndex+5],BondNORecord[BondNumberIndex+6]);
            //printf("%d test DiaUpdateJQ3-a %d \n",LoopNumA,BondNumber);
            if (BondNumber<(long long)(SpinNO*2))//J Bond
            {
                //printf("HoperatorNO-HNO=%d  %f\n",HoperatorNO-HNO, (double)((BondNO)*(BondNOsystem[BondNumber*2+1]*Beta*0.5)));
                //printf("%d test DiaUpdateJQ3-a-1 J Bond %d \n",LoopNumA,BondNumber);
                if(genrand64_real2()*(double)(HoperatorNO-HNO)<(double)((BondNO)*(BondNOsystem[BondNumber*2+1]*Beta*0.5)))
                {
                   //Bond2Spin2D(BondNumber,Size,SpinNO,LeftSpin,RightSpin);
                   if(BondNORecord[BondNumberIndex]==-1)
                   {
                       if(SpinSystem[BondNORecord[BondNumberIndex+2]*3+1]==SpinSystem[BondNORecord[BondNumberIndex+1]*3+1]*(-1))
                       {
                           //printf("J Bond %d %d \n",SpinSystem[BondNORecord[BondNumberIndex+2]*3+1],SpinSystem[BondNORecord[BondNumberIndex+1]*3+1]);
                           Hoperator[LoopNumA]=BondNumber*15;
                           Hoperator[LoopNumA+1]=BondNORecord[BondNumberIndex+1];
                           Hoperator[LoopNumA+2]=BondNORecord[BondNumberIndex+2];
                           Hoperator[LoopNumA+3]=-1;
                           Hoperator[LoopNumA+4]=-1;
                           Hoperator[LoopNumA+5]=-1;
                           Hoperator[LoopNumA+6]=-1; 
                           HNO+=1;
                        }   
                   }
                   else
                   {
                       if(SpinSystem[BondNORecord[BondNumberIndex+2]*3+1]==SpinSystem[BondNORecord[BondNumberIndex+1]*3+1])
                       {
                           ///printf("J BondType %d  %d \n",BondNORecord[BondNumberIndex],BondNumber);
                           //printf("J Bond %f %f \n",SpinSystem[BondNORecord[BondNumberIndex+2]*3+1],SpinSystem[BondNORecord[BondNumberIndex+1]*3+1]);
                           Hoperator[LoopNumA]=BondNumber*15;
                           Hoperator[LoopNumA+1]=BondNORecord[BondNumberIndex+1];
                           Hoperator[LoopNumA+2]=BondNORecord[BondNumberIndex+2];
                           Hoperator[LoopNumA+3]=-1;
                           Hoperator[LoopNumA+4]=-1;
                           Hoperator[LoopNumA+5]=-1;
                           Hoperator[LoopNumA+6]=-1; 
                           HNO+=1;
                        }                       
                       
                   }
                   
                   

                }
                
            }
            else//Q3 Bond
            {
                //printf("HoperatorNO-HNO=%d  %f\n",HoperatorNO-HNO, (double)((BondNO)*(BondNOsystem[BondNumber*2+1]*Beta*0.125)));
                if(genrand64_real2()*(double)(HoperatorNO-HNO)<(double)((BondNO)*(BondNOsystem[BondNumber*2+1]*Beta*0.125)))
                {
                   //printf("Y-HoperatorNO-HNO=%d  %f\n",HoperatorNO-HNO, (double)((BondNO)*(BondNOsystem[BondNumber*2+1]*Beta*0.125)));
                   BondNumbertemp=BondNumber-(long long)(BondNO*0.5);
                    Q3Bond2Bond2D(BondNumbertemp,Size,SpinNO,Bond1,Bond2,Bond3);
                   //printf("LeftBond=%d RightBond=%d \n",LeftBond,RightBond);
                   Bond2Spin2D(Bond1,Size,SpinNO,LeftSpin,RightSpin);             
                   Bond2Spin2D(Bond2,Size,SpinNO,LeftSpin2,RightSpin2);
                   Bond2Spin2D(Bond3,Size,SpinNO,LeftSpin3,RightSpin3);
                   
                    if(BondNORecord[BondNumberIndex]==-1)
                    {

                       if(SpinSystem[BondNORecord[BondNumberIndex+1]*3+1]==SpinSystem[BondNORecord[BondNumberIndex+2]*3+1]*(-1) and \
                       SpinSystem[BondNORecord[BondNumberIndex+4]*3+1]==SpinSystem[BondNORecord[BondNumberIndex+3]*3+1]*(-1) and \
                       SpinSystem[BondNORecord[BondNumberIndex+6]*3+1]==SpinSystem[BondNORecord[BondNumberIndex+5]*3+1]*(-1))
                       {
                           Hoperator[LoopNumA]=BondNumber*15+2;//*13 bond碼編號
                           Hoperator[LoopNumA+1]=BondNORecord[BondNumberIndex+1];
                           Hoperator[LoopNumA+2]=BondNORecord[BondNumberIndex+2];
                           Hoperator[LoopNumA+3]=BondNORecord[BondNumberIndex+3];
                           Hoperator[LoopNumA+4]=BondNORecord[BondNumberIndex+4];
                           Hoperator[LoopNumA+5]=BondNORecord[BondNumberIndex+5];
                           Hoperator[LoopNumA+6]=BondNORecord[BondNumberIndex+6];
                           HNO+=1;
                        }
                    }
                    else
                    {
                       Check = 1;
                       for(LoopNumB = 0; LoopNumB < 3 ; LoopNumB+=1 )
                       {
                         if(LoopNumB!= BondNORecord[BondNumberIndex]-1)
                         {
                            if(SpinSystem[BondNORecord[BondNumberIndex+LoopNumB*2+1]*3+1]!=SpinSystem[BondNORecord[BondNumberIndex+LoopNumB*2+2]*3+1]*(-1))
                            {
                                Check = 0;
                                //printf("Anti %.1f %.1f \n",SpinSystem[BondNORecord[BondNumberIndex+LoopNumB*2+1]*3+1],SpinSystem[BondNORecord[BondNumberIndex+LoopNumB*2+2]*3+1]);
                                break;
                            } 
                         }
                         else
                         {
                            if(SpinSystem[BondNORecord[BondNumberIndex+LoopNumB*2+1]*3+1]!=SpinSystem[BondNORecord[BondNumberIndex+LoopNumB*2+2]*3+1])
                            {
                                //printf("Ferro %.1f %.1f \n",SpinSystem[BondNORecord[BondNumberIndex+LoopNumB*2+1]*3+1],SpinSystem[BondNORecord[BondNumberIndex+LoopNumB*2+2]*3+1]);
                                Check = 0;
                                break;
                            } 
                         }  
                       
                       }
                       if(Check==1)
                       {
                           //printf("Q BondType %d  %d \n",BondNORecord[BondNumberIndex],BondNumber);
                           //printf("Q Bond %f %f \n",SpinSystem[BondNORecord[BondNumberIndex+2]*3+1],SpinSystem[BondNORecord[BondNumberIndex+1]*3+1]);
                           ///printf("Q Bond %f %f \n",SpinSystem[BondNORecord[BondNumberIndex+3]*3+1],SpinSystem[BondNORecord[BondNumberIndex+4]*3+1]);
                           ///printf("Q Bond %f %f \n",SpinSystem[BondNORecord[BondNumberIndex+5]*3+1],SpinSystem[BondNORecord[BondNumberIndex+6]*3+1]);                           
                 
                           
                           Hoperator[LoopNumA]=BondNumber*15+2;//*13 bond碼編號
                           Hoperator[LoopNumA+1]=BondNORecord[BondNumberIndex+1];
                           Hoperator[LoopNumA+2]=BondNORecord[BondNumberIndex+2];
                           Hoperator[LoopNumA+3]=BondNORecord[BondNumberIndex+3];
                           Hoperator[LoopNumA+4]=BondNORecord[BondNumberIndex+4];
                           Hoperator[LoopNumA+5]=BondNORecord[BondNumberIndex+5];
                           Hoperator[LoopNumA+6]=BondNORecord[BondNumberIndex+6];
                           HNO+=1;
                        }                        
                        
                    }
                }                
                
            }

        }
        else//該Hoperator非空
        {
            SwitchNO = Hoperator[LoopNumA]%15;
            //printf("diagnonal-update %d \n",SwitchNO);
            switch(SwitchNO)
            {
                case 0:
                    if(genrand64_real2()*((double)((BondNO)*(BondNOsystem[(long long)(Hoperator[LoopNumA]/15)*2+1]*Beta*0.5)))<(double)(HoperatorNO-HNO+1))
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
                    /*
                    if(SpinSystem[Hoperator[LoopNumA+1]*3+1]==SpinSystem[Hoperator[LoopNumA+2]*3+1])
                    {
                        printf("%d  %f  %f  \n",BondNORecord[((long long)(Hoperator[LoopNumA]/15))*7],SpinSystem[Hoperator[LoopNumA+1]*3+1],SpinSystem[Hoperator[LoopNumA+2]*3+1]);    
                        
                    }
                    */
                    break;
                case 2:
                    if(genrand64_real2()*((double)((BondNO)*(BondNOsystem[(long long)((Hoperator[LoopNumA]-2)/15)*2+1]*Beta*0.125)))<(double)(HoperatorNO-HNO+1))
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

void LoopUpdate(double* SpinSystem,double* BondNOsystem,long long* Hoperator,long long &HNO,long long &SpinNO,long long &BondNO,long long &HoperatorNO)
{
    long long LoopNumA,LoopNumB,LoopNumC,LoopNumD;
    long long LeftSpin,RightSpin;
    long long *SpinRecord= NULL,*FirstSpin= NULL,*LastSpin= NULL;
    long long StartSpin;
    long long CurrentSpin,footSpin,Check,Hop,HLeft,HRight,SpinNumber;
    double Chance,Goal;
    //srand(time(NULL)*rand());
    SpinRecord=(long long *)malloc((HoperatorNO*4+1)*sizeof(long long*));
    FirstSpin=(long long *)malloc((SpinNO+1)*sizeof(long long*));
    LastSpin=(long long *)malloc((SpinNO+1)*sizeof(long long*));
    memset(SpinRecord,-1,(HoperatorNO*4)*sizeof(long long*));
    
    memset(FirstSpin,-1,SpinNO*sizeof(long long*));
    memset(LastSpin,-1,SpinNO*sizeof(long long*));
    SpinRecord[HoperatorNO*4]=-999;
    FirstSpin[SpinNO]=-999;
    LastSpin[SpinNO]=-999;
    Chance=0.50;
    //建構vertex operator的腳
    for (LoopNumA=0;LoopNumA<HoperatorNO*3;LoopNumA+=3)
    {
        Hop=Hoperator[LoopNumA];
        HLeft=Hoperator[LoopNumA+1];
        HRight=Hoperator[LoopNumA+2];
        SpinNumber=LoopNumA/3*4;
        if(Hop!=-1)
        {
            LeftSpin=LastSpin[HLeft];
            RightSpin=LastSpin[HRight];
            if(LeftSpin!=-1)
            {
                SpinRecord[SpinNumber]=LeftSpin;
                SpinRecord[LeftSpin]=SpinNumber;
            }
            else
            {
                FirstSpin[HLeft]=SpinNumber;
            }
            if(RightSpin!=-1)
            {
                SpinRecord[SpinNumber+1]=RightSpin;
                SpinRecord[RightSpin]=SpinNumber+1;
            }
            else
            {
                FirstSpin[HRight]=SpinNumber+1;
            }
            LastSpin[HLeft]=SpinNumber+2;
            LastSpin[HRight]=SpinNumber+3;
            
        }
        else
        {
            for(LoopNumB=0;LoopNumB<4;LoopNumB+=1)
            {
                SpinRecord[SpinNumber+LoopNumB]=-1;
            }
        }
    }
    for(LoopNumA=0;LoopNumA<SpinNO;LoopNumA+=1)
    {
        if(FirstSpin[LoopNumA]!=-1)
        {
            SpinRecord[FirstSpin[LoopNumA]]=LastSpin[LoopNumA];
            SpinRecord[LastSpin[LoopNumA]]=FirstSpin[LoopNumA];
        }
        
    }
    for(LoopNumA=0;LoopNumA<HoperatorNO*4;LoopNumA+=4)
    {
        
        if(SpinRecord[LoopNumA]>-1)
        { 
            
            //Goal=genrand64_real2();
            StartSpin=LoopNumA;
            CurrentSpin=LoopNumA;
            Check=1;
            if(genrand64_real2()<Chance)
            {
                while (Check==1)
                {
                    if(CurrentSpin%2==0)
                    {
                        footSpin=CurrentSpin+1;                     
                    }
                    else
                    {
                        footSpin=CurrentSpin-1; 
                    }
                    
                   // printf("%d \n",Hoperator[CurrentSpin/4*3]);
                    if(Hoperator[CurrentSpin/4*3]%2==0) 
                    {
                        Hoperator[CurrentSpin/4*3]+=1;
                    }
                    else
                    {
                        Hoperator[CurrentSpin/4*3]-=1;
                    }
                    SpinRecord[CurrentSpin]=-1;
                    CurrentSpin=SpinRecord[footSpin];
                    SpinRecord[footSpin]=-1;
                    if(CurrentSpin==StartSpin)
                    {
                        Check=0;
                    }
                }
            }
            else
            {
                while(Check==1)
                {
                    if(CurrentSpin%2==0)
                    {
                        footSpin=CurrentSpin+1;                     
                    }
                    else
                    {
                        footSpin=CurrentSpin-1; 
                    }
                    SpinRecord[CurrentSpin]=-2;
                    CurrentSpin=SpinRecord[footSpin];
                    SpinRecord[footSpin]=-2;
                    if(CurrentSpin==StartSpin)
                    {
                        Check=0;
                    }      
                }
          
            }
        }
    }
       
    for(LoopNumA=0;LoopNumA<SpinNO;LoopNumA+=1)
    {
        SpinNumber=LoopNumA*3;
        if(FirstSpin[LoopNumA]!=-1)
        {
            if(SpinRecord[FirstSpin[LoopNumA]]==-1)
            {
                SpinSystem[SpinNumber+1]*=-1;
            }
        }
        else
        {
            //Goal=genrand64_real2();
            if(genrand64_real2()<Chance)
            {
                SpinSystem[SpinNumber+1]*=-1; 
            }
        }
    }
    free(SpinRecord);
    free(FirstSpin);
    free(LastSpin);
    SpinRecord=NULL;
    FirstSpin=NULL;
    LastSpin=NULL;
}

void LoopUpdate_TempW(double* SpinSystem,double* BondNOsystem,long long* Hoperator,long long &HNO,\
                    long long &SpinNO,long long &BondNO,long long &HoperatorNO,double &TempW)
    {
    long long LoopNumA,LoopNumB,LoopNumC,LoopNumD;
    long long LeftSpin,RightSpin;
    long long *SpinRecord= NULL,*FirstSpin= NULL,*LastSpin= NULL;
    long long StartSpin,HSpin;
    long long CurrentSpin,footSpin,Check,Hop,HLeft,HRight,SpinNumber,SingleFoot,SingleCurrent;
    double Chance,Goal,SumSpin;
    //srand(time(NULL)*rand());
    SpinRecord=(long long *)malloc((HoperatorNO*4+1)*sizeof(long long*));
    FirstSpin=(long long *)malloc((SpinNO+1)*sizeof(long long*));
    LastSpin=(long long *)malloc((SpinNO+1)*sizeof(long long*));
    memset(SpinRecord,-1,(HoperatorNO*4)*sizeof(long long*));
    
    memset(FirstSpin,-1,SpinNO*sizeof(long long*));
    memset(LastSpin,-1,SpinNO*sizeof(long long*));
    SpinRecord[HoperatorNO*4]=-999;
    FirstSpin[SpinNO]=-999;
    LastSpin[SpinNO]=-999;
    Chance=0.50;
    //建構vertex operator的腳
    for (LoopNumA=0;LoopNumA<HoperatorNO*3;LoopNumA+=3)
    {
        Hop=Hoperator[LoopNumA];
        HLeft=Hoperator[LoopNumA+1];
        HRight=Hoperator[LoopNumA+2];
        SpinNumber=LoopNumA/3*4;
        if(Hop!=-1)
        {
            LeftSpin=LastSpin[HLeft];
            RightSpin=LastSpin[HRight];
            if(LeftSpin!=-1)
            {
                SpinRecord[SpinNumber]=LeftSpin;
                SpinRecord[LeftSpin]=SpinNumber;
            }
            else
            {
                FirstSpin[HLeft]=SpinNumber;
            }
            if(RightSpin!=-1)
            {
                SpinRecord[SpinNumber+1]=RightSpin;
                SpinRecord[RightSpin]=SpinNumber+1;
            }
            else
            {
                FirstSpin[HRight]=SpinNumber+1;
            }
            LastSpin[HLeft]=SpinNumber+2;
            LastSpin[HRight]=SpinNumber+3;
            
        }
        else
        {
            for(LoopNumB=0;LoopNumB<4;LoopNumB+=1)
            {
                SpinRecord[SpinNumber+LoopNumB]=-1;
            }
        }
    }
    for(LoopNumA=0;LoopNumA<SpinNO;LoopNumA+=1)
    {
        if(FirstSpin[LoopNumA]!=-1)
        {
            SpinRecord[FirstSpin[LoopNumA]]=LastSpin[LoopNumA];
            SpinRecord[LastSpin[LoopNumA]]=FirstSpin[LoopNumA];
        }
        
    }
    for(LoopNumA=0;LoopNumA<HoperatorNO*4;LoopNumA+=4)
    {
        
        if(SpinRecord[LoopNumA]>-1)
        { 
            
            //Goal=genrand64_real2();
            StartSpin=LoopNumA;
            CurrentSpin=LoopNumA;
            Check=1;
            if(genrand64_real2()<Chance)
            {
                SumSpin=0;
                while (Check==1)
                {
                    if(CurrentSpin%2==0)
                    {
                        footSpin=CurrentSpin+1;                     
                    }
                    else
                    {
                        footSpin=CurrentSpin-1; 
                    }
                    
                   // printf("%d \n",Hoperator[CurrentSpin/4*3]);
                    if(Hoperator[CurrentSpin/4*3]%2==0) 
                    {
                        Hoperator[CurrentSpin/4*3]+=1;
                    }
                    else
                    {
                        Hoperator[CurrentSpin/4*3]-=1;
                    }
                    SpinRecord[CurrentSpin]=-1;
                    CurrentSpin=SpinRecord[footSpin];
                    SpinRecord[footSpin]=-1;
                    SingleFoot=footSpin%4;
                    HSpin=Hoperator[(long long)(footSpin/4*3)+SingleFoot%2+1];
                    if(footSpin%4<2)
                    {

                        if(FirstSpin[HSpin]==footSpin)
                        {
                           SumSpin+=SpinSystem[HSpin*3+1];

                        }
                    }
                    else
                    {
                        if(LastSpin[HSpin]==footSpin)
                        {
                           SumSpin+=SpinSystem[HSpin*3+1];

                            
                        }
                        
                    }
                    if(CurrentSpin==StartSpin)
                    {
                        Check=0;
                    }
                }
                TempW+=SumSpin*SumSpin*0.25;
            }
            else
            {
                while(Check==1)
                {
                    SumSpin=0;
                    if(CurrentSpin%2==0)
                    {
                        footSpin=CurrentSpin+1;                     
                    }
                    else
                    {
                        footSpin=CurrentSpin-1; 
                    }
                    SpinRecord[CurrentSpin]=-2;
                    CurrentSpin=SpinRecord[footSpin];
                    SpinRecord[footSpin]=-2;
                    SingleFoot=footSpin%4;
                    HSpin=Hoperator[(long long)(footSpin/4*3)+SingleFoot%2+1];
                    if(footSpin%4<2)
                    {

                        if(FirstSpin[HSpin]==footSpin)
                        {
                           SumSpin+=SpinSystem[HSpin*3+1];

                        }
                    }
                    else
                    {
                        if(LastSpin[HSpin]==footSpin)
                        {
                           SumSpin+=SpinSystem[HSpin*3+1];

                            
                        }
                        
                    }
                    if(CurrentSpin==StartSpin)
                    {
                        Check=0;
                    }      
                }
                TempW+=SumSpin*SumSpin*0.25;
          
            }
        }
    }
       
    for(LoopNumA=0;LoopNumA<SpinNO;LoopNumA+=1)
    {
        SpinNumber=LoopNumA*3;
        if(FirstSpin[LoopNumA]!=-1)
        {
            if(SpinRecord[FirstSpin[LoopNumA]]==-1)
            {
                SpinSystem[SpinNumber+1]*=-1;
            }
        }
        else
        {
            //Goal=genrand64_real2();
            if(genrand64_real2()<Chance)
            {
                SpinSystem[SpinNumber+1]*=-1; 
            }
        }
        TempW+=SpinSystem[SpinNumber+1]*SpinSystem[SpinNumber+1]*0.25;
    }
    free(SpinRecord);
    free(FirstSpin);
    free(LastSpin);
    SpinRecord=NULL;
    FirstSpin=NULL;
    LastSpin=NULL;
}

void LoopUpdateJQ2(double* SpinSystem,double* BondNOsystem,\
    long long* Hoperator,long long &HNO,\
    long long &SpinNO,long long &BondNO,long long &HoperatorNO,\
    double &TempW)
{
    long long LoopNumA,LoopNumB,LoopNumC,LoopNumD;
    long long LeftSpin,RightSpin,LeftSpin2,RightSpin2;
    long long *SpinRecord= NULL,*FirstSpin= NULL,*LastSpin= NULL;
    long long StartSpin,SumSpin;
    long long CurrentSpin,footSpin,Check,Hop,HLeft,HRight,HLeft2,HRight2,SpinNumber,SpinNumber2,SingleFoot,SingleCurrent;
    double Chance,Goal;
    //srand(time(NULL)*rand());
    SpinRecord=(long long *)malloc((HoperatorNO*8+1)*sizeof(long long*));
    FirstSpin=(long long *)malloc((SpinNO+1)*sizeof(long long*));
    LastSpin=(long long *)malloc((SpinNO+1)*sizeof(long long*));
    memset(SpinRecord,-1,(HoperatorNO*8)*sizeof(long long*));
    memset(FirstSpin,-1,SpinNO*sizeof(long long*));
    memset(LastSpin,-1,SpinNO*sizeof(long long*));
    SpinRecord[HoperatorNO*8]=-999;
    FirstSpin[SpinNO]=-999;
    LastSpin[SpinNO]=-999;
    Chance=0.50;
    //建構vertex operator的腳
    //printf("vertex \n");
    for (LoopNumA=0;LoopNumA<HoperatorNO*5;LoopNumA+=5)
    {
        //printf("HoperatorNO=%d,LoopNumA=%d \n",HoperatorNO,LoopNumA);
        //printf("Hop=%d,HLeft=%d,HRight=%d,HLeft2=%d,HRight2=%d \n",Hoperator[LoopNumA],Hoperator[LoopNumA+1],Hoperator[LoopNumA+2],Hoperator[LoopNumA+3],Hoperator[LoopNumA+4]);
        Hop=Hoperator[LoopNumA];
        HLeft=Hoperator[LoopNumA+1];
        HRight=Hoperator[LoopNumA+2];
        HLeft2=Hoperator[LoopNumA+3];
        HRight2=Hoperator[LoopNumA+4];
        SpinNumber=(long long)(LoopNumA/5)*8;
        SpinNumber2=(long long)(LoopNumA/5)*8+4;

        if(Hop!=-1)
        {
            if(Hop%10<2)
            {
                LeftSpin=LastSpin[HLeft];
                RightSpin=LastSpin[HRight];
                if(LeftSpin!=-1)
                {
                    SpinRecord[SpinNumber]=LeftSpin;
                    SpinRecord[LeftSpin]=SpinNumber;
                }
                else
                {
                    FirstSpin[HLeft]=SpinNumber;
                }
                if(RightSpin!=-1)
                {
                    SpinRecord[SpinNumber+1]=RightSpin;
                    SpinRecord[RightSpin]=SpinNumber+1;
                }
                else
                {
                    FirstSpin[HRight]=SpinNumber+1;
                }
                LastSpin[HLeft]=SpinNumber+2;
                LastSpin[HRight]=SpinNumber+3;                
            }
            else//JQBond
            {
                            
                LeftSpin=LastSpin[HLeft];
                RightSpin=LastSpin[HRight];
                LeftSpin2=LastSpin[HLeft2];
                RightSpin2=LastSpin[HRight2];
                if(LeftSpin!=-1)
                {
                    
                    SpinRecord[SpinNumber]=LeftSpin;
                    SpinRecord[LeftSpin]=SpinNumber;
    
                }
                else
                {
                    FirstSpin[HLeft]=SpinNumber;
                }
                if(RightSpin!=-1)
                {
                    SpinRecord[SpinNumber+1]=RightSpin;
                    SpinRecord[RightSpin]=SpinNumber+1;
                }
                else
                {
                    FirstSpin[HRight]=SpinNumber+1;
                }
                //QBond~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                
                if(LeftSpin2!=-1)
                {
                    SpinRecord[SpinNumber2]=LeftSpin2;
                    SpinRecord[LeftSpin2]=SpinNumber2;
                }
                else
                {
                    FirstSpin[HLeft2]=SpinNumber2;
                }
                if(RightSpin2!=-1)
                {
                    SpinRecord[SpinNumber2+1]=RightSpin2;
                    SpinRecord[RightSpin2]=SpinNumber2+1;
                }
                else
                {
                    FirstSpin[HRight2]=SpinNumber2+1;
                }           
                
                LastSpin[HLeft]=SpinNumber+2;
                LastSpin[HRight]=SpinNumber+3;
                LastSpin[HLeft2]=SpinNumber2+2;
                LastSpin[HRight2]=SpinNumber2+3;   
                
            }
 
        }
        else
        {
            for(LoopNumB=0;LoopNumB<8;LoopNumB+=1)
            {

                SpinRecord[SpinNumber+LoopNumB]=-1;
            }
        }
    }
    //printf("vertex-1 \n");
    for(LoopNumA=0;LoopNumA<SpinNO;LoopNumA+=1)
    {
        if(FirstSpin[LoopNumA]!=-1)
        {
            SpinRecord[FirstSpin[LoopNumA]]=LastSpin[LoopNumA];
            SpinRecord[LastSpin[LoopNumA]]=FirstSpin[LoopNumA];
        }
        
    }
    /*for(LoopNumA=0;LoopNumA <HoperatorNO*8;LoopNumA=LoopNumA+8)
    {
        //printf("%2d ,H=%3d  ,L=%3d  ,R=%3d \n",LoopNumA/3, Hoperator[LoopNumA], Hoperator[LoopNumA+1], Hoperator[LoopNumA+2]);
        printf("%2d ,%4d[%4d]  ,%4d[%4d]  ,%4d[%4d] ,%4d[%4d] ,%4d[%4d] ,%4d[%4d]  ,%4d[%4d]  ,%4d[%4d] \n",LoopNumA/8,LoopNumA,SpinRecord[LoopNumA],LoopNumA+1,SpinRecord[LoopNumA+1],LoopNumA+2, SpinRecord[LoopNumA+2],LoopNumA+3, SpinRecord[LoopNumA+3], \
        LoopNumA+4,SpinRecord[LoopNumA+4],LoopNumA+5,SpinRecord[LoopNumA+5],LoopNumA+6,SpinRecord[LoopNumA+6],LoopNumA+7,SpinRecord[LoopNumA+7]);
    }*/
    //printf("loop \n");
    for(LoopNumA=0;LoopNumA<HoperatorNO*8;LoopNumA+=4)//4為一個operator幾個腳，在這邊Q會4*2，半邊半邊算
    {
        //printf("LoopNumA=%d ,SpinRecord[LoopNumA]=%d \n",LoopNumA,SpinRecord[LoopNumA]);
        if(SpinRecord[LoopNumA]>-1)
        { 
           
            //Goal=genrand64_real2();
            StartSpin=LoopNumA;
            CurrentSpin=LoopNumA;
            Check=1;
            if(genrand64_real2()<Chance)
            {
                SumSpin=0; 
                while (Check==1)
                {
                    if(CurrentSpin%2==0)
                    {
                        footSpin=CurrentSpin+1;                     
                    }
                    else
                    {
                        footSpin=CurrentSpin-1; 
                    }
                    
                    switch(Hoperator[CurrentSpin/8*5]%10)
                    {
                        case 0:
                           Hoperator[CurrentSpin/8*5]+=1;
                           break;
                        case 1:
                           Hoperator[CurrentSpin/8*5]-=1;
                            break;
                        case 2:
                            if(CurrentSpin%8<4)
                            {
                                Hoperator[CurrentSpin/8*5]+=3;
                            }
                            else
                            {
                                Hoperator[CurrentSpin/8*5]+=4;
                            }
                            break;
                        case 5:
                            if(CurrentSpin%8<4)
                            {
                                Hoperator[CurrentSpin/8*5]-=3;
                            }
                            else
                            {
                                Hoperator[CurrentSpin/8*5]+=4;
                            }
                            break;
                        case 6:
                            if(CurrentSpin%8<4)
                            {
                                Hoperator[CurrentSpin/8*5]+=3;
                            }
                            else
                            {
                                Hoperator[CurrentSpin/8*5]-=4;
                            }
                            break;
                        case 9:
                            if(CurrentSpin%8<4)
                            {
                                Hoperator[CurrentSpin/8*5]-=3;
                            }
                            else
                            {
                                Hoperator[CurrentSpin/8*5]-=4;
                            }
                            break;                       
                    }
                    SpinRecord[CurrentSpin]=-1;
                    CurrentSpin=SpinRecord[footSpin];
                    SpinRecord[footSpin]=-1;

                    
                    if(CurrentSpin==StartSpin)
                    {
                        Check=0;
                    }
                    //printf("loop x1 CurrentSpin %d footSpin %d\n",CurrentSpin,footSpin);
                }
            }
            else
            {
                
                while(Check==1)
                {
                    if(CurrentSpin%2==0)
                    {
                        footSpin=CurrentSpin+1;                     
                    }
                    else
                    {
                        footSpin=CurrentSpin-1; 
                    }
                    SpinRecord[CurrentSpin]=-2;
                    CurrentSpin=SpinRecord[footSpin];
                    SpinRecord[footSpin]=-2;
 
                    
                    if(CurrentSpin==StartSpin)
                    {
                        Check=0;
                    }
                    //printf("loop x-1 CurrentSpin %d footSpin %d\n",CurrentSpin,footSpin);      
                }
          
            }
        }
        
    }
    //printf("loop 1 \n");   
    for(LoopNumA=0;LoopNumA<SpinNO;LoopNumA+=1)
    {
        SpinNumber=LoopNumA*3;
        if(FirstSpin[LoopNumA]!=-1)
        {
            if(SpinRecord[FirstSpin[LoopNumA]]==-1)
            {
                SpinSystem[SpinNumber+1]*=-1;
            }
        }
        else
        {
            //Goal=genrand64_real2();
            if(genrand64_real2()<Chance)
            {
                SpinSystem[SpinNumber+1]*=-1; 
            }
        }
    }
    //printf("loop end \n");
    free(SpinRecord);
    free(FirstSpin);
    free(LastSpin);
    SpinRecord=NULL;
    FirstSpin=NULL;
    LastSpin=NULL;
}


void LoopUpdateJQ2_TempW(double* SpinSystem,double* BondNOsystem,\
                    long long* Hoperator,long long &HNO,\
                    long long &SpinNO,long long &BondNO,long long &HoperatorNO,\
                    double &TempW)
{
    long long LoopNumA,LoopNumB,LoopNumC,LoopNumD;
    long long LeftSpin,RightSpin,LeftSpin2,RightSpin2;
    long long *SpinRecord= NULL,*FirstSpin= NULL,*LastSpin= NULL;
    long long StartSpin,HSpin;
    long long CurrentSpin,footSpin,Check,Hop,HLeft,HRight,HLeft2,HRight2,SpinNumber,SpinNumber2,SingleFoot,SingleCurrent;
    double Chance,Goal,SumSpin;
    //srand(time(NULL)*rand());
    SpinRecord=(long long *)malloc((HoperatorNO*8+1)*sizeof(long long*));
    FirstSpin=(long long *)malloc((SpinNO+1)*sizeof(long long*));
    LastSpin=(long long *)malloc((SpinNO+1)*sizeof(long long*));
    memset(SpinRecord,-1,(HoperatorNO*8)*sizeof(long long*));
    memset(FirstSpin,-1,SpinNO*sizeof(long long*));
    memset(LastSpin,-1,SpinNO*sizeof(long long*));
    SpinRecord[HoperatorNO*8]=-999;
    FirstSpin[SpinNO]=-999;
    LastSpin[SpinNO]=-999;
    Chance=0.50;
    //建構vertex operator的腳
    //printf("vertex \n");
    for (LoopNumA=0;LoopNumA<HoperatorNO*5;LoopNumA+=5)
    {
        //printf("HoperatorNO=%d,LoopNumA=%d \n",HoperatorNO,LoopNumA);
        //printf("Hop=%d,HLeft=%d,HRight=%d,HLeft2=%d,HRight2=%d \n",Hoperator[LoopNumA],Hoperator[LoopNumA+1],Hoperator[LoopNumA+2],Hoperator[LoopNumA+3],Hoperator[LoopNumA+4]);
        Hop=Hoperator[LoopNumA];
        HLeft=Hoperator[LoopNumA+1];
        HRight=Hoperator[LoopNumA+2];
        HLeft2=Hoperator[LoopNumA+3];
        HRight2=Hoperator[LoopNumA+4];
        SpinNumber=(long long)(LoopNumA/5)*8;
        SpinNumber2=(long long)(LoopNumA/5)*8+4;

        if(Hop!=-1)
        {
            //printf("%d , %d\n",Hop,Hop%10); 
            if(Hop%10<2)
            {
                //printf("%d , %d\n",Hop,Hop%10);
                LeftSpin=LastSpin[HLeft];
                RightSpin=LastSpin[HRight];
                if(LeftSpin!=-1)
                {
                    SpinRecord[SpinNumber]=LeftSpin;
                    SpinRecord[LeftSpin]=SpinNumber;
                }
                else
                {
                    FirstSpin[HLeft]=SpinNumber;
                }
                if(RightSpin!=-1)
                {
                    SpinRecord[SpinNumber+1]=RightSpin;
                    SpinRecord[RightSpin]=SpinNumber+1;
                }
                else
                {
                    FirstSpin[HRight]=SpinNumber+1;
                }
                LastSpin[HLeft]=SpinNumber+2;
                LastSpin[HRight]=SpinNumber+3;                
            }
            else//JQBond
            {
                           
                LeftSpin=LastSpin[HLeft];
                RightSpin=LastSpin[HRight];
                LeftSpin2=LastSpin[HLeft2];
                RightSpin2=LastSpin[HRight2];
                if(LeftSpin!=-1)
                {
                    
                    SpinRecord[SpinNumber]=LeftSpin;
                    SpinRecord[LeftSpin]=SpinNumber;
    
                }
                else
                {
                    FirstSpin[HLeft]=SpinNumber;
                }
                if(RightSpin!=-1)
                {
                    SpinRecord[SpinNumber+1]=RightSpin;
                    SpinRecord[RightSpin]=SpinNumber+1;
                }
                else
                {
                    FirstSpin[HRight]=SpinNumber+1;
                }
                //QBond~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                
                if(LeftSpin2!=-1)
                {
                    SpinRecord[SpinNumber2]=LeftSpin2;
                    SpinRecord[LeftSpin2]=SpinNumber2;
                }
                else
                {
                    FirstSpin[HLeft2]=SpinNumber2;
                }
                if(RightSpin2!=-1)
                {
                    SpinRecord[SpinNumber2+1]=RightSpin2;
                    SpinRecord[RightSpin2]=SpinNumber2+1;
                }
                else
                {
                    FirstSpin[HRight2]=SpinNumber2+1;
                }           
                
                LastSpin[HLeft]=SpinNumber+2;
                LastSpin[HRight]=SpinNumber+3;
                LastSpin[HLeft2]=SpinNumber2+2;
                LastSpin[HRight2]=SpinNumber2+3;   
                
            }
 
        }
        else
        {
            for(LoopNumB=0;LoopNumB<8;LoopNumB+=1)
            {

                SpinRecord[SpinNumber+LoopNumB]=-1;
            }
        }
    }
    //printf("vertex-1 \n");
    for(LoopNumA=0;LoopNumA<SpinNO;LoopNumA+=1)
    {
        if(FirstSpin[LoopNumA]!=-1)
        {
            SpinRecord[FirstSpin[LoopNumA]]=LastSpin[LoopNumA];
            SpinRecord[LastSpin[LoopNumA]]=FirstSpin[LoopNumA];
        }
        
    }
    /*for(LoopNumA=0;LoopNumA <HoperatorNO*8;LoopNumA=LoopNumA+8)
    {
        //printf("%2d ,H=%3d  ,L=%3d  ,R=%3d \n",LoopNumA/3, Hoperator[LoopNumA], Hoperator[LoopNumA+1], Hoperator[LoopNumA+2]);
        printf("%2d ,%4d[%4d]  ,%4d[%4d]  ,%4d[%4d] ,%4d[%4d] ,%4d[%4d] ,%4d[%4d]  ,%4d[%4d]  ,%4d[%4d] \n",LoopNumA/8,LoopNumA,SpinRecord[LoopNumA],LoopNumA+1,SpinRecord[LoopNumA+1],LoopNumA+2, SpinRecord[LoopNumA+2],LoopNumA+3, SpinRecord[LoopNumA+3], \
        LoopNumA+4,SpinRecord[LoopNumA+4],LoopNumA+5,SpinRecord[LoopNumA+5],LoopNumA+6,SpinRecord[LoopNumA+6],LoopNumA+7,SpinRecord[LoopNumA+7]);
    }*/
    //printf("loop \n");
    for(LoopNumA=0;LoopNumA<HoperatorNO*8;LoopNumA+=4)//4為一個operator幾個腳，在這邊Q會4*2，半邊半邊算
    {
        //printf("LoopNumA=%d ,SpinRecord[LoopNumA]=%d \n",LoopNumA,SpinRecord[LoopNumA]);
        if(SpinRecord[LoopNumA]>-1)
        { 
           
            //Goal=genrand64_real2();
            StartSpin=LoopNumA;
            CurrentSpin=LoopNumA;
            Check=1;
            if(genrand64_real2()<Chance)
            {
                SumSpin=0; 
                while (Check==1)
                {
                    if(CurrentSpin%2==0)
                    {
                        footSpin=CurrentSpin+1;                     
                    }
                    else
                    {
                        footSpin=CurrentSpin-1; 
                    }
                    
                    switch(Hoperator[CurrentSpin/8*5]%10)
                    {
                        case 0:
                           Hoperator[CurrentSpin/8*5]+=1;
                           break;
                        case 1:
                           Hoperator[CurrentSpin/8*5]-=1;
                            break;
                        case 2:
                            if(CurrentSpin%8<4)
                            {
                                Hoperator[CurrentSpin/8*5]+=3;
                            }
                            else
                            {
                                Hoperator[CurrentSpin/8*5]+=4;
                            }
                            break;
                        case 5:
                            if(CurrentSpin%8<4)
                            {
                                Hoperator[CurrentSpin/8*5]-=3;
                            }
                            else
                            {
                                Hoperator[CurrentSpin/8*5]+=4;
                            }
                            break;
                        case 6:
                            if(CurrentSpin%8<4)
                            {
                                Hoperator[CurrentSpin/8*5]+=3;
                            }
                            else
                            {
                                Hoperator[CurrentSpin/8*5]-=4;
                            }
                            break;
                        case 9:
                            if(CurrentSpin%8<4)
                            {
                                Hoperator[CurrentSpin/8*5]-=3;
                            }
                            else
                            {
                                Hoperator[CurrentSpin/8*5]-=4;
                            }
                            break;                       
                    }
                    SpinRecord[CurrentSpin]=-1;
                    CurrentSpin=SpinRecord[footSpin];
                    SpinRecord[footSpin]=-1;
                    SingleFoot=footSpin%8;
                    HSpin=Hoperator[(long long)(footSpin/8*5)+2*(long long)(SingleFoot/4)+SingleFoot%2+1];
                    
                    /*if(HSpin>64)
                    {
                        printf("footSpin=%d SingleFoot=%d footSpin/8=%d  SingleFoot/4=%d SingleFoot%2=%d \n",footSpin,SingleFoot,footSpin/8,SingleFoot/4,SingleFoot%2);
                        printf("%2d ,H=%3d  ,L=%3d  ,R=%3d ,L2=%3d  ,R2=%3d\n",footSpin/8*5, Hoperator[footSpin/8*5], Hoperator[footSpin/8*5+1], Hoperator[footSpin/8*5+2], Hoperator[footSpin/8*5+3], Hoperator[footSpin/8*5+4]);
                        system("pause");
                    }*/
                    //printf("footSpin=%d SingleFoot=%d footSpin/8=%d  SingleFoot/4=%d SingleFoot%2=%d \n",footSpin,SingleFoot,footSpin/8,SingleFoot/4,SingleFoot%2);
                    if(footSpin%4<2)
                    {
                        //printf("%f \n",SpinSystem[HSpin*3+1]);
                        if(FirstSpin[HSpin]==footSpin)
                        {
                           SumSpin+=SpinSystem[HSpin*3+1];
                           //printf("%f \n",SpinSystem[Hoperator[footSpin/8*5+2*SingleFoot/4+SingleFoot%2+1]*3+1]);
                           //SumSpin+=SpinSystem[Hoperator[CurrentSpin/8*5+SingleCurrent/4+SingleCurrent%2]*3+1]
                            
                        }
                    }
                    else
                    {
                        if(LastSpin[HSpin]==footSpin)
                        {
                           SumSpin+=SpinSystem[HSpin*3+1];
                           //SumSpin+=SpinSystem[Hoperator[CurrentSpin/8*5+SingleCurrent/4+SingleCurrent%2]*3+1]
                            
                        }
                        
                    }
                    
                    if(CurrentSpin==StartSpin)
                    {
                        Check=0;
                    }
                    //printf("loop x1 CurrentSpin %d footSpin %d\n",CurrentSpin,footSpin);
                }
                TempW+=SumSpin*SumSpin*0.25;
            }
            else
            {
                SumSpin=0;
                while(Check==1)
                {
                    if(CurrentSpin%2==0)
                    {
                        footSpin=CurrentSpin+1;                     
                    }
                    else
                    {
                        footSpin=CurrentSpin-1; 
                    }
                    SpinRecord[CurrentSpin]=-2;
                    CurrentSpin=SpinRecord[footSpin];
                    SpinRecord[footSpin]=-2;
                    SingleFoot=footSpin%8;
                    HSpin=Hoperator[(long long)(footSpin/8*5)+2*(long long)(SingleFoot/4)+SingleFoot%2+1];

                    //printf("%d \n",HSpin);
                    if(footSpin%4<2)
                    {
                        if(FirstSpin[HSpin]==footSpin)
                        {
                           SumSpin+=SpinSystem[HSpin*3+1];
                           //SumSpin+=SpinSystem[Hoperator[CurrentSpin/8*5+SingleCurrent/4+SingleCurrent%2]*3+1]
                            
                        }
                    }
                    else
                    {
                        if(LastSpin[HSpin]==footSpin)
                        {
                           SumSpin+=SpinSystem[HSpin*3+1];
                           //SumSpin+=SpinSystem[Hoperator[CurrentSpin/8*5+SingleCurrent/4+SingleCurrent%2]*3+1]
                            
                        }
                        
                    }
                    
                    if(CurrentSpin==StartSpin)
                    {
                        Check=0;
                    }
                    //printf("loop x-1 CurrentSpin %d footSpin %d\n",CurrentSpin,footSpin);      
                }
                TempW+=SumSpin*SumSpin*0.25;
          
            }
        }
        
    }
    //printf("%f \n",TempW);
    //printf("loop 1 \n");   
    for(LoopNumA=0;LoopNumA<SpinNO;LoopNumA+=1)
    {
        SpinNumber=LoopNumA*3;
        if(FirstSpin[LoopNumA]!=-1)
        {
            if(SpinRecord[FirstSpin[LoopNumA]]==-1)
            {
                SpinSystem[SpinNumber+1]*=-1;
            }
        }
        else
        {
            //Goal=genrand64_real2();
            if(genrand64_real2()<Chance)
            {
                SpinSystem[SpinNumber+1]*=-1; 
            }
            TempW+=SpinSystem[SpinNumber+1]*SpinSystem[SpinNumber+1]*0.25;
        }
    }
    //printf("loop end \n");
    free(SpinRecord);
    free(FirstSpin);
    free(LastSpin);
    SpinRecord=NULL;
    FirstSpin=NULL;
    LastSpin=NULL;
}
/***********************************************************/
void LoopUpdateJQ3_test(double* SpinSystem,double* BondNOsystem,\
                    long long* Hoperator,long long &HNO,\
                    long long &SpinNO,long long &BondNO,long long &HoperatorNO,\
                    double &TempW)
{
    long long LoopNumA,LoopNumB,LoopNumC,LoopNumD;
    long long LeftSpin,RightSpin,LeftSpin2,RightSpin2,LeftSpin3,RightSpin3;
    long long *SpinRecord= NULL,*FirstSpin= NULL,*LastSpin= NULL;
    long long StartSpin,HSpin;
    long long CurrentSpin,footSpin,Check,Hop,HLeft,HRight,HLeft2,HRight2,HLeft3,HRight3,SpinNumber,SpinNumber2,SpinNumber3,SingleFoot,SingleCurrent;
    double Chance,Goal,SumSpin;
    //srand(time(NULL)*rand());
    SpinRecord=(long long *)malloc((HoperatorNO*12+1)*sizeof(long long*));
    FirstSpin=(long long *)malloc((SpinNO+1)*sizeof(long long*));
    LastSpin=(long long *)malloc((SpinNO+1)*sizeof(long long*));
    memset(SpinRecord,-1,(HoperatorNO*12)*sizeof(long long*));
    memset(FirstSpin,-1,SpinNO*sizeof(long long*));
    memset(LastSpin,-1,SpinNO*sizeof(long long*));
    SpinRecord[HoperatorNO*12]=-999;
    FirstSpin[SpinNO]=-999;
    LastSpin[SpinNO]=-999;
    Chance=0.50;
    //建構vertex operator的腳
    //printf("vertex \n");
    for (LoopNumA=0;LoopNumA<HoperatorNO*7;LoopNumA+=7)
    {
        //printf("HoperatorNO=%d,LoopNumA=%d \n",HoperatorNO,LoopNumA);
        //printf("Hop=%d,HLeft=%d,HRight=%d,HLeft2=%d,HRight2=%d \n",Hoperator[LoopNumA],Hoperator[LoopNumA+1],Hoperator[LoopNumA+2],Hoperator[LoopNumA+3],Hoperator[LoopNumA+4]);
        Hop=Hoperator[LoopNumA];
        HLeft=Hoperator[LoopNumA+1];
        HRight=Hoperator[LoopNumA+2];
        HLeft2=Hoperator[LoopNumA+3];
        HRight2=Hoperator[LoopNumA+4];
        HLeft3=Hoperator[LoopNumA+5];
        HRight3=Hoperator[LoopNumA+6];
        SpinNumber=(long long)(LoopNumA/7)*12;
        SpinNumber2=(long long)(LoopNumA/7)*12+4;
        SpinNumber3=(long long)(LoopNumA/7)*12+8;
        //Q3 0-3第一個pair 4-7 第二個pair 8-11第三個pair  
        if(Hop!=-1)
        {
            //printf("%d , %d\n",Hop,Hop%10); 
            if(Hop%15<2)
            {
                //printf("%d , %d\n",Hop,Hop%10);
                LeftSpin=LastSpin[HLeft];
                RightSpin=LastSpin[HRight];
                if(LeftSpin!=-1)
                {
                    SpinRecord[SpinNumber]=LeftSpin;
                    SpinRecord[LeftSpin]=SpinNumber;
                }
                else
                {
                    FirstSpin[HLeft]=SpinNumber;
                }
                if(RightSpin!=-1)
                {
                    SpinRecord[SpinNumber+1]=RightSpin;
                    SpinRecord[RightSpin]=SpinNumber+1;
                }
                else
                {
                    FirstSpin[HRight]=SpinNumber+1;
                }
                LastSpin[HLeft]=SpinNumber+2;
                LastSpin[HRight]=SpinNumber+3;                
            }
            else//JQBond
            {
                           
                LeftSpin=LastSpin[HLeft];
                RightSpin=LastSpin[HRight];
                LeftSpin2=LastSpin[HLeft2];
                RightSpin2=LastSpin[HRight2];
                LeftSpin3=LastSpin[HLeft3];
                RightSpin3=LastSpin[HRight3];
                if(LeftSpin!=-1)
                {
                    
                    SpinRecord[SpinNumber]=LeftSpin;
                    SpinRecord[LeftSpin]=SpinNumber;
    
                }
                else
                {
                    FirstSpin[HLeft]=SpinNumber;
                }
                if(RightSpin!=-1)
                {
                    SpinRecord[SpinNumber+1]=RightSpin;
                    SpinRecord[RightSpin]=SpinNumber+1;
                }
                else
                {
                    FirstSpin[HRight]=SpinNumber+1;
                }
                //QBond~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                
                if(LeftSpin2!=-1)
                {
                    SpinRecord[SpinNumber2]=LeftSpin2;
                    SpinRecord[LeftSpin2]=SpinNumber2;
                }
                else
                {
                    FirstSpin[HLeft2]=SpinNumber2;
                }
                if(RightSpin2!=-1)
                {
                    SpinRecord[SpinNumber2+1]=RightSpin2;
                    SpinRecord[RightSpin2]=SpinNumber2+1;
                }
                else
                {
                    FirstSpin[HRight2]=SpinNumber2+1;
                }
                           
                if(LeftSpin3!=-1)
                {
                    SpinRecord[SpinNumber3]=LeftSpin3;
                    SpinRecord[LeftSpin3]=SpinNumber3;
                }
                else
                {
                    FirstSpin[HLeft3]=SpinNumber3;
                }
                if(RightSpin3!=-1)
                {
                    SpinRecord[SpinNumber3+1]=RightSpin3;
                    SpinRecord[RightSpin3]=SpinNumber3+1;
                }
                else
                {
                    FirstSpin[HRight3]=SpinNumber3+1;
                }                  
                LastSpin[HLeft]=SpinNumber+2;
                LastSpin[HRight]=SpinNumber+3;
                LastSpin[HLeft2]=SpinNumber2+2;
                LastSpin[HRight2]=SpinNumber2+3;
                LastSpin[HLeft3]=SpinNumber3+2;
                LastSpin[HRight3]=SpinNumber3+3;  
                
            }
 
        }
        else
        {
            for(LoopNumB=0;LoopNumB<12;LoopNumB+=1)
            {

                SpinRecord[SpinNumber+LoopNumB]=-1;
            }
        }
    }
    //printf("vertex-1 \n");
    for(LoopNumA=0;LoopNumA<SpinNO;LoopNumA+=1)
    {
        if(FirstSpin[LoopNumA]!=-1)
        {
            SpinRecord[FirstSpin[LoopNumA]]=LastSpin[LoopNumA];
            SpinRecord[LastSpin[LoopNumA]]=FirstSpin[LoopNumA];
        }
        
    }
    /*
    for(LoopNumA=0;LoopNumA <HoperatorNO*12;LoopNumA=LoopNumA+12)
    {
        //printf("%2d ,H=%3d  ,L=%3d  ,R=%3d \n",LoopNumA/3, Hoperator[LoopNumA], Hoperator[LoopNumA+1], Hoperator[LoopNumA+2]);
        printf("%2d ,%4d[%4d]  ,%4d[%4d]  ,%4d[%4d] ,%4d[%4d] ,%4d[%4d] ,%4d[%4d]  ,%4d[%4d]  ,%4d[%4d] ,%4d[%4d] ,%4d[%4d]  ,%4d[%4d]  ,%4d[%4d] \n", \
        LoopNumA/12,LoopNumA,SpinRecord[LoopNumA],LoopNumA+1,SpinRecord[LoopNumA+1],LoopNumA+2, SpinRecord[LoopNumA+2],LoopNumA+3, SpinRecord[LoopNumA+3], \
        LoopNumA+4,SpinRecord[LoopNumA+4],LoopNumA+5,SpinRecord[LoopNumA+5],LoopNumA+6,SpinRecord[LoopNumA+6],LoopNumA+7,SpinRecord[LoopNumA+7], \
        LoopNumA+8,SpinRecord[LoopNumA+8],LoopNumA+9,SpinRecord[LoopNumA+9],LoopNumA+10,SpinRecord[LoopNumA+10],LoopNumA+11,SpinRecord[LoopNumA+11]);
    }
    */
    for(LoopNumA=0;LoopNumA<HoperatorNO*12;LoopNumA+=4)//4為一個operator幾個腳，在這邊Q會4*3，半邊半邊算
    {
        if(SpinRecord[LoopNumA]>-1)
        { 
            StartSpin=LoopNumA;
            CurrentSpin=LoopNumA;
            Check=1;
            if(genrand64_real2()<Chance)
            {
                SumSpin=0; 
                while (Check==1)
                {
                    if(CurrentSpin%2==0)
                    {
                        footSpin=CurrentSpin+1;                     
                    }
                    else
                    {
                        footSpin=CurrentSpin-1; 
                    }
                    //printf("test %d \n",(long long)(CurrentSpin%12/4));
                    switch(Hoperator[(long long)(CurrentSpin/12)*7]%15)//1091002 修正
                    {
                        case 0:
                           Hoperator[(long long)(CurrentSpin/12)*7]+=1;
                           break;
                        case 1:
                           Hoperator[(long long)(CurrentSpin/12)*7]-=1;
                           break;
                        case 2:
              
                            switch((long long )((long long)(CurrentSpin%12/4)))
                            {
                                case 0:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=3;
                                    break;
                                case 1:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=4;
                                    break;
                                case 2:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=5;
                                    break;
                                                      
                            }
                            break;
                        case 5:
                            switch((long long )((long long)(CurrentSpin%12/4)))
                            {
                                case 0:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=3;
                                    break;
                                case 1:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=4;
                                    break;
                                case 2:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=5;
                                    break;
                            }
                            break;
                        case 6:
                            switch((long long )((long long)(CurrentSpin%12/4)))
                            {
                                case 0:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=3;
                                    break;
                                case 1:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=4;
                                    break;
                                case 2:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=5;
                                    break;
                            }
                            break;        
                        case 7:
                            switch((long long )((long long)(CurrentSpin%12/4)))
                            {
                                case 0:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=3;
                                    break;
                                case 1:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=4;
                                    break;
                                case 2:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=5;
                                    break;
                            }
                            break;
                        case 9:
                            switch((long long )((long long)(CurrentSpin%12/4)))
                            {
                                case 0:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=3;
                                    break;
                                case 1:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=4;
                                    break;
                                case 2:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=5;
                                    break;
                            }
                            break;
                        case 10:
                            switch((long long )((long long)(CurrentSpin%12/4)))
                            {
                                case 0:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=3;
                                    break;
                                case 1:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=4;
                                    break;
                                case 2:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=5;
                                    break;
                            }
                            break;
                        case 11:
                            switch((long long )((long long)(CurrentSpin%12/4)))
                            {
                                case 0:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=3;
                                    break;
                                case 1:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=4;
                                    break;
                                case 2:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=5;
                                    break;
                            }
                            break;
                        case 14:
                            switch((long long )((long long)(CurrentSpin%12/4)))
                            {
                                case 0:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=3;
                                    break;
                                case 1:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=4;
                                    break;
                                case 2:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=5;
                                    break;  
                            }
                            break;                           
                    }
                    SpinRecord[CurrentSpin]=-1;
                    //SpinRecord[CurrentSpin]=-1;
                    CurrentSpin=SpinRecord[footSpin];
                    SpinRecord[footSpin]=-1;
                    /*
                    SingleFoot=footSpin%12;
                    HSpin=Hoperator[(long long)(footSpin/12*7)+2*(long long)(SingleFoot/4)+SingleFoot%2+1];//請Hoperator內Spin的index

                    if(footSpin%4<2)
                    {
                        //printf("%f \n",SpinSystem[HSpin*3+1]);
                        if(FirstSpin[HSpin]==footSpin)
                        {
                           SumSpin+=SpinSystem[HSpin*3+1];
                           //printf("%f \n",SpinSystem[Hoperator[footSpin/8*5+2*SingleFoot/4+SingleFoot%2+1]*3+1]);
                           //SumSpin+=SpinSystem[Hoperator[CurrentSpin/8*5+SingleCurrent/4+SingleCurrent%2]*3+1]
                            
                        }
                    }
                    else
                    {
                        if(LastSpin[HSpin]==footSpin)
                        {
                           SumSpin+=SpinSystem[HSpin*3+1];
                           //SumSpin+=SpinSystem[Hoperator[CurrentSpin/8*5+SingleCurrent/4+SingleCurrent%2]*3+1]
                            
                        }
                        
                    }
                    */
                    if(CurrentSpin==StartSpin)
                    {
                        Check=0;
                    }
                    //printf("loop x1 CurrentSpin %d footSpin %d\n",CurrentSpin,footSpin);
                }
                //TempW+=SumSpin*SumSpin*0.25;
            }
            else
            {
                SumSpin=0;
                while(Check==1)
                {
                    if(CurrentSpin%2==0)
                    {
                        footSpin=CurrentSpin+1;                     
                    }
                    else
                    {
                        footSpin=CurrentSpin-1; 
                    }
                    SpinRecord[CurrentSpin]=-2;
                    CurrentSpin=SpinRecord[footSpin];
                    SpinRecord[footSpin]=-2;
                    /*SingleFoot=footSpin%12;
                    HSpin=Hoperator[(long long)(footSpin/12*7)+2*(long long)(SingleFoot/4)+SingleFoot%2+1];

                    //printf("%d \n",HSpin);
                    if(footSpin%4<2)
                    {
                        if(FirstSpin[HSpin]==footSpin)
                        {
                           SumSpin+=SpinSystem[HSpin*3+1];
                           //SumSpin+=SpinSystem[Hoperator[CurrentSpin/8*5+SingleCurrent/4+SingleCurrent%2]*3+1]
                            
                        }
                    }
                    else
                    {
                        if(LastSpin[HSpin]==footSpin)
                        {
                           SumSpin+=SpinSystem[HSpin*3+1];
                           //SumSpin+=SpinSystem[Hoperator[CurrentSpin/8*5+SingleCurrent/4+SingleCurrent%2]*3+1]
                            
                        }
                        
                    }
                    */
                    if(CurrentSpin==StartSpin)
                    {
                        Check=0;
                    }
                    //printf("loop x-1 CurrentSpin %d footSpin %d\n",CurrentSpin,footSpin);      
                }
                //TempW+=SumSpin*SumSpin*0.25;
          
            }
        }
        
    }
    //printf("%f \n",TempW);
    //printf("loop 1 \n");   
    for(LoopNumA=0;LoopNumA<SpinNO;LoopNumA+=1)
    {
        SpinNumber=LoopNumA*3;
        if(FirstSpin[LoopNumA]!=-1)
        {
            if(SpinRecord[FirstSpin[LoopNumA]]==-1)
            {
                SpinSystem[SpinNumber+1]*=-1;
            }
        }
        else
        {
            //Goal=genrand64_real2();
            if(genrand64_real2()<Chance)
            {
                SpinSystem[SpinNumber+1]*=-1; 
            }
            TempW+=SpinSystem[SpinNumber+1]*SpinSystem[SpinNumber+1]*0.25;
        }
    }
    //printf("loop end \n");
    free(SpinRecord);
    free(FirstSpin);
    free(LastSpin);
    SpinRecord=NULL;
    FirstSpin=NULL;
    LastSpin=NULL;
}



void LoopUpdateJQ3_TempW_test(double* SpinSystem,double* BondNOsystem,\
                    long long* Hoperator,long long &HNO,\
                    long long &SpinNO,long long &BondNO,long long &HoperatorNO,\
                    double &TempW)
{
    long long LoopNumA,LoopNumB,LoopNumC,LoopNumD;
    long long LeftSpin,RightSpin,LeftSpin2,RightSpin2,LeftSpin3,RightSpin3;
    long long *SpinRecord= NULL,*FirstSpin= NULL,*LastSpin= NULL;
    long long StartSpin,HSpin;
    long long CurrentSpin,footSpin,Check,Hop,HLeft,HRight,HLeft2,HRight2,HLeft3,HRight3,SpinNumber,SpinNumber2,SpinNumber3,SingleFoot,SingleCurrent;
    double Chance,Goal,SumSpin;
    //srand(time(NULL)*rand());
    SpinRecord=(long long *)malloc((HoperatorNO*12+1)*sizeof(long long*));
    FirstSpin=(long long *)malloc((SpinNO+1)*sizeof(long long*));
    LastSpin=(long long *)malloc((SpinNO+1)*sizeof(long long*));
    memset(SpinRecord,-1,(HoperatorNO*12)*sizeof(long long*));
    memset(FirstSpin,-1,SpinNO*sizeof(long long*));
    memset(LastSpin,-1,SpinNO*sizeof(long long*));
    //SpinRecord[HoperatorNO*12+1]=-999;
    //FirstSpin[SpinNO]=-999;
    //LastSpin[SpinNO]=-999;
    Chance=0.50;
    //建構vertex operator的腳
    //printf("vertex \n");
    for (LoopNumA=0;LoopNumA<HoperatorNO*7;LoopNumA+=7)
    {
        //printf("HoperatorNO=%d,LoopNumA=%d \n",HoperatorNO,LoopNumA);
        //printf("Hop=%d,HLeft=%d,HRight=%d,HLeft2=%d,HRight2=%d \n",Hoperator[LoopNumA],Hoperator[LoopNumA+1],Hoperator[LoopNumA+2],Hoperator[LoopNumA+3],Hoperator[LoopNumA+4]);
        Hop=Hoperator[LoopNumA];
        HLeft=Hoperator[LoopNumA+1];
        HRight=Hoperator[LoopNumA+2];
        HLeft2=Hoperator[LoopNumA+3];
        HRight2=Hoperator[LoopNumA+4];
        HLeft3=Hoperator[LoopNumA+5];
        HRight3=Hoperator[LoopNumA+6];
        SpinNumber=(long long)(LoopNumA/7)*12;
        SpinNumber2=(long long)(LoopNumA/7)*12+4;
        SpinNumber3=(long long)(LoopNumA/7)*12+8;
        //Q3 0-3第一個pair 4-7 第二個pair 8-11第三個pair  
        if(Hop!=-1)
        {
            //printf("%d , %d\n",Hop,Hop%10); 
            if(Hop%15<2)
            {
                //printf("%d , %d\n",Hop,Hop%10);
                LeftSpin=LastSpin[HLeft];
                RightSpin=LastSpin[HRight];
                if(LeftSpin!=-1)
                {
                    SpinRecord[SpinNumber]=LeftSpin;
                    SpinRecord[LeftSpin]=SpinNumber;
                }
                else
                {
                    FirstSpin[HLeft]=SpinNumber;
                }
                if(RightSpin!=-1)
                {
                    SpinRecord[SpinNumber+1]=RightSpin;
                    SpinRecord[RightSpin]=SpinNumber+1;
                }
                else
                {
                    FirstSpin[HRight]=SpinNumber+1;
                }
                LastSpin[HLeft]=SpinNumber+2;
                LastSpin[HRight]=SpinNumber+3;                
            }
            else//JQBond
            {
                           
                LeftSpin=LastSpin[HLeft];
                RightSpin=LastSpin[HRight];
                LeftSpin2=LastSpin[HLeft2];
                RightSpin2=LastSpin[HRight2];
                LeftSpin3=LastSpin[HLeft3];
                RightSpin3=LastSpin[HRight3];
                if(LeftSpin!=-1)
                {
                    
                    SpinRecord[SpinNumber]=LeftSpin;
                    SpinRecord[LeftSpin]=SpinNumber;
    
                }
                else
                {
                    FirstSpin[HLeft]=SpinNumber;
                }
                if(RightSpin!=-1)
                {
                    SpinRecord[SpinNumber+1]=RightSpin;
                    SpinRecord[RightSpin]=SpinNumber+1;
                }
                else
                {
                    FirstSpin[HRight]=SpinNumber+1;
                }
                //QBond~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                
                if(LeftSpin2!=-1)
                {
                    SpinRecord[SpinNumber2]=LeftSpin2;
                    SpinRecord[LeftSpin2]=SpinNumber2;
                }
                else
                {
                    FirstSpin[HLeft2]=SpinNumber2;
                }
                if(RightSpin2!=-1)
                {
                    SpinRecord[SpinNumber2+1]=RightSpin2;
                    SpinRecord[RightSpin2]=SpinNumber2+1;
                }
                else
                {
                    FirstSpin[HRight2]=SpinNumber2+1;
                }
                           
                if(LeftSpin3!=-1)
                {
                    SpinRecord[SpinNumber3]=LeftSpin3;
                    SpinRecord[LeftSpin3]=SpinNumber3;
                }
                else
                {
                    FirstSpin[HLeft3]=SpinNumber3;
                }
                if(RightSpin3!=-1)
                {
                    SpinRecord[SpinNumber3+1]=RightSpin3;
                    SpinRecord[RightSpin3]=SpinNumber3+1;
                }
                else
                {
                    FirstSpin[HRight3]=SpinNumber3+1;
                }                  
                LastSpin[HLeft]=SpinNumber+2;
                LastSpin[HRight]=SpinNumber+3;
                LastSpin[HLeft2]=SpinNumber2+2;
                LastSpin[HRight2]=SpinNumber2+3;
                LastSpin[HLeft3]=SpinNumber3+2;
                LastSpin[HRight3]=SpinNumber3+3;  
                
            }
 
        }
        else
        {
            for(LoopNumB=0;LoopNumB<12;LoopNumB+=1)
            {

                SpinRecord[SpinNumber+LoopNumB]=-1;
            }
        }
    }
    //printf("vertex-1 \n");
    for(LoopNumA=0;LoopNumA<SpinNO;LoopNumA+=1)
    {
        if(FirstSpin[LoopNumA]!=-1)
        {
            SpinRecord[FirstSpin[LoopNumA]]=LastSpin[LoopNumA];
            SpinRecord[LastSpin[LoopNumA]]=FirstSpin[LoopNumA];
        }
        
    }
 
    for(LoopNumA=0;LoopNumA<HoperatorNO*12;LoopNumA+=4)//4為一個operator幾個腳，在這邊Q會4*3，半邊半邊算
    {
        if(SpinRecord[LoopNumA]>-1)
        { 
            StartSpin=LoopNumA;
            CurrentSpin=LoopNumA;
            Check=1;
            if(genrand64_real2()<Chance)
            {
                SumSpin=0; 
                while (Check==1)
                {
                    if(CurrentSpin%2==0)
                    {
                        footSpin=CurrentSpin+1;                     
                    }
                    else
                    {
                        footSpin=CurrentSpin-1; 
                    }
                    //printf("%d %d %d\n",Hoperator[(long long)(CurrentSpin/12)*7]%15,CurrentSpin%12,(long long)(CurrentSpin%12/4));
                    switch(Hoperator[(long long)(CurrentSpin/12)*7]%15)//1091002 修正
                    {
                        case 0:
                           Hoperator[(long long)(CurrentSpin/12)*7]+=1;
                           break;
                        case 1:
                           Hoperator[(long long)(CurrentSpin/12)*7]-=1;
                           break;
                        case 2:
              
                            switch((long long )((long long)(CurrentSpin%12/4)))
                            {
                                case 0:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=3;
                                    break;
                                case 1:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=4;
                                    break;
                                case 2:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=5;
                                    break;
                          
                            }
                            break;

                        case 5:
                            switch((long long )((long long)(CurrentSpin%12/4)))
                            {
                                case 0:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=3;
                                    break;
                                case 1:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=4;
                                    break;
                                case 2:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=5;
                                    break;
                            }
                            break;
                        case 6:
                            switch((long long )((long long)(CurrentSpin%12/4)))
                            {
                                case 0:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=3;
                                    break;
                                case 1:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=4;
                                    break;
                                case 2:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=5;
                                    break;
                            }
                            break;        
                        case 7:
                            switch((long long )((long long)(CurrentSpin%12/4)))
                            {
                                case 0:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=3;
                                    break;
                                case 1:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=4;
                                    break;
                                case 2:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=5;
                                    break;
                            }
                            break;
                        case 9:
                            switch((long long )((long long)(CurrentSpin%12/4)))
                            {
                                case 0:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=3;
                                    break;
                                case 1:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=4;
                                    break;
                                case 2:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=5;
                                    break;
                            }
                            break;
                        case 10:
                            switch((long long )((long long)(CurrentSpin%12/4)))
                            {
                                case 0:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=3;
                                    break;
                                case 1:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=4;
                                    break;
                                case 2:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=5;
                                    break;
                            }
                            break;
                        case 11:
                            switch((long long )((long long)(CurrentSpin%12/4)))
                            {
                                case 0:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=3;
                                    break;
                                case 1:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=4;
                                    break;
                                case 2:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=5;
                                    break;
                            }
                            break;
                        case 14:
                            switch((long long )((long long)(CurrentSpin%12/4)))
                            {
                                case 0:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=3;
                                    break;
                                case 1:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=4;
                                    break;
                                case 2:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=5;
                                    break;  
                            }
                            break;                           
                    }
                    SpinRecord[CurrentSpin]=-1;
                    CurrentSpin=SpinRecord[footSpin];
                    SpinRecord[footSpin]=-1;
                    SingleFoot=footSpin%12;
                    HSpin=Hoperator[(long long)(footSpin/12*7)+2*(long long)(SingleFoot/4)+SingleFoot%2+1];//請Hoperator內Spin的index

                    if(footSpin%4<2)
                    {
                        //printf("%f \n",SpinSystem[HSpin*3+1]);
                        if(FirstSpin[HSpin]==footSpin)
                        {
                           SumSpin+=SpinSystem[HSpin*3+1];
                           //printf("%f \n",SpinSystem[Hoperator[footSpin/8*5+2*SingleFoot/4+SingleFoot%2+1]*3+1]);
                           //SumSpin+=SpinSystem[Hoperator[CurrentSpin/8*5+SingleCurrent/4+SingleCurrent%2]*3+1]
                            
                        }
                    }
                    else
                    {
                        if(LastSpin[HSpin]==footSpin)
                        {
                           SumSpin+=SpinSystem[HSpin*3+1];
                           //SumSpin+=SpinSystem[Hoperator[CurrentSpin/8*5+SingleCurrent/4+SingleCurrent%2]*3+1]
                            
                        }
                        
                    }
                    
                    if(CurrentSpin==StartSpin)
                    {
                        Check=0;
                    }
                    //printf("loop x1 CurrentSpin %d footSpin %d\n",CurrentSpin,footSpin);
                }
                TempW+=SumSpin*SumSpin*0.25;
            }
            else
            {
                SumSpin=0;
                while(Check==1)
                {
                    if(CurrentSpin%2==0)
                    {
                        footSpin=CurrentSpin+1;                     
                    }
                    else
                    {
                        footSpin=CurrentSpin-1; 
                    }
                    SpinRecord[CurrentSpin]=-2;
                    CurrentSpin=SpinRecord[footSpin];
                    SpinRecord[footSpin]=-2;
                    SingleFoot=footSpin%12;
                    HSpin=Hoperator[(long long)(footSpin/12*7)+2*(long long)(SingleFoot/4)+SingleFoot%2+1];

                    //printf("%d \n",HSpin);
                    if(footSpin%4<2)
                    {
                        if(FirstSpin[HSpin]==footSpin)
                        {
                           SumSpin+=SpinSystem[HSpin*3+1];
                           //SumSpin+=SpinSystem[Hoperator[CurrentSpin/8*5+SingleCurrent/4+SingleCurrent%2]*3+1]
                            
                        }
                    }
                    else
                    {
                        if(LastSpin[HSpin]==footSpin)
                        {
                           SumSpin+=SpinSystem[HSpin*3+1];
                           //SumSpin+=SpinSystem[Hoperator[CurrentSpin/8*5+SingleCurrent/4+SingleCurrent%2]*3+1]
                            
                        }
                        
                    }
                    
                    if(CurrentSpin==StartSpin)
                    {
                        Check=0;
                    }
                    //printf("loop x-1 CurrentSpin %d footSpin %d\n",CurrentSpin,footSpin);      
                }
                TempW+=SumSpin*SumSpin*0.25;
          
            }
        }
        
    }
    //printf("%f \n",TempW);
    //printf("loop 1 \n");   
    for(LoopNumA=0;LoopNumA<SpinNO;LoopNumA+=1)
    {
        SpinNumber=LoopNumA*3;
        if(FirstSpin[LoopNumA]!=-1)
        {
            if(SpinRecord[FirstSpin[LoopNumA]]==-1)
            {
                SpinSystem[SpinNumber+1]*=-1;
            }
        }
        else
        {
            //Goal=genrand64_real2();
            if(genrand64_real2()<Chance)
            {
                SpinSystem[SpinNumber+1]*=-1; 
            }
            TempW+=SpinSystem[SpinNumber+1]*SpinSystem[SpinNumber+1]*0.25;
        }
    }
    //printf("loop end \n");
    free(SpinRecord);
    free(FirstSpin);
    free(LastSpin);
    SpinRecord=NULL;
    FirstSpin=NULL;
    LastSpin=NULL;
}












/************************************************************/
void LoopUpdateJQ3(double* SpinSystem,double* BondNOsystem,\
                    long long* Hoperator,long long &HNO,\
                    long long &SpinNO,long long &BondNO,long long &HoperatorNO,\
                    double &TempW,long long* BondNORecord)
{
    long long LoopNumA,LoopNumB,LoopNumC,LoopNumD;
    long long LeftSpin,RightSpin,LeftSpin2,RightSpin2,LeftSpin3,RightSpin3;
    long long *SpinRecord= NULL,*FirstSpin= NULL,*LastSpin= NULL;
    long long StartSpin,HSpin,HopNO,SwitchNO;
    long long CurrentSpin,footSpin,Check,Hop,HLeft,HRight,HLeft2,HRight2,HLeft3,HRight3,SpinNumber,SpinNumber2,SpinNumber3,SingleFoot,SingleCurrent;
    double Chance,Goal,SumSpin;
    //srand(time(NULL)*rand());
    SpinRecord=(long long *)malloc((HoperatorNO*12+1)*sizeof(long long*));
    FirstSpin=(long long *)malloc((SpinNO+1)*sizeof(long long*));
    LastSpin=(long long *)malloc((SpinNO+1)*sizeof(long long*));
    memset(SpinRecord,-1,(HoperatorNO*12)*sizeof(long long*));
    memset(FirstSpin,-1,SpinNO*sizeof(long long*));
    memset(LastSpin,-1,SpinNO*sizeof(long long*));
    SpinRecord[HoperatorNO*12]=-999;
    FirstSpin[SpinNO]=-999;
    LastSpin[SpinNO]=-999;
    Chance=0.50;
    //建構vertex operator的腳
    //printf("vertex \n");
    for (LoopNumA=0;LoopNumA<HoperatorNO*7;LoopNumA+=7)
    {
        //printf("HoperatorNO=%d,LoopNumA=%d \n",HoperatorNO,LoopNumA);
        //printf("Hop=%d,HLeft=%d,HRight=%d,HLeft2=%d,HRight2=%d \n",Hoperator[LoopNumA],Hoperator[LoopNumA+1],Hoperator[LoopNumA+2],Hoperator[LoopNumA+3],Hoperator[LoopNumA+4]);
        Hop=Hoperator[LoopNumA];
        HLeft=Hoperator[LoopNumA+1];
        HRight=Hoperator[LoopNumA+2];
        HLeft2=Hoperator[LoopNumA+3];
        HRight2=Hoperator[LoopNumA+4];
        HLeft3=Hoperator[LoopNumA+5];
        HRight3=Hoperator[LoopNumA+6];
        SpinNumber=(long long)(LoopNumA/7)*12;
        SpinNumber2=(long long)(LoopNumA/7)*12+4;
        SpinNumber3=(long long)(LoopNumA/7)*12+8;
        //Q3 0-3第一個pair 4-7 第二個pair 8-11第三個pair  
        if(Hop!=-1)
        {
            //printf("%d , %d\n",Hop,Hop%10); 
            if(Hop%15<2)
            {
                //printf("%d , %d\n",Hop,Hop%10);
                LeftSpin=LastSpin[HLeft];
                RightSpin=LastSpin[HRight];
                if(LeftSpin!=-1)
                {
                    SpinRecord[SpinNumber]=LeftSpin;
                    SpinRecord[LeftSpin]=SpinNumber;
                }
                else
                {
                    FirstSpin[HLeft]=SpinNumber;
                }
                if(RightSpin!=-1)
                {
                    SpinRecord[SpinNumber+1]=RightSpin;
                    SpinRecord[RightSpin]=SpinNumber+1;
                }
                else
                {
                    FirstSpin[HRight]=SpinNumber+1;
                }
                LastSpin[HLeft]=SpinNumber+2;
                LastSpin[HRight]=SpinNumber+3;                
            }
            else//JQBond
            {
                           
                LeftSpin=LastSpin[HLeft];
                RightSpin=LastSpin[HRight];
                LeftSpin2=LastSpin[HLeft2];
                RightSpin2=LastSpin[HRight2];
                LeftSpin3=LastSpin[HLeft3];
                RightSpin3=LastSpin[HRight3];
                if(LeftSpin!=-1)
                {
                    
                    SpinRecord[SpinNumber]=LeftSpin;
                    SpinRecord[LeftSpin]=SpinNumber;
    
                }
                else
                {
                    FirstSpin[HLeft]=SpinNumber;
                }
                if(RightSpin!=-1)
                {
                    SpinRecord[SpinNumber+1]=RightSpin;
                    SpinRecord[RightSpin]=SpinNumber+1;
                }
                else
                {
                    FirstSpin[HRight]=SpinNumber+1;
                }
                //QBond~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                
                if(LeftSpin2!=-1)
                {
                    SpinRecord[SpinNumber2]=LeftSpin2;
                    SpinRecord[LeftSpin2]=SpinNumber2;
                }
                else
                {
                    FirstSpin[HLeft2]=SpinNumber2;
                }
                if(RightSpin2!=-1)
                {
                    SpinRecord[SpinNumber2+1]=RightSpin2;
                    SpinRecord[RightSpin2]=SpinNumber2+1;
                }
                else
                {
                    FirstSpin[HRight2]=SpinNumber2+1;
                }
                           
                if(LeftSpin3!=-1)
                {
                    SpinRecord[SpinNumber3]=LeftSpin3;
                    SpinRecord[LeftSpin3]=SpinNumber3;
                }
                else
                {
                    FirstSpin[HLeft3]=SpinNumber3;
                }
                if(RightSpin3!=-1)
                {
                    SpinRecord[SpinNumber3+1]=RightSpin3;
                    SpinRecord[RightSpin3]=SpinNumber3+1;
                }
                else
                {
                    FirstSpin[HRight3]=SpinNumber3+1;
                }                  
                LastSpin[HLeft]=SpinNumber+2;
                LastSpin[HRight]=SpinNumber+3;
                LastSpin[HLeft2]=SpinNumber2+2;
                LastSpin[HRight2]=SpinNumber2+3;
                LastSpin[HLeft3]=SpinNumber3+2;
                LastSpin[HRight3]=SpinNumber3+3;  
                
            }
 
        }
        else
        {
            for(LoopNumB=0;LoopNumB<12;LoopNumB+=1)
            {

                SpinRecord[SpinNumber+LoopNumB]=-1;
            }
        }
    }
    //printf("vertex-1 \n");
    for(LoopNumA=0;LoopNumA<SpinNO;LoopNumA+=1)
    {
        if(FirstSpin[LoopNumA]!=-1)
        {
            SpinRecord[FirstSpin[LoopNumA]]=LastSpin[LoopNumA];
            SpinRecord[LastSpin[LoopNumA]]=FirstSpin[LoopNumA];
        }
        
    }
    /*
    for(LoopNumA=0;LoopNumA <HoperatorNO*12;LoopNumA=LoopNumA+12)
    {
        //printf("%2d ,H=%3d  ,L=%3d  ,R=%3d \n",LoopNumA/3, Hoperator[LoopNumA], Hoperator[LoopNumA+1], Hoperator[LoopNumA+2]);
        printf("%2d ,%4d[%4d]  ,%4d[%4d]  ,%4d[%4d] ,%4d[%4d] ,%4d[%4d] ,%4d[%4d]  ,%4d[%4d]  ,%4d[%4d] ,%4d[%4d] ,%4d[%4d]  ,%4d[%4d]  ,%4d[%4d] \n", \
        LoopNumA/12,LoopNumA,SpinRecord[LoopNumA],LoopNumA+1,SpinRecord[LoopNumA+1],LoopNumA+2, SpinRecord[LoopNumA+2],LoopNumA+3, SpinRecord[LoopNumA+3], \
        LoopNumA+4,SpinRecord[LoopNumA+4],LoopNumA+5,SpinRecord[LoopNumA+5],LoopNumA+6,SpinRecord[LoopNumA+6],LoopNumA+7,SpinRecord[LoopNumA+7], \
        LoopNumA+8,SpinRecord[LoopNumA+8],LoopNumA+9,SpinRecord[LoopNumA+9],LoopNumA+10,SpinRecord[LoopNumA+10],LoopNumA+11,SpinRecord[LoopNumA+11]);
    }
    */
    for(LoopNumA=0;LoopNumA<HoperatorNO*12;LoopNumA+=4)//4為一個operator幾個腳，在這邊Q會4*3，半邊半邊算
    {
        if(SpinRecord[LoopNumA]>-1)
        { 
            StartSpin=LoopNumA;
            CurrentSpin=LoopNumA;
            Check=1;
            if(genrand64_real2()<Chance)
            {
                SumSpin=0; 
                while (Check==1)
                {
                    if(CurrentSpin%2==0)
                    {
                        footSpin=CurrentSpin+1;                     
                    }
                    else
                    {
                        footSpin=CurrentSpin-1; 
                    }
                    HopNO = (long long)(CurrentSpin/12)*7;
                    SwitchNO = (long long)((CurrentSpin%12)/4);
                    //printf("test %d \n",(long long)(CurrentSpin%12/4));
                    switch(Hoperator[(long long)(CurrentSpin/12)*7]%15)//1091002 修正
                    {
                        case 0:
                           Hoperator[(long long)(CurrentSpin/12)*7]+=1;
                           break;
                        case 1:
                           Hoperator[(long long)(CurrentSpin/12)*7]-=1;
                           break;
                        case 2:
              
                            switch((long long)((CurrentSpin%12)/4))
                            {
                                case 0:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=3;
                                    break;
                                case 1:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=4;
                                    break;
                                case 2:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=5;
                                    break;
                                                      
                            }
                            break;
                        case 5:
                            switch((long long)((CurrentSpin%12)/4))
                            {
                                case 0:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=3;
                                    break;
                                case 1:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=4;
                                    break;
                                case 2:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=5;
                                    break;
                            }
                            break;
                        case 6:
                            switch((long long)((CurrentSpin%12)/4))
                            {
                                case 0:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=3;
                                    break;
                                case 1:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=4;
                                    break;
                                case 2:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=5;
                                    break;
                            }
                            break;        
                        case 7:
                            switch((long long)((CurrentSpin%12)/4))
                            {
                                case 0:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=3;
                                    break;
                                case 1:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=4;
                                    break;
                                case 2:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=5;
                                    break;
                            }
                            break;
                        case 9:
                            switch((long long)((CurrentSpin%12)/4))
                            {
                                case 0:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=3;
                                    break;
                                case 1:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=4;
                                    break;
                                case 2:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=5;
                                    break;
                            }
                            break;
                        case 10:
                            switch((long long)((CurrentSpin%12)/4))
                            {
                                case 0:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=3;
                                    break;
                                case 1:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=4;
                                    break;
                                case 2:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=5;
                                    break;
                            }
                            break;
                        case 11:
                            switch((long long)((CurrentSpin%12)/4))
                            {
                                case 0:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=3;
                                    break;
                                case 1:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=4;
                                    break;
                                case 2:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=5;
                                    break;
                            }
                            break;
                        case 14:
                            switch((long long)((CurrentSpin%12)/4))
                            {
                                case 0:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=3;
                                    break;
                                case 1:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=4;
                                    break;
                                case 2:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=5;
                                    break;  
                            }
                            break;                           
                    }
                    SpinRecord[CurrentSpin]=-1;
                    //SpinRecord[CurrentSpin]=-1;
                    CurrentSpin=SpinRecord[footSpin];
                    SpinRecord[footSpin]=-1;
                    /*
                    SingleFoot=footSpin%12;
                    HSpin=Hoperator[(long long)(footSpin/12*7)+2*(long long)(SingleFoot/4)+SingleFoot%2+1];//請Hoperator內Spin的index

                    if(footSpin%4<2)
                    {
                        //printf("%f \n",SpinSystem[HSpin*3+1]);
                        if(FirstSpin[HSpin]==footSpin)
                        {
                           SumSpin+=SpinSystem[HSpin*3+1];
                           //printf("%f \n",SpinSystem[Hoperator[footSpin/8*5+2*SingleFoot/4+SingleFoot%2+1]*3+1]);
                           //SumSpin+=SpinSystem[Hoperator[CurrentSpin/8*5+SingleCurrent/4+SingleCurrent%2]*3+1]
                            
                        }
                    }
                    else
                    {
                        if(LastSpin[HSpin]==footSpin)
                        {
                           SumSpin+=SpinSystem[HSpin*3+1];
                           //SumSpin+=SpinSystem[Hoperator[CurrentSpin/8*5+SingleCurrent/4+SingleCurrent%2]*3+1]
                            
                        }
                        
                    }
                    */
                    if(CurrentSpin==StartSpin)
                    {
                        Check=0;
                    }
                    //printf("loop x1 CurrentSpin %d footSpin %d\n",CurrentSpin,footSpin);
                }
                //TempW+=SumSpin*SumSpin*0.25;
            }
            else
            {
                SumSpin=0;
                while(Check==1)
                {
                    if(CurrentSpin%2==0)
                    {
                        footSpin=CurrentSpin+1;                     
                    }
                    else
                    {
                        footSpin=CurrentSpin-1; 
                    }
                    SpinRecord[CurrentSpin]=-2;
                    CurrentSpin=SpinRecord[footSpin];
                    SpinRecord[footSpin]=-2;
                    /*SingleFoot=footSpin%12;
                    HSpin=Hoperator[(long long)(footSpin/12*7)+2*(long long)(SingleFoot/4)+SingleFoot%2+1];

                    //printf("%d \n",HSpin);
                    if(footSpin%4<2)
                    {
                        if(FirstSpin[HSpin]==footSpin)
                        {
                           SumSpin+=SpinSystem[HSpin*3+1];
                           //SumSpin+=SpinSystem[Hoperator[CurrentSpin/8*5+SingleCurrent/4+SingleCurrent%2]*3+1]
                            
                        }
                    }
                    else
                    {
                        if(LastSpin[HSpin]==footSpin)
                        {
                           SumSpin+=SpinSystem[HSpin*3+1];
                           //SumSpin+=SpinSystem[Hoperator[CurrentSpin/8*5+SingleCurrent/4+SingleCurrent%2]*3+1]
                            
                        }
                        
                    }
                    */
                    if(CurrentSpin==StartSpin)
                    {
                        Check=0;
                    }
                    //printf("loop x-1 CurrentSpin %d footSpin %d\n",CurrentSpin,footSpin);      
                }
                //TempW+=SumSpin*SumSpin*0.25;
          
            }
        }
        
    }
    //printf("%f \n",TempW);
    //printf("loop 1 \n");   
    for(LoopNumA=0;LoopNumA<SpinNO;LoopNumA+=1)
    {
        SpinNumber=LoopNumA*3;
        if(FirstSpin[LoopNumA]!=-1)
        {
            if(SpinRecord[FirstSpin[LoopNumA]]==-1)
            {
                SpinSystem[SpinNumber+1]*=-1;
            }
        }
        else
        {
            //Goal=genrand64_real2();
            if(genrand64_real2()<Chance)
            {
                SpinSystem[SpinNumber+1]*=-1; 
            }
            //TempW+=SpinSystem[SpinNumber+1]*SpinSystem[SpinNumber+1]*0.25;
        }
    }
    //printf("loop end \n");
    free(SpinRecord);
    free(FirstSpin);
    free(LastSpin);
    SpinRecord=NULL;
    FirstSpin=NULL;
    LastSpin=NULL;
}


void LoopUpdateJQ3_TempW(double* SpinSystem,double* BondNOsystem,\
                    long long* Hoperator,long long &HNO,\
                    long long &SpinNO,long long &BondNO,long long &HoperatorNO,\
                    double &TempW,long long* BondNORecord)
{
    long long LoopNumA,LoopNumB,LoopNumC,LoopNumD;
    long long LeftSpin,RightSpin,LeftSpin2,RightSpin2,LeftSpin3,RightSpin3;
    long long *SpinRecord= NULL,*FirstSpin= NULL,*LastSpin= NULL;
    long long StartSpin,HSpin,HopNO,SwitchNO;
    long long CurrentSpin,footSpin,Check,Hop,HLeft,HRight,HLeft2,HRight2,HLeft3,HRight3,SpinNumber,SpinNumber2,SpinNumber3,SingleFoot,SingleCurrent;
    double Chance,Goal,SumSpin;
    //srand(time(NULL)*rand());
    SpinRecord=(long long *)malloc((HoperatorNO*12+1)*sizeof(long long*));
    FirstSpin=(long long *)malloc((SpinNO+1)*sizeof(long long*));
    LastSpin=(long long *)malloc((SpinNO+1)*sizeof(long long*));
    memset(SpinRecord,-1,(HoperatorNO*12)*sizeof(long long*));
    memset(FirstSpin,-1,SpinNO*sizeof(long long*));
    memset(LastSpin,-1,SpinNO*sizeof(long long*));
    //SpinRecord[HoperatorNO*12+1]=-999;
    //FirstSpin[SpinNO]=-999;
    //LastSpin[SpinNO]=-999;
    Chance=0.50;
    //建構vertex operator的腳
    //printf("vertex \n");
    for (LoopNumA=0;LoopNumA<HoperatorNO*7;LoopNumA+=7)
    {
        //printf("HoperatorNO=%d,LoopNumA=%d \n",HoperatorNO,LoopNumA);
        //printf("Hop=%d,HLeft=%d,HRight=%d,HLeft2=%d,HRight2=%d \n",Hoperator[LoopNumA],Hoperator[LoopNumA+1],Hoperator[LoopNumA+2],Hoperator[LoopNumA+3],Hoperator[LoopNumA+4]);
        Hop=Hoperator[LoopNumA];
        HLeft=Hoperator[LoopNumA+1];
        HRight=Hoperator[LoopNumA+2];
        HLeft2=Hoperator[LoopNumA+3];
        HRight2=Hoperator[LoopNumA+4];
        HLeft3=Hoperator[LoopNumA+5];
        HRight3=Hoperator[LoopNumA+6];
        SpinNumber=(long long)(LoopNumA/7)*12;
        SpinNumber2=(long long)(LoopNumA/7)*12+4;
        SpinNumber3=(long long)(LoopNumA/7)*12+8;
        //Q3 0-3第一個pair 4-7 第二個pair 8-11第三個pair  
        if(Hop!=-1)
        {
            //printf("%d , %d\n",Hop,Hop%10); 
            if(Hop%15<2)
            {
                //printf("%d , %d\n",Hop,Hop%10);
                LeftSpin=LastSpin[HLeft];
                RightSpin=LastSpin[HRight];
                if(LeftSpin!=-1)
                {
                    SpinRecord[SpinNumber]=LeftSpin;
                    SpinRecord[LeftSpin]=SpinNumber;
                }
                else
                {
                    FirstSpin[HLeft]=SpinNumber;
                }
                if(RightSpin!=-1)
                {
                    SpinRecord[SpinNumber+1]=RightSpin;
                    SpinRecord[RightSpin]=SpinNumber+1;
                }
                else
                {
                    FirstSpin[HRight]=SpinNumber+1;
                }
                LastSpin[HLeft]=SpinNumber+2;
                LastSpin[HRight]=SpinNumber+3;                
            }
            else//JQBond
            {
                           
                LeftSpin=LastSpin[HLeft];
                RightSpin=LastSpin[HRight];
                LeftSpin2=LastSpin[HLeft2];
                RightSpin2=LastSpin[HRight2];
                LeftSpin3=LastSpin[HLeft3];
                RightSpin3=LastSpin[HRight3];
                if(LeftSpin!=-1)
                {
                    
                    SpinRecord[SpinNumber]=LeftSpin;
                    SpinRecord[LeftSpin]=SpinNumber;
    
                }
                else
                {
                    FirstSpin[HLeft]=SpinNumber;
                }
                if(RightSpin!=-1)
                {
                    SpinRecord[SpinNumber+1]=RightSpin;
                    SpinRecord[RightSpin]=SpinNumber+1;
                }
                else
                {
                    FirstSpin[HRight]=SpinNumber+1;
                }
                //QBond~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                
                if(LeftSpin2!=-1)
                {
                    SpinRecord[SpinNumber2]=LeftSpin2;
                    SpinRecord[LeftSpin2]=SpinNumber2;
                }
                else
                {
                    FirstSpin[HLeft2]=SpinNumber2;
                }
                if(RightSpin2!=-1)
                {
                    SpinRecord[SpinNumber2+1]=RightSpin2;
                    SpinRecord[RightSpin2]=SpinNumber2+1;
                }
                else
                {
                    FirstSpin[HRight2]=SpinNumber2+1;
                }
                           
                if(LeftSpin3!=-1)
                {
                    SpinRecord[SpinNumber3]=LeftSpin3;
                    SpinRecord[LeftSpin3]=SpinNumber3;
                }
                else
                {
                    FirstSpin[HLeft3]=SpinNumber3;
                }
                if(RightSpin3!=-1)
                {
                    SpinRecord[SpinNumber3+1]=RightSpin3;
                    SpinRecord[RightSpin3]=SpinNumber3+1;
                }
                else
                {
                    FirstSpin[HRight3]=SpinNumber3+1;
                }                  
                LastSpin[HLeft]=SpinNumber+2;
                LastSpin[HRight]=SpinNumber+3;
                LastSpin[HLeft2]=SpinNumber2+2;
                LastSpin[HRight2]=SpinNumber2+3;
                LastSpin[HLeft3]=SpinNumber3+2;
                LastSpin[HRight3]=SpinNumber3+3;  
                
            }
 
        }
        else
        {
            for(LoopNumB=0;LoopNumB<12;LoopNumB+=1)
            {

                SpinRecord[SpinNumber+LoopNumB]=-1;
            }
        }
    }
    //printf("vertex-1 \n");
    for(LoopNumA=0;LoopNumA<SpinNO;LoopNumA+=1)
    {
        if(FirstSpin[LoopNumA]!=-1)
        {
            SpinRecord[FirstSpin[LoopNumA]]=LastSpin[LoopNumA];
            SpinRecord[LastSpin[LoopNumA]]=FirstSpin[LoopNumA];
        }
        
    }
 
    for(LoopNumA=0;LoopNumA<HoperatorNO*12;LoopNumA+=4)//4為一個operator幾個腳，在這邊Q會4*3，半邊半邊算
    {
        if(SpinRecord[LoopNumA]>-1)
        { 
            StartSpin=LoopNumA;
            CurrentSpin=LoopNumA;
            Check=1;
            if(genrand64_real2()<Chance)
            {
                SumSpin=0; 
                while (Check==1)
                {
                    if(CurrentSpin%2==0)
                    {
                        footSpin=CurrentSpin+1;                     
                    }
                    else
                    {
                        footSpin=CurrentSpin-1; 
                    }
                    
                    HopNO = (long long)(CurrentSpin/12)*7;;
                    SwitchNO = (long long)((CurrentSpin%12)/4);
                    //printf("%d %d %d\n",Hoperator[(long long)(CurrentSpin/12)*7]%15,CurrentSpin%12,(long long)(CurrentSpin%12/4));
                    
                    switch(Hoperator[(long long)(CurrentSpin/12)*7]%15)//1091002 修正
                    {
                        case 0:
                           Hoperator[(long long)(CurrentSpin/12)*7]+=1;
                           break;
                        case 1:
                           Hoperator[(long long)(CurrentSpin/12)*7]-=1;
                           break;
                        case 2:
              
                            switch((long long)((CurrentSpin%12)/4))
                            {
                                case 0:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=3;
                                    break;
                                case 1:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=4;
                                    break;
                                case 2:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=5;
                                    break;
                                                      
                            }
                            break;
                        case 5:
                            switch((long long)((CurrentSpin%12)/4))
                            {
                                case 0:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=3;
                                    break;
                                case 1:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=4;
                                    break;
                                case 2:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=5;
                                    break;
                            }
                            break;
                        case 6:
                            switch((long long)((CurrentSpin%12)/4))
                            {
                                case 0:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=3;
                                    break;
                                case 1:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=4;
                                    break;
                                case 2:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=5;
                                    break;
                            }
                            break;        
                        case 7:
                            switch((long long)((CurrentSpin%12)/4))
                            {
                                case 0:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=3;
                                    break;
                                case 1:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=4;
                                    break;
                                case 2:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=5;
                                    break;
                            }
                            break;
                        case 9:
                            switch((long long)((CurrentSpin%12)/4))
                            {
                                case 0:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=3;
                                    break;
                                case 1:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=4;
                                    break;
                                case 2:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=5;
                                    break;
                            }
                            break;
                        case 10:
                            switch((long long)((CurrentSpin%12)/4))
                            {
                                case 0:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=3;
                                    break;
                                case 1:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=4;
                                    break;
                                case 2:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=5;
                                    break;
                            }
                            break;
                        case 11:
                            switch((long long)((CurrentSpin%12)/4))
                            {
                                case 0:
                                    Hoperator[(long long)(CurrentSpin/12)*7]+=3;
                                    break;
                                case 1:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=4;
                                    break;
                                case 2:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=5;
                                    break;
                            }
                            break;
                        case 14:
                            switch((long long)((CurrentSpin%12)/4))
                            {
                                case 0:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=3;
                                    break;
                                case 1:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=4;
                                    break;
                                case 2:
                                    Hoperator[(long long)(CurrentSpin/12)*7]-=5;
                                    break;  
                            }
                            break;                           
                    }
                    

                    SpinRecord[CurrentSpin]=-1;
                    CurrentSpin=SpinRecord[footSpin];
                    SpinRecord[footSpin]=-1;
                    SingleFoot=footSpin%12;
                    HSpin=Hoperator[(long long)(footSpin/12*7)+2*(long long)(SingleFoot/4)+SingleFoot%2+1];//請Hoperator內Spin的index

                    if(footSpin%4<2)
                    {
                        //printf("%f \n",SpinSystem[HSpin*3+1]);
                        if(FirstSpin[HSpin]==footSpin)
                        {
                           SumSpin+=SpinSystem[HSpin*3+1];
                           //printf("%f \n",SpinSystem[Hoperator[footSpin/8*5+2*SingleFoot/4+SingleFoot%2+1]*3+1]);
                           //SumSpin+=SpinSystem[Hoperator[CurrentSpin/8*5+SingleCurrent/4+SingleCurrent%2]*3+1]
                            
                        }
                    }
                    else
                    {
                        if(LastSpin[HSpin]==footSpin)
                        {
                           SumSpin+=SpinSystem[HSpin*3+1];
                           //SumSpin+=SpinSystem[Hoperator[CurrentSpin/8*5+SingleCurrent/4+SingleCurrent%2]*3+1]
                            
                        }
                        
                    }
                    
                    if(CurrentSpin==StartSpin)
                    {
                        Check=0;
                    }
                    //printf("loop x1 CurrentSpin %d footSpin %d\n",CurrentSpin,footSpin);
                }
                TempW+=SumSpin*SumSpin*0.25;
            }
            else
            {
                SumSpin=0;
                while(Check==1)
                {
                    if(CurrentSpin%2==0)
                    {
                        footSpin=CurrentSpin+1;                     
                    }
                    else
                    {
                        footSpin=CurrentSpin-1; 
                    }
                    SpinRecord[CurrentSpin]=-2;
                    CurrentSpin=SpinRecord[footSpin];
                    SpinRecord[footSpin]=-2;
                    SingleFoot=footSpin%12;
                    HSpin=Hoperator[(long long)(footSpin/12*7)+2*(long long)(SingleFoot/4)+SingleFoot%2+1];

                    //printf("%d \n",HSpin);
                    if(footSpin%4<2)
                    {
                        if(FirstSpin[HSpin]==footSpin)
                        {
                           SumSpin+=SpinSystem[HSpin*3+1];
                           //SumSpin+=SpinSystem[Hoperator[CurrentSpin/8*5+SingleCurrent/4+SingleCurrent%2]*3+1]
                            
                        }
                    }
                    else
                    {
                        if(LastSpin[HSpin]==footSpin)
                        {
                           SumSpin+=SpinSystem[HSpin*3+1];
                           //SumSpin+=SpinSystem[Hoperator[CurrentSpin/8*5+SingleCurrent/4+SingleCurrent%2]*3+1]
                            
                        }
                        
                    }
                    
                    if(CurrentSpin==StartSpin)
                    {
                        Check=0;
                    }
                    //printf("loop x-1 CurrentSpin %d footSpin %d\n",CurrentSpin,footSpin);      
                }
                TempW+=SumSpin*SumSpin*0.25;
          
            }
        }
        
    }
    //printf("%f \n",TempW);
    //printf("loop 1 \n");   
    for(LoopNumA=0;LoopNumA<SpinNO;LoopNumA+=1)
    {
        SpinNumber=LoopNumA*3;
        if(FirstSpin[LoopNumA]!=-1)
        {
            if(SpinRecord[FirstSpin[LoopNumA]]==-1)
            {
                SpinSystem[SpinNumber+1]*=-1;
            }
        }
        else
        {
            //Goal=genrand64_real2();
            if(genrand64_real2()<Chance)
            {
                SpinSystem[SpinNumber+1]*=-1; 
            }
            TempW+=SpinSystem[SpinNumber+1]*SpinSystem[SpinNumber+1]*0.25;
        }
    }
    //printf("loop end \n");
    free(SpinRecord);
    free(FirstSpin);
    free(LastSpin);
    SpinRecord=NULL;
    FirstSpin=NULL;
    LastSpin=NULL;
}
void LoopUpdateJQ3_Spin1_TempW(double* SpinSystem,double* BondNOsystem,\
                    long long* Hoperator,long long &HNO,\
                    long long &SpinNO,long long &BondNO,long long &HoperatorNO,\
                    double &TempW,long long* BondNORecord)
{
    long long LoopNumA,LoopNumB,LoopNumC,LoopNumD;
    long long LeftSpin,RightSpin,LeftSpin2,RightSpin2,LeftSpin3,RightSpin3;
    long long *SpinRecord= NULL,*FirstSpin= NULL,*LastSpin= NULL,*HSpinLR = NULL, *SpinNumber=NULL, *FootTemp=NULL;
    long long StartSpin,HopNO,HSpin,SwitchNO,SpinNumber_NO;
    long long CurrentSpin,footSpin,Check,Hop,HLeft,HRight,HLeft2,HRight2,HLeft3,HRight3,SingleFoot,SingleCurrent;
    double Chance,Goal,SumSpin;
    //srand(time(NULL)*rand());
    SpinRecord=(long long *)malloc((HoperatorNO*2*12+1)*sizeof(long long*));
    FirstSpin=(long long *)malloc((SpinNO+1)*sizeof(long long*));
    LastSpin=(long long *)malloc((SpinNO+1)*sizeof(long long*));
    HSpinLR=(long long *)malloc((6*2+1)*sizeof(long long*));//每個Spin都記是否為Ferromagnetic
    SpinNumber=(long long *)malloc((3+1)*sizeof(long long*));
    FootTemp=(long long *)malloc((4+1)*sizeof(long long*));
    memset(SpinRecord,-1,(HoperatorNO*2*12)*sizeof(long long*));
    memset(FirstSpin,-1,SpinNO*sizeof(long long*));
    memset(LastSpin,-1,SpinNO*sizeof(long long*));
    memset(HSpinLR,-1,(6*2+1)*sizeof(long long*));
    memset(SpinNumber,-1,(3+1)*sizeof(long long*));
    memset(FootTemp,-1,(4+1)*sizeof(long long*));
    FootTemp[0]=3;
    FootTemp[1]=1;
    FootTemp[2]=-1;
    FootTemp[3]=-3;
    
    //SpinRecord[HoperatorNO*12+1]=-999;
    //FirstSpin[SpinNO]=-999;
    //LastSpin[SpinNO]=-999;
    Chance=0.50;
    //建構vertex operator的腳
    //printf("vertex \n");
    for (LoopNumA=0;LoopNumA<HoperatorNO*7;LoopNumA+=7)
    {
        //printf("HoperatorNO=%d,LoopNumA=%d \n",HoperatorNO,LoopNumA);
        //printf("Hop=%d,HLeft=%d,HRight=%d,HLeft2=%d,HRight2=%d \n",Hoperator[LoopNumA],Hoperator[LoopNumA+1],Hoperator[LoopNumA+2],Hoperator[LoopNumA+3],Hoperator[LoopNumA+4]);
       memset(HSpinLR,-1,(6*2)*sizeof(long long*));
        //printf("HoperatorNO=%d,LoopNumA=%d \n",HoperatorNO,LoopNumA);
        //printf("Hop=%d,HLeft=%d,HRight=%d,HLeft2=%d,HRight2=%d \n",Hoperator[LoopNumA],Hoperator[LoopNumA+1],Hoperator[LoopNumA+2],Hoperator[LoopNumA+3],Hoperator[LoopNumA+4]);
        //printf("Check Loop-1\n");
        Hop=Hoperator[LoopNumA];
        if (BondNORecord[((long long)(Hop/15))*7]>-1)
        {
            if(BondNORecord[((long long)(Hop/15))*7]==0)
            {
                HSpinLR[0] = BondNORecord[((long long)(Hop/15))*7];
                HSpinLR[2] = BondNORecord[((long long)(Hop/15))*7];  
                //printf("%d %d \n",HSpinLR[0],HSpinLR[2]);  
            }
            else
            {
                HSpinLR[(BondNORecord[((long long)(Hop/15))*7]-1)*2]= BondNORecord[((long long)(Hop/15))*7];
                HSpinLR[(BondNORecord[((long long)(Hop/15))*7]-1)*2+2]= BondNORecord[((long long)(Hop/15))*7];
            }
              
        }
        for(LoopNumB=0;LoopNumB<6;LoopNumB+=1)
        {
          

          HSpinLR[LoopNumB*2+1] = Hoperator[LoopNumA+LoopNumB+1];

        }       
        /*
        HLeft=Hoperator[LoopNumA+1];
        HRight=Hoperator[LoopNumA+2];
        HLeft2=Hoperator[LoopNumA+3];
        HRight2=Hoperator[LoopNumA+4];
        HLeft3=Hoperator[LoopNumA+5];
        HRight3=Hoperator[LoopNumA+6];
        */
        for(LoopNumB = 0 ; LoopNumB < 3 ; LoopNumB+=1)
        {
            SpinNumber[LoopNumB] = (long long)(LoopNumA/7)*12+4*LoopNumB;
        }
        /*
        SpinNumber=(long long)(LoopNumA/7)*12;
        SpinNumber2=(long long)(LoopNumA/7)*12+4;
        SpinNumber3=(long long)(LoopNumA/7)*12+8;
        */
        
        //Q3 0-3第一個pair 4-7 第二個pair 8-11第三個pair  
        if(Hop!=-1)
        {
            //printf("%d , %d\n",Hop,Hop%10); 
            if(Hop%15<2)
            {
                //printf("%d , %d\n",Hop,Hop%10);
                //LeftSpin=LastSpin[HLeft];
                //RightSpin=LastSpin[HRight];
                if(HSpinLR[0] >-1)
                {
                    for(LoopNumB=0 ; LoopNumB < 2 ; LoopNumB+=1)
                    {
                        SpinRecord[(SpinNumber[0]+LoopNumB)*2]=HSpinLR[LoopNumB*2];
                        SpinRecord[(SpinNumber[0]+LoopNumB+2)*2]=HSpinLR[LoopNumB*2]; 
                    }
                        
                                        
                } 
                
                
                for(LoopNumB=0 ; LoopNumB < 2 ; LoopNumB+=1)
                {
                    if(LastSpin[HSpinLR[LoopNumB*2+1]]!=-1)
                    {
                        SpinRecord[(SpinNumber[0]+LoopNumB)*2+1]=LastSpin[HSpinLR[LoopNumB*2+1]];
                        SpinRecord[LastSpin[HSpinLR[LoopNumB*2+1]]*2+1]=SpinNumber[0]+LoopNumB;
                        //printf("%3d %3d \n",SpinRecord[(SpinNumber[0]+LoopNumB)*2+1], SpinRecord[LastSpin[HSpinLR[LoopNumB*2+1]]*2+1]);
                        /*
                        if(HSpinLR[LoopNumB*2] !=-1)
                        {
                           //printf("Spin1");
                           SpinRecord[(SpinNumber[0]+LoopNumB)*2]=HSpinLR[LoopNumB*2];
                           ///SpinRecord[LastSpin[HSpinLR[LoopNumB*2+1]]*2]=HSpinLR[LoopNumB*2];
                        }
                        */
                        
                    }
                    else
                    {
                        FirstSpin[HSpinLR[LoopNumB*2+1]]=SpinNumber[0]+LoopNumB ;
                        /*
                        if(HSpinLR[LoopNumB*2] >-1)
                        {
                           //printf("Spin1");
                           SpinRecord[(SpinNumber[0]+LoopNumB)*2]=HSpinLR[LoopNumB*2];
                           SpinRecord[(SpinNumber[0]+LoopNumB+2)*2]=HSpinLR[LoopNumB*2];
                        }
                        */                        
                    }
                    LastSpin[HSpinLR[LoopNumB*2+1]]=SpinNumber[0]+2+LoopNumB;
                }
                /*
                if(LeftSpin!=-1)
                {
                    SpinRecord[SpinNumber]=LeftSpin;
                    SpinRecord[LeftSpin]=SpinNumber;
                }
                else
                {
                    FirstSpin[HLeft]=SpinNumber;
                }
                if(RightSpin!=-1)
                {
                    SpinRecord[SpinNumber+1]=RightSpin;
                    SpinRecord[RightSpin]=SpinNumber+1;
                }
                else
                {
                    FirstSpin[HRight]=SpinNumber+1;
                }
                
                LastSpin[HLeft]=SpinNumber+2;
                LastSpin[HRight]=SpinNumber+3; 
                */               
            }
            else//JQBond
            {
                for(LoopNumC=0 ; LoopNumC < 3 ; LoopNumC+=1)
                {    
                    if(HSpinLR[LoopNumC*4] >-1)
                    {
                        for(LoopNumB=0 ; LoopNumB < 2 ; LoopNumB+=1)
                        {
                            SpinRecord[(SpinNumber[LoopNumC]+LoopNumB)*2]=HSpinLR[LoopNumC*4];
                            SpinRecord[(SpinNumber[LoopNumC]+LoopNumB+2)*2]=HSpinLR[LoopNumC*4];  
                        }
                    }
                } 
                
                
                for(LoopNumC=0 ; LoopNumC < 3 ; LoopNumC+=1)
                {
                    for(LoopNumB=0 ; LoopNumB < 2 ; LoopNumB+=1)
                    {
                        if(LastSpin[HSpinLR[LoopNumB*2+LoopNumC*4+1]]!=-1)
                        {
                            SpinRecord[(SpinNumber[LoopNumC]+LoopNumB)*2+1]=LastSpin[HSpinLR[LoopNumB*2+LoopNumC*4+1]];
                            SpinRecord[LastSpin[HSpinLR[LoopNumB*2+LoopNumC*4+1]]*2+1]=SpinNumber[LoopNumC]+LoopNumB;
                            //printf("%3d %3d \n",SpinRecord[(SpinNumber[LoopNumC]+LoopNumB)*2+1],SpinRecord[LastSpin[HSpinLR[LoopNumB*2+LoopNumC*4+1]]*2+1]);
                            /*
                            if(HSpinLR[LoopNumB*2+LoopNumC*4]!=-1)
                            {
                               //printf("Spin1");
                               SpinRecord[(SpinNumber[LoopNumC]+LoopNumB)*2]=HSpinLR[LoopNumB*2+LoopNumC*4];
                               //SpinRecord[LastSpin[HSpinLR[LoopNumB*2+LoopNumC*4+1]]*2]=HSpinLR[LoopNumB*2+LoopNumC*4];
                            }
                            * */
                        }
                        else
                        {
                            FirstSpin[HSpinLR[LoopNumB*2+LoopNumC*4+1]]=SpinNumber[LoopNumC]+LoopNumB ;
                            /*
                            if(HSpinLR[LoopNumB*2+LoopNumC*4]>-1)
                            {
                               //printf("Spin1");
                               SpinRecord[(SpinNumber[LoopNumC]+LoopNumB)*2]=HSpinLR[LoopNumB*2+LoopNumC*4];
                               SpinRecord[(SpinNumber[LoopNumC]+LoopNumB+2)*2]=HSpinLR[LoopNumB*2+LoopNumC*4];
                            }
                            */                            
                        }
                        LastSpin[HSpinLR[LoopNumB*2+LoopNumC*4+1]]=SpinNumber[LoopNumC]+2+LoopNumB;
                    }                    
                }
                /*           
                LeftSpin=LastSpin[HLeft];
                RightSpin=LastSpin[HRight];
                LeftSpin2=LastSpin[HLeft2];
                RightSpin2=LastSpin[HRight2];
                LeftSpin3=LastSpin[HLeft3];
                RightSpin3=LastSpin[HRight3];
                
                
                if(LeftSpin!=-1)
                {
                    
                    SpinRecord[SpinNumber]=LeftSpin;
                    SpinRecord[LeftSpin]=SpinNumber;
    
                }
                else
                {
                    FirstSpin[HLeft]=SpinNumber;
                }
                if(RightSpin!=-1)
                {
                    SpinRecord[SpinNumber+1]=RightSpin;
                    SpinRecord[RightSpin]=SpinNumber+1;
                }
                else
                {
                    FirstSpin[HRight]=SpinNumber+1;
                }
                //QBond~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                
                if(LeftSpin2!=-1)
                {
                    SpinRecord[SpinNumber2]=LeftSpin2;
                    SpinRecord[LeftSpin2]=SpinNumber2;
                }
                else
                {
                    FirstSpin[HLeft2]=SpinNumber2;
                }
                if(RightSpin2!=-1)
                {
                    SpinRecord[SpinNumber2+1]=RightSpin2;
                    SpinRecord[RightSpin2]=SpinNumber2+1;
                }
                else
                {
                    FirstSpin[HRight2]=SpinNumber2+1;
                }
                           
                if(LeftSpin3!=-1)
                {
                    SpinRecord[SpinNumber3]=LeftSpin3;
                    SpinRecord[LeftSpin3]=SpinNumber3;
                }
                else
                {
                    FirstSpin[HLeft3]=SpinNumber3;
                }
                if(RightSpin3!=-1)
                {
                    SpinRecord[SpinNumber3+1]=RightSpin3;
                    SpinRecord[RightSpin3]=SpinNumber3+1;
                }
                else
                {
                    FirstSpin[HRight3]=SpinNumber3+1;
                }                  
                LastSpin[HLeft]=SpinNumber+2;
                LastSpin[HRight]=SpinNumber+3;
                LastSpin[HLeft2]=SpinNumber2+2;
                LastSpin[HRight2]=SpinNumber2+3;
                LastSpin[HLeft3]=SpinNumber3+2;
                LastSpin[HRight3]=SpinNumber3+3;  
                */
            }
 
        }
        else
        {
            //continue;
            
            for(LoopNumB=0;LoopNumB<12;LoopNumB+=1)
            {

                SpinRecord[(SpinNumber[0]+LoopNumB)*2]=-1;
            }
            
        }
    }
    //printf("vertex-1 \n");
    for(LoopNumA=0;LoopNumA<SpinNO;LoopNumA+=1)
    {
        if(FirstSpin[LoopNumA]!=-1)
        {
            SpinRecord[FirstSpin[LoopNumA]*2+1]=LastSpin[LoopNumA];
            SpinRecord[LastSpin[LoopNumA]*2+1]=FirstSpin[LoopNumA];
        }
        
    }
    /*    
    for(LoopNumA=0;LoopNumA<SpinNO;LoopNumA+=1)
    {
        if(FirstSpin[LoopNumA]!=-1)
        {
            SpinRecord[FirstSpin[LoopNumA]]=LastSpin[LoopNumA];
            SpinRecord[LastSpin[LoopNumA]]=FirstSpin[LoopNumA];
        }
        
    }
    */
 
    for(LoopNumA=0;LoopNumA<HoperatorNO*12;LoopNumA+=4)//4為一個operator幾個腳，在這邊Q會4*3，半邊半邊算
    {
        if(SpinRecord[LoopNumA*2+1]>-1)
        { 
            StartSpin=LoopNumA;
            CurrentSpin=LoopNumA;
            Check=1;
            if(genrand64_real2()<Chance)
            {
                
                SumSpin=0; 
                while (Check==1)
                {
                    if(SpinRecord[CurrentSpin*2]<0)
                    {
                        if(CurrentSpin%2==0)
                        {
                            footSpin=CurrentSpin+1;                     
                        }
                        else
                        {
                            footSpin=CurrentSpin-1; 
                        }
                    }
                    else
                    {
                        footSpin=CurrentSpin+FootTemp[CurrentSpin%4];
                       
                    }
        /*
        if(SpinRecord[LoopNumA]>-1)
        { 
            StartSpin=LoopNumA;
            CurrentSpin=LoopNumA;
            Check=1;
            if(genrand64_real2()<Chance)
            {
                SumSpin=0; 
                while (Check==1)
                {
                    if(CurrentSpin%2==0)
                    {
                        footSpin=CurrentSpin+1;                     
                    }
                    else
                    {
                        footSpin=CurrentSpin-1; 
                    }
        */            
                    HopNO = ((long long)(CurrentSpin/12)*7);
                    SwitchNO = (long long)((CurrentSpin%12)/4);
                    //printf("%d %d %d\n",Hoperator[(long long)(CurrentSpin/12)*7]%15,CurrentSpin%12,(long long)(CurrentSpin%12/4));
                    
                    switch(Hoperator[HopNO]%15)//1091002 修正
                    {
                        case 0:
                           Hoperator[HopNO]+=1;
                           break;
                        case 1:
                           Hoperator[HopNO]-=1;
                           break;
                        case 2:
              
                            switch(SwitchNO)
                            {
                                case 0:
                                    Hoperator[HopNO]+=3;
                                    break;
                                case 1:
                                    Hoperator[HopNO]+=4;
                                    break;
                                case 2:
                                    Hoperator[HopNO]+=5;
                                    break;
                          
                            }
                            break;

                        case 5:
                            switch(SwitchNO)
                            {
                                case 0:
                                    Hoperator[HopNO]-=3;
                                    break;
                                case 1:
                                    Hoperator[HopNO]+=4;
                                    break;
                                case 2:
                                    Hoperator[HopNO]+=5;
                                    break;
                            }
                            break;
                        case 6:
                            switch(SwitchNO)
                            {
                                case 0:
                                    Hoperator[HopNO]+=3;
                                    break;
                                case 1:
                                    Hoperator[HopNO]-=4;
                                    break;
                                case 2:
                                    Hoperator[HopNO]+=5;
                                    break;
                            }
                            break;        
                        case 7:
                            switch(SwitchNO)
                            {
                                case 0:
                                    Hoperator[HopNO]+=3;
                                    break;
                                case 1:
                                    Hoperator[HopNO]+=4;
                                    break;
                                case 2:
                                    Hoperator[HopNO]-=5;
                                    break;
                            }
                            break;
                        case 9:
                            switch(SwitchNO)
                            {
                                case 0:
                                    Hoperator[HopNO]-=3;
                                    break;
                                case 1:
                                    Hoperator[HopNO]-=4;
                                    break;
                                case 2:
                                    Hoperator[HopNO]+=5;
                                    break;
                            }
                            break;
                        case 10:
                            switch(SwitchNO)
                            {
                                case 0:
                                    Hoperator[HopNO]-=3;
                                    break;
                                case 1:
                                    Hoperator[HopNO]+=4;
                                    break;
                                case 2:
                                    Hoperator[HopNO]-=5;
                                    break;
                            }
                            break;
                        case 11:
                            switch(SwitchNO)
                            {
                                case 0:
                                    Hoperator[HopNO]+=3;
                                    break;
                                case 1:
                                    Hoperator[HopNO]-=4;
                                    break;
                                case 2:
                                    Hoperator[HopNO]-=5;
                                    break;
                            }
                            break;
                        case 14:
                            switch(SwitchNO)
                            {
                                case 0:
                                    Hoperator[HopNO]-=3;
                                    break;
                                case 1:
                                    Hoperator[HopNO]-=4;
                                    break;
                                case 2:
                                    Hoperator[HopNO]-=5;
                                    break;  
                            }
                            break;                           
                    }
                    

                    SpinRecord[CurrentSpin*2+1]=-1;
                    CurrentSpin=SpinRecord[footSpin*2+1];
                    SpinRecord[footSpin*2+1]=-1;
                    SingleFoot=footSpin%12;
                    HSpin=Hoperator[(long long)(footSpin/12*7)+2*(long long)(SingleFoot/4)+SingleFoot%2+1];//請Hoperator內Spin的index

                    if(footSpin%4<2)
                    {
                        //printf("%f \n",SpinSystem[HSpin*3+1]);
                        if(FirstSpin[HSpin]==footSpin)
                        {
                           SumSpin+=SpinSystem[HSpin*3+1];
                           //printf("%f \n",SpinSystem[Hoperator[footSpin/8*5+2*SingleFoot/4+SingleFoot%2+1]*3+1]);
                           //SumSpin+=SpinSystem[Hoperator[CurrentSpin/8*5+SingleCurrent/4+SingleCurrent%2]*3+1]
                            
                        }
                    }
                    else
                    {
                        if(LastSpin[HSpin]==footSpin)
                        {
                           SumSpin+=SpinSystem[HSpin*3+1];
                           //SumSpin+=SpinSystem[Hoperator[CurrentSpin/8*5+SingleCurrent/4+SingleCurrent%2]*3+1]
                            
                        }
                        
                    }
                    
                    if(CurrentSpin==StartSpin)
                    {
                        Check=0;
                    }
                    //printf("loop x1 CurrentSpin %d footSpin %d\n",CurrentSpin,footSpin);
                }
                TempW+=SumSpin*SumSpin*0.25;
            }
            else
            {
                SumSpin=0;
                while(Check==1)
                {
                    if(SpinRecord[CurrentSpin*2]<0)
                    {
                        if(CurrentSpin%2==0)
                        {
                            footSpin=CurrentSpin+1;                     
                        }
                        else
                        {
                            footSpin=CurrentSpin-1; 
                        }
                    }
                    else
                    {
                        footSpin=CurrentSpin+FootTemp[CurrentSpin%4];
                       
                    }                    
                    /*               
                    
                    if(CurrentSpin%2==0)
                    {
                        footSpin=CurrentSpin+1;                     
                    }
                    else
                    {
                        footSpin=CurrentSpin-1; 
                    }
                    */
                    SpinRecord[CurrentSpin*2+1]=-2;
                    CurrentSpin=SpinRecord[footSpin*2+1];
                    SpinRecord[footSpin*2+1]=-2;
                    SingleFoot=footSpin%12;
                    HSpin=Hoperator[(long long)(footSpin/12*7)+2*(long long)(SingleFoot/4)+SingleFoot%2+1];

                    //printf("%d \n",HSpin);
                    if(footSpin%4<2)
                    {
                        if(FirstSpin[HSpin]==footSpin)
                        {
                           SumSpin+=SpinSystem[HSpin*3+1];
                           //SumSpin+=SpinSystem[Hoperator[CurrentSpin/8*5+SingleCurrent/4+SingleCurrent%2]*3+1]
                            
                        }
                    }
                    else
                    {
                        if(LastSpin[HSpin]==footSpin)
                        {
                           SumSpin+=SpinSystem[HSpin*3+1];
                           //SumSpin+=SpinSystem[Hoperator[CurrentSpin/8*5+SingleCurrent/4+SingleCurrent%2]*3+1]
                            
                        }
                        
                    }
                    
                    if(CurrentSpin==StartSpin)
                    {
                        Check=0;
                    }
                    //printf("loop x-1 CurrentSpin %d footSpin %d\n",CurrentSpin,footSpin);      
                }
                TempW+=SumSpin*SumSpin*0.25;
          
            }
        }
        
    }
    //printf("%f \n",TempW);
    //printf("loop 1 \n");   
    for(LoopNumA=0;LoopNumA<SpinNO;LoopNumA+=1)
    {
        SpinNumber_NO=LoopNumA*3;
        if(FirstSpin[LoopNumA]!=-1)
        {
            if(SpinRecord[FirstSpin[LoopNumA]*2+1]==-1)
            {
                SpinSystem[SpinNumber_NO+1]*=-1;
            }
        }
        else
        {
            //Goal=genrand64_real2();
            if(genrand64_real2()<Chance)
            {
                SpinSystem[SpinNumber_NO+1]*=-1; 
            }
            TempW+=SpinSystem[SpinNumber_NO+1]*SpinSystem[SpinNumber_NO+1]*0.25;
        }
    }
    //printf("loop end \n");
    //*SpinRecord= NULL,*FirstSpin= NULL,*LastSpin= NULL,*HSpinLR = NULL, *SpinNumber=NULL, *FootTemp=NULL;
    free(SpinRecord);
    free(FirstSpin);
    free(LastSpin);
    free(HSpinLR);
    free(SpinNumber);
    free(FootTemp);
    SpinRecord=NULL;
    FirstSpin=NULL;
    LastSpin=NULL;
    HSpinLR=NULL;
    SpinNumber=NULL;
    FootTemp=NULL;
    
}
void LoopUpdateJQ3_Spin1(double* SpinSystem,double* BondNOsystem,\
                    long long* Hoperator,long long &HNO,\
                    long long &SpinNO,long long &BondNO,long long &HoperatorNO,\
                    double &TempW,long long* BondNORecord)
{
    long long LoopNumA,LoopNumB,LoopNumC,LoopNumD;
    long long LeftSpin,RightSpin,LeftSpin2,RightSpin2,LeftSpin3,RightSpin3;
    long long *SpinRecord= NULL,*FirstSpin= NULL,*LastSpin= NULL,*HSpinLR = NULL, *SpinNumber=NULL, *FootTemp=NULL;
    long long StartSpin,HopNO,HSpin,SwitchNO,SpinNumber_NO;
    long long CurrentSpin,footSpin,Check,Hop,HLeft,HRight,HLeft2,HRight2,HLeft3,HRight3,SingleFoot,SingleCurrent;
    double Chance,Goal,SumSpin;
    //srand(time(NULL)*rand());
    //printf("test LoopUpdate-memset start");
    SpinRecord=(long long *)malloc((HoperatorNO*2*12+1)*sizeof(long long*));
    FirstSpin=(long long *)malloc((SpinNO+1)*sizeof(long long*));
    LastSpin=(long long *)malloc((SpinNO+1)*sizeof(long long*));
    HSpinLR=(long long *)malloc((6*2+1)*sizeof(long long*));//每個Spin都記是否為Ferromagnetic
    SpinNumber=(long long *)malloc((3+1)*sizeof(long long*));
    FootTemp=(long long *)malloc((4+1)*sizeof(long long*));
    memset(SpinRecord,-1,(HoperatorNO*2*12)*sizeof(long long*));
    memset(FirstSpin,-1,SpinNO*sizeof(long long*));
    memset(LastSpin,-1,SpinNO*sizeof(long long*));
    
    memset(SpinNumber,-1,3*sizeof(long long*));
    memset(FootTemp,-1,(4+1)*sizeof(long long*));
    FootTemp[0]=3;
    FootTemp[1]=1;
    FootTemp[2]=-1;
    FootTemp[3]=-3;
    //printf("test LoopUpdate-memset end");
    //SpinRecord[HoperatorNO*12+1]=-999;
    //FirstSpin[SpinNO]=-999;
    //LastSpin[SpinNO]=-999;
    Chance=0.50;
    //建構vertex operator的腳
    //printf("vertex \n");
    //printf("Check Loop-0\n");
    for (LoopNumA=0;LoopNumA<HoperatorNO*7;LoopNumA+=7)
    {
        memset(HSpinLR,-1,(6*2)*sizeof(long long*));
        //printf("HoperatorNO=%d,LoopNumA=%d \n",HoperatorNO,LoopNumA);
        //printf("Hop=%d,HLeft=%d,HRight=%d,HLeft2=%d,HRight2=%d \n",Hoperator[LoopNumA],Hoperator[LoopNumA+1],Hoperator[LoopNumA+2],Hoperator[LoopNumA+3],Hoperator[LoopNumA+4]);
        //printf("Check Loop-1\n");
        Hop=Hoperator[LoopNumA];
        if (BondNORecord[((long long)(Hop/15))*7]>-1)
        {
            if(BondNORecord[((long long)(Hop/15))*7]==0)
            {
                HSpinLR[0] = BondNORecord[((long long)(Hop/15))*7];
                HSpinLR[2] = BondNORecord[((long long)(Hop/15))*7];  
                //printf("%d %d \n",HSpinLR[0],HSpinLR[2]);  
            }
            else
            {
                HSpinLR[(BondNORecord[((long long)(Hop/15))*7]-1)*2]= BondNORecord[((long long)(Hop/15))*7];
                HSpinLR[(BondNORecord[((long long)(Hop/15))*7]-1)*2+2]= BondNORecord[((long long)(Hop/15))*7];
            }
              
        }
        for(LoopNumB=0;LoopNumB<6;LoopNumB+=1)
        {
          

          HSpinLR[LoopNumB*2+1] = Hoperator[LoopNumA+LoopNumB+1];

        }        
        
        //printf("Check Loop-2\n");
        /*
        HLeft=Hoperator[LoopNumA+1];
        HRight=Hoperator[LoopNumA+2];
        HLeft2=Hoperator[LoopNumA+3];
        HRight2=Hoperator[LoopNumA+4];
        HLeft3=Hoperator[LoopNumA+5];
        HRight3=Hoperator[LoopNumA+6];
        */
        for(LoopNumB = 0 ; LoopNumB < 3 ; LoopNumB+=1)
        {
            SpinNumber[LoopNumB] = ((long long)(LoopNumA/7))*12+4*LoopNumB;
        }
        /*
        SpinNumber=(long long)(LoopNumA/7)*12;
        SpinNumber2=(long long)(LoopNumA/7)*12+4;
        SpinNumber3=(long long)(LoopNumA/7)*12+8;
        */
        
        //Q3 0-3第一個pair 4-7 第二個pair 8-11第三個pair  
        if(Hop!=-1)
        {
            //printf("Check Loop-3\n");
            //printf("%d , %d\n",Hop,Hop%10); 
            if(Hop%15<2)
            {
                //printf("Check Loop-4-1\n");
                //printf("%d , %d\n",Hop,Hop%10);
                //LeftSpin=LastSpin[HLeft];
                //RightSpin=LastSpin[HRight];
                if(HSpinLR[0] >-1)
                {
                    for(LoopNumB=0 ; LoopNumB < 2 ; LoopNumB+=1)
                    {
                        SpinRecord[(SpinNumber[0]+LoopNumB)*2]=HSpinLR[LoopNumB*2];
                        SpinRecord[(SpinNumber[0]+LoopNumB+2)*2]=HSpinLR[LoopNumB*2]; 
                    }
                        
                                        
                } 
                //printf("Check Loop-4-2\n");
                
                for(LoopNumB=0 ; LoopNumB < 2 ; LoopNumB+=1)
                {
                    if(LastSpin[HSpinLR[LoopNumB*2+1]]!=-1)
                    {
                        //printf("Check Loop-4-2-1\n");
                        SpinRecord[(SpinNumber[0]+LoopNumB)*2+1]=LastSpin[HSpinLR[LoopNumB*2+1]];
                        
                        SpinRecord[LastSpin[HSpinLR[LoopNumB*2+1]]*2+1]=SpinNumber[0]+LoopNumB;
                        //printf("%3d %3d \n",SpinRecord[(SpinNumber[0]+LoopNumB)*2+1], SpinRecord[LastSpin[HSpinLR[LoopNumB*2+1]]*2+1]);
                        /*
                        if(HSpinLR[LoopNumB*2] !=-1)
                        {
                           //printf("Spin1");
                           SpinRecord[(SpinNumber[0]+LoopNumB)*2]=HSpinLR[LoopNumB*2];
                           ///SpinRecord[LastSpin[HSpinLR[LoopNumB*2+1]]*2]=HSpinLR[LoopNumB*2];
                        }
                        */
                        //printf("Check Loop-4-2-2\n");
                        
                    }
                    else
                    {
                        FirstSpin[HSpinLR[LoopNumB*2+1]]=SpinNumber[0]+LoopNumB ;
                        /*
                        if(HSpinLR[LoopNumB*2] >-1)
                        {
                           //printf("Spin1");
                           SpinRecord[(SpinNumber[0]+LoopNumB)*2]=HSpinLR[LoopNumB*2];
                           SpinRecord[(SpinNumber[0]+LoopNumB+2)*2]=HSpinLR[LoopNumB*2];
                        }
                        */                        
                    }
                    LastSpin[HSpinLR[LoopNumB*2+1]]=SpinNumber[0]+2+LoopNumB;
                }
                //printf("Check Loop-4-3\n");
                /*
                if(LeftSpin!=-1)
                {
                    SpinRecord[SpinNumber]=LeftSpin;
                    SpinRecord[LeftSpin]=SpinNumber;
                }
                else
                {
                    FirstSpin[HLeft]=SpinNumber;
                }
                if(RightSpin!=-1)
                {
                    SpinRecord[SpinNumber+1]=RightSpin;
                    SpinRecord[RightSpin]=SpinNumber+1;
                }
                else
                {
                    FirstSpin[HRight]=SpinNumber+1;
                }
                
                LastSpin[HLeft]=SpinNumber+2;
                LastSpin[HRight]=SpinNumber+3; 
                */               
            }
            else//JQBond
            {
                //printf("Check Loop-5-1\n");
                for(LoopNumC=0 ; LoopNumC < 3 ; LoopNumC+=1)
                {    
                    if(HSpinLR[LoopNumC*4] >-1)
                    {
                        for(LoopNumB=0 ; LoopNumB < 2 ; LoopNumB+=1)
                        {
                            SpinRecord[(SpinNumber[LoopNumC]+LoopNumB)*2]=HSpinLR[LoopNumC*4];
                            SpinRecord[(SpinNumber[LoopNumC]+LoopNumB+2)*2]=HSpinLR[LoopNumC*4];  
                        }
                    }
                }   
                
                //printf("Check Loop-5-2\n");
                for(LoopNumC=0 ; LoopNumC < 3 ; LoopNumC+=1)
                {
                    for(LoopNumB=0 ; LoopNumB < 2 ; LoopNumB+=1)
                    {
                        if(LastSpin[HSpinLR[LoopNumB*2+LoopNumC*4+1]]!=-1)
                        {
                            SpinRecord[(SpinNumber[LoopNumC]+LoopNumB)*2+1]=LastSpin[HSpinLR[LoopNumB*2+LoopNumC*4+1]];
                            SpinRecord[LastSpin[HSpinLR[LoopNumB*2+LoopNumC*4+1]]*2+1]=SpinNumber[LoopNumC]+LoopNumB;
                            //printf("%3d %3d \n",SpinRecord[(SpinNumber[LoopNumC]+LoopNumB)*2+1],SpinRecord[LastSpin[HSpinLR[LoopNumB*2+LoopNumC*4+1]]*2+1]);
                            /*
                            if(HSpinLR[LoopNumB*2+LoopNumC*4]!=-1)
                            {
                               //printf("Spin1");
                               SpinRecord[(SpinNumber[LoopNumC]+LoopNumB)*2]=HSpinLR[LoopNumB*2+LoopNumC*4];
                               //SpinRecord[LastSpin[HSpinLR[LoopNumB*2+LoopNumC*4+1]]*2]=HSpinLR[LoopNumB*2+LoopNumC*4];
                            }
                            * */
                        }
                        else
                        {
                            FirstSpin[HSpinLR[LoopNumB*2+LoopNumC*4+1]]=SpinNumber[LoopNumC]+LoopNumB ;
                            /*
                            if(HSpinLR[LoopNumB*2+LoopNumC*4]>-1)
                            {
                               //printf("Spin1");
                               SpinRecord[(SpinNumber[LoopNumC]+LoopNumB)*2]=HSpinLR[LoopNumB*2+LoopNumC*4];
                               SpinRecord[(SpinNumber[LoopNumC]+LoopNumB+2)*2]=HSpinLR[LoopNumB*2+LoopNumC*4];
                            }
                            */                            
                        }
                        LastSpin[HSpinLR[LoopNumB*2+LoopNumC*4+1]]=SpinNumber[LoopNumC]+2+LoopNumB;
                    }                    
                    
                }
                //printf("Check Loop-5-3\n");

                /*           
                LeftSpin=LastSpin[HLeft];
                RightSpin=LastSpin[HRight];
                LeftSpin2=LastSpin[HLeft2];
                RightSpin2=LastSpin[HRight2];
                LeftSpin3=LastSpin[HLeft3];
                RightSpin3=LastSpin[HRight3];
                
                
                if(LeftSpin!=-1)
                {
                    
                    SpinRecord[SpinNumber]=LeftSpin;
                    SpinRecord[LeftSpin]=SpinNumber;
    
                }
                else
                {
                    FirstSpin[HLeft]=SpinNumber;
                }
                if(RightSpin!=-1)
                {
                    SpinRecord[SpinNumber+1]=RightSpin;
                    SpinRecord[RightSpin]=SpinNumber+1;
                }
                else
                {
                    FirstSpin[HRight]=SpinNumber+1;
                }
                //QBond~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                
                if(LeftSpin2!=-1)
                {
                    SpinRecord[SpinNumber2]=LeftSpin2;
                    SpinRecord[LeftSpin2]=SpinNumber2;
                }
                else
                {
                    FirstSpin[HLeft2]=SpinNumber2;
                }
                if(RightSpin2!=-1)
                {
                    SpinRecord[SpinNumber2+1]=RightSpin2;
                    SpinRecord[RightSpin2]=SpinNumber2+1;
                }
                else
                {
                    FirstSpin[HRight2]=SpinNumber2+1;
                }
                           
                if(LeftSpin3!=-1)
                {
                    SpinRecord[SpinNumber3]=LeftSpin3;
                    SpinRecord[LeftSpin3]=SpinNumber3;
                }
                else
                {
                    FirstSpin[HLeft3]=SpinNumber3;
                }
                if(RightSpin3!=-1)
                {
                    SpinRecord[SpinNumber3+1]=RightSpin3;
                    SpinRecord[RightSpin3]=SpinNumber3+1;
                }
                else
                {
                    FirstSpin[HRight3]=SpinNumber3+1;
                }                  
                LastSpin[HLeft]=SpinNumber+2;
                LastSpin[HRight]=SpinNumber+3;
                LastSpin[HLeft2]=SpinNumber2+2;
                LastSpin[HRight2]=SpinNumber2+3;
                LastSpin[HLeft3]=SpinNumber3+2;
                LastSpin[HRight3]=SpinNumber3+3;  
                */
            }
 
        }
        else
        {
            continue;
            /*
            for(LoopNumB=0;LoopNumB<12;LoopNumB+=1)
            {

                SpinRecord[(SpinNumber[0]+LoopNumB)*2]=-1;
            }
            */
            
        }
    }

    for(LoopNumA=0;LoopNumA<SpinNO;LoopNumA+=1)
    {
        if(FirstSpin[LoopNumA]!=-1)
        {
            SpinRecord[FirstSpin[LoopNumA]*2+1]=LastSpin[LoopNumA];
            SpinRecord[LastSpin[LoopNumA]*2+1]=FirstSpin[LoopNumA];
        }
        
    }
    /*
    for(LoopNumA=0;LoopNumA <HoperatorNO*12;LoopNumA=LoopNumA+12)
    {
        //printf("%2d ,H=%3d  ,L=%3d  ,R=%3d \n",LoopNumA/3, Hoperator[LoopNumA], Hoperator[LoopNumA+1], Hoperator[LoopNumA+2]);
        
        if(Hoperator[(long long)LoopNumA/12*7]!=-1)
        {
            printf("%2d  ",LoopNumA/12) ;
            for(LoopNumB=0;LoopNumB <12;LoopNumB+=1)
            {
                printf("%4d[%4d]%d ",LoopNumA+LoopNumB,SpinRecord[LoopNumA*2+LoopNumB*2+1],SpinRecord[LoopNumA*2+LoopNumB*2]);
          
            }
        }
        printf("\n ") ;
    }
    system("pause");
    */
    /*    
    for(LoopNumA=0;LoopNumA<SpinNO;LoopNumA+=1)
    {
        if(FirstSpin[LoopNumA]!=-1)
        {
            SpinRecord[FirstSpin[LoopNumA]]=LastSpin[LoopNumA];
            SpinRecord[LastSpin[LoopNumA]]=FirstSpin[LoopNumA];
        }
        
    }
    */
    //printf("Check Loop-6\n");
    for(LoopNumA=0;LoopNumA<HoperatorNO*12;LoopNumA+=4)//4為一個operator幾個腳，在這邊Q會4*3，半邊半邊算
    {
        //printf("%d \n",LoopNumA);
        if(SpinRecord[LoopNumA*2+1]>-1)
        { 
            
            StartSpin=LoopNumA;
            CurrentSpin=LoopNumA;
            Check=1;
            if(genrand64_real2()<Chance)
            {
                //printf("Check Loop-6-1\n");
                SumSpin=0; 
                while (Check==1)
                {
                    //printf("Check Loop-6-1\n");
                    //printf("SpinType %2d CurrentSpin=%3d \n",SpinRecord[CurrentSpin*2],CurrentSpin);
                    if(SpinRecord[CurrentSpin*2]<0)
                    {
                        
                        if(CurrentSpin%2==0)
                        {
                            footSpin=CurrentSpin+1;                     
                        }
                        else
                        {
                            footSpin=CurrentSpin-1; 
                        }
                    }
                    else
                    {
                        //printf("SpinType %2d CurrentSpin=%3d \n",SpinRecord[CurrentSpin*2],CurrentSpin);
                        footSpin=CurrentSpin+FootTemp[CurrentSpin%4];
                        //printf("SpinType %2d footSpin=%3d \n",SpinRecord[footSpin*2],footSpin);
                    }
                    ///printf("SpinType %2d footSpin=%3d \n",SpinRecord[footSpin*2],footSpin);
        /*
        if(SpinRecord[LoopNumA]>-1)
        { 
            StartSpin=LoopNumA;
            CurrentSpin=LoopNumA;
            Check=1;
            if(genrand64_real2()<Chance)
            {
                SumSpin=0; 
                while (Check==1)
                {
                    if(CurrentSpin%2==0)
                    {
                        footSpin=CurrentSpin+1;                     
                    }
                    else
                    {
                        footSpin=CurrentSpin-1; 
                    }
        */            
                    HopNO = (((long long)(CurrentSpin/12))*7);
                    SwitchNO = ((long long)((CurrentSpin%12)/4));
                    //printf("%d %d %d\n",HopNO,Hoperator[HopNO]%15,SwitchNO);
                    
                    switch(Hoperator[HopNO]%15)//1091002 修正
                    {
                        case 0:
                           Hoperator[HopNO]+=1;
                           break;
                        case 1:
                           Hoperator[HopNO]-=1;
                           break;
                        case 2:
              
                            switch(SwitchNO)
                            {
                                case 0:
                                    Hoperator[HopNO]+=3;
                                    break;
                                case 1:
                                    Hoperator[HopNO]+=4;
                                    break;
                                case 2:
                                    Hoperator[HopNO]+=5;
                                    break;
                          
                            }
                            break;

                        case 5:
                            switch(SwitchNO)
                            {
                                case 0:
                                    Hoperator[HopNO]-=3;
                                    break;
                                case 1:
                                    Hoperator[HopNO]+=4;
                                    break;
                                case 2:
                                    Hoperator[HopNO]+=5;
                                    break;
                            }
                            break;
                        case 6:
                            switch(SwitchNO)
                            {
                                case 0:
                                    Hoperator[HopNO]+=3;
                                    break;
                                case 1:
                                    Hoperator[HopNO]-=4;
                                    break;
                                case 2:
                                    Hoperator[HopNO]+=5;
                                    break;
                            }
                            break;        
                        case 7:
                            switch(SwitchNO)
                            {
                                case 0:
                                    Hoperator[HopNO]+=3;
                                    break;
                                case 1:
                                    Hoperator[HopNO]+=4;
                                    break;
                                case 2:
                                    Hoperator[HopNO]-=5;
                                    break;
                            }
                            break;
                        case 9:
                            switch(SwitchNO)
                            {
                                case 0:
                                    Hoperator[HopNO]-=3;
                                    break;
                                case 1:
                                    Hoperator[HopNO]-=4;
                                    break;
                                case 2:
                                    Hoperator[HopNO]+=5;
                                    break;
                            }
                            break;
                        case 10:
                            switch(SwitchNO)
                            {
                                case 0:
                                    Hoperator[HopNO]-=3;
                                    break;
                                case 1:
                                    Hoperator[HopNO]+=4;
                                    break;
                                case 2:
                                    Hoperator[HopNO]-=5;
                                    break;
                            }
                            break;
                        case 11:
                           // printf("+++++++ %d %d %d\n",HopNO,Hoperator[HopNO]%15,SwitchNO);
                            switch(SwitchNO)
                            {
                                
                                case 0:
                                    Hoperator[HopNO]+=3;
                                    break;
                                case 1:
                                    Hoperator[HopNO]-=4;
                                    break;
                                case 2:
                                    Hoperator[HopNO]-=5;
                                    break;
                            }
                            break;
                        case 14:
                            switch(SwitchNO)
                            {
                                case 0:
                                    Hoperator[HopNO]-=3;
                                    break;
                                case 1:
                                    Hoperator[HopNO]-=4;
                                    break;
                                case 2:
                                    Hoperator[HopNO]-=5;
                                    break;  
                            }
                            break;                           
                    }
                    
                    SpinRecord[CurrentSpin*2]=-1;
                    SpinRecord[CurrentSpin*2+1]=-1;
                    
                    CurrentSpin=SpinRecord[footSpin*2+1];
                    SpinRecord[footSpin*2]=-1;
                    SpinRecord[footSpin*2+1]=-1;
                    //printf("SpinType %2d CurrentSpin=%3d \n",SpinRecord[CurrentSpin*2],CurrentSpin);
                    /*
                    SingleFoot=footSpin%12;
                    HSpin=Hoperator[(long long)(footSpin/12*7)+2*(long long)(SingleFoot/4)+SingleFoot%2+1];//請Hoperator內Spin的index

                    if(footSpin%4<2)
                    {
                        //printf("%f \n",SpinSystem[HSpin*3+1]);
                        if(FirstSpin[HSpin]==footSpin)
                        {
                           SumSpin+=SpinSystem[HSpin*3+1];
                           //printf("%f \n",SpinSystem[Hoperator[footSpin/8*5+2*SingleFoot/4+SingleFoot%2+1]*3+1]);
                           //SumSpin+=SpinSystem[Hoperator[CurrentSpin/8*5+SingleCurrent/4+SingleCurrent%2]*3+1]
                            
                        }
                    }
                    else
                    {
                        if(LastSpin[HSpin]==footSpin)
                        {
                           SumSpin+=SpinSystem[HSpin*3+1];
                           //SumSpin+=SpinSystem[Hoperator[CurrentSpin/8*5+SingleCurrent/4+SingleCurrent%2]*3+1]
                            
                        }
                        
                    }
                    */
                    if(CurrentSpin==StartSpin)
                    {
                        Check=0;
                    }
                    //printf("loop x1 CurrentSpin %d footSpin %d\n",CurrentSpin,footSpin);
                }
                //TempW+=SumSpin*SumSpin*0.25;
            }
            else
            {
                //printf("Check Loop-6-2\n");
                SumSpin=0;
                while(Check==1)
                {
                    //printf("Check Loop-6-2\n");
                    //printf("SpinType %2d CurrentSpin=%3d \n",SpinRecord[CurrentSpin*2],CurrentSpin);
                    if(SpinRecord[CurrentSpin*2]<0)
                    {
                        if(CurrentSpin%2==0)
                        {
                            footSpin=CurrentSpin+1;                     
                        }
                        else
                        {
                            footSpin=CurrentSpin-1; 
                        }
                    }
                    else
                    {
                        footSpin=CurrentSpin+FootTemp[CurrentSpin%4];
                       
                    }
                    //printf("Check Loop-6-2-1\n");
                    //printf("SpinType %2d footSpin=%3d \n",SpinRecord[footSpin*2],footSpin);                    
                    /*               
                    
                    if(CurrentSpin%2==0)
                    {
                        footSpin=CurrentSpin+1;                     
                    }
                    else
                    {
                        footSpin=CurrentSpin-1; 
                    }
                    */
                    SpinRecord[CurrentSpin*2]=-1;
                    SpinRecord[CurrentSpin*2+1]=-2;
                    
                    CurrentSpin=SpinRecord[footSpin*2+1];
                    SpinRecord[footSpin*2]=-1;
                    SpinRecord[footSpin*2+1]=-2;
                   /// printf("Check Loop-6-2-2\n");
                    /*
                    SingleFoot=footSpin%12;
                    HSpin=Hoperator[(long long)(footSpin/12*7)+2*(long long)(SingleFoot/4)+SingleFoot%2+1];

                    //printf("%d \n",HSpin);
                    if(footSpin%4<2)
                    {
                        if(FirstSpin[HSpin]==footSpin)
                        {
                           SumSpin+=SpinSystem[HSpin*3+1];
                           //SumSpin+=SpinSystem[Hoperator[CurrentSpin/8*5+SingleCurrent/4+SingleCurrent%2]*3+1]
                            
                        }
                    }
                    else
                    {
                        if(LastSpin[HSpin]==footSpin)
                        {
                           SumSpin+=SpinSystem[HSpin*3+1];
                           //SumSpin+=SpinSystem[Hoperator[CurrentSpin/8*5+SingleCurrent/4+SingleCurrent%2]*3+1]
                            
                        }
                        
                    }
                    */
                    if(CurrentSpin==StartSpin)
                    {
                        Check=0;
                    }
                    //printf("loop x-1 CurrentSpin %d footSpin %d\n",CurrentSpin,footSpin);      
                }
                //TempW+=SumSpin*SumSpin*0.25;
          
            }
        }
        
    }
    ///printf("Check Loop-7\n");
    //printf("%f \n",TempW);
    //printf("loop 1 \n");   
    for(LoopNumA=0;LoopNumA<SpinNO;LoopNumA+=1)
    {
        SpinNumber_NO=LoopNumA*3;
        if(FirstSpin[LoopNumA]!=-1)
        {
            if(SpinRecord[FirstSpin[LoopNumA]*2+1]==-1)
            {
                SpinSystem[SpinNumber_NO+1]*=-1;
            }
        }
        else
        {
            //Goal=genrand64_real2();
            if(genrand64_real2()<Chance)
            {
                SpinSystem[SpinNumber_NO+1]*=-1; 
            }
            //TempW+=SpinSystem[SpinNumber_NO+1]*SpinSystem[SpinNumber_NO+1]*0.25;
        }
    }
    //printf("loop end \n");
    //*SpinRecord= NULL,*FirstSpin= NULL,*LastSpin= NULL,*HSpinLR = NULL, *SpinNumber=NULL, *FootTemp=NULL;
    free(SpinRecord);
    free(FirstSpin);
    free(LastSpin);
    free(HSpinLR);
    free(SpinNumber);
    free(FootTemp);
    SpinRecord=NULL;
    FirstSpin=NULL;
    LastSpin=NULL;
    HSpinLR=NULL;
    SpinNumber=NULL;
    FootTemp=NULL;
    
}
long long AddHoperator(long long** Hoperator,long long &HNO,long long &HoperatorNO,long long &CurrentT)
{
    long long OldLenth,LoopNumA,Check,NewLenth,*Temp,*Temp1;
    double c,multiple;
    //if((double)HNO/(double)(len(*Hoperator)/3)>=0.8)
    //{
    //printf("d \n");
    multiple=1.33333;
    //printf("%d \n",HoperatorNO);
    OldLenth=HoperatorNO*3;
    NewLenth=(long long)(HNO*multiple);
    NewLenth*=3;
    if(NewLenth<=HoperatorNO*3)
    {
        return 0;
    }
    else
    {
        HoperatorNO=NewLenth/3;
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
long long AddHoperatorJQ3(long long** Hoperator,long long &HNO,long long &HoperatorNO,long long &CurrentT)
{
    long long OldLenth,LoopNumA,Check,NewLenth,*Temp,*Temp1;
    double c,multiple;
    //if((double)HNO/(double)(len(*Hoperator)/3)>=0.8)
    //{
    //printf("d \n");
    multiple=1.33333;
    //printf("%d \n",HoperatorNO);
    OldLenth=HoperatorNO*7;
    NewLenth=(long long)(HNO*multiple)*7;
    //NewLenth*=7;
    if(NewLenth<=HoperatorNO*7)
    {
        return 0;
    }
    else
    {
        HoperatorNO=NewLenth/7;
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
        //(*Hoperator)[NewLenth]=-999;
        free(Temp);
        return 0;
    }
    //printf("%d \n",len(*Hoperator));
   // }
    
}

void MeasureFuct(double* SpinSystem,double* BondNOsystem,long long* Hoperator\
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
            SpinSystem[Hoperator[LoopNumA+1]*3+1]*=(-1.0);
            SpinSystem[Hoperator[LoopNumA+2]*3+1]*=(-1.0);
            SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+1]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+1]*3]);
            //SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+1]*3+1]*(double)pow( -1.0 , (long long)Hoperator[LoopNumA+1]%Size+(long long)Hoperator[LoopNumA+1]/Size ) );
            Widding[((Hoperator[LoopNumA]-1)/2)/SpinNO]+=(double)SpinSystem[Hoperator[LoopNumA+2]*3+1];
           
        }
        /*
        SingleAX1+=(double)SingleAFM;
        SingleAFM1+=(double)abs((long long)SingleAFM);
        SingleAFM2+=(double)pow(SingleAFM,2);
        SingleAFM4+=(double)pow(SingleAFM,4);
        SingleAFM6+=(double)pow(SingleAFM,6);
        */
        SingleAX1+=(double)SingleAFM;
        SingleAFM1+=(double)abs((long long)SingleAFM);
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
        SingleAFM1=(double)abs((long long)SingleAFM);
        SingleAFM2=(double)pow(SingleAFM,2);
        SingleAFM4=(double)pow(SingleAFM,4);
        SingleAFM6=(double)pow(SingleAFM,6);
        SingleAX1=(double)SingleAFM2;
        */
        SingleAFM1=(double)abs((long long)SingleAFM);
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

void MeasureFuctJQ2(double* SpinSystem,double* BondNOsystem,long long* Hoperator\
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
                    SpinSystem[Hoperator[LoopNumA+1]*3+1]*=(-1.0);
                    SpinSystem[Hoperator[LoopNumA+2]*3+1]*=(-1.0);
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+1]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+1]*3]);
                    Widding[((Hoperator[LoopNumA]-1)/10)/SpinNO]+=(double)SpinSystem[Hoperator[LoopNumA+2]*3+1];
                    break;
                case 5:
                    SpinSystem[Hoperator[LoopNumA+1]*3+1]*=(-1.0);
                    SpinSystem[Hoperator[LoopNumA+2]*3+1]*=(-1.0);
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+1]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+1]*3]);
                    Widding[((Hoperator[LoopNumA]-5)/10)/SpinNO]+=(double)SpinSystem[Hoperator[LoopNumA+2]*3+1];
                    break;
                case 6:
                    SpinSystem[Hoperator[LoopNumA+3]*3+1]*=(-1.0);
                    SpinSystem[Hoperator[LoopNumA+4]*3+1]*=(-1.0);
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+3]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+3]*3]);
                    Widding[((Hoperator[LoopNumA]-6)/10)/SpinNO]+=(double)SpinSystem[Hoperator[LoopNumA+4]*3+1];
                    break;
                
                case 9:
                    SpinSystem[Hoperator[LoopNumA+1]*3+1]*=(-1.0);
                    SpinSystem[Hoperator[LoopNumA+2]*3+1]*=(-1.0);
                    SpinSystem[Hoperator[LoopNumA+3]*3+1]*=(-1.0);
                    SpinSystem[Hoperator[LoopNumA+4]*3+1]*=(-1.0);
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+1]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+1]*3]);
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+3]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+3]*3]);
                    Widding[((Hoperator[LoopNumA]-9)/10)/SpinNO]+=(double)SpinSystem[Hoperator[LoopNumA+2]*3+1];
                    Widding[((Hoperator[LoopNumA]-9)/10)/SpinNO]+=(double)SpinSystem[Hoperator[LoopNumA+4]*3+1];                
                    break;
            }   
        }
        /*
        SingleAX1+=(double)SingleAFM;
        SingleAFM1+=(double)abs((long long)SingleAFM);
        SingleAFM2+=(double)pow(SingleAFM,2);
        SingleAFM4+=(double)pow(SingleAFM,4);
        SingleAFM6+=(double)pow(SingleAFM,6);
        */
        SingleAX1+=(double)SingleAFM;
        SingleAFM1+=(double)abs((long long)SingleAFM);
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
        SingleAFM1=(double)abs((long long)SingleAFM);
        SingleAFM2=(double)pow(SingleAFM,2);
        SingleAFM4=(double)pow(SingleAFM,4);
        SingleAFM6=(double)pow(SingleAFM,6);
        SingleAX1=(double)SingleAFM2;
        */
        SingleAFM1=(double)abs((long long)SingleAFM);
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


void MeasureFuctJQ3(double* SpinSystem,double* BondNOsystem,long long* Hoperator\
          ,long long &HNO,long long &Size,long long &SpinNO,long long &BondNO,long long &HoperatorNO\
          ,double &AFM,double &AFM1,double &AFM2,double &AFM4,double &AFM6,double &AX1,double &Measure\
          ,double &WiddingX,double &WiddingY,double &WiddingZ,long long * BondNORecord)
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
            switch(Hoperator[LoopNumA]%15)
            {
                case 1:
                    SpinSystem[Hoperator[LoopNumA+1]*3+1]*=(-1.0);
                    SpinSystem[Hoperator[LoopNumA+2]*3+1]*=(-1.0);
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+1]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+1]*3]);
                    Widding[((long long)((Hoperator[LoopNumA]-1)/15)/SpinNO)]+=(double)SpinSystem[Hoperator[LoopNumA+2]*3+1];
                    /*
                    if(SpinSystem[Hoperator[LoopNumA+1]*3+1]==SpinSystem[Hoperator[LoopNumA+2]*3+1])
                    {
                        printf("%d  %f  %f  \n",BondNORecord[((long long)(Hoperator[LoopNumA]/15))*7],SpinSystem[Hoperator[LoopNumA+1]*3+1],SpinSystem[Hoperator[LoopNumA+2]*3+1]);    
                        
                    }
                    */
                    break;
                case 5:
                    SpinSystem[Hoperator[LoopNumA+1]*3+1]*=(-1.0);
                    SpinSystem[Hoperator[LoopNumA+2]*3+1]*=(-1.0);
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+1]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+1]*3]);
                    Widding[(long long)(((Hoperator[LoopNumA]-5)/15)/SpinNO)]+=(double)SpinSystem[Hoperator[LoopNumA+2]*3+1];
                    break;
                case 6:
                    SpinSystem[Hoperator[LoopNumA+3]*3+1]*=(-1.0);
                    SpinSystem[Hoperator[LoopNumA+4]*3+1]*=(-1.0);
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+3]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+3]*3]);
                    Widding[(long long)(((Hoperator[LoopNumA]-6)/15)/SpinNO)]+=(double)SpinSystem[Hoperator[LoopNumA+4]*3+1];
                    break;
                case 7:
                    SpinSystem[Hoperator[LoopNumA+5]*3+1]*=(-1.0);
                    SpinSystem[Hoperator[LoopNumA+6]*3+1]*=(-1.0);
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+5]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+5]*3]);
                    Widding[(long long)(((Hoperator[LoopNumA]-7)/15)/SpinNO)]+=(double)SpinSystem[Hoperator[LoopNumA+6]*3+1];
                    break;                
                case 9:
                    SpinSystem[Hoperator[LoopNumA+1]*3+1]*=(-1.0);
                    SpinSystem[Hoperator[LoopNumA+2]*3+1]*=(-1.0);
                    SpinSystem[Hoperator[LoopNumA+3]*3+1]*=(-1.0);
                    SpinSystem[Hoperator[LoopNumA+4]*3+1]*=(-1.0);
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+1]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+1]*3]);
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+3]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+3]*3]);
                    Widding[(long long)(((Hoperator[LoopNumA]-9)/15)/SpinNO)]+=(double)SpinSystem[Hoperator[LoopNumA+2]*3+1];
                    Widding[(long long)(((Hoperator[LoopNumA]-9)/15)/SpinNO)]+=(double)SpinSystem[Hoperator[LoopNumA+4]*3+1];                
                    break;
                case 10:
                    SpinSystem[Hoperator[LoopNumA+1]*3+1]*=(-1.0);
                    SpinSystem[Hoperator[LoopNumA+2]*3+1]*=(-1.0);
                    SpinSystem[Hoperator[LoopNumA+5]*3+1]*=(-1.0);
                    SpinSystem[Hoperator[LoopNumA+6]*3+1]*=(-1.0);                    
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+1]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+1]*3]);
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+5]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+5]*3]);
                    Widding[(long long)(((Hoperator[LoopNumA]-10)/15)/SpinNO)]+=(double)SpinSystem[Hoperator[LoopNumA+2]*3+1];
                    Widding[(long long)(((Hoperator[LoopNumA]-10)/15)/SpinNO)]+=(double)SpinSystem[Hoperator[LoopNumA+6]*3+1];                
                    break;
                case 11:
                    SpinSystem[Hoperator[LoopNumA+3]*3+1]*=(-1.0);
                    SpinSystem[Hoperator[LoopNumA+4]*3+1]*=(-1.0);
                    SpinSystem[Hoperator[LoopNumA+5]*3+1]*=(-1.0);
                    SpinSystem[Hoperator[LoopNumA+6]*3+1]*=(-1.0);                    
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+5]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+5]*3]);
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+3]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+3]*3]);
                    Widding[(long long)(((Hoperator[LoopNumA]-11)/15)/SpinNO)]+=(double)SpinSystem[Hoperator[LoopNumA+6]*3+1];
                    Widding[(long long)(((Hoperator[LoopNumA]-11)/15)/SpinNO)]+=(double)SpinSystem[Hoperator[LoopNumA+4]*3+1];                
                    break;
                case 14:
                    SpinSystem[Hoperator[LoopNumA+1]*3+1]*=(-1.0);
                    SpinSystem[Hoperator[LoopNumA+2]*3+1]*=(-1.0);
                    SpinSystem[Hoperator[LoopNumA+3]*3+1]*=(-1.0);
                    SpinSystem[Hoperator[LoopNumA+4]*3+1]*=(-1.0);
                    SpinSystem[Hoperator[LoopNumA+5]*3+1]*=(-1.0);
                    SpinSystem[Hoperator[LoopNumA+6]*3+1]*=(-1.0);
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+1]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+1]*3]);                  
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+5]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+5]*3]);
                    SingleAFM+=2.0*(double)((double)SpinSystem[Hoperator[LoopNumA+3]*3+1]*(double)SpinSystem[Hoperator[LoopNumA+3]*3]);
                    Widding[(long long)(((Hoperator[LoopNumA]-14)/15)/SpinNO)]+=(double)SpinSystem[Hoperator[LoopNumA+2]*3+1];                    
                    Widding[(long long)(((Hoperator[LoopNumA]-14)/15)/SpinNO)]+=(double)SpinSystem[Hoperator[LoopNumA+6]*3+1];
                    Widding[(long long)(((Hoperator[LoopNumA]-14)/15)/SpinNO)]+=(double)SpinSystem[Hoperator[LoopNumA+4]*3+1];                
                    break;               
            }   
        }
        
        /*
        SingleAX1+=(double)SingleAFM;
        SingleAFM1+=(double)abs((long long)SingleAFM);
        SingleAFM2+=(double)pow(SingleAFM,2);
        SingleAFM4+=(double)pow(SingleAFM,4);
        SingleAFM6+=(double)pow(SingleAFM,6);
        */
        SingleAX1+=(double)SingleAFM;
        SingleAFM1+=(double)abs((long long)SingleAFM);
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
        SingleAFM1=(double)abs((long long)SingleAFM);
        SingleAFM2=(double)pow(SingleAFM,2);
        SingleAFM4=(double)pow(SingleAFM,4);
        SingleAFM6=(double)pow(SingleAFM,6);
        SingleAX1=(double)SingleAFM2;
        */
        SingleAFM1=(double)abs((long long)SingleAFM);
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
void MeasureFuct_1(double* SpinSystem,double* BondNOsystem,long long* Hoperator\
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
    SingleAFM1=(double)abs((long long)SingleAFM);
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
        ,double &AX1,double &Ususc,double &WiddingX,double &WiddingY,double &WiddingZ,double &TempW\
        ,long long &XSize,long long &YSize,double &Beta,long long &MeasureStep,long long &SpinNO\
        ,double &UsuscMent,double &AFM1Ment,double &AFM2Ment,double &AFM4Ment\
        ,double &AFM6Ment,double &AX1Ment,double &WindingXMent,double &WindingYMent,double &TempWMent)//每個測量的平均
{
    double Vol;
    Vol=(double)(XSize*YSize);
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
}



void MakeLattice(long long &Type,double* SpinSystem,double* BondNOsystem,long long* Hoperator\
          ,long long &Size,long long &SpinNO,long long &BondNO,long long &HoperatorNO\
          ,double &J,double &StrongJ,double &Q,double &StrongQ,double &Probability,long long* BondNORecord)
{   
    long long LoopNumA,LoopNumB,LoopNumC,BondNOtemp;
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
    else if(Type<201)
    {
        SpinSave=(long long *)malloc((6+1)*sizeof(long long*));
        memset(SpinSave,-1,(6+1)*sizeof(long long*));
        switch(Type)
        {
            case 20:
            
                printf("JQ Ladder model \n");
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

        }
  
        for(LoopNumA=0;LoopNumA < HoperatorNO*7;LoopNumA=LoopNumA+7)
        {
           for(LoopNumB=0;LoopNumB < 7 ; LoopNumB+=1 )
           {
                Hoperator[LoopNumA+LoopNumB]=-1 ;              
           }
    
        } 
        
    }
    else
    {
        SpinSave=(long long *)malloc((6+1)*sizeof(long long*));
        memset(SpinSave,-1,(6+1)*sizeof(long long*));   
        for(LoopNumA=0;LoopNumA < SpinNO*2 ;LoopNumA+=1)
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
               SpinSystem[LoopNumA]=(double)pow(-1.0,(long long)(LoopNumA/3)%Size+(long long)(LoopNumA/3)/Size);
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
               SpinSystem[LoopNumA]=(double)pow(-1.0,(long long)(LoopNumA/3)%Size+(long long)(LoopNumA/3)/Size);
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
               SpinSystem[LoopNumA]=(double)pow(-1.0,(long long)(LoopNumA/3)%Size+(long long)(LoopNumA/3)/Size);
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
    
               SpinSystem[LoopNumA]=(double)pow(-1.0,(long long)(LoopNumA/3)%Size+(long long)(LoopNumA/3)/Size);
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
               SpinSystem[LoopNumA]=(double)pow(-1.0,(long long)(LoopNumA/3)%Size+(long long)(LoopNumA/3)/Size);
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
               SpinSystem[LoopNumA]=(double)pow(-1.0,(long long)(LoopNumA/3)%Size+(long long)(LoopNumA/3)/Size);
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
               SpinSystem[LoopNumA]=(double)pow(-1.0,(long long)(LoopNumA/3)%Size+(long long)(LoopNumA/3)/Size);
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
        
        case 201:
            for(LoopNumA=0;LoopNumA < SpinNO*3;LoopNumA=LoopNumA+3)
            {
               SpinSystem[LoopNumA]=(double)pow(-1.0,(long long)(LoopNumA/3)%Size+(long long)(LoopNumA/3)/Size);
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
    }

    
    File=fopen("ModelPlot-1.txt", "w");
    for(LoopNumA=0;LoopNumA < BondNO*2;LoopNumA=LoopNumA+2)
    {
        fprintf(File,"%lf  %2.16lf  \n",BondNOsystem[LoopNumA],BondNOsystem[LoopNumA+1]);
    }
    fclose(File);
    free(SpinSave);
}


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
    *WindingXMent,*WindingYMent,*WindingZMent,*TempWMent,*SpinSystembk;//,*Widding;
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

    init_genrand64(atoi(argv[8])+(long long)getpid());

    if (genrand64_real2()>0.5)
    {
        SeedNum=(long long)(time(NULL)+atoi(argv[8])-10000*atoi(argv[8])*genrand64_real2()+10000*(long long)getpid());        
    }
    else
    {
        SeedNum=(long long)(time(NULL)-atoi(argv[8])+10000*atoi(argv[8])*genrand64_real2()-10000*(long long)getpid());       
    }
    init_genrand64(SeedNum);
    XSize=atoi(argv[1]);
    YSize=atoi(argv[2]);
    Beta=(double)(atof(argv[3])/10000.0);
    J=(double)(atof(argv[4])/10000.0);
    StrongJ=(double)(atof(argv[5])/10000.0);
    Q=(double)(atof(argv[6])/10000.0);
    StrongQ=(double)(atof(argv[7])/10000.0);
    Type=20;
    Probability=0.5;
    T=20000;
    MeasureT=4000*2000;
    MeasureStep=4000;
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
    else
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
    //SpinSystembk=(double *)malloc((SpinSystemSize+1)*sizeof(double*));
    //SpinSystembk[SpinSystemSize]=-999; 
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
    
    MakeLattice(Type,SpinSystem,BondNOsystem,Hoperator,Size,SpinNO,BondNO,HoperatorNO,J,StrongJ,Q,StrongQ,Probability,BondNORecord);
    /*
    for(LoopNumA=0;LoopNumA < BondNO*7;LoopNumA=LoopNumA+7)
    {
        printf("%d %d \n",LoopNumA/7,BondNORecord[LoopNumA]);
        for(LoopNumB=0;LoopNumB < 6;LoopNumB=LoopNumB+1)
        {
            printf("%d ",BondNORecord[LoopNumA+LoopNumB+1]);    
        }
        printf("\n");
        printf("\n");
    }
    system("pause");
    /*
    /*
    for(LoopNumA=0;LoopNumA < BondNO*7;LoopNumA=LoopNumA+1)
    {
        printf("%d \n",BondNORecord[LoopNumA]);
            
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
        ///printf("%d test0\n",LoopNumA);
        /*
        for(LoopNumB=0;LoopNumB<SpinSystemSize;LoopNumB+=1)
        {
            SpinSystembk[LoopNumB]=SpinSystem[LoopNumB]  ;  
        }
        * */
        DiaUpdateJQ3(SpinSystem,BondNOsystem,Hoperator,Beta,HNO,Size,SpinNO,BondNO,HoperatorNO,BondNORecord);
        //DiaUpdateJQ3_test(SpinSystem,BondNOsystem,Hoperator,Beta,HNO,Size,SpinNO,BondNO,HoperatorNO);
        
        /*
        for(LoopNumA=0;LoopNumA <HoperatorNO*7;LoopNumA=LoopNumA+7)
        {
            //printf("%2d ,H=%3d  ,L=%3d  ,R=%3d \n",LoopNumA/3, Hoperator[LoopNumA], Hoperator[LoopNumA+1], Hoperator[LoopNumA+2]);
            
            if (Hoperator[LoopNumA]%15==6 and BondNORecord[((long long)((Hoperator[LoopNumA]-1)/15))*7]==2 and \
            SpinSystem[Hoperator[LoopNumA+3]*3+1]==SpinSystem[Hoperator[LoopNumA+4]*3+1])
            {
                printf("%d ,H=%3d  ,L=%3d  ,R=%3d ,L2=%3d  ,R2=%3d ,L3=%3d  ,R3=%3d\n",BondNORecord[((long long)((Hoperator[LoopNumA]-1)/15))*7], (Hoperator[LoopNumA]-1)/15, Hoperator[LoopNumA+1], Hoperator[LoopNumA+2], Hoperator[LoopNumA+3], Hoperator[LoopNumA+4], Hoperator[LoopNumA+5], Hoperator[LoopNumA+6]);
                printf("%f %f\n",SpinSystem[Hoperator[LoopNumA+3]*3+1], SpinSystem[Hoperator[LoopNumA+4]*3+1]);
                system("pause"); 
            }
            
            //printf("%d ,H=%3d  ,L=%3d  ,R=%3d ,L2=%3d  ,R2=%3d ,L3=%3d  ,R3=%3d\n",LoopNumA/7, Hoperator[LoopNumA], Hoperator[LoopNumA+1], Hoperator[LoopNumA+2], Hoperator[LoopNumA+3], Hoperator[LoopNumA+4], Hoperator[LoopNumA+5], Hoperator[LoopNumA+6]);
        }
        */
        /*
        for(LoopNumB=0;LoopNumB<SpinSystemSize;LoopNumB+=3)
        {       
            if(SpinSystembk[LoopNumB+1]!=SpinSystem[LoopNumB+1])
            {
                printf("%d %f %f \n",(long long)LoopNumB/3,SpinSystembk[LoopNumB+1], SpinSystem[LoopNumB+1]);
                system("pause");    
            }
        }
        /*
        for(LoopNumA=0;LoopNumA <HoperatorNO*7;LoopNumA=LoopNumA+7)
        {
            //printf("%2d ,H=%3d  ,L=%3d  ,R=%3d \n",LoopNumA/3, Hoperator[LoopNumA], Hoperator[LoopNumA+1], Hoperator[LoopNumA+2]);
            printf("%2d ,H=%3d  %3d,L=%3d  ,R=%3d ,L2=%3d  ,R2=%3d ,L3=%3d  ,R3=%3d\n",LoopNumA/7, Hoperator[LoopNumA], Hoperator[LoopNumA]%15, Hoperator[LoopNumA+1], Hoperator[LoopNumA+2], Hoperator[LoopNumA+3], Hoperator[LoopNumA+4], Hoperator[LoopNumA+5], Hoperator[LoopNumA+6]);
        }
        */
        //printf("%d test1\n",LoopNumA);
        //LoopUpdateJQ3(SpinSystem,BondNOsystem,Hoperator,HNO,SpinNO,BondNO,HoperatorNO,TempW,BondNORecord);
        LoopUpdateJQ3_test(SpinSystem,BondNOsystem,Hoperator,HNO,SpinNO,BondNO,HoperatorNO,TempW);
        //printf("%d test2\n",LoopNumA);
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
    sprintf(FileNameDetail,"SSE-L%d-Beta%.4lf-Q%.4lf-Seed%ld-Detail-JQ3.txt",XSize,Beta,Q,SeedNum);//FileNameDetailData
    
    //File=fopen("SSE-Beta1.0-J1.15.txt", "w+");
    //File=fopen(FileName, "a+");
    for(LoopNumA=0;LoopNumA<(long long)(MeasureT/MeasureStep);LoopNumA++)
    {
        
        for(LoopNumB=0;LoopNumB<(long long)MeasureStep;LoopNumB++)
        {
            //printf("%d test4\n",LoopNumA);
            DiaUpdateJQ3(SpinSystem,BondNOsystem,Hoperator,Beta,HNO,Size,SpinNO,BondNO,HoperatorNO,BondNORecord);
            //DiaUpdateJQ3_test(SpinSystem,BondNOsystem,Hoperator,Beta,HNO,Size,SpinNO,BondNO,HoperatorNO);
            //printf("%d test5\n",LoopNumA);
            //LoopUpdateJQ3_TempW(SpinSystem,BondNOsystem,Hoperator,HNO,SpinNO,BondNO,HoperatorNO,TempW,BondNORecord);
            LoopUpdateJQ3_TempW_test(SpinSystem,BondNOsystem,Hoperator,HNO,SpinNO,BondNO,HoperatorNO,TempW);
            //printf("%d test6\n",LoopNumA);
            MeasureFuctJQ3(SpinSystem, BondNOsystem, Hoperator,HNO,Size,SpinNO,BondNO,HoperatorNO\
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
        fprintf(FileDetail,"%2d   %2.16lf   %2.16lf  %2.16lf   %d   ",XSize,Beta,J,Q, HNO);
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

