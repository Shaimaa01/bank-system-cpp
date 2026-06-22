#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"

class clsTranserLogScreen : protected clsScreen
{
private:
    static void PrintClientRecordLine(clsBankClient::stTransferLogRecord T)
    {
        cout << setw(8) << left << "" << "| " << setw(15) << left << T.DateTime;
        cout << "| " << setw(20) << left << T.SourceAccountNumber;
        cout << "| " << setw(12) << left << T.DestinationAccountNumber;
        cout << "| " << setw(20) << left << T.srcBalanceAfter;
        cout << "| " << setw(10) << left << T.destBalanceAfter;
        cout << "| " << setw(12) << left << T.UserName;
    }

public:
	static void ShowTransferLogScreen()
	{
        vector <clsBankClient::stTransferLogRecord> vRegisterTransferList = clsBankClient::GetTransferLogList();

        string Title = "\t  Transfer Log List Screen";
        string SubTitle = "\t    (" + to_string(vRegisterTransferList.size()) + ") Client(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(15) << "Data/Time";
        cout << "| " << left << setw(20) << "S.Acct";
        cout << "| " << left << setw(12) << "D.Acct";
        cout << "| " << left << setw(20) << "S.Balance";
        cout << "| " << left << setw(10) << "d.Balance";
        cout << "| " << left << setw(12) << "User";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vRegisterTransferList.size() == 0)
            cout << "\t\t\t\tNo Operations Available In the System!";
        else

            for (clsBankClient::stTransferLogRecord T : vRegisterTransferList)
            {

                PrintClientRecordLine(T);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
	}
};

