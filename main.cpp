#include <iostream>
#include <vector>
#include <limits>
#include "User.h"
#include "Instructor.h"
#include "Student.h"

using namespace std;

void SpeakTextFromFile(const string& filePath) {
    string command = "espeak -v en+m3 -s 150 -f \"" + filePath + "\"";
    int result = system(command.c_str());
    if (result != 0) {
        cerr << "Error executing espeak command. Result code: " << result << endl;
    }
}

void displayMainMenu() {
    cout << "1. Register\n2. Login\n3. Exit" << endl;
    cout << "Select: ";
}

void displayUserTypeMenu() {
    cout << "1. Student Account\n2. Instructor Account" << endl;
    cout << "Select: ";
}

bool isUsernameTaken(const vector<User*>& users, const string& username) {
    for (const User* user : users) {
        if (user->getName() == username) {
            return true;
        }
    }
    return false;
}

int getIntegerInput() {
    int input;
    while (true) {
        cin >> input;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid integer." << endl;
        }
        else {
            // Clear the input buffer in case there are extra characters
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return input;
        }
    }
}


void handleStudentRegistration(vector<User*>& users) {
    User* currentUser = new Student();
    currentUser->get_username();

    if (isUsernameTaken(users, currentUser->getName())) {
        cout << "Username already taken. Please choose a different username." << endl;
        delete currentUser;
        return;
    }

    currentUser->get_password();
    users.push_back(currentUser);
    cout << "Student registration successful!\n";
}

void handleInstructorRegistration(vector<User*>& users) {
    User* currentUser = new Instructor();
    currentUser->get_username();

    if (isUsernameTaken(users, currentUser->getName())) {
        cout << "Username already taken. Please choose a different username." << endl;
        delete currentUser;
        return;
    }

    currentUser->get_password();
    users.push_back(currentUser);
    cout << "Instructor registration successful!\n";
}

