import numpy as np
from pprint import pprint

def mylu(A):
    A = A.copy()
    n = len(A)
    for k in range(n-1):
        A[k+1, k] = A[k+1, k]/A[k, k]
        for i in range(k+1,n):
            for j in range(k+1,n):
                A[i, j] = A[i, j] - A[i, k]*A[k, j]
    return A

def forward(L, b):
    n = len(b)
    y = b.copy()
    for i in range(n):
        t = b[i]
        if(i > 0):
            t = t - L[i, i-1]*y[i-1]
        y[i] = t
    return y

def backward(U, b):
    n = len(b)
    y = b.copy()
    for i in range(n-1,-1,-1):
        t = b[i]
        for j in range(i+1,n):
            t = t - U[i, j]*y[j]
        y[i] = t/U[i, i]
    return y

def lu_solve(A, b):
    L = U = mylu(A)
    t = forward(L, b)
    x = backward(U, t)
    return x

if __name__ == "__main__":
    A = np.array([[1, 1, 1], [4, 3, -1], [0, 5, 3]]).astype(float)
    b = np.array([1, 6 ,4]).astype(float)
    x = lu_solve(A, b)
    print("x")
    pprint(x)
    error = np.linalg.norm(b - np.dot(A,x.reshape(len(x),1)).flatten())
    pprint("Error: {0}".format(error))