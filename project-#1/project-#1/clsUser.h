#pragma once
#include "clsPerson.h"
#include <vector>
#include <fstream>
#include <string>
#include "clsString.h"
#include "clsDate.h"

using namespace std;

class clsUser : public clsPerson
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };

	enMode _Mode;
	string _UserName;
	string _Password;
	int _Permissions;

	bool _MarkedForDelete = false;

	 static clsUser _ConvertLineToUserObject(string Line , string Seperator = "#//#")
	 {
		vector <string> vUsers = clsString::Split(Line , Seperator);
		return clsUser(enMode::UpdateMode, vUsers[0], vUsers[1] , vUsers[2] , vUsers[3] , vUsers[4] , vUsers[5]  , stoi(vUsers[6]));
	 }

	 string _ConvertUserObjectToLine(clsUser User, string Seperator = "#//#")
	 {
		 string UserRecord = "";
		 UserRecord += User.FirstName + Seperator;
		 UserRecord += User.LastName + Seperator;
		 UserRecord += User.Email + Seperator;
		 UserRecord += User.Phone + Seperator;
		 UserRecord += User.UserName + Seperator;
		 UserRecord += User.Password + Seperator;
		 UserRecord += to_string(User.Permissions);

		 return UserRecord;
	 }

	 static vector <clsUser> _LoadUsersDataFromFile()
	 {
		 vector <clsUser> vUsers;
		 fstream MyFile;


		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);
				vUsers.push_back(User);
			}

			MyFile.close();
		}

		return vUsers;
	 }

	 void _SaveUsersDataToFile(vector <clsUser>& vUsers)
	 {
		 fstream MyFile;

		 MyFile.open("Users.txt", ios::out);

		 string DataLine;

		 if (MyFile.is_open())
		 {
			 for (clsUser& U : vUsers)
			 {
				 if (U.MarkedForDeleted() == false)
				 {
					 DataLine = _ConvertUserObjectToLine(U);
					 MyFile << DataLine << endl;
				 }
			 }

			 MyFile.close();
		 }
	 }

	 void _Update()
	 {
		 vector <clsUser> vUsers = _LoadUsersDataFromFile();

		 for (clsUser& U : vUsers)
		 {
			 if (U.UserName == UserName)
			 {
				 U = *this;
				 break;
			 }
		 }

		 _SaveUsersDataToFile(vUsers);
	 }

	 void _AddNew()
	 {
		 _AddDataLineToFile(_ConvertUserObjectToLine(*this));
	 }

	 void _AddDataLineToFile(string stDataLine)
	 {
		 fstream MyFile;

		 MyFile.open("Users.txt", ios::out | ios::app);

		 if (MyFile.is_open())
		 {
			 MyFile << stDataLine << endl;
		 }

		 MyFile.close();
	 }

	 static clsUser _GetEmptyUserObject()
	 {
		 return clsUser(enMode::EmptyMode, " ", " ", " ", " ", " ", " ", 0);
	 }

	 string _PrepareLogInRecord(string Seperator = "#//#")
	 {
		 string LineRecord = "";
		 
		 LineRecord += clsDate::GetSystemTimeDataString() + Seperator;
		 LineRecord += UserName + Seperator;
		 LineRecord += Password + Seperator;
		 LineRecord += to_string(Permissions);

		 return LineRecord;
	 }

public:
	enum enPermissions { eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4, pUpdateClient = 8, pFindClient = 16, pTrancations = 32, pManageUsers = 64 };

	clsUser( enMode Mode , string FirstName , string LastName , string Email , string Phone ,string UserName , string Password , int Permissions )
		:clsPerson( FirstName,  LastName,  Email,  Phone)
	{
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;
	}

	bool IsEmpty()
	{
		return _Mode == enMode::EmptyMode;
	}

	bool MarkedForDeleted()
	{
		return _MarkedForDelete;
	}

	void SetUserName(string UserName)
	{
		_UserName = UserName;
	}
	 
	string GetUserName()
	{
		return _UserName;
	}

	__declspec(property(get = GetUserName, put = SetUserName)) string UserName;

	void SetPassword(string Password)
	{
		_Password = Password;
	}

	string GetPassword()
	{
		return _Password;
	}

	__declspec(property(get = GetPassword, put = SetPassword)) string Password;

	void SetPermissions(int Permissions)
	{
		_Permissions = Permissions;
	}

	int GetPermissions()
	{
		return _Permissions;
	}

	__declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

	static clsUser Find(string UserName)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsUser Client = _ConvertLineToUserObject(Line);

				if (Client.UserName == UserName)
				{
					MyFile.close();
					return Client;
				}

			}

			MyFile.close();
		}

		return _GetEmptyUserObject();
	}

	static clsUser Find(string UserName , string Password)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsUser Client = _ConvertLineToUserObject(Line);

				if (Client.UserName == UserName && Client.Password == Password)
				{
					MyFile.close();
					return Client;
				}

			}

			MyFile.close();
		}

		return _GetEmptyUserObject();
	}
	
	enum enSaveResults { svFailedEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };

	 enSaveResults Save()
	{
		switch (_Mode)
		{
		case(enMode::EmptyMode):
			return enSaveResults::svFailedEmptyObject;

		case(enMode::UpdateMode):
			_Update();
			return enSaveResults::svSucceeded;

		case(enMode::AddNewMode):
		{
			if (IsUserExist(UserName))
			{
				return enSaveResults::svFaildUserExists;
			}
			else
			{
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}
		}
		}
	}

	static bool IsUserExist(string UserName)
	{
		clsUser User = Find(UserName);
		return !User.IsEmpty();
	}

	static clsUser GetAddNewUserObject(string UserName)
	{
		return clsUser(enMode::AddNewMode, " ", " ", " ", " ", UserName, " ", 0);
	}

	bool Delete()
	{
		vector <clsUser> vUsers = _LoadUsersDataFromFile();

		for (clsUser& U : vUsers)
		{
			if (U.UserName == UserName)
			{
				U._MarkedForDelete = true;
				break;
			}
		}

		_SaveUsersDataToFile(vUsers);

		*this = _GetEmptyUserObject();

		return true;
	}

	static vector <clsUser> GetUsersList()
	{
		return _LoadUsersDataFromFile();
	}

	bool CheckAccessPermission(enPermissions Permission) 
	{
		if (this->Permissions == enPermissions::eAll)
		{
			return true;
		}

		if ((this->Permissions & Permission) == Permission)
		{
			return true;
		}

		return false;
	}

	void RegisterLogIn()
	{
		fstream MyFile;

		string DateLine = _PrepareLogInRecord();

		MyFile.open("LoginRegister.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << DateLine << endl;

			MyFile.close();
		}
	}
};

