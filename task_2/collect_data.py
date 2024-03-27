import subprocess
import sys

import pandas
import pandas as pd
from py_markdown_table.markdown_table import markdown_table

# Setup base data directory
BASE_DATA_DIR = f'{sys.path[0]}/data'


# Run cmake compilation with reading
subprocess.run(
    [
        'rm',
        '-rf',
        f'{sys.path[0]}/../cmake-build-release',
    ]
)
subprocess.run(
    [
        'cmake',
        '-DCMAKE_BUILD_TYPE=Release',
        '-GNinja',
        '-B',
        f'{sys.path[0]}/../cmake-build-release',
        f'{sys.path[0]}/../',
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
        'rm',
        '-rf',
        f'{sys.path[0]}/../cmake-build-release',
    ]
)
subprocess.run(
    [
        'cmake',
        '-DCMAKE_BUILD_TYPE=Release',
        '-GNinja',
        '-DDO_JSON_SKIP_WRITING=ON',
        '-B',
        f'{sys.path[0]}/../cmake-build-release',
        f'{sys.path[0]}/../',
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
df_small_nowrite = pd.read_csv(f'{BASE_DATA_DIR}/small_nowrite.csv', sep=',', skipinitialspace=True)

df_medium = pd.read_csv(f'{BASE_DATA_DIR}/medium.csv', sep=',', skipinitialspace=True)
df_medium_nowrite = pd.read_csv(f'{BASE_DATA_DIR}/medium_nowrite.csv', sep=',', skipinitialspace=True)


df_small = df_small.groupby(['TAG'], as_index=False).median(numeric_only=True)
df_small_nowrite = df_small_nowrite.groupby(['TAG'], as_index=False).median(numeric_only=True)
df_medium = df_medium.groupby(['TAG'], as_index=False).median(numeric_only=True)
df_medium_nowrite = df_medium_nowrite.groupby(['TAG'], as_index=False).median(numeric_only=True)

def printTable(df: pandas.DataFrame, df_nowrite: pandas.DataFrame):
    data = [
        {
            "mode": "write",
            "DOM": df[df["TAG"] == "DOM"].iloc[0]["DURATION"],
            "SAX": df[df["TAG"] == "SAX"].iloc[0]["DURATION"],
            "Stream": df[df["TAG"] == "STREAM"].iloc[0]["DURATION"],
            "Fullread": df[df["TAG"] == "FULLREAD"].iloc[0]["DURATION"]
        },
        {
            "mode": "nowrite",
            "DOM": df_nowrite[df_nowrite["TAG"] == "DOM"].iloc[0]["DURATION"],
            "SAX": df_nowrite[df_nowrite["TAG"] == "SAX"].iloc[0]["DURATION"],
            "Stream": df_nowrite[df_nowrite["TAG"] == "STREAM"].iloc[0]["DURATION"],
            "Fullread": df_nowrite[df_nowrite["TAG"] == "FULLREAD"].iloc[0]["DURATION"]
        }
    ]

    markdown = markdown_table(data).get_markdown()
    print(markdown)


print("SMALL")
printTable(df_small, df_small_nowrite)
print("MEDIUM")
printTable(df_medium, df_medium_nowrite)
