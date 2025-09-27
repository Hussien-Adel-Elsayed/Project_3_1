#include<iostream>
#include<string>
#include<cstdlib>
#include <iomanip>
#include <cctype>
#include <vector>
#include <fstream>

using namespace std;

const string ClientsFileName = "Clients.txt";

enum enUserChoice { ShowClientList = 1, AddNewClients, DeleteClients, UpdateClientInfo, FindClients, Exits };

struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};

void ResetScreen()
{
	system("cls");
	system("color 0f");
}

string ReadAccountNumber()
{
	string str;

	cout << "\nPlease Enter AccountNumber? ";
	getline(cin >> ws, str);

	return str;;
}

vector <string> SplitString(string S1, string delim)
{
	vector <string> vString;

	short pos = 0;
	string sWord;

	while ((pos = S1.find(delim)) != string::npos)
	{
		sWord = S1.substr(0, pos);
		if (sWord != "")
		{
			vString.push_back(sWord);
		}

		S1.erase(0, pos + delim.length());
	}

	if (S1 != "")
	{
		vString.push_back(S1);
	}

	return vString;

}

sClient ConvertLineToRecord(string Line, string Seperator = "#//#")
{
	sClient Client;
	vector <string> vClientData;

	vClientData = SplitString(Line, Seperator);

	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]);

	return Client;

}

vector <sClient> LoadClientDataFormFile(string FileName)
{
	vector <sClient> vClient;
	fstream MyFile;

	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string Line;
		sClient Client;

		while (getline(MyFile, Line))
		{
			Client = ConvertLineToRecord(Line);

			vClient.push_back(Client);
		}

		MyFile.close();
	}

	return vClient;
}

void AddDataToFile(string FileName, string stDataLine)
{
	fstream MyFile;

	MyFile.open(ClientsFileName, ios::app);

	if (MyFile.is_open())
	{
		MyFile << stDataLine << endl;

		MyFile.close();
	}
}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{
	string stClientRecord = "";

	stClientRecord += Client.AccountNumber + Seperator;
	stClientRecord += Client.PinCode + Seperator;
	stClientRecord += Client.Name + Seperator;
	stClientRecord += Client.Phone + Seperator;
	stClientRecord += to_string(Client.AccountBalance);

	return stClientRecord;
}

sClient ReadNewClient()
{
	vector <sClient> vClient = LoadClientDataFormFile(ClientsFileName);

	sClient Client;

	string AccountNumber;
	bool AccountNumberIsExist;

	cout << "Enter Account Number? ";
	cin >> AccountNumber;

	do
	{
		AccountNumberIsExist = false;

		for (sClient c : vClient)
		{
			if (c.AccountNumber == AccountNumber)
			{
				AccountNumberIsExist = true;
				cout << "\n\nClient With [" << AccountNumber << "] alredy exists, Enter another Account Number ? ";
				getline(cin >> ws, AccountNumber);
				break;
			}
		}

	} while (AccountNumberIsExist);

	Client.AccountNumber = AccountNumber;


	cout << "Enter PinCode? ";
	getline(cin >> ws, Client.PinCode);

	cout << "Enter Name? ";
	getline(cin, Client.Name);

	cout << "Enter Phone? ";
	getline(cin, Client.Phone);

	cout << "Enter Account Balance? ";
	cin >> Client.AccountBalance;

	return Client;
}

void AddNewClient()
{
	sClient Client;

	Client = ReadNewClient();
	AddDataToFile(ClientsFileName, ConvertRecordToLine(Client));
}

void AddClients()
{
	ResetScreen();

	char AddMore = 'Y';

	do
	{
		ResetScreen();

		cout << "\n----------------------------------------\n";
		cout << "\tAdd New Clients Screen";
		cout << "\n----------------------------------------\n";

		cout << "Adding New Client:\n\n";

		AddNewClient();
		cout << "\nClient Added Successfully, do you want to add more clients? [Y/N]? ";
		cin >> AddMore;

	} while (toupper(AddMore) == 'Y');

	cout << "\nPress any key to go back to Main Menue...";
	system("pause > nul");
}

enUserChoice ReadUserChoice()
{
	short UserChoice = 0;

	cout << "Choose what do you want to do ? [1 to 6]? ";
	cin >> UserChoice;

	while (cin.fail() || UserChoice <= 0 || UserChoice > 6)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "Invalid Choice, Enter a valid once: ";
		cin >> UserChoice;
	}

	return (enUserChoice)UserChoice;
}

