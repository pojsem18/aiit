import scipy.io
import pandas as pd
import matplotlib.pyplot as plt


mat = scipy.io.loadmat('100.mat')
print mat['ecg'].size
print mat['ecg'][mat['ecg'].size/2-1]

mydata = {"ecg 1":[],"ecg 2":[]}
f = open("mdata.txt","w")
irow = 0
strrow = ""
for i in range(0,5000):
    mydata["ecg 1"].append(mat['ecg'][i][0])
    mydata["ecg 2"].append(mat['ecg'][i][1])
    
    strrow = strrow + "," + str(mat['ecg'][i][0])
    irow = irow + 1
    if irow == 30:
        f.write(strrow[1:] + ",\n")
        irow = 0
        strrow = ""

f.close()

data = pd.DataFrame(mydata)
data.to_csv("100.csv")

plt.plot(mydata["ecg 1"])
plt.show()