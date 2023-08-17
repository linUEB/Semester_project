#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Structure to represent a user account
struct User {
    string username;
    string password;
    double balance;
    vector<string> transactionHistory;
};

// Function to register a new user
void registerUser(vector<User>& users) {
    User newUser;
    cout << "Enter username: ";
    cin >> newUser.username;
    cout << "Enter password: ";
    cin >> newUser.password;
    newUser.balance = 0.0;
    users.push_back(newUser);
    cout << "Registration successful!" << endl;
}

// Function to authenticate user login
bool authenticateUser(const vector<User>& users, string username, string password) {
    for (const User& user : users) {
        if (user.username == username && user.password == password) {
            return true;
        }
    }
    return false;
}

// Function to perform a money transfer
void transferMoney(vector<User>& users, string sender, string recipient, double amount) {
    User* senderUser = nullptr;
    User* recipientUser = nullptr;

    // Find sender and recipient users
    for (User& user : users) {
        if (user.username == sender) {
            senderUser = &user;
        }
        if (user.username == recipient) {
            recipientUser = &user;
        }
    }

    // Perform the transfer if both users exist
    if (senderUser && recipientUser) {
        if (senderUser->balance >= amount) {
            senderUser->balance -= amount;
            recipientUser->balance += amount;
            senderUser->transactionHistory.push_back("Sent $" + to_string(amount) + " to " + recipient);
            recipientUser->transactionHistory.push_back("Received $" + to_string(amount) + " from " + sender);
            cout << "Transfer successful!" << endl;
        } else {
            cout << "Insufficient balance for transfer." << endl;
        }
    } else {
        cout << "Invalid sender or recipient." << endl;
    }
}

// Function to display transaction history for a user
void viewTransactionHistory(const vector<User>& users, string username) {
    for (const User& user : users) {
        if (user.username == username) {
            cout << "Transaction History for " << user.username << ":" << endl;
            for (const string& transaction : user.transactionHistory) {
                cout << "- " << transaction << endl;
            }
            return;
        }
    }
    cout << "User not found." << endl;
}

int main() {
    vector<User> users;

    while (true) {
        cout << "Welcome to Vodafone Cash Clone!" << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Choose an option: ";
        int option;
        cin >> option;

        if (option == 1) {
            registerUser(users);
        } else if (option == 2) {
            string username, password;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            if (authenticateUser(users, username, password)) {
                while (true) {
                    cout << "Welcome, " << username << "!" << endl;
                    cout << "1. Transfer Money" << endl;
                    cout << "2. View Transaction History" << endl;
                    cout << "3. Logout" << endl;
                    cout << "Choose an option: ";
                    cin >> option;

                    if (option == 1) {
                        string recipient;
                        double amount;
                        cout << "Enter recipient username: ";
                        cin >> recipient;
                        cout << "Enter amount to transfer: ";
                        cin >> amount;
                        transferMoney(users, username, recipient, amount);
                    } else if (option == 2) {
                        viewTransactionHistory(users, username);
                    } else if (option == 3) {
                        break;
                    } else {
                        cout << "Invalid option. Please try again." << endl;
                    }
                }
            } else {
                cout << "Invalid username or password." << endl;
            }
        } else if (option == 3) {
            break;
        } else {
            cout << "Invalid option. Please try again." << endl;
        }
    }

    return 0;
}