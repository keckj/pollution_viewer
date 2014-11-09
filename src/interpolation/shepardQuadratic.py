# linear algebra package
import numpy as np
# graphical display package
import pyqtgraph as pg
import matplotlib.pyplot as plt
# Qt
from PySide import QtGui

#=================================#
# Shepard Quadratic interpolation:
#=================================#

# weigth computation module
import weightFunction

# display grid mesh = [mesh_x,mesh_y], mesh_x: np array of size NX, mesh_y: np array of size NY
# knowValues list of two arrays (x_known and y_known) corresponding to the location where we know our data
# f = data value at point [knownPos_x[i],knownPos_y[i]]
# density : we interpolate at each point of the mesh a corresponding density value 
def interpolate(mesh,f,knownPos,density):
	
	# recovering mesh
	mesh_x = mesh[0]
	mesh_y = mesh[1]

	NX = len(mesh_x)        #Number of grid points in x
	NY = len(mesh_y)        #Number of grid points in y



	# we now need to compute the density value in point [mesh_x[i],mesh_y[i]]
	# this will be done via Shepard's methode
	# F(x) = sum(i=1,n) w_i(x) f_i , where w_i(x) : Shepard's weights f_i data


	# postion of where the density is known
	x_known = knownPos[0]
	y_known = knownPos[1]

	n = len(f)


	# interpolating
	for i in range(NX):
		for j in range(NY):
			x_vec = np.array([mesh_x[i],mesh_y[j]]) 
			F_x = 0
			for k in range(n):
				w = weightFunction.shepardQuadraticWeights(k,x_vec,knownPos)
				F_x += w * f[k]

			density[i,j] = F_x

