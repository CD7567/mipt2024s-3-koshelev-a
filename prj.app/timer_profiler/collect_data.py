import subprocess
import sys
import numpy as np
import pandas as pd
from py_markdown_table.markdown_table import markdown_table


# Setup base data directory
BASE_DATA_DIR = f'{sys.path[0]}/../../prj.data/timer-profiler'


# Run cmake compilation without internal measurement
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
        f'{BASE_DATA_DIR}/data_internal.csv'
    ]
)


# Register data collection runners
runners = [
    [
        f'{sys.path[0]}/../../cmake-build-release/prj.app/timer-profiler',
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


# Run cmake compilation with internal measurement
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
        '-DDO_ON_TIME=ON',
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


# Register data collection runners
runners = [
    [
        f'{sys.path[0]}/../../cmake-build-release/prj.app/timer-profiler',
        f'{BASE_DATA_DIR}/test_string.txt',
        f'{BASE_DATA_DIR}/data_internal.csv',
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
df_internal = pd.read_csv(f'{BASE_DATA_DIR}/data_internal.csv', sep=',', skipinitialspace=True)


df = df.groupby(['TAG', 'METHOD'], as_index=False).mean(numeric_only=True)
df_internal = df_internal.groupby(['TAG', 'METHOD'], as_index=False).mean(numeric_only=True)

tags = [
    "ARRAY",
    "LIST"
]

classes = [
    "StackArrT",
    "StackLstT"
]

methods = [
    "COPY_CONSTR",
    "COPY_ASSIGN",
    "MOVE_CONSTR",
    "MOVE_ASSIGN",
    "IS_EMPTY",
    "SIZE",
    "PUSH",
    "POP",
    "TOP",
]

zipped = []

for tag, clazz in zip(tags, classes):
    for method in methods:
        zipped.append((tag, clazz, method))

data = [
    {
        "method": f"{clazz}_{method}",
        "External w/o internal": np.trunc(df[np.logical_and(df["TAG"] == tag, df['METHOD'] == method)].iloc[0]["DURATION"]),
        "External w internal": np.trunc(df_internal[np.logical_and(df_internal["TAG"] == tag, df_internal['METHOD'] == method)].iloc[0]["DURATION"]),
        "Internal": np.trunc(df_internal[np.logical_and(df_internal["TAG"] == "INTERNAL", df_internal['METHOD'] == f"{clazz}_{method}")].iloc[0]["DURATION"])
    }
    for (tag, clazz, method) in zipped
]

print(markdown_table(data).set_params(row_sep='markdown').get_markdown())
