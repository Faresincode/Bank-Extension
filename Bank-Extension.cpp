#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;
//=================================================== Global variables ====================================================
const string ClientsFileName = "Clients.txt";
const string UsersFileName = "Users.txt";

//=================================================== structures variables ================================================
struct stClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;


};
struct stManagePermissions
{

	bool showClientList;
	bool AddNewClient;
	bool DeleteClient;
	bool UpdateClient;
	bool FindClient;
	bool Transaction;
	bool ManageUsers;

};
struct stUser
{
	string UserName = "";
	string Password = "";
	short Permission;
	bool MarkForDelete = false;
	stManagePermissions UserPermission;

};
//=================================================== enum variables ======================================================
enum enTransactionsMenueOptions { eDeposit = 1, eWithdraw = 2, eShowTotalBalance = 3, eShowMainMenue = 4 };
enum enMainMenueOptions { eListClients = 1, eAddNewClient = 2, eDeleteClient = 3, eUpdateClient = 4, eFindClient = 5, eTransactions = 6, eManageUsers = 7, eLogOut = 8 };
enum enMainMenueOptionsBitwise { enListClients = 1, enAddNewClient = 2, enDeleteClient = 4, enUpdateClient = 8, enFindClient = 16, enTransactions = 32, enManageUsers = 64, enLogOut = 0 };
enum enManageUsersOptions { eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3, eUpdateUser = 4, eFindUser = 5, eMainMenue = 6 };

