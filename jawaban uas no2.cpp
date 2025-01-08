#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

// Fungsi untuk menemukan pasangan dengan jumlah K
vector<pair<int, int>> findPairs(const vector<int>& arr1, const vector<int>& arr2, int K) {
    unordered_map<int, int> hashMap;
    vector<pair<int, int>> result;

    // Masukkan elemen-elemen dari arr1 ke dalam hashMap
    for (int num : arr1) {
        hashMap[num]++;
    }

    // Periksa elemen-elemen di arr2
    for (int num : arr2) {
        int complement = K - num;
        if (hashMap.find(complement) != hashMap.end() && hashMap[complement] > 0) {
            result.emplace_back(complement, num);
            hashMap[complement]--; // Kurangi jumlah untuk menghindari penggunaan ulang
        }
    }

    return result;
}

int main() {
    vector<int> arr1 = {1, 2, 3, 4, 5};
    vector<int> arr2 = {6, 7, 8, 9, 10};
    int K = 10;

    // Temukan pasangan
    vector<pair<int, int>> pairs = findPairs(arr1, arr2, K);

    // Tampilkan hasil
    cout << "Pasangan dengan jumlah " << K << ":\n";
    for (const auto& p : pairs) {
        cout << "(" << p.first << ", " << p.second << ")\n";
    }

    return 0;
}

