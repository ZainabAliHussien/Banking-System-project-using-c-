#pragma once
#include <iostream>
#include"clsInputValidate.h";
#include"clsBankClient.h";
#include "clsScreen.h"
using namespace std;

class clsDeleteClientScreen:protected clsScreen
{
private:
      
    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n____________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\_____________________\n";

    }

public:

     static void ShowDeleteClientScreen()
    {
         if (!CheckAccessPermission(clsUser::enPermissionOption::DelPermission))
         {
             return;
         }
        _DrawScreenHeader("\t Delete Client Screen");

        string AccountNumber = "";
        cout << "\nPlease Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found,please enter another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        cout << "\nAre you sure you want to delete this client y/n ? ";
        char Answer = 'n';
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            if (Client.Delete())
            {
                cout << "\nAccount Deleted Successfully :-)\n";
                _PrintClient(Client);
            }
            else
            {
                cout << "\nError, account was not deleted\n";
            }
        }
    }
};




