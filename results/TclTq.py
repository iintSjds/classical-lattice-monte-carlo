import numpy as np
import sys
from matplotlib import pyplot as plt
import os

L=16
argn=1

np.set_printoptions(threshold=np.nan,suppress=True)



fname=os.listdir(".")

Tc=[]
Tq=[]

for qname in fname:
    if(qname[0]=="q" and qname[-1]=='t' and os.path.getsize(qname)):
        i,j,a1,a2,a3=np.loadtxt(qname,unpack=True)
        Js=[]
        Fr=[]
        Jq=eval(qname[7:-4])
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
                #Fr.append(diff/err)

        Js=np.array(Js)
        Fr=np.array(Fr)

        Tc.append( 1.0/Js[np.argmin(Fr)])
        Tq.append(1.0/Jq)

Tq=np.array(Tq)
Tc=np.array(Tc)
print 1/Tc
print 1/Tq

print Tc
print Tq

plt.figure()
plt.xlim((0,2))
plt.ylim((0,3))
plt.plot(Tq,Tc,"o-")
plt.plot(Tq,4*Tq/3.0)
plt.savefig("tt.png")

