#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

const int PermShowList = 1;
const int PermAddClient = 2;
const int PermDeleteClient = 4;
const int PermUpdateClient = 8;
const int PermFindClient = 16;
const int PermTransactions = 32;
const int permManageUsers = 64;
const int PermAll = -1;

const string ClientsFileName = "Clients.txt";
const string UsersFileName = "Users.txt";
int CurrentUserPermission = 0;

void ShowMainMenu();
void ShowTransctionMenuScreen();
void ShowLoginScreen();
void ShowManageUsersMenuScreen();

struct stClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelet = false;
};

struct stUser
{
    string Name;
    string Password;
    int Permission;
    bool MarkForDelete = false;
};

bool FindClientByAccountNumber(string AccountNumber , vector <stClient>& vClients , stClient &Client)
{
    for (stClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

vector <string> SplitString(string S1, string Seperator)
{
    vector <string> vString;
    int Pos;
    string sWord;

    while ((Pos = S1.find(Seperator)) != S1.npos)
    {
        sWord = S1.substr(0, Pos);
        if (sWord != "")
        {
            vString.push_back(sWord);
        }
        S1.erase(0, Pos + Seperator.length());
    }

    if (S1 != "")
    {
        vString.push_back(S1);
    }

    return vString;
}

stClient ConvertLineToRecord(string Line, string Seperator = "#//#")
{
    vector <string> vClientData = SplitString(Line, Seperator);
    stClient Client;

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);

    return Client;
}

bool ClientExistByAccountNumber(string AccountNumber)
{
    fstream MyFile;
    stClient Client;
    string Line;

    MyFile.open(ClientsFileName, ios::in);

    if (MyFile.is_open())
    {
        while (getline(MyFile, Line))
        {
            Client = ConvertLineToRecord(Line);
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

stClient ReadNewClient()
{
    stClient NewClient;

    cout << "Adding New Client:\n";

    cout << "\nEnter Account Number ? ";
    getline(cin >> ws, NewClient.AccountNumber);

    while(ClientExistByAccountNumber(NewClient.AccountNumber ))
    {
        cout << "\nClient with [" << NewClient.AccountNumber << "] already exists, Enter another Account Number? ";
        getline(cin, NewClient.AccountNumber);
    }

    cout << "Enter PinCode? ";
    getline( cin, NewClient.PinCode);

    cout << "Enter Name ? ";
    getline(cin , NewClient.Name);

    cout << "Enter Phone? ";
    getline(cin , NewClient.Phone);

    cout << "Enter AccountBalance? ";
    cin >> NewClient.AccountBalance;

    return NewClient;
}

string ReadClientAccountNumber()
{
    string AccountNumber = "";

    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;

    return AccountNumber;
}

string ReadUserName()
{
    string UserName;
    cout << "Enter UserName? ";
    getline(cin >> ws, UserName);
    return UserName;
}

string ReadUserPassword()
{
    string Password;
    cout << "Enter Password? ";
    getline(cin >> ws, Password);
    return Password;
}

string ConvertRecordToLine(stClient Client , string Seperator = "#//#")
{
    string Line;

    Line += Client.AccountNumber + Seperator;
    Line += Client.PinCode + Seperator;
    Line += Client.Name + Seperator;
    Line += Client.Phone + Seperator;
    Line += to_string(Client.AccountBalance);

    return Line;
}

stUser ConvertLineToUserRecord(string Line)
{
    vector <string> vUserDate = SplitString(Line, "#//#");
    stUser UserDate;
    UserDate.Name = vUserDate[0];
    UserDate.Password = vUserDate[1];
    UserDate.Permission = stoi(vUserDate[2]);
    return UserDate;
}

void SaveClientsDataToFile(string FileName, vector <stClient>& vClients, bool IsAppend = false)
{
    fstream MyFile;

    if (IsAppend)
    {
        MyFile.open(FileName, ios::out | ios::app);
    }
    else
    {
        MyFile.open(FileName, ios::out);
    }
   
    string Line;

    if (MyFile.is_open())
    {
        for (stClient Client : vClients)
        {
            if (!Client.MarkForDelet)
            {
                Line = ConvertRecordToLine(Client);

                MyFile << Line << endl;
            }
        }

        MyFile.close();
    }
}

vector <stClient> LoadDataLineFromFile(string FileName)
{
    fstream MyFile;

    MyFile.open(FileName, ios::in);

    string Line;
    stClient ClientRecord;
    vector <stClient> vClients;

    if(MyFile.is_open())
    {
        while (getline(MyFile, Line))
        {
            if (Line != "")
            {
                ClientRecord = ConvertLineToRecord(Line);
                vClients.push_back(ClientRecord);
            }
            
        }

        MyFile.close();
    }

    return vClients;
}

void PrintClientRecordLine(stClient Client)
{
    cout << "| " << left << setw(15) << Client.AccountNumber;
    cout << "| " << left << setw(10) << Client.PinCode;
    cout << "| " << left << setw(40) << Client.Name;
    cout << "| " << left << setw(12) << Client.Phone;
    cout << "| " << left << setw(12) << Client.AccountBalance << endl;
}

void PrintUserRecordLine(stUser User)
{
    cout << "| " << left << setw(30) << User.Name;
    cout << "| " << left << setw(20) << User.Password;
    cout << "| " << left << setw(20) << User.Permission << endl;
}

void ShowAllClientListScreen()
{
    vector <stClient> vClients = LoadDataLineFromFile(ClientsFileName);
   
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client (s).\n";
    cout << "_____________________________________________________________________________________________________________\n\n";
    cout << "| " <<left << setw(15) << "Account Number";
    cout << "| " <<left << setw(10) << "PinCode";
    cout << "| " <<left << setw(40) << "Client Name";
    cout << "| " <<left << setw(12) << "Phone";
    cout << "| " <<left << setw(12) << "Balance";
    cout <<"\n_____________________________________________________________________________________________________________\n\n";
  
    if (vClients.size() == 0)
    {
        cout << "\t\t\t\tNo Clients Available In the System!";
    }

    for (stClient& Client : vClients)
    {
        PrintClientRecordLine(Client);
    }
    cout << "\n_____________________________________________________________________________________________________________\n\n";
}

void AddDataLineToFile(string ClientsFileName, string Line)
{
    fstream MyFile;

    MyFile.open(ClientsFileName, ios::out | ios::app);
    
    if (MyFile.is_open())
    {
        MyFile << Line << endl;

        MyFile.close();
    }
}

void AddNewClient()
{
    stClient NewClient = ReadNewClient();
    AddDataLineToFile(ClientsFileName, ConvertRecordToLine(NewClient));
}

void AddNewClients()
{
    char AddMore = 'n';

    do
    {
        AddNewClient();

        cout << "\nClient Added Successfully , do you want to add more clients? Y/N? ";
        cin >> AddMore;

    } while (AddMore == 'Y' || AddMore == 'y');
}

void ShowAddNewClientScreen()
{
    cout << "------------------------------------\n";
    cout << "\tAdd New Clients Screen\n";
    cout << "------------------------------------\n";
    
    AddNewClients();
}

void PrintClientCard(stClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "------------------------------------\n";
    cout << "Account Number: " << Client.AccountNumber;
    cout << "\nPin Code      : " << Client.PinCode;
    cout << "\nName          : " << Client.Name;
    cout << "\nPhone         : " << Client.Phone;
    cout << "\nAccount Balance : " << Client.AccountBalance << endl;
    cout << "------------------------------------\n";
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber , vector <stClient>& vClients)
{
    for (stClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelet = true;
            return true;
        }
    }
    return false;
}

bool DeleteClientByAccountNumber(string AccountNumber, vector <stClient>& vClients)
{
    stClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);

        cout << "\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;

        if (tolower(Answer) == 'y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);

            SaveClientsDataToFile(ClientsFileName, vClients, false);

            vClients = LoadDataLineFromFile(ClientsFileName);

            cout << "\nClient Deleted Successfully.\n";
        }

        return true;
    }
    else
    {
        cout << "Client with Account Number (" << AccountNumber << ") is Not Found!\n";
        return false;
    }
}

void ShowDeleteClientScreen()
{
    cout << "------------------------------------\n";
    cout << "\tDelete Clients Screen\n";
    cout << "------------------------------------\n";

    vector <stClient> vClients = LoadDataLineFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    DeleteClientByAccountNumber(AccountNumber, vClients);
}

stClient ChangeClientRecord(string AccountNumber)
{
    stClient Client;

    Client.AccountNumber = AccountNumber;

    cout << "\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name ? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;
}

bool UpdateClientByAccountNumber(string AccountNumber, vector <stClient>& vClients)
{
    stClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);

        cout << "\nAre you sure you want update this client? y/n ? ";
        cin >> Answer;

        if (tolower(Answer) == 'y')
        {
            for (stClient& Client : vClients)
            {
                if (Client.AccountNumber == AccountNumber)
                {
                    Client = ChangeClientRecord(AccountNumber);
                    break;
                }
            }
            SaveClientsDataToFile(ClientsFileName, vClients, false);

            cout << "\nClient updated Successfully.\n";
        }

        return true;
    }
    else
    {
        cout << "Client with Account Number (" << AccountNumber << ") is Not Found!\n";
        return false;
    }
}

