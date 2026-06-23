#pragma once
#include <iostream>
#include "IntrefaceCommunication.h"

using namespace std;

class clsPerson : public IntrefaceCommunication
{
private:
	string _FirstName;
	string _LastName;
	string _Email;
	string _Phone;

public:
	clsPerson(string FirstName , string LastName , string Email , string Phone)
	{
		_FirstName = FirstName;
		_LastName = LastName;
		_Email = Email;
		_Phone = Phone;
	}

	void SetFirstName(string FirstName)
	{
		_FirstName = FirstName;
	}

	string GetFirstName()
	{
		return _FirstName;
	}

	__declspec(property(put = SetFirstName, get = GetFirstName)) string FirstName;

	void SetLastName(string LastName)
	{
		_LastName = LastName;
	}

	string GetLastName()
	{
		return _LastName;
	}

	__declspec(property(put = SetLastName, get = GetLastName)) string LastName;

	void SetEmail(string Email)
	{
		_Email = Email;
	}

	string GetEmail()
	{
		return _Email;
	}

	__declspec(property(put = SetEmail, get = GetEmail)) string Email;

	void SetPhone(string Phone)
	{
		_Phone = Phone;
	}

	string GetPhone()
	{
		return _Phone;
	}

	__declspec(property(put = SetPhone, get = GetPhone)) string Phone;

	string FullName()
	{
		return _FirstName + " " + _LastName;
	}

	void SendEmail(string Title, string Body)
	{

	}

	void SendFax(string Title, string Body)
	{

	}

	void SendSMS(string Title, string Body)
	{

	}
};

