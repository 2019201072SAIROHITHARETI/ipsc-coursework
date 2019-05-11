import numpy as np
from pprint import pprint

def householder(v):
    v = np.copy(v)
    normx = np.linalg.norm(v)
    s = -v[0]/abs(v[0])
    u1 = v[0] - s*normx
    w = v / u1
    w[0] = 1
    I = np.eye(len(v))
    P = I - (2 / np.dot(w, w)) * np.dot(w[:, None], w[None, :])
    return P

def my_qr(A):
    m, n = A.shape
    Q = np.eye(m)
    R = np.copy(A)
    for i in range(n - (m == n)):
        H = np.eye(m)
        H[i:, i:] = householder(R[i:, i])
        Q = np.dot(Q, H)
        R = np.dot(H, R)
    return Q, R

def backward(U, b):
    n = len(b)
    y = b.copy()
    for i in range(n-1,-1,-1):
        t = b[i]
        for j in range(i+1,n):
            t = t - U[i, j]*y[j]
        y[i] = t/U[i, i]
    return y

def qr_solve(A, b):
    Q, R = my_qr(A)
    pprint(Q)
    pprint(R)
    t = np.dot(Q.T, b.reshape(len(b),1))
    x = backward(R, t)
    return x.flatten()


if __name__ == "__main__":
    A = np.array([[1, 1, 1], [4, 3, -1], [3, 5, 3]]).astype(float)
    b = np.array([1, 6 ,4]).astype(float)
    x = qr_solve(A, b)
    print("x")
    pprint(x)
    error = np.linalg.norm(b - np.dot(A,x.reshape(len(x),1)).flatten())
    pprint("Error: {0}".format(error))