void ShowUpdateClientScreen()
{
    cout << "------------------------------------\n";
    cout << "\tUpdate Client Info Screen\n";
    cout << "------------------------------------\n";

    vector <stClient> vClients = LoadDataLineFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
  
    UpdateClientByAccountNumber(AccountNumber, vClients);
}

void ShowFindClientScreen()
{
    cout << "------------------------------------\n";
    cout << "\tFind Client Screen\n";
    cout << "------------------------------------\n";

    vector <stClient> vClients = LoadDataLineFromFile(ClientsFileName);
    stClient Client;
    string AccountNumber = ReadClientAccountNumber();

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
        PrintClientCard(Client);
    else
        cout << "Client with Account Number (" << AccountNumber << ") is Not Found!\n";
}

void ShowEndScreen()
{
    cout << "------------------------------------\n";
    cout << "\tProgram Ends :-) \n";
    cout << "------------------------------------\n";
}

enum enMainMenueOptions { eListClients = 1, eAddNewClient = 2, eDeleteClient = 3, eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6, eManageUsers = 7 , eLogout = 8 };

enum enTransactionsMenueOptions { eDeposit = 1, eWithdraw = 2 , eTotalBalances = 3 , eMainMenu = 4};

enum enManageUsersMenueOptions {eListUsers = 1 , eAddNewUser = 2 , eDeleteUser = 3 , eUpdateUser = 4 , eFindUser = 5 , eShowMainMenu = 6};

void GoBackToMainMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause > nul");
    ShowMainMenu();
}

short ReadMenuOption(short Limit)
{
    short Choice = 0;

    do {
        cout << "Choose what do you want to do? [1 to " << Limit << " ] ? ";
        cin >> Choice;
    } while (Choice < 1 || Choice > Limit);

    return Choice;
}

bool DepositBalanceToClientByAccountNumber(string AccountNumber , double Amount , vector <stClient> &vClients)
{

    char Answer = 'n';

    cout << "\n\nAre you sure you want perfrom this transaction? y/n ? ";
    cin >> Answer;

    if (tolower(Answer) == 'y')
    {
        for (stClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Amount;
                SaveClientsDataToFile(ClientsFileName, vClients);
                cout << "\nDone Sucessfully, New Balance is :" << C.AccountBalance << endl;
                return true;
            }
        }
    }

    return false;
}

void ShowDepositScreen()
{
    cout << "------------------------------------\n";
    cout << "\tDeposit Screen\n";
    cout << "------------------------------------\n";

    vector <stClient> vClients = LoadDataLineFromFile(ClientsFileName);
    stClient Client;
    string AccountNumber = ReadClientAccountNumber();

    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "Client with Account Number (" << AccountNumber << ") is Not Found!\n";
        AccountNumber = ReadClientAccountNumber();
    }

    PrintClientCard(Client);

    double Amount = 0;

    cout << "\nPlease enter withdraw amount? ";
    cin >> Amount;

    DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);
}

