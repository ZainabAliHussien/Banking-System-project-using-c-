#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
using namespace std;

class clsCurrencyFindScreen:protected clsScreen
{
private:
	enum enCurrencyFindOption {eFindByCode=1,eFindByCountry=2};

	static short _ReadCurrencyFindOption()
	{    
		cout << "Find By: [1] Code or [2] Country ? ";
		short Choice = clsInputValidate::ReadNumberBetween<short>(1, 2, "Enter Number between 1 to 2 ? ");
		return Choice;
	}
	static void _PrintCurrency(clsCurrency Currency)
	{
		cout << "\nCurrency Card:\n";
		cout << "\n------------------------------- \n";
		cout << "\nCountry   :" << Currency.Country();
		cout << "\nCode      :" << Currency.CurrencyCode();
		cout << "\nName      :" << Currency.CurrencyName();
		cout << "\nRate(1$)= :" << Currency.Rate();
		cout << "\n------------------------------- \n";
	}
	static void _ShowResult(clsCurrency Currency)
	{
		if (!Currency.IsEmpty())
		{
			cout << "\nCurrency Found :-)\n";
			_PrintCurrency(Currency);
		}
		else
		{
			cout << "\nCurrency Was not Found :-(\n";
		}
	}
	static void _PerformCurrencyFindOption(enCurrencyFindOption CurrencyFindOption)
	{
		switch (CurrencyFindOption)
		{
		case enCurrencyFindOption::eFindByCode:
		{
			cout << "Please Enter Currency code: ";
			string CurrencyCode = clsInputValidate::ReadString();
			clsCurrency Currency1 = clsCurrency::FindByCode(CurrencyCode);
			_ShowResult(Currency1);
			break;
		}
		case enCurrencyFindOption::eFindByCountry:
		{
			cout << "Please Enter Country Name: ";
			string CurrencyCountry = clsInputValidate::ReadString();
			clsCurrency Currency1 = clsCurrency::FindByCountry(CurrencyCountry);
			_ShowResult(Currency1);
            break;
		}
		}
	}
public:
	static void ShowCurrencyFindScreen()
	{
		_DrawScreenHeader("    Find Currency Screen");
		_PerformCurrencyFindOption(enCurrencyFindOption(_ReadCurrencyFindOption()));
	}
};

