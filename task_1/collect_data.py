import subprocess
import sys
import math
import numpy as np
import pandas as pd
from matplotlib import pyplot as plt

# Run cmake compilation
subprocess.run(["cmake", "-DCMAKE_BUILD_TYPE=Release", "-B", "build", "."])
subprocess.run(["cmake", "--build", "build"])

# Run data collection runner
subprocess.run(["./build/runner", sys.argv[1], sys.argv[2]])

# Read collected data from csv
df = pd.read_csv("./data/data.csv", sep=',', skipinitialspace=True)

# Pyplot params
plt.ioff()
plt.rcParams['text.usetex'] = True

# Create push graph for array stack
METHOD = 'PUSH'


array_df = df[df['TAG'] == 'ARRAY']
array_method_df = array_df[array_df['METHOD'] == METHOD].dropna()
array_method_df_median = array_method_df.groupby(['SIZE'], as_index=False).median(numeric_only=True)


spike_indices = [2 ** i for i in range(math.ceil(math.log(max(array_method_df_median['SIZE']), 2)))]
spikes = [array_method_df_median['DURATION'][i] for i in spike_indices]
coef = np.polyfit(spike_indices, spikes, 1)
poly = np.poly1d(coef)


fig = plt.figure()
plt.grid()

plt.title(r'Time measurement of push for array stack')
plt.xlabel(r'size')
plt.ylabel(r'time, $\mathrm{ns}$')

plt.plot(array_method_df_median['SIZE'], array_method_df_median['DURATION'], color='orange')
plt.errorbar(spike_indices, spikes, fmt='.', color='black')
plt.plot(array_method_df_median['SIZE'], poly(array_method_df_median['SIZE']), color='red', linestyle='--')
plt.axhline(y=np.median([i for i in array_method_df_median['SIZE'] if not i in spike_indices]), color='green', linestyle='--')

plt.legend(['Estimated time', 'Linear fit of spikes', 'Median of bottom values'])
plt.savefig('./data/array_push.png', format = 'png')
plt.close(fig)


# Create push graph for list_stack

list_df = df[df['TAG'] == 'LIST']
list_method_df = list_df[list_df['METHOD'] == METHOD].dropna()
list_method_df_median = list_method_df.groupby(['SIZE'], as_index=False).median(numeric_only=True)

fig = plt.figure()
plt.grid()

plt.title(r'Time measurement of push for list stack')
plt.xlabel(r'size')
plt.ylabel(r'time, $\mathrm{ns}$')

plt.plot(list_method_df_median['SIZE'], list_method_df_median['DURATION'], color="blue")

plt.savefig('./data/list_push.png', format = 'png')
plt.close(fig)


# Create copy constructor graph for array stack
METHOD = 'COPY_CONSTRUCTOR'


array_df = df[df['TAG'] == 'ARRAY']
array_method_df = array_df[array_df['METHOD'] == METHOD].dropna()
array_method_df_median = array_method_df.groupby(['SIZE'], as_index=False).median(numeric_only=True)


spike_indices = [2 ** i for i in range(math.ceil(math.log(max(array_method_df_median['SIZE']), 2)))]
spikes = [array_method_df_median['DURATION'][i] for i in spike_indices]
coef = np.polyfit(array_method_df_median['SIZE'], array_method_df_median['DURATION'], 1)
poly = np.poly1d(coef)


fig = plt.figure()
plt.grid()

plt.title(r'Time measurement of copy constructor for array stack')
plt.xlabel(r'size')
plt.ylabel(r'time, $\mathrm{ns}$')

plt.plot(array_method_df_median['SIZE'], array_method_df_median['DURATION'], color='orange')
plt.errorbar(spike_indices, spikes, fmt='.', color='black')
plt.plot(array_method_df_median['SIZE'], poly(array_method_df_median['SIZE']), color='green', linestyle='--')

plt.legend(['Estimated time', 'Linear fit'])
plt.savefig('./data/array_copy_constructor.png', format = 'png')
plt.close(fig)


# Create copy constructor graph for list_stack

list_df = df[df['TAG'] == 'LIST']
list_method_df = list_df[list_df['METHOD'] == METHOD].dropna()
list_method_df_median = list_method_df.groupby(['SIZE'], as_index=False).median(numeric_only=True)


fig = plt.figure()
plt.grid()

plt.title(r'Time measurement of copy constructor for list stack')
plt.xlabel(r'size')
plt.ylabel(r'time, $\mathrm{ns}$')

plt.plot(list_method_df_median['SIZE'], list_method_df_median['DURATION'], color="blue")


plt.savefig('./data/list_copy_constructor.png', format = 'png')
plt.close(fig)
