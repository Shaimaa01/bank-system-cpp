#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsAddNewUserScreen : protected clsScreen
{
private:
	
	static void _ReadUserInfo(clsUser & User)
	{
		cout << "\nEnter FirstName : ";
		User.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter LastName : ";
		User.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email : ";
		User.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone : ";
		User.Phone = clsInputValidate::ReadString();

		cout << "\nEnter Password : ";
		User.Password = clsInputValidate::ReadString();

		cout << "\nEnter Permissions : ";
		User.Permissions = _ReadPermissionsToSet();
	}

	static short _ReadPermissionsToSet()
	{
		int Permission = 0;
		char Answer;

		cout << "\nDo you want to give full access? y/n? ";
		cin >> Answer;
		if (tolower(Answer) == 'y')
			return Permission = clsUser::enPermissions::eAll;

		cout << "\nDo you want to give access to : ";
		cout << "\n\nShow Client List? y/n? ";
		cin >> Answer;
		if (tolower(Answer) == 'y')
			Permission += clsUser::enPermissions::pListClients;

		cout << "\n\nAdd New Client? y/n? ";
		cin >> Answer;
		if (tolower(Answer) == 'y')
			Permission += clsUser::enPermissions::pAddNewClient;

		cout << "\n\nDelete Client? y/n? ";
		cin >> Answer;
		if (tolower(Answer) == 'y')
			Permission += clsUser::enPermissions::pDeleteClient;

		cout << "\n\nUpdate Client? y/n? ";
		cin >> Answer;
		if (tolower(Answer) == 'y')
			Permission += clsUser::enPermissions::pUpdateClient;

		cout << "\n\nFind Client? y/n? ";
		cin >> Answer;
		if (tolower(Answer) == 'y')
			Permission += clsUser::enPermissions::pFindClient;

		cout << "\n\nTransactions? y/n? ";
		cin >> Answer;
		if (tolower(Answer) == 'y')
			Permission += clsUser::enPermissions::pTrancations;

		cout << "\n\nManage Users? y/n? ";
		cin >> Answer;
		if (tolower(Answer) == 'y')
			Permission += clsUser::enPermissions::pManageUsers;

		return Permission;
	}

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

	static void ShowAddNewUserScreen()
	{
		_DrawScreenHeader("\t Add New User Screen");

		cout << "\nPlease Enter UserName: ";
		string UserName = clsInputValidate::ReadString();

		while (clsUser::IsUserExist(UserName))
		{
			cout << "\nUserName Is Already Used, Choose another one: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser NewUser = clsUser::GetAddNewUserObject(UserName);

		_ReadUserInfo(NewUser);

		clsUser::enSaveResults SaveResults;

		SaveResults = NewUser.Save();

			switch (SaveResults)
			{
			case(clsUser::enSaveResults::svSucceeded):
				cout << "\nUser Addeded Successfully :-)\n";
				_PrintUser(NewUser);
				break;

			case(clsUser::enSaveResults::svFailedEmptyObject):
				cout << "\nError User was not saved because it's Empty";
				break;

			case(clsUser::enSaveResults::svFaildUserExists):
				cout << "\nError User was not saved because UserName is used!\n";
				break;
			}
	}
};

