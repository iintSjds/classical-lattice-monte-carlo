import numpy as np
import sys
from matplotlib import pyplot as plt
import os

L=16
argn=1

np.set_printoptions(threshold=np.nan,suppress=True)

for i in range(len(sys.argv)):
    print sys.argv[i]

if len(np.loadtxt(sys.argv[argn],unpack=True))==5:
    i,j,a1,a2,a3=np.loadtxt(sys.argv[argn],unpack=True)
else:
    i,j,a1,e1,a2,e2,a3,e3=np.loadtxt(sys.argv[argn],unpack=True)

fname=os.listdir(".")

Js=[]
Fr=[]

for name in fname:
    if (name[0]=="J" and name[-1]=="t" and os.path.getsize(name)):
        if len(np.loadtxt(name,unpack=True))==5:
            i,j,b1,b2,b3=np.loadtxt(name,unpack=True)
        else:
            i,j,b1,e1,b2,e2,b3,e3=np.loadtxt(name,unpack=True)
        J=eval(name[1:-4])
        Js.append(J)
        diff=np.sqrt(np.sum( (a1-b1)**2+(a2-b2)**2+(a3-b3)**2 )/16./16./3.)
        err=np.sqrt(np.sum( (e1)**2+(e2)**2+(e3)**2 )/16./16./3.)
        Fr.append(diff-err)
        Fr.append(diff/err)

Js=np.array(Js)
Fr=np.array(Fr)

print Js[np.argmin(Fr)]

plt.figure()
plt.grid()
plt.plot(Js,Fr,"bo")
#plt.xlim((0,1))
#plt.ylim((-.001,0.005))
#plt.ylim((0.9,10))
plt.savefig(sys.argv[argn]+"sigma.png")
