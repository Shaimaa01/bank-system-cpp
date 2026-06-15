#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
using namespace std;

void ReadClientInfo(clsBankClient &Client)
{
    cout << "\nEnter FirstName : ";
    Client.FirstName = clsInputValidate::ReadString();

    cout << "\nEnter LastName : ";
    Client.LastName = clsInputValidate::ReadString();

    cout << "\nEnter Email : ";
    Client.Email = clsInputValidate::ReadString();

    cout << "\nEnter Phone : ";
    Client.Phone = clsInputValidate::ReadString();

    cout << "\nEnter PinCode : ";
    Client.PinCode = clsInputValidate::ReadString();

    cout << "\nEnter Account Balance : ";
    Client.AccountBalance = clsInputValidate::ReadFloatNumber();
}

void UpdateClient()
{
    cout << "\nPlease Enter Client Account Number: ";
    string AccountNumber = clsInputValidate::ReadString();

    while (!clsBankClient::IsClientExist(AccountNumber))
    {
        cout << "\nAccount Number is not Found , choose another one:";
        AccountNumber = clsInputValidate::ReadString();
    }

    clsBankClient Client = clsBankClient::Find(AccountNumber);
    Client.Print();

    cout << "\n\nUpdate Client Info:\n";
    cout << "\n______________________\n";

    ReadClientInfo(Client);

    clsBankClient::enSaveResults SaveResults;
    SaveResults = Client.Save();

    switch (SaveResults)
    {
    case(clsBankClient::enSaveResults::svSucceeded):
        cout << "\nAccount Updated Successfully :-)\n";
        Client.Print();
        break;
    case(clsBankClient::enSaveResults::svFailedEmptyObject):
        cout << "\nError account was not saved because it's Empty";
        break;
    }
}

void AddNewClient()
{
    string AccountNumber = "";
   
    cout << "\nPlease Enter Account Number: ";
    AccountNumber = clsInputValidate::ReadString();
    while (clsBankClient::IsClientExist(AccountNumber))
    {
        cout << "\nAccount Number Is Already Used, Choose another one: ";
        AccountNumber = clsInputValidate::ReadString();
    }

    clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

    ReadClientInfo(NewClient);

    clsBankClient::enSaveResults SaveResults;

    SaveResults = NewClient.Save();

    switch (SaveResults)
    {
    case(clsBankClient::enSaveResults::svSucceeded):
        cout << "\nAccount Addeded Successfully :-)\n";
        break;

    case(clsBankClient::enSaveResults::svFailedEmptyObject):
        cout << "\nError account was not saved because it's Empty";
        break;

    case(clsBankClient::enSaveResults::svFaildAccountNumberExists):
        cout << "\nError account was not saved because account number is used!\n";
        break;
    }
}

int main()
{
    //Login();

   //clsBankClient Client1 =  clsBankClient::Find("A101");
   //Client1.Print();

   //clsBankClient Client2 = clsBankClient::Find("A101", "1234");
   //Client2.Print();

   //cout <<  endl << clsBankClient::IsClientExist("A101");

    //UpdateClient();

    AddNewClient();

    system("Pause>0");
    return 0;
}


