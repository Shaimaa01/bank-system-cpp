#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "clsLoginRegisterScreen.h"
#include "Global.h"
#include "clsCurrencyExchangeMainScreen.h"

using namespace std;

class clsMainScreen : protected clsScreen
{
private:
    enum enMainMenueOptions { eListClients = 1, eAddNewClient = 2, eDeleteClient = 3, eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6, eManageUsers = 7, eRegisterLogIn = 8 , eCurrencyExchange = 9, eLogout = 10 };

    static short _ReadMainMenuOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 10]? ";
        short Choice = clsInputValidate::ReadshortNumberBetween(1, 10, "Number should be betwwen 1 to 10 , Enter again:");
        return Choice;
    }

    static void _GoBackToMainMenue()
    {
        cout << "\n\n" << setw(37) << left << "" << "\tPress any key to go back to Main Menue...\n";
        system("pause > nul");
        ShowMainMenue();
    }

    static void _ShowAllClientListScreen()
    {
        clsClientListScreen::ShowClientsList();
    }

    static void _ShowAddNewClientScreen()
    {
        clsAddNewClientScreen::ShowAddNewClientScreen();
    }

    static void _ShowDeleteClientScreen()
    {
        clsDeleteClientScreen::ShowDeleteClientScreen();
    }

    static void _ShowUpdateClientScreen()
    {
        clsUpdateClientScreen::ShowUpdateClientScreen();
    }

    static void _ShowFindClientScreen()
    {
        clsFindClientScreen::ShowFindClientScreen();
    }

    static void _ShowTransctionMenuScreen()
    {
        clsTransactionsScreen::ShowTransactionsMenue();
    }

    static void _ShowManageUsersMenuScreen()
    {
        clsManageUsersScreen::ShowManageUsersMenue();
    }

    static void _ShowLoginRegisterScreen()
    {
        clsLoginRegisterScreen::ShowLoginRegisterScreen();
    }

    static void _ShowCurrencyExchangeMenu()
    {
        clsCurrencyExchangeMainScreen::ShowCurrencyExchangeMenu();
    }
 
    static void _Logout()
    {
        CurrentUser = clsUser::Find("", "");
    }

    static void _PerformMainMenueOpetion(enMainMenueOptions MainMenuOption)
    {
        switch (MainMenuOption)
        {
        case(enMainMenueOptions::eListClients):
            system("cls");
            _ShowAllClientListScreen();
            _GoBackToMainMenue();
            break;
        case(enMainMenueOptions::eAddNewClient):
            system("cls");
            _ShowAddNewClientScreen();
            _GoBackToMainMenue();
            break;
        case(enMainMenueOptions::eDeleteClient):
            system("cls");
            _ShowDeleteClientScreen();
            _GoBackToMainMenue();
            break;
        case(enMainMenueOptions::eUpdateClient):
            system("cls");
            _ShowUpdateClientScreen();
            _GoBackToMainMenue();
            break;
        case(enMainMenueOptions::eFindClient):
            system("cls");
            _ShowFindClientScreen();
            _GoBackToMainMenue();
            break;
        case(enMainMenueOptions::eShowTransactionsMenue):
            system("cls");
            _ShowTransctionMenuScreen();
            _GoBackToMainMenue();
            break;
        case(enMainMenueOptions::eManageUsers):
            system("cls");
            _ShowManageUsersMenuScreen();
            _GoBackToMainMenue();
            break;
        case(enMainMenueOptions::eRegisterLogIn):
            system("cls");
            _ShowLoginRegisterScreen();
            _GoBackToMainMenue();
            break;
        case(enMainMenueOptions::eCurrencyExchange):
            system("cls");
            _ShowCurrencyExchangeMenu();
            _GoBackToMainMenue();
            break;
        case(enMainMenueOptions::eLogout):
            system("cls");
            _Logout();
            break;
        }
    }

public:
	static void ShowMainMenue()
	{
        system("cls");
        _DrawScreenHeader("\t\tMain Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
        cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
        cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
        cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
        cout << setw(37) << left << "" << "\t[5] Find Client.\n";
        cout << setw(37) << left << "" << "\t[6] Transactions.\n";
        cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
        cout << setw(37) << left << "" << "\t[8] Login Register.\n";
        cout << setw(37) << left << "" << "\t[9] Currency Exchange.\n";
        cout << setw(37) << left << "" << "\t[10] Logout.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformMainMenueOpetion((enMainMenueOptions)_ReadMainMenuOption());
	}
};

