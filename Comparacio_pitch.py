#import matplotlib
#matplotlib.use('TkAgg')
import matplotlib.pyplot as plt
import numpy as np


#Read files
cPitch = np.loadtxt('rl006.f0')
wavesurferPitch = np.loadtxt('pitch_wavesurfer.f0')


#Time axis
temps = np.zeros(len(cPitch))
for i in range(len(cPitch)):
    temps[i] = i * 0.015


#Plotting the graph
plt.plot(temps, cPitch,'b', label = 'Calculat')
plt.plot(temps, wavesurferPitch,'g', label = 'Wavesurfer')

plt.xlabel('Temps(s)')
plt.ylabel('Frequencia(Hz)')
plt.title('Comparacio del pitch')
plt.legend(loc = 'upper right')
plt.savefig("Pitch")  