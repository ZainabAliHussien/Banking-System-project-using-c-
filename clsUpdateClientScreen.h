#pragma once
#include <iostream>
#include"clsInputValidate.h";
#include"clsBankClient.h";
#include"clsScreen.h"
using namespace std;

class clsUpdateClientScreen:protected clsScreen
{
private:
     static void  ReadClientInfo(clsBankClient& Client)
     {
         cout << "\nEnter FirstName: ";
         Client.FirstName = clsInputValidate::ReadString();

         cout << "\nEnter LastName: ";
         Client.LastName = clsInputValidate::ReadString();

         cout << "\nEnter Email: ";
         Client.Email = clsInputValidate::ReadString();

         cout << "\nEnter Phone: ";
         Client.Phone = clsInputValidate::ReadString();

         cout << "\nEnter PinCode: ";
         Client.PinCode = clsInputValidate::ReadString();

         cout << "\nEnter Account Balance: ";
         Client.AccountBalance = clsInputValidate::ReadNumber<float>();
     }
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

   static void ShowUpdateClientScreen()
    {
       if (!CheckAccessPermission(clsUser::enPermissionOption::UpdatePermission))
       {
           return;
       }
       _DrawScreenHeader("\t Update Client Screen");

        string AccountNumber = "";
        cout << "\nPlease Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found,please enter another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient( Client);

        cout << "\nUpdate Client Info:";
        cout << "\n-------------------\n";
        ReadClientInfo(Client);


        clsBankClient::enSaveResults SaveResult;
        SaveResult = Client.Save();

        switch (SaveResult)
        {
        case clsBankClient::svFaildEmptyObject:
            cout << "\nError account was not saved because its empty";
            break;
        case clsBankClient::svSaveSucceeded:
            cout << "\nAccount Update Successfully :-)\n";
            _PrintClient( Client);
            break;
        }
    }
};





