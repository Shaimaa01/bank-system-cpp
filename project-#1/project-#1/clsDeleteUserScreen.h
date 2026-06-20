#pragma once
#include "clsScreen.h"
#include "clsUser.h"

using namespace std;

class clsDeleteUserScreen : protected clsScreen
{
    private:

    static void _PrintUser(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.FirstName;
        cout << "\nLastName    : " << User.LastName;
        cout << "\nFull Name   : " << User.FullName();
        cout << "\nEmail       : " << User.Email;
        cout << "\nPhone       : " << User.Phone;
        cout << "\nUserName    : " << User.UserName;
        cout << "\nPassword    : " << User.Password;
        cout << "\nPermissions : " << User.Permissions;
        cout << "\n___________________\n";
    }

    public:

        static void ShowDeleteUserScreen()
        {
            _DrawScreenHeader("\tDelete User Screen");

            cout << "\nPlease Enter User UserName: ";
            string UserName = clsInputValidate::ReadString();

            while(!clsUser::IsUserExist(UserName))
            {
                cout << "\nUser Name is not Found , choose another one:";
                UserName = clsInputValidate::ReadString();
            }

            clsUser User = clsUser::Find(UserName);
            _PrintUser(User);

            char Answer = 'n';

            cout << "Are you sure you want to delete this User y/n ";
            cin >> Answer;

            if (Answer == 'y' || Answer == 'Y')
            {
                if (User.Delete())
                {
                    cout << "\nUser Deleted Successfully :-)\n";
                    _PrintUser(User);
                }
                else
                {
                    cout << "\nError Client Was not Deleted\n";
                }
            }
        }
	
};

