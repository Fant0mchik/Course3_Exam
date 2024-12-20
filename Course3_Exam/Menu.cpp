#include "Header.h"

void printWelcomeMenu() {
    cout << "#=======================================#" << endl;
    cout << "|         Welcome in the system         |" << endl;
    cout << "#=======================================#" << endl;
    cout << "|  1. Log in                            |" << endl;
    cout << "|  2. Create account                    |" << endl;
    cout << "|  3. Exit                              |" << endl;
    cout << "#=======================================#" << endl;
    cout << "Your choice: ";
}

vector<account>::iterator login(vector<account>& Accounts) {
    string username, password;
    cout << "#=======================================#" << endl;
    cout << "|                Log in                 |" << endl;
    cout << "#=======================================#" << endl;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    for (auto it = Accounts.begin(); it != Accounts.end(); ++it) {
        if (it->compare(username, password)) {
            return it;
        }
    }
    throw exception("Incorrect username or password.");
}

vector<account>::iterator registerAccount(vector<account>& Accounts) {
    string username, password, phone, adress, full_name;
    cout << "#=======================================#" << endl;
    cout << "|          Account registration         |" << endl;
    cout << "#=======================================#" << endl;

    cout << "Create new username: ";
    cin >> username;

    cout << "Create new password: ";
    cin >> password;

    cout << "Enter your phone number: ";
    cin >> phone;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter your full name: ";
    getline(cin, full_name);

    cout << "Enter your adress: ";
    getline(cin, adress);

    Accounts.emplace_back(username, password, phone, full_name, adress);
    return Accounts.end() - 1;
}

void regularMenu() {
    cout << "#=======================================#" << endl;
    cout << "|        Welcome in test system         |" << endl;
    cout << "#=======================================#" << endl;
    cout << "|  1. Show results for previous tests   |" << endl;
    cout << "|  2. Show avaloble tests to do         |" << endl;
    cout << "|  3. Log Out                           |" << endl;
    cout << "#=======================================#" << endl;
    cout << "Your choice: ";
}

void adminMenu() {
    cout << "#=======================================#" << endl;
    cout << "|        Welcome in test system         |" << endl;
    cout << "#=======================================#" << endl;
    cout << "|  1. Show all users                    |" << endl;
    cout << "|  2. Show all tests                    |" << endl;
    cout << "|  3. Log Out                           |" << endl;
    cout << "#=======================================#" << endl;
    cout << "Your choice: ";
}


void DoATest(vector<map<string, test>>::iterator test, vector<account>::iterator user) {
    TestResult result(test); 
    cout << "Starting test: " << test->begin()->second.test_name << endl;
    cout << string(50, '-') << endl;

    
    for (const auto& question : test->begin()->second.questions) {
        for (const auto& el : question) {
            cout << "Question: " << el.first << endl;

            
            for (size_t i = 0; i < el.second.size(); ++i) {
                cout << i + 1 << ". " << el.second[i].first << endl;
            }

            
            int userAnswer;
            do {
                cout << "Your answer (1-" << el.second.size() << "): ";
                cin >> userAnswer;

                if (userAnswer < 1 || userAnswer > static_cast<int>(el.second.size())) {
                    cout << "Invalid choice. Please try again." << endl;
                }
            } while (userAnswer < 1 || userAnswer > static_cast<int>(el.second.size()));

           
            bool isCorrect = el.second[userAnswer - 1].second;
            result.addAnswer(el.first, el.second[userAnswer - 1].first, isCorrect);
        }
    }

    
    user->Results.push_back(result);

    
    cout << string(50, '-') << endl;
    cout << "Test completed! Your results:" << endl;
    result.printResults();
    cout << endl;
}


void showAllUsers(vector<account>& Accounts) {
    while (true) {
        system("cls");
        cout << "All Users:\n";
        for (size_t i = 0; i < Accounts.size(); ++i) {
            cout << i + 1 << ". " << "Login: " << Accounts[i].getUsername() << "\n";
            cout << "   Name: " << Accounts[i].full_name << "\n";
            cout << "   Address: " << Accounts[i].adress << "\n";
            cout << "   Phone: " << Accounts[i].phone_number << "\n";
            cout << "   Tests Taken: " << Accounts[i].Results.size() << "\n\n";
        }

        cout << "1. Add Account\n";
        cout << "2. Delete Account\n";
        cout << "3. Modify Account\n";
        cout << "4. Go Back\n";
        cout << "Your choice: ";
        int choice;
        cin >> choice;

        if (choice == 4) return;

        if (choice == 1) {
            cout << "Adding a new account:\n";
            registerAccount(Accounts);
        }
        else if (choice == 2) {
            cout << "Enter the number of the account to delete: ";
            size_t index;
            cin >> index;
            if (index > 0 && index <= Accounts.size()) {
                Accounts.erase(Accounts.begin() + index - 1);
            }
            else {
                cout << "Invalid index!\n";
            }
        }
        else if (choice == 3) {
            cout << "Enter the number of the account to modify: ";
            size_t index;
            cin >> index;
            if (index > 0 && index <= Accounts.size()) {
                modifyAccount(Accounts[index - 1]);
            }
            else {
                cout << "Invalid index!\n";
            }
        }
    }
}

