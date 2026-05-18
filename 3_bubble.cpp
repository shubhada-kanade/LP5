#include <iostream>
#include <vector>
#include <omp.h>
#include <iomanip>

using namespace std;

void bubbleSortSequential(vector<int>& arr) {

    int n = arr.size();

    for (int i = 0; i < n - 1; i++) {

        for (int j = 0; j < n - i - 1; j++) {

            if (arr[j] > arr[j + 1]) {

                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void bubbleSortParallel(vector<int>& arr) {

    int n = arr.size();

    for (int i = 0; i < n; i++) {

        // Even Phase
        #pragma omp parallel for
        for (int j = 0; j < n - 1; j += 2) {

            if (arr[j] > arr[j + 1]) {

                swap(arr[j], arr[j + 1]);
            }
        }

        // Odd Phase
        #pragma omp parallel for
        for (int j = 1; j < n - 1; j += 2) {

            if (arr[j] > arr[j + 1]) {

                swap(arr[j], arr[j + 1]);
            }
        }
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

    // Sequential Bubble Sort
    temp = arr;

    start = omp_get_wtime();

    bubbleSortSequential(temp);

    end = omp_get_wtime();

    cout << "\nSequential Bubble Sort:\n";

    printArray(temp);
    
    cout << fixed << setprecision(8);
    cout << "Time: " << (end - start) << " sec\n";

    // Parallel Bubble Sort
    temp = arr;

    start = omp_get_wtime();

    bubbleSortParallel(temp);

    end = omp_get_wtime();

    cout << "\nParallel Bubble Sort:\n";

    printArray(temp);

    cout << fixed << setprecision(8);
	cout << "Time: " << (end - start) << " sec\n";
	
    return 0;
}
