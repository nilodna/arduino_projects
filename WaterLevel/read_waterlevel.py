import pandas as pd
import matplotlib.pyplot as plt
import sys

if len(sys.argv) > 1:
    fname = sys.argv[1]
else:
    fname = 'TRIAL02.csv'

fout = fname.replace('.csv', '.png')

df = pd.read_csv(fname, delimiter=';')

df = df.set_index('Time')
df.index = pd.to_datetime(df.index)

df[['T_INT', 'T_EXT']].plot()
plt.savefig(fout.replace('.png', '_raw.png'))

dfhourly = df.resample('1H').mean() #1800S

dfhourly[['T_INT', 'T_EXT']].plot()
plt.savefig(fout.replace('.png', '_hourly.png'))
