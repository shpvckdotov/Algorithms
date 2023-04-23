import pandas as pd
import numpy as np
import matplotlib.pyplot as plt



fileName = 'tests2.csv'
ds = pd.read_csv(fileName)
MidMid = ds.iloc[0, 0:10].values
Random = ds.iloc[1, 0:10].values
Centre = ds.iloc[2, 0:10].values
ThreeMid = ds.iloc[3, 0:10].values

t = np.arange(1,11,1)


plt.plot(t,MidMid,'b',label='MidMid')
plt.plot(t,Random,'g',label='Random')
plt.plot(t,Centre,'r',label='Centre')
plt.plot(t,ThreeMid,'k',label='ThreeMid')
plt.legend()
plt.show()