void ShowWithdrawScreen()
{
    cout << "------------------------------------\n";
    cout << "\tWithdraw Screen\n";
    cout << "------------------------------------\n";

    vector <stClient> vClients = LoadDataLineFromFile(ClientsFileName);
    stClient Client;
    string AccountNumber = ReadClientAccountNumber();

    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "Client with Account Number (" << AccountNumber << ") is Not Found!\n";
        AccountNumber = ReadClientAccountNumber();
    }

        PrintClientCard(Client);

        double Amount = 0;

        cout << "\nPlease enter withdraw amount? ";
        cin >> Amount;

        while (Amount > Client.AccountBalance)
        {
            cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
            cout << "Please enter another amount? ";
            cin >> Amount;
        }

        DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients); 
}

void PrintClientRecordBalanceLine(stClient Client)
{
    cout << "| " << left << setw(15) << Client.AccountNumber;
    cout << "| " << left << setw(40) << Client.Name;
    cout << "| " << left << setw(10) << Client.AccountBalance << endl;
}

void ShowTotalBalances()
{
    vector <stClient> vClients = LoadDataLineFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client (s).\n";
    cout << "_____________________________________________________________________________________________________________\n\n";
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_____________________________________________________________________________________________________________\n\n";

    if (vClients.size() == 0)
    {
        cout << "\t\t\t\tNo Clients Available In the System!";
    }

    double TotalBalances = 0;

    for (stClient& Client : vClients)
    {
        PrintClientRecordBalanceLine(Client);
        TotalBalances += Client.AccountBalance;
    }
    cout << "\n_____________________________________________________________________________________________________________\n\n";

    cout << "\n\t\t\t\t\t\tTotal Balances = " << TotalBalances << endl;
}

void ShowTotalBalancesScreen()
{
    ShowTotalBalances();
}

void GoBackToTransactionMenu()
{
    cout << "\n\nPress any key to go back to Transactions Menue...";
    system("pause > nul");
    ShowTransctionMenuScreen();
}

void PerformTransactionMenueOpetion(enTransactionsMenueOptions TransactionMenuOption)
{
    switch (TransactionMenuOption)
    {
    case(enTransactionsMenueOptions::eDeposit):
        system("cls");
        ShowDepositScreen();
        GoBackToTransactionMenu();
        break;
    case(enTransactionsMenueOptions::eWithdraw):
        system("cls");
        ShowWithdrawScreen();
        GoBackToTransactionMenu();
        break;
    case(enTransactionsMenueOptions::eTotalBalances):
        system("cls");
        ShowTotalBalancesScreen();
        GoBackToTransactionMenu();
        break;
    case(enTransactionsMenueOptions::eMainMenu):
        ShowMainMenu();
        break;
    }
}

void ShowTransctionMenuScreen()
{
    system("cls");
    cout << "===================================================\n";
    cout << "\t\tTransaction Menue Screen\n";
    cout << "===================================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] TotalBalances.\n";
    cout << "\t[4] MainMenu.\n";
    cout << "===================================================\n";

    PerformTransactionMenueOpetion((enTransactionsMenueOptions)ReadMenuOption(4));
}

vector <stUser> LoadUserDateLineFromFile()
{
    vector <stUser> vUsersDate;
    fstream MyFile;

    MyFile.open(UsersFileName, ios::in);

    string Line;
    stUser UserRecord;

    if (MyFile.is_open())
    {
        while(getline(MyFile, Line))
        {
            if (Line != "")
            {
                UserRecord = ConvertLineToUserRecord(Line);
                vUsersDate.push_back(UserRecord);
            }
        }

        MyFile.close();
    }

    return vUsersDate;
}

void GoBackToManageUsersMenu()
{
    cout << "\n\nPress any key to go back to Manage User  Menue...";
    system("pause > nul");
    ShowManageUsersMenuScreen();
}

void ShowListUsersScreen()
{
    vector <stUser> vUsers = LoadUserDateLineFromFile();

    cout << "\n\t\t\t\t\tUsers List (" << vUsers.size() << ") User (s).\n";
    cout << "_____________________________________________________________________________________________________________\n\n";
    cout << "| " << left << setw(30) << "User Name";
    cout << "| " << left << setw(20) << "Password";
    cout << "| " << left << setw(20) << "Permission";
    cout << "\n_____________________________________________________________________________________________________________\n\n";

    for (stUser& User  : vUsers)
    {
        PrintUserRecordLine(User);
    }
    cout << "\n_____________________________________________________________________________________________________________\n\n";
}

