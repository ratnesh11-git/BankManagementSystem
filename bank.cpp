#include <iostream>
#include <fstream>
using namespace std;

class Account {
    int accNo;
    char name[50];
    float balance;

public:
    void createAccount() {
        cout << "Enter Account Number: ";
        cin >> accNo;
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Initial Balance: ";
        cin >> balance;
    }

    void displayAccount() {
        cout << "Acc No: " << accNo << " Name: " << name << " Balance: " << balance << endl;
    }

    int getAccNo() {
        return accNo;
    }

    void deposit() {
        float amt;
        cout << "Enter amount to deposit: ";
        cin >> amt;
        balance += amt;
    }

    void withdraw() {
        float amt;
        cout << "Enter amount to withdraw: ";
        cin >> amt;
        if (amt <= balance)
            balance -= amt;
        else
            cout << "Insufficient balance\n";
    }
};

// Add Account
void addAccount() {
    Account a;
    ofstream file("bank.dat", ios::binary | ios::app);

    a.createAccount();
    file.write((char*)&a, sizeof(a));

    file.close();
    cout << "Account Created!\n";
}

// Display Accounts
void displayAccounts() {
    Account a;
    ifstream file("bank.dat", ios::binary);

    while (file.read((char*)&a, sizeof(a))) {
        a.displayAccount();
    }

    file.close();
}

// Deposit
void depositMoney() {
    Account a;
    fstream file("bank.dat", ios::binary | ios::in | ios::out);
    int acc;

    cout << "Enter Account Number: ";
    cin >> acc;

    while (file.read((char*)&a, sizeof(a))) {
        if (a.getAccNo() == acc) {
            a.deposit();
            file.seekp(-sizeof(a), ios::cur);
            file.write((char*)&a, sizeof(a));
            cout << "Deposit Successful\n";
            break;
        }
    }

    file.close();
}

// Withdraw
void withdrawMoney() {
    Account a;
    fstream file("bank.dat", ios::binary | ios::in | ios::out);
    int acc;

    cout << "Enter Account Number: ";
    cin >> acc;

    while (file.read((char*)&a, sizeof(a))) {
        if (a.getAccNo() == acc) {
            a.withdraw();
            file.seekp(-sizeof(a), ios::cur);
            file.write((char*)&a, sizeof(a));
            cout << "Withdrawal Successful\n";
            break;
        }
    }

    file.close();
}

int main() {
    int choice;

    do {
        cout << "\n1. Create Account\n2. Display Accounts\n3. Deposit\n4. Withdraw\n5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addAccount(); break;
            case 2: displayAccounts(); break;
            case 3: depositMoney(); break;
            case 4: withdrawMoney(); break;
        }
    } while (choice != 5);

    return 0;
}