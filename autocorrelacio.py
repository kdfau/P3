import matplotlib.pyplot as plt
import soundfile as sf
import numpy as np

#Llegim l'audio
audio, fm = sf.read("/home/miriam27/PAV/P3/pav_30ms.wav")

#Temps 
time = (np.linspace(0, len(audio)-1, len(audio)))/fm 
                                                 
#Calculem autocorrelació i axis
r = np.correlate(audio, audio, "same")
r = r / r[int(len(r)/2)] 
raxis = np.arange(len(r))

#Plots
plt.subplot(2,1,1)
plt.plot(time, audio, lineWidth=1)
plt.grid(True)
plt.xlabel("Temps(s)")
plt.ylabel("Amplitud")

plt.subplot(2,1,2)
plt.plot(raxis, r, lineWidth=1)
plt.grid(True)
plt.xlabel("Mostres")
plt.ylabel("Autocorrelacio")

plt.show()  