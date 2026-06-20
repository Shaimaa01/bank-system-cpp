#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"

using namespace std;

class clsWithdrawScreen :protected clsScreen
{
private:
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

    static string _ReadAccountNumber()
    {
        cout << "\nPlease enter AccountNumber? ";
        string AccountNumber = clsInputValidate::ReadString();
        return AccountNumber;
    }

public:
    static void ShowWithdrawScreen()
    {
        _DrawScreenHeader("\t  Withdraw Screen");

        string AccountNumber = _ReadAccountNumber();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
            AccountNumber = _ReadAccountNumber();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        double Amount = 0;
        cout << "\nPlease enter Withdraw amount? ";
        Amount = clsInputValidate::ReadDblNumber();

        cout << "\nAre you sure you want to perform this transaction? ";
        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            if (Client.Withdraw(Amount))
            {
                cout << "\nAmount Withdraw Successfully.\n";
                cout << "New Balance is = " << Client.AccountBalance;
            }
            else
            {
                cout << "\nCan't withdraw, Insuffecient Balance!\n";
                cout << "\nAmount to withdraw is : " << Amount;
                cout << "\nYour Balance is: " << Client.AccountBalance;
            }
            
        }
        else
        {
            cout << "\nOperation was cancelled.\n";
        }
    }
};

