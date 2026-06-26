#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"

using namespace std;

class clsCurrencyExchangeMainScreen : public clsScreen
{
private:
	enum enCurrencyExchangeMenueOptions {eListCurrencies =1 , eFindCurrency = 2 , eUpdateCurrencyRate = 3 , eCurrencyCalculator = 4 , enMainMenu = 5 };

	static short _ReadCurrenciesMainMenueOptions()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
		short Choice = clsInputValidate::ReadshortNumberBetween(1, 5, "Number should be betwwen 1 to 5 , Enter again:");
		return Choice;
	}

	static void _ShowCurrenciesListScreen()
	{
		clsCurrenciesListScreen::ShowCurrenciesListScreen();
	}

	static void _ShowFindCurrencyScreen()
	{
		clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}

	static void _ShowUpdateCurrencyRateScreen()
	{
		clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
	}

	static void _ShowCurrencyCalculatorScreen()
	{
		clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
	}

	static void _GoBackToCurrenciesMenue()
	{
		cout << "\n\nPress any key to go back to Currencies Menue...";
		system("pause > nul");
		ShowCurrencyExchangeMenu();
	}

	static void _PerformCurrenciesMainMenueOptions(enCurrencyExchangeMenueOptions CurrencyExchangeMenueOption)
	{
		switch (CurrencyExchangeMenueOption)
		{
		case(enCurrencyExchangeMenueOptions::eListCurrencies):
			system("cls");
			_ShowCurrenciesListScreen();
			_GoBackToCurrenciesMenue();
			break;

		case(enCurrencyExchangeMenueOptions::eFindCurrency):
			system("cls");
			_ShowFindCurrencyScreen();
			_GoBackToCurrenciesMenue();
			break;

		case(enCurrencyExchangeMenueOptions::eUpdateCurrencyRate):
			system("cls");
			_ShowUpdateCurrencyRateScreen();
			_GoBackToCurrenciesMenue();
			break;

		case(enCurrencyExchangeMenueOptions::eCurrencyCalculator):
			system("cls");
			_ShowCurrencyCalculatorScreen();
			_GoBackToCurrenciesMenue();
			break;

		case(enCurrencyExchangeMenueOptions::enMainMenu):
		{
			// main menu will handle it :-)
		}
		}
	}

public: 
	static void ShowCurrencyExchangeMenu()
	{
		system("cls");

		_DrawScreenHeader("\t Currency Exchange Main Screen");

		if (!AccessPermissionsRight(clsUser::enPermissions::pCurrencyExchange))
		{
			return;
		}

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t  Currency Exchange Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
		cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
		cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
		cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
		cout << setw(37) << left << "" << "\t[5] Main Menue.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_PerformCurrenciesMainMenueOptions((enCurrencyExchangeMenueOptions)_ReadCurrenciesMainMenueOptions());
	}
};

