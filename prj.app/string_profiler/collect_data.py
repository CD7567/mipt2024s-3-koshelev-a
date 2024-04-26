import subprocess
import sys
import numpy as np
import pandas as pd
from matplotlib import pyplot as plt


# Setup base data directory
BASE_DATA_DIR = f'{sys.path[0]}/../../prj.data/string-profiler'


# Run cmake compilation
subprocess.run(
    [
        'rm',
        '-rf',
        f'{sys.path[0]}/../../cmake-build-release',
    ]
)
subprocess.run(
    [
        'cmake',
        '-DCMAKE_BUILD_TYPE=Release',
        '-GNinja',
        '-B',
        f'{sys.path[0]}/../../cmake-build-release',
        f'{sys.path[0]}/../../'
    ]
)
subprocess.run(
    [
        'cmake',
        '--build',
        f'{sys.path[0]}/../../cmake-build-release'
    ]
)


# Clear data files if exist
subprocess.run(
    [
        'rm',
        f'{BASE_DATA_DIR}/data.csv',
    ]
)


# Register data collection runners
runners = [
    [
        f'{sys.path[0]}/../../cmake-build-release/prj.app/string-profiler',
        f'{BASE_DATA_DIR}/data.csv',
        sys.argv[1],
        sys.argv[2]
    ]
]


# Run data collection runners
procs = [subprocess.Popen(runner) for runner in runners]

for proc in procs:
    proc.wait()


# Read collected data for custom stacks from csv
df = pd.read_csv(f'{BASE_DATA_DIR}/data.csv', sep=',', skipinitialspace=True)
df_grouped = df.groupby(['TAG', 'METHOD', 'SIZE'], as_index=False).mean(numeric_only=True)


# Plots constructor
def create_graph(
        tags: list[str],
        method: str,
        title: str,
        legend: list[str],
        savefile: str
):
    dfs = [
        df_grouped[
            np.logical_and(
                df_grouped['TAG'] == f'{tag}',
                df_grouped['METHOD'] == method
            )
        ]
        for tag in tags
    ]

    colors = [
        'orange',
        'blue'
    ]

    fig = plt.figure()
    plt.grid()
    plt.title(title)
    plt.xlabel(r'$\mathrm{size}$')
    plt.ylabel(r'$\mathrm{time},\ \mathrm{ns}$')

    for frame, color in zip(dfs, colors):
        plt.plot(frame['SIZE'], frame['DURATION'], color=color, alpha=0.5)

    plt.legend(legend)

    plt.savefig(savefile, format='png', dpi=300)
    plt.close(fig)


create_graph(
    ['COPY', 'MOVE'],
    'CONSTRUCTION',
    'Comparison of copy/move construction',
    [
        r'Copy construction',
        r'Move construction'
    ],
    f'{BASE_DATA_DIR}/construction_cmp.png'
)

create_graph(
    ['COPY', 'MOVE'],
    'ASSIGNMENT',
    'Comparison of copy/move assignment',
    [
        r'Copy assignment',
        r'Move assignment'
    ],
    f'{BASE_DATA_DIR}/assignment_cmp.png'
)