bool UserExistsByUserName(string UserName)
{
    vector <stUser> vUsers = LoadUserDateLineFromFile();

    for (stUser& User : vUsers)
    {
        if (User.Name == UserName)
        {
            return true;
        }
    }
    
    return false;
}

short ReadPermission()
{
    int Permission = 0;
    char Choice;

    cout << "\nDo you want to give full access? y/n? ";
    cin >> Choice;
    if (tolower(Choice) == 'y')
     return Permission |= PermAll;

    cout << "\nDo you want to give access to : ";
    cout << "\n\nShow Client List? y/n? ";
    cin >> Choice;
    if (tolower(Choice) == 'y')
        Permission |= PermShowList;

    cout << "\n\nAdd New Client? y/n? ";
    cin >> Choice;
    if (tolower(Choice) == 'y')
        Permission |= PermAddClient;

    cout << "\n\nDelete Client? y/n? ";
    cin >> Choice;
    if (tolower(Choice) == 'y')
        Permission |= PermDeleteClient;

    cout << "\n\nUpdate Client? y/n? ";
    cin >> Choice;
    if (tolower(Choice) == 'y')
        Permission |= PermUpdateClient;

    cout << "\n\nFind Client? y/n? ";
    cin >> Choice;
    if (tolower(Choice) == 'y')
        Permission |= PermFindClient;

    cout << "\n\nTransactions? y/n? ";
    cin >> Choice;
    if (tolower(Choice) == 'y')
        Permission |= PermTransactions;

    cout << "\n\nManage Users? y/n? ";
    cin >> Choice;
    if (tolower(Choice) == 'y')
        Permission |= permManageUsers;

    return Permission;
}

stUser ReadNewUser()
{
    stUser User;
    cout << "Adding New User:\n";

    cout << "\nEnter UserName? ";
    getline(cin >> ws, User.Name);

    while (UserExistsByUserName(User.Name))
    {
        cout << "\nUser with [" << User.Name << "] already exists,Enter another user name ? ";
        getline(cin, User.Name);
    }

    cout << "\nEnter Password? ";
    getline(cin, User.Password);

    User.Permission = ReadPermission();

    return User;
}

string ConverUserRecordToLine(stUser NewUser , string Seperator = "#//#")
{
    string Line = NewUser.Name + Seperator + NewUser.Password + Seperator + to_string(NewUser.Permission);
    return Line;
}

void LoadDateUserToFile(stUser User)
{
    fstream MyFile;
    string Line = ConverUserRecordToLine(User);

    MyFile.open(UsersFileName , ios::out | ios::app);

    if (MyFile.is_open())
    {
        MyFile << Line << endl;
        MyFile.close();
    }

}

void ShowAddNewUserScreen()
{
    cout << "------------------------------------\n";
    cout << "\tAdd New User Screen\n";
    cout << "------------------------------------\n";

    char Answer = 'n';

    do
    {
        stUser NewUser = ReadNewUser();
        LoadDateUserToFile(NewUser);
        cout << "\nUser Addd Successfully , do you want to add more Users? y/n? ";
        cin >> Answer; 
    } while (tolower(Answer) == 'y');
}

void PrintUserRecord(stUser User)
{
    cout << "\nThe following are the user details:\n";
    cout << "------------------------------------\n";
    cout << "UserName      : " << User.Name;
    cout << "\nPassword    : " << User.Password;
    cout << "\nPermissions : " << User.Permission;
    cout << "\n------------------------------------\n";
}

void MarkUserForDeleteByUserName(string& UserName, vector <stUser> &Users)
{
    for (stUser& User : Users)
    {
        if (User.Name == UserName)
        {
            User.MarkForDelete = true;
        }
    }
}

void SaveUsersDateToFile(vector <stUser> Users)
{
    fstream MyFile;

    MyFile.open(UsersFileName, ios::out);

    if (MyFile.is_open())
    {
        string Line;

        for (stUser& User : Users)
        {
            if (!User.MarkForDelete == true)
            {
                Line = ConverUserRecordToLine(User);
                MyFile << Line << endl;
            }
        }

        MyFile.close();
    }
}

