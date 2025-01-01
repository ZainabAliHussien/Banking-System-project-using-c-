#pragma once
#include<iostream>
#include<cstdlib>
#include<string>
#include"clsDate.h"
using namespace std;

class clsUtil
{
public:
	enum enCharType { SmallLetter = 1, CapitallLetter = 2, Degit = 3,MixChars=4 , SpecialCharacter = 5 }; // random char enum



	 static void Srand()
	 {
		 srand((unsigned)time(NULL));
	 }
	// random num function
	static int RandomNumber(int from, int To)
	{

		int Rand = rand() % (To - from + 1) + from;

		return Rand;
	}


	static char GetRandomCharacter(enCharType CharType)  // function which generate random number or char depending on our choice
	{
		if (CharType == enCharType::MixChars)
		{
			CharType = (enCharType)RandomNumber(1, 3);
		}
		switch (CharType)
		{
		case enCharType::SmallLetter:
			return RandomNumber(97, 122);
		case enCharType::CapitallLetter:
			return RandomNumber(65, 90);
		case enCharType::SpecialCharacter:
			return RandomNumber(33, 47);
		case enCharType::Degit:
			return RandomNumber(48, 57);

		default:
			return RandomNumber(65, 90);

			break;
		}

	}


	static string GenerateWord(enCharType CharType, short Length) // function to generate Random word depending on the random char generated above
	{
		string Word = "";

		for (int i = 1; i <= Length; i++)
		{
			Word += GetRandomCharacter(CharType);

		}

		return Word;
	}


	static string GenerateKey(enCharType CharType) // function which generates Key by gathering words generated Above
	{
		string Key = "";

		Key += GenerateWord(CharType, 4) + "-";
		Key += GenerateWord(CharType, 4) + "-";
		Key += GenerateWord(CharType, 4) + "-";
		Key += GenerateWord(CharType, 4);

		return Key;
	}


	static void GenerateKeys(enCharType CharType, int NumKeys) // function to generate keys as much as you want  depending on key generated above
	{
		for (int i = 1; i <= NumKeys; i++)
		{
			cout << "Key[" << i << "] : ";
			cout << GenerateKey(CharType) << endl;

		}

	}


	static void Swap(int& a, int& b) // int swap function
	{
		int Temp;

		Temp = a;
		a = b;
		b = Temp;

	}


	static void Swap(double& a, double& b)  //double swap function
	{
		double Temp;

		Temp = a;
		a = b;
		b = Temp;

	}

	static void Swap(string& a, string& b) //string swap function
	{
		string Temp;

		Temp = a;
		a = b;
		b = Temp;

	}

	static void Swap(clsDate& a, clsDate& b) //dates swap function
	{
		clsDate Temp;

		Temp = a;
		a = b;
		b = Temp;

	}

	static void ShuffleArray(int arr[100], int arrLength) // int shuffle arr functtion
	{

		for (int i = 0; i < arrLength; i++)
		{
			Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
		}

	}

	static void ShuffleArray(string arr[100], int arrLength) // string shuffle arr functtion
	{

		for (int i = 0; i < arrLength; i++)
		{
			Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
		}

	}

	static void FillArrWithRandomNumbers(int Arr[100], int ArrLength, int From, int To)
	{
		/*cout << "how many elements in the array ?\n";
		cin >> ArrLength;*/

		for (int i = 0; i < ArrLength; i++)
		{
			Arr[i] = RandomNumber(From, To);

		}

	}

	static void FillArrayWithRandomWords(string Arr[100], int ArrLength, enCharType CharType, int Wordlength)
	{
		for (int i = 0; i < ArrLength; i++)
		{
			Arr[i] = GenerateWord(CharType, Wordlength);
		}

	}

	static void FillArrWithRandomKeys(string Arr[100], int ArrLength, enCharType CharType)
	{
		for (int i = 0; i < ArrLength; i++)
		{
			Arr[i] = GenerateKey(CharType);
		}


	}



	static string Tabs(int NumOfTabs) // function to generate spaces (tabs) as much as you want
	{
		string tab = "";

		for (int i = 0; i < NumOfTabs; i++)
		{
			tab += "\t";
		}

		return tab;
	}

	static string EncryptText(string Text, int EncryptionKey=2) // Encrypt Text function
	{

		for (int i = 0; i <= Text.length(); i++)
		{

			Text[i] = char((int)Text[i] + EncryptionKey);

		}

		return Text;
	}

	static string DecryptText(string Text, int EncryptionKey=2)// Decrypion text function
	{

		for (int i = 0; i <= Text.length(); i++)
		{

			Text[i] = char((int)Text[i] - EncryptionKey);

		}

		return Text;
	}

	static string NumberToText(int Num) //Function that turns Number to string  using recursion
	{
		if (Num == 0)
		{
			return"";
		}

		if (Num >= 1 && Num <= 19)
		{
			string Arr[] = { "","One","Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Eleven","Twelve",
			"Therteen","FourTeen","Feefteen","SixTeen","Seventeen","Eighteen","Nineteen" };

			return Arr[Num] + " ";

		}

		if (Num >= 20 && Num <= 99)
		{
			string Arr[] = { "","","Twenty","Thirty","Fourty","Fifty","Sixty","Seventy","Eighty","Ninety" };

			return Arr[Num / 10] + " " + NumberToText(Num % 10);

		}
		if (Num >= 100 && Num <= 199)
		{

			return "One Handred " + NumberToText(Num % 100);

		}

		if (Num >= 200 && Num <= 999)
		{
			return  NumberToText(Num / 100) + "Hundreds " + NumberToText(Num % 100) + " ";
		}

		if (Num >= 1000 && Num <= 1999)
		{

			return  "One Thousands " + NumberToText(Num % 1000);
		}

		if (Num >= 2000 && Num <= 999999)
		{
			return NumberToText(Num / 1000) + "Thaousands " + NumberToText(Num % 1000);
		}

		if (Num >= 1000000 && Num <= 1999999)
		{
			return  " One Million " + NumberToText(Num % 1000000);
		}

		if (Num >= 2000000 && Num <= 999999999)
		{
			return  NumberToText(Num / 1000000) + " Milions " + NumberToText(Num % 1000000);

		}

		if (Num >= 1000000000 && Num <= 1999999999)
		{
			return  "One Bilion " + NumberToText(Num % 1000000000);
		}

		else
		{
			return NumberToText(Num / 1000000000) + "Bilions " + NumberToText(Num % 1000000000);
		}



	}



};

