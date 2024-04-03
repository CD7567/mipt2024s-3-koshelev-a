import subprocess
import sys
import numpy as np
import pandas as pd
from matplotlib import pyplot as plt


# Setup base data directory
BASE_DATA_DIR = f'{sys.path[0]}/../../prj.data/stack-profiler'


# Run cmake compilation
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
        f'{sys.path[0]}/../../cmake-build-release/prj.app/stack-profiler',
        f'{BASE_DATA_DIR}/test_string.txt',
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
df_grouped = df.groupby(['TAG', 'METHOD', 'SIZE'], as_index=False).median(numeric_only=True)


# Pyplot params
plt.ioff()
plt.rcParams['text.usetex'] = True


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


# Create graphs for article
create_graph(
    ['ARRAY', 'STL_ARRAY'],
    'PUSH',
    'Comparison of array-based stacks push performance',
    [
        r'\texttt{StackArrT<T>}',
        r'\texttt{std::stack<T, std::vector<T>>}'
    ],
    f'{BASE_DATA_DIR}/array_push_cmp.png'
)

create_graph(
    ['ARRAY', 'STL_ARRAY'],
    'COPY_CONSTRUCTOR',
    'Comparison of array-based stacks copy construction performance',
    [
        r'\texttt{StackArrT<T>}',
        r'\texttt{std::stack<T, std::vector<T>>}'
    ],
    f'{BASE_DATA_DIR}/array_copy_constructor_cmp.png'
)

create_graph(
    ['LIST', 'STL_LIST'],
    'PUSH',
    'Comparison of list-based stacks push performance',
    [
        r'\texttt{StackLstT<T>}',
        r'\texttt{std::stack<T, std::list<T>>}'
    ],
    f'{BASE_DATA_DIR}/list_push_cmp.png'
)

create_graph(
    ['LIST', 'STL_LIST'],
    'COPY_CONSTRUCTOR',
    'Comparison of list-based stacks copy construction performance',
    [
        r'\texttt{StackLstT<T>}',
        r'\texttt{std::stack<T, std::list<T>>}'
    ],
    f'{BASE_DATA_DIR}/list_copy_constructor_cmp.png'
)
