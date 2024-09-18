import galois
import numpy as np
# find the rank of an NxN "Lights Out" game
for N in range(2,10):
    words = []
    for cidx in range(N):
        for ridx in range(N):
            words.append(np.zeros(N*N,dtype='int'))
            words[-1][cidx+ridx*N] = 1;
            if(cidx+1 < N):
                words[-1][cidx+1+ridx*N] = 1;
            if(cidx-1 >= 0):
                words[-1][cidx-1+ridx*N] = 1;
            if(ridx+1 < N):
                words[-1][cidx+(ridx+1)*N] = 1;
            if(ridx-1 >= 0):
                words[-1][cidx+(ridx-1)*N] = 1;
    mat = galois.GF2(words)
    rnk = np.linalg.matrix_rank(mat)
    print(N,N*N,rnk,N*N-rnk)

