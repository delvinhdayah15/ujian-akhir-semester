#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

// Struktur simpul untuk pohon Huffman
struct Node {
    char ch;
    int freq;
    Node *left, *right;

    Node(char ch, int freq) : ch(ch), freq(freq), left(nullptr), right(nullptr) {}
};

// Comparator untuk priority queue
struct Compare {
    bool operator()(Node* left, Node* right) {
        return left->freq > right->freq;
    }
};

// Fungsi untuk membangun pohon Huffman
Node* buildHuffmanTree(const string& text) {
    unordered_map<char, int> freqMap;

    // Hitung frekuensi karakter
    for (char ch : text) {
        freqMap[ch]++;
    }

    // Buat priority queue
    priority_queue<Node*, vector<Node*>, Compare> pq;

    // Tambahkan semua karakter ke dalam queue
    for (auto pair : freqMap) {
        pq.push(new Node(pair.first, pair.second));
    }

    // Gabungkan simpul hingga hanya tersisa satu
    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* merged = new Node('\0', left->freq + right->freq);
        merged->left = left;
        merged->right = right;

        pq.push(merged);
    }

    return pq.top();
}

// Membuat tabel kode Huffman
void buildHuffmanCodes(Node* root, const string& str, unordered_map<char, string>& huffmanCodes) {
    if (!root) return;

    if (root->ch != '\0') {
        huffmanCodes[root->ch] = str;
    }

    buildHuffmanCodes(root->left, str + "0", huffmanCodes);
    buildHuffmanCodes(root->right, str + "1", huffmanCodes);
}

// Fungsi untuk encoding
string encode(const string& text, unordered_map<char, string>& huffmanCodes) {
    string encodedStr;
    for (char ch : text) {
        encodedStr += huffmanCodes[ch];
    }
    return encodedStr;
}

// Fungsi untuk decoding
string decode(Node* root, const string& encodedStr) {
    string decodedStr;
    Node* currentNode = root;

    for (char bit : encodedStr) {
        if (bit == '0') {
            currentNode = currentNode->left;
        } else {
            currentNode = currentNode->right;
        }

        if (!currentNode->left && !currentNode->right) {
            decodedStr += currentNode->ch;
            currentNode = root;
        }
    }

    return decodedStr;
}

int main() {
    string text;
    cout << "Masukkan string untuk dikompresi: ";
    cin >> text;

    // Bangun pohon Huffman
    Node* root = buildHuffmanTree(text);

    // Bangun tabel kode Huffman
    unordered_map<char, string> huffmanCodes;
    buildHuffmanCodes(root, "", huffmanCodes);

    cout << "Kode Huffman untuk setiap karakter:\n";
    for (auto pair : huffmanCodes) {
        cout << pair.first << ": " << pair.second << endl;
    }

    // Encoding
    string encodedStr = encode(text, huffmanCodes);
    cout << "\nString terkompresi: " << encodedStr << endl;

    // Decoding
    string decodedStr = decode(root, encodedStr);
    cout << "String setelah didekompresi: " << decodedStr << endl;

    return 0;
}

