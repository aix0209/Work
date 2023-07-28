from scipy import *
from scipy.optimize import leastsq
import scipy
import pylab
from pylab import *
import numpy
from numpy import *
import os
import scipy.odr as odr
def ErrorR(p, y, y1, x1,Model,c1):
    if "x1" in Model :
        err = (y-Equation_x1(p,x1,Model,c1))/y1
        if (y1 == np.zeros((len(y1)))).any:
            for NumA in range(len(y1)):
                if y1[NumA]==0:
                    err[NumA]=0
            

        return err

def ErrorR_100(p, y, y1, x1,Model,c1):
    if "x1" in Model :
        err = np.abs(1-Equation_x1(p,x1,Model,c1)/y)*100
        err[np.where(y<1.e-8)]=0
        #if (y == np.zeros((len(y)))).any:
        #    for NumA in range(len(y)):
        #        if y[NumA]==0:
        #            err[NumA]=0
        return np.mean(err)
"""
exp(-bx^a)              Exp_p1_x1
exp(-(bx)^a)            Exp_p1_x1_2    
exp(-bx^a)+c            Exp_p2_x1
c*exp(-bx^a)            Exp_p2_x1-a
d*exp(-bx^a)+c          Exp_p3_x1
b*exp(-ax)+c            Exp_p2_x1_1
b*exp(-ax)+const2       Exp_p2_x1_1_const2
exp(-ax)+c              Exp_p1_x1_1
exp(-ax)                Exp_p0_x1

c1x+c0                  Poly_p1_x1
c2x^2+c1x+c0            Poly_p2_x1
c3x^3+c2x^2+c1x+c0      Poly_p3_x1
(1+(1-c0)*x)^(1/(1-c0)  Tsallis_p1_x1

""" 
def f(p,x1):
    return(p[2]*np.exp(-p[1]*(x1**p[0])))
    
    
def Equation_x1(p,x1,Model,c1):
    if "Exp" in Model:
        if "p1" in Model:
            if Model ==  "Exp_p1_x1" :
                return(0.058386794*(c1)*np.exp(-p[1]*(x1**p[0])))
            elif Model == "Exp_p1_x1_1" :
                return(np.exp(-p[0]*x1)+p[1])
            elif Model == "Exp_p1_x1_2" :
                return(np.exp(-1.0*(p[1]*x1)**p[0]))       
        elif "p2" in Model:
        
            if Model ==  "Exp_p2_x1" :
                return(np.exp(-p[1]*(x1**p[0]))+p[2])
            elif Model == "Exp_p2_x1-a" :
                return(p[2]*np.exp(-p[1]*(x1**p[0])))
            elif Model == "Exp_p2_x1-b" :
                return((1/c1)*np.exp(-p[1]*x1**p[0]))
            elif Model == "Exp_p2_x1_1_const2" :
                return(p[1]*np.exp(-p[0]*x1)+0.0)
            elif Model == "Exp_p2_x1_1" :
                return(p[1]*np.exp(-p[0]*x1)+p[2])
        elif "p3" in Model:
            
            if Model == "Exp_p3_x1" :
               return(p[3]*np.exp(-p[1]*(x1**p[0]))+p[2])
        elif "p0" in Model:
            if Model == "Exp_p0_x1" :
               return(np.exp(-p[0]*x1))


    elif "Poly" in Model : 
        if Model == "Poly_p1_x1 " :
            return(p[0]+p[1]*x1)
        elif Model == "Poly_p2_x1" :
            return(p[0]+p[1]*x1+p[2]*x1**2)
        elif Model == "Poly_p3_x1" :
            return(p[0]+p[1]*x1+p[2]*x1**2+p[3]*x1**3)
        elif Model == "Poly_p4_x1" :
            return(p[0]+p[1]*x1+p[2]*x1**2+p[3]*x1**3+p[4]*x1**4)
    elif "Tsallis" in Model:
        if Model == "Tsallis_p1_x1" :
            return(1+p[2]*(1-p[0])*x1**p[1])**(1/(1-p[0]))
    else:
        print("Model is wrong "+Model)
    




