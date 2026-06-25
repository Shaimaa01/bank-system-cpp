#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTranserLogScreen.h"

using namespace std;

class clsTransactionsScreen : protected clsScreen
{
private:
    enum enTransactionsMenueOptions { eDeposit = 1, eWithdraw = 2, eTotalBalances = 3, eTransfer = 4 , eTransferLog = 5 , eMainMenu = 6 };

    static short _ReadTransactionMenuOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short Choice = clsInputValidate::ReadshortNumberBetween(1, 6, "Number should be betwwen 1 to 6 , Enter again:");
        return Choice;
    }

    static void _GoBackToTransactionMenu()
    {
        cout << "\n\nPress any key to go back to Transactions Menue...";
        system("pause > nul");
        ShowTransactionsMenue();
    }

    static void _ShowDepositScreen()
    {
        clsDepositScreen::ShowDepositScreen();
    }

    static void _ShowWithdrawScreen()
    {
        clsWithdrawScreen::ShowWithdrawScreen();
    }

    static void _ShowTotalBalancesScreen()
    {
        clsTotalBalancesScreen::ShowTotalBalances();
    }

    static void _ShowTransferScreen()
    {
        clsTransferScreen::ShowTransferScreen();
    }

    static void _ShowTransferLogScreen()
    {
        clsTranserLogScreen::ShowTransferLogScreen();
    }

     static void _PerformTransactionMenueOpetion(enTransactionsMenueOptions TransactionMenuOption)
    {
        switch (TransactionMenuOption)
        {
        case(enTransactionsMenueOptions::eDeposit):
            system("cls");
            _ShowDepositScreen();
            _GoBackToTransactionMenu();
            break;
        case(enTransactionsMenueOptions::eWithdraw):
            system("cls");
            _ShowWithdrawScreen();
            _GoBackToTransactionMenu();
            break;
        case(enTransactionsMenueOptions::eTotalBalances):
            system("cls");
            _ShowTotalBalancesScreen();
            _GoBackToTransactionMenu();
            break;
        case(enTransactionsMenueOptions::eTransfer):
            system("cls");
            _ShowTransferScreen();
            _GoBackToTransactionMenu();
            break;
        case(enTransactionsMenueOptions::eTransferLog):
            system("cls");
            _ShowTransferLogScreen();
            _GoBackToTransactionMenu();
            break;
        case(enTransactionsMenueOptions::eMainMenu):
        {

        }
        }
    }

public:
	static void ShowTransactionsMenue()
	{
        system("cls");

        if (!AccessPermissionsRight(clsUser::enPermissions::pTrancations))
        {
            return;
        }
        
        _DrawScreenHeader("\t  Transactions Menue Screen");
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Transactions Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit.\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
        cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
        cout << setw(37) << left << "" << "\t[4] Transfer.\n";
        cout << setw(37) << left << "" << "\t[5] Transfer Log.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformTransactionMenueOpetion((enTransactionsMenueOptions)_ReadTransactionMenuOption());
	}
};

