#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsCurrencyCalculatorScreen : protected clsScreen
{
private:

	static float _ReadAmount()
	{
		cout << "\nEnter Amount to Exchange: ";
		float Amount = clsInputValidate::ReadNumber<float>();
		return Amount;
	}

	static void _PrintCurrencyCard(clsCurrency Currency , string Title)
	{
		cout << "\n" << Title << "\n";
		cout << "__________________________________\n";
		cout << "\nCourntry    : " << Currency.Country();
		cout << "\nCode        : " << Currency.CurrencyCode();
		cout << "\nName        : " << Currency.CurrencyName();
		cout << "\nRate(1$) =  : " << Currency.Rate();
		cout << "\n__________________________________\n";
	}

	static clsCurrency _GetGurrency(string Message)
	{
		cout << Message << endl;
		string CurrencyCode = clsInputValidate::ReadString();

		while (!clsCurrency::IsCurrencyExist(CurrencyCode))
		{
			cout << "\nCurrency is not found , choose another one: ";
			CurrencyCode = clsInputValidate::ReadString();
		}

		return clsCurrency::FindByCode(CurrencyCode);
	}

	static void _PrintCalculationResults(float Amount , clsCurrency Currency1 , clsCurrency Currency2)
	{
		_PrintCurrencyCard(Currency1 , "Convert From:");

		float AmountInUSD = Currency1.ConvertToUSD(Amount);
		cout << endl << Amount << " " << Currency1.CurrencyCode() 
			<< " = " << AmountInUSD << " USD\n";

		if (Currency2.CurrencyCode() == "USD")
		{
			return;
		}

		cout << "\nConverting from USD to:\n";
		_PrintCurrencyCard(Currency2, "To:");

		float AmountInCurrency2 = Currency1.ConvertToOtherCurrency(Amount, Currency2);
		cout << "\n" << Amount << " " << Currency1.CurrencyCode() 
			<< " = " << AmountInCurrency2 << Currency2.CurrencyCode();
	}

public:

	static void ShowCurrencyCalculatorScreen()
	{
		char Continue = 'y';

		while (Continue == 'Y' || Continue == 'y')
		{
			system("cls");

			_DrawScreenHeader("\t  Calculator Currency Screen");

			clsCurrency CurrencyFrom = _GetGurrency("Please Enter Currency1 Code:");
			clsCurrency CurrencyTo = _GetGurrency("\nPlease Enter Currency2 Code:");
			float Amount = _ReadAmount();

			_PrintCalculationResults(Amount , CurrencyFrom , CurrencyTo);

			cout << "\n\nDo you want to perform another calcualtion? y/n ?";
			cin >> Continue;
		};

	}
};

