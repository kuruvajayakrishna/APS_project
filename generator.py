#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import math
import matplotlib.pyplot as plt
import random
import os
N = 100
n = 0
for i in range(200):
    fname = "file_"+str(i) + ".txt"
    fd = open(fname, 'w+')
    print(i)
    n += (5*N) 
    fd.write(str(n+1) + '\n')
    fd.write(str(2*n+1)+ '\n')

    for i in range(0,n):
        fd.write(str(i) + " " + str( i+1) + " " + str( random.randint(1,1000)) + '\n')
    
	
    fd.write(str(n) + " " + str( 0) + " " + str( random.randint(1,1000)) + '\n')

    for i in range(0,n):
        a = random.randint(1,n-1)
        b = random.randint(1,n-1)
        c = random.randint(1,10000)
        fd.write(str(a) + " " + str(b) + " " + str(c) + '\n')
    
    fd.close()