import pandas as pd
import numpy as np
import matplotlib.pyplot as plt



fileName = 'testLSD.csv'
ds = pd.read_csv(fileName)
LSD = ds.iloc[0, 0:10].values

t = np.arange(1,11,1)


plt.plot(t,LSD,'r',label='LSD')
plt.legend()
plt.show()


