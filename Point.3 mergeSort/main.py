import pandas as pd
import numpy as np
import matplotlib.pyplot as plt



fileName = 'testMerge.csv'
ds = pd.read_csv(fileName)
Merge = ds.iloc[0, 0:10].values

t = np.arange(1,11,1)


plt.plot(t,Merge,'b',label='Merge')
plt.legend()
plt.show()


