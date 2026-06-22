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

	enum enMode {EmptyMode = 0 , UpdateMode = 1 , AddNewMode = 2};
	enMode _Mode; 

	string _PinCode;
	string _AccountNumber;
	float _AccountBalance;
	bool _MarkForDelete = false;

	struct stTransferLogRecord;

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

	static vector <clsBankClient> _LoadClientsDataFromFile()
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
				if (C.MarkForDelete() == false)
				{
					DataLine = _ConvertClientObjectToLine(C);
					MyFile << DataLine << endl;
				}
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

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}

	string _PrepareTransferLogRecord( float Amount ,  clsBankClient DestinationClient , string UserName , string Seperator = "#//#" )
	{
		string TransferLogRecord = "";

		TransferLogRecord += clsDate::GetSystemTimeDataString() + Seperator;
		TransferLogRecord += _AccountNumber + Seperator;
		TransferLogRecord += DestinationClient.AccountNumber() + Seperator;
		TransferLogRecord += to_string(Amount) + Seperator;
		TransferLogRecord += to_string(_AccountBalance) + Seperator;
		TransferLogRecord += to_string(DestinationClient.AccountBalance) + Seperator;
		TransferLogRecord += CurrentUser.UserName;

		return TransferLogRecord;
	}

	void _RegisterTransferLog(float Amount, clsBankClient DestinationClient , string UserName)
	{
		fstream MyFile;

		MyFile.open("TransferLog.txt", ios::out | ios::app);

		string stDataLine = _PrepareTransferLogRecord( Amount, DestinationClient , UserName);

		if (MyFile.is_open())
		{
			MyFile << stDataLine << endl;

			MyFile.close();
		}
	}

	static stTransferLogRecord _ConvertTransferLogLineToRecord(string Line , string Seperator = "#//#")
	{
		vector <string> vTransferLogRecordLine = clsString::Split(Line, Seperator);

		stTransferLogRecord TransferRecord;

		TransferRecord.DateTime = vTransferLogRecordLine[0];
		TransferRecord.SourceAccountNumber = vTransferLogRecordLine[1];
		TransferRecord.DestinationAccountNumber = vTransferLogRecordLine[2];
		TransferRecord.Amount =stof(vTransferLogRecordLine[3]);
		TransferRecord.srcBalanceAfter = stof(vTransferLogRecordLine[4]);
		TransferRecord.destBalanceAfter = stof(vTransferLogRecordLine[5]);
		TransferRecord.UserName = vTransferLogRecordLine[6];

		return TransferRecord;
	}

public:
	static struct stTransferLogRecord
	{
		string DateTime;
		string SourceAccountNumber;
		string DestinationAccountNumber;
		float Amount;
		float srcBalanceAfter;
		float destBalanceAfter;
		string UserName;
	};

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

	bool MarkForDelete()
	{
		return _MarkForDelete;
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

	enum enSaveResults {svFailedEmptyObject = 0 , svSucceeded = 1 , svFaildAccountNumberExists = 2};

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
			if (IsClientExist(AccountNumber()))
			{
				return enSaveResults::svFaildAccountNumberExists;
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

	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client = Find(AccountNumber);

		return !Client.IsEmpty();
	}

	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode , " " , " " , " " , " " , AccountNumber , " " , 0);
	}

	bool Delete()
	{
		vector <clsBankClient> vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : vClients)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C._MarkForDelete = true;
				break;
			}
		}

		_SaveClientsDataToFile(vClients);

		*this = _GetEmptyClientObject();

		return true;
	}

	static vector <clsBankClient> GetClientsList()
	{
		return _LoadClientsDataFromFile();
	}

	static double GetTotalBalances()
	{
		double TotalBalances = 0;

		vector <clsBankClient> vClients = GetClientsList();

		for (clsBankClient C : vClients)
		{
			TotalBalances += C.AccountBalance;
		}

		return TotalBalances;
	}

	void Deposit(double Amount)
	{
		_AccountBalance += Amount;
		Save();
	}

	bool Withdraw(double Amount)
	{
		if (Amount > _AccountBalance)
		{
			return false;
		}
		else
		{
			_AccountBalance -= Amount;
			Save();
		}
	}

	bool Tansfer(double Amount, clsBankClient& DestinationClient , string UserName)
	{
		if (Amount > AccountBalance)
		{
			return false;
		}

		Withdraw(Amount);
		DestinationClient.Deposit(Amount);

		_RegisterTransferLog(Amount, DestinationClient , UserName);

		return true;
	}	

	static vector <stTransferLogRecord> GetTransferLogList()
	{
		vector <stTransferLogRecord> vTransferLogRecord;

		fstream MyFile;

		MyFile.open("TransferLog.txt", ios::in);

		string Line;
		stTransferLogRecord TransferRecord;

		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{
				TransferRecord = _ConvertTransferLogLineToRecord(Line);
				vTransferLogRecord.push_back(TransferRecord);
			}

			MyFile.close();
		}

		return vTransferLogRecord;
	}
};

