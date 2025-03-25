#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

using namespace std;

// TODO: Define custom exception classes here
class NegativeDepositException : public runtime_error {
    public:
        NegativeDepositException() : runtime_error("Cannot deposit a negative amount.") {}
    };
// - OverdrawException (for withdrawing more than the balance)
    class OverdrawException : public runtime_error{
        public:
            OverdrawException() : runtime_error("Cannot withdraw more than the balance,") {}
    };
// - InvalidAccountOperationException (for transactions on a closed account)
    class InvalidAccountOperationException : public runtime_error{
        public:
            InvalidAccountOperationException() : runtime_error("Cannot make transactions on a closed account") {}
    };

class BankAccount {
private:
    std::string accountNumber;
    double balance;
    bool isActive;

public:
    // Constructor to initialize account number, balance, and active status
    BankAccount(std::string accNum, double initialBalance) : accountNumber(accNum), balance(initialBalance), isActive(true) {}

    // Deposit method
    void deposit(double amount) {
        // TODO: Implement exception handling for negative deposits
        if (!isActive) {
            throw InvalidAccountOperationException();
        } if (amount < 0) {
            throw NegativeDepositException();
        }
        balance += amount;
    }

    // Withdraw method
    void withdraw(double amount) {
        // TODO: Implement exception handling for overdrawing and closed accounts
        if (!isActive) {
            throw InvalidAccountOperationException();
        } if (amount > balance) {
            throw OverdrawException();
        }
        balance -= amount;
    }

    // Method to get current balance
    double getBalance() const {
        return balance;
    }

    // Method to close the account
    void closeAccount() {
        // TODO: Prevent further transactions when the account is closed
        isActive = false;
    }
};

int main() {
    try {
        // TODO: Ask the user to enter an initial balance and create a BankAccount object using smart pointers
        // Example: std::cout << "Enter initial balance: ";
        //          std::cin >> initialBalance;
        //          auto account = std::make_unique<BankAccount>("123456", initialBalance);
        double initialBalance;
        cout << "Enter intial balance: ";
        cin >> initialBalance;
        auto account = make_unique<BankAccount>("123456", initialBalance); // Example initialization

        std::cout << "\nBank Account Created: #" << "123456" << std::endl;

        // TODO: Allow the user to enter deposit amounts and call deposit() method
        double depositAmount;
        cout << "Enter deposit amount: ";
        cin >> depositAmount;
        cout << "\nDepositing $" << depositAmount << "..." << endl;
        account->deposit(depositAmount);

        // TODO: Allow the user to enter withdrawal amounts and call withdraw() method
        double withdrawAmount;
        cout << "Enter withdrawal amount: ";
        cin >> withdrawAmount;
        cout << "Withdrawing $" << withdrawAmount << "..." << std::endl;
        account->withdraw(withdrawAmount);

        std::cout << "Current Balance: $" << account->getBalance() << std::endl;

        // TODO: Test edge cases - try withdrawing more than available balance
        std::cout << "Attempting to withdraw $20000..." << std::endl;
        account->withdraw(20000); // This should trigger an exception once implemented

    } 
    catch (const std::exception& e) {
        // TODO: Catch and handle exceptions properly
        std::cerr << "Error: " << e.what() << std::endl;
    }

    try {
        auto account = make_unique<BankAccount>("654321", 500.0);

        cout << "Attempting to deposit $-50..." << endl;
        account->deposit(-50);
    }   catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    try {
        auto account = make_unique<BankAccount>("615243", 500.0);
        account->closeAccount();
        cout << "Closing account... \nAttempting to deposit $50 into account...\n";
        account->deposit(50);
    }   catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}