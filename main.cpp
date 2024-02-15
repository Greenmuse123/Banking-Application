#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

struct Account {
    std::string username;
    std::string password;
    double balance;

    Account(const std::string& u, const std::string& p, double b) : username(u), password(p), balance(b) {}
};

std::vector<Account> loadAccounts(const std::string& filename) {
    std::vector<Account> accounts;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string username, password;
        double balance;
        if (iss >> username >> password >> balance) {
            accounts.emplace_back(username, password, balance);
        }
    }
    return accounts;
}

void saveAccounts(const std::vector<Account>& accounts, const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& account : accounts) {
        file << account.username << " " << account.password << " " << account.balance << std::endl;
    }
}

void drawLine(char symbol, int count) {
    for (int i = 0; i < count; i++) {
        std::cout << symbol;
    }
    std::cout << std::endl;
}

void displayMenu() {
    drawLine('-', 50);
    std::cout << "||\t\tBanking Application\t\t||" << std::endl;
    drawLine('-', 50);
    std::cout << "1. Login" << std::endl;
    std::cout << "2. Display Account Information" << std::endl;
    std::cout << "3. Deposit" << std::endl;
    std::cout << "4. Withdraw" << std::endl;
    std::cout << "5. Exit" << std::endl;
    drawLine('-', 50);
    std::cout << "Select an option: ";
}

Account* login(std::vector<Account>& accounts) {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    for (auto& account : accounts) {
        if (account.username == username && account.password == password) {
            std::cout << "Login successful!\n";
            return &account;
        }
    }
    std::cout << "Login failed. Please try again.\n";
    return nullptr;
}

int main() {
    std::vector<Account> accounts = loadAccounts("accounts.txt");
    Account* currentAccount = nullptr;
    int option;

    do {
        displayMenu();
        std::cin >> option;

        switch (option) {
            case 1:
                currentAccount = login(accounts);
                break;
            case 2:
                if (currentAccount) {
                    std::cout << "Account Information:\nUsername: " << currentAccount->username
                              << "\nBalance: $" << currentAccount->balance << std::endl;
                } else {
                    std::cout << "Please login first.\n";
                }
                break;
            case 3:
                if (currentAccount) {
                    double amount;
                    std::cout << "Enter deposit amount: ";
                    std::cin >> amount;
                    currentAccount->balance += amount;
                    std::cout << "New balance: $" << currentAccount->balance << std::endl;
                } else {
                    std::cout << "Please login first.\n";
                }
                break;
            case 4:
                if (currentAccount) {
                    double amount;
                    std::cout << "Enter withdrawal amount: ";
                    std::cin >> amount;
                    if (amount <= currentAccount->balance) {
                        currentAccount->balance -= amount;
                        std::cout << "New balance: $" << currentAccount->balance << std::endl;
                    } else {
                        std::cout << "Insufficient funds.\n";
                    }
                } else {
                    std::cout << "Please login first.\n";
                }
                break;
            case 5:
                std::cout << "Exiting application.\n";
                break;
            default:
                std::cout << "Invalid option, please try again.\n";
        }
    } while (option != 5);

    saveAccounts(accounts, "accounts.txt");
    return 0;
}
