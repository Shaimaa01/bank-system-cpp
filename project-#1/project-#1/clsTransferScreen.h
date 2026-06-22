#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"

class clsTransferScreen : protected clsScreen
{
private:
    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";
    }

    static string _ReadAccountNumber(string Destination = "From")
    {
        string AccountNumber;

        cout << "\nPlease Enter Client Account Number to Transfer " << Destination << ": ";
         AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount Number is not Found , choose another one:";
            AccountNumber = clsInputValidate::ReadString();
        }

        return AccountNumber;
    }

    static float ReadAmount(clsBankClient SourceClient)
    {
        double Amount = 0;
        cout << "\nEnter Transfer Amount?";
        Amount = clsInputValidate::ReadDblNumber();

        while (SourceClient.AccountBalance < Amount)
        {
            cout << "\nAmount Exceeds the available Balance, Enter another Amount ? ";
            Amount = clsInputValidate::ReadDblNumber();
        }

        return Amount;
    }


public:

	static void ShowTransferScreen() 
	{
		_DrawScreenHeader("\t Transfer Screen");

        clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber());
        _PrintClient(SourceClient);

   
        clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber("To"));
        _PrintClient(DestinationClient);

        double Amount = ReadAmount(SourceClient);

        char Answer = 'n';

        cout << "\nAre you sure you want to perform this operation? y/n?";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            if (SourceClient.Tansfer(Amount, DestinationClient , CurrentUser.UserName))
            {
                cout << "\nTransfer Done Successfully\n";
            }
            else
            {
                cout << "\nTransfer Faild \n";
            }
        }

        _PrintClient(SourceClient);
        _PrintClient(DestinationClient);
	}
};

