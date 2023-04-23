import pandas as pd
import numpy as np
import matplotlib.pyplot as plt



fileName = 'test.csv'
ds = pd.read_csv(fileName)
select = ds.iloc[0, 0:10].values
insert = ds.iloc[1, 0:10].values
bubble = ds.iloc[2, 0:10].values

t = np.arange(1,11,1)


plt.plot(t,select,'b--',label='selectionSort')
plt.plot(t,insert,'g',label='insertionSort')
plt.plot(t,bubble,'r-.',label='bubbleSort')
plt.legend()
plt.show()


