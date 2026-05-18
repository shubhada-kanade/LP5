#include <iostream>
#include <vector>
#include <omp.h>
#include <iomanip>

using namespace std;

void merge(vector<int>& arr, int l, int m, int r) {

    vector<int> left(arr.begin() + l, arr.begin() + m + 1);
    vector<int> right(arr.begin() + m + 1, arr.begin() + r + 1);

    int i = 0, j = 0, k = l;

    while (i < left.size() && j < right.size()) {

        if (left[i] <= right[j]) {

            arr[k++] = left[i++];
        }
        else {

            arr[k++] = right[j++];
        }
    }

    while (i < left.size()) {

        arr[k++] = left[i++];
    }

    while (j < right.size()) {

        arr[k++] = right[j++];
    }
}

void mergeSortSequential(vector<int>& arr, int l, int r) {

    if (l < r) {

        int m = (l + r) / 2;

        mergeSortSequential(arr, l, m);
        mergeSortSequential(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

void mergeSortParallel(vector<int>& arr, int l, int r, int depth) {

    if (l < r) {

        int m = (l + r) / 2;

        if (depth <= 0) {

            mergeSortSequential(arr, l, m);
            mergeSortSequential(arr, m + 1, r);
        }
        else {

            #pragma omp parallel sections
            {
                #pragma omp section
                mergeSortParallel(arr, l, m, depth - 1);

                #pragma omp section
                mergeSortParallel(arr, m + 1, r, depth - 1);
            }
        }

        merge(arr, l, m, r);
    }
}

void printArray(vector<int>& arr) {

    for (int x : arr) {

        cout << x << " ";
    }

    cout << endl;
}


int main() {

    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n), temp;

    cout << "Enter elements:\n";

    for (int i = 0; i < n; i++) {

        cin >> arr[i];
    }

    double start, end;

    // Sequential Merge Sort
    temp = arr;

    start = omp_get_wtime();

    mergeSortSequential(temp, 0, n - 1);

    end = omp_get_wtime();

    cout << "\nSequential Merge Sort:\n";

    printArray(temp);

    cout << fixed << setprecision(8);
    cout << "Time: " << (end - start) << " sec\n";

    // Parallel Merge Sort
    temp = arr;

    start = omp_get_wtime();

    mergeSortParallel(temp, 0, n - 1, 4);

    end = omp_get_wtime();

    cout << "\nParallel Merge Sort:\n";

    printArray(temp);
    
    cout << fixed << setprecision(8);
    cout << "Time: " << (end - start) << " sec\n";

    return 0;
}
