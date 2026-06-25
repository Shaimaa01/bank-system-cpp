#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

using namespace std;

class clsFindCurrencyScreen : protected clsScreen
{
private:
	static void _PrintCurrecy(clsCurrency Currency)
	{
		cout << "\nCurrency Card:\n";
		cout << "__________________________________\n";
		cout << "\nCourntry    : " << Currency.Country();
		cout << "\nCode        : " << Currency.CurrencyCode();
		cout << "\nName        : " << Currency.CurrencyName();
		cout << "\nRate(1$) =  : " << Currency.Rate();
		cout << "\n__________________________________\n";
	}

	static void _ShowResults(clsCurrency Currency)
	{
		if (!Currency.IsEmpty())
		{
			cout << "\nCurrency Found :-)";
			_PrintCurrecy(Currency);
		}
		else
		{
			cout << "\nCurrency Not Found ;-(";
		}
	}

public:
	static void ShowFindCurrencyScreen()
	{
		_DrawScreenHeader("\t  Find Currency Screen");

		cout << "\nFind By: [1] Code or [2] Country ? ";
		short Answer = clsInputValidate::ReadshortNumberBetween(1, 2, "Number should be between 1 to 2 , Enter Again:");

		if (Answer == 1)
		{
			cout << "\nPlease Enter CurrencyCode: ";
			string CurrencyCode = clsInputValidate::ReadString();
			clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
			_ShowResults(Currency);
		}
		else
		{
			cout << "\nPlease Enter CurrencyName: ";
			string CurrencyName = clsInputValidate::ReadString();
			clsCurrency Currency = clsCurrency::FindByCountry(CurrencyName);
			_ShowResults(Currency);
		}
	}
};