void handleUserLogin(vector<User*>& users) {
    string inputUsername;
    cout << "Enter username: ";
    cin >> inputUsername;

    int pos = -1;
    for (int i = 0; i < users.size(); ++i) {
        if (users.at(i)->getName() == inputUsername) {
            pos = i;
            break;
        }
    }

    if (pos != -1) {
        bool success = users.at(pos)->login();
        if (success) {
            cout << "Successfully logged in" << endl;

            Student* studentUser = dynamic_cast<Student*>(users.at(pos));
            if (studentUser) {
                cout << "Student-specific actions..." << endl;

                int choice;
                cout << "Do you want to make photo to speech? (1 for yes, 2 for no): ";

                while (true) {
                    cin >> choice;

                    if (cin.fail() || (choice != 1 && choice != 2)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input.\nPlease enter 1 for yes or 2 for no: ";
                    }
                    else {
                        break; // Valid input, exit the loop
                    }
                }
                if (choice == 1) {
                    int i = studentUser->getOCR().return_i();
                    studentUser->getOCR().set_i(i, studentUser->getName());

                    char createMoreText;
                    do {
                        string imagePath;
                        cout << "Please input your image's path: ";
                        cin >> imagePath;
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Invalid input. Please enter a valid path." << endl;
                            continue; // Skip the rest of the loop and prompt again
                        }

                        studentUser->getOCR().performOCR(imagePath);
                        cout << "Do you want to create more texts? (y/n): ";
                        

                        while (true) {
                            cin >> createMoreText;

                            if (cin.fail() || (createMoreText != 'y' && createMoreText != 'Y' && createMoreText != 'n' && createMoreText != 'N')) {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << "Invalid input. Please enter 'y' or 'n': ";
                            }
                            else {
                                break; // Valid input, exit the loop
                            }
                        }
                        
                       
                        i++;
                        studentUser->getOCR().set_i(i, studentUser->getName());
                    } while (createMoreText == 'y' || createMoreText == 'Y');
                }

                // Dosyalarý dinleme iþlemi burada olmalý
                int choice2;
                cout << "Do you want to listen to created files? (1 for yes, 2 for no): ";
                while (true) {
                    cin >> choice2;

                    if (cin.fail() || (choice2 != 1 && choice2 != 2)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input.\nPlease enter 1 for yes or 2 for no: ";
                    }
                    else {
                        break; // Valid input, exit the loop
                    }
                }
                while (choice2 == 1) {
                    studentUser->listenToCreatedTexts();
                    cout << "Do you want to listen to more created files? (1 for yes, 2 for no): ";
                    while (true) {
                        cin >> choice2;

                        if (cin.fail() || (choice2 != 1 && choice2 != 2)) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Invalid input.\nPlease enter 1 for yes or 2 for no: ";
                        }
                        else {
                            break; // Valid input, exit the loop
                        }
                    }
                }
            }

            Instructor* instructorUser = dynamic_cast<Instructor*>(users.at(pos));
            if (instructorUser) {
                cout << "Instructor-specific actions..." << endl;
                int choice;
                cout << "Do you want to make photo to speech? (1 for yes, 2 for no): ";

                while (true) {
                    cin >> choice;

                    if (cin.fail() || (choice != 1 && choice != 2)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input.\nPlease enter 1 for yes or 2 for no: ";
                    }
                    else {
                        break; // Valid input, exit the loop
                    }
                }
                if (choice == 1) {
                    int i = instructorUser->getOCR().return_i();
                    instructorUser->getOCR().set_i(i, instructorUser->getName());

                    char createMoreText;
                    do {
                        string imagePath;
                        cout << "Please input your image's path: ";
                        cin >> imagePath;
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Invalid input. Please enter a valid path." << endl;
                            continue; // Skip the rest of the loop and prompt again
                        }
                        instructorUser->getOCR().performOCR(imagePath);
                        cout << "Do you want to create more texts? (y/n): ";


                        while (true) {
                            cin >> createMoreText;

                            if (cin.fail() || (createMoreText != 'y' && createMoreText != 'Y' && createMoreText != 'n' && createMoreText != 'N')) {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << "Invalid input. Please enter 'y' or 'n': ";
                            }
                            else {
                                break; // Valid input, exit the loop
                            }
                        }
                        i++;
                        instructorUser->getOCR().set_i(i, instructorUser->getName());
                    } while (createMoreText == 'y' || createMoreText == 'Y');
                }

                // Dosyalarý dinleme iþlemi burada olmalý
                int choice2;
                cout << "Do you want to listen to created files? (1 for yes, 2 for no): ";
                while (true) {
                    cin >> choice2;

                    if (cin.fail() || (choice2 != 1 && choice2 != 2)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input.\nPlease enter 1 for yes or 2 for no: ";
                    }
                    else {
                        break; // Valid input, exit the loop
                    }
                }
                while (choice2 == 1) {
                    instructorUser->listenToCreatedTexts();
                    cout << "Do you want to listen to more created files? (1 for yes, 2 for no): ";
                    while (true) {
                        cin >> choice2;

                        if (cin.fail() || (choice2 != 1 && choice2 != 2)) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Invalid input.\nPlease enter 1 for yes or 2 for no: ";
                        }
                        else {
                            break; // Valid input, exit the loop
                        }
                    }
                }
                int choice3;
                cout << "Do you want to add notes to a student's file? (1 for yes, 2 for no): ";
                while (true) {
                    cin >> choice3;

                    if (cin.fail() || (choice3 != 1 && choice3 != 2)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. Please enter 1 or 2." << endl;
                        cout << "Do you want to add notes to a student's file? (1 for yes, 2 for no): ";
                    }
                    else {
                        break; // Valid input, exit the loop
                    }
                }


                while (choice3 == 1) {
                    instructorUser->viewAllUsersTexts(users);
                    string studentFileName;
                    cout << "Enter the student's file name to add notes: ";
                    while (true) {
                        cin >> studentFileName;

                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Invalid input. Please enter a valid file name." << endl;
                            cout << "Enter the student's file name to add notes: ";
                        }
                        else {
                            break; // Valid input, exit the loop
                        }
                    }

                    instructorUser->addNotesToStudentFile(studentFileName);

                    cout << "Do you want to add notes to another student's file? (1 for yes, 2 for no): ";
                    while (true) {
                        cin >> choice3;

                        if (cin.fail() || (choice3 != 1 && choice3 != 2)) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Invalid input. Please enter 1 or 2." << endl;
                            cout << "Do you want to add notes to another student's file? (1 for yes, 2 for no): ";
                        }
                        else {
                            break; // Valid input, exit the loop
                        }
                    }

                }
            }
        }
        else {
            cout << "Unable to login" << endl;
        }
    }
    else {
        cout << "User does not exist" << endl;
    }
}

int main() {
    cout << "----------READ LENS----------" << endl;
    vector<User*> users;
    int choice;
    int userTypeChoice;
    do {
        try {
            displayMainMenu();
            choice = getIntegerInput();

            switch (choice) {
            case 1:
                displayUserTypeMenu();
                userTypeChoice = getIntegerInput();

                if (userTypeChoice == 1) {
                    handleStudentRegistration(users);
                }
                else if (userTypeChoice == 2) {
                    handleInstructorRegistration(users);
                }
                else {
                    cout << "Invalid Choice!" << endl;
                }
                break;
            case 2:
                handleUserLogin(users);
                break;
            case 3:
                cout << "Exit program" << endl;
                break;
            default:
                cout << "Invalid Choice!" << endl;
            }
        }
        catch (const invalid_argument& e) {
            cerr << "Error: " << e.what() << endl;
        }
    } while (choice != 3);

    for (User* user : users) {
        for (int i = 1; i <= user->getOCR().createdTexts.size(); ++i) {
            string fileName = user->getName() + "_temp" + to_string(i) + ".txt";
            if (remove(fileName.c_str()) != 0) {
                cerr << "Error deleting file: " << fileName << endl;
            }
            else {
                cout << "File deleted: " << fileName << endl;
            }
        }
        delete user;
    }
    return 0;
}