//=================================================== declaration function ================================================ 
vector<string> SplitString(string, string);
stClient ConvertLinetoRecord(string, string);
stUser ConvertLinetoRecordForUsers(string, string);
string ConvertRecordToLine(stClient, string);
string ConvertRecordToLine(stUser, string);
bool IsClientExistsByAccountNumber(string, string);
stClient ReadNewClient();
vector <stClient> LoadCleintsDataFromFile(string);
vector<stUser>LoadUsersDataFromFile(string);
void PrintClientRecordLine(stClient);
void PrintUsersRecordLine(stUser);
void PrintClientRecordBalanceLine(stClient);
void ShowAllClientsScreen();
void ShowTotalBalances();
void PrintClientCard(stClient);
void PrintUsersCard(stUser);
bool FindClientByAccountNumber(string, vector <stClient>, stClient&);
bool FindUserByUserName(string, vector <stUser>, stUser&);
stClient ChangeClientRecord(string AccountNumber);
bool MarkClientForDeleteByAccountNumber(string, vector <stClient>&);
bool MarkUserForDeleteByUserName(string, vector <stUser>&);
vector <stClient> SaveCleintsDataToFile(string, vector <stClient>);
vector <stUser> SaveUsersDataToFile(string, vector <stUser>);
void AddDataLineToFile(string, string);
void AddNewClient();
void AddNewClients();
bool DeleteClientByAccountNumber(string, vector <stClient>&);
bool UpdateClientByAccountNumber(string, vector <stClient>&);
bool DepositBalanceToClientByAccountNumber(string, double, vector <stClient>&);
string ReadClientAccountNumber();
string ReadUserUserName();
void ShowDeleteClientScreen();
void ShowUpdateClientScreen();
void ShowAddNewClientsScreen();
void ShowFindClientScreen();
void ShowEndScreen();
void ShowDepositScreen();
void ShowWithDrawScreen();
void ShowTotalBalances();
void ShowUpdateUserScreen();
void GoBackToMainMenue(stUser);
void GoBackToManageUsersMenueScreen(stUser);
void GoBackToTransactionsMenue(stUser);
short ReadTransactionsMenueOption();
void PerfromTranactionsMenueOption(enTransactionsMenueOptions, stUser);
void ShowTransactionsMenue(stUser);
short ReadMainMenueOption();
short ReadManageMenueOption();
bool IsUserExistByUsername(string, string);
stUser LogIn();
void ShowLogInScreen();
void ShowListUsersScreen(stUser);
void PerfromMainMenueOption(enMainMenueOptions, stUser&);
void PerformManageUserMenueOption(enManageUsersOptions, stUser);
void  ShowManageUsersMenueScreen(stUser);
bool IsChoiceIsYes();
short ReadPermssion(stUser);
stUser AddNewUser();
void AddUser();
void AddUsers();
void ShowAddNewUsersScreen();
void FindUser();
void ShowFindUserScreen(stUser);
bool DeleteUserByUserName(string, vector<stUser>&);
void ShowDeleteUserScreen(stUser);
stUser ChangeUserRecords(string);
bool UpdateUserByUserName(string, vector<stUser>&);
void ShowMainMenue(stUser);
string ReverseString(string);
string FromDecimalToBinary(int);
short VerifyNum(short);
short VerifyNum(short Number)
{
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Invalid Number, Enter a valid one: " << endl;
		cin >> Number;
	}
	return Number;
}
string ReverseString(string MyString)
{

	string RevercedString = "";
	for (int i = MyString.length() - 1; i >= 0; i--)
	{
		RevercedString += MyString[i];
	}
	return RevercedString;
}
string FromDecimalToBinary(int Decimal)
{
	int OurDicimal = Decimal;
	int remainder, Binary;
	string BinaryRevercedInString = "";
	while (OurDicimal >= 1)
	{
		remainder = OurDicimal;
		OurDicimal = (OurDicimal / 2);
		Binary = remainder - (OurDicimal * 2);
		BinaryRevercedInString += to_string(Binary);
	}
	return ReverseString(BinaryRevercedInString);

}
//---------------------------------------------------------------------------------------------------
vector<string> SplitString(string S1, string Delim)
{

	vector<string> vString;

	short pos = 0;
	string sWord; // define a string variable

	// use find() function to get the position of the delimiters
	while ((pos = S1.find(Delim)) != std::string::npos)
	{
		sWord = S1.substr(0, pos); // store the word
		if (sWord != "")
		{
			vString.push_back(sWord);
		}

		S1.erase(0, pos + Delim.length());  //erase() until positon and move to next word
	}

	if (S1 != "")
	{
		vString.push_back(S1); // it adds last word of the string.
	}

	return vString;

}
stClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{

	stClient Client;
	vector<string> vClientData;

	vClientData = SplitString(Line, Seperator);

	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]);//cast string to double


	return Client;

}
stUser ConvertLinetoRecordForUsers(string Line, string Seperator = "#//#")
{
	stUser User;
	vector<string> vUsersData;
	vUsersData = SplitString(Line, Seperator);
	User.UserName = vUsersData[0];
	User.Password = vUsersData[1];
	User.Permission = stoi(vUsersData[2]);
	return User;
}
string ConvertRecordToLine(stClient Client, string Seperator = "#//#")
{

	string stClientRecord = "";

	stClientRecord += Client.AccountNumber + Seperator;
	stClientRecord += Client.PinCode + Seperator;
	stClientRecord += Client.Name + Seperator;
	stClientRecord += Client.Phone + Seperator;
	stClientRecord += to_string(Client.AccountBalance);

	return stClientRecord;

}
string ConvertRecordToLine(stUser Users, string Seperator = "#//#")
{

	string stUserRecord = "";
	stUserRecord += Users.UserName + Seperator;
	stUserRecord += Users.Password + Seperator;
	stUserRecord += to_string(Users.Permission);
	return stUserRecord;
}
//---------------------------------------------------------------------------------------------------
stUser ChangeUserRecords(string UserName)
{
	stUser User;
	User.UserName = UserName;
	cout << "\nPlease enter Password? ";
	getline(cin >> ws, User.Password);
	User.Permission = ReadPermssion(User);
	return User;

}
stClient ChangeClientRecord(string AccountNumber)
{
	stClient Client;

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
//---------------------------------------------------------------------------------------------------
vector <stClient> SaveCleintsDataToFile(string FileName, vector <stClient> vClients)
{

	fstream MyFile;
	MyFile.open(FileName, ios::out);//overwrite

	string DataLine;

	if (MyFile.is_open())
	{

		for (stClient C : vClients)
		{

			if (C.MarkForDelete == false)
			{
				//we only write records that are not marked for delete.
				DataLine = ConvertRecordToLine(C);
				MyFile << DataLine << endl;

			}

		}

		MyFile.close();

	}

	return vClients;

}
vector <stUser> SaveUsersDataToFile(string FileName, vector <stUser>vUsers)
{

	fstream MyFile;

	MyFile.open(FileName, ios::out); //write mode

	if (MyFile.is_open())
	{
		string DataLine;
		for (stUser user : vUsers)
		{
			if (user.MarkForDelete == false)
			{
				DataLine = ConvertRecordToLine(user);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}



	return vUsers;
}
vector <stClient> LoadCleintsDataFromFile(string FileName)
{
	vector <stClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);//read Mode

	if (MyFile.is_open())
	{
		stClient Client;
		string Line;
		while (getline(MyFile, Line))
		{
			Client = ConvertLinetoRecord(Line);
			vClients.push_back(Client);

		}
		MyFile.close();
	}
	return vClients;
}
vector<stUser>LoadUsersDataFromFile(string FileName)
{
	vector<stUser>vUsers;
	fstream MyFile;
	MyFile.open(FileName, ios::in); //read mode
	if (MyFile.is_open())
	{
		stUser User;
		string Line;
		while (getline(MyFile, Line))
		{
			User = ConvertLinetoRecordForUsers(Line);
			vUsers.push_back(User);
		}
		MyFile.close();
	}
	return vUsers;
}
//---------------------------------------------------------------------------------------------------
stClient ReadNewClient()
{
	stClient Client;

	cout << "Enter Account Number? ";

	// Usage of std::ws will extract allthe whitespace character

	getline(cin >> ws, Client.AccountNumber);
	while (IsClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
	{
		cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
		getline(cin >> ws, Client.AccountNumber);
	}

	cout << "Enter PinCode? ";
	getline(cin, Client.PinCode);

	cout << "Enter Name? ";
	getline(cin, Client.Name);

	cout << "Enter Phone? ";
	getline(cin, Client.Phone);

	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;

	return Client;

}
string ReadClientAccountNumber()
{
	string AccountNumber = "";

	cout << "\nPlease enter AccountNumber ? ";
	cin >> AccountNumber;
	return AccountNumber;

}
string ReadUserUserName()
{
	string UserName;
	cout << "\nEnter UserName? ";
	getline(cin >> ws, UserName);
	return UserName;
}
//---------------------------------------------------------------------------------------------------
short ReadMainMenueOption()
{
	short Choice = 0;
	do
	{
		cout << "Choose what do you want to do ? enter Number in this Range [1 To 8]? ";
		cin >> Choice;
		VerifyNum(Choice);
	} while (Choice > 8 || Choice < 1);
	return Choice;
}
short ReadManageMenueOption()
{
	short Choice = 0;
	do
	{
		cout << "Choose what do you want to do ? enter Number in this Range [1 To 6]? ";
		cin >> Choice;
		VerifyNum(Choice);
	} while (Choice > 6 || Choice < 1);
	return Choice;
}
short ReadTransactionsMenueOption()
{
	cout << "Choose what do you want to do? [1 to 4]? ";
	short Choice = 0;
	cin >> Choice;

	return Choice;
}
//---------------------------------------------------------------------------------------------------
stManagePermissions ReadUserPermissions(stUser User)
{

	cout << "\nShow Client List? y/n? ";
	if (IsChoiceIsYes())
		User.UserPermission.showClientList = true;
	else
		User.UserPermission.showClientList = false;
	cout << "\n Add New Client? y/n? ";
	if (IsChoiceIsYes())
		User.UserPermission.AddNewClient = true;
	else
		User.UserPermission.AddNewClient = false;
	cout << "\nDelete Client? y/n? ";
	if (IsChoiceIsYes())
		User.UserPermission.DeleteClient = true;
	else
		User.UserPermission.DeleteClient = false;
	cout << "\nUpdate Client? y/n? ";
	if (IsChoiceIsYes())
		User.UserPermission.UpdateClient = true;
	else
		User.UserPermission.UpdateClient = false;
	cout << "\nFind Client? y/n? ";
	if (IsChoiceIsYes())
		User.UserPermission.FindClient = true;
	else
		User.UserPermission.FindClient = false;
	cout << "\nTransactions? y/n? ";
	if (IsChoiceIsYes())
		User.UserPermission.Transaction = true;
	else
		User.UserPermission.Transaction = false;
	cout << "\nManage Users? y/n? ";
	if (IsChoiceIsYes())
		User.UserPermission.ManageUsers = true;
	else
		User.UserPermission.ManageUsers = false;

	return User.UserPermission;

}
short ReadPermssion(stUser User)
{

	char Choice = 'n';
	short Permission;
	cout << "\nDo you want to give access to all system (y/n) ? ";
	cin >> Choice;
	short BinaryOptionValue[7];
	if (tolower(Choice) == 'y')
	{
		return -1;
	}
	else
	{
		stManagePermissions  ManagePermissions;

		ManagePermissions = ReadUserPermissions(User);
		if (ManagePermissions.showClientList == true)
			BinaryOptionValue[0] = enMainMenueOptionsBitwise::enListClients;
		else
			BinaryOptionValue[0] = 0;

		if (ManagePermissions.AddNewClient == true)
			BinaryOptionValue[1] = enMainMenueOptionsBitwise::enAddNewClient;
		else
			BinaryOptionValue[1] = 0;

		if (ManagePermissions.DeleteClient == true)
			BinaryOptionValue[2] = enMainMenueOptionsBitwise::enDeleteClient;
		else
			BinaryOptionValue[2] = 0;

		if (ManagePermissions.UpdateClient == true)
			BinaryOptionValue[3] = enMainMenueOptionsBitwise::enUpdateClient;
		else
			BinaryOptionValue[3] = 0;

		if (ManagePermissions.FindClient == true)
			BinaryOptionValue[4] = enMainMenueOptionsBitwise::enFindClient;
		else
			BinaryOptionValue[4] = 0;

		if (ManagePermissions.Transaction == true)
			BinaryOptionValue[5] = enMainMenueOptionsBitwise::enTransactions;
		else
			BinaryOptionValue[5] = 0;

		if (ManagePermissions.ManageUsers == true)
			BinaryOptionValue[6] = enMainMenueOptionsBitwise::enManageUsers;
		else
			BinaryOptionValue[6] = 0;
	}
	return (BinaryOptionValue[0] | BinaryOptionValue[1] | BinaryOptionValue[2] | BinaryOptionValue[3] | BinaryOptionValue[4] | BinaryOptionValue[5] | BinaryOptionValue[6]);
}
//---------------------------------------------------------------------------------------------------
bool IsClientExistsByAccountNumber(string AccountNumber, string FileName)
{

	fstream MyFile;
	MyFile.open(FileName, ios::in);//read Mode

	if (MyFile.is_open())
	{

		string Line;
		stClient Client;

		while (getline(MyFile, Line))
		{

			Client = ConvertLinetoRecord(Line);
			if (Client.AccountNumber == AccountNumber)
			{
				MyFile.close();
				return true;
			}

		}

		MyFile.close();

	}

	return false;


}
bool IsUserExistByUsername(string UserName, string FileName)
{

	fstream MyFile;
	MyFile.open(FileName, ios::in);
	if (MyFile.is_open())
	{
		string Line;
		stUser User;
		while (getline(MyFile, Line))
		{
			User = ConvertLinetoRecordForUsers(Line);
			if (User.UserName == UserName)
			{
				MyFile.close();
				return true;
			}
		}
		MyFile.close();
	}
	return false;
}
//---------------------------------------------------------------------------------------------------
bool FindClientByAccountNumber(string AccountNumber, vector <stClient> vClients, stClient& Client)
{
	for (stClient C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}

	}
	return false;
}
bool FindUserByUserName(string UserName, vector <stUser> vUsers, stUser& User)
{
	for (stUser Us : vUsers)
	{
		if (Us.UserName == UserName)
		{
			User = Us;
			return true;
		}
	}
	return false;
}
//---------------------------------------------------------------------------------------------------
bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <stClient>& vClients)
{

	for (stClient& C : vClients)
	{

		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}

	}

	return false;

}
bool MarkUserForDeleteByUserName(string UserName, vector <stUser>& vUsers)
{

	for (stUser& User : vUsers)
	{
		if (User.UserName == UserName)
		{
			User.MarkForDelete = true;
			return true;
		}
	}
	return false;
}
//---------------------------------------------------------------------------------------------------
bool DeleteClientByAccountNumber(string AccountNumber, vector <stClient>& vClients)
{

	stClient Client;
	char Answer = 'n';

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{

		PrintClientCard(Client);

		cout << "\n\nAre you sure you want delete this client? y/n ? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
			SaveCleintsDataToFile(ClientsFileName, vClients);

			//Refresh Clients
			vClients = LoadCleintsDataFromFile(ClientsFileName);

			cout << "\n\nClient Deleted Successfully.";
			return true;
		}

	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
		return false;
	}

}
bool DeleteUserByUserName(string UserName, vector<stUser>& vUsers)
{
	stUser User;
	char Choice = 'n';
	if (UserName == "Admin")
	{
		cout << "\nYou can't Delete Admin \n";
		return false;
	}
	if (FindUserByUserName(UserName, vUsers, User))
	{
		PrintUsersCard(User);

		cout << "\nAre you sure you want to delete this user? ";
		cin >> Choice;
		if (Choice == 'Y' || Choice == 'y')
		{
			MarkUserForDeleteByUserName(UserName, vUsers);
			SaveUsersDataToFile(UsersFileName, vUsers);

			//refresh vUsers vector
			vUsers = LoadUsersDataFromFile(UsersFileName);
			cout << "\nClient Deleted Succesfully " << endl;
			return true;
		}
		else
		{
			return false;
		}

	}
	else
	{
		cout << "\nClient with Account Number (" << UserName << ") is Not Found!";
		return false;
	}

}
//---------------------------------------------------------------------------------------------------
bool UpdateClientByAccountNumber(string AccountNumber, vector <stClient>& vClients)
{

	stClient Client;
	char Answer = 'n';

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{

		PrintClientCard(Client);
		cout << "\n\nAre you sure you want update this client? y/n ? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{

			for (stClient& C : vClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = ChangeClientRecord(AccountNumber);
					break;
				}

			}

			SaveCleintsDataToFile(ClientsFileName, vClients);

			cout << "\n\nClient Updated Successfully.";
			return true;
		}

	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
		return false;
	}

}
bool UpdateUserByUserName(string UserName, vector<stUser>& vUsers)
{

	stUser User;
	char Choice = 'n';
	if (UserName == "Admin")
	{
		cout << "\nYou can't Update Admin Prevellage\n";
		return false;
	}
	if (FindUserByUserName(UserName, vUsers, User))
	{

		PrintUsersCard(User);
		cout << "\nAre you sure you want to update this user? ";
		cin >> Choice;
		if (Choice == 'Y' || Choice == 'y')
		{
			for (stUser& User : vUsers)
			{
				if (User.UserName == UserName)
				{
					User = ChangeUserRecords(UserName);
				}
			}
			//refresh and update Users data 
			vUsers = SaveUsersDataToFile(UsersFileName, vUsers);
			cout << "\nUser data updated Succesfully \n";
			return true;
		}
		else
		{
			return false;
		}


	}
	else
	{
		cout << "\nClient with Account Number (" << UserName << ") is Not Found!\n";
		return false;
	}

}
//---------------------------------------------------------------------------------------------------
bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector <stClient>& vClients)
{

	char Answer = 'n';
	cout << "\n\nAre you sure you want perfrom this transaction? y/n ? ";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y')
	{

		for (stClient& C : vClients)
		{
			if (C.AccountNumber == AccountNumber)
			{
				C.AccountBalance += Amount;
				SaveCleintsDataToFile(ClientsFileName, vClients);
				cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance << endl;

				return true;
			}

		}

	}

	return false;
}
//---------------------------------------------------------------------------------------------------
bool IsHasFullAccess(stUser User)
{
	return User.Permission == -1;
}
bool IsHasAccessToSpecifiqueOption(stUser User, enMainMenueOptions MainMenueOptions)
{
	string RevercedBinaryString = ReverseString(FromDecimalToBinary(User.Permission));
	int Counter = 0;
	for (int i = 0; i <= RevercedBinaryString.length() - 1; i++)
	{
		Counter++;
		if (RevercedBinaryString[i] == '1')
		{
			if ((enMainMenueOptions)Counter == MainMenueOptions)
				return  true;
		}

	}
	return false;
}
bool IsHasAccesse(stUser User, enMainMenueOptions MainMenueOptions)
{
	if (IsHasFullAccess(User))
	{
		return true;
	}
	else
	{
		return IsHasAccessToSpecifiqueOption(User, MainMenueOptions);
	}
	return false;
}
//---------------------------------------------------------------------------------------------------
bool IsChoiceIsYes()
{
	char Choice = 'n';
	cin >> Choice;
	return (tolower(Choice) == 'y') ? true : false;
}
//---------------------------------------------------------------------------------------------------
void PrintClientRecordLine(stClient Client)
{

	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;

}
void PrintUsersRecordLine(stUser User)
{

	cout << "| " << setw(20) << left << User.UserName;
	cout << "| " << setw(20) << left << User.Password;
	cout << "| " << setw(20) << left << User.Permission;

}
void PrintClientRecordBalanceLine(stClient Client)
{

	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.AccountBalance;

}
void PrintClientCard(stClient Client)
{
	cout << "\nThe following are the client details:\n";
	cout << "-----------------------------------";
	cout << "\nAccout Number: " << Client.AccountNumber;
	cout << "\nPin Code     : " << Client.PinCode;
	cout << "\nName         : " << Client.Name;
	cout << "\nPhone        : " << Client.Phone;
	cout << "\nAccount Balance: " << Client.AccountBalance;
	cout << "\n-----------------------------------\n";

}
void PrintUsersCard(stUser Users)
{
	cout << "\nThe following are the client details:\n";
	cout << "-----------------------------------";
	cout << "\nUserName     : " << Users.UserName;
	cout << "\nPassword     : " << Users.Password;
	cout << "\nPermission   : " << Users.Permission;
	cout << "\n-----------------------------------" << endl;

}
void AddDataLineToFile(string FileName, string  stDataLine)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);
	if (MyFile.is_open())
	{
		MyFile << stDataLine << endl;
	}
	MyFile.close();
}
void AddNewClient()
{
	AddDataLineToFile(ClientsFileName, ConvertRecordToLine(ReadNewClient()));
}
void AddNewClients()
{
	char AddMore = 'Y';
	do
	{
		//system("cls");
		cout << "Adding New Client:\n\n";
		AddNewClient();
		cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
		cin >> AddMore;

	} while (toupper(AddMore) == 'Y');

}
//---------------------------------------------------------------------------------------------------
void ShowAllClientsScreen()
{


	vector <stClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	if (vClients.size() == 0)
		cout << "\t\t\t\tNo Clients Available In the System!";
	else

		for (stClient Client : vClients)
		{

			PrintClientRecordLine(Client);
			cout << endl;
		}

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

}
void ShowTotalBalances()
{

	vector <stClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

	cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	double TotalBalances = 0;

	if (vClients.size() == 0)
		cout << "\t\t\t\tNo Clients Available In the System!";
	else
	{

		for (stClient Client : vClients)
		{

			PrintClientRecordBalanceLine(Client);
			TotalBalances += Client.AccountBalance;

			cout << endl;
		}

	}



	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "\t\t\t\t\t   Total Balances = " << TotalBalances << endl;

}
void ShowDeleteClientScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tDelete Client Screen";
	cout << "\n-----------------------------------\n";
	vector <stClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	DeleteClientByAccountNumber(AccountNumber, vClients);

}
void ShowUpdateClientScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tUpdate Client Info Screen";
	cout << "\n-----------------------------------\n";

	vector <stClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	UpdateClientByAccountNumber(AccountNumber, vClients);

}
void ShowAddNewClientsScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tAdd New Clients Screen";
	cout << "\n-----------------------------------\n";

	AddNewClients();

}
void ShowFindClientScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tFind Client Screen";
	cout << "\n-----------------------------------\n";

	vector <stClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	stClient Client;
	string AccountNumber = ReadClientAccountNumber();
	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
		PrintClientCard(Client);
	else
		cout << "\nClient with Account Number[" << AccountNumber << "] is not found!" << endl;

}
void ShowEndScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tProgram Ends :-)";
	cout << "\n-----------------------------------\n";

}
void ShowDepositScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tDeposit Screen";
	cout << "\n-----------------------------------\n";


	stClient Client;

	vector <stClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();


	while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
		AccountNumber = ReadClientAccountNumber();
	}


	PrintClientCard(Client);

	double Amount = 0;
	cout << "\nPlease enter deposit amount? ";
	cin >> Amount;

	DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);

}
void ShowWithDrawScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tWithdraw Screen";
	cout << "\n-----------------------------------\n";

	stClient Client;

	vector <stClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();


	while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
		AccountNumber = ReadClientAccountNumber();
	}

	PrintClientCard(Client);

	double Amount = 0;
	cout << "\nPlease enter withdraw amount? ";
	cin >> Amount;

	//Validate that the amount does not exceeds the balance
	while (Amount > Client.AccountBalance)
	{
		cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
		cout << "Please enter another amount? ";
		cin >> Amount;
	}

	DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients);

}
void ShowTotalBalancesScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tWithdraw Screen";
	cout << "\n-----------------------------------\n";
	ShowTotalBalances();
}
//---------------------------------------------------------------------------------------------------
void GoBackToMainMenue(stUser User)
{
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	ShowMainMenue(User);

}
void GoBackToManageUsersMenueScreen(stUser User)
{
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	ShowManageUsersMenueScreen(User);

}
void GoBackToTransactionsMenue(stUser User)
{
	cout << "\n\nPress any key to go back to Transactions Menue...";
	system("pause>0");
	ShowTransactionsMenue(User);

}
//---------------------------------------------------------------------------------------------------
void PerformManageUserMenueOption(enManageUsersOptions ManageUsers, stUser User)
{
	switch (ManageUsers)
	{

	case enManageUsersOptions::eListUsers:
	{
		system("cls");
		ShowListUsersScreen();
		GoBackToManageUsersMenueScreen(User);
		break;

	}
	case enManageUsersOptions::eAddNewUser:
	{

		system("cls");
		ShowAddNewUsersScreen();
		GoBackToManageUsersMenueScreen(User);
		break;
	}
	case enManageUsersOptions::eDeleteUser:
	{
		system("cls");
		ShowDeleteUserScreen(User);
		GoBackToManageUsersMenueScreen(User);
		break;
	}
	case enManageUsersOptions::eUpdateUser:
	{
		system("cls");
		ShowUpdateUserScreen();
		GoBackToManageUsersMenueScreen(User);
		break;

	}
	case enManageUsersOptions::eFindUser:
	{
		system("cls");
		ShowFindUserScreen(User);
		GoBackToManageUsersMenueScreen(User);
		break;
	}
	case enManageUsersOptions::eMainMenue:
	{

		system("cls");
		GoBackToMainMenue(User);
		break;
	}


	}


}
void PerfromTranactionsMenueOption(enTransactionsMenueOptions TransactionMenueOption, stUser User)
{
	switch (TransactionMenueOption)
	{
	case enTransactionsMenueOptions::eDeposit:
	{
		system("cls");
		ShowDepositScreen();
		GoBackToTransactionsMenue(User);
		break;
	}

	case enTransactionsMenueOptions::eWithdraw:
	{
		system("cls");
		ShowWithDrawScreen();
		GoBackToTransactionsMenue(User);
		break;
	}


	case enTransactionsMenueOptions::eShowTotalBalance:
	{
		system("cls");
		ShowTotalBalances();
		GoBackToTransactionsMenue(User);
		break;
	}


	case enTransactionsMenueOptions::eShowMainMenue:
	{
		system("cls");
		ShowMainMenue(User);

	}

	}

}
void PerfromMainMenueOption(enMainMenueOptions MainMenueOption, stUser& User)
{


	switch (MainMenueOption)
	{
	case enMainMenueOptions::eListClients:
	{
		system("cls");
		if (IsHasAccesse(User, enMainMenueOptions::eListClients))
			ShowAllClientsScreen();
		else
			cout << "\nAccesse denied" << endl;
		GoBackToMainMenue(User);
		break;
	}
	case enMainMenueOptions::eAddNewClient:
		system("cls");
		if (IsHasAccesse(User, enMainMenueOptions::eAddNewClient))
			ShowAddNewClientsScreen();
		else
			cout << "\nAccesse denied" << endl;
		GoBackToMainMenue(User);
		break;

	case enMainMenueOptions::eDeleteClient:
		system("cls");
		if (IsHasAccesse(User, enMainMenueOptions::eDeleteClient))
			ShowDeleteClientScreen();
		else
			cout << "\nAccesse denied" << endl;

		GoBackToMainMenue(User);
		break;

	case enMainMenueOptions::eUpdateClient:
		system("cls");
		if (IsHasAccesse(User, enMainMenueOptions::eUpdateClient))
			ShowUpdateClientScreen();
		else
			cout << "\nAccesse denied" << endl;
		GoBackToMainMenue(User);
		break;

	case enMainMenueOptions::eFindClient:
		system("cls");
		if (IsHasAccesse(User, enMainMenueOptions::eFindClient))
			ShowFindClientScreen();
		else
			cout << "\nAccesse denied" << endl;
		GoBackToMainMenue(User);
		break;

	case enMainMenueOptions::eTransactions:
		system("cls");
		if (IsHasAccesse(User, enMainMenueOptions::eTransactions))
			ShowTransactionsMenue(User);
		else
			cout << "\nAccesse denied" << endl;
		GoBackToMainMenue(User);
		break;

	case enMainMenueOptions::eManageUsers:
		system("cls");
		if (IsHasAccesse(User, enMainMenueOptions::eManageUsers))
			ShowManageUsersMenueScreen(User);
		else
			cout << "\nAccesse denied" << endl;
		GoBackToMainMenue(User);
		break;
	case enMainMenueOptions::eLogOut:
		system("cls");
		ShowLogInScreen();
		break;
	}

}
//---------------------------------------------------------------------------------------------------
void ShowListUsersScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tList users Screen";
	cout << "\n-----------------------------------\n";

	vector <stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
	ListUserScreen(vUsers);

}
void ShowAddNewUsersScreen()
{

	cout << "\n-----------------------------------\n";
	cout << "\tAdd New Screen";
	cout << "\n-----------------------------------\n";
	AddUsers();

}
void ShowFindUserScreen(stUser User)
{
	cout << "\n-----------------------------------\n";
	cout << "\tFind User Screen";
	cout << "\n-----------------------------------\n";
	FindUser();
	GoBackToManageUsersMenueScreen(User);


}
void ShowDeleteUserScreen(stUser User)
{

	cout << "\n-----------------------------------\n";
	cout << "\tDelete User Screen";
	cout << "\n-----------------------------------\n";
	vector<stUser>vUsers = LoadUsersDataFromFile(UsersFileName);
	string UserName = ReadUserUserName();
	if (UserName == "Admin")
	{
		cout << "\nYou can't delete Admin" << endl;
	}
	else
	{
		DeleteUserByUserName(UserName, vUsers);
		GoBackToManageUsersMenueScreen(User);
	}
}
void ShowUpdateUserScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tDelete User Screen";
	cout << "\n-----------------------------------\n";
	vector<stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
	string UserName = ReadUserUserName();
	UpdateUserByUserName(UserName, vUsers);

}
void ShowTransactionsMenue(stUser User)
{
	system("cls");
	cout << "===========================================\n";
	cout << "\t\tTransactions Menue Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balances.\n";
	cout << "\t[4] Main Menue.\n";
	cout << "===========================================\n";
	PerfromTranactionsMenueOption((enTransactionsMenueOptions)ReadTransactionsMenueOption(), User);
}
void  ShowManageUsersMenueScreen(stUser User)
{

	system("cls");
	cout << "\n-----------------------------------\n";
	cout << "\tShow Manage Users Menue Screen";
	cout << "\n-----------------------------------\n";
	cout << "\t[1] Show List Users.\n";
	cout << "\t[2] Add New Users.\n";
	cout << "\t[3] Delete Users.\n";
	cout << "\t[4] Update Users.\n";
	cout << "\t[5] Find Users.\n";
	cout << "\t[6] Main Menue.\n";
	cout << "===========================================" << endl;
	PerformManageUserMenueOption((enManageUsersOptions)ReadManageMenueOption(), User);


}
//---------------------------------------------------------------------------------------------------
void ListUserScreen(vector<stUser>vUsers)
{
	cout << "\n\t\t\t\t\tUsers List (" << vUsers.size() << ") Users(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(20) << "User Name";
	cout << "| " << left << setw(20) << "Password";
	cout << "| " << left << setw(20) << "Permission";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	if (vUsers.size() == 0)
		cout << "\t\t\t\tNo Users Available In the System!";
	else
	{
		for (stUser User : vUsers)
		{
			PrintUsersRecordLine(User);
			cout << endl;
		}
	}
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

}
stUser AddNewUser()
{
	stUser User;
	cout << "\n Adding New User \n";
	cout << "\nplease enter User name ? ";
	getline(cin >> ws, User.UserName);

	while (IsUserExistByUsername(User.UserName, UsersFileName))
	{
		cout << "User with  [" << User.UserName << "] Username Is already exist. Enter another username ? ";
		getline(cin, User.UserName);
	}
	cout << "\nplease enter Password ? ";
	getline(cin, User.Password);

	User.Permission = ReadPermssion(User);
	return User;
}
void AddUser()
{
	AddDataLineToFile(UsersFileName, ConvertRecordToLine(AddNewUser()));
}
void AddUsers()
{
	char Choice = 'n';
	do
	{

		AddUser();
		cout << "\you want to add New User (answer with  Y/N) ? ";
		cin >> Choice;

	} while (tolower(Choice) == 'y');
}
void FindUser()
{
	stUser User;
	cout << "\n Please enter username? ";
	getline(cin >> ws, User.UserName);
	vector<stUser>vUsers = LoadUsersDataFromFile(UsersFileName);

	if (FindUserByUserName(User.UserName, vUsers, User))
		PrintUsersCard(User);
	else
		cout << "User [" << User.UserName << "] is not exist" << endl;



}
void ShowMainMenue(stUser User)
{
	system("cls");
	cout << "===========================================\n";
	cout << "\t\tMain Menue Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transactions.\n";
	cout << "\t[7] Manage Users.\n";
	cout << "\t[8] Log out.\n";
	cout << "===========================================\n";
	PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption(), User);
}
//---------------------------------------------------------------------------------------------------
stUser LogIn()
{
	string UserNameInput = "";
	string PasswordInput = "";
	cout << "\nPlease Enter UserName ? ";
	getline(cin >> ws, UserNameInput);
	cout << "\n Please Enter A Password ? ";
	getline(cin, PasswordInput);
	vector<stUser>vUsers;
	vUsers = LoadUsersDataFromFile(UsersFileName);
	stUser User;
	if (FindUserByUserName(UserNameInput, vUsers, User) && User.Password == PasswordInput)
	{
		return User;
	}
	else
	{
		do
		{
			cout << "\nInvalid Username/Password\n";
			cout << "\nPlease Enter UserName ? ";
			getline(cin >> ws, UserNameInput);
			cout << "\n Please Enter A Password ? ";
			getline(cin, PasswordInput);
		} while (!FindUserByUserName(UserNameInput, vUsers, User) || User.Password != PasswordInput);

	}
	return User;
}
void ShowLogInScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tLogIn Screen";
	cout << "\n-----------------------------------\n";
	stUser User = LogIn();
	ShowMainMenue(User);

}
//---------------------------------------------------------------------------------------------------

int main()
{
	ShowLogInScreen();

	system("pause>0");
	return 0;
}