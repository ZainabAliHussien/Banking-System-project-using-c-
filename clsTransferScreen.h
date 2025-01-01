#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
using namespace std;

class clsTransferScreen: protected clsScreen
{
private:
    static string _ReadAccountNumber(string message)
    {
        string AccountNumber = "";
        cout << message;
        cin >> AccountNumber;
        return AccountNumber;
    }
    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n_______";
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n_______\n";

    }
    static float _ReadAmount(clsBankClient Client)
    {
        float Amount = 0;
        cout << "\nEnter Transfer Amount? ";
        Amount = clsInputValidate::ReadNumber<float>();
        while (Amount> Client.AccountBalance)
        {
            cout << "\nAmount Exceeds the available Balance, Enter another Amount? ";
            Amount = clsInputValidate::ReadNumber<float>();
        }
        return Amount ;
    }
public:
	static void ShowTransferScreen()
	{
		_DrawScreenHeader("\t   Transfer Screen");


        string AccountNumber1 = _ReadAccountNumber("\nPlease enter AccountNumber that transfer from ? ");
        while (! clsBankClient::IsClientExist(AccountNumber1))
        {
            cout << "\nClient with [" << AccountNumber1 << "] does not exist.\n";
            AccountNumber1 = _ReadAccountNumber("\nPlease enter AccountNumber that transfer from ? ");
        }
        clsBankClient SourceClient = clsBankClient::Find(AccountNumber1);
        _PrintClient(SourceClient);


        string AccountNumber2 = _ReadAccountNumber("\nPlease enter AccountNumber that transfer to ? ");
        while (!clsBankClient::IsClientExist(AccountNumber2))
        {
            cout << "\nClient with [" << AccountNumber2 << "] does not exist.\n";
            AccountNumber2 = _ReadAccountNumber("\nPlease enter AccountNumber that transfer to ? ");
        }
        clsBankClient DestinationClient = clsBankClient::Find(AccountNumber2);
        _PrintClient(DestinationClient);
        

        float Amount = _ReadAmount(SourceClient);
        cout << "\nAre you sure you want to perform this operation? y/n? ";
        char Answer = 'n';
        cin >> Answer;
        if (Answer=='Y' || Answer=='y')
        {
            if (SourceClient.Transfer(Amount, DestinationClient,CurrentUser.UserName))
            {
                cout << "\nTransfer done successfully\n";
            }
            else
            {
                cout << "\nTransfer Failed\n";
            }
        }
        _PrintClient(SourceClient);
        _PrintClient(DestinationClient);
	}
};

