#include <iostream>
#include <vector>
#include <algorithm> // Untuk std::copy_if
using namespace std;

// Fungsi fungsional untuk Quick Sort
vector<int> quickSort(const vector<int>& arr) {
    if (arr.size() <= 1) {
        return arr; // Basis rekursi: array kosong atau satu elemen
    }

    // Pilih pivot (ambil elemen pertama)
    int pivot = arr[0];

    // Elemen-elemen lebih kecil dari pivot
    vector<int> less;
    copy_if(arr.begin() + 1, arr.end(), back_inserter(less), [pivot](int x) { return x <= pivot; });

    // Elemen-elemen lebih besar dari pivot
    vector<int> greater;
    copy_if(arr.begin() + 1, arr.end(), back_inserter(greater), [pivot](int x) { return x > pivot; });

    // Rekursi pada kedua bagian dan gabungkan hasilnya
    vector<int> sortedLess = quickSort(less);
    vector<int> sortedGreater = quickSort(greater);

    // Gabungkan sortedLess, pivot, dan sortedGreater
    sortedLess.push_back(pivot);
    sortedLess.insert(sortedLess.end(), sortedGreater.begin(), sortedGreater.end());

    return sortedLess;
}

int main() {
    vector<int> data = {3, 6, 8, 10, 1, 2, 1};

    // Quick Sort fungsional
    vector<int> sortedData = quickSort(data);

    // Tampilkan hasil
    cout << "Data yang sudah diurutkan: ";
    for (int num : sortedData) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}

