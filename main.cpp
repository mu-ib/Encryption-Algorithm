/*
 * Muhammad Ibrahim
 * 12 January 2022
 * Encryption Algorithm
 * Vigenère cipher algorithm
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

char chars[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz 1234567890`~!@#$%^&*()-_=+[{]}\\|;:'\",<.>/?"};
int size = sizeof(chars);
string keyword = "PsEuDoPsEuDoHyPoPaRaThYrOiDiSm";

// returns the index cuz idk if c++ already has something like this
int indexOf(char c) {
    int i;
    for (i = 0; i < size; i++) {
        if (chars[i] == c)
            break;
    }

    return i;
}

// method to get the indexes of the keystream
vector <int> getKeyStreamIndexes(string text){
    string keyStream;
    // first make the keystream
    if (keyword.length() >= text.length()) {
        for (int i = 0; i < text.length(); i++) {
            keyStream += keyword[i];
        }
    }
    else if (keyword.length() < text.length()) {
        int r = text.length() % keyword.length();
        int whole = text.length() / keyword.length();

        for (int i = 0; i < whole; i++) {
            keyStream += keyword;
        }
        for (int i = 0; i < r; i++) {
            keyStream += keyword[i];
        }
    }

    //get the indexes of the keystream
    vector <int> keyStreamIndexes;
    for (char i : keyStream) {
        keyStreamIndexes.push_back(indexOf(i));
    }

    return keyStreamIndexes;
}

// ENCRYPTION
string encrypt(string plaintext) {
    vector <int> keyStreamIndexes = getKeyStreamIndexes(plaintext);

    //get the indexes of the plaintext
    vector <int> plainTextIndexes;
    for (char i : plaintext) {
        plainTextIndexes.push_back(indexOf(i));
    }

    //find the indexes for the cipher text
    vector <int> cipherTextIndexes;
    for (int i = 0; i < plaintext.length(); i++) {
        int cipherTextIndex = plainTextIndexes.at(i) + keyStreamIndexes.at(i);

        if (cipherTextIndex >= size) {
            cipherTextIndex %= size;
        }
        cipherTextIndexes.push_back(cipherTextIndex);
    }

    //finally, assembling the ciphertext
    string ciphertext;
    for (int i = 0; i < plaintext.length(); i++) {
        ciphertext += chars[cipherTextIndexes.at(i)];
    }

    return ciphertext;
}

// DECRYPTION
string decrypt(string ciphertext) {
    vector <int> keyStreamIndexes = getKeyStreamIndexes(ciphertext);

    //get the indexes of the ciphertext
    vector <int> cipherTextIndexes;
    for (char i : ciphertext) {
        cipherTextIndexes.push_back(indexOf(i));
    }

    //find the indexes of the plaintext
    vector <int> plainTextIndexes;

    for (int i = 0; i < ciphertext.length(); i++) {
        int plainTextIndex = cipherTextIndexes.at(i) - keyStreamIndexes.at(i);
        if (plainTextIndex < 0) {
            plainTextIndex += size;
        }

        plainTextIndexes.push_back(plainTextIndex);
    }

    //assembling the plaintext
    string plaintext;
    for (int i = 0; i < ciphertext.length(); i++) {
        plaintext += chars[plainTextIndexes.at(i)];
    }

    return plaintext;
}

bool isCont(){
    string cont;
    cin >> cont;
    string temp;
    getline(cin, temp);
    if(cont != "y")
        return false;
    else
        return true;
}

int main() {
    //get the plaintexts from the user and store them in a vector
    vector<string> messages;

    bool cont = true;
    while(cont){
        string plaintext;
        cout << "Enter the word/sentence to encrypt:" << endl;
        getline(cin, plaintext);

        messages.push_back(plaintext);

        cout << endl << "Would you like to encrypt another message? (y/n)\t";
        cont = isCont();
        cout << endl;
    }

    vector <string> encryptedMessages;
    encryptedMessages.reserve(messages.size());
    for(auto & message : messages){
        encryptedMessages.push_back(encrypt(message));
    }

    cont = true;
    //ask the user which message to decode
    while(cont){
        cout << endl << "Which message would you like to decrypt?" << endl;
        int idx;
        cin >> idx;
        idx--;

        string decrypted = decrypt(encryptedMessages.at(idx));
        cout << endl << "Original Text:\t" << messages.at(idx) << endl;
        cout << "Decrypted Text:\t" << decrypted << endl;

        cout << endl << "Would you like to decrypt another message? (y/n)\t";
        cont = isCont();
    }
}