def Fitting(DataLoad,FileWrite,FileWriteError,XNo,YNo,YErrorNo,StartDataNO,EndDataNO,Model,ParaNO,P0aTemp,P0alimitMaxTemp,P0alimitMinTemp,CNO):
    #StartDataNO=0
    P0a = np.zeros((ParaNO))
    P0alimitMax = np.zeros((ParaNO))
    P0alimitMin = np.zeros((ParaNO))
    for NumA in range(ParaNO) :
        P0a[NumA] = P0aTemp[NumA]
        P0alimitMax[NumA] = P0alimitMaxTemp[NumA]
        P0alimitMin[NumA] = P0alimitMinTemp[NumA]
    """
    P0a = [3 ,-10, 1 ,1]
    #P0a = [-0.4016033  ,   -9.1666942   ,  -4.2193648   ,  0.5991620]
    #P0alimitMax = [ 0 ,15 , 10 , 10 ]
    #P0alimitMin = [ -1 ,-15 , -10 , -10 ]
    P0alimitMax = [ 20 ,-1000, 1.1]
    P0alimitMin = [ -20 ,-5000 , 0.9 ]
    #P0alimitMax = [ 200 ,200]
    #P0alimitMin = [ -200 ,-200]
    """
    y = DataLoad[StartDataNO:EndDataNO,YNo]
    x1 = DataLoad[StartDataNO:EndDataNO,XNo]
    c1 = DataLoad[StartDataNO:EndDataNO,CNO]
    x1Error = DataLoad[StartDataNO:EndDataNO,XNo+1]
    x1Error [np.where(x1Error==0)]+=1.0e-9
    a = len(y)
    DataSave=np.zeros((4))
    FootStep=10000
    FittingNO=1000
    p0 = zeros((ParaNO))
    W=0.2
    
    for NumA in range(FittingNO):
        y = np.random.normal(DataLoad[StartDataNO:EndDataNO,YNo],DataLoad[StartDataNO:EndDataNO,YErrorNo])
        #y = DataLoad[StartDataNO:EndDataNO,YNo]
        yError = DataLoad[StartDataNO:EndDataNO,YErrorNo]
        y [np.where(y==0)]+=1.0e-8
        yError [np.where(yError==0)]+=1.0e-9

        for NumB in range(ParaNO) :
            p0[NumB] =  P0a[NumB]*(1.0+(W*(numpy.random.random()-0.5)))
        """
        A1_0=P0a[0]*(1.0+(0.2*(numpy.random.random()-0.5)))
        A2_0=P0a[1]*(1.0+(0.2*(numpy.random.random()-0.5)))
        A3_0=P0a[2]*(1.0+(0.2*(numpy.random.random()-0.5)))
        A4_0=P0a[3]*(1.0+(0.2*(numpy.random.random()-0.5)))
        #p0 = array([A1_0, A2_0, A3_0,A4_0])
        p0 = array([A1_0, A2_0, A3_0])
        #p0 = array([A1_0, A2_0])
        """
        ModelOdr=odr.Model(Equation_x1,extra_args=[Model,c1])#Equation_x1(p,x1,Model)
        #print(ModelOdr)
        FittingData = odr.RealData(x1,y,sx=x1Error,sy=yError)
        FittingODR = odr.ODR(FittingData,ModelOdr,p0,maxit = FootStep)
        FittingODR.set_job(fit_type=2,deriv=0,)
        FittingDataOut = FittingODR.run()
        #FittingDataOut.pprint()
        plsq1 = FittingDataOut.beta
        #plsqstd = FittingDataOut.sd_beta
        #print(plsq,plsqstd)
        
        #plsq = leastsq(ErrorR, p0, args=(y, y1,x1 ,Model), maxfev=FootStep, full_output=1)
        #plsq1 = plsq[0]
        
        #covar = plsq[1]
        chisqr = numpy.sum(ErrorR(plsq1,y,yError,x1,Model,c1)**2)/float(a-ParaNO)
        chisqr100 = ErrorR_100(plsq1,y,yError,x1,Model,c1)
        check=1
        #print(chisqr,plsq1)
        for NumB in range(len(plsq1)):
            if  plsq1[NumB] > P0alimitMax[NumB] or  plsq1[NumB] < P0alimitMin[NumB] :
                check=0
                break
        """
        if  plsq1[0] > P0alimitMax[0] or  plsq1[0] < P0alimitMin[0] :
            check=0
        #0.0000169  -0.4016033     -9.1666942     -4.2193648     0.5991620 
        elif (plsq1[2]+plsq1[3])<0 or (plsq1[2]+plsq1[3])>5:
            check=0
        """
        if chisqr < 30 and check==1 :         
            FileSave = open(FileWrite,"a+")
            FileSave.write("  %6.16f"  %chisqr)
            #FileSave.write("  %6.7f"  %chisqr100)
            for NumB in range(len(plsq1)):
                FileSave.write("  %6.16f   "%plsq1[NumB])
            FileSave.write("\n")
            FileSave.close()
        else:
            FileSave = open(FileWriteError,"a+")
            FileSave.write("  %6.16f"  %chisqr)
            #FileSave.write("  %6.7f"  %chisqr100)
            for NumB in range(len(plsq1)):
                FileSave.write("  %6.16f   "%plsq1[NumB])
            FileSave.write("\n")
            FileSave.close()
        
