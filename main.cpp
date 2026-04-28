#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class PasswordManager {
private:
    string fileName = "secure_vault.dat";
    char encryptionKey = 'K'; // XOR Encryption Key

    // Core XOR Encryption/Decryption Algorithm


    string encryptDecrypt(string data) {
        string output = data;
        for (int i = 0; i < data.size(); i++) {
            output[i] = data[i] ^ encryptionKey; // Bitwise XOR operation
        }
        return output;
    }

public:
    // 1. Add and Encrypt New Password


    void addPassword(string platform, string username, string password) {
        ofstream file(fileName, ios::app);
        if (file.is_open()) {
            string combinedData = platform + " | " + username + " | " + password;
            string encryptedData = encryptDecrypt(combinedData); 
            
            file << encryptedData << "\n"; 
            file.close();
            cout << "\n[+] Credentials successfully encrypted and saved to vault!\n";
        } else {
            cout << "[-] Error: Unable to open vault file!\n";
        }
    }

    // 2. Decrypt and View Passwords


    void viewPasswords() {
        ifstream file(fileName);
        string line;
        
        if (file.is_open()) {
            cout << "\n=== ENCRYPTED VAULT CONTENTS ===\n";
            while (getline(file, line)) {
                string decryptedData = encryptDecrypt(line); 
                cout << decryptedData << "\n";
            }
            cout << "================================\n";
            file.close();
        } else {
            cout << "[-] Vault is empty or file not found.\n";
        }
    }
};

int main() {
    PasswordManager vault;
    int choice;

    cout << "--- C++ SECURE PASSWORD VAULT ---\n";

    while (true) {
        cout << "\n1. Add New Password\n2. Open Vault (Decrypt)\n3. Exit\nYour choice: ";
        cin >> choice;

        if (choice == 1) {
            string platform, user, pass;
            cout << "Platform (e.g., Github): "; cin >> platform;
            cout << "Username: "; cin >> user;
            cout << "Password: "; cin >> pass;
            
            vault.addPassword(platform, user, pass);

        } else if (choice == 2) {
            vault.viewPasswords();

        } else if (choice == 3) {
            cout << "Locking vault... Goodbye!\n";
            break;
        } else {
            cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}


/*
Efe Turan * C++ Developer
*/
