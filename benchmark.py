import subprocess
import csv
import os

SIZES = [
    10_000,
    50_000,
    100_000,
    500_000,
    1_000_000,
    2_000_000,
    5_000_000,
    10_000_000,
]

GEN = "generator.py"
SORT = "./sort"
INPUT = "input.txt"
CSV_FILE = "results.csv"

THRESHOLD = "1000"


def run_cmd(cmd):
    result = subprocess.run(cmd, capture_output=True, text=True)
    return result.stdout.strip()


def main():

    # Compile sort
    print("Compiling sort.cpp...")
    subprocess.run(
        ["g++", "-O3", "-fopenmp", "-pthread", "-std=c++17", "src/sort.cpp", "-o", "sort"]
    )

    with open(CSV_FILE, "w", newline="") as f:
        writer = csv.writer(f)
        writer.writerow([
            "size",
            "single_ms",
            "mt_thread_ms",
            "openmp_ms",
            "stl_sort_ms",
        ])

        for size in SIZES:
            print(f"\nRunning size = {size}")

            # Generate input
            run_cmd(["python3", GEN, str(size), INPUT])

            # Run sort
            out = run_cmd([SORT, INPUT, THRESHOLD])

            t1, t2, t3, t4 = map(int, out.split())

            writer.writerow([size, t1, t2, t3, t4])

            print(f"Times: {t1} {t2} {t3} {t4}")


if __name__ == "__main__":
    main()