void modifyAccount(account& acc) {
    while (true) {
        cout << "1. Modify Address\n";
        cout << "2. Modify Name\n";
        cout << "3. Modify Phone Number\n";
        cout << "4. Go Back\n";
        cout << "Your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {    
        case 1:
            cout << "Enter new address: ";
            cin.ignore();
            getline(cin, acc.adress);
            break;
        case 2:
            cout << "Enter new name: ";
            cin.ignore();
            getline(cin, acc.full_name);
            break;
        case 3:
            cout << "Enter new phone number: ";
            cin >> acc.phone_number;
            break;
        case 4:
            return;
        default:
            cout << "Invalid choice!\n";
        }
    }
}

void showAllTests(tests& testCollection) {
    while (true) {
        system("cls");
        cout << "All Tests:\n";
        size_t index = 1;
        for (auto& topic : testCollection.Test) {
            for (auto& el : topic) {
                cout << index++ << ". " << "Topic: " << el.first << "\n";
                cout << "   Test: " << el.second.test_name << "\n";
                cout << "   Questions: " << el.second.questions.size() << "\n\n";
            }
        }

        cout << "1. Add Test\n";
        cout << "2. Delete Test\n";
        cout << "3. Modify Test\n";
        cout << "4. Go Back\n";
        cout << "Your choice: ";
        int choice;
        cin >> choice;

        if (choice == 4) return;

        if (choice == 1) {
            cout << "Enter the topic of the new test: ";
            string topic;
            cin.ignore();
            getline(cin, topic);

            cout << "Enter the name of the new test: ";
            string testName;
            getline(cin, testName);

            test newTest(testName);
            testCollection.addTest(topic, newTest);
            cout << "Test added successfully!\n";
        }
        else if (choice == 2) {
            cout << "Enter the number of the test to delete: ";
            size_t index;
            cin >> index;
            if (index > 0 && index <= testCollection.Test.size()) {
                testCollection.Test.erase(testCollection.Test.begin() + index - 1);
                cout << "Test deleted successfully!\n";
            }
            else {
                cout << "Invalid index!\n";
            }
        }
        else if (choice == 3) {
            cout << "Enter the number of the test to modify: ";
            size_t index;
            cin >> index;
            if (index > 0 && index <= testCollection.Test.size()) {
                auto& test = testCollection.Test[index - 1];
                while (true) {
                    cout << endl;
                    cout << "1. Modify Test Name\n";
                    cout << "2. Add Question\n";
                    cout << "3. Delete Question\n";
                    cout << "4. Go Back\n";
                    cout << "Your choice: ";
                    int choice;
                    cin >> choice;
                    string question;
                    string answer;
                    array<pair<string, bool>, 4> answers;
                    switch (choice) {
                    case 1:
                        cout << "Enter new test name: ";
                        cin.ignore();
                        getline(cin, test.begin()->second.test_name);
                        break;
                    case 2:
                        cout << "Enter the question: ";
                        
                        cin.ignore();
                        getline(cin, question);

                        cout << "Enter 4 answers (mark correct answers with '*'):\n";
                        
                        for (size_t i = 0; i < 4; ++i) {
                            cout << "Answer " << i + 1 << ": ";
                            
                            getline(cin, answer);
                            answers[i] = { answer, answer.back() == '*' };
                            if (answers[i].second) {
                                answers[i].first.pop_back(); 
                            }
                        }

                        test.begin()->second.addQuestion(question, answers);
                        cout << "Question added successfully!\n";
                        break;
                    case 3:
                        cout << "Current questions:\n";
                        for (size_t i = 0; i < test.begin()->second.questions.size(); ++i) {
                            cout << i + 1 << ". " << test.begin()->second.questions[i].begin()->first << "\n";
                        }

                        cout << "Enter the number of the question to delete: ";
                        size_t questionIndex;
                        cin >> questionIndex;

                        if (questionIndex > 0 && questionIndex <= test.begin()->second.questions.size()) {
                            test.begin()->second.questions.erase(test.begin()->second.questions.begin() + questionIndex - 1);
                            cout << "Question deleted successfully!\n";
                        }
                        else {
                            cout << "Invalid index!\n";
                        }
                        break;
                    case 4:
                        return;
                    default:
                        cout << "Invalid choice!\n";
                    }
                }
            }
            else {
                cout << "Invalid index!\n";
            }
        }
    }
}
