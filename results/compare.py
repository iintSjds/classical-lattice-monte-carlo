import numpy as np
import sys
from matplotlib import pyplot as plt

L=16
argn=1

np.set_printoptions(threshold=np.nan,suppress=True)

for i in range(len(sys.argv)):
    print sys.argv[i]

if len(np.loadtxt(sys.argv[argn],unpack=True))==5:
    i,j,a1,a2,a3=np.loadtxt(sys.argv[argn],unpack=True)
else:
    i,j,a1,e1,a2,e2,a3,e3=np.loadtxt(sys.argv[argn],unpack=True)

if len(np.loadtxt(sys.argv[argn+1],unpack=True))==5:
    i,j,b1,b2,b3=np.loadtxt(sys.argv[argn+1],unpack=True)
else:
    i,j,b1,e1,b2,e2,b3,e3=np.loadtxt(sys.argv[argn+1],unpack=True)

print np.sqrt(np.sum( (a1-b1)**2+(a2-b2)**2+(a3-b3)**2 )/16./16./3.)
print np.sqrt(np.sum( (e1)**2+(e2)**2+(e3)**2 )/16./16./3.)
