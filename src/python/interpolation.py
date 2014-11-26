# linear algebra package
import numpy as np
# graphical display package
import pyqtgraph as pg
import matplotlib.pyplot as plt
# Qt
from PySide import QtGui

#=================================#
#	computes and display a square mesh
#	by interpolating specified values
#=================================#

# simple shepard's interpolation
import shepardSimple
# quadratically modified shepard
import shepardQuadratic
# least squared
import leastSquared
# multi quadrics
import multiQuadrics

# generating qt window
fig = plt.figure()
ax = fig.add_subplot(111)

# pysical parameters
Lx = 1.0   #Domain size x
Ly = 1.0   #Domain size y
n = 4 # data length


# generating mesh
NX = 200        #Number of grid points in x
NY = 200        #Number of grid points in y
dx = Lx/(NX-1) #Grid step in x (space)
dy = Ly/(NY-1) #Grid step in y (space)

mesh_x = np.linspace(0,Lx,NX)
mesh_y = np.linspace(0,Ly,NY)
mesh = [mesh_x,mesh_y]

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
# shepardSimple.interpolate(mesh,f,knownPos,density)	
# shepardQuadratic.interpolate(mesh,f,knownPos,density)	
# leastSquared.interpolate(mesh,f,knownPos,density)
multiQuadrics.interpolate(mesh,f,knownPos,density)

# customasing and ploting options
plt.pcolormesh(mesh_x,mesh_y,density, shading='flat')

plt.title("Hardy's multi quadrics")
plt.axis('image')
plt.draw()
plt.colorbar()
if 'qt' in plt.get_backend().lower():
  QtGui.qApp.processEvents()


plt.show()


# interpolating
shepardSimple.interpolate(mesh,f,knownPos,density)	

# customasing and ploting options
plt.pcolormesh(mesh_x,mesh_y,density, shading='flat')

plt.title("Shepard simple interpolation")
plt.axis('image')
plt.draw()
plt.colorbar()
if 'qt' in plt.get_backend().lower():
  QtGui.qApp.processEvents()


plt.show()
