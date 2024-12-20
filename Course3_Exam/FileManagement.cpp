#include "Header.h"



void saveAccounts(vector<account>& Accounts, const string& filename) {
    ofstream outFile(filename, ios::out | ios::trunc);
    if (!outFile) {
        cerr << "Error: Unable to open file for saving accounts." << endl;
        return;
    }

    for (auto& acc : Accounts) {
        outFile << acc.getUsername() << "\n";
        outFile << acc.getPassword() << "\n";
        outFile << acc.full_name << "\n";
        outFile << acc.adress << "\n";
        outFile << acc.phone_number << "\n";
        outFile << acc.Results.size() << "\n";

        for (auto& result : acc.Results) {
            outFile << result.getTestRef()->begin()->second.test_name << "\n";
            outFile << result.getTestRef()->begin()->first << "\n";
            outFile << result.calculateScore() << "\n";

            for (const auto& answer : result.answers) {
                outFile << answer.first << "|" << answer.second.first << "|" << answer.second.second << "\n";
            }
        }
    }

    outFile.close();
    cout << "Accounts saved successfully to " << filename << "\n";
}


void loadAccounts(vector<account>& Accounts, const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Error: Unable to open file for loading accounts." << endl;
        return;
    }

    Accounts.clear();
    string username, password, full_name, adress, phone_number;
    size_t resultsCount;

    while (getline(inFile, username)) {
        getline(inFile, password);
        getline(inFile, full_name);
        getline(inFile, adress);
        getline(inFile, phone_number);
        inFile >> resultsCount;
        inFile.ignore();

        account acc(username, password, phone_number, full_name, adress);

        for (size_t i = 0; i < resultsCount; ++i) {
            string testName, topicName;
            int score;

            getline(inFile, testName);
            getline(inFile, topicName);
            inFile >> score;
            inFile.ignore();

            TestResult result({});

            string question, chosenAnswer;
            bool isCorrect;

            while (getline(inFile, question, '|')) {
                getline(inFile, chosenAnswer, '|');
                inFile >> isCorrect;
                inFile.ignore();
                result.addAnswer(question, chosenAnswer, isCorrect);
            }

            acc.Results.push_back(result);
        }

        Accounts.push_back(acc);
    }

    inFile.close();
    cout << "Accounts loaded successfully from " << filename << "\n";
}




void saveTests(const tests& testCollection, const string& filename) {
    ofstream outFile(filename, ios::out | ios::trunc);
    if (!outFile) {
        cerr << "Error: Unable to open file for saving tests." << endl;
        return;
    }

    for (const auto& topic : testCollection.Test) {
        for (const auto& el : topic) {
            outFile << el.first << "\n";
            outFile << el.second.test_name << "\n";
            outFile << el.second.questions.size() << "\n";

            for (const auto& question : el.second.questions) {
                outFile << question.begin()->first << "\n";
                for (const auto& answer : question.begin()->second) {
                    outFile << answer.first << "|" << answer.second << "\n";
                }
            }
        }
    }

    outFile.close();
    cout << "Tests saved successfully to " << filename << "\n";
}


void loadTests(tests& testCollection, const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Error: Unable to open file for loading tests." << endl;
        return;
    }

    testCollection.Test.clear();
    string topicName, testName, questionText, answerText;
    size_t questionCount;

    while (getline(inFile, topicName)) {
        getline(inFile, testName);
        inFile >> questionCount;
        inFile.ignore();

        test newTest(testName);

        for (size_t i = 0; i < questionCount; ++i) {
            getline(inFile, questionText);
            array<pair<string, bool>, 4> answers;

            for (size_t j = 0; j < 4; ++j) {
                getline(inFile, answerText);
                size_t delimiterPos = answerText.find('|');
                answers[j].first = answerText.substr(0, delimiterPos);
                answers[j].second = (answerText.substr(delimiterPos + 1) == "1");
            }

            newTest.addQuestion(questionText, answers);
        }

        map<string, test> topic;
        topic[topicName] = newTest;
        testCollection.Test.push_back(topic);
    }

    inFile.close();
    cout << "Tests loaded successfully from " << filename << "\n";
}
