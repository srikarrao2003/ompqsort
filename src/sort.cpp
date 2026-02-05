#include <algorithm>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <omp.h>
#include <thread>
#include <vector>

using namespace std;

int medianOfThree(vector<int> &a, int low, int high) {
    int mid = low + (high - low) / 2;

    if (a[mid] < a[low])
        swap(a[mid], a[low]);
    if (a[high] < a[low])
        swap(a[high], a[low]);
    if (a[high] < a[mid])
        swap(a[high], a[mid]);

    swap(a[mid], a[low]);
    return low;
}

int partition(vector<int> &v, int low, int high) {
    int pivot = medianOfThree(v, low, high);
    int val = v[pivot];

    int i = low, j = high;
    while (j > i) {
        while (v[j] > val)
            j--;
        while (v[i] <= val)
            i++;
        if (j > i)
            swap(v[i], v[j]);
    }
    swap(v[pivot], v[j]);
    return j;
}

void qsort_single(vector<int> &v, int low, int high) {
    if (low < high) {
        int pivot = partition(v, low, high);
        qsort_single(v, low, pivot - 1);
        qsort_single(v, pivot + 1, high);
    }
}

void mtqsort(vector<int> &v, int low, int high, int depth, int max_depth, int threshold) {

    if (low >= high)
        return;

    int size = high - low + 1;

    if (size < threshold || depth >= max_depth) {
        qsort_single(v, low, high);
        return;
    }

    int pivot = partition(v, low, high);

    thread lt(mtqsort, ref(v), low, pivot - 1, depth + 1, max_depth, threshold);
    thread rt(mtqsort, ref(v), pivot + 1, high, depth + 1, max_depth, threshold);

    lt.join();
    rt.join();
}

void ompqsort_internal(vector<int> &v, int low, int high, int threshold) {

    if (low >= high)
        return;

    int size = high - low + 1;

    if (size < threshold) {
        qsort_single(v, low, high);
        return;
    }

    int pivot = partition(v, low, high);

#pragma omp task shared(v)
    ompqsort_internal(v, low, pivot - 1, threshold);

#pragma omp task shared(v)
    ompqsort_internal(v, pivot + 1, high, threshold);
}

void ompqsort(vector<int> &v, int threshold) {
#pragma omp parallel
    {
#pragma omp single nowait
        ompqsort_internal(v, 0, v.size() - 1, threshold);
    }
}

vector<int> read_input(const string &filename) {
    ifstream fin(filename);
    vector<int> data;
    int x;
    while (fin >> x)
        data.push_back(x);
    return data;
}

bool is_sorted_vec(const vector<int> &v) {
    return is_sorted(v.begin(), v.end());
}

bool equal_vec(const vector<int> &a, const vector<int> &b) {
    return a == b;
}

int main(int argc, char **argv) {

    if (argc < 2) {
        cout << "Usage: ./sort input.txt [threshold]\n";
        return 0;
    }

    string filename = argv[1];
    int threshold = (argc >= 3) ? stoi(argv[2]) : 1000;

    vector<int> original = read_input(filename);
    if (original.empty()) {
        cout << "Input empty\n";
        return 0;
    }

    vector<int> v1 = original;
    vector<int> v2 = original;
    vector<int> v3 = original;
    vector<int> v4 = original; // STL sort

    int hw_threads = thread::hardware_concurrency();
    int max_depth = log2(hw_threads == 0 ? 8 : hw_threads);

    auto t1s = chrono::high_resolution_clock::now();
    qsort_single(v1, 0, v1.size() - 1);
    auto t1e = chrono::high_resolution_clock::now();

    auto t2s = chrono::high_resolution_clock::now();
    mtqsort(v2, 0, v2.size() - 1, 0, max_depth, threshold);
    auto t2e = chrono::high_resolution_clock::now();

    auto t3s = chrono::high_resolution_clock::now();
    ompqsort(v3, threshold);
    auto t3e = chrono::high_resolution_clock::now();

    auto t4s = chrono::high_resolution_clock::now();
    sort(v4.begin(), v4.end());
    auto t4e = chrono::high_resolution_clock::now();

    if (!(is_sorted_vec(v1) && equal_vec(v1, v2) && equal_vec(v1, v3) &&
          equal_vec(v1, v4))) {

        cout << "ERROR\n";
        return 0;
    }

    auto d1 = chrono::duration_cast<chrono::milliseconds>(t1e - t1s).count();
    auto d2 = chrono::duration_cast<chrono::milliseconds>(t2e - t2s).count();
    auto d3 = chrono::duration_cast<chrono::milliseconds>(t3e - t3s).count();
    auto d4 = chrono::duration_cast<chrono::milliseconds>(t4e - t4s).count();

    cout << d1 << " " << d2 << " " << d3 << " " << d4 << "\n";
}
