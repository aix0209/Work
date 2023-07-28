#!/usr/bin/env python
# -*- coding: utf-8 -*-
import random
class test:
    def __init__(self,a,b,c):
        self.a=a
        self.b=b
        self.c=c

    def printfun(self):
        print(self.a)
        print(self.b)
        print(self.c)
        self.printabc()
        
    def printabc(self):
        print(self.a[3]*self.b[4])
d=[]
a=[1,2,3,4,5]
d.append(a)
b=a
c=a.copy()
test1=test(a,b,c)
a[1]=10
print(a)
print(b)
print(c)
print(d)
test1.printfun()
