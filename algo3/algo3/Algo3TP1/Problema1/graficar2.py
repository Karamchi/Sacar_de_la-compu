#import numpy as np
#import matplotlib.pyplot as plt
#import os
#from sys import argv
#import decimal

from pylab import *
import math

values = []

read_file = open('Tiempo')

lim=100.0
i=0
suma=0
n=1000
for line in read_file:
	value = int(line.split(" ")[1])
	suma=suma+value
	i=i+1
	if i==lim:
		i=0
		values.append((suma/lim))
		n=(n%20000)+1000
		suma=0


		
g1=values[0:19]	
g2=values[20:39]
g3=values[40:59]
#g4=values[60:79]

t=list(range(1000,20000,1000))

plot(t, g1, '--', label="Aleatorio") 
plot(t, g2, '.-', label="Mejor Caso")
plot(t, g3, label="Peor Caso") 
#plot(t, g4, label="Piramide")

legend()
ylabel('Tiempo (Ciclos)')
#ylim(0,0.0012)
#yscale('log')
xlabel('Tam. Entrada')
title('Tiempo de Computo')
grid(True)
show()
