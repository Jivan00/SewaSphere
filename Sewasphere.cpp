#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

// ─── Data Structures ────────────────────────────────────────────────────────

struct UserRegister {
    string username;
    string password;
};

struct Complaint {
    string name;
    string issueType;
    string location;
    string description;
};

struct HelpRequest {
    string name;
    string helpType;
    string location;
    string quantity;
    string description;
};

// ─── Utility ─────────────────────────────────────────────────────────────────

void clearInputBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ─── Function Declarations ────────────────────────────────────────────────────

void userRegistration();
bool userLogin();
void complaintSubmission();
void helpRequestFunc();
void viewComplaints();
void viewRequests();

// ─── Implementations ──────────────────────────────────────────────────────────

void userRegistration() {
    UserRegister newUser;

    cout << "Enter your username: ";
    cin >> newUser.username;
    cout << "Enter your password: ";
    cin >> newUser.password;

    if (newUser.username.empty() || newUser.password.empty()) {
        cout << "Username and password must not be empty. Please try again.\n";
        userRegistration();
        return;
    }

    ofstream userFile("user.txt", ios::app);
    if (!userFile) {
        cout << "Error opening file!\n";
        return;
    }

    userFile << newUser.username << " " << newUser.password << "\n";
    cout << "Registration successful! You can now log in.\n";
}

bool userLogin() {
    string inputUsername, inputPassword;

    cout << "Enter your username: ";
    cin >> inputUsername;
    cout << "Enter your password: ";
    cin >> inputPassword;

    ifstream userFile("user.txt");
    if (!userFile) {
        cout << "No users registered yet. Please register first.\n";
        return false;
    }

    string storedUsername, storedPassword;
    while (userFile >> storedUsername >> storedPassword) {
        if (storedUsername == inputUsername && storedPassword == inputPassword) {
            cout << "Welcome to SewaSphere!\n";
            return true;
        }
    }

    cout << "The data you entered doesn't match our records. Please try again.\n";
    return false;
}

void complaintSubmission() {
    Complaint c;

    clearInputBuffer(); // flush newline left by cin >> choice

    cout << "Enter your name: ";
    getline(cin, c.name);

    cout << "Enter the type of issue: ";
    getline(cin, c.issueType);

    cout << "Enter the location for your complaint: ";
    getline(cin, c.location);

    cout << "Describe your complaint: ";
    getline(cin, c.description);

    ofstream complaintFile("complain.txt", ios::app);
    if (!complaintFile) {
        cout << "Error opening complaint file!\n";
        return;
    }

    complaintFile << "Name: "        << c.name        << "\n"
                  << "Issue: "       << c.issueType   << "\n"
                  << "Location: "    << c.location    << "\n"
                  << "Description: " << c.description << "\n"
                  << "---\n";

    cout << "Your complaint has been submitted successfully.\n";
}

void helpRequestFunc() {
    HelpRequest h;

    clearInputBuffer(); // flush newline left by cin >> choice

    cout << "Enter your name: ";
    getline(cin, h.name);

    cout << "Enter the type of help needed: ";
    getline(cin, h.helpType);

    cout << "Enter the location for help: ";
    getline(cin, h.location);

    cout << "Enter the quantity of products required: ";
    getline(cin, h.quantity);

    cout << "Describe your help request: ";
    getline(cin, h.description);

    ofstream helpFile("request.txt", ios::app);
    if (!helpFile) {
        cout << "Error opening request file!\n";
        return;
    }

    helpFile << "Name: "        << h.name        << "\n"
             << "Help Type: "  << h.helpType    << "\n"
             << "Location: "   << h.location    << "\n"
             << "Quantity: "   << h.quantity    << "\n"
             << "Description: " << h.description << "\n"
             << "---\n";

    cout << "Your help request has been submitted successfully.\n";
}

void viewComplaints() {
    ifstream complaintFile("complain.txt");
    if (!complaintFile) {
        cout << "No complaints found.\n";
        return;
    }

    cout << "\n--- Complaints ---\n";
    cout << complaintFile.rdbuf(); // stream entire file directly to stdout
}

void viewRequests() {
    ifstream requestFile("request.txt");
    if (!requestFile) {
        cout << "No help requests found.\n";
        return;
    }

    cout << "\n--- Help Requests ---\n";
    cout << requestFile.rdbuf();
}

// ─── Main ─────────────────────────────────────────────────────────────────────

int main() {
    int choice;
    bool loggedIn = false;

    while (true) {
        cout << "\n\t\t\t SewaSphere\n";
        cout << "1. Register User\n";
        cout << "2. Login User\n";
        cout << "3. Submit Complaint\n";
        cout << "4. Request Help\n";
        cout << "5. View Complaints\n";
        cout << "6. View Help Requests\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                userRegistration();
                break;
            case 2:
                loggedIn = userLogin();
                break;
            case 3:
                if (loggedIn) {
                    complaintSubmission();
                } else {
                    cout << "Please login first.\n";
                }
                break;
            case 4:
                if (loggedIn) {
                    helpRequestFunc();
                } else {
                    cout << "Please login first.\n";
                }
                break;
            case 5:
                viewComplaints();
                break;
            case 6:
                viewRequests();
                break;
            case 7:
                cout << "Thank you for using SewaSphere!\n";
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
                clearInputBuffer();
        }
    }
}