def LoadCal4Fitting(FileRead,FileWrite):
    Data=np.loadtxt(FileRead,dtype=np.float64)
    DataNum=len(Data[0])
    DataT=len(Data)
    MeansData=np.zeros((DataNum*2),np.float64)
    #MeansData=np.zeros((DataNum),np.float64)
    for NumB in range(DataNum):
        MeansData[NumB*2]=np.mean(Data[:,NumB])
        #MeansData[NumA]=np.mean(Data[:,NumA])
        #MeansData[NumA*2+1]=np.std(Data[:,NumA])/np.sqrt(DataT)
        MeansData[NumB*2+1]=np.std(Data[:,NumB])
    #print(NumA,"  %.16f  "%(ParaValue[NumA,ParaName.index("ParaG")]/10000.0))
    FileSave= open(FileWrite,"a+")
    
    FileSave.write( "  %.16f  "%(ParaValue[NumA,ParaName.index("ParaG")]/10000.0))
    
    for NumB in range(len(MeansData)):
        FileSave.write( "%.16f " % MeansData[NumB])
       
    FileSave.write("\n")
    FileSave.close()
    return MeansData
"""
exp(-bx^a)              Exp_p1_x1    
exp(-bx^a)+c            Exp_p2_x1
c*exp(-bx^a)            Exp_p2_x1-a
c*exp(-(bx)^a)            Exp_p2_x1-b
d*exp(-bx^a)+c          Exp_p3_x1
b*exp(-ax)+c            Exp_p2_x1_1
b*exp(-ax)+const2       Exp_p2_x1_1_const2
exp(-ax)+c              Exp_p1_x1_1
exp(-(bx)^a)            Exp_p1_x1_2
exp(-ax)                Exp_p0_x1


c1x+c0                  Poly_p1_x1
c2x^2+c1x+c0            Poly_p2_x1
c3x^3+c2x^2+c1x+c0      Poly_p3_x1
"""   
    
Parameter=np.loadtxt("Parameter4IncreaseBeta-g-d-run.txt",dtype=np.str)
ParaName=list(Parameter[0,:])
ParaValue=Parameter[1:,:].astype(int)
Times="Exp_p1_x1" 
#Times="Exp_p2_x1-a"  

