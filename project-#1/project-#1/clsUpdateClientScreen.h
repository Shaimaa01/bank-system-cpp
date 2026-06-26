#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"

using namespace std;

class clsUpdateClientScreen : protected clsScreen
{
private:
    static void _ReadClientInfo(clsBankClient& Client)
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
        Client.AccountBalance = clsInputValidate::ReadNumber<float>();
    }

    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";
    }
    
public:
    static void ShowUpdateClientScreen()
    {
        if (!AccessPermissionsRight(clsUser::enPermissions::pUpdateClient))
        {
            return;
        }

        _DrawScreenHeader("\t Update Client Screen");

        cout << "\nPlease Enter Client Account Number: ";
        string AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount Number is not Found , choose another one:";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        char Answer = 'n';

        cout << "\nAre you sure you want to delete this client y/n ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            cout << "\n\nUpdate Client Info:\n";
            cout << "\n______________________\n";

            _ReadClientInfo(Client);

            clsBankClient::enSaveResults SaveResults;
            SaveResults = Client.Save();

            switch (SaveResults)
            {
            case(clsBankClient::enSaveResults::svSucceeded):
                cout << "\nAccount Updated Successfully :-)\n";
                _PrintClient(Client);
                break;
            case(clsBankClient::enSaveResults::svFailedEmptyObject):
                cout << "\nError account was not saved because it's Empty";
                break;
            }
        }
    } 

};

