#pragma once
#include <iostream>
#include <fstream>
#include "clsString.h"
#include <vector>
using namespace std;

class clsCurrency
{
private:

	enum enMode {EmptyMode=0,UpdateMode=1};
	enMode _Mode;
	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float  _Rate; 

	static string _ConverCurrencyObjectToLine(clsCurrency Currency,string Seperator="#//#")
	{
		string stCurrencyRecord = "";
		stCurrencyRecord += Currency.Country() + Seperator;
		stCurrencyRecord += Currency.CurrencyCode() + Seperator;
		stCurrencyRecord += Currency.CurrencyName() + Seperator;
		stCurrencyRecord += to_string(Currency.Rate()) ;
		return stCurrencyRecord;
	}
	static void _SaveCurrencyDataToFile(vector<clsCurrency> vCurrency)
	{
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::out);//overwrite
		string DataLine;
		if (MyFile.is_open())
		{
			for (clsCurrency& C : vCurrency)
			{
				DataLine = _ConverCurrencyObjectToLine(C);
				MyFile << DataLine << endl;
			}

			MyFile.close();
		}
		
	}
	static clsCurrency _ConverLineToCurrencyRecord(string Line, string Seperator = "#//#")
	{
		vector<string> vRecord =clsString::Split(Line, Seperator);
		return clsCurrency(enMode::UpdateMode, vRecord[0], vRecord[1], vRecord[2], stof(vRecord[3]));
	}
	static  vector <clsCurrency> _LoadCurrencyDataFromFile()
	{

		vector <clsCurrency> vCurrency;

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{

			string Line;


			while (getline(MyFile, Line))
			{

				clsCurrency Currency = _ConverLineToCurrencyRecord(Line);

				vCurrency.push_back(Currency);
			}

			MyFile.close();
		}
		return vCurrency;
	}
	void _Update()
	{
		vector<clsCurrency> vCurrency = _LoadCurrencyDataFromFile();
		for (clsCurrency & C : vCurrency)
		{
			if (C.CurrencyCode() == CurrencyCode())
			{
				C._Rate = _Rate ;
				break;
			}
		}
		_SaveCurrencyDataToFile(vCurrency);
	}
	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}
public:
	clsCurrency(enMode Mode,string Country,string CurrencyCode,string CurrencyName,float Rate)
	{
	    _Mode= Mode;
		_Country= Country;
		_CurrencyCode= CurrencyCode;
	    _CurrencyName= CurrencyName;
		_Rate = Rate;
	}
	string Country()
	{
		return _Country;
	}
	//IQD
	string CurrencyCode()
	{
		return _CurrencyCode;
	}
	//Iraqi Dinar
	string CurrencyName()
	{
		return _CurrencyName;
	}
	void UpdateRate(float NewRate)
	{
		_Rate = NewRate;
		_Update();
	}
	float Rate()
	{
		return _Rate;
	}

	bool IsEmpty()
	{
		return (_Mode==enMode::EmptyMode);
	}
	static clsCurrency FindByCode(string CurrencyCode)
	{
		CurrencyCode = clsString::UpperAllString(CurrencyCode);
		

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{

			string Line;


			while (getline(MyFile, Line))
			{

				clsCurrency C = _ConverLineToCurrencyRecord(Line);
				if (C.CurrencyCode() == CurrencyCode)
				{
					MyFile.close();
					return C;
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
		MyFile.open("Currencies.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{

			string Line;


			while (getline(MyFile, Line))
			{

				clsCurrency C = _ConverLineToCurrencyRecord(Line);
				if (clsString::UpperAllString(C.Country()) == Country)
				{
					MyFile.close();
					return C;
				}
			}
			MyFile.close();
		}
		return _GetEmptyCurrencyObject();
	}
	static bool IsCurrencyExist(string CurrencyCode)
	{
		clsCurrency Currency = FindByCode(CurrencyCode);
		return !(Currency.IsEmpty());
	}
	static vector <clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrencyDataFromFile();
	}
	float ConvertToUSD(float Amount)
	{
		return (float)(Amount / Rate());
	}
	float ConvertToOtherCurrency(float Amount, clsCurrency Currency2)
	{
		float AmountToUSD = ConvertToUSD(Amount);
		if (Currency2.CurrencyCode() == "USD")
		{
			return AmountToUSD;
		}
		return (float)(AmountToUSD * Currency2.Rate());
	}
};

