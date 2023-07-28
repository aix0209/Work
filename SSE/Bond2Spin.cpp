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

void Bond2Spin2DXY(long long &BondNO,long long &XSize,long long &YSize,long long &ZSize,long long &SpinNO,long long &SingleSpinNO,long long &LeftSpin,long long &RightSpin)//Bond編號轉成Spin的編號
{
    
    
    if (BondNO%(SingleSpinNO*2)<SingleSpinNO)//左右向的Bond
    {
        if((BondNO%(SingleSpinNO*2))%XSize!=(XSize-1))
        {
            LeftSpin=BondNO%(SingleSpinNO*2)+(long long)(BondNO/(SingleSpinNO*2))*SingleSpinNO;
            RightSpin=LeftSpin+1;
        }
        else
        {
            LeftSpin=BondNO%(SingleSpinNO*2)+(long long)(BondNO/(SingleSpinNO*2))*SingleSpinNO;
            RightSpin=LeftSpin-XSize+1;
        }
    }
    else
    {
        if(BondNO%(SingleSpinNO*2)<(SingleSpinNO*2-XSize))//上下向的Spin
        {
            LeftSpin=BondNO%(SingleSpinNO*2)-SingleSpinNO+(long long)(BondNO/(SingleSpinNO*2))*SingleSpinNO;
            RightSpin=LeftSpin+XSize;
        }
        else
        {
            LeftSpin=BondNO%(SingleSpinNO*2)-SingleSpinNO+(long long)(BondNO/(SingleSpinNO*2))*SingleSpinNO;
            RightSpin=LeftSpin-SingleSpinNO+XSize;
        }
    }
    
}

void Bond2Spin2DZ(long long &BondNO,long long &XSize,long long &YSize,long long &ZSize,long long &SpinNO,long long &SingleSpinNO,long long &LeftSpin,long long &RightSpin)//Z方向 Bond編號轉成Spin的編號
{
    //BondNO-=SingleSpinNO*2*ZSize;
    if(BondNO<SingleSpinNO*(ZSize-1))
    {
        LeftSpin=BondNO;
        RightSpin=BondNO+SingleSpinNO;
    }
    else
    {
        LeftSpin=BondNO;
        RightSpin=BondNO-(SingleSpinNO*(ZSize-1));
    }
    
}

void Bond2Spin2D_HoneyComb(long long &BondNO,long long &XSize,long long &YSize,long long &SpinNO,long long &LeftSpin,long long &RightSpin)//Bond編號轉成Spin的編號
{
    if (BondNO<SpinNO)//左右向的Bond
    {
        if(BondNO%XSize!=(XSize-1))
        {
            LeftSpin=BondNO;
            RightSpin=LeftSpin+1;
        }
        else
        {
            LeftSpin=BondNO;
            RightSpin=LeftSpin-XSize+1;
        }
    }
    else
    {
        if(BondNO<SpinNO*2-XSize)//上下向的Spin
        {
            LeftSpin=BondNO-SpinNO;
            RightSpin=LeftSpin+XSize;
        }
        else
        {
            LeftSpin=BondNO-SpinNO;
            RightSpin=LeftSpin-SpinNO+XSize;
        }
    }
    
}

void Q2Bond2Bond2D(long long &BondNO,long long &Size ,long long &SpinNO,long long &LeftSpin,long long &RightSpin)//Bond編號轉成Spin的編號
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
void Q3Bond2Bond2D_HoneyComb(long long &BondNO,long long &XSize, long long &YSize,long long &SpinNO,long long &Bond1,long long &Bond2,long long &Bond3)
{   
    if (BondNO<SpinNO)    
    {//向右QBond
        Bond1 = BondNO+SpinNO;
        
        Bond2 = BondNO+1;
        if(Bond2%XSize==0)
        {
            Bond2 = ((long long)(Bond2/XSize)-1)*XSize+Bond2%XSize;  
        }
   
        Bond3 = Bond2+XSize;
        
        if(Bond3>=SpinNO)
        {
            Bond3 -= SpinNO;  
        }         
        
    }
    else
    {//向左QBond
        //BondNO-=SpinNO;
        Bond1 = BondNO;
        
        Bond2 = Bond1-SpinNO-2;
        if(Bond2%XSize==(XSize-2) or Bond2%XSize==(XSize-1) or Bond2 < 0 )
        {
            if(Bond2%XSize==XSize-2 or Bond2%XSize==(XSize-1))
            {
                Bond2 = ((long long)(Bond2/XSize)+1)*XSize+Bond2%XSize;  
            }
            else
            {
                Bond2 +=XSize;
            }
             
        }
   
        Bond3 = Bond2+XSize;
        
        if(Bond3>=SpinNO)
        {
            Bond3 -= SpinNO;  
        }       
        
        
    }
}
void Q3Bond2Bond2DXY_Ladder(long long &BondNO,long long &XSize,long long &YSize,long long &ZSize,long long &SpinNO,long long &SingleSpinNO,long long &Bond1,long long &Bond2,long long &Bond3)
{
    if (BondNO%(SingleSpinNO*2)<SingleSpinNO)//左右向的QBond ≡
    {
        if(BondNO%(SingleSpinNO*2)<(SingleSpinNO-XSize*2))
        {
            Bond1=BondNO;
            Bond2=Bond1+XSize;
            Bond3=Bond1+XSize*2; 


        }
        else
        {
            
            if(BondNO%(SingleSpinNO*2)>(SingleSpinNO-XSize-1))
            {
                Bond1=BondNO;
                Bond2=Bond1+XSize-SingleSpinNO;
                Bond3=Bond1+XSize*2-SingleSpinNO;   
                
            }
            else
            {
                Bond1=BondNO;
                Bond2=Bond1+XSize;
                Bond3=Bond1+XSize*2-SingleSpinNO;         
            }
        }
    }
    else//Q上下向的Spin Ⅲ Size**2*2
    {
        if(BondNO%(SingleSpinNO*2)%XSize<(XSize-2))
        {
            Bond1=BondNO;
            Bond2=Bond1+1;
            Bond3=Bond1+2;
        }
        else
        {
            if(BondNO%(SingleSpinNO*2)%XSize==(XSize-1))
            {
                Bond1=BondNO;
                Bond2=Bond1+1-XSize;
                Bond3=Bond1+2-XSize;
            }
            else
            {
                Bond1=BondNO;
                Bond2=Bond1+1;
                Bond3=Bond1+2-XSize;                
                
            }
        }
    }
    
}
