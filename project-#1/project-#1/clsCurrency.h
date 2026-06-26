#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "clsString.h"

using namespace std;

class clsCurrency
{
private:

	enum enMode { enEmptyMode = 0 , enUpdateMode = 1 };
	enMode _Mode;

	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;

	static clsCurrency _ConvertLinetoCurrencyObject(string Line , string Seperator = "#//#")
	{
		vector <string> vCurrencyData = clsString::Split(Line, Seperator);
		return clsCurrency(enMode::enUpdateMode, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2], stof(vCurrencyData[3]));
	}

	string _ConvertCurrecyObjectToLine(clsCurrency CurrencyData, string Seperator = "#//#")
	{
		string stCurrencyRecord;

		stCurrencyRecord += CurrencyData.Country() + Seperator;
		stCurrencyRecord += CurrencyData.CurrencyCode() + Seperator;
		stCurrencyRecord += CurrencyData.CurrencyName() + Seperator;
		stCurrencyRecord += to_string(CurrencyData.Rate());

		return stCurrencyRecord;
	}

	static vector <clsCurrency> _LoadCurrencysDataFromFile()
	{
		vector <clsCurrency> vCurrencys;

		fstream MyFile;

		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				vCurrencys.push_back(_ConvertLinetoCurrencyObject(Line));
			}

			MyFile.close();
		}

		return vCurrencys;
	}

	void _SaveCurrencyDataToFile(vector <clsCurrency> vCurrencys)
	{
		fstream MyFile;

		MyFile.open("Currencies.txt", ios::out);

		if (MyFile.is_open())
		{
			string DataLine;

			for (clsCurrency C : vCurrencys)
			{
				DataLine = _ConvertCurrecyObjectToLine(C);

				MyFile << DataLine << endl;
			}

			MyFile.close();
		}
	}

	void _Update()
	{
		vector <clsCurrency> vCurrencys = _LoadCurrencysDataFromFile();

		for (clsCurrency &C : vCurrencys)
		{
			if (C.Country() == Country())
			{
				C = *this;
				break;
			}
		}

		_SaveCurrencyDataToFile(vCurrencys);
	}

	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(enMode::enEmptyMode, "", "", "", 0);
	}

public:

	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	string Country()
	{
		return _Country;
	}

	string CurrencyCode()
	{
		return _CurrencyCode;
	}

	string CurrencyName()
	{
		return _CurrencyName;
	}

	float Rate()
	{
		return _Rate; 
	}

	void UpdateRate(float NewRate)
	{
		_Rate = NewRate;
		_Update();
	}

	bool IsEmpty()
	{
		return _Mode == enEmptyMode;
	}

	static clsCurrency FindByCode(string CurrencyCode)
	{
		CurrencyCode = clsString::UpperAllString(CurrencyCode);

		fstream MyFile;

		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);

			if (clsString::UpperAllString(Currency.CurrencyCode()) == CurrencyCode)
			{
				MyFile.close();
				return Currency;
			}
			}

			MyFile.close();
		}

		return _GetEmptyCurrencyObject();
	}

	static clsCurrency FindByCountry(string Country)
	{
		Country = clsString::UpperAllString(Country);

		fstream MyFile;

		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);

				if (clsString::UpperAllString(Currency.Country()) == Country)
				{
					MyFile.close();
					return Currency;
				}
			}

			MyFile.close();
		}

		return _GetEmptyCurrencyObject();
	}

	static bool  IsCurrencyExist(string CurrencyCode)
	{
		clsCurrency C1 = FindByCode(CurrencyCode);

		return !C1.IsEmpty();
	}

	static vector <clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrencysDataFromFile();
	}

	float ConvertToUSD(float Amount)
	{
		return Amount / Rate();
	}

	float ConvertToOtherCurrency(float Amount, clsCurrency Currency2)
	{
		float AmountInUSD = ConvertToUSD(Amount);

		if (Currency2.CurrencyCode() == "USD")
		{
			return AmountInUSD;
		}

		return AmountInUSD * Currency2.Rate();
	}

};

