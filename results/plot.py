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

i=(i+L/2)%L-L/2
j=(j+L/2)%L-L/2

x1=np.sqrt((2*i+j)**2+3*j**2)
x2=np.sqrt((2*i-0.5+j)**2+3*(j+0.5)**2)
x3=np.sqrt((2*i+j+0.5)**2+3*(j+0.5)**2)

n=[k for k in range(len(x1)) if x1[k]<5]

a1=np.abs(a1)
a2=np.abs(a2)
a3=np.abs(a3)

x=np.concatenate((x1,x2,x3))
a=np.concatenate((a1,a2,a3))
#e=np.concatenate((e1,e2,e3))
xa=np.concatenate(([x],[a])).T
xa=xa[xa[:,0].argsort()]

#site_label=[[(0,0,0),(0,0,0)],[(0,0,1),(0,0,2)],[(1,-1,2),(-1,1,1)],[(1,0,0),(0,1,0)],[(1,-1,0),(-1,1,0)],[(1,0,2),(0,1,1)],[(1,0,1),(0,1,2)],[(1,1,0),(-1,-1,0)],[(2,-1,2),(2,-2,2)],[(2,-1,0),(1,-2,0)],[(2,-2,0),(-2,2,0)],[(2,0,0),(-2,0,0)],[(1,1,1),(2,-1,1)],[(2,0,2),(2,-2,1)],[(2,0,1),(-3,0,1)]]

#label = np.arange(15)
#chi = np.zeros(15)
#err = np.zeros(15)
#a=[a1,a2,a3]
#e=[e1,e2,e3]


#for i in label:
#    for j in range(2):
#        site=site_label[i][j]
#        chi[i]+=a[site[2]][ ((site[0]+32)%32)*32 +(site[1]+32)%32 ]
#        err[i]+=e[site[2]][ ((site[0]+32)%32)*32 +(site[1]+32)%32 ]**2/4.0
#    chi[i]/=2.0
#    err[i]=np.sqrt(err[i])

#chi=np.abs(chi)

#res=np.array([label,chi,err]).T

#print(res)

#plt.figure(figsize=(9,9))
#plt.yscale("log")
#plt.errorbar(label,chi,err,fmt="o-",ms=3,elinewidth=1,capsize=3)


#for a in range(len(xae)):
#    if xae[a][0]<5:
#        plt.errorbar(xae[a][0],xae[a][1],xae[a][2],fmt="o",ms=2,elinewidth=1,capsize=3)
#plt.plot(x1,a1,"o")
#plt.plot(x2,a2,"o")
#plt.plot(x3,a3,"o")
plt.figure(figsize=(9,9))
plt.yscale("log")
for i in n:
    plt.plot(x1[i],a1[i],'o')
    plt.plot(x2[i],a2[i],'o')
    plt.plot(x3[i],a3[i],'o')

plt.savefig((sys.argv[argn][:-4]+".png"))
