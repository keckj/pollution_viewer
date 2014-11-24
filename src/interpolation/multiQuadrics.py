# linear algebra package
import numpy as np
# graphical display package
import pyqtgraph as pg
import matplotlib.pyplot as plt
# Qt
from PySide import QtGui
# linerar solver
import scipy.linalg as solver
# maths
import math

#=================================#
# Hardy's multi quadric interpolation:
#=================================#

# compue dist(a,b)
# a,b: two np arrays
def dist(a,b):
	d = np.linalg.norm(a-b)
	return d

def hardy(i,pos,knownPos):
	n = len(knownPos)
	x = pos[0]
	y = pos[1]
	x_i = knownPos[i][0]
	y_i = knownPos[i][1]

	delta_min = 10**(-10)
	delta_max = 10**(-2)

	delta_i = delta_min * (delta_max/delta_min)**((i-1)/(n-1))

	return math.sqrt(dist(x,x_i)**2 + dist(y,y_i)**2 + delta_i)



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


	# postion of where the density is known

	n = len(f)


	# interpolating
	# none optimized loop
	M = np.zeros((n,n))
	for i in range(n):
		for j in range(n):
			pos_i = knownPos[i]
			pos_j = knownPos[j]
			M[i,j] = hardy(i,pos_j,knownPos)


	# Mc = f
	c = solver.solve(M,f)

	for i in range(n):
		F_i = 0
		x_vec = knownPos[i]
		for k in range(n):
			F_i += c[k]*hardy(k,x_vec,knownPos)

	for i in range(NX):
		for j in range(NY):
			x_vec = np.array([mesh_x[i],mesh_y[j]]) 
			F_x = 0
			for k in range(n):
				x_k = knownPos[k]
				F_x += c[k] * hardy(k,x_vec,knownPos)

			density[i,j] = F_x