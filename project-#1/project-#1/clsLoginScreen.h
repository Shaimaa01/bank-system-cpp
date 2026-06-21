#pragma once
#include "Global.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsMainScreen.h"

class clsLoginScreen :protected clsScreen
{
private:

    static bool _Login()
    {
        bool LoginFaild = false;
        short LoginFaildCounter = 0;
        string UserName, Password;
     
        do
        {
            if (LoginFaild)
            {
                cout << "\nInvalid Username/Password:\n";
                LoginFaildCounter++;
                cout << "You have " << 3-LoginFaildCounter << " Trials to login.\n\n";
            }

            if (LoginFaildCounter == 3)
            {
                cout << "\nYour are Locked after " << LoginFaildCounter << " faild trails\n";
                return false;
            }

            cout << "Enter Username? ";
            UserName = clsInputValidate::ReadString();

            cout << "Enter Password? ";
            Password = clsInputValidate::ReadString();

            CurrentUser = clsUser::Find(UserName, Password);

            LoginFaild = CurrentUser.IsEmpty();

        } while (LoginFaild);

        clsMainScreen::ShowMainMenue();
        return true;
    }

public:
	static bool ShowLoginScreen()
	{
        system("cls");
		_DrawScreenHeader("\t Login Screen");
        return _Login();
	}
};

