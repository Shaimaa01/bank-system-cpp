#pragma once
#include "Global.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsMainScreen.h"

class clsLoginScreen :protected clsScreen
{
private:

    static void _Login()
    {
        bool LoginFaild = false;
        string UserName, Password;

        do
        {
            if (LoginFaild)
            {
                cout << "Invalid Username/Password:\n";
            }

            cout << "Enter Username? ";
            UserName = clsInputValidate::ReadString();

            cout << "Enter Password? ";
            Password = clsInputValidate::ReadString();

            CurrentUser = clsUser::Find(UserName, Password);

            LoginFaild = CurrentUser.IsEmpty();

        } while (LoginFaild);

        clsMainScreen::ShowMainMenue();
    }

public:
	static void ShowLoginScreen()
	{
        system("cls");
		_DrawScreenHeader("\t Login Screen");
        _Login();
	}
};

