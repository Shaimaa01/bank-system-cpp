#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUsersListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

class clsManageUsersScreen : protected clsScreen
{
private:
    enum enManageUsersMenueOptions{ eListUsers = 1 , eAddNewUser = 2 , eDeleteUser = 3 , eUpdateUser = 4 , eFindUser = 5 , eShowMainMenu = 6 };

    static short _ReadManageUsersMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short Choice = clsInputValidate::ReadshortNumberBetween(1, 6, "Number should be betwwen 1 to 6 , Enter again:");
        return Choice;
    }

    static void _GoBackToManageUsersMenu()
    {
        cout << "\n\nPress any key to go back to Manage Users  Menue...";
        system("pause > nul");
        ShowManageUsersMenue();
    }

    static void _ShowListUsersScreen()
    {
        clsListUsersScreen::ShowUsersList();
    }

    static void _ShowAddNewUserScreen()
    {
        clsAddNewUserScreen::ShowAddNewUserScreen();
    }

    static void _ShowDeleteUserScreen()
    {
        clsDeleteUserScreen::ShowDeleteUserScreen();
    }

    static void _ShowUpdateUserScreen()
    {
        clsUpdateUserScreen::ShowUpdateUserScreen();
    }

    static void _ShowFindUserScreen()
    {
        clsFindUserScreen::ShowFindUserScreen();
    }

    static void _PerformMangeUsersMenueOpetion(enManageUsersMenueOptions MangeUsersMenuOption)
    {
        switch (MangeUsersMenuOption)
        {
        case(enManageUsersMenueOptions::eListUsers):
            system("cls");
            _ShowListUsersScreen();
            _GoBackToManageUsersMenu();
            break;
        case(enManageUsersMenueOptions::eAddNewUser):
            system("cls");
            _ShowAddNewUserScreen();
            _GoBackToManageUsersMenu();
            break;
        case(enManageUsersMenueOptions::eDeleteUser):
            system("cls");
            _ShowDeleteUserScreen();
            _GoBackToManageUsersMenu();
            break;
        case(enManageUsersMenueOptions::eUpdateUser):
            system("cls");
            _ShowUpdateUserScreen();
            _GoBackToManageUsersMenu();
            break;
        case(enManageUsersMenueOptions::eFindUser):
            system("cls");
            _ShowFindUserScreen();
            _GoBackToManageUsersMenu();
            break;
        case(enManageUsersMenueOptions::eShowMainMenu):
        {
            
        }
        }
    }


public:
	static void ShowManageUsersMenue()
	{
        system("cls");

        if (!AccessPermissionsRight(clsUser::enPermissions::pManageUsers))
        {
            return;
        }

        _DrawScreenHeader("\t Manage Users Screen");


        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Manage Users Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Users.\n";
        cout << setw(37) << left << "" << "\t[2] Add New User.\n";
        cout << setw(37) << left << "" << "\t[3] Delete User.\n";
        cout << setw(37) << left << "" << "\t[4] Update User.\n";
        cout << setw(37) << left << "" << "\t[5] Find User.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformMangeUsersMenueOpetion((enManageUsersMenueOptions)_ReadManageUsersMenueOption());
	}
};

