#include <iomanip>
#include <iostream>
#include <string>

class SavingsAccount {
    static constexpr int MAX_TXN = 10;
    std::string accountNumber;
    double balance;
    double transactions[MAX_TXN];
    int count;
    int head;

    void recordTransaction(double amount);

public:
    SavingsAccount(const std::string& accNo, double initialBalance)
        : accountNumber(accNo), balance(initialBalance), count(0), head(0) {
        for (int i = 0; i < MAX_TXN; ++i) transactions[i] = 0.0;
    }

    double getBalance() const { return balance; }
    void deposit(double amount);
    bool withdraw(double amount);
    void miniStatement() const;
};

void SavingsAccount::recordTransaction(double amount) {
    transactions[head] = amount;
    head = (head + 1) % MAX_TXN;
    if (count < MAX_TXN) {
        ++count;
    }
}

void SavingsAccount::deposit(double amount) {
    if (amount <= 0) return;
    balance += amount;
    recordTransaction(amount);
}

bool SavingsAccount::withdraw(double amount) {
    if (amount <= 0 || amount > balance) return false;
    balance -= amount;
    recordTransaction(-amount);
    return true;
}

void SavingsAccount::miniStatement() const {
    std::cout << "Mini-Statement for Account " << accountNumber << ":\n";
    int start = (count < MAX_TXN) ? 0 : head;
    std::cout << std::fixed << std::setprecision(2);
    for (int i = 0; i < count; ++i) {
        int idx = (start + i) % MAX_TXN;
        std::cout << "  Txn " << (i + 1) << ": " << (transactions[idx] >= 0 ? "+" : "")
                  << transactions[idx] << '\n';
    }
    std::cout << "Current Balance: Rs " << balance << '\n';
}

int main() {
    SavingsAccount acc("SB-10045", 5000.0);
    for (int i = 1; i <= 12; ++i) {
        if (i % 2 == 1) acc.deposit(i * 100.0);
        else acc.withdraw(i * 50.0);
    }
    acc.miniStatement();
    return 0;
}
