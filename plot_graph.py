#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import matplotlib.pyplot as plt

file_d= open("veb.txt", 'r')
file_data= file_d.readlines()
li1=[]
for t in file_data:
    li1.append(int(t))   
file_d= open("union_find.txt", 'r')
file_data= file_d.readlines()
li2=[]
for t in file_data:
    li2.append(int(t))
file_d = open("avl.txt", 'r')
file_data= file_d.readlines()
li3=[]
for t in file_data:
    li3.append(int(t))
edges= []
N = 100
n = 0
for i in range(200):
    n += (2*N)
    edges.append(2*n+1)

plt.plot(edges,li1, 'r', label='vBE TREE')
plt.plot(edges,li2, 'b', label='union_find')
plt.plot(edges,li3 ,'g', label='AVL TREE')

plt.xlabel('NUMBER OF EDGES')
plt.ylabel('TIME OF EXECUTION (MICROSECONDS)')


legend = plt.legend(loc='upper center')
legend.get_frame().set_facecolor('C0')

plt.show()
