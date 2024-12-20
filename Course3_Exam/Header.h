#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <array>
using namespace std;


class test {
public:
	string test_name; 
	vector<map<string, array<pair<string, bool>, 4>>> questions; 

	test() : test_name("") {}
	test(string name) : test_name(name) {}

	void addQuestion(const string& question, const array<pair<string, bool>, 4>& answers) {
		map<string, array<pair<string, bool>, 4>> q;
		q[question] = answers;
		questions.push_back(q);
	}
};

class tests {
public:
	vector<map<string, test>> Test; 

	void addTest(const string& topic, const test& t) {
		map<string, test> m;
		m[topic] = t;
		Test.push_back(m);
	}
};


class TestResult {
public:
	vector<map<string, test>>::iterator testRef; 

	vector<pair<string, pair<string, bool>>> answers;


	TestResult(vector<map<string, test>>::iterator test) : testRef(test) {}

	void addAnswer(const string& question, const string& chosenAnswer, bool isCorrect) {
		answers.push_back({ question, {chosenAnswer, isCorrect} });
	}

	int calculateScore() const {
		int correctAnswers = 0;
		for (const auto& answer : answers) {
			if (answer.second.second) {
				correctAnswers++;
			}
		}
		
		return static_cast<int>(12.0 * correctAnswers / answers.size());
	}

	void printResults() const {
		cout << "Results for test: " << testRef->begin()->second.test_name << endl;
		for (const auto& answer : answers) {
			cout << "Question: " << answer.first << endl;
			cout << "Your answer: " << answer.second.first
				<< (answer.second.second ? " (Correct)" : " (Incorrect)") << endl;
		}
		cout << "Final score: " << calculateScore() << "/12" << endl;
	}

	vector<map<string, test>>::iterator getTestRef() { return testRef; }
};



class account {
private:
	string login;
	string password;
	bool admin;
public:
	static vector<string>used_logins;
	string phone_number;
	string full_name;
	string adress;
	vector<TestResult> Results;

	account(string login, string password, string phone_number, string full_name, string adress) {
		for (auto el : used_logins) {
			if (login == el)
				throw exception("This accout name already taken.");
		}
		used_logins.push_back(login);
		this->login = login;
		if (login == "admin")
			admin = true;
		else
			admin = false;
		this->password= password;
		this->phone_number = phone_number;
		this->full_name = full_name;
		this->adress = adress;
		
	}

	account(const account& acc) {
		this->login = acc.login;
		this->password = acc.password;
		this->admin = acc.admin;
		this->phone_number = acc.phone_number;
		this->full_name = acc.full_name;
		this->adress = acc.adress;
		for (auto el : acc.Results) {
			this->Results.push_back(el);
		}
	}

	bool compare(string login, string password) {
		return this->login == login && this->password == password;
	}

	bool isAdmin() {
		return admin;
	}

	string getUsername() {
		return this->login;
	}
	string getPassword() {
		return this->password;
	}
};






void printWelcomeMenu();


vector<account>::iterator login(vector<account>&Accounts);
vector<account>::iterator registerAccount(vector<account>& Accounts);

void regularMenu();
void adminMenu();

void DoATest(vector<map<string, test>>::iterator test, vector<account>::iterator user);

void showAllUsers(vector<account>& Accounts);
void modifyAccount(account& acc);
void showAllTests(tests& testCollection);

void saveAccounts(vector<account>& Accounts, const string& filename);
void loadAccounts(vector<account>& Accounts, const string& filename);
void saveTests(const tests& testCollection, const string& filename);
void loadTests(tests& testCollection, const string& filename);