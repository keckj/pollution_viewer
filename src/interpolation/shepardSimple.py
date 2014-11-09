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

# generating qt window
fig = plt.figure()
ax = fig.add_subplot(111)

# pysical parameters
Lx = 1.0   #Domain size x
Ly = 1.0   #Domain size y

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



# customasing and ploting options
plt.pcolormesh(mesh_x,mesh_y,density, shading='flat')
plt.title("Shepard simple interpolation")
plt.axis('image')
plt.draw()
if 'qt' in plt.get_backend().lower():
  QtGui.qApp.processEvents()


plt.show()
