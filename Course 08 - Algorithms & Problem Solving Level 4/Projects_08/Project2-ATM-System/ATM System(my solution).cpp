//ATM System 

#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <fstream>
#include <cmath>
#include <iomanip>
using namespace std;
const string ClientsFileName = "Clients.txt";

struct stClient {
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};

enum enATMOptions {
	QuickWithdraw = 1, NormalWithdraw = 2, Deposit = 3,
	CheckBalance = 4, Logout = 5
};
stClient CurrentClient;

void ShowATMMainMenue();
void Login();

vector <string> SplitString(string S1, string delim) {

	vector <string> vString;

	short pos = 0;
	string sWord;

	while ((pos = S1.find(delim)) != std::string::npos) {
		sWord = S1.substr(0, pos);

		if (sWord != "")
			vString.push_back(sWord);

		S1.erase(0, pos + delim.length());
	}

	if (S1 != "")
		vString.push_back(S1);

	return vString;

}
string ConvertRecordToLine(stClient Client, string Seperator = "#//#") {
	string ClientRecord = "";

	ClientRecord += Client.AccountNumber + Seperator;
	ClientRecord += Client.PinCode + Seperator;
	ClientRecord += Client.Name + Seperator;
	ClientRecord += Client.Phone + Seperator;
	ClientRecord += to_string(Client.AccountBalance);

	return ClientRecord;
}
stClient ConvertLinetoRecord(string LineData, string Seperator = "#//#") {
	stClient Client;

	vector<string> vClientData;
	vClientData = SplitString(LineData, Seperator);

	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]);

	return Client;
}
vector <stClient> LoadClientsDataFromFile(string FileName) {
	vector <stClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open()) {
		string Line;
		stClient Client;

		while (getline(MyFile, Line)) {
			Client = ConvertLinetoRecord(Line);
			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return vClients;
}
void SaveCleintsDataToFile(string FileName, vector<stClient> vClients) {

	fstream MyFile;

	MyFile.open(FileName, ios::out);
	string DataLine;

	if (MyFile.is_open()) {

		for (stClient C : vClients) {

			if (C.MarkForDelete == false) {
				//we only write records that are not marked for delete.      
				DataLine = ConvertRecordToLine(C);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
}

int ReadAmount(enATMOptions Option) {
	int Amount;
	if (Option == enATMOptions::NormalWithdraw)
		cout << "\nEnter an amount multiple of 5's ? ";
	else if (Option == enATMOptions::Deposit )
		cout << "\nEnter a positive deposit amount? ";
	cin >> Amount;
	return Amount;
}
string ReadAccountNumber() {
	string AccountNumber = "";
	cout << "\nPlease enter Account Number? ";
	cin >> AccountNumber;
	return AccountNumber;
}
string ReadUserPIN() {
	string PIN = "";
	cout << "Please enter PIN? ";
	cin >> PIN;
	return PIN;
}
short ReadQuickWithdrawOption() {
	short c;
	cout << "\nChoose what to withdraw from? [1 to 8]? ";
	cin >> c;

	return c;

}
enATMOptions ReadATMOption() {
	short c;
	cout << "Choose what do you want to do? [1 to 5]? ";
	cin >> c;

	return (enATMOptions)c;

}

void LoginScreen_Header() {
	cout << "\n-------------------------------------------\n";
	cout << "\t\tLogin Screen\n";
	cout << "-------------------------------------------\n";
}
void Header_ATM(enATMOptions Option) {
	switch (Option) {
	case enATMOptions::CheckBalance:
		cout << "===========================================\n";
		cout << "\t   Check Balance Screen\n";
		cout << "===========================================\n";
		break;
	case enATMOptions::NormalWithdraw:
		cout << "===========================================\n";
		cout << "\t  Normal Withdraw Screen\n";
		cout << "===========================================\n";
		break;
	case enATMOptions::QuickWithdraw:
		cout << "===========================================\n";
		cout << "\t  Quick Withdraw Screen\n";
		cout << "===========================================\n";
		cout << "\t[1] 20  \t  [2] 50\n";
		cout << "\t[3] 100 \t  [4] 200\n";
		cout << "\t[5] 400 \t  [6] 600\n";
		cout << "\t[7] 800 \t  [8] 1000\n";
		cout << "\t[9] Exit.\n";
		break;
	case enATMOptions::Deposit:
		cout << "===========================================\n";
		cout << "\t\tDeposit Screen\n";
		cout << "===========================================\n";
		break;
	}
}

bool FindClientByAccNumAndPIN(string AccountNumber, string PINCode, stClient& Client) {
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	for (stClient C : vClients) {
		if (C.AccountNumber == AccountNumber && C.PinCode == PINCode) {
			Client = C;
			return true;
		}
	}
	return false;
}

bool DepositeBlanceByAccountNumber(string AccountNumber, double DepositeAmount, vector <stClient>& vClients , stClient& Client) {
	char Answer;
	short Counter = 0;

	cout << "\nAre you sure you want to preform this transaction? y/n? ";
	cin >> Answer;

	if (tolower(Answer) == 'y') {
		for (stClient& C : vClients) {

			if (C.AccountNumber == AccountNumber) {
				C.AccountBalance += DepositeAmount;
				SaveCleintsDataToFile(ClientsFileName, vClients);
				cout << "\n\nDone Successfully, New Balance is: "
					<< C.AccountBalance << endl;
				Client = C;
				return true;
			}
		}
		return true;
	}
}

void PrintBalance(stClient Client) {
	cout << "\nYour Balance is: " << Client.AccountBalance << "\n";
}

short WhatToWithdraw(short Option) {

	switch (Option) {
	case 1:
		return 20;
	case 2:
		return 50;
	case 3:
		return 100;
	case 4:
		return 200;
	case 5:
		return 400;
	case 6:
		return 600;
	case 7:
		return 800;
	case 8:
		return 1000;
	case 9:
		ShowATMMainMenue();
		return 0;
	}
}

void QuickWithdrawScreen() {
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	Header_ATM(enATMOptions::QuickWithdraw);
	PrintBalance(CurrentClient);

	short Amount = WhatToWithdraw(ReadQuickWithdrawOption());

	while (Amount > CurrentClient.AccountBalance) {
		cout << "\nAmont Exceeds the balance, "
			<< "you can withdraw up to : "
			<< CurrentClient.AccountBalance << endl;
		Amount = WhatToWithdraw(ReadQuickWithdrawOption());
	}

	DepositeBlanceByAccountNumber(CurrentClient.AccountNumber, Amount * -1, vClients,CurrentClient);
}
void WithdrawScreen() {
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	short Amount;

	Header_ATM(enATMOptions::NormalWithdraw);

	do {
		Amount = ReadAmount(enATMOptions::NormalWithdraw);
	} while (Amount % 5 != 0);

	while (Amount > CurrentClient.AccountBalance) {
		cout << "\nAmont Exceeds the balance, "
			<< "you can withdraw up to : "
			<< CurrentClient.AccountBalance << endl;
		do {
			Amount = ReadAmount(enATMOptions::NormalWithdraw);
		} while (Amount % 5 != 0);
	}

	DepositeBlanceByAccountNumber(CurrentClient.AccountNumber, Amount * -1, vClients, CurrentClient);
}
void DepositScreen() {
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	double Amount;

	Header_ATM(enATMOptions::Deposit);

	do {
		Amount = ReadAmount(enATMOptions::Deposit);
	} while (Amount <= 0);

	DepositeBlanceByAccountNumber(CurrentClient.AccountNumber, Amount, vClients,CurrentClient);
}
void CheckBalanceScrean() {

	Header_ATM(enATMOptions::CheckBalance);
	PrintBalance(CurrentClient);
}

void GoBackToATMMainMenue() {
	cout << "\nPress any key to go back to ATM Main Menue...";
	system("pause>0");
	ShowATMMainMenue();
}

void WhatToDo_ATM(enATMOptions Option) {
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	switch (Option) {
	case enATMOptions::QuickWithdraw:
		system("cls");
		QuickWithdrawScreen();
		GoBackToATMMainMenue();
		break;
	case enATMOptions::NormalWithdraw:
		system("cls");
		WithdrawScreen();
		GoBackToATMMainMenue();		
		break;
	case enATMOptions::Deposit:
		system("cls");
		DepositScreen();
		GoBackToATMMainMenue();
		break;
	case enATMOptions::CheckBalance:
		system("cls");
		CheckBalanceScrean();
		GoBackToATMMainMenue();
		break;
	case enATMOptions::Logout:
		system("cls");
		Login();
		break;
	}
}

void ShowATMMainMenue() {

	system("cls");
	cout << "===========================================\n";
	cout << "\t  ATM Main Menue Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Quick Withdraw.\n";
	cout << "\t[2] Normal Withdraw.\n";
	cout << "\t[3] Deposit.\n";
	cout << "\t[4] Check Balances.\n";
	cout << "\t[5] Logout.\n";
	cout << "===========================================\n";
	WhatToDo_ATM(ReadATMOption());
}

void Login() {
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	string AccountNumber;
	string PIN;

	LoginScreen_Header();

	do {
		AccountNumber = ReadAccountNumber();
		PIN = ReadUserPIN();
		if (!FindClientByAccNumAndPIN(AccountNumber, PIN, CurrentClient)) {
			system("cls");
			LoginScreen_Header();
			cout << "\nInvlaid Account Number/PIN!\n";
		}

	} while (!FindClientByAccNumAndPIN(AccountNumber, PIN, CurrentClient));

	ShowATMMainMenue();
}

int main() {
	Login();
	return 0;
}
