#pragma once
#include <iostream>
#include <vector>

using namespace std;

class clsString
{
private:
	string _Value;

public:

	clsString()
	{
		_Value = "";
	}

	clsString(string Value)
	{
		_Value = Value;
	}

	void SetValue(string Value)
	{
		_Value = Value;
	}

	string GetValue()
	{
		return _Value;
	}

	__declspec(property(put = SetValue, get = GetValue)) string Value;

	static short Length(string S1)
	{
		return S1.length();
	}

	short Length()
	{
		return _Value.length();
	}

	static short CountWords(string S1)
	{
		string delim = " ";
		int Counter = 0;
		string sWord;
		int pos = 0;

		while ((pos = S1.find(delim)) != S1.npos)
		{
			sWord = S1.substr(0, pos);
			if (sWord != "")
			{
				Counter++;
			}

			S1.erase(0, pos + delim.length());
		}

		if (S1 != "")
		{
			Counter++;
		}

		return Counter;
	}

	short CountWords()
	{
		return CountWords(_Value);
	}

	static string UpperFirstLetterOfEachWord(string S1)
	{
		bool IsFirstLetter = true;

		for (int i = 0; i < S1.length(); i++)
		{
			if (S1[i] != ' ' && IsFirstLetter)
			{
				S1[i] = toupper(S1[i]);
			}

			IsFirstLetter = (S1[i] == ' ' ? true : false);
		}

		return S1;
	}

	void UpperFirstLetterOfEachWord()
	{
		_Value = UpperFirstLetterOfEachWord(_Value);
	}

	static string LowerFirstLetterOfEachWord(string S1)
	{
		bool IsFirstLetter = true;

		for (int i = 0; i < S1.length(); i++)
		{
			if (S1[i] != ' ' && IsFirstLetter)
			{
				S1[i] = tolower(S1[i]);
			}

			IsFirstLetter = (S1[i] == ' ' ? true : false);
		}

		return S1;
	}

	void LowerFirstLetterOfEachWord()
	{
		_Value = LowerFirstLetterOfEachWord(_Value);
	}

	static string UpperAllString(string S1)
	{
		for (int i = 0; i < S1.length(); i++)
		{
			S1[i] = toupper(S1[i]);
		}
		return S1;
	}

	void UpperAllString()
	{
		_Value = UpperAllString(_Value);
	}

	static string LowerAllString(string S1)
	{
		for (int i = 0; i < S1.length(); i++)
		{
			S1[i] = tolower(S1[i]);
		}
		return S1;
	}

	void LowerAllString()
	{
		_Value = LowerAllString(_Value);
	}

	static char InverLetterCase(char Char1)
	{
		return isupper(Char1) ? tolower(Char1) : toupper(Char1);
	}

	static string InvertAllLettersCase(string S1)
	{
		for (int i = 0; i < S1.length(); i++)
		{
			S1[i] = InverLetterCase(S1[i]);
		}

		return S1;
	}

	void InvertAllLettersCase()
	{
		_Value = InvertAllLettersCase(_Value);
	}

	enum enWhatToCount { SmallLetters = 0, CapitalLetters = 1, All = 2 };

	static short CountLetters(string S1, enWhatToCount WhatToCount = All)
	{
		if (WhatToCount == enWhatToCount::All)
			return S1.length();

		short Counter = 0;

		for (int i = 0; i < S1.length(); i++)
		{
			if (WhatToCount == enWhatToCount::SmallLetters && islower(S1[i]))
				Counter++;

			if (WhatToCount == enWhatToCount::CapitalLetters && isupper(S1[i]))
				Counter++;
		}

		return Counter;
	}

	static int CountCapitalLetters(string S1)
	{
		int Counter = 0;
		for (int i = 0; i < S1.length(); i++)
		{
			if (isupper(S1[i]))
			{
				Counter++;
			}
		}
		return Counter;
	}

	int CountCapitalLetters()
	{
		return CountCapitalLetters(_Value);
	}

	static int CountSmallLetters(string S1)
	{
		int Counter = 0;
		for (int i = 0; i < S1.length(); i++)
		{
			if (islower(S1[i]))
			{
				Counter++;
			}
		}
		return Counter;
	}

	int CountSmallLetters()
	{
		return CountSmallLetters(_Value);
	}

