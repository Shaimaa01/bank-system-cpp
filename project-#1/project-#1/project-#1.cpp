#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

const string ClientsFileName = "Clients.txt";
const string UsersFileName = "Users.txt";

void ShowMainMenu();
void ShowTransctionMenuScreen();

struct stClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelet = false;
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

enum enMainMenueOptions { eListClients = 1, eAddNewClient = 2, eDeleteClient = 3, eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6, eExit = 7 };

enum enTransactionsMenueOptions { eDeposit = 1, eWithdraw = 2 , eTotalBalances = 3 , eMainMenu = 4};

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

void PerformMainMenueOpetion(enMainMenueOptions MainMenuOption )
{
    switch (MainMenuOption)
    {
    case(enMainMenueOptions::eListClients):
        system("cls");
        ShowAllClientListScreen();
        GoBackToMainMenue();
        break;
    case(enMainMenueOptions::eAddNewClient):
        system("cls");
        ShowAddNewClientScreen();
        GoBackToMainMenue();
        break;
    case(enMainMenueOptions::eDeleteClient):
        system("cls");
        ShowDeleteClientScreen();
        GoBackToMainMenue();
        break;
    case(enMainMenueOptions::eUpdateClient):
        system("cls");
        ShowUpdateClientScreen();
        GoBackToMainMenue();
        break;
    case(enMainMenueOptions::eFindClient):
        system("cls");
        ShowFindClientScreen();
        GoBackToMainMenue();
        break;
    case(enMainMenueOptions::eShowTransactionsMenue):
        system("cls");
        ShowTransctionMenuScreen();
        break;
    case(enMainMenueOptions::eExit):
        system("cls");
        ShowEndScreen();
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
    cout << "\t[7] Exit.\n";
    cout << "===================================================\n";

    PerformMainMenueOpetion((enMainMenueOptions)ReadMenuOption(7));
}

// Bank Extension 2  

string ReadUserName()
{
    string UserName;
    cout << "Enter UserName? ";
    getline(cin, UserName);
    return UserName;
}

string ReadUserPassword()
{
    string Password;
    cout << "Enter Password? ";
    getline(cin, Password);
    return Password;
}

struct stUser
{
    string Name;
    string Password;
    string Permission;
};

stUser ConvertLineToUserStruct(string Line)
{
    vector <string> vUserDate = SplitString(Line , "#//#");
    stUser UserDate;
    UserDate.Name = vUserDate[0];
    UserDate.Password = vUserDate[1];
    UserDate.Permission = vUserDate[2];
    return UserDate;
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
            UserDate = ConvertLineToUserStruct(Line);
            if (UserName == UserDate.Name && UserPassword == UserDate.Password)
                return true;
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


