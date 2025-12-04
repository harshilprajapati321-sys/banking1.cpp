#include <iostream>
using namespace std;
class BankAccount {
protected:
    string accountNumber;
    string holderName;

private:
    double balance;   

public:
    BankAccount(string acc, string name, double bal) {
        accountNumber = acc;
        holderName = name;
        balance = bal;
    }
    void deposit(double amt) {
        balance += amt;
    }

    virtual void withdraw(double amt) {
        if (amt <= balance) {
            balance -= amt;
            cout << "Withdraw Successful!\n";
        } else {
            cout << "Not Enough Balance!\n";
        }
    }

    double getBalance() {
        return balance;
    }

    virtual double calculateInterest() {
        return 0;
    }

    virtual void show() {
        cout << "\nAccount No: " << accountNumber;
        cout << "\nName: " << holderName;
        cout << "\nBalance: " << balance << endl;
    }
};
class SavingsAccount : public BankAccount {
    double rate;
    public:
    SavingsAccount(string a, string n, double b, double r)
        : BankAccount(a, n, b) {
        rate = r;
    }

    double calculateInterest() override {
        return getBalance() * (rate / 100);
    }

    void show() override {
        BankAccount::show();
        cout << "Type: Savings\n";
    }
};
class CheckingAccount : public BankAccount {
    double overdraft;
    public:
    CheckingAccount(string a, string n, double b, double o)
        : BankAccount(a, n, b), overdraft(o) {}

    void withdraw(double amt) override {
        if (amt <= getBalance() + overdraft)
            cout << "Withdraw Allowed (Overdraft Used)\n";
        else
            cout << "Overdraft Limit Exceeded!\n";
    }

    void show() override {
        BankAccount::show();
        cout << "Type: Checking\n";
    }
};

class FixedDepositAccount : public BankAccount {
    int months;
    public:
    FixedDepositAccount(string a, string n, double b, int m)
        : BankAccount(a, n, b), months(m) {}

    double calculateInterest() override {
        return (getBalance() * 7.0 * months) / (100 * 12);
    }

    void show() override {
        BankAccount::show();
        cout << "Type: Fixed Deposit\n";
    }
};

int main() {
    BankAccount* acc = nullptr;
    int ch;

    while (true) {
        cout << "\n1. Savings Account";
        cout << "\n2. Checking Account";
        cout << "\n3. Fixed Deposit Account";
        cout << "\n4. Deposit";
        cout << "\n5. Withdraw";
        cout << "\n6. Show Info";
        cout << "\n7. Interest";
        cout << "\n8. Exit\n";

        cin >> ch;

        if (ch == 8) break;

        switch (ch) {
        case 1:
            acc = new SavingsAccount("S01", "Harshil", 5000, 5);
            cout << "Savings Account Created!\n";
            break;
        case 2:
            acc = new CheckingAccount("P01", "Harshil", 3000, 2000);
            cout << "Checking Account Created!\n";
            break;
        case 3:
            acc = new FixedDepositAccount("N01", "Harshil", 10000, 12);
            cout << "FD Account Created!\n";
            break;
        case 4:
            if (acc) {
                double d; cout << "Deposit: "; cin >> d;
                acc->deposit(d);
            }
            break;
        case 5:
            if (acc) {
                double w; cout << "Withdraw: "; cin >> w;
                acc->withdraw(w);
            }
            break;
        case 6:
            if (acc) acc->show();
            break;
        case 7:
            if (acc) cout << "Interest: " << acc->calculateInterest() << endl;
            break;
        default:
            cout << "Invalid!\n";
        }
    }

    return 0;
}
