# linear algebra package
import numpy as np
# graphical display package
import pyqtgraph as pg
import matplotlib.pyplot as plt
# Qt
from PySide import QtGui
# linerar solver
import scipy.linalg as solver

#=================================#
# Shepard Quadratic interpolation:
#=================================#

# weigth computation module
import weightFunction

# Q_i(pos) = f_i + a_i0*(x-x_i) + a_i1*(y-y_i)
#			+ a_i2*(x-x_i)**2 + ai3*(y-y_i)**2
# compute the coeficient corresonping to a_i,k
def qTerm(k,i,pos,pos_i):
	if (k==0):
		return pos[0] - pos_i[0]
	elif (k==1):
		return pos[1] - pos_i[1]
	elif (k==2):
		return (pos[0] - pos_i[0])**2
	elif (k==3):
		return (pos[1] - pos_i[1])**2

	return 0

# 4 * 4 matrix
# M(k,l) = sum(j=1,n)*phi_i(x_j) * qTerm(l) * qTerm(k)
def computeMatrixTerm(k,l,i,n,knownPos):
	s = 0
	pos_i = knownPos[i] 
	for j in range(n):
		if j != i:
			pos_j = knownPos[j] 
			s += weightFunction.phi(i,pos_j,knownPos)*qTerm(k,i,pos_j,pos_i)*qTerm(l,i,pos_j,pos_i)
	return s

def Q(i,pos,knownPos,f):
	pos_i = knownPos[i] 
	n = len(f)

	M = np.zeros((4,4))

	for l in range(4):
		for k in range(4):
			M[l,k] = computeMatrixTerm(k,l,i,n,knownPos)

	b = np.zeros(4)
	s = 0
	f_i = f[i]
	for j in range(n):
		if j!=i:
			f_j = f[j]
			pos_j = knownPos[j] 
			s += weightFunction.phi(i,pos_j,knownPos)*(f_i-f_j)
	b.fill(s)

	# Mx = b
	x = solver.solve(M,b)

	q = f_i
	for k in range(4):
		q += x[k]*qTerm(k,i,pos,pos_i)

	return q


# display grid mesh = [mesh_x,mesh_y], mesh_x: np array of size NX, mesh_y: np array of size NY
# knownPos list of two arrays (x_known and y_known) corresponding to the location where we know our data
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



	n = len(f)


	# interpolating
	for i in range(NX):
		for j in range(NY):
			x_vec = np.array([mesh_x[i],mesh_y[j]]) 
			F_x = 0
			s_w = 0
			for k in range(n):
				w = weightFunction.shepardQuadraticWeights(k,x_vec,knownPos)
				s_w += w
				q = Q(k,x_vec,knownPos,f)
				F_x += w * q

			density[i,j] = F_x/s_w