for NumA in range(len(ParaValue)):
    if ParaValue[NumA,ParaName.index("YesNO")]==1:
        #print(ParaValue[NumA,:])
        #FileRead="T4000.txt"
        FileRead=\
        "OriginData\\"\
        +"Lx"+"%d"%(ParaValue[NumA,ParaName.index("Lx")])+"-"\
        +"B"+"%d"%(ParaValue[NumA,ParaName.index("StartBeta")])+""\
        +"to"+"%d"%(ParaValue[NumA,ParaName.index("StopBeta")])+"-"\
        +"ParaP"+"%d"%(ParaValue[NumA,ParaName.index("ParaP")])+"-"\
        +"ParaG"+"%d"%(ParaValue[NumA,ParaName.index("ParaG")])+"-"\
        +"T"+"%d"%(ParaValue[NumA,ParaName.index("T")])+"-"\
        +"Means.txt"
        if os.path.isfile(FileRead):
            print(FileRead)
        else :
            print("沒有",FileRead)
            continue
        DataLoad=np.loadtxt(FileRead,dtype=np.float64)
        FileWrite=FileRead.replace("OriginData\\Lx","FittingDatamMeans\\Fitting-"+Times+"-Lx")
        FileWriteError=FileRead.replace("OriginData\\Lx","FittingDatamMeans\\Fitting-Error"+Times+"-Lx")
        if os.path.isfile(FileWrite):
            os.remove(FileWrite)
        #print(FileWrite,"\n",FileWriteError)
        XNo=4
        CNO=29
        print(DataLoad[0,CNO])
        YNo=10
        YErrorNo=11
        StartDataNO=19
        EndDataNO=len(DataLoad[:,YNo])
        #Model = "Exp_p2_x1_1_const2"
        #Model = "Exp_p1_x1"
        Model = Times
        ParaNO = 2
        #P0aTemp = [0.9,0.5, 0.1 ,0.1]
        P0aTemp = [0.8,0.5, 0.1 ,0.1]
        P0aAny=0
        for NumB in range(len(DataLoad[:,YNo])):
            if DataLoad[NumB,YErrorNo]/DataLoad[NumB,YNo] < 0.1 and DataLoad[NumB,YNo]>1.0e-10:
                EndDataNO = NumB
            else:
                break
        #EndDataNO=len(DataLoad[:,YNo])
        #EndDataNO=49
        print(StartDataNO,EndDataNO)
        if P0aAny == 1:
            P0alimitMaxTemp = [ 9999 ,9999 , 9999 , 9999 ]
            P0alimitMinTemp = [ -9999 ,-9999, -9999 , -9999 ]
        else  : 
            P0alimitMaxTemp = [ 50,50 ,50 , 1 ]
            P0alimitMinTemp = [ 0 ,0, 0, 1.0e-6 ]
        Fitting(DataLoad,FileWrite,FileWriteError,XNo,YNo,YErrorNo,StartDataNO,EndDataNO,Model,ParaNO,P0aTemp,P0alimitMaxTemp,P0alimitMinTemp,CNO)
        if os.path.isfile(FileWrite):
            if os.path.isfile(FileWriteError):
                os.remove(FileWriteError)
            FileRead=FileWrite
            FileWrite=\
            "FittingDatamMeans\HB-"\
            +ParaName[ParaName.index("Lx")]+"%d"%(ParaValue[NumA,ParaName.index("Lx")])+"-"\
            +ParaName[ParaName.index("ParaP")]+"%d"%(ParaValue[NumA,ParaName.index("ParaP")])+"-"\
            +ParaName[ParaName.index("T")]+"%d"%(ParaValue[NumA,ParaName.index("T")])\
            +"-Fitting"+Times+".txt"
          
            p2temp=LoadCal4Fitting(FileRead,FileWrite)
            p2=np.zeros((int(len(p2temp)/2)-1))
            for NumB in range(2,len(p2temp),2):
                p2[int(NumB/2)-1]=p2temp[NumB ]
            print(\
            "P="+"%.1f"%(ParaValue[NumA,ParaName.index("ParaP")]/10000.0)\
            ,"G="+"%.4f"%(ParaValue[NumA,ParaName.index("ParaG")]/10000.0)\
            ,p2\
            )
            x1=DataLoad[StartDataNO:EndDataNO,XNo]
            c1=DataLoad[0,CNO]
            y1=DataLoad[StartDataNO:EndDataNO,YNo]
            y1Error=DataLoad[StartDataNO:EndDataNO,YErrorNo]
            x2=np.linspace(min(x1)*0.99,max(x1)*1.01,100)
            y2=Equation_x1(p2,x2,Model,c1)
            plt.plot(x2,y2,linestyle="-")
            plt.errorbar(x1,y1,y1Error,color='black', marker='o',linestyle="None")
            



            
            plt.xlabel("Beta")
            plt.ylabel("Xu")        
            plt.title('Xu-Beta'+"  P"+"%.1f"%(ParaValue[NumA,ParaName.index("ParaP")]/10000.0)+"  G"+"%.4f"%(ParaValue[NumA,ParaName.index("ParaG")]/10000.0))
            plt.legend(('Fitting','Data' ), shadow=True, loc="upper right")
            SavePic=\
            "Picture\Picture-Xu-Beta"+"-"\
            +"Lx"+"%d"%(ParaValue[NumA,ParaName.index("Lx")])+"-"\
            +"B"+"%d"%(ParaValue[NumA,ParaName.index("StartBeta")])+""\
            +"to"+"%d"%(ParaValue[NumA,ParaName.index("StopBeta")])+"-"\
            +"P"+"%.1f"%(ParaValue[NumA,ParaName.index("ParaP")]/10000.0)+"-"\
            +"G"+"%.4f"%(ParaValue[NumA,ParaName.index("ParaG")]/10000.0)+"-"\
            +"T"+"%d"%(ParaValue[NumA,ParaName.index("T")])\
            +Times+".png"
            if os.path.isfile(SavePic):
                os.remove(SavePic)
            plt.savefig(SavePic,dpi=300,format='png')
            #plt.show()
            plt.clf()
        else:
            print("Fitting 失敗")
