import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("results.csv")

plt.figure()
plt.plot(df["size"], df["single_ms"], marker='o', label="Single QuickSort")
plt.plot(df["size"], df["mt_thread_ms"], marker='o', label="MT std::thread")
plt.plot(df["size"], df["openmp_ms"], marker='o', label="OpenMP")
plt.plot(df["size"], df["stl_sort_ms"], marker='o', label="STL sort")

plt.xlabel("Input Size")
plt.ylabel("Time (ms)")
plt.title("Sorting Performance Comparison")
plt.legend()
plt.grid()


plt.savefig("images/sorting_performance.png", dpi=300, bbox_inches="tight")

plt.show()
