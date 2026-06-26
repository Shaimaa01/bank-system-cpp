#pragma once
#include <iostream>
#include "clsCurrency.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsUpdateCurrencyRateScreen : protected clsScreen
{
private:

	static float _ReadRate()
	{
		cout << "\nEnter New Rate: ";
		float NewRate = 0;

		NewRate = clsInputValidate::ReadNumber<float>();
		return NewRate;
	}

	static void _PrintCurrency(clsCurrency Currency)
	{
		cout << "\nCurrency Card:\n";
		cout << "__________________________________\n";
		cout << "\nCourntry    : " << Currency.Country();
		cout << "\nCode        : " << Currency.CurrencyCode();
		cout << "\nName        : " << Currency.CurrencyName();
		cout << "\nRate(1$) =  : " << Currency.Rate();
		cout << "\n__________________________________\n";
	}

public:

	static void ShowUpdateCurrencyRateScreen()
	{
		_DrawScreenHeader("\t  Update Currency Screen");

		cout << "\nPlease Enter Currency Code: ";

		string CurrencyCode = clsInputValidate::ReadString();
		


		while (!clsCurrency::IsCurrencyExist(CurrencyCode))
		{
			cout << "\nCurrency is not found , choose another one: ";
			CurrencyCode = clsInputValidate::ReadString();
		}

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		_PrintCurrency(Currency);

		cout << "\nAre you sure you want to update the rate of this Currency y/n? ";
		char Answer = 'n';
		cin >> Answer; 

		if (Answer == 'y' || Answer == 'Y')
		{
			cout << "\nUpdate Currency Rate:\n";
			cout << "________________________\n";

			Currency.UpdateRate(_ReadRate());

			cout << "\nCurrency Rate Updated Successfully :-)\n";
			_PrintCurrency(Currency);
		}
	}

};

