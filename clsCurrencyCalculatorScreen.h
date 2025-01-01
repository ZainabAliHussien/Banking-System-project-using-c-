#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
using namespace std;

class clsCurrencyCalculatorScreen :protected clsScreen
{
private:
	static clsCurrency _GetCurrency(string message)
	{
		cout << message<<endl;
		string CurrencyCode = clsInputValidate::ReadString();
		while (! clsCurrency::IsCurrencyExist(CurrencyCode))
		{
			cout << "\nCurrency is not found, choose another one : ";
			string CurrencyCode = clsInputValidate::ReadString();
		}
		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		return Currency;
	}
	static float _ReadAmount()
	{
		float Amount = 0;
		cout << "Enter Amount to Exchange: ";
		Amount = clsInputValidate::ReadNumber<float>();
		return Amount;
	}
	static void _PrintCurrency(clsCurrency Currency,string Title="Currency Card:")
	{
		cout << "\n"<<Title<<"\n";
		cout << "\n------------------------------- \n";
		cout << "\nCountry   :" << Currency.Country();
		cout << "\nCode      :" << Currency.CurrencyCode();
		cout << "\nName      :" << Currency.CurrencyName();
		cout << "\nRate(1$)= :" << Currency.Rate();
		cout << "\n------------------------------- \n";
	}
	static void _PrintCalculatorResults(float Amount, clsCurrency CurrencyFrom, clsCurrency CurrencyTo)
	{
		_PrintCurrency(CurrencyFrom, "Convert From:");
		float AmountInUSD = CurrencyFrom.ConvertToUSD(Amount);

		cout << Amount << " " << CurrencyFrom.CurrencyCode() << " = " << AmountInUSD << "USD\n";
		if (CurrencyTo.CurrencyCode() == "USD")
		{
			return;
		}
		cout << "\n\nConverting from USD to:\n";
		_PrintCurrency(CurrencyTo,"To");
		float AmountInCurrencyTo = CurrencyFrom.ConvertToOtherCurrency(Amount, CurrencyTo);
		cout << Amount << " " << CurrencyFrom.CurrencyCode() << " = " << AmountInCurrencyTo << " "<<CurrencyTo.CurrencyCode();

	}
public:
	static void ShowCurrencyCalculator()
	{
		char Continue = 'y';
		while (Continue == 'y' || Continue == 'Y')
		{
			system("cls");
			_DrawScreenHeader("    Find Currency Screen");

			
			clsCurrency CurrencyFrom = _GetCurrency("Please Enter Currency1 code:");
			clsCurrency CurrencyTo = _GetCurrency("Please Enter Currency2 code:");
			float Amount = _ReadAmount();
			
			_PrintCalculatorResults(Amount, CurrencyFrom, CurrencyTo);

			cout << "\n\nDo you want to perform another calculation? y/n ";
			cin >> Continue;
		}
	}
};

