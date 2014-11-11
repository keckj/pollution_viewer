# linear algebra package
import numpy as np
# graphical display package
import pyqtgraph as pg
import matplotlib.pyplot as plt
# Qt
from PySide import QtGui
# binomial coeficient
from scipy.special import binom
# linerar solver
import scipy.linalg as solver

#=================================#
# Least Squared interpolation:
#=================================#

# compute B_i^n(x) : berstein polynom
def berstein(i,n,x):
	binom_coeff = binom(n, i)
	return binom_coeff * (x**i) * ( (1-x)**(n-i) )


# compute M matrix
def computeM(M,n,m,knownPos):
	N = len(knownPos)

	for i in range(n):
		for j in range(m):

			for k in range(n):
				for l in range(m):
					T = i*(n)+j
					K = k*(m)+l

					sigma = 0
					for s in range(N):
						x = knownPos[s]
						u_s = x[0]
						v_s = x[1]
						sigma += (berstein(i,n,u_s)*berstein(j,m,v_s))*(berstein(k,n,u_s)*berstein(l,m,v_s))
					M[T,K] = sigma

def computeA(A,n,m,knownPos):
	N = len(knownPos)

	for i in range(n):
		for j in range(m):
			I = i*(m)+j
			
			for s in range(N):
				x = knownPos[s]
				u_s = x[0]
				v_s = x[1]
				A[s,I] = berstein(i,n,u_s)*berstein(j,m,v_s)

def computeX(b,u,n,v,m):
	s = 0
	for k in range(n):
		for l in range(m):
			b1 = berstein(k,n,u)
			b2 = berstein(l,m,v)
			s += b[l+k*m]*b1*b2
	return s

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



	# we now need to compute the density value in point [mesh_x[i],mesh_y[j]]
	
	# postion of where the density is known
	x_known = knownPos[0]
	y_known = knownPos[1]

	N = len(f)
	P = f


	n = 3
	m = 3


	# interpolating
	A = np.zeros((N,n*m))
	print "starting to compute A"
	computeA(A,n,m,knownPos)
	print "A computation ended"

	print "transposing A"
	At = np.matrix.transpose(A)
	print "finshed transpose"

	M = np.zeros((n*m,n*m))
	print "starting to compute M"
	# computeM(M,n,m,knownPos)
	M = np.dot(At, A)	
	print "M computation ended"


	#  b = (At P)
	print "solving"
	b = solver.solve(M,np.dot(At,P))
	print b

	for i in range(NX):
		for j in range(NY):
			d = computeX(b,mesh_x[i],n,mesh_y[j],m)
			density[i,j] = d