"""
#def residuals(p, y, y1, x1, x2): 
#    err = (y-peval(x1, x2, p))/y1
#    return err

#def peval(x1, x2, p): 
#    return (1.0-p[6]*(x1**(-p[7])))*(p[0] + p[3]*(((x2-p[1])/p[1])*(x1**(1.0/p[2]))) + p[4]*(((x2-p[1])/p[1])*(x1**(1.0/p[2])))**2 + p[5]*(((x2-p[1])/p[1])*(x1**(1.0/p[2])))**3)
La=np.array([10,12,16,20,24,28,32,36,40,44,48])
p0a=np.zeros((11,8))
p0a[0,:]=array([0.684554646,0.497063539,0.869900790,-0.012101853,0.000081807,-0.000152088,3.270604363,0.992348955 ])
p0a[1,:]=array([0.687995821,0.359254695,1.368116340,-0.012171304,-0.003921976,0.000296001,3.344061468,0.988038111 ])
p0a[2,:]=array([0.695372922,0.520533230,0.986585984,-0.022849729,-0.000771562,0.000194013,4.298887593,0.899561936 ])
p0a[3,:]=array([0.696431273,0.387429756,1.392388002,-0.011316526,-0.007077939,0.000575776,3.397697750,0.846474079 ])
p0a[4,:]=array([0.677518238,0.567786252,0.943695958,-0.026036726,0.000721590,0.000260235,5.411101212,0.828628038 ])
p0a[5,:]=array([0.691475079,0.445358201,0.938020121,0.005424260,-0.003106763,0.000131714,3.813453839,0.775744706 ])
p0a[6,:]=array([0.706284409,0.475162975,0.988071760,-0.003310654,-0.003758903,0.000223795,5.744793465,0.847233524 ])
p0a[7,:]=array([0.675496563,0.492689600,0.898147974,-0.006513764,-0.001703384,0.000088918,4.928235273,0.806280429 ])
p0a[8,:]=array([0.702977917,0.533070876,0.918317859,-0.021846131,-0.000334834,0.000075779,7.224442708,0.814023450 ])
p0a[9,:]=array([0.680616309,0.495067645,0.895739832,-0.002729942,-0.001816154,0.000075664,5.384711848,0.788924867 ])
p0a[10,:]=array([0.705680699,0.503566730,0.893612149,-0.003244845,-0.002289489,0.000110708,6.040005555,0.777747731 ])
j=0
for P in range(0,7000,1000):
    for Q in range(1,3,1):
        if Q==1:
            QNO=2
            Qstd=3
            p0a= array([0.685681716  , 2.636982155 ,  0.783118904  ,-0.013539631 , -0.000051017  , 0.000308100 , -0.489771209 ,  1.845065573  ] )
            QTemp=0.85
        else:
            QNO=4
            Qstd=5
            p0a= array([0.455681716  , 2.636982155 ,  0.783118904  ,-0.013539631 , -0.000051017  , 0.000308100 , -0.489771209 ,  1.845065573  ] )
            QTemp=0.65
        filename="HDZP04N1000L48_new.txt"
        #"P"+str(P)+"Q.txt"
        SaveName=filename.replace(".txt","-Q"+str(Q)+"Fitting-20190921.txt")
        data = loadtxt(filename)
        #x1 = data[:,0]
        y = data[:,1]
        #y1 = data[:,3]
        #figure()
        #errorbar(x, y, yerr=y1, fmt='k.')
        #savefig('power_law_fit.png')
        #k = 0
        a = len(y)
        #print(a)
        #arr = [[1] for x3 in xrange(a)]
        #for i in xrange(0,2500):
        #  for j in xrange(0,a):
        #    n = random.randint(0,a)
        #    arr[j] = [data[n,0], data[n,1], data[n,2]] 
        #  arr = reshape(arr,(a,3))
        x1 = data[:,0]
        x2 = data[:,1]

        InitailNO=10
        FittingTemp=np.zeros((InitailNO,8))
        ChisqrNO=50
        Initial=0
        TempNO=0
        
        print("Initial..."+filename)
        while Initial==0:
            y = np.random.normal(data[:,QNO],data[:,Qstd])
            y1 = data[:,Qstd]
            A1_0=p0a[0]*(1.0+(0.4*numpy.random.random()-1))
            A2_0=p0a[1]*(1.0+(0.4*numpy.random.random()-1))
            A3_0=p0a[2]*(1.0+(0.4*numpy.random.random()-1))
            A4_0=p0a[3]*(1.0+(0.4*numpy.random.random()-1))
            k2_0=p0a[4]*(1+0.4*numpy.random.random()-1)
            n1_0=p0a[5]*(1+0.4*numpy.random.random()-1)
            n2_0=p0a[6]*(1+0.4*numpy.random.random()-1)
            n3_0=p0a[7]*(1+0.4*numpy.random.random()-1)
            p0 = array([A1_0, A2_0, A3_0, A4_0, k2_0, n1_0, n2_0,n3_0])
            plsq = leastsq(residuals, p0, args=(y, y1,x1,x2), maxfev=100000, full_output=1)
            plsq1 = plsq[0]
            covar = plsq[1]
            chisqr = numpy.sum(residuals(plsq1,y,y1,x1,x2)**2)/float(a-8)
            if chisqr<10 and plsq1[0]<QTemp:
               print("SaveInitial By chisqr<10..."+str(TempNO+1))
               print(plsq1)
               FittingTemp[TempNO,:]=plsq1[:8]
               TempNO+=1
            elif abs(1-ChisqrNO/chisqr)< 1.0e-1:
               print("SaveInitial By abs(1-ChisqrNO/chisqr)< 1.0e-1..."+str(TempNO+1))
               print(plsq1)
               FittingTemp[TempNO,:]=plsq1[:8]
               TempNO+=1 
            elif chisqr<ChisqrNO:
               #ChisqrNO=chisqr
               p0a=plsq1[:8]
               print("Approaching..."+str(ChisqrNO))
               print(plsq1)
            if TempNO==InitailNO:
                for T in range(8):
                    p0a[T]=np.mean(FittingTemp[:,T])
                Initial=1
               
          
        print("Fitting...")
        for i in range(1000):
            y = np.random.normal(data[:,QNO],data[:,Qstd])
            y1 = data[:,Qstd]
            A1_0=p0a[0]*(1.0+0.1*numpy.random.random())
            A2_0=p0a[1]*(1.0+0.1*numpy.random.random())
            A3_0=p0a[2]*(1.0+0.1*numpy.random.random())
            A4_0=p0a[3]*(1.0+0.1*numpy.random.random())
            k2_0=p0a[4]*(1+0.1*numpy.random.random())
            n1_0=p0a[5]*(1+0.1*numpy.random.random())
            n2_0=p0a[6]*(1+0.1*numpy.random.random())
            n3_0=p0a[7]*(1+0.1*numpy.random.random())
            p0 = array([A1_0, A2_0, A3_0, A4_0, k2_0, n1_0, n2_0,n3_0])
            plsq = leastsq(residuals, p0, args=(y, y1,x1,x2), maxfev=100000, full_output=1)
            plsq1 = plsq[0]
            covar = plsq[1]
            chisqr = numpy.sum(residuals(plsq1,y,y1,x1,x2)**2)/float(a-8)

        
            if chisqr < 10:
                #if chisqr<lowerchisqr:
                #    lowerchisqr=chisqr
                #    p0a=plsq1
                if plsq[0][0] < QTemp:
          #if plsq[0][0] > 0.380:
                    #if plsq[0][0] < 0.72:
                    #    if plsq[0][2] > 0.75:
                    #        if plsq[0][2] < 0.91:
                   #if plsq[0][0] < 0.48:
                    #            if abs(plsq[0][6]) < 10.0:
                    #                if plsq[0][7] < 10.0:
                                #        if plsq[0][7] > 0.0:
                
                #  k = k + 1 
                # if k < 2001:
                #   if plsq[0][2] > 0.0:
                                #print(chisqr,plsq1)
                    myfile = open(SaveName, 'a')
                    #for i in range(len(pname)):
                    myfile.write( "%13.9f " % chisqr)
                    #myfile.write( " %6.7f " % d)
                    #myfile.write( " %6.7f " % e)
                    myfile.write( "%13.9f " % plsq1[0]) 
                    #myfile.write( " %6.7f " % sqrt(chisqr*covar[0][0]))
                    myfile.write( "%13.9f " % plsq1[1])
                    #myfile.write( " %6.7f " % sqrt(chisqr*covar[1][1]))
                    myfile.write( "%13.9f " % plsq1[2])
                    myfile.write( "%13.9f " % plsq1[3])
                    myfile.write( "%13.9f " % plsq1[4])
                    myfile.write( "%13.9f " % plsq1[5])
                    myfile.write( "%13.9f " % plsq1[6])
                    myfile.write( "%13.9f \n" % plsq1[7])
                    #myfile.write( " %6.7f \n" % sqrt(chisqr*covar[2][2]))
                    #myfile.write( " %6.7f " % plsq1[2])
                    #myfile.write( " %6.7f \n" % sqrt(1.25*1.25*chisqr*covar[2][2]))
                    #myfile.write( " %6.7f " % plsq1[3])
                    #myfile.write( " %6.7f \n" % sqrt(covar[3][3]))
                    myfile.close()
    

#myfile.write( " %6.7f " % (3.0**(0.5))*0.5*sqrt(covar[0][0])/((plsq[0][0])**(0.5)))
#myfile.write( " %6.7f " % sqrt(covar[1][1]))
#myfile.write( " %6.7f " % sqrt(covar[2][2]))
#myfile.write( " %6.7f \n" % sqrt(covar[3][3])) 
#myfile.write( " %6.7f " % plsq[0][3])
#myfile.write( " %6.7f " % plsq[0][4])
#myfile.write( " %6.7f \n" % plsq[0][5])
"""
