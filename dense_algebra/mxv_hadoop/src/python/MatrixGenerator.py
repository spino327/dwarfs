#!/bin/python

'''
Created on Dec 4, 2014

Generates a nxn matrix A and a nx1 vector X.

@author: pinogal
'''
import sys
import random

USAGE = "USAGE: n <n = number of rows of the matrix> p_0 <p_0 probability of an element being zero (0 <= p_0 < 1)>" 

if __name__ == '__main__':
    '''
    USAGE: n <n = number of rows of the matrix> p_0 <p_0 probability of an element being zero (0 <= p_0 < 1)>
    '''
    
    if len(sys.argv) < 3:
        print USAGE
        sys.exit(1)
        
    n = int (sys.argv[1])
    n = n if n > 0 else 100
    p_0 = float (sys.argv[2])
    p_0 = p_0 if p_0 >= 0.0 and p_0 < 1.0 else 0.1
    seed = random.randint(0, 100) if len(sys.argv) == 3 else int (sys.argv[3]) 
    
    print "Working with n=", n ,", p_0=", p_0, ", seed=", seed
    
    random.seed (seed)
    
    matrix_file = open ("matrix.txt", "w")
    vector_file = open ("vector.txt", "w")
    
    # matrix and vector generation
    for row in range(n):
        # matrix
        for column in range(n):
            # writing non-zero element of the matrix
            if random.random() > p_0:
                a_ij = random.randint(1, 100)
                matrix_file.write(str(row) + "," + str(column) + "," + str(a_ij) + "\n")
        
        # vector
        x_i = random.gauss(0, 1)
        vector_file.write(str(row) + "," + str(x_i) + "\n")
                
    matrix_file.close()
    vector_file.close()
    print "Done"