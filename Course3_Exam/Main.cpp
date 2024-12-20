#include "Header.h"
vector<string> account::used_logins;

int main()
{
    vector<account> Accounts;
    vector<account>::iterator AccInUse = Accounts.end(); 
    tests testCollection;
    loadTests(testCollection, "Data/tests.txt");
    loadAccounts(Accounts, "Data/accounts.txt");


start:
    
    printWelcomeMenu();
    int ch;
    cin >> ch;

    try {
        switch (ch) {
        case 1:
            AccInUse = login(Accounts);
            break;
        case 2:
            AccInUse = registerAccount(Accounts);
            break;
        case 3:
            saveAccounts(Accounts, "Data/accounts.txt");
            saveTests(testCollection, "Data/tests.txt");
            return 0;
        default:
            system("cls");
            cout << "\nInvalid input, returning to start window\n\n";
            goto start;
        }
    }
    catch (exception& ex) {
        system("cls");
        cout << "Error occurred: " << ex.what() << endl;
        cout << "Returning to main menu.";
        goto start;
    }

    system("cls");
    cout << "Successfully logged in.\n\n";
    
    if (AccInUse->isAdmin()) 
    {
        admen:
        adminMenu();
        int ch1_2;
        cin >> ch1_2;
        switch (ch1_2)
        {
        case 1:
            showAllUsers(Accounts);
            goto admen;
        case 2:
            showAllTests(testCollection);
            goto admen;
        case 3:
            system("cls");
            cout << "\nLogging out. Returning to main menu\n\n";
            goto start;
        default:
            system("cls");
            cout << "\nInvalid input. Try again\n\n";
            goto admen;
        }

    }
    else 
    {
        regmen:
        regularMenu();
        int ch2;
        int chNum = 0;
        cin >> ch2;
        switch (ch2)
        {
        case 1:
            cout << "Finished tests: " << AccInUse->Results.size() << endl << endl;
            for (auto el : AccInUse->Results) {
                el.printResults();
            }
            cout << string(50, '-') << endl;
            goto regmen;
        case 2: 
            system("cls");
            cout << endl << "Tests: " << endl;
            
            for (const auto& topic : testCollection.Test) {
                for (const auto& el : topic) {
                    bool alreadyTaken = false;

                   
                    for (auto& result : AccInUse->Results) {
                        if (result.getTestRef()->begin()->second.test_name == el.second.test_name) {
                            alreadyTaken = true;
                            break;
                        }
                    }

                    cout << "Choice number: " << chNum << endl; chNum++;
                    cout << "Topic: " << el.first << "\n";
                    cout << "Test: " << el.second.test_name << "\n";
                    cout << "Questions: " << el.second.questions.size() << "\n";
                    cout << "Status: " << (alreadyTaken ? "Not available (already completed)" : "Available") << "\n\n";
                }
            }
            cout << string(50, '-') << endl;
            int ch3;
            cout << "#========================================#" << endl;
            cout << "|Would you like to do a test from list?  |" << endl;
            cout << "#========================================#" << endl;
            cout << "|Select number of test you want to go for|" << endl;
            cout << "|Enter -1 to return to the menu          |" << endl;
            cout << "#========================================#" << endl;
            cin >> ch3;
            switch (ch3)
            {
            case -1:
                system("cls");
                cout << "\n Returning to the menu\n\n";
                goto regmen;
            default:
                if (ch3 < 0 || ch3 > testCollection.Test.size()) {
                    system("cls");
                    cout << "\nInvalid input, returning to menu\n\n";
                }
                int j = 0;
                for (auto i = testCollection.Test.begin(); j < ch3+1; i++)
                {
                    if (j == ch3) {
                        cout << endl;
                        DoATest(i, AccInUse);
                        break;
                    }
                    else j++;
                }
            }
            goto regmen;
        case 3:
            system("cls");
            goto start;
        default:
            system("cls");
            cout << "\nInvalid input, try again\n\n";
            goto regmen;
        }
    }
}
