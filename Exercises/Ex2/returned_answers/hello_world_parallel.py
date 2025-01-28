#!/usr/bin/python3
import multiprocessing as mp
import os
import subprocess

def run_hello_world(number):
    result = subprocess.run(
            ["make", "run", f"NUMBER={number}"],
            stdout=subprocess.PIPE,
            text=True,
        )

    with open(f"hello_world_{number}.txt", "w") as file:
        file.write(result.stdout)


if __name__ == "__main__":
    inputs = list(range(1, 11))
    subprocess.run(["make", "compile"])
    with mp.Pool(max(mp.cpu_count() - 1, 1)) as pool:
        pool.map(run_hello_world, inputs)
