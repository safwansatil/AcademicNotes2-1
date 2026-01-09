#include <bits/stdc++.h>

using namespace std;

string caesarWithRepeatingKey(const string& message, const vector<int>& shifts) {
    queue<int> keyQueue;
    for (int shift : shifts) {
        keyQueue.push(shift);
    }
    
    string result = "";
    
    for (char ch : message) {
        if (isalpha(ch)) {
            int shift = keyQueue.front();
            keyQueue.pop();
            keyQueue.push(shift); // cycle the key
            
            char base = isupper(ch) ? 'A' : 'a';
            result += static_cast<char>((ch - base + shift) % 26 + base);
        } else {
            result += ch; // non-letter unchanged
        }
    }
    return result;
}

int main() {
    string text = "HELLO WORLD";
    vector<int> key = {3, 5, 7, 1};
    
    string encrypted = caesarWithRepeatingKey(text, key);
    cout << "Encrypted: " << encrypted << endl;
    
    // To decrypt, use negative shifts (or same function with 26-shift values)
    vector<int> decryptKey;
    for (int shift : key) {
        decryptKey.push_back(26 - (shift % 26));
    }
    string decrypted = caesarWithRepeatingKey(encrypted, decryptKey);
    cout << "Decrypted: " << decrypted << endl;
    
    return 0;
}