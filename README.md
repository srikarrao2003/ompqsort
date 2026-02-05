# OMPQ Sort

🚀 Parallel QuickSort Benchmark Suite
📌 Overview

This project benchmarks and compares the performance of multiple QuickSort implementations on large randomly generated datasets. It evaluates:

✅ Single-thread QuickSort

✅ Multi-thread QuickSort using std::thread

✅ Parallel QuickSort using OpenMP tasks

✅ (Optional) STL std::sort baseline

The benchmark measures execution time across input sizes ranging from 10⁴ to 10⁷ elements and exports results to CSV for visualization.


📊 Benchmark Range

Input sizes tested:

10K → 10M elements


🔧 Requirements
Compiler
g++ (>= 9 recommended)

Python
Python 3.8+

Python Packages
pip install pandas matplotlib

🧪 Build & Run
Step 1 — Run Benchmark
python benchmark.py

📊 Example Visualization

![Performance](images/sorting_performance.png)

Graph shows:

Execution time vs input size

Parallel scaling behavior

Overhead impact at small sizes

🧬 Performance Insights
Why Single Thread Can Be Faster

Thread creation overhead

Memory bandwidth contention

Cache locality advantages

When Parallel Helps

Very large datasets

High compute-to-overhead ratio

Proper threshold tuning

🔬 Key Tunable Parameters
Threshold

Controls minimum partition size for parallel execution.

Typical good values:

10K – 100K

Max Thread Depth

Limits exponential thread explosion.

Computed from:

log2(hardware_threads)

🚀 Optimization Ideas (Future Work)

Thread pool instead of recursive spawning

NUMA-aware partitioning

SIMD partition kernels

Parallel MergeSort comparison

GPU sorting (CUDA / Thrust)

Multi-run statistical averaging

CPU affinity pinning

📚 Concepts Demonstrated

Parallel recursion design

Task granularity tuning

Memory-bound workload analysis

CPU scaling limits

OpenMP task scheduling behavior

🧑‍💻 Author Notes

This project is useful for:

Systems performance learning

Parallel algorithm experimentation

HPC benchmarking practice

CPU architecture behavior study

📜 License

MIT License (or choose your preferred license)

🤝 Contributions

Pull requests and performance improvements are welcome.
