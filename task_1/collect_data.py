import subprocess
import sys
import numpy as np
import pandas as pd
from matplotlib import pyplot as plt


# Setup base data directory
BASE_DATA_DIR = f'{sys.path[0]}/data'


# Run cmake compilation
subprocess.run(
    [
        'cmake',
        '-DCMAKE_BUILD_TYPE=Release',
        '-GNinja',
        '-B',
        f'{sys.path[0]}/../cmake-build-release',
        f'{sys.path[0]}/../'
    ]
)
subprocess.run(
    [
        'cmake',
        '--build',
        f'{sys.path[0]}/../cmake-build-release'
    ]
)


# Clear data files if exist
subprocess.run(
    [
        'rm',
        f'{BASE_DATA_DIR}/custom_data.csv',
        f'{BASE_DATA_DIR}/stl_data.csv'
    ]
)


# Register data collection runners
runners = [
    [
        f'{sys.path[0]}/../cmake-build-release/task_1/task-1-runner',
        f'{BASE_DATA_DIR}/test_string.txt',
        f'{BASE_DATA_DIR}/custom_data.csv',
        'true',
        sys.argv[1],
        sys.argv[2]
    ],
    [
        f'{sys.path[0]}/../cmake-build-release/task_1/task-1-stl-runner',
        f'{BASE_DATA_DIR}/test_string.txt',
        f'{BASE_DATA_DIR}/stl_data.csv',
        'true',
        sys.argv[1],
        sys.argv[2]
    ]
]


# Run data collection runners
procs = [subprocess.Popen(runner) for runner in runners]

for proc in procs:
    proc.wait()


# Read collected data for custom stacks from csv
df_custom = pd.read_csv(f'{BASE_DATA_DIR}/custom_data.csv', sep=',', skipinitialspace=True)
df_stl = pd.read_csv(f'{BASE_DATA_DIR}/stl_data.csv', sep=',', skipinitialspace=True)

df_custom_grouped = df_custom.groupby(['TAG', 'METHOD', 'SIZE'], as_index=False).median(numeric_only=True)
df_stl_grouped = df_stl.groupby(['TAG', 'METHOD', 'SIZE'], as_index=False).median(numeric_only=True)


# Pyplot params
plt.ioff()
plt.rcParams['text.usetex'] = True


# Plots constructor
def create_graph(
        tag: str,
        method: str,
        title: str,
        legend: list,
        contains_virtual: bool,
        savefile: str
):
    df_custom_plot = df_custom_grouped[
        np.logical_and(
            df_custom_grouped['TAG'] == f'{tag}',
            df_custom_grouped['METHOD'] == method
        )
    ]
    df_stl_plot = df_stl_grouped[
        np.logical_and(
            df_stl_grouped['TAG'] == f'{tag}',
            df_stl_grouped['METHOD'] == method
        )
    ]

    fig = plt.figure()
    plt.grid()
    plt.title(title)
    plt.xlabel(r'$\mathrm{size}$')
    plt.ylabel(r'$\mathrm{time},\ \mathrm{ns}$')

    plt.plot(df_custom_plot['SIZE'], df_custom_plot['DURATION'], color='orange', alpha=0.5)

    if contains_virtual:
        df_custom_v_array_plot = df_custom_grouped[
            np.logical_and(
                df_custom_grouped['TAG'] == f'VIRT_{tag}',
                df_custom_grouped['METHOD'] == method
            )
        ]

        plt.plot(df_custom_v_array_plot['SIZE'], df_custom_v_array_plot['DURATION'], color='magenta', alpha=0.5)

    plt.plot(df_stl_plot['SIZE'], df_stl_plot['DURATION'], color='blue', alpha=0.5)

    plt.legend(legend)

    plt.savefig(savefile, format='png', dpi=300)
    plt.close(fig)


# Create graphs for article
create_graph(
    'ARRAY',
    'PUSH',
    'Comparison of array-based stacks push performance',
    [
        r'\texttt{stack-lib::ArrayStack<T>}',
        r'\texttt{dynamic_cast<stack-lib::AbstractStack<T>>}',
        r'\texttt{std::stack<T, std::vector<T>>}'
    ],
    True,
    f'{BASE_DATA_DIR}/array_push_cmp.png'
)

create_graph(
    'ARRAY',
    'COPY_CONSTRUCTOR',
    'Comparison of array-based stacks copy construction performance',
    [
        r'\texttt{stack-lib::ArrayStack<T>}',
        r'\texttt{std::stack<T, std::vector<T>>}'
    ],
    False,
    f'{BASE_DATA_DIR}/array_copy_constructor_cmp.png'
)

create_graph(
    'LIST',
    'PUSH',
    'Comparison of list-based stacks push performance',
    [
        r'\texttt{stack-lib::ListStack<T>}',
        r'\texttt{dynamic_cast<stack-lib::AbstractStack<T>>}',
        r'\texttt{std::stack<T, std::list<T>>}'
    ],
    True,
    f'{BASE_DATA_DIR}/list_push_cmp.png'
)

create_graph(
    'LIST',
    'COPY_CONSTRUCTOR',
    'Comparison of list-based stacks copy construction performance',
    [
        r'\texttt{stack-lib::ListStack<T>}',
        r'\texttt{std::stack<T, std::list<T>>}'
    ],
    False,
    f'{BASE_DATA_DIR}/list_copy_constructor_cmp.png'
)