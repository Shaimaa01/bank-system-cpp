#pragma once
#include "Global.h"

class clsLoginRegister
{
private:



	static void _LoadCurrentUserDateToFile()
	{
		fstream MyFile;

		MyFile.open("LoginRegister.txt", ios::out | ios::app);

		string Line = PrepareLogInRecord();

		if (MyFile.is_open())
		{
			MyFile << Line << endl;

			MyFile.close();
		}
	}

public:
	static void LoginRegister()
	{
		_LoadCurrentUserDateToFile();
	}
};

