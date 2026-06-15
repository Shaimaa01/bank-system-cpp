#pragma once
#include <iostream>
#include "clsPerson.h"
#include "clsString.h"
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class clsBankClient :public clsPerson
{
private:

	enum enMode {EmptyMode = 0 , UpdateMode = 1};
	enMode _Mode; 

	string _PinCode;
	string _AccountNumber;
	float _AccountBalance;

	static clsBankClient _ConvertLinetoClientObject(string Line , string Seperator = "#//#")
	{
		vector <string> vClientData = clsString::Split(Line, Seperator);
		
		return clsBankClient(enMode::UpdateMode , vClientData[0] , vClientData[1] , vClientData[2] , vClientData[3] , vClientData[4] , vClientData[5] , stod(vClientData[6]));
	}

	string _ConvertClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
	{
		string stClientRecord = "";
		stClientRecord += Client.FirstName + Seperator;
		stClientRecord += Client.LastName + Seperator;
		stClientRecord += Client.Email + Seperator;
		stClientRecord += Client.Phone + Seperator;
		stClientRecord += Client.AccountNumber() + Seperator;
		stClientRecord += Client.PinCode + Seperator;
		stClientRecord += to_string(Client.AccountBalance);

		return stClientRecord;
	}

	vector <clsBankClient> _LoadClientsDataFromFile()
	{
		vector <clsBankClient> vClientsData;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLinetoClientObject(Line);
				vClientsData.push_back(Client);
			}

			MyFile.close();
		}

		return vClientsData;
	}

	void _SaveClientsDataToFile(vector <clsBankClient>& vClients)
	{
		fstream MyFile;

		MyFile.open("Clients.txt", ios::out);

		string DataLine;

		if (MyFile.is_open())
		{
			for (clsBankClient& C : vClients)
			{
				DataLine = _ConvertClientObjectToLine(C);
				MyFile << DataLine << endl;
			}

			MyFile.close();
		}
	}

	void _Update()
	{
		vector <clsBankClient> vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : vClients)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C = *this;
				break;
			}
		}

		_SaveClientsDataToFile(vClients);
	}

	void _AddDataLineToFile(string stDataLine)
	{
		fstream MyFile;

		MyFile.open("Clients.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << stDataLine << endl;
		}

		MyFile.close();
	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode , " ", " ", " ", " ", " ", " " ,  0);
	}

public:

	clsBankClient(enMode Mode ,string FirstName , string LastName , string Email , string Phone , string AccountNumber, string PinCode, float AccountBalance) :clsPerson(FirstName , LastName , Email , Phone)
	{
		_Mode = Mode;
		_PinCode = PinCode;
		_AccountNumber = AccountNumber;
		_AccountBalance = AccountBalance;
	}

	 bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	string AccountNumber()
	{
		return _AccountNumber;
	}

	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}

	string GetPinCode()
	{
		return _PinCode;
	}

	__declspec(property(put = SetPinCode, get = GetPinCode)) string PinCode;

	void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	float GetAccountBalance()
	{
		return _AccountBalance;
	}

	__declspec(property(put = SetAccountBalance, get = GetAccountBalance)) float AccountBalance;

	void Print()
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << FirstName;
		cout << "\nLastName    : " << LastName;
		cout << "\nFull Name   : " << FullName();
		cout << "\nEmail       : " << Email;
		cout << "\nPhone       : " << Phone;
		cout << "\nAcc. Number : " << _AccountNumber;
		cout << "\nPassword    : " << _PinCode;
		cout << "\nBalance     : " << _AccountBalance;
		cout << "\n___________________\n";
	}

	static clsBankClient Find(string AccountNumber)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLinetoClientObject(Line);

				if (Client.AccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Client;
				}

			}

			MyFile.close();
		}
		
		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber , string PinCode)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLinetoClientObject(Line);

				if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
				{
					MyFile.close();
					return Client;
				}
			}

			MyFile.close();
		}

		return _GetEmptyClientObject();
	}

	enum enSaveResults {svFailedEmptyObject = 0 , svSucceeded = 1};

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case(enMode::EmptyMode):
			return enSaveResults::svFailedEmptyObject;
			break;

		case(enMode::UpdateMode):
			_Update();
			return enSaveResults::svSucceeded;
			break;
		}
	}

	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client = Find(AccountNumber);

		return !Client.IsEmpty();
	}
};

