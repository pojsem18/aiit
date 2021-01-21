import numpy as np
from matplotlib.lines import Line2D
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib.widgets import Button

import os.path
import os

ecg_scope = []

FILENAME_ECGSCOPE = "ecgscope.csv"
FILENAME_ECGDATA = "ecg.csv"

class ECGScope(object):
    def __init__(self, ax, maxt=5, dt=1.0/360.0):
        self.ax = ax
        self.dt = dt
        self.maxt = maxt
        self.tdata = [0]
        self.ydata = [0]
        self.line = Line2D(self.tdata, self.ydata)
        self.ax.add_line(self.line)
        self.ax.set_ylim(-1000, 2000)
        self.ax.set_xlim(0, self.maxt)
        self.ecgdata = [0]
        self.zerovalue = 0
        self.heartbeat = True

    def update(self, y):
        if (os.path.exists(FILENAME_ECGDATA) == False) and (os.path.exists(FILENAME_ECGSCOPE) == True):
            f = open(FILENAME_ECGSCOPE, 'r').read().split('\n')
            self.ecgdata = []
            for data in f:
                if(len(data)):
                    self.ecgdata.append(float(data))

            lastt = self.tdata[-1]
            if (lastt + (len(self.ecgdata) * self.dt)) > (self.tdata[0] + self.maxt):
                self.tdata = []
                self.ydata = []
                self.ax.set_xlim(lastt + self.dt, lastt + self.maxt)
                self.ax.figure.canvas.draw()

            strcsv = "" 
            noise = np.random.normal(0, 1, len(self.ecgdata))
            for i in range(len(self.ecgdata)):
                lastt = lastt + self.dt
                self.tdata.append(lastt)
                if (self.heartbeat):
                    self.ydata.append(self.ecgdata[i])
                    strcsv = strcsv + str(self.ecgdata[i]) + "\n"
                else:
                    self.ydata.append(self.zerovalue)
                    strcsv = strcsv + str(self.zerovalue + noise[i]) + "\n"
            self.line.set_data(self.tdata, self.ydata)
        
            f = open(FILENAME_ECGDATA, 'w')
            f.write(strcsv)
            f.close()
            os.remove(FILENAME_ECGSCOPE)
        return self.line,

    def stop(self, event):
        self.heartbeat = False
        self.zerovalue = self.ecgdata[0]

    def go(self, event):
        self.heartbeat = True

def loadECGData():
    ecg=[[],[]]
    f = open('100.csv', 'r').read().split('\n')
    for data in f[1:]:
        data = data.split(',')
        if(len(data))==3:
            ecg[0].append(float(data[1]))
            ecg[1].append(float(data[2]))
    return ecg
            

def writeECGData():
    offset = 0
    buffersize = 720
    necg = len(ecg[0])
    #fidx = 0
    while True:
        if (os.path.exists(FILENAME_ECGSCOPE) == False):
            f = open(FILENAME_ECGSCOPE, 'w')
            for i in range(buffersize):
                f.write(str(ecg[0][offset]) + "\n")
                offset = (offset + 1) % necg
            f.close()
            yield 1
        else:
            yield -1

try:
    os.remove(FILENAME_ECGSCOPE)
except:
    pass
try:
    os.remove(FILENAME_ECGDATA)
except:
    pass


np.random.seed(19680801)
ecg = loadECGData()

fig, ax = plt.subplots()
ecgscope = ECGScope(ax)

axgo = plt.axes([0.8, 0.9, 0.1, 0.075])
axstop = plt.axes([0.7, .9, 0.1, 0.075])
bnstop = Button(axstop, 'Stop')
bngo = Button(axgo, 'Go')

bngo.on_clicked(ecgscope.go)
bnstop.on_clicked(ecgscope.stop)

ani = animation.FuncAnimation(fig, ecgscope.update, writeECGData, interval=1,
                              blit=True)

plt.show()