void PrintClientRecord(sClient Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintAllClientsData(vector <sClient> vClients)
{
	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	for (sClient Client : vClients)
	{
		PrintClientRecord(Client);
		cout << endl;
	}

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}

void ShowClientsList()
{
	ResetScreen();

	vector <sClient> vClient = LoadClientDataFormFile(ClientsFileName);
	PrintAllClientsData(vClient);

	cout << "\nPress any key to go back to Main Menue...";
	system("pause > nul");
}

void PrintClientCard(sClient Client)
{
	cout << "\nThe following are the client details:\n";
	cout << "\nAccout Number: " << Client.AccountNumber;
	cout << "\nPin Code     : " << Client.PinCode;
	cout << "\nName         : " << Client.Name;
	cout << "\nPhone        : " << Client.Phone;
	cout << "\nAccount Balance: " << Client.AccountBalance;
}

bool FindClientByAccountNumber(string AccountNumber, vector <sClient> vClients, sClient& Client)
{

	for (sClient& c : vClients)
	{
		if (c.AccountNumber == AccountNumber)
		{
			Client = c;
			return true;
		}
	}

	return false;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
	for (sClient& c : vClients)
	{
		if (c.AccountNumber == AccountNumber)
		{
			c.MarkForDelete = true;
			return true;
		}
	}
}

void SaveClientsDataToFile(string FileName, vector <sClient> vClients)
{
	fstream MyFile;

	MyFile.open(FileName, ios::out);

	string DataLine;

	if (MyFile.is_open())
	{
		for (sClient c : vClients)
		{
			if (c.MarkForDelete == false)
			{
				DataLine = ConvertRecordToLine(c);
				MyFile << DataLine << endl;
			}
		}

		MyFile.close();
	}

}

sClient ChangeClientRecord(string AccountNumber)
{
	sClient Client;

	Client.AccountNumber = AccountNumber;

	cout << "\n\nEnter PinCode? ";
	getline(cin >> ws, Client.PinCode);

	cout << "Enter Name? ";
	getline(cin, Client.Name);

	cout << "Enter Phone? ";
	getline(cin, Client.Phone);

	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;

	return Client;
}

bool UpdateClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
	sClient Client;

	char Answer = 'n';

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);

		cout << "\n\nAre you sure you want Updated this client? y/n ? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			for (sClient& c : vClients)
			{
				if (c.AccountNumber == AccountNumber)
				{
					c = ChangeClientRecord(AccountNumber);
					break;
				}
			}

			SaveClientsDataToFile(ClientsFileName, vClients);

			cout << "\n\nClient Updated Successfully.";
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
		return false;
	}
}

bool DeleteClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
	sClient Client;

	char Answer = 'n';

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);

		cout << "\n\nAre you sure you want delete this client? y/n ? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
			SaveClientsDataToFile(ClientsFileName, vClients);
			vClients = LoadClientDataFormFile(ClientsFileName);

			cout << "\n\nClient Deleted Successfully.";
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
		return false;
	}
}

bool SearchClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
	sClient Client;

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);

		return true;

	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
		return false;
	}
}

void FindClient()
{
	ResetScreen();

	cout << "\n----------------------------------------\n";
	cout << "\tFind Client Screen";
	cout << "\n----------------------------------------\n";

	string AccountNumber = ReadAccountNumber();

	vector <sClient> vClient = LoadClientDataFormFile(ClientsFileName);

	SearchClientByAccountNumber(AccountNumber, vClient);

	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause > nul");

}

void DeleteClient()
{
	ResetScreen();

	cout << "\n----------------------------------------\n";
	cout << "\tDelete Client Screen";
	cout << "\n----------------------------------------\n";

	string AccountNumber = ReadAccountNumber();

	vector <sClient> vClient = LoadClientDataFormFile(ClientsFileName);

	DeleteClientByAccountNumber(AccountNumber, vClient);

	cout << "\nPress any key to go back to Main Menue...";
	system("pause > nul");
}

void UpdateClient()
{
	ResetScreen();

	cout << "\n----------------------------------------\n";
	cout << "\tUpdate Client Info Screen";
	cout << "\n----------------------------------------\n";

	string AccountNumber = ReadAccountNumber();

	vector <sClient> vClient = LoadClientDataFormFile(ClientsFileName);

	UpdateClientByAccountNumber(AccountNumber, vClient);

	cout << "\nPress any key to go back to Main Menue...";
	system("pause > nul");
}

void Exit()
{
	ResetScreen();

	cout << "\n----------------------------------------\n";
	cout << "\tProgram Ends :-)";
	cout << "\n----------------------------------------\n";
	system("pause > nul");
}

void MainMenueScreen()
{
	ResetScreen();

	cout << "\n=================================================\n";
	cout << "\t\tMain Menue Screen\t\t\n";
	cout << "=================================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Exit.\n";
	cout << "=================================================\n";

	enUserChoice UserChoice = ReadUserChoice();

	switch (UserChoice)
	{
	case enUserChoice::ShowClientList:
		ShowClientsList();
		MainMenueScreen();
		break;
	case enUserChoice::AddNewClients:
		AddClients();
		MainMenueScreen();
		break;
	case enUserChoice::DeleteClients:
		DeleteClient();
		MainMenueScreen();
		break;
	case enUserChoice::UpdateClientInfo:
		UpdateClient();
		MainMenueScreen();
		break;
	case enUserChoice::FindClients:
		FindClient();
		MainMenueScreen();
		break;
	case enUserChoice::Exits:
		Exit();
	}



}

int main()
{


	MainMenueScreen();




	return 0;
}