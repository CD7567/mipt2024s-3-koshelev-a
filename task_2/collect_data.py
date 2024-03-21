import subprocess
import sys
import numpy as np
import pandas as pd
from matplotlib import pyplot as plt


# Setup base data directory
BASE_DATA_DIR = f'{sys.path[0]}/data'


# Run cmake compilation with reading
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
        f'{BASE_DATA_DIR}/small.csv',
        f'{BASE_DATA_DIR}/medium.csv',
        f'{BASE_DATA_DIR}/small_nowrite.csv',
        f'{BASE_DATA_DIR}/medium_nowrite.csv'
    ]
)


# Register data collection runners
runners = [
    [
        f'{sys.path[0]}/../cmake-build-release/task_2/task-2-runner',
        f'{BASE_DATA_DIR}/data-small.json',
        f'{BASE_DATA_DIR}/small.csv',
        'true',
        sys.argv[1]
    ],
    [
        f'{sys.path[0]}/../cmake-build-release/task_2/task-2-lib-runner',
        f'{BASE_DATA_DIR}/data-small.json',
        f'{BASE_DATA_DIR}/small.csv',
        'false',
        sys.argv[1]
    ],
    [
        f'{sys.path[0]}/../cmake-build-release/task_2/task-2-runner',
        f'{BASE_DATA_DIR}/data-medium.json',
        f'{BASE_DATA_DIR}/medium.csv',
        'true',
        sys.argv[1]
    ],
    [
        f'{sys.path[0]}/../cmake-build-release/task_2/task-2-lib-runner',
        f'{BASE_DATA_DIR}/data-medium.json',
        f'{BASE_DATA_DIR}/medium.csv',
        'false',
        sys.argv[1]
    ]
]


# Run data collection runners
procs = [subprocess.Popen(runner) for runner in runners]

for proc in procs:
    proc.wait()


# Run cmake compilation without reading
subprocess.run(
    [
        'cmake',
        '-DCMAKE_BUILD_TYPE=Release',
        '-GNinja',
        '-DDO_JSON_SKIP_WRITING=ON',
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

# Register data collection runners
runners = [
    [
        f'{sys.path[0]}/../cmake-build-release/task_2/task-2-runner',
        f'{BASE_DATA_DIR}/data-small.json',
        f'{BASE_DATA_DIR}/small_nowrite.csv',
        'true',
        sys.argv[1]
    ],
    [
        f'{sys.path[0]}/../cmake-build-release/task_2/task-2-lib-runner',
        f'{BASE_DATA_DIR}/data-small.json',
        f'{BASE_DATA_DIR}/small_nowrite.csv',
        'false',
        sys.argv[1]
    ],
    [
        f'{sys.path[0]}/../cmake-build-release/task_2/task-2-runner',
        f'{BASE_DATA_DIR}/data-medium.json',
        f'{BASE_DATA_DIR}/medium_nowrite.csv',
        'true',
        sys.argv[1]
    ],
    [
        f'{sys.path[0]}/../cmake-build-release/task_2/task-2-lib-runner',
        f'{BASE_DATA_DIR}/data-medium.json',
        f'{BASE_DATA_DIR}/medium_nowrite.csv',
        'false',
        sys.argv[1]
    ]
]


# Run data collection runners
procs = [subprocess.Popen(runner) for runner in runners]

for proc in procs:
    proc.wait()


# Read collected data for custom stacks from csv
df_small = pd.read_csv(f'{BASE_DATA_DIR}/small.csv', sep=',', skipinitialspace=True)
df_small_write = pd.read_csv(f'{BASE_DATA_DIR}/small_nowrite.csv', sep=',', skipinitialspace=True)

df_medium = pd.read_csv(f'{BASE_DATA_DIR}/medium.csv', sep=',', skipinitialspace=True)
df_medium_write = pd.read_csv(f'{BASE_DATA_DIR}/medium_nowrite.csv', sep=',', skipinitialspace=True)


