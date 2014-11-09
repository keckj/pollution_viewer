# linear algebra package
import numpy as np
# graphical display package
import pyqtgraph as pg
import matplotlib.pyplot as plt
# Qt
from PySide import QtGui

#=================================#
# Shepard Simple interpolation:
#	computes and display a square mesh
#	by interpolating specified values
#=================================#

# weigth computation module
import weightFunction

# generating qt window
fig = plt.figure()
ax = fig.add_subplot(111)

# pysical parameters
Lx = 1.0   #Domain size x
Ly = 1.0   #Domain size y
n = 7 # data length


# generating mesh
NX = 50        #Number of grid points in x
NY = 50        #Number of grid points in y
dx = Lx/(NX-1) #Grid step in x (space)
dy = Ly/(NY-1) #Grid step in y (space)

mesh_x = np.linspace(0,Lx,NX)
mesh_y = np.linspace(0,Ly,NY)

density = np.zeros((NX,NY))


# we now need to compute the density value in point [mesh_x[i],mesh_y[i]]
# this will be done via Shepard's methode
# F(x) = sum(i=1,n) w_i(x) f_i , where w_i(x) : Shepard's weights f_i data

# data generation
f = np.random.random_sample((n,)) # generating random data between 0 and 1
# f.fill(0)
# f[1] = 1

# postion of where the density is known
x_known = np.random.random_sample((n,))
y_known = np.random.random_sample((n,))

knownPos = []
for i in range(n):
	knownPos.append(np.array([x_known[i],y_known[i]]))


# interpolating
# none optimized loop
for i in range(NX):
	for j in range(NY):
		x_vec = np.array([mesh_x[i],mesh_y[j]]) 
		F_x = 0
		for k in range(n):
			w = weightFunction.shepardSimpleWeights(k,x_vec,knownPos)
			F_x += w * f[k]

		density[i,j] = F_x
		

# customasing and ploting options
plt.pcolormesh(mesh_x,mesh_y,density, shading='flat')

plt.title("Shepard simple interpolation")
plt.axis('image')
plt.draw()
plt.colorbar()
if 'qt' in plt.get_backend().lower():
  QtGui.qApp.processEvents()


plt.show()
