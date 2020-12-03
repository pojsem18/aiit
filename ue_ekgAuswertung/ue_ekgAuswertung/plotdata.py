#import scipy.io
#import pandas as pd
import sys
import matplotlib.pyplot as plt

#print sys.argv

for i in range(len(sys.argv)- 1):
    mdata = []
    f = open(sys.argv[i+1], 'r').read().split('\n')
    for data in f:
        if(len(data)):
            mdata.append(float(data))

    plt.plot(mdata)
plt.show()