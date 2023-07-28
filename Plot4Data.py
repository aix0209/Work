import matplotlib.pyplot as plt
import os
import sys
import numpy as np
#FileRead="HB-Lx32-ParaP4000-T1000-Fitting.txt"
#Data = np.loadtxt(FileRead)
#LoadFilename1=("BD-Q1-Fitting-Means.txt")
#DataLoad = np.loadtxt(FileRead)

#MeansT=[1,3,5,7,9,11,13,15]
#MeansT=[0,2,4,6,8,10,12,14]
XNo=0
YNo=3
YErrorNo=4
#plt.xlabel("g")
#plt.ylabel("α")
plt.xlabel("g",size=14)
plt.ylabel("α",size=14)
L=[32,40,44,48,64,128]
for NumA in L:
    FileName="FittingDatamMeans\HB-Lx"+str(NumA)+"-ParaP6000-T1000-FittingExp_p2_x1-a.txt"
    DataLoad = np.loadtxt(FileName)
    plt.plot(DataLoad[:,XNo],DataLoad[:,YNo], marker='o',linestyle="None")
"""
FileName="FittingDatamMeans\HB-Lx32-ParaP6000-T1000-FittingExp_p2_x1-a.txt"
DataLoad = np.loadtxt(FileName)
plt.plot(DataLoad[:,XNo],DataLoad[:,YNo], marker='o',linestyle="None")
#plt.errorbar(DataLoad[:,XNo],DataLoad[:,YNo],DataLoad[:,YErrorNo], marker='o',linestyle="None")

FileName="FittingDatamMeans\HB-Lx32-ParaP6000-T1000-FittingExp_p2_x1-a-ODR-250Test.txt"
DataLoad = np.loadtxt(FileName)
plt.errorbar(DataLoad[:,XNo],DataLoad[:,YNo],DataLoad[:,YErrorNo], marker='o',linestyle="None")

FileName="FittingDatamMeans\HB-Lx128-ParaP6000-T1000-Fitting-Exp_p2_x1_1_const2-15-30.txt"
DataLoad = np.loadtxt(FileName)
plt.errorbar(DataLoad[:,XNo],DataLoad[:,YNo],DataLoad[:,YErrorNo], marker='o',linestyle="None")

[\
"Lx128-B1000to200000-ParaP4000-ParaG40000-T1000-Means.txt",\
"Lx128-B1000to200000-ParaP4000-ParaG60000-T1000-Means.txt",\
"Lx256-B1000to200000-ParaP4000-ParaG40000-T1000-Means.txt",\
"Lx256-B1000to200000-ParaP4000-ParaG60000-T1000-Means.txt",\
]


for NumA in range(0,len(FileName),1):
    FileRead = FileName[NumA]
    DataLoad = np.loadtxt(FileRead)
    plt.errorbar(DataLoad[:,XNo],DataLoad[:,YNo],DataLoad[:,YErrorNo], marker='o',linestyle="None")
"""
#FileRead="Lx128-B50000to200000-ParaP4000-ParaG60000-T1000-Means.txt"
#DataLoad = np.loadtxt(FileRead)
#plt.errorbar(DataLoad[:,XNo],DataLoad[:,YNo],DataLoad[:,YErrorNo],color='black', marker='o',linestyle="None")

plt.title("P=0.6",size=18)
plt.legend(L, shadow=True, loc="upper right")
#SavePic=FileRead.replace(".txt",".png")
#plt.savefig(SavePic,dpi=600,format='png')
#plt.plot(LoadData[:,XNo],LoadData[:,YNo],"o",label="L="+"%.0f"%Data[LIndex,0])
#plt.xlabel("Beta")
#plt.ylabel("Xu")    
#plt.legend(("L32 P=0.6","L64 P=0.6","L128 P=0.6"), shadow=True, loc="upper right")
plt.show()
"""
MeansT=np.arange(0,24,3)
#print(MeansT)
#print(Data1)
for T in (500,1000,2000,3000,4000):
    FileRead="T"+"%d"%(T)+"-Means.txt"
    Data = np.loadtxt(FileRead)
    x=Data[7:13,4]
    y=Data[7:13,10]
    yerr=Data[7:13,11]
    #Lcheck=x[0]
    #LIndex=0

    #print(LIndex,NumA+1,Data[LIndex,0],Data[NumA,0])
    plt.errorbar(x,y,yerr,linestyle="None",marker='o')
    #plt.errorbar(J245x,J245y,J245err,color='black', marker='o')
    #plt.plot(x[LIndex:NumA+1],y[LIndex:NumA+1],"o",label="L="+"%.0f"%Data[LIndex,0])
    #LIndex=NumA
    #plt.xlim(0.05, 0.8)
    plt.xlabel("Beta")
    plt.ylabel("Xu")    
    plt.legend(loc='upper right', shadow=True )
    #plt.savefig(SaveFile,dpi=600,format='png')
plt.legend(('T=500', 'T=1000', 'T=2000', 'T=3000', 'T=4000'), shadow=True, loc="upper right")
plt.show()
    #plt.legend((str(NumA)), shadow=True, loc="upper right")
    #print(len(p))
    #x1=NumA
    #x2=np.linspace(x[0]-0.005,x[-1]+0.005,100)
    #print(p)    
    # y2=(1.0-p[6]*(x1**(-p[7])))*\
    #(p[0] + p[3]*(((x2-p[1])/p[1])*(x1**(1.0/p[2]))) + p[4]*(((x2-p[1])/p[1])*(x1**(1.0/p[2])))**2 + p[5]*(((x2-p[1])/p[1])*(x1**(1.0/p[2])))**3)
    #plt.legend((str(NumA)), shadow=True, loc="upper right")
    #plt.plot(x2,y2, linestyle='dashed')
    #T+=1
"""
    