	static short CountSpecificLetter(string S1, char Letter, bool MatchCase = true)
	{
		short Counter = 0;

		for (int i = 0; i < S1.length(); i++)
		{
			if (MatchCase)
			{
				if (S1[i] == Letter)
					Counter++;
			}
			else
			{
				if (tolower(S1[i]) == tolower(Letter))
					Counter++;
			}

		}

		return Counter;
	}

	short CountSpecificLetter(char Letter, bool MatchCase = true)
	{
		return CountSpecificLetter(_Value, Letter, MatchCase);
	}

	static bool IsVowel(char Char1)
	{
		Char1 = tolower(Char1);

		return (Char1 == 'a' || Char1 == 'e' || Char1 == 'i' || Char1 == 'o' || Char1 == 'u');
	}

	static int CountVowels(string S1)
	{
		int Counter = 0;

		for (int i = 0; i < S1.length(); i++)
		{
			if (IsVowel(S1[i]))
			{
				Counter++;
			}
		}
		return Counter;
	}

	int CountVowels()
	{
		return CountVowels(_Value);
	}

	static vector <string> Split(string S1, string delim)
	{
		vector <string> vString;
		string sWord;
		int pos = 0;

		while ((pos = S1.find(delim)) != S1.npos)
		{
			sWord = S1.substr(0, pos);
			if (sWord != "")
			{
				vString.push_back(sWord);
			}

			S1.erase(0, pos + delim.length());
		}

		if (S1 != "")
		{
			vString.push_back(S1);
		}

		return vString;
	}

	vector <string> Split(string delim)
	{
		return Split(_Value, delim);
	}

	static string TrimLeft(string S1)
	{
		for (int i = 0; i < S1.length(); i++)
		{
			if (S1[i] != ' ')
			{
				return S1.substr(i, S1.length() - i);
			}
		}
		return "";
	}

	void TrimLeft()
	{
		_Value = TrimLeft(_Value);
	}

	static string TrimRight(string S1)
	{
		for (int i = S1.length() - 1; i >= 0; i--)
		{
			if (S1[i] != ' ')
			{
				return S1.substr(0, i + 1);
			}
		}
		return "";
	}

	void TrimRight()
	{
		_Value = TrimRight(_Value);
	}

	static string Trim(string S1)
	{
		return TrimLeft(TrimRight(S1));
	}

	void Trim()
	{
		_Value = Trim(_Value);
	}

	static string JoinString(vector <string> vString, string delim)
	{
		string S1 = "";

		for (string& s : vString)
		{
			S1 += s + delim;
		}

		return S1.substr(0, S1.length() - delim.length());
	}

	static string JoinString(string arrString[], short Length, string delim)
	{
		string S2 = "";

		for (int i = 0; i < Length; i++)
		{
			S2 += arrString[i] + delim;
		}

		return S2.substr(0, S2.length() - delim.length());
	}

	static string ReverseWordsInString(string S1)
	{
		vector <string> vString = Split(S1, " ");
		string S2 = "";

		vector <string>::iterator iter = vString.end();

		while (iter != vString.begin())
		{
			--iter;

			S2 += *iter + " ";
		}

		S2 = S2.substr(0, S2.length() - 1);

		return S2;
	}

	void ReverseWordsInString()
	{
		_Value = ReverseWordsInString(_Value);
	}

	static string ReplaceWord(string S1, string StringToReplace, string sReplaceTo, bool MatchCase = true)
	{
		vector <string> vString = Split(S1, " ");

		for (string& s : vString)
		{
			if (MatchCase)
			{
				if (s == StringToReplace)
					s = sReplaceTo;
			}
			else
			{
				if (LowerAllString(s) == LowerAllString(StringToReplace))
					s = sReplaceTo;
			}
		}

		return JoinString(vString, " ");
	}

	string ReplaceWord(string StringToReplace, string sReplaceTo)
	{
		return ReplaceWord(_Value, StringToReplace, sReplaceTo);
	}

	static string RemovePunctuations(string S1)
	{
		string S2 = "";

		for (int i = 0; i < S1.length(); i++)
		{
			if (!ispunct(S1[i]))
			{
				S2 += S1[i];
			}
		}

		return S2;
	}

	void RemovePunctuations()
	{
		_Value = RemovePunctuations(_Value);
	}
};


