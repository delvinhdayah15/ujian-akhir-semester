#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

// Fungsi untuk mendapatkan digit tertentu
int getDigit(int number, int digitPlace) {
    return (number / digitPlace) % 10;
}

// Counting Sort untuk Radix Sort
void countingSort(vector<int>& arr, int digitPlace) {
    int n = arr.size();
    vector<int> output(n);
    int count[10] = {0};

    // Hitung frekuensi digit
    for (int num : arr) {
        int digit = getDigit(num, digitPlace);
        count[digit]++;
    }

    // Akumulasi jumlah
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // Bangun array terurut berdasarkan digit
    for (int i = n - 1; i >= 0; i--) {
        int digit = getDigit(arr[i], digitPlace);
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    // Salin hasil ke array asli
    arr = output;
}

// Radix Sort
void radixSort(vector<int>& arr) {
    int maxVal = *max_element(arr.begin(), arr.end());
    for (int digitPlace = 1; maxVal / digitPlace > 0; digitPlace *= 10) {
        countingSort(arr, digitPlace);
    }
}

// Quick Sort
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        int pi = i + 1;

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Merge Sort
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1, n2 = right - mid;
    vector<int> L(arr.begin() + left, arr.begin() + mid + 1);
    vector<int> R(arr.begin() + mid + 1, arr.begin() + right + 1);

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main() {
    vector<int> arr = {170, 45, 75, 90, 802, 24, 2, 66};
    vector<int> radixArr = arr, quickArr = arr, mergeArr = arr;

    cout << "Array asli: ";
    for (int num : arr) cout << num << " ";
    cout << endl;

    // Radix Sort
    radixSort(radixArr);
    cout << "Setelah Radix Sort: ";
    for (int num : radixArr) cout << num << " ";
    cout << endl;

    // Quick Sort
    quickSort(quickArr, 0, quickArr.size() - 1);
    cout << "Setelah Quick Sort: ";
    for (int num : quickArr) cout << num << " ";
    cout << endl;

    // Merge Sort
    mergeSort(mergeArr, 0, mergeArr.size() - 1);
    cout << "Setelah Merge Sort: ";
    for (int num : mergeArr) cout << num << " ";
    cout << endl;

    return 0;
}