void DeleteUserbyUserName(string UserName , vector <stUser> Users)
{
    char Answer = 'n';

    cout << "\nAre you sure you want to delete this user? y/n? ";
    cin >> Answer;

    if (tolower(Answer) == 'y')
    {
        MarkUserForDeleteByUserName(UserName, Users);
        SaveUsersDateToFile(Users);
        Users = LoadUserDateLineFromFile();
    }
}

void ShowDeleteUserScreen()
{
    cout << "------------------------------------\n";
    cout << "\tDelete Users Screen\n";
    cout << "------------------------------------\n";

    string UserName = ReadUserName();

    if (UserName == "Admin")
    {
        cout << "\nYou can not delete this user.";
        return;
    }

    vector <stUser> Users = LoadUserDateLineFromFile();

    if (UserExistsByUserName(UserName))
    {
        for (stUser& User : Users)
        {
            if (User.Name == UserName)
            {
                PrintUserRecord(User);
                DeleteUserbyUserName(UserName , Users);
                cout << "\nUsers Delete Sucessfully";
                break;
            }
        }
    }
    else
    {
        cout << "\nUser with user name (" << UserName << ") is Not found!";
    }
}

void UpdateUserbyUserName(string UserName , vector <stUser> &Users)
{
    char Answer = 'n';

        cout << "\nAre you sure you want to update this user ? y/n ? ";
        cin >> Answer;
        if (tolower(Answer) == 'y')
        {
            for (stUser& User : Users)
            {
                if (User.Name == UserName)
                {
                    User.Password = ReadUserPassword();
                    User.Permission = ReadPermission();
                    SaveUsersDateToFile(Users);
                    cout << "\nUser Updated Sucessfully";
                    break;
                }
            }
        }
}

void ShowUpdateUserScreen()
{
    cout << "------------------------------------\n";
    cout << "\tUpdate Users Screen\n";
    cout << "------------------------------------\n";

    string UserName = ReadUserName();
    vector <stUser> Users = LoadUserDateLineFromFile();

    if (UserExistsByUserName(UserName))
    {
        for (stUser& User : Users)
        {
            if (User.Name == UserName)
            {
                PrintUserRecord(User);
                UpdateUserbyUserName(UserName, Users);
                break;
            }
        }
    }
    else
    {
        cout << "\nUser with user name (" << UserName << ") is Not found!";
    }
}

void ShowFindUserScreen()
{
    cout << "------------------------------------\n";
    cout << "\tFind Users Screen\n";
    cout << "------------------------------------\n";

    string UserName = ReadUserName();
    vector <stUser> Users = LoadUserDateLineFromFile();

    if (UserExistsByUserName(UserName))
    {
        for (stUser& User : Users)
        {
            if (User.Name == UserName)
            {
                PrintUserRecord(User);
                break;
            }
        }
    }
    else
    {
        cout << "\nUser with user name (" << UserName << ") is Not found!";
    }
}

void PerformMangeUsersMenueOpetion(enManageUsersMenueOptions MangeUsersMenuOption)
{
    switch (MangeUsersMenuOption)
    {
    case(enManageUsersMenueOptions::eListUsers):
        system("cls");
        ShowListUsersScreen();
        GoBackToManageUsersMenu();
        break;
    case(enManageUsersMenueOptions::eAddNewUser):
        system("cls");
        ShowAddNewUserScreen();
        GoBackToManageUsersMenu();
        break;
    case(enManageUsersMenueOptions::eDeleteUser):
        system("cls");
        ShowDeleteUserScreen();
        GoBackToManageUsersMenu();
        break;
    case(enManageUsersMenueOptions::eUpdateUser):
        system("cls");
        ShowUpdateUserScreen();
        GoBackToManageUsersMenu();
        break;
    case(enManageUsersMenueOptions::eFindUser):
        system("cls");
        ShowFindUserScreen();
        GoBackToManageUsersMenu();
        break;
    case(enManageUsersMenueOptions::eShowMainMenu):
        system("cls");
        ShowMainMenu();
        break;
    }
}

void ShowManageUsersMenuScreen()
{
    system("cls");
    cout << "===================================================\n";
    cout << "\t\tManage Users Menue Screen\n";
    cout << "===================================================\n";
    cout << "\t[1] List Users.\n";
    cout << "\t[2] Add New User.\n";
    cout << "\t[3] Delete User.\n";
    cout << "\t[4] Update User.\n";
    cout << "\t[5] Find User.\n";
    cout << "\t[6] Main Menue.\n";
    cout << "===================================================\n";

    PerformMangeUsersMenueOpetion((enManageUsersMenueOptions)ReadMenuOption(6));
}

void ShowAccessDeniedScreen()
{
    cout << "------------------------------------\n";
    cout << "\tAccess denied :-) \n";
    cout << "------------------------------------\n";
}

void PerformMainMenueOpetion(enMainMenueOptions MainMenuOption)
{
    switch (MainMenuOption)
    {
    case(enMainMenueOptions::eListClients):
        system("cls");
        if (CurrentUserPermission & PermShowList)
            ShowAllClientListScreen();
        else
            ShowAccessDeniedScreen();
        GoBackToMainMenue();
        break;
    case(enMainMenueOptions::eAddNewClient):
        system("cls");
        if (CurrentUserPermission & PermAddClient)
            ShowAddNewClientScreen();
        else
            ShowAccessDeniedScreen();

        GoBackToMainMenue();
        break;
    case(enMainMenueOptions::eDeleteClient):
        system("cls");
        if (CurrentUserPermission & PermDeleteClient)
            ShowDeleteClientScreen();
        else
            ShowAccessDeniedScreen();
        GoBackToMainMenue();
        break;
    case(enMainMenueOptions::eUpdateClient):
        system("cls");
        if (CurrentUserPermission & PermUpdateClient)
            ShowUpdateClientScreen();
        else
            ShowAccessDeniedScreen();
        GoBackToMainMenue();
        break;
    case(enMainMenueOptions::eFindClient):
        system("cls");
        if (CurrentUserPermission & PermFindClient )
            ShowFindClientScreen();
        else
            ShowAccessDeniedScreen();
        GoBackToMainMenue();
        break;
    case(enMainMenueOptions::eShowTransactionsMenue):
        system("cls");
        if (CurrentUserPermission & PermTransactions )
            ShowTransctionMenuScreen();
        else
            ShowAccessDeniedScreen();
        break;
    case(enMainMenueOptions::eManageUsers):
        system("cls");
        if (CurrentUserPermission & permManageUsers)
            ShowManageUsersMenuScreen();
        else
            ShowAccessDeniedScreen();
        break;
    case(enMainMenueOptions::eLogout):
        system("cls");
        ShowLoginScreen();
        break;
    }
}

void ShowMainMenu()
{
    system("cls");
    cout << "===================================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "===================================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Manage Users.\n";
    cout << "\t[8] Logout.\n";
    cout << "===================================================\n";

    PerformMainMenueOpetion((enMainMenueOptions)ReadMenuOption(8));
}

bool IsUserNameAndPasswordValid(string UserName , string UserPassword)
{
    fstream MyFile;

    MyFile.open(UsersFileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        stUser UserDate;

        while (getline(MyFile, Line))
        {
            UserDate = ConvertLineToUserRecord(Line);
            if (UserName == UserDate.Name && UserPassword == UserDate.Password)
            {
                CurrentUserPermission = UserDate.Permission;
                return true;
            }     
        }

        MyFile.close();
    }
    return false;
}

void ShowLoginScreen()
{
    system("cls");
    cout << "===================================================\n";
    cout << "\t\tLogin Screen\n";
    cout << "===================================================\n";
    CurrentUserPermission = 0;
    string UserName = ReadUserName();
    string UserPassword = ReadUserPassword();
    short LinesToDelet = 2;

    while (!IsUserNameAndPasswordValid(UserName, UserPassword))
    {
        cout << "\033[" << LinesToDelet << "A\033[J";
        cout << "Invalid Username/Password:\n";
        UserName = ReadUserName();
        UserPassword = ReadUserPassword();
        LinesToDelet = 3;
    }

    ShowMainMenu();
   
}

int main()
{
    ShowLoginScreen();
    system("Pause>0");
    return 0